#include "socket.h"
#include <QDebug>

Socket::Socket(int socketDescriptor)
{
    qDebug() << "Constructor Begin: ServerThread";

    this->socketDescriptor = socketDescriptor;
    tcpSocket = 0;

    qDebug() << "Constructor End: ServerThread";
}

Socket::~Socket()
{
    qDebug() << "Destructor Begin: ServerThread";

    tcpSocket->disconnectFromHost();
    //tcpSocket->waitForDisconnected();

    delete tcpSocket;

    qDebug() << "Destructor End: ServerThread";
}

void Socket::run()
{
    if (!tcpSocket) {
        tcpSocket = new QTcpSocket();
        if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
            qDebug() << tcpSocket->error();
            return;
        }
    }

    //qDebug() << "TCP data size:" << data->size();

    tcpSocket->write(*data);
    tcpSocket->flush();
}
