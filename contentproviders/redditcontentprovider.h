#ifndef REDDITCONTENTPROVIDER_H
#define REDDITCONTENTPROVIDER_H

#include "icontentprovider.h"
#include <QNetworkAccessManager>
#include <QSemaphore>


class RedditContentProvider : public IContentProvider
{
    Q_OBJECT

private:
    QNetworkAccessManager *manager;
    QObject* parent;

    ListModel* createListModel(QSharedPointer<QJsonObject> jsonObject);
    void parseSearchResults(QSharedPointer <QJsonObject> jsonObject, ListModel* listModel);
    void parseFrontPageResults(ListModel* listModel, QSharedPointer <QJsonObject> jsonObject);

public:
    RedditContentProvider();
    RedditContentProvider(QObject* parent);

    virtual void retrieveContent() override;
    Q_INVOKABLE virtual void retrieveSearchResults(QString query) override;

public slots:
    void slotRequestFinished(QNetworkReply* reply);
    virtual void update() override;
};

#endif // REDDITCONTENTPROVIDER_H
