#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    void serverInit();

    QTcpSocket* m_pSocket;
    struct SocketName
    {
        QTcpSocket* pSocket;
        QString name = "guest";
    };

private:

    QVector<SocketName> m_pSocketVector;       //текущий сокет
    enum class e_ClientMsgType                        //тип сообщения и команды
    {
        text =0,
        loginRequest=1,
        logoutRequest=2,
        registrationRequest=3
    };

    enum class e_ServerMsgType                        //тип сообщения и команды
    {
        text =0,
        loginSucsessful=1,
        loginDenied=2,
        looutSucsessful=3,
        logoutDenied=4,
        registrationSucsessful=5,
        registrationDenied=6
    };

    void SendToClient();                        //функция отправки данных клиенту

public slots:

    void incomingConnection(qintptr socketDescriptor);      //слот на установку соединения
    void slotReadyRead();                                   //слот на прочтение данных
};

#endif // SERVER_H
