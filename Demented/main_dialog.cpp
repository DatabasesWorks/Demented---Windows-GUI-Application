#include "main_dialog.h"
#include "ui_main_dialog.h"

Main_Dialog::Main_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Main_Dialog)
{
    ui->setupUi(this);
}

Main_Dialog::~Main_Dialog()
{
    delete ui;
}
