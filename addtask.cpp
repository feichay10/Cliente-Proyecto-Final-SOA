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

void AddTask::on_pushButton_clicked()
{
    close();
    if(mainWindow_ != NULL) {
        mainWindow_->setEnabled(true);
    }
}
