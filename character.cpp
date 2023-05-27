#include "character.h"
#include "ui_character.h"

character::character(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::character)
{
    ui->setupUi(this);
}

character::~character()
{
    delete ui;
}
