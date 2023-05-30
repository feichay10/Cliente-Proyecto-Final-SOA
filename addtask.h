#ifndef ADDTASK_H
#define ADDTASK_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class AddTask;
}

class AddTask : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddTask(QMainWindow *parent = nullptr);
    ~AddTask();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddTask *ui;
    QMainWindow* mainWindow_; ///< It's neccesary to manipulate the main window from this object
};

#endif // ADDTASK_H

