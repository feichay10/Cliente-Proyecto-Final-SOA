#include "rowinputdiag.h"
#include "ui_rowinputdiag.h"

rowInputDiag::rowInputDiag(QWidget* parent, const std::string& ok_str) :
  QDialog(parent),
  ui(new Ui::rowInputDiag),
  ok_rows_(ok_str) {
  ui->setupUi(this);
  ui->spinBox_row_wanted->setValue(std::stoi(ok_str.substr(0, 1)));
  ui->label_images->setText(ok_str.c_str());
}

rowInputDiag::~rowInputDiag() {
  delete ui;
}

void rowInputDiag::on_spinBox_row_wanted_valueChanged(int val) {
  std::vector<int> rows_allowed;
  std::stringstream stream(ok_rows_);
  std::string str;

  while (std::getline(stream, str))
    rows_allowed.push_back(std::stoi(str.substr(0, 1)));

  if (std::find(rows_allowed.begin(), rows_allowed.end(), val) == rows_allowed.end()) ui->spinBox_row_wanted->setValue(rows_allowed[0]);
}

