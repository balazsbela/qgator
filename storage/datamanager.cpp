#include "datamanager.h"
#include <QSqlQuery>
#include <QSqlError>


DataManager::DataManager(QObject* parent)
{
    // Open database using Qt library
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("articles.db" );
    if(!db.open()) {
        qDebug() << "Could not open database";
    }
}

void DataManager :: saveArticle(const ArticleItem& articleItem) {
    qDebug() << "Saving article with title" << articleItem.title();
    QSqlQuery selectQuery(db);
    selectQuery.prepare("SELECT * FROM Articles WHERE url = :url");
    selectQuery.bindValue(":url",articleItem.url());
    if(!selectQuery.exec()) {
        qWarning() << "Query failed" << selectQuery.lastError();
    }

    int recCount = 0;
    while( selectQuery.next() ) {
       recCount++;
    }

    if(recCount > 0 ) {
        qDebug() << "Already existed, not saving";
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Articles(title,url,points,commentCount,postedAgo,commentsUrl) VALUES(:title,:url,:points,:commentCount,:postedAgo,:commentsUrl)");
    query.bindValue(":title",articleItem.title());
    query.bindValue(":url",articleItem.url().toString());
    query.bindValue(":points",articleItem.points());
    query.bindValue(":commentCount",articleItem.commentCount());
    query.bindValue(":postedAgo",articleItem.postedAgo());
    query.bindValue(":commentsUrl",articleItem.commentsUrl().toString());
    if(!query.exec()) {
        qWarning() << "QUERY FAILED " << query.lastError();
    }
}

QList<ArticleItem*> DataManager :: getArticles() {
    QSqlQuery query(db);
    query.exec("SELECT * FROM Articles");
    QList<ArticleItem*> articleList;
    int recCount = 0;
    while(query.next()) {
       ArticleItem* article = new ArticleItem(query.value(0).toString(),QUrl(query.value(1).toString()),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toString(),QUrl(query.value(5).toString()));
       articleList.append(article);
    }
    qDebug() << "Found " << recCount << " favorite articles";
    return articleList;
}

void DataManager :: removeArticle(const ArticleItem& articleItem) {    

    qDebug() << "DELETING article " << articleItem.title();
    QSqlQuery query(db);

    query.prepare("DELETE FROM Articles WHERE title=:title AND url=:url");
    query.bindValue(":title",articleItem.title());
    query.bindValue(":url",articleItem.url().toString());
    if(!query.exec()) {
        qWarning() << "DELETE QUERY FAILED " << query.lastError();
    }
}

DataManager :: ~DataManager() {
    db.close();
}
