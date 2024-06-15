#include "server.h"
#include "dbmanager.h"

Server::Server()
{
}

void Server::serverInit()
{
    if (!this->listen(QHostAddress::LocalHost, 2323))
    {
        qDebug()<<"Error! Server not started!";
        return;
    }
    qDebug()<<"server started.";
}

void Server::SendToClient(e_ServerMsgType msgType, QVariantList input)
{
    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out<<qint16(0);
    out<<msgType;
    out<<input;
    out.device()->seek(0);
    out<<qint16(data.size()-sizeof(qint16));
    qDebug()<<m_pSocket->write(data);
}

void Server::SendToClient(e_ServerMsgType msgType)
{
    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out<<qint16(0);
    out<<msgType;
    out.device()->seek(0);
    out<<qint16(data.size()-sizeof(qint16));
    qDebug()<<m_pSocket->write(data);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    m_pSocket = new QTcpSocket;
    m_pSocket->setSocketDescriptor(socketDescriptor);
    connect (m_pSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect (m_pSocket, &QTcpSocket::disconnected, m_pSocket, &QTcpSocket::deleteLater);
    SocketID socketID;
    socketID.pSocket = m_pSocket;
    m_pSocketVector.push_back(socketID);
    qDebug()<<""<<socketDescriptor;
}

void Server::slotReadyRead()
{
    m_pSocket = (QTcpSocket*)sender();
    qint16 blocksize=0;
    QDataStream in(m_pSocket);
    e_ClientMsgType msgType;
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
            QVariantList data;
            in>>data;
            switch(msgType)
            {
            case e_ClientMsgType::text:
                break;
            case e_ClientMsgType::loginRequest:
            {
                QString login = data[0].toString();
                QString password = data[1].toString();
                qDebug()<<""<<login<<" "<<password;
                int id=-1;
                if (DBManager::check_credentials(login, password,id))
                {
                    qDebug()<<"Login Succsessful";
                    for(auto i:m_pSocketVector)
                    {
                        if (i.pSocket == m_pSocket)
                        {
                            i.id = id;
                        }
                    }
                    SendToClient(e_ServerMsgType::loginSucsessful);
                }
            }
                break;
            case e_ClientMsgType::logoutRequest:
            {
                for(auto i:m_pSocketVector)
                {
                    if (i.pSocket == m_pSocket)
                    {
                        qDebug()<<"Logout Succsessful";
                        i.id = -1;
                    }
                }
            }
                break;
            case e_ClientMsgType::registrationRequest:
            {
                QString name = data[0].toString();
                QString birthDate = data[1].toString();
                QString login = data[2].toString();
                QString password = data[3].toString();
                qDebug()<<name<<" "<<birthDate<<" "<<login<<" "<<password;
                if(DBManager::add_user(name, birthDate, 0,true, login, password) == 0)
                {
                    SendToClient(e_ServerMsgType::registrationSucsessful);
                }
                else
                {
                    qDebug() << "Can't add user!";
                    SendToClient(e_ServerMsgType::registrationDenied);
                }

            }
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



