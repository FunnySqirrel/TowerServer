#ifndef SERVER_H
#define SERVER_H

#pragma once
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

class Server: public QWidget
{
    Q_OBJECT
private:
    QTcpServer* m_pTcpServer;
    quint16 m_nNextBlockSize;
private:
    void sendToClient(QTcpSocket *pSocket, const QString &str);
public:
    Server(int nPort);
public slots:
    virtual void slotNewConnection();
    void slotReadClient();
};

#endif // SERVER_H
