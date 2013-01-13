#include "hncontentprovider.h"
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
#include <QFile>
#include "../models/articleitem.h"


#define COMMENTS_URL "http://news.ycombinator.com/item?id="

HNContentProvider :: HNContentProvider()  {
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
}

HNContentProvider::HNContentProvider(QObject* parent) : manager(new QNetworkAccessManager(this)) {
    this->parent = parent;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)),SLOT(slotRequestFinished(QNetworkReply *)));
}


void HNContentProvider :: retrieveContent() {

    QNetworkRequest request;
    request.setUrl(QUrl("http://api.ihackernews.com/page"));

    QNetworkReply *reply = 0;
    reply = manager->get(request);   
}


void HNContentProvider :: slotRequestFinished(QNetworkReply *reply) {
    QByteArray json;
    if (reply->error() > 0) {
           qDebug() << "Network error";
           qDebug() << reply->errorString();
           QFile file("qml/qGator/Components/response.txt");
           if(!file.open(QIODevice::ReadOnly)) {
               QMessageBox::information(0, "error", file.errorString());
           }
           qDebug() << file.exists();
           QTextStream in(&file);
           QString contents = in.readAll();
           file.close();

           json = contents.toUtf8();
           qDebug() << "Read from file" << json;
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
        //foreach(QString key ,jsonObject->keys()) {
        //     qDebug() << key << ":" << jsonObject->value(key) << "\n";
        // }

        ListModel* listModel = this->createListModel(jsonObject);
        emit modelReady(listModel);
   }
}

void HNContentProvider::parseSearchResults(QSharedPointer <QJsonObject> jsonObject, ListModel* listModel)
{
    QJsonValue results = jsonObject->value("results");
    if(results.isArray()) {
        QJsonArray itemsList = jsonObject->value("results").toArray();
        foreach(QJsonValue jsonValue, itemsList) {
            if(jsonValue.isObject()) {
              QJsonObject obj = jsonValue.toObject().value("item").toObject();

              if(!obj.value("title").toString().isEmpty() && !obj.value("url").toString().isEmpty() ) {
                  listModel -> appendRow(new ArticleItem(obj.value("title").toString(),
                                                       QUrl(obj.value("url").toString()),
                                                       (int) obj.value("points").toDouble(),
                                                       (int)obj.value("num_comments").toDouble(),
                                                       obj.value("postedAgo").toString(),
                                                       QUrl(COMMENTS_URL+QString::number((int)obj.value("id").toDouble()))));
              }
            }
        }
    }
}

void HNContentProvider::parseFrontPageResults(ListModel* listModel, QSharedPointer <QJsonObject> jsonObject)
{
    QJsonArray itemsList = jsonObject->value("items").toArray();
    foreach(QJsonValue jsonValue, itemsList) {
        if(jsonValue.isObject()) {
          QJsonObject obj = jsonValue.toObject();
          listModel -> appendRow(new ArticleItem(obj.value("title").toString(),
                                               QUrl(obj.value("url").toString()),
                                               (int) obj.value("points").toDouble(),
                                               (int)obj.value("commentCount").toDouble(),
                                               obj.value("postedAgo").toString(),
                                               QUrl(COMMENTS_URL+QString::number((int)obj.value("id").toDouble()))));
        }
    }
}

ListModel* HNContentProvider :: createListModel(QSharedPointer <QJsonObject> jsonObject) {
    ListModel* listModel = new ListModel(new ArticleItem,parent);

    qDebug() << "Constructing model";
    QJsonValue items = jsonObject->value("items");
    if(items.isArray()) {
        parseFrontPageResults(listModel, jsonObject);
    }
    else {
        parseSearchResults(jsonObject, listModel);
    }

    return listModel;
}


void HNContentProvider :: update() {
   retrieveContent();
}

Q_INVOKABLE void HNContentProvider::retrieveSearchResults(QString query) {

    QNetworkRequest request;
    request.setUrl(QUrl("http://api.thriftdb.com/api.hnsearch.com/items/_search?q="+QUrl::toPercentEncoding(query)));

    QNetworkReply *reply = 0;
    reply = manager->get(request);
}
