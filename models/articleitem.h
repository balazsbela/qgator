#ifndef ARTICLEITEM_H
#define ARTICLEITEM_H

#include "listmodel.h"
#include <QString>
#include <QUrl>
#include <QVariant>
#include <QHash>

class ArticleItem : public ListItem
{
    Q_OBJECT
public:
    ArticleItem(QObject *parent = 0) : ListItem(parent) {}
    explicit ArticleItem(QString title,QUrl url,int points,int commentCount,QString postedAgo);
    public:
      enum Roles {
        titleRole = Qt::UserRole+1,
        urlRole,
        pointsRole,
        commentCountRole,
        postedAgoRole
      };

    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    inline QString id() const { return m_title; }
    inline QString title() const { return m_title; }
    inline QUrl url() const { return m_url; }
    inline int points() const { return m_points; }
    inline int commentCount() const { return m_commentCount; }
    inline QString postedAgo() const { return m_postedAgo; }

private:
    QString m_title;
    QUrl m_url;
    int m_points;
    int m_commentCount;
    QString m_postedAgo;
};

#endif // ARTICLEITEM_H
