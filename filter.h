#ifndef FILTER_H
#define FILTER_H

#include <QDialog>
#include <regex>

namespace Ui {
class Filter;
}

class Filter : public QDialog {
  Q_OBJECT

 public:
  explicit Filter(QWidget* parent = nullptr);
  ~Filter();

 private slots:

  void on_lineEdit_name_textChanged(const QString& arg1);

 private:
  Ui::Filter* ui;
};

#endif // FILTER_H
