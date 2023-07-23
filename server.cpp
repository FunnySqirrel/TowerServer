#include "server.h"
#include <QMessageBox>
#include <QTimeEdit>

void Server::sendToClient(QTcpSocket *pSocket, const QString &str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out<<quint16(0)<<QTime::currentTime()<<str;
    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));
    pSocket->write(arrBlock);
}

Server::Server(int nPort)
{
    m_pTcpServer = new QTcpServer(this);
    if (!m_pTcpServer->listen(QHostAddress::Any, nPort))
    {
        QMessageBox::critical(0,
                              "ServerError",
                              "Unable to start the server:"
                              +m_pTcpServer->errorString());
        m_pTcpServer->close();
        return;
    }
    connect (m_pTcpServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);
}

void Server::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_pTcpServer->nextPendingConnection();
    connect(pClientSocket, &QTcpSocket::disconnected, pClientSocket, &QTcpSocket::deleteLater);
    connect(pClientSocket, &QTcpSocket::readyRead, this, &Server::slotReadClient);
    sendToClient(pClientSocket,"Server response: Connected");
}

void Server::slotReadClient()
{
    QTcpSocket *pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_12);
    for(;;)
    {
        if(!m_nNextBlockSize)
        {
            if(pClientSocket->bytesAvailable()<sizeof(quint16))
            {
                break;
            }
            in>>m_nNextBlockSize;
        }
        if(pClientSocket->bytesAvailable()<sizeof(m_nNextBlockSize))
        {
            break;
        }
        QTime time;
        QString str;
        in>>time>>str;
        QString strMessage = time.toString()+" "+"Client has sent - "+str;
        m_nNextBlockSize = 0;
        sendToClient(pClientSocket, "Server Response: Received \"" +str+"\"");
    }
}
