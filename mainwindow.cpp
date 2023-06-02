#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow),
    sv_conn(NULL),
    tasks(NULL) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::closeEvent(QCloseEvent* event) {
  if (isEnabled()) event->accept();

  else event->ignore();
}

void MainWindow::on_actionConnection_triggered() {
  if (sv_conn == NULL)
    sv_conn = new SvCon(this);

  sv_conn->setWindowTitle("Connect to Server");
  sv_conn->show();
  this->setEnabled(false);
  sv_conn->setEnabled(true);
}

void MainWindow::on_actionExit_triggered() {
  close();
}

void MainWindow::on_actionAbout_Cheddar_Client_triggered() {
  QMessageBox::information(this, "About Cheddar++ Client", "this message must be filled in the end of the development of the app");
}


void MainWindow::on_actionManual_triggered() {
  QMessageBox::information(this, "Manual", "this message must be filled in the end of the development of the app");
}


void MainWindow::on_actionTasks_triggered() {
  if (tasks == NULL)
    tasks = new AddTask(this);

  tasks->setWindowTitle("Task Adder");
  tasks->show();
  this->setEnabled(false);
  tasks->setEnabled(true);
}

// // Abrir archivo de foto
//QString nameFile = QFileDialog::getOpenFileName(this, "Abrir imagen", QDir::rootPath(), "Imágenes (*.png *.jpg *.jpeg);;Cualquier archivo(*.*)");
//ui->lineEdit_image->setText(nameFile);
//QPixmap pixmap(ui->lineEdit_image->text());
// // set a scaled pixmap
//ui->imageLabel->resize(pixmap.width(), pixmap.height());
//ui->imageLabel->setPixmap(pixmap.scaled(pixmap.width(),pixmap.height(),Qt::KeepAspectRatio));


void MainWindow::on_actionSend_Image_triggered() {
  if (sv_conn != NULL && sv_conn->socket_to_sv != NULL && sv_conn->socket_to_sv->isOpen()) {
    sv_conn->socket_to_sv->write("SEND_IMG");
    sv_conn->socket_to_sv->flush();
    sv_conn->socket_to_sv->waitForBytesWritten();
    QByteArray server_response;
    sv_conn->socket_to_sv->waitForReadyRead();

    while (sv_conn->socket_to_sv->bytesAvailable() > 0)
      server_response = sv_conn->socket_to_sv->readAll();

    if (server_response.toStdString() == "OK") {
      /// The cliente select the image
      QString imagePath = QFileDialog::getOpenFileName(this, "Select image to send to server", QDir::homePath(), "Images (*.png *.jpg *.jpeg);;Any file(*.*)");

      if (!imagePath.isEmpty()) {
        QImage imageToServer(imagePath); ///< We store the image correctly from the file system
        QByteArray byteArrayImage;
        QBuffer bufferImage(&byteArrayImage);
        bufferImage.open(QIODevice::WriteOnly);
        imageToServer.save(&bufferImage, "JPEG"); ///< We store the image in the "bufferImage" as a "JPEG" to be sent to server
        sv_conn->socket_to_sv->write(byteArrayImage);
        sv_conn->socket_to_sv->waitForBytesWritten();
      }

    } else
      QMessageBox::critical(this, "ERROR: Server does not respose", ("Server could not receive the image; it sent this: " + server_response.toStdString()).c_str());

  } else QMessageBox::critical(this, "ERROR: Image cannot be sent correctly", "There is no connection to server; go to Connection button, then try again...");
}


void MainWindow::on_actionReceive_Image_triggered() {
  if (sv_conn != NULL && sv_conn->socket_to_sv != NULL && sv_conn->socket_to_sv->isOpen()) {
    ///receive some temporal answer from server
    QByteArray bytes = sv_conn->socket_to_sv->readAll();
    QMessageBox::information(this, "Server response", bytes.toStdString().c_str());

  } else QMessageBox::critical(this, "ERROR: Image cannot be received correctly", "Nothing can be received; check Connection button, then try again...");
}
