#include "dbmanager.h"

QSqlDatabase DBManager::db =  QSqlDatabase::database();

MainWindow *DBManager::m_pOwner = nullptr;

DBManager::DBManager()
{

}

bool DBManager::connect_to_database()
{
    bool result = false;
    if(!QFile(DATABASE_NAME).exists())
    {
        qDebug() << "Database not exist! Restoring...";
        result = restore_database();
    }
    else
    {
        qDebug() << "Database found. Opening...";
        result = open_database();
    }
    return result;
}

bool DBManager::open_database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DATABASE_NAME);
    if(db.open())
    {
        qDebug() << "Database opened.";
        return true;
    }
    else
    {
        qDebug() << "Can't open database!";
        return false;
    }
}

bool DBManager::restore_database()
{
    if(open_database())
    {
        if(!create_user_table())
        {
            qDebug() << "Can't create user table!";
            return false;
        }
        if(!create_event_table())
        {
            qDebug() << "Can't create event table!";
            return false;
        }
        return true;
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

bool DBManager::create_event_table()
{
    QSqlQuery query;
    if(query.exec(
            "create table if not exists " EVENT_TABLE " ("
            EVENT_ID                    " INTEGER PRIMARY KEY,"
            EVENT_NAME                  " TEXT NOT NULL,"
            EVENT_PLACE                 " TEXT NOT NULL,"
            EVENT_START                 " TEXT UNIQUE NOT NULL,"
            EVENT_END                   " TEXT NOT NULL,"
            EVENT_MAX_PARTICIPANTS      " INTEGER DEFAULT 0,"
            EVENT_CURRENT_PARTICIPANTS  " INTEGER DEFAULT 0);"
            ))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int DBManager::add_user(QString name, QString birthDate, int balance, bool isActive, QString login, QString password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " USER_TABLE " (" USER_NAME ", " USER_BIRTHDATE ", " USER_LOGIN ", " USER_PASSWORD ", " USER_BALANCE ", " USER_ISACTIVE ") "
                  "VALUES (:Name, :BirthDate, :Login, :Password, :Balance, :IsActive)");

    query.bindValue(":Name", name);
    query.bindValue(":BirthDate", birthDate);
    query.bindValue(":Login", login);
    query.bindValue(":Password", password);
    query.bindValue(":Balance", balance);
    query.bindValue(":IsActive", isActive);

    if(query.exec())
    {
        m_pOwner->updateUsers();
        return query.lastError().nativeErrorCode().toInt();
    }
    else
    {
        return query.lastError().nativeErrorCode().toInt();
    }
}

bool DBManager::check_credentials(QString login, QString password, int& id)
{
    QSqlQuery query;
    query.prepare("SELECT " USER_PASSWORD " FROM " USER_TABLE " WHERE " USER_LOGIN " LIKE :Login");
    query.bindValue(":Login", login);

    query.exec();

    if (!query.next())
    {
        qDebug() << "Login not found!";
        return false;
    }
    qDebug() << "Login is found";
    QString dbPassword = query.value(0).toString();

    if (dbPassword == password)
    {
        qDebug() << "Password is right. Good boy!";
        QSqlQuery query;
        query.prepare("SELECT " USER_ID " FROM " USER_TABLE " WHERE " USER_LOGIN " LIKE :Login");
        query.bindValue(":Login", login);

        query.exec();

        id = query.value(0).toInt();

        return true;
    }

    else
    {
        qDebug() << "Wrong password!";
        return false;
    }
}

void DBManager::setOwner(MainWindow *owner)
{
    m_pOwner = owner;
}

void DBManager::updateTable()
{}
