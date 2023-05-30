#ifndef SVCON_H
#define SVCON_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class SvCon;
}

class SvCon : public QWidget
{
    Q_OBJECT

public:
    explicit SvCon(QWidget *parent = nullptr);
    ~SvCon();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::SvCon *ui;
    QWidget* widget_mainWindow_; ///< It's neccesary to manipulate the main window from this object
};

#endif // SVCON_H
