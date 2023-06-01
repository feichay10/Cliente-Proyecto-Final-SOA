#include "svcon.h"
#include "ui_svcon.h"

SvCon::SvCon(QMainWindow* parent) :
  QMainWindow(parent),
  ui(new Ui::SvCon),
  widget_mainWindow_(parent),
  socket_to_sv(NULL) {
  ui->setupUi(this);
  last_IP_text = findChild<QLineEdit*>("lineEdit_ServerIP")->text();
}

SvCon::~SvCon() {
  if (socket_to_sv != NULL) {
    socket_to_sv->close();
    delete socket_to_sv;
    socket_to_sv = NULL;
  }

  delete ui;
}

void SvCon::closeEvent(QCloseEvent* event) {
  event->accept(); ///< We close the window

  if(widget_mainWindow_ != NULL)
    widget_mainWindow_->setEnabled(true);
}

void SvCon::on_closeButton_clicked() {
  close();

  if(widget_mainWindow_ != NULL)
    widget_mainWindow_->setEnabled(true);
}


void SvCon::on_start_disconnButton_clicked() {
  const std::string kZeroTo255Regex{"25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9]"};
  std::regex good_IP("^(((" + kZeroTo255Regex + ")\\.){3}(" + kZeroTo255Regex + "))$");
  if (socket_to_sv == NULL && findChild<QPushButton*>("start_disconnButton")->text() == "Start") {
    if (std::regex_match(last_IP_text.toStdString(), good_IP)) {
        socket_to_sv = new QTcpSocket;
        socket_to_sv->connectToHost(QHostAddress(last_IP_text), findChild<QSpinBox*>("spinBox_port")->value());
        socket_to_sv->open(QIODevice::ReadWrite);
        QString port = std::to_string(findChild<QSpinBox*>("spinBox_port")->value()).c_str();
        findChild<QPushButton*>("start_disconnButton")->setText("Disconnect");
        QMessageBox::information(this, "Server connection", (socket_to_sv->isOpen() && socket_to_sv->isValid()) ? ("Connected correctly with " + last_IP_text + ":" + port) : "Error when connecting");
    } else {
        QMessageBox::information(this, "Error: Wrong IP", "The IP given is wrong, change it and try again");
    }
  } else if (findChild<QPushButton*>("start_disconnButton")->text() == "Disconnect") {
    if (socket_to_sv != NULL) {
      socket_to_sv->close();
      delete socket_to_sv;
      socket_to_sv = NULL;
    }

    findChild<QPushButton*>("start_disconnButton")->setText("Start");
    QMessageBox::information(this, windowTitle(), "Disconnected from server");
  }
}


void SvCon::on_lineEdit_ServerIP_textChanged(const QString& user_string_ip) {
  const std::string kZeroTo255Regex{"25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9]"};
  std::regex valid_input("^(" + kZeroTo255Regex + ")?(\\.)?(" + kZeroTo255Regex + ")?(\\.)?(" + kZeroTo255Regex + ")?(\\.)?(" + kZeroTo255Regex + ")?$");
  if (!std::regex_match(user_string_ip.toStdString(), valid_input)) findChild<QLineEdit*>("lineEdit_ServerIP")->setText(last_IP_text);
  else last_IP_text = user_string_ip;
}
