#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::AddTask)
{
    ui->setupUi(this);
}

AddTask::~AddTask()
{
    delete ui;
}
