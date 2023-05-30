#include "addtask.h"
#include "ui_addtask.h"

AddTask::AddTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTask)
{
    ui->setupUi(this);
}

AddTask::~AddTask()
{
    delete ui;
}
