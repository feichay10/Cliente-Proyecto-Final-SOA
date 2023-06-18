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
#include <QClipboard>
#include <QByteArray>
#include "mainwindow.h"

namespace Ui {
class SvCon;
}

class SvCon : public QMainWindow {
  Q_OBJECT
  friend class MainWindow;
 public:
  explicit SvCon(QMainWindow* parent = nullptr);
  ~SvCon();
  bool eventFilter(QObject* obj, QEvent* event) override;

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void on_closeButton_clicked();

  void on_start_disconnButton_clicked();


 private:
  Ui::SvCon* ui;
  QMainWindow* widget_mainWindow_; ///< It's neccesary to manipulate the main window from this object
  QTcpSocket* socket_to_sv;
};

#endif // SVCON_H
