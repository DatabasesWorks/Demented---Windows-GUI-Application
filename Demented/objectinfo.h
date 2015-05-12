#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include <QString>
#include <QStandardItemModel>
#include <QMainWindow>


class objectInfo
{
public:
    objectInfo(QString type, QString band, QString album,
               double price, QString location, qint32 XS,
               qint32 S, qint32 M, qint32 L, qint32 XL, qint32 XXL, QString catNum, qint32 TQ);

    QString type;
    QString band;
    QString album;
    double price;
    QString location;
    qint32 XS;
    qint32 S;
    qint32 M;
    qint32 L;
    qint32 XL;
    qint32 XXL;
    QString catNum;
    qint32 TQ;
};

#endif // OBJECTINFO_H
