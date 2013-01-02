#include "articleitem.h"

ArticleItem::ArticleItem(QString title,QUrl url,int points,int commentCount,QString postedAgo):m_title(title),m_url(url),m_points(points),m_commentCount(commentCount),m_postedAgo(postedAgo)
{
}

QHash<int, QByteArray> ArticleItem::roleNames() const
{
  QHash<int, QByteArray> names;
  names[titleRole] = "title";
  names[urlRole] = "url";
  names[pointsRole] = "points";
  names[commentCountRole] = "commentCount";
  names[postedAgoRole] = "postedAgo";
  return names;
}

QVariant ArticleItem::data(int role) const
{
  switch(role) {
  case titleRole:
    return title();
  case urlRole:
    return url();
  case pointsRole:
    return points();
  case commentCountRole:
    return commentCount();
  case postedAgoRole:
    return postedAgo();
  default:
    return QVariant();
  }
}
