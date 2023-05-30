#ifndef ADDTASK_H
#define ADDTASK_H

#include <QMainWindow>

namespace Ui {
class AddTask;
}

class AddTask : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddTask(QMainWindow *parent = nullptr);
    ~AddTask();

private:
    Ui::AddTask *ui;
};

#endif // ADDTASK_H
