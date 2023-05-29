#include "tcptosv.h"
#include "ui_tcptosv.h"

tcptosv::tcptosv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcptosv)
{
    ui->setupUi(this);
}

tcptosv::~tcptosv()
{
    delete ui;
}
