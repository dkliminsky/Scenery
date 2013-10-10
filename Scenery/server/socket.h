#ifndef SOCKET_H
#define SOCKET_H

#include <QThread>
#include <QTcpSocket>

class Socket : public QThread {
    Q_OBJECT
public:
    Socket(int socketDescriptor);
    ~Socket();

    void setData(QByteArray *data) { this->data = data; }

protected:
    void run();

private:
    int socketDescriptor;
    QTcpSocket *tcpSocket;
    QByteArray *data;

public slots:
   // void slotNewConnection();
   // void slotReadClient   ();

};

#endif // SOCKETTHREAD_H
