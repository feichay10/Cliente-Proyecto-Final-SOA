#ifndef SVCON_H
#define SVCON_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <regex>
#include <QByteArray>

namespace Ui {
class SvCon;
}

class SvCon : public QMainWindow {
  Q_OBJECT
  friend class MainWindow;
 public:
  explicit SvCon(QMainWindow* parent = nullptr);
  ~SvCon();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void on_closeButton_clicked();

  void on_start_disconnButton_clicked();

  void on_lineEdit_ServerIP_textChanged(const QString& arg1);

 private:
  Ui::SvCon* ui;
  QMainWindow* widget_mainWindow_; ///< It's neccesary to manipulate the main window from this object
  QTcpSocket* socket_to_sv;
  QString last_IP_text;
};

#endif // SVCON_H
