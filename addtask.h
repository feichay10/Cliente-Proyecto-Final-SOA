#ifndef ADDTASK_H
#define ADDTASK_H

#include <QWidget>

namespace Ui {
class AddTask;
}

class AddTask : public QWidget
{
    Q_OBJECT

public:
    explicit AddTask(QWidget *parent = nullptr);
    ~AddTask();

private:
    Ui::AddTask *ui;
};

#endif // ADDTASK_H
