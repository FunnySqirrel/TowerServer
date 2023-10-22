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
    QTcpSocket *m_pSocket;

private:
    struct SocketName
    {
        QTcpSocket socket;
        QString name;
    };
    QVector<QTcpSocket*> m_pSocketVector;       //текущий сокет
    QByteArray m_Data;                          //данные
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
