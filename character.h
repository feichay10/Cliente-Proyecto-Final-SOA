#ifndef CHARACTER_H
#define CHARACTER_H

#include <QDialog>

namespace Ui {
class character;
}

class character : public QDialog
{
    Q_OBJECT

public:
    explicit character(QWidget *parent = nullptr);
    ~character();

private:
    Ui::character *ui;
};

#endif // CHARACTER_H
