#include "svcon.h"
#include "ui_svcon.h"

SvCon::SvCon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SvCon),
    widget_mainWindow_(parent)
{
    ui->setupUi(this);
}

SvCon::~SvCon()
{
    delete ui;
}

void SvCon::closeEvent(QCloseEvent *event)
{
    event->accept(); ///< We close the window
    if(widget_mainWindow_ != NULL) {
        widget_mainWindow_->setEnabled(true);
    }
}

void SvCon::on_pushButton_clicked()
{

}

