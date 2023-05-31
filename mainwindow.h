#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "svcon.h"
#include "addtask.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 protected:
  void closeEvent(QCloseEvent* event) override;

 private slots:
  void on_actionConnection_triggered();

  void on_actionExit_triggered();

  void on_actionAbout_Cheddar_Client_triggered();

  void on_actionManual_triggered();

  void on_actionTasks_triggered();

  void on_actionSend_Image_triggered();

  void on_actionReceive_Image_triggered();

 private:
  Ui::MainWindow* ui;
  SvCon* sv_conn;
  AddTask* tasks;
};
#endif // MAINWINDOW_H
