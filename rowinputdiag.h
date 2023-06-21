#ifndef ROWINPUTDIAG_H
#define ROWINPUTDIAG_H

#include <QDialog>
#include <sstream>

namespace Ui {
class rowInputDiag;
}

class rowInputDiag : public QDialog {
  Q_OBJECT

 public:
  explicit rowInputDiag(QWidget* parent, const std::string&);
  ~rowInputDiag();

 private slots:
  void on_spinBox_row_wanted_valueChanged(int val);

 private:
  Ui::rowInputDiag* ui;
  std::string ok_rows_;
};

#endif // ROWINPUTDIAG_H
