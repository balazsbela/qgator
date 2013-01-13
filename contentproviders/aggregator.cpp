#include "aggregator.h"
#include "hncontentprovider.h"
#include "redditcontentprovider.h"
#include "qtquick2applicationviewer.h"
#include "../models/articleitem.h"
#include <QQmlContext>
#include <QDebug>

int Aggregator::dataCounter = 0;

Aggregator :: Aggregator() {
    model = new ListModel(new ArticleItem,this);
}

Aggregator :: Aggregator(QObject* parent) {
    this->parent = parent;
    model = new ListModel(new ArticleItem,this);
    dataCounter=0;
    initContentProviders();
}

void Aggregator :: initContentProviders() {
    IContentProvider* hnProvider = new HNContentProvider(parent);
    IContentProvider* redditProvider = new RedditContentProvider(parent);
    contentProviders.insert("hn",hnProvider);
    contentProviders.insert("reddit",redditProvider);
}


void Aggregator :: retrieveContent() {

    foreach(IContentProvider* provider,contentProviders) {
        QObject::connect(provider, SIGNAL(modelReady(ListModel *)),SLOT(mergeModel(ListModel*)));
        provider->retrieveContent();
    }
}

void Aggregator :: refreshList() {
    model->sort(0);
    QtQuick2ApplicationViewer* viewer = dynamic_cast<QtQuick2ApplicationViewer*>(this->parent);
    if(viewer!=nullptr) {
        qDebug() << "Added feedModel";
        viewer->rootContext()->setContextProperty("feedModel",this->model);
        viewer->showMaximized();
    }
}


void Aggregator :: mergeModel(ListModel* model) {
    qDebug() << QObject::sender();
    if(dataCounter<contentProviders.size()-1) {
        delete this->model;
        this->model = model;
        dataCounter++;
    } else {
        foreach(ListItem* item,*model->list()) {
            this->model->appendRow(item);
        }
        dataCounter = 0;
        refreshList();
    }
}


void Aggregator :: update() {
    foreach(IContentProvider* provider,contentProviders) {
        provider->update();
    }
}

void Aggregator :: retrieveSearchResults(QString query) {
    foreach(IContentProvider* provider,contentProviders) {
        provider->retrieveSearchResults(query);
    }
}


Aggregator :: ~Aggregator() {
    foreach(IContentProvider* provider,contentProviders) {
        delete provider;
    }
}

