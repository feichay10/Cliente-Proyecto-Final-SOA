#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(QMainWindow* parent) :
  QMainWindow(parent),
  ui(new Ui::AddTask),
  mainWindow_(parent) {
  ui->setupUi(this);
}

AddTask::~AddTask() {
  delete ui;
}

void AddTask::closeEvent(QCloseEvent* event) {
  event->accept(); ///< We close the window
  if(mainWindow_ != NULL)
    mainWindow_->setEnabled(true);
}

void AddTask::on_closeButton_clicked() {
  close();
  if(mainWindow_ != NULL)
    mainWindow_->setEnabled(true);
}

void AddTask::on_addTaskButton_clicked() {
  QTableWidget* ptr = findChild<QTableWidget*>("tableWidget");
  QString new_task_name = findChild<QLineEdit*>("lineEdit_name_task")->text();

  if (new_task_name != "" && (ptr->findItems(new_task_name, Qt::MatchExactly | Qt::MatchCaseSensitive).isEmpty())) {
    QTableWidgetItem* itemName = new QTableWidgetItem(new_task_name);
    QTableWidgetItem* itemTimeOfTask = new QTableWidgetItem(QString(std::to_string(findChild<QSpinBox*>("spinBox_time_of_task")->value()).c_str()));
    QTableWidgetItem* itemPeriod = new QTableWidgetItem(QString(std::to_string(findChild<QSpinBox*>("spinBox_period")->value()).c_str()));
    QTableWidgetItem* itemDeadline = new QTableWidgetItem(QString(std::to_string(findChild<QSpinBox*>("spinBox_deadline")->value()).c_str()));

    itemName->setFlags(itemName->flags() & ~Qt::ItemIsEditable);
    itemTimeOfTask->setFlags(itemTimeOfTask->flags() & ~Qt::ItemIsEditable);
    itemPeriod->setFlags(itemPeriod->flags() & ~Qt::ItemIsEditable);
    itemDeadline->setFlags(itemDeadline->flags() & ~Qt::ItemIsEditable);

    ptr->insertRow(ptr->rowCount());
    ptr->setItem(ptr->rowCount() - 1, 0, itemName);
    ptr->setItem(ptr->rowCount() - 1, 1, itemTimeOfTask);
    ptr->setItem(ptr->rowCount() - 1, 2, itemPeriod);
    ptr->setItem(ptr->rowCount() - 1, 3, itemDeadline);
  }
}


void AddTask::on_cleanButton_clicked() {
  findChild<QLineEdit*>("lineEdit_name_task")->setText("");
  findChild<QSpinBox*>("spinBox_time_of_task")->setValue(0);
  findChild<QSpinBox*>("spinBox_period")->setValue(0);
  findChild<QSpinBox*>("spinBox_deadline")->setValue(0);
}


void AddTask::on_deleteButton_clicked() {
  QTableWidget* ptr = findChild<QTableWidget*>("tableWidget");
  ptr->removeRow(ptr->currentRow());
  findChild<QPushButton*>("deleteButton")->setEnabled(false);
}


void AddTask::on_tableWidget_cellClicked(int row, int column) {
  findChild<QPushButton*>("deleteButton")->setEnabled(true);
}

void AddTask::keyPressEvent( QKeyEvent* event ) {
  if(event->key() == Qt::Key_Delete) {
    QTableWidget* ptr = findChild<QTableWidget*>("tableWidget");
    ptr->removeRow(ptr->currentRow());
    findChild<QPushButton*>("deleteButton")->setEnabled(false);
  }
}
