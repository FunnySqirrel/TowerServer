#include "server.h"

Server::Server()
{
    if (!this->listen(QHostAddress::Any, 2323))
    {
        qDebug()<<"Error! Server not started!";
        return;
    }
    qDebug()<<"server started.";
}

void Server::SendToClient()
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
    m_pSocket = new QTcpSocket;
    m_pSocket->setSocketDescriptor(socketDescriptor);
    connect (m_pSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect (m_pSocket, &QTcpSocket::disconnected, m_pSocket, &QTcpSocket::deleteLater);
    m_pSocketVector.push_back(m_pSocket);
    qDebug()<<""<<socketDescriptor;
}

void Server::slotReadyRead()
{
    m_pSocket = (QTcpSocket*)sender();
    qint16 blocksize=0;
    QDataStream in(m_pSocket);
    e_MsgType msgType;
    in.setVersion(QDataStream::Qt_6_6);
    if(in.status() == QDataStream::Ok)
    {
        while(true)
        {
            if(blocksize == 0)
            {
                if(m_pSocket->bytesAvailable()<2)
                {
                    break;
                }
                in>>blocksize;
            }
            if(m_pSocket->bytesAvailable()<blocksize)
            {
                break;
            }
            in>>msgType;
            switch(msgType)
            {
            case e_MsgType::text:
                break;
            case e_MsgType::loginRequest:
                break;
            case e_MsgType::logoutRequest:
                break;
            default:
                break;
            }
        }
    }
    else
    {
        qDebug()<<"Datastream Error!";
    }
}
