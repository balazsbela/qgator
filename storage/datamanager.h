#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QtSql/QSqlDatabase>
#include "storage.h"

class DataManager : public Storage
{
    Q_OBJECT
public:
    DataManager(QObject* parent);
    void saveArticle(const ArticleItem& articleItem) override;
    QList<ArticleItem*> getArticles() override;
    void removeArticle(const ArticleItem& articleItem) override;

    virtual ~DataManager();
private:
    QSqlDatabase db;
};

#endif // DATAMANAGER_H
