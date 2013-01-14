#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include "icontentprovider.h"
#include "../storage/storage.h"
#include <QMap>


class Aggregator : public IContentProvider
{    
    Q_OBJECT

public:
    Aggregator();
    Aggregator(QObject* parent);

    virtual void retrieveContent() override;
    Q_INVOKABLE virtual void retrieveSearchResults(QString query) override;

    Q_INVOKABLE void addToFavorites(int articlePosition);
    Q_INVOKABLE void removeFromFavorites(int articlePosition);
    Q_INVOKABLE void loadFavorites();


    virtual ~Aggregator();

private:
    QObject* parent;
    QMap<QString,IContentProvider*> contentProviders;
    ListModel* model;
    Storage* storage;
    static int dataCounter;

    bool modelAdded;
    void initContentProviders();
    void refreshList();
    void clearList();
private slots:
    void mergeModel(ListModel* model);

public slots:
    virtual void update() override;

};

#endif // AGGREGATOR_H
