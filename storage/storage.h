#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QList>
#include "articleitemmodel.h"
#include "../models/articleitem.h"

class Storage : public QObject
{
    Q_OBJECT
public:
    virtual void saveArticle(const ArticleItem& articleItem) = 0;
    virtual QList<ArticleItem*> getArticles() = 0;
    virtual void removeArticle(const ArticleItem& articleItem) = 0;

};


#endif // STORAGE_H
