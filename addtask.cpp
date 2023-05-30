#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AddTask),
    mainWindow_(parent)
{
    ui->setupUi(this);
}

AddTask::~AddTask()
{
    delete ui;
}

void AddTask::closeEvent(QCloseEvent *event)
{
    event->accept(); ///< We close the window
    if(mainWindow_ != NULL) {
        mainWindow_->setEnabled(true);
    }
}

void AddTask::on_closeButton_clicked()
{
    close();
    if(mainWindow_ != NULL) {
        mainWindow_->setEnabled(true);
    }
}

void AddTask::on_addTaskButton_clicked()
{

}


void AddTask::on_cleanButton_clicked()
{
    findChild<QLineEdit*>("lineEdit_name_task")->setText("");
    findChild<QSpinBox*>("spinBox_time_of_task")->setValue(0);
    findChild<QSpinBox*>("spinBox_period")->setValue(0);
    findChild<QSpinBox*>("spinBox_deadline")->setValue(0);
}


void AddTask::on_pushButton_clicked()
{
    auto* ptr = findChild<QTableWidget*>("tableWidget");
    ptr->removeRow(ptr->currentRow());
}


void AddTask::on_tableWidget_cellClicked(int row, int column)
{
    findChild<QPushButton*>("deleteButton")->setEnabled(true);

}

