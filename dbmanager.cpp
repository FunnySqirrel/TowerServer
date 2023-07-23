#include "dbmanager.h"

QSqlDatabase DBManager::db =  QSqlDatabase::database();

DBManager::DBManager()
{

}

bool DBManager::connect_to_database()
{
    bool result = false;
    if(!QFile(DATABASE_NAME).exists())
    {result = restore_database();}
    else
    {result = open_database();}
    return result;
}

bool DBManager::open_database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if(db.open())
    {return true;}
    else
    {return false;}
}

bool DBManager::restore_database()
{
    if(open_database())
    {
        if(!create_user_table())
        {return false;}
        else
        {return true;}
    }
    else
    {
        qDebug() << "Can't open database!";
        return false;
    }
    return false;
}

void DBManager::close_database()
{
    db.close();
}

bool DBManager::create_user_table()
{
    QSqlQuery query;
    if(query.exec(
                "create table if not exists " USER_TABLE " ("
                USER_ID         " INTEGER PRIMARY KEY,"
                USER_NAME       " TEXT NOT NULL,"
                USER_BIRTHDATE  " TEXT NOT NULL,"
                USER_EMAIL      " TEXT,"
                USER_PHONE      " TEXT,"
                USER_LOGIN      " TEXT UNIQUE NOT NULL,"
                USER_PASSWORD   " TEXT NOT NULL,"
                USER_BALANCE    " INTEGER DEFAULT 0,"
                USER_ISACTIVE   " BOOL NOT NULL);"
                ))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DBManager::add_user(QString name, QString birthDate, QString eMail, QString phone, int balance, bool isActive, QString login, QString password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " USER_TABLE " (" USER_NAME ", " USER_BIRTHDATE ", " USER_EMAIL ", " USER_PHONE ", " USER_LOGIN ", " USER_PASSWORD ", " USER_BALANCE ", " USER_ISACTIVE ") "
                  "VALUES (:Name, :BirthDate, :EMail, :Phone, :Login, :Password, :Balance, :IsActive)");

    query.bindValue(":Name", name);
    query.bindValue(":BirthDate", birthDate);
    query.bindValue(":EMail", eMail);
    query.bindValue(":Phone", phone);
    query.bindValue(":Login", login);
    query.bindValue(":Password", password);
    query.bindValue(":Balance", balance);
    query.bindValue(":IsActive", isActive);

    if(query.exec())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DBManager::edit_user(QString name, QString birthDate, QString eMail, QString phone, int balance, bool isActive, QString login, QString password, int id)
{
    QSqlQuery query;
    query.prepare("UPDATE " USER_TABLE " SET "
                  USER_NAME " = :Name, "
                  USER_BIRTHDATE " = :BirthDate, "
                  USER_EMAIL " = :EMail, "
                  USER_PHONE " = :Phone, "
                  USER_LOGIN " = :Login, "
                  USER_PASSWORD " = :Password, "
                  USER_BALANCE " = :Balance, "
                  USER_ISACTIVE " = :IsActive "
                  "WHERE " USER_ID " = :ID;"
                  );

    query.bindValue(":Name", name);
    query.bindValue(":BirthDate", birthDate);
    query.bindValue(":EMail", eMail);
    query.bindValue(":Phone", phone);
    query.bindValue(":Login", login);
    query.bindValue(":Password", password);
    query.bindValue(":Balance", balance);
    query.bindValue(":IsActive", isActive);
    query.bindValue(":ID", id);

    if(query.exec())
    {
        return true;
    }
    else
    {
        return false;
    }
}
