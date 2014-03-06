#ifndef REMOTE_H
#define REMOTE_H

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <fb.h>
#include <QFile>
#include <QThread>


//class QTcpSocket;

class Remote : public QObject
{
    Q_OBJECT
public:
    typedef short int CustomInt;
    explicit Remote(QObject *parent, struct fb *fbuff);
    bool status;
    bool statusR;
    bool statusI;
    CustomInt statusMode;
    QFile file;
    int countbuffer;
    struct fb *fbuffer;
    const struct fbinfo* info;
    QByteArray Data;
    void *buffer;
    void write();
signals:
    void finishedFB();
public slots:
    void connectToServer(CustomInt modeN);
    void on_connected();
    void bytesWritten(qint64 bytes);
    void on_readyRead();
    void on_error(QAbstractSocket::SocketError error);
private:
    QTcpSocket *socket;
};

#endif // REMOTE_H
