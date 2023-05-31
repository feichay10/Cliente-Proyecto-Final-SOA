#ifndef SVCON_H
#define SVCON_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTcpSocket>

namespace Ui {
class SvCon;
}

class SvCon : public QMainWindow
{
    Q_OBJECT

public:
    explicit SvCon(QMainWindow *parent = nullptr);
    ~SvCon();

    // Methods of TCP

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_closeButton_clicked();

    void on_startButton_clicked();

private:
    Ui::SvCon *ui;
    QMainWindow* widget_mainWindow_; ///< It's neccesary to manipulate the main window from this object
    QTcpSocket* socket;

};

#endif // SVCON_H
