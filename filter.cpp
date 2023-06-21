#include "filter.h"
#include "ui_filter.h"

Filter::Filter(QWidget* parent) :
  QDialog(parent),
  ui(new Ui::Filter) {
  ui->setupUi(this);
}

Filter::~Filter() {
  delete ui;
}

void Filter::on_lineEdit_name_textChanged(const QString& new_text) {
  if (!(std::regex_match(new_text.toStdString(), std::regex("^[A-Za-z0-9]*$")))) ui->lineEdit_name->undo();
}

void Filter::on_pushButton_accept_clicked()
{
  close();
}


void Filter::on_pushButton_ignore_filters_clicked()
{
  ui->dateTimeEdit->setDateTime(QDateTime::fromString(QString("2000-01-01 00:00:00"), "yyyy-MM-dd hh:mm:ss"));
  ui->spinBox_num_tasks->setValue(0);
  ui->lineEdit_name->setText("");
}
