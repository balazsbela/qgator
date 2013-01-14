#include "aggregator.h"
#include "hncontentprovider.h"
#include "redditcontentprovider.h"
#include "qtquick2applicationviewer.h"
#include "../models/articleitem.h"
#include "../storage/datamanager.h"
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
    modelAdded = false;
    initContentProviders();
}

void Aggregator :: initContentProviders() {
    IContentProvider* hnProvider = new HNContentProvider(parent);
    IContentProvider* redditProvider = new RedditContentProvider(parent);
    contentProviders.insert("hn",hnProvider);
    contentProviders.insert("reddit",redditProvider);

    storage = new DataManager(parent);
}


void Aggregator :: retrieveContent() {

    foreach(IContentProvider* provider,contentProviders) {
        QObject::connect(provider, SIGNAL(modelReady(ListModel *)),SLOT(mergeModel(ListModel*)));
        provider->retrieveContent();
    }
}

void Aggregator :: refreshList() {
    model->sort(0);

    if(!modelAdded) {
        QtQuick2ApplicationViewer* viewer = dynamic_cast<QtQuick2ApplicationViewer*>(this->parent);
        if(viewer!=nullptr) {
            qDebug() << "Added feedModel";
            viewer->rootContext()->setContextProperty("feedModel",this->model);
            viewer->showMaximized();
        }
        modelAdded = true;
    }
}

void Aggregator :: mergeModel(ListModel* model) {
    //qDebug() << QObject::sender();
    if(dataCounter<contentProviders.size()-1) {
        clearList();
        foreach(ListItem* item,*model->list()) {
            this->model->appendRow(item);
        }
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

void Aggregator :: addToFavorites(int articlePosition) {
    storage->saveArticle(*(dynamic_cast<ArticleItem*>(model->getIndex(articlePosition))));
}


void Aggregator :: removeFromFavorites(int articlePosition) {
    storage->removeArticle(*(dynamic_cast<ArticleItem*>(model->getIndex(articlePosition))));
    loadFavorites();
}

void Aggregator :: clearList() {
    int i=0;
    while(this->model->rowCount()>0) {
        this->model->removeRow(i);
    }
}

void Aggregator :: loadFavorites() {
    clearList();
    qDebug() << "Displaying favorites";
    QList<ArticleItem*> items = storage -> getArticles();
    foreach(ArticleItem* item,items) {
        ListItem* listItem = dynamic_cast<ListItem*>(item);
        if(listItem!=nullptr) {
            qDebug() << "Adding " << item->title();
            this->model->appendRow(item);
        }
    }
    refreshList();
}


Aggregator :: ~Aggregator() {
    foreach(IContentProvider* provider,contentProviders) {
        delete provider;
    }
}
