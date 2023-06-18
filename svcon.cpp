#include "svcon.h"
#include "ui_svcon.h"

SvCon::SvCon(QMainWindow* parent) :
  QMainWindow(parent),
  ui(new Ui::SvCon),
  widget_mainWindow_(parent),
  socket_to_sv(NULL) {
  ui->setupUi(this);
  ui->spinBox_IP_1->installEventFilter(this);
  ui->spinBox_IP_2->installEventFilter(this);
  ui->spinBox_IP_3->installEventFilter(this);
  ui->spinBox_IP_4->installEventFilter(this);
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
  if (socket_to_sv == NULL && findChild<QPushButton*>("start_disconnButton")->text() == "Start") {
    socket_to_sv = new QTcpSocket;
    std::string IP = std::to_string(ui->spinBox_IP_1->value()) + "." + std::to_string(ui->spinBox_IP_2->value()) + "." + std::to_string(ui->spinBox_IP_3->value()) + "." + std::to_string(ui->spinBox_IP_4->value());
    socket_to_sv->connectToHost(QHostAddress(IP.c_str()), findChild<QSpinBox*>("spinBox_port")->value());
    socket_to_sv->open(QIODevice::ReadWrite);
    QString port = std::to_string(findChild<QSpinBox*>("spinBox_port")->value()).c_str();
    ui->start_disconnButton->setText("Disconnect");
    ((MainWindow*)widget_mainWindow_)->findChild<QTextEdit*>("textEdit_messages")->insertPlainText((socket_to_sv->isOpen() && socket_to_sv->isValid()) ? ("Connected correctly with " + IP + ":" + port.toStdString() + "\n").c_str() : "Error when connecting\n");

  } else if (ui->start_disconnButton->text() == "Disconnect") {
    if (socket_to_sv != NULL) {
      socket_to_sv->close();
      delete socket_to_sv;
      socket_to_sv = NULL;
    }

    ui->start_disconnButton->setText("Start");
    ((MainWindow*)widget_mainWindow_)->findChild<QTextEdit*>("textEdit_messages")->insertPlainText("Disconnected from server\n"); ///< It's neccesary to manipulate the main window from this object
  }
}

bool SvCon::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

    if (keyEvent->modifiers() == Qt::ControlModifier && keyEvent->key() == Qt::Key_V) {
      const std::string kZeroTo255Regex{"25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9]"};
      std::regex valid_input("^(" + kZeroTo255Regex + ")\\.(" + kZeroTo255Regex + ")\\.(" + kZeroTo255Regex + ")\\.(" + kZeroTo255Regex + ")$");
      std::smatch number_groups;
      QClipboard* clipboard = QGuiApplication::clipboard();
      std::string clipboard_IP = clipboard->text().toStdString();
      std::regex_match(clipboard_IP, number_groups, valid_input);

      if (!number_groups.empty()) {
        ui->spinBox_IP_1->setValue(std::stoi(number_groups[1]));
        ui->spinBox_IP_2->setValue(std::stoi(number_groups[2]));
        ui->spinBox_IP_3->setValue(std::stoi(number_groups[3]));
        ui->spinBox_IP_4->setValue(std::stoi(number_groups[4]));
      }

      return true;
    }
  }

  return QObject::eventFilter(obj, event);
}
