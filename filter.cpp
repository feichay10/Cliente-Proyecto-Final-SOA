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

