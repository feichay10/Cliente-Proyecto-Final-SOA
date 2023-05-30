#include "svcon.h"
#include "ui_svcon.h"

SvCon::SvCon(QMainWindow *parent) :
    QMainWindow(parent),
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

void SvCon::on_closeButton_clicked()
{
    close();
    if(widget_mainWindow_ != NULL) {
        widget_mainWindow_->setEnabled(true);
    }
}

