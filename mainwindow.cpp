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
  ui->lineEdit_sim_name->installEventFilter(this);
  ui->graph_sim->installEventFilter(this);
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
  QMessageBox::information(this, "About Cheddar++ Client", "This is a real-time scheduler simulator inspired by Cheddar. It was done using QT Creator framework (version 6.5.1). This program acts as a client and connects (via TCP) to the server to introduce and retrieve data to/from the database. The main function of this program simulates a real-time scheduler the Rate Monothonic algorithm. At the same time, it can send/receive images to/from the server.");
}


void MainWindow::on_actionManual_triggered() {
  QString link = "https://github.com/feichay10/Cliente-Proyecto-Final-SOA/blob/main/README.md";
  QDesktopServices::openUrl(QUrl(link));
}


void MainWindow::on_actionTasks_triggered() {
  if (tasks == NULL)
    tasks = new AddTask(this);

  tasks->setWindowTitle("Task Adder");
  tasks->show();
  this->setEnabled(false);
  tasks->setEnabled(true);
}

void MainWindow::on_actionSend_Image_triggered() {
  if (sv_conn != NULL && sv_conn->socket_to_sv != NULL && sv_conn->socket_to_sv->isOpen()) {
    if (ui->graph_sim->isVisible()) {
      sv_conn->socket_to_sv->write("SEND_IMG");
      sv_conn->socket_to_sv->flush();
      sv_conn->socket_to_sv->waitForBytesWritten();
      QByteArray server_response;
      sv_conn->socket_to_sv->waitForReadyRead(3000);

      while (sv_conn->socket_to_sv->bytesAvailable() > 0)
        server_response = sv_conn->socket_to_sv->readAll();

      if (server_response.toStdString() == "OK") {
        ///Send image info
        sv_conn->socket_to_sv->write((ui->lineEdit_sim_name->text().toStdString() + "|" + std::to_string(((int)ui->graph_sim->yAxis->range().upper - 1)) + "|" + (last_sim_task_error_ == "" ? "YES" : "NO")).c_str());
        sv_conn->socket_to_sv->flush();
        sv_conn->socket_to_sv->waitForBytesWritten();
        ///Send image
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

    } else QMessageBox::critical(this, "ERROR: No image available", "No simulation has been done, therefore no image to send");

  } else QMessageBox::critical(this, "ERROR: Image cannot be sent correctly", "There is no connection to server; go to Connection button, then try again...");
}


void MainWindow::on_actionReceive_Image_triggered() {
  if (sv_conn != NULL && sv_conn->socket_to_sv != NULL && sv_conn->socket_to_sv->isOpen()) {
    //Open the new widget
    QByteArray message_from_server;
    sv_conn->socket_to_sv->write("RECEIVE_IMG");
    sv_conn->socket_to_sv->flush();
    sv_conn->socket_to_sv->waitForBytesWritten();
    ///Read the OK
    message_from_server.clear();
    sv_conn->socket_to_sv->waitForReadyRead(3000);

    while (sv_conn->socket_to_sv->bytesAvailable() > 0)
      message_from_server = sv_conn->socket_to_sv->readAll();

    if (message_from_server.toStdString() == "OK") {
      ///Send the filters
      Filter filter_diag;
      filter_diag.exec();
      sv_conn->socket_to_sv->write((filter_diag.findChild<QLineEdit*>("lineEdit_name")->text() + "|" + filter_diag.findChild<QSpinBox*>("spinBox_num_tasks")->text() + "|" + filter_diag.findChild<QDateTimeEdit*>("dateTimeEdit")->text()).toStdString().c_str());
      sv_conn->socket_to_sv->flush();
      sv_conn->socket_to_sv->waitForBytesWritten();
      ///Read the list
      message_from_server.clear();
      sv_conn->socket_to_sv->waitForReadyRead(3000);

      while (sv_conn->socket_to_sv->bytesAvailable() > 0)
        message_from_server = sv_conn->socket_to_sv->readAll();

      std::string wishlist = message_from_server.toStdString();

      if (wishlist.size() > 0 && wishlist != "X") {
        bool ok;
        rowInputDiag input_diag(this, wishlist);
        input_diag.exec();
        int wanted_line = input_diag.findChild<QSpinBox*>("spinBox_row_wanted")->value();
        sv_conn->socket_to_sv->write(std::to_string(wanted_line).c_str());
        sv_conn->socket_to_sv->flush();
        sv_conn->socket_to_sv->waitForBytesWritten();
        ///Receive the wanted image of the list
        message_from_server.clear();
        sv_conn->socket_to_sv->waitForReadyRead(3000);

        while (sv_conn->socket_to_sv->bytesAvailable() > 0)
          message_from_server = sv_conn->socket_to_sv->readAll();

        QImage image_from_server;
        bool delivery_success = image_from_server.loadFromData(message_from_server);

        if (delivery_success) {
          QPixmap pixmap_image_server = QPixmap::fromImage(image_from_server);
          ui->textEdit_messages->insertPlainText("\nThe server sent an image");
          ui->label_ImgFromSv->resize(pixmap_image_server.width(), pixmap_image_server.height());
          ui->label_ImgFromSv->setPixmap(pixmap_image_server);

        } else
          QMessageBox::critical(this, "Error: Cannot get the image", "The image from server had some problems to be read");

      } else
        QMessageBox::critical(this, "Error: Cannot get the image", "Server database didn't accept the petition");

    } else QMessageBox::critical(this, "Error: Cannot get the image", "Server didn't accept the transmission");

  } else QMessageBox::critical(this, "ERROR: Image cannot be received correctly", "Nothing can be received; check Connection button, then try again...");
}

void MainWindow::on_actionRun_simulation_triggered() {
  RMAlgorithm rm_algorithm(findChild<QTableWidget*>("tableWidget"));
  auto garanty_test_val = rm_algorithm.garantyTest();

  if (garanty_test_val != -1) ui->textEdit_messages->insertPlainText((std::string("\nGaranty test results: ") + std::to_string(garanty_test_val)).c_str());

  switch (garanty_test_val) {
    case -1:
      QMessageBox::critical(this, "Error: there are no tasks", "Please, check the tasks list and add some tasks");
      break;

    case 0:
    case 1: {
      last_sim_task_error_ = rm_algorithm.rateMonotonic(ui->graph_sim);
      ui->graph_sim->setVisible(true);
      ui->graph_sim->replot();
      ui->lineEdit_sim_name->setVisible(true);
      ui->label_sim_name->setVisible(true);

      if (last_sim_task_error_ != "") QMessageBox::critical(this, "Error: not planificable", (QString("Task not schedulable: ") + last_sim_task_error_).toStdString().c_str());

      break;
    }

    case 2:
      QMessageBox::critical(this, "Error: tasks overload", "Please, check the tasks list as there is an overload");
      break;

    default:
      break;
  }
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

    if (keyEvent->key() >= 0x30 && keyEvent->key() <= 0x39) {
      int graph_pos = keyEvent->key() & 0xF;

      if (graph_pos < ui->graph_sim->graphCount()) {
        if (keyEvent->modifiers() == Qt::ControlModifier)
          ui->graph_sim->graph(graph_pos)->setVisible(!ui->graph_sim->graph(graph_pos)->visible());

        else if (keyEvent->modifiers() == Qt::AltModifier)
          ui->graph_sim->graph(graph_pos)->setPen(QPen(QColor(GenerateRandomNumber(0, 255), GenerateRandomNumber(0, 255), GenerateRandomNumber(0, 255)), 2, Qt::DashLine));

        ui->graph_sim->replot();
      }
    }
  }

  return QObject::eventFilter(obj, event);
}

void MainWindow::on_lineEdit_sim_name_textChanged(const QString& new_text) {
  if (!(std::regex_match(new_text.toStdString(), std::regex("^[A-Za-z0-9]+$")))) ui->lineEdit_sim_name->undo();
}



