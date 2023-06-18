#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QBuffer>
#include <QLabel>
#include <QTextStream>
#include "addtask.h"
#include "rmalgorithm.h"
#include "qcustomplot.h"
#include "svcon.h"

class SvCon;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
  friend class SvCon;
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
  void on_actionRun_simulation_triggered();

 private:
  Ui::MainWindow* ui;
  SvCon* sv_conn;
  AddTask* tasks;
  QCustomPlot* last_graph_;
  QString last_sim_task_error_;
};
#endif // MAINWINDOW_H
