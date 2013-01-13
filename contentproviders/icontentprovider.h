#ifndef ICONTENTPROVIDER_H
#define ICONTENTPROVIDER_H

#include <QObject>
#include <QJsonObject>
#include "../models/listmodel.h"


class IContentProvider : public QObject {
    Q_OBJECT
public :

    virtual void retrieveContent() = 0;
    virtual void retrieveSearchResults(QString query) = 0;

signals:
    void modelReady(ListModel*);

public slots:
    virtual void update() = 0;
};


#endif // ICONTENTPROVIDER_H
