#ifndef HNCONTENTPROVIDER_H
#define HNCONTENTPROVIDER_H

#include "icontentprovider.h"
#include <QNetworkAccessManager>
#include <QSemaphore>
#include "../models/listmodel.h"

class HNContentProvider : public IContentProvider
{
    Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QObject* parent;

    ListModel* createListModel(QSharedPointer<QJsonObject> jsonObject);
    void parseSearchResults(QSharedPointer <QJsonObject> jsonObject, ListModel* listModel);
    void parseFrontPageResults(ListModel* listModel, QSharedPointer <QJsonObject> jsonObject);
public:
    HNContentProvider();
    HNContentProvider(QObject* parent);
    virtual void retrieveContent() override;
    Q_INVOKABLE virtual void retrieveSearchResults(QString query) override;

    QJsonValue parseFrontPageResults(QSharedPointer <QJsonObject> jsonObject);
public slots:
    void slotRequestFinished(QNetworkReply* reply);
    void update();
};

#endif // HNCONTENTPROVIDER_H
