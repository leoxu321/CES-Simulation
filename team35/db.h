#ifndef DB_H
#define DB_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QList>


class db
{
public:
    db();
    void addSession(QString, QString, int);
    void removeSession(QString, QString, int);
    QStringList getLastSession();


private:
//    QString time;
//    QString session;
//    int intensity;

    QVector<QStringList> database;
};

#endif // DB_H
