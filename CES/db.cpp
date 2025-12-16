#include "db.h"


db::db()
{
}



void db::addSession(QString time, QString session, int intensity)
{
    QList<QString> ls;

    ls = {time, session, QString::number(intensity)};

    if (database.isEmpty() != true)
    {


        if (database.last().at(0) != time || database.last().at(1) != session || database.last().at(2) != intensity)
        {
            qInfo("hello");
            database.push_back(ls);

        }
    }
    else
    {
        database.push_back(ls);
    }
}

void db::removeSession(QString time, QString session, int intensity)
{
    if (database.last().at(0) == time && database.last().at(1) == session)
    {
        database.pop_back();
    }
}

QStringList db::getLastSession()
{
    if (database.isEmpty() == false )
    {
        QStringList str = {database.last().at(0),database.last().at(1), database.last().at(2)};

        return str;
    }
}
