#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QPixmap>
#include <QTcpSocket>

class tcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpServer(QObject *parent = nullptr);
    void sendText(QString name);
    void sendImage(QByteArray *image);

    QString getError();

private:
    QTcpSocket *socket;
    QImage *imageObject;
    QPixmap image;
    qint64 totalBytes;
    QString error;

    QByteArray getImageData(const QPixmap &pixmap);
};

#endif // TCPSERVER_H
