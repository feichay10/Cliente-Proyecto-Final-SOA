#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow),
    sv_conn(NULL),
    tasks(NULL),
    last_graph_(NULL) {
  ui->setupUi(this);
  ui->graph_sim->setVisible(false);
  ui->lineEdit_sim_name->setVisible(false);
  ui->label_sim_name->setVisible(false);
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
  //if (sv_conn != NULL && sv_conn->socket_to_sv != NULL && sv_conn->socket_to_sv->isOpen() && !ui->label_Image_Simulation->pixmap().isNull()) {
  if (sv_conn != NULL && sv_conn->socket_to_sv != NULL && sv_conn->socket_to_sv->isOpen()) {
    sv_conn->socket_to_sv->write("SEND_IMG");
    sv_conn->socket_to_sv->flush();
    sv_conn->socket_to_sv->waitForBytesWritten();
    QByteArray server_response;
    sv_conn->socket_to_sv->waitForReadyRead();

    while (sv_conn->socket_to_sv->bytesAvailable() > 0)
      server_response = sv_conn->socket_to_sv->readAll();

    if (server_response.toStdString() == "OK") {
      //sv_conn->socket_to_sv->write("SIM_INFO:" + ui->lineEdit_sim_name->text() + "|" + );
      sv_conn->socket_to_sv->flush();
      sv_conn->socket_to_sv->waitForBytesWritten();
      QPixmap pix = ui->graph_sim->toPixmap();
      QImage image_to_server = pix.toImage();
      QByteArray byteArrayImage;
      QBuffer bufferImage(&byteArrayImage);
      bufferImage.open(QIODevice::WriteOnly);
      image_to_server.save(&bufferImage, "JPEG"); ///< We store the image in the "bufferImage" as a "JPEG" to be sent to server
      sv_conn->socket_to_sv->write(byteArrayImage);
      sv_conn->socket_to_sv->waitForBytesWritten();

    } else
      QMessageBox::critical(this, "ERROR: Server does not send response", ("Server could not receive the image; it sent this: " + server_response.toStdString()).c_str());

  } else QMessageBox::critical(this, "ERROR: Image cannot be sent correctly", "There is no connection to server; go to Connection button, then try again...");
}


void MainWindow::on_actionReceive_Image_triggered() {
  if (sv_conn != NULL && sv_conn->socket_to_sv != NULL && sv_conn->socket_to_sv->isOpen()) {
    ///receive some temporal answer from server
    QByteArray message_from_server;
    sv_conn->socket_to_sv->write("RECEIVE_IMG");
    sv_conn->socket_to_sv->flush();
    sv_conn->socket_to_sv->waitForBytesWritten();
    sv_conn->socket_to_sv->waitForReadyRead();

    while (sv_conn->socket_to_sv->bytesAvailable() > 0)
      message_from_server = sv_conn->socket_to_sv->readAll();

    QImage image_from_server;
    bool delivery_success = image_from_server.loadFromData(message_from_server);

    if (delivery_success) {
      QPixmap pixmap_image_server = QPixmap::fromImage(image_from_server);
      ui->textEdit_messages->insertPlainText("\nThe server sent a simulation");
      //ui->label_Image_Simulation->resize(pixmap_image_server.width(), pixmap_image_server.height());
      //ui->label_Image_Simulation->setPixmap(pixmap_image_server);

    } else
      QMessageBox::critical(this, "Error: Cannot be able to get the image", "The image from server had some problems to be read");

  } else QMessageBox::critical(this, "ERROR: Image cannot be received correctly", "Nothing can be received; check Connection button, then try again...");
}

void MainWindow::on_actionRun_simulation_triggered() {
  RMAlgorithm rm_algorithm(findChild<QTableWidget*>("tableWidget"));

  switch (rm_algorithm.garantyTest()) {
    case -1:
      QMessageBox::critical(this, "Error: there are no tasks", "Please, check the tasks list and add some tasks");
      break;

    case 0:
    case 1: {
      if (!(last_sim_is_schedulable_ = rm_algorithm.rateMonotonic(ui->graph_sim))) QMessageBox::critical(this, "Error: not planificable", "TEST");

      ui->graph_sim->setVisible(true);
      ui->graph_sim->replot();
      ui->lineEdit_sim_name->setVisible(true);
      ui->label_sim_name->setVisible(true);
      break;
    }

    case 2:
      QMessageBox::critical(this, "Error: tasks overload", "Please, check the tasks list as there is an overload");
      break;

    default:
      break;
  }
}
