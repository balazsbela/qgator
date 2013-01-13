#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include "icontentprovider.h"
#include <QMap>


class Aggregator : public IContentProvider
{    
    Q_OBJECT

public:
    Aggregator();
    Aggregator(QObject* parent);

    virtual void retrieveContent() override;
    Q_INVOKABLE virtual void retrieveSearchResults(QString query) override;

    virtual ~Aggregator();

private:
    QObject* parent;
    QMap<QString,IContentProvider*> contentProviders;
    ListModel* model;

    static int dataCounter;

    void initContentProviders();
    void refreshList();

private slots:
    void mergeModel(ListModel* model);

public slots:
    virtual void update() override;
};

#endif // AGGREGATOR_H
