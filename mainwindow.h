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

  void on_actionAdd_task_triggered();

  private:
  Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
