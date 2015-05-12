#include "menu.h"
#include "ui_menu.h"
#include "login.h"

menu::menu(QWidget *parent, QString namePassed, bool isAdmin) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    name = namePassed;
    admin = isAdmin;

    QPixmap pix(QDir::currentPath() + "/pixMap/Inventory_Icon.png");
    QIcon icon(pix);
    ui->pushButton_Inventory->setIcon(icon);
    ui->pushButton_Inventory->setIconSize(pix.size());

    QPixmap pix2(QDir::currentPath() + "/pixMap/logout_icon.png");
    QIcon icon2(pix2);
    ui->pushButton_Logout->setIcon(icon2);
    ui->pushButton_Logout->setIconSize(pix2.size());
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_Inventory_clicked()
{
    this->hide();
    Manager *manager = new Manager();
    manager->sendUsername(name, admin);
    qDebug() << "NAME IN LOGIN.CPP:";
    qDebug() << name;
    manager->setup();
    manager->showMaximized();
}

void menu::on_pushButton_Logout_clicked()
{
    this->hide();
    Login *login = new Login();
    login->show();
    return;
}
