#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::closeEvent(QCloseEvent* event)
{
  if(this != NULL) {
      if(this->isEnabled() == true) {
          event->accept(); ///< We close the window
      } else {
          event->ignore(); ///< We don't close the window because others widgets would be activated
      }
  }
}

void MainWindow::on_actionConnection_triggered() {
  SvCon* test = new SvCon(this);
  test->setWindowTitle("Connect to Server");
  test->show();
  this->setEnabled(false);
  test->setEnabled(true);
}

void MainWindow::on_actionExit_triggered()
{
  close();
}

void MainWindow::on_actionAbout_Cheddar_Client_triggered()
{
  QMessageBox::information(this, "About Cheddar++ Client", "this message must be filled in the end of the development of the app");
}


void MainWindow::on_actionManual_triggered()
{
    QMessageBox::information(this, "Manual", "this message must be filled in the end of the development of the app");
}


void MainWindow::on_actionTasks_triggered()
{
    AddTask* test = new AddTask(this);
    test->setWindowTitle("Task Adder");

    test->show();
    this->setEnabled(false);
    test->setEnabled(true);
}

