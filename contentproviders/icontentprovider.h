#ifndef ICONTENTPROVIDER_H
#define ICONTENTPROVIDER_H

#include <QObject>
#include <QJsonObject>

class IContentProvider : public QObject {
    Q_OBJECT
    public :

    virtual void retrieveContent() = 0;
    virtual void retrieveSearchResults(QString query) = 0;
};


#endif // ICONTENTPROVIDER_H
