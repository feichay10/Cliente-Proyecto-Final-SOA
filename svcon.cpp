#include "svcon.h"
#include "ui_svcon.h"

SvCon::SvCon(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SvCon)
{
  ui->setupUi(this);
}

SvCon::~SvCon()
{
  delete ui;
}
