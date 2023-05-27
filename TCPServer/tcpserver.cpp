#include "tcpserver.h"

tcpServer::tcpServer(QObject *parent)
    : QTcpServer(parent)
{
    // Socket a utilizar
    socket= nullptr;
    // Total de bytes
    totalBytes = 0;
    connect(this, &TcpServer::newConnection, [&](){
        socket=nextPendingConnection();
    });
    error = "";
}

void tcpServer::sendText(QString name)
{
    if (socket) {
        // Crea elemento texto que va a enviar el socket
        QTextStream T(socket);
        // Añade mensaje
        T<<message;
        // Flushea mensaje
        socket->flush();
    }
}

void tcpServer::sendImage(QByteArray *image)
{
    // El buffer de los datos, que almacena el conjunto de bytes de la Imagen que se va a enviar por el DataStream
    QByteArray outImageBlock;
    // El objeto DataStream. Se "come" lo que le eches, no solo objetos QBytesArray
    QDataStream sendOut(&outImageBlock, QIODevice::WriteOnly);
    // El get image data te permite pasar de un objeto Pixmap, donde se guarda la imagen en el
    // lugar físico de la interfaz
    QString imageData = getImageData(pixmapVal);
    // Reserve the total size information space, the image size information space, and then enter the image information
    // Se reserva el tamañano donde se guarda la información del tamaño de la imagen y se mete ya el objeto en sí, en este
    // caso la imagen
    sendOut << qint64(0) << qint64(0) << imageData;
    // El tamaño total es la suma de los tamaños de los bloques, en este caso un bloque con el tamaño de la imagen
    // y la propia información
    totalBytes += outImageBlock.size();
    // Ahora sí metemos en el DataStream los tamaños sustituyendo al espacio asignado
    // Para ello tenemos que volver al inicio
    sendOut.device()->seek(0);
    sendOut << totalBytes << qint64((outImageBlock.size() - sizeof(qint64)*2));
    // Send the readyRead() signal
    // Desde que se envía el readyRead del socket lo tiene en cuenta
    socket->write(outImageBlock);
    socket->flush();
    // Esto sólo para que vean el debug, lo pueden BORRAR
    qDebug() << "Tamaño de la imagen: " << qint64((outImageBlock.size() - sizeof(qint64)*2));
    qDebug() << "Tamaño entero del paquete que se envía: " << totalBytes;
    // Borramos lo que tenemos
    outImageBlock.resize(0);
    totalBytes = 0;
}

QString tcpServer::getError()
{
    return error;
}


QByteArray TcpServer::getImageData(const QPixmap &pixmap)
{
    QByteArray imageData;
    QBuffer buffer(&imageData);
    QImage im = pixmap.toImage();
    im.save(&buffer, "png");
    imageData = imageData.toBase64();
    return imageData;
}
