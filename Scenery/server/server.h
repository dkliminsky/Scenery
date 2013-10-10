#ifndef SERVER_H
#define SERVER_H

#include "process/processdata.h"
#include "socket.h"
#include <QTcpServer>
#include <QThread>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    ~Server();

    void start();
    void wait();

    void setSeqAreas(SeqAreas seqAreas) { this->seqAreas = seqAreas; }

protected:
    void incomingConnection(int socketDescriptor);

private:
    Socket *thread;
    QByteArray array;

    SeqAreas seqAreas;

    void createArray();

    QString jsonObject(QString name);
    QString jsonObject(QString name, int value);
    QString jsonObject(QString name, double value);
    QString jsonObject(QString name, QString value);
};

#endif // SERVER_H
