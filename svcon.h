#ifndef SVCON_H
#define SVCON_H

#include <QMainWindow>

namespace Ui {
  class SvCon;
}

class SvCon : public QMainWindow
{
  Q_OBJECT

public:
  explicit SvCon(QWidget *parent = nullptr);
  ~SvCon();

private:
  Ui::SvCon *ui;
};

#endif // SVCON_H
