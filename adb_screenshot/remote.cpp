#include <QTcpSocket>
#include <QHostAddress>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <QString>
#include <remote.h>
#include <QDebug>

#define DDMS_RAWIMAGE_VERSION 1
#define FB 1

Remote::Remote(QObject *parent = 0, struct fb *fbuff = 0) :
    fbuffer(fbuff)
{
    status = false;
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),
            this, SLOT(on_connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(on_error(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(on_readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)),
            this, SLOT(bytesWritten(qint64)));
    connect(this, SIGNAL(finishedFB()),
            parent, SLOT(on_finishedFB()));
}

void Remote::write() {
    char buf[1024];

    printf("trying to write 1\n");
    sprintf(buf, "%04x%s", strlen("host:transport-"), "host:transport-");
    printf("tentando: %s\n", buf);
    socket->write(buf);
    socket->flush();
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(4000);

    memset(buf, 0, 1024);

    printf("trying to write 2\n");
    sprintf(buf, "%04x%s", strlen("framebuffer:"), "framebuffer:");
    printf("tentando: %s\n", buf);
    socket->write(buf);
    socket->flush();
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(4000);
}

void Remote::on_readyRead() {

    countbuffer = socket->bytesAvailable();

    if (countbuffer == 4) {
        Data.append(socket->read(4));
    }
    if ((strcmp(Data.constData(), "OKAY")) == 0) {
        qDebug() << Data;
        qDebug() << countbuffer;
        Data.clear();
        statusI = false;
        return;
    }
    qDebug() << socket->bytesAvailable();
    if ((countbuffer > sizeof(struct fbinfo)) && (statusI == false)) {
        qDebug() << "Tamanho esperado";
        qDebug() << sizeof(struct fbinfo);
        qDebug() << "Capturou!";
        Data.append(socket->read(sizeof(struct fbinfo)));
        statusI = true;
    }

    return;
}

void Remote::on_connected()
{
    printf("Connection established.\n");
    status = true;
    printf("STATUS MODE1: %d\n", statusMode);
    switch (statusMode) {
    case FB:
        printf("STATUS MODE2: %d\n", statusMode);
        write();
        printf("STATUS MODE3: %d\n", statusMode);
        break;
    }
}

void Remote::bytesWritten(qint64 bytes)
{
    // printf("bytes escritos: %I64d\n", bytes);
    printf("bytes escritos: %d\n", (int)bytes);
}


void Remote::on_error(QAbstractSocket::SocketError error)
{
    switch (error)
    {
    case QAbstractSocket::AddressInUseError:
        printf("SOCKET ERROR: Address is already in use\n");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        printf("SOCKET ERROR: Connection refused\n");
        break;
    case QAbstractSocket::HostNotFoundError:
        printf("SOCKET ERROR: Host not found\n");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        printf("SOCKET ERROR: Remote host closed\n");
        statusR = true;
        if (statusI = true) {
            info = (fbinfo*)Data.constData();
            if (info->version == DDMS_RAWIMAGE_VERSION) {
                printf("version: %u\n", info->version);
                printf("bpp: %u\n", info->bpp);
                printf("size: %u\n", info->size);
                printf("width: %u\n", info->width);
                printf("height: %u\n", info->height);
                printf("red offset: %u\n", info->red_offset);
                printf("red length: %u\n", info->red_length);
                printf("blue offset: %u\n", info->blue_offset);
                printf("blue length: %u\n", info->blue_length);
                printf("green offset: %u\n", info->green_offset);
                printf("green length: %u\n", info->green_length);
                printf("alpha offset: %u\n", info->alpha_offset);
                printf("alpha length: %u\n", info->alpha_length);

                // memcpy(fbuffer, &info->bpp, sizeof(fbinfo*));
                memcpy(fbuffer, &info->bpp, sizeof(fb));
                //       printf("tamanho antes malloc: %u\n", info->size);
                //    fbuffer->data = malloc(info->size);

                qDebug() << "Bytes available";
                qDebug() << socket->bytesAvailable();
                qDebug() << countbuffer;
                //  buffer = (unsigned char *)malloc(info->size);
                Data.clear();
                //  socket->read((char *)buffer, (quint64) info->size);

                //    QFile file("arquivo2.txt");
                //    file.open(QIODevice::WriteOnly);
                //    file.write(socket->readAll());
                //  file.write("asdasdad");
                //   file.close();
                Data = socket->readAll();

                //   Data.fromRawData((const char *) buffer, fbuffer->size);
                //   printf("tamanho buffer: %d\n", sizeof(buffer));
                //    memcpy(fbuffer->data, Data.constData(), info->size);
                qDebug() << "Data size";
                qDebug() << Data.size();
                qDebug() << "Bytes available";
                qDebug() << socket->bytesAvailable();
                qDebug()<<"Thread Remote: "<<this->QObject::thread()->currentThreadId();
                emit finishedFB();
            }
        }
        break;
    }
    socket->abort();
    socket->close();
    //    delete(socket);
    status = false;

    //  this->deleteLater();

}

void Remote::connectToServer(CustomInt modeN)
{
    qDebug() << "HAHHAHA";
    statusMode = modeN;
    socket->connectToHost(QHostAddress::LocalHost, 5037);
    if(!socket->waitForConnected(5000))
    {
        QString str1 = socket->errorString();
        QByteArray ba = str1.toLocal8Bit();
        const char *cstr2 = ba.data();
        printf("Cant connect Error: %s\n", cstr2);
        return;
    }
    printf("STATUS MODE: %d\n", statusMode);
}

