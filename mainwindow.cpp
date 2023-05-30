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
  test->show();
}

void MainWindow::on_actionExit_triggered()
{
  close();
}


void MainWindow::on_actionAdd_task_triggered()
{
  AddTask* test = new AddTask(this);
  test->show();
  this->setEnabled(false);
  test->setEnabled(true);
}

