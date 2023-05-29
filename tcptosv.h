#ifndef TCPTOSV_H
#define TCPTOSV_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class tcptosv;
}
QT_END_NAMESPACE

class tcptosv : public QWidget
{
    Q_OBJECT

public:
    explicit tcptosv(QWidget *parent = nullptr);
    ~tcptosv();

private:
    Ui::tcptosv *ui;
};

#endif // TCPTOSV_H
