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

    static QTcpSocket* m_pSocket;

    struct SocketName
    {
        QTcpSocket* pSocket;
        QString name = "guest";
    };

private:

    QVector<SocketName> m_pSocketVector;       //текущий сокет
    enum class e_MsgType                        //тип сообщения и команды
    {
        text =0,
        loginRequest=1,
        logoutRequest=2,
        registrationRequest=3
    };

    void SendToClient();                        //функция отправки данных клиенту

public slots:

    void incomingConnection(qintptr socketDescriptor);      //слот на установку соединения
    void slotReadyRead();                                   //слот на прочтение данных
};

#endif // SERVER_H
