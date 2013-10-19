#include "server.h"
#include <QDebug>

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    qDebug() << "Constructor Begin: Server";

    thread = NULL;
    if (!listen(QHostAddress::Any, 5000)) {
        qDebug() << "Unable to start the server: " << errorString();
    }

    qDebug() << "Constructor End: Server";
}

Server::~Server()
{
    if (thread)
        delete thread;
}

void Server::start()
{
    if (thread) {
        createArray();
        thread->setData(&array);
        thread->start();
    }
}

void Server::wait()
{
    if (thread) {
        thread->wait();
    }
}

void Server::setAreas(uint n, Areas areas)
{
    if (areasArray.size() < n+1)
        areasArray.resize(n+1);

    areasArray[n] = areas;
}

void Server::incomingConnection(int socketDescriptor)
{
    qDebug() << "TCP: New connection";

    if (thread)
        thread->wait();

    if (thread)
        delete thread;

    thread = new Socket(socketDescriptor);

    qDebug() << "TCP: End new connection";
}

void Server::createArray()
{
    array.clear();
    QString string;
    QTextStream out(&string, QIODevice::ReadWrite);

    //createSeqAreas(out);
    createAreas(out);

    array = string.toUtf8();
}

void Server::createAreas(QTextStream &out)
{
    out << "{" << endl;

    out << jsonObject("data") << " [" << endl;
    //out << "  data: [" << endl;
    for (uint i=0; i<areasArray.size(); i++) {
        Areas &areas = areasArray[i];
        out << "    {" << endl;
        out << "    " << jsonObject("device", (int)i) << ", " << endl;

        out << "     " << jsonObject("areas") << " [" << endl;
        for (uint j=0; j<areas.size(); j++) {
            Area &area = areas.at(j);

            out << "       {" << endl;
            out << "        " << jsonObject("x", area.pt[0]) << ", " << endl;
            out << "        " << jsonObject("y", area.pt[1]) << ", " << endl;
            out << "        " << jsonObject("width", area.width) << ", " << endl;
            out << "        " << jsonObject("height", area.height) << endl;

            if ( j == areas.size() - 1  )
                out << "       } " << endl;
            else
                out << "       }, " << endl;
        }
        out << "      ]" << endl;

        if ( i == areasArray.size() - 1  )
            out << "    }" << endl;
        else
            out << "    }," << endl;
    }
    out << "  ]" << endl;

    out << "}" << endl;
}

void Server::createSeqAreas(QTextStream &out)
{
    out << "{" << endl;
    out << jsonObject("device", 0) << ", " << endl;
    out << jsonObject("seqAreas") << endl;

    out << " [" << endl;
    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        out << "  {" << endl;
        out << "   " << jsonObject("number", (int)seqArea.number) << ", " << endl;
        out << "   " << jsonObject("x", seqArea.pt[0]) << ", " << endl;
        out << "   " << jsonObject("y", seqArea.pt[1]) << ", " << endl;
        out << "   " << jsonObject("xPrev", seqArea.ptPrev[0]) << ", " << endl;
        out << "   " << jsonObject("yPrev", seqArea.ptPrev[1]) << ", " << endl;
        out << "   " << jsonObject("angle", seqArea.angle) << ", " << endl;
        out << "   " << jsonObject("lenght", seqArea.length) << " " << endl;

        if (i == seqAreas.size()-1 )
            out << "  }" << endl;
        else
            out << "  }, " << endl;
    }
    out << " ]" << endl;

    out << "}" << endl;
}

QString Server::jsonObject(QString name)
{
    return "\"" + name + "\": ";
}

QString Server::jsonObject(QString name, int value)
{
    return "\"" + name + "\": \"" + QString::number(value) + "\"";
}

QString Server::jsonObject(QString name, double value)
{
    return "\"" + name + "\": \"" + QString::number(value) + "\"";
}

/*
void ServerThread::setSeqAreas(SeqAreas &seqAreas)
{
    array.clear();
    QDataStream out(&array, QIODevice::WriteOnly);
    out << (quint32)0; // Размер блока

    out << (quint8)10; // Номер устройства
    out << (quint8)0; // Номер обработчика
    out << (quint8)3; // Тип передаваемых данных

    int size = seqAreas.size();
    if ( size > 255 )
        size = 255;

    out << (quint8)size;

    for (unsigned int i=0; i<seqAreas.size(); i++) {
        SeqArea &seqArea = seqAreas.at(i);
        out << (quint32)seqArea.number;
        out << (qint16)seqArea.pt[0];
        out << (qint16)seqArea.pt[1];
        out << (qint16)seqArea.ptReal[0];
        out << (qint16)seqArea.ptReal[1];
        out << (qint16)seqArea.ptPrev[0];
        out << (qint16)seqArea.ptPrev[1];
        out << (qint16)seqArea.ptPrevReal[0];
        out << (qint16)seqArea.ptPrevReal[1];
        out << (quint16)seqArea.width;
        out << (quint16)seqArea.height;
        out << (quint16)seqArea.widthReal;
        out << (quint16)seqArea.heightReal;
        out << (qreal)seqArea.angle;
        out << (qreal)seqArea.length;
    }

    out.device()->seek(0);
    out << (quint32)(array.size() - sizeof(quint32));
    //qDebug() << array.size() - sizeof(quint32);

    if (thread)
        thread->setData(&array);
}
*/
