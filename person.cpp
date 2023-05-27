#include "person.h"
#include "ui_person.h"

person::person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::person)
{
    ui->setupUi(this);
}

person::~person()
{
    delete ui;
}
