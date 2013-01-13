#include "redditcontentprovider.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QStringList>
#include <QJsonArray>
#include <QJsonValue>
#include <QMessageBox>
#include <QDate>
#include "../models/articleitem.h"


#define COMMENTS_URL "http://reddit.com"


RedditContentProvider::RedditContentProvider() {
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
}

RedditContentProvider :: RedditContentProvider(QObject* parent) : manager(new QNetworkAccessManager(this)) {
    this->parent = parent;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
}

void RedditContentProvider :: retrieveContent() {

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.reddit.com/top.json"));

    QNetworkReply *reply = 0;
    reply = manager->get(request);
}

void RedditContentProvider :: slotRequestFinished(QNetworkReply *reply) {
    QByteArray json;
    if (reply->error() > 0) {
        return;
    }
    else {
        json = reply->readAll();
    }

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument :: fromJson(json,&parseError);
    if(parseError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing" << parseError.errorString();
        qDebug() << json;
    }
    else {
        QSharedPointer <QJsonObject> jsonObject = (QSharedPointer <QJsonObject>)new QJsonObject(document.object());
//        foreach(QString key ,jsonObject->keys()) {
//             qDebug() << key << ":" << jsonObject->value(key) << "\n";
//        }

        ListModel* listModel = this->createListModel(jsonObject);
        emit modelReady(listModel);
   }
}

ListModel* RedditContentProvider :: createListModel(QSharedPointer <QJsonObject> jsonObject) {
    ListModel* listModel = new ListModel(new ArticleItem,parent);

    qDebug() << "Constructing model";
    qDebug() << jsonObject;
    QJsonValue items = jsonObject->value("data").toObject().value("children");
    if(items.isArray()) {
        parseFrontPageResults(listModel, jsonObject);
    }
    else {
        parseSearchResults(jsonObject, listModel);
    }

    return listModel;
}

void RedditContentProvider::parseSearchResults(QSharedPointer <QJsonObject> jsonObject, ListModel* listModel) {
    QJsonValue results = jsonObject->value("data").toObject().value("children").toArray();
    if(results.isArray()) {
        QJsonArray itemsList = results.toArray();
        foreach(QJsonValue jsonValue, itemsList) {
            if(jsonValue.isObject()) {
              QJsonObject obj = jsonValue.toObject().value("data").toObject();

              if(!obj.value("title").toString().isEmpty() && !obj.value("url").toString().isEmpty() ) {
                  qint64 msecs = (qint64)obj.value("created").toDouble();
                  QString title = obj.value("title").toString();
                  title.truncate(100);
                  listModel -> appendRow(new ArticleItem(title,
                                                       QUrl(obj.value("url").toString()),
                                                       (int) obj.value("score").toDouble(),
                                                       (int)obj.value("num_comments").toDouble(),
                                                       QDateTime::fromMSecsSinceEpoch(msecs*1000).toString("dd.MM.yyyy hh:mm"),
                                                       QUrl(COMMENTS_URL+obj.value("permalink").toString())));
              }
            }
        }
    }
}

void RedditContentProvider::parseFrontPageResults(ListModel* listModel, QSharedPointer <QJsonObject> jsonObject) {
    QJsonArray itemsList = jsonObject->value("data").toObject().value("children").toArray();
    foreach(QJsonValue jsonValue, itemsList) {
        if(jsonValue.isObject()) {
          QJsonObject obj = jsonValue.toObject().value("data").toObject();
          QString title = obj.value("title").toString();
          title.truncate(100);
          qint64 msecs = (qint64)obj.value("created").toDouble();
          listModel -> appendRow(new ArticleItem(title,
                                               QUrl(obj.value("url").toString()),
                                               (int) obj.value("score").toDouble(),
                                               (int)obj.value("num_comments").toDouble(),
                                               QDateTime::fromMSecsSinceEpoch(msecs*1000).toString("dd.MM.yyyy hh:mm"),
                                               QUrl(COMMENTS_URL+obj.value("permalink").toString())));
        }
    }
}



void RedditContentProvider :: update() {
   retrieveContent();
}

void RedditContentProvider::retrieveSearchResults(QString query) {

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.reddit.com/search.json?q="+QUrl::toPercentEncoding(query)));

    QNetworkReply *reply = 0;
    reply = manager->get(request);
}
