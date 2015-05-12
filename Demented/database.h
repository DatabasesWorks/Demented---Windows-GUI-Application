#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>

class Database
{
public:
    Database();

    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(QString select)
    {
        if(select == "Inventory")
        {
            mydb=QSqlDatabase::addDatabase("QSQLITE");

            mydb.setDatabaseName(QDir::currentPath() + "/data/Inventory.db");

            if(!mydb.open())
            {
                qDebug()<<("Database Failed to connect");
                return false;
            }
            else
            {
                qDebug()<<("Connected to Database..");
                return true;
            }
       }
       else if(select == "Log")
       {
           mydb=QSqlDatabase::addDatabase("QSQLITE");

           mydb.setDatabaseName(QDir::currentPath() + "/data/Log.db");

           if(!mydb.open())
           {
               qDebug()<<("Database Failed to connect");
               return false;
           }
           else
           {
               qDebug()<<("Connected to Database..");
               return true;
           }
       }
        else if(select == "Employee")
        {
            mydb=QSqlDatabase::addDatabase("QSQLITE");

            mydb.setDatabaseName(QDir::currentPath() + "/data/Employees.db");

            if(!mydb.open())
            {
                qDebug()<<("Database Failed to connect");
                return false;
            }
            else
            {
                qDebug()<<("Connected to Database..");
                return true;
            }
        }
       else
            return false;
    }
};

#endif // DATABASE_H
