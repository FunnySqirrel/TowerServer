#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>

#define DATABASE_NAME           "TowerOfMage.db"

#define USER_TABLE              "User_table"
#define USER_ID                 "ID"
#define USER_NAME               "Name"
#define USER_BIRTHDATE          "Birth_date"
#define USER_EMAIL              "Email"
#define USER_PHONE              "Phone"
#define USER_LOGIN              "Login"
#define USER_PASSWORD           "Password"
#define USER_BALANCE            "Balance"
#define USER_ISACTIVE           "Is_active"

#define EVENT_TABLE                 "Event_table"
#define EVENT_ID                    "ID"
#define EVENT_NAME                  "Name"
#define EVENT_PLACE                 "Place"
#define EVENT_START                 "Start_time"
#define EVENT_END                   "End_time"
#define EVENT_MAX_PARTICIPANTS      "Max_participants"
#define EVENT_CURRENT_PARTICIPANTS  "Current_participants"
#define EVENT_PARTICIPANTS_LIST     "Participants_list"

#define TICKET_TABLE                "Ticket_table"
#define TICKET_ID                   "ID"
#define TICKET_EVENT                "Event"
#define TICKET_USER                 "User"

class DBManager
{
private:
    static QSqlDatabase db;
public:
    DBManager();

    static QSqlDatabase get_db() {return db;}

    static bool connect_to_database();

    static bool open_database();
    static bool restore_database();
    static void close_database();

    static bool create_user_table();
    static bool create_event_table();
    static bool create_ticket_table();

    static bool add_user(QString name, QString birthDate, int balance, bool isActive, QString login, QString password);
    static bool edit_user(QString name, QString birthDate, int balance, bool isActive, QString login, QString password, int id);
    static void delete_user();

    static void get_user();
    static void gelt_user_list();
    static QStringList get_user_field(QStringList fields);
};

#endif // DBMANAGER_H
