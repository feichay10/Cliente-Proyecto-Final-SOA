#ifndef PERSON_H
#define PERSON_H

#include <QDialog>

namespace Ui {
class person;
}

class person : public QDialog
{
    Q_OBJECT

public:
    explicit person(QWidget *parent = nullptr);
    ~person();

private:
    Ui::person *ui;
};

#endif // PERSON_H
