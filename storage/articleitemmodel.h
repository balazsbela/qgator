#ifndef ARTICLEITEMMODEL_H
#define ARTICLEITEMMODEL_H

#include <QString>
#include <QUrl>

class ArticleItemModel
{
public:
    explicit ArticleItemModel(QString title,QUrl url,int points,int commentCount,QString postedAgo,QUrl commentsUrl);
public :
    int id;
    QString title;
    QUrl url;
    int points;
    int commentCount;
    QString postedAgo;
    QUrl commentsUrl;
};

#endif // ARTICLEITEMMODEL_H
