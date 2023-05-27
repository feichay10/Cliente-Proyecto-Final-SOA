#include "widget.h"
#include "ui_widget.h"
#include "tcpserver.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QHostAddress>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new tcpServer(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Iniciar_clicked()
{
    if (!server->listen(QHostAddress::Any, ui->spinBox_Puerto->value())){
        QMessageBox::critical(this, "Error", server->getError());
    } else {
        QMessageBox::information(this, "Servidor", "Iniciado");
    }
}


void Widget::on_Cerrar_clicked()
{
    close();
}


void Widget::on_Enviar_clicked()
{



}


void Widget::on_toolButton_Imagen_clicked()
{
    // Abrir archivo de foto
        QString nameFile = QFileDialog::getOpenFileName(this, "Abrir imagen",
                                     QDir::rootPath(),
                                     "Imágenes (*.png *.jpg *.jpeg);;Cualquier archivo(*.*)");
        ui->lineEdit_Imagen->setText(nameFile);
        QPixmap pixmap(ui->lineEdit_Imagen->text());
        // set a scaled pixmap
        ui->label_Imagen->setPixmap(pixmap.scaled(300,300,Qt::KeepAspectRatio));
}

