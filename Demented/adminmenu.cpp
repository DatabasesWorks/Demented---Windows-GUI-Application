#include "adminmenu.h"
#include "ui_adminmenu.h"
#include "masterlog.h"
#include "login.h"
#include "manageuser.h"

AdminMenu::AdminMenu(QWidget *parent, QString userPassed, bool isAdmin) :
    QDialog(parent),
    ui(new Ui::AdminMenu)
{
    ui->setupUi(this);

    name = userPassed;
    admin = isAdmin;

    QPixmap pix(QDir::currentPath() + "/pixMap/Inventory_Icon.png");
    QIcon icon(pix);
    ui->pushButton_Inventory->setIcon(icon);
    ui->pushButton_Inventory->setIconSize(pix.size());

    QPixmap pix2(QDir::currentPath() + "/pixMap/log_icon.png");
    QIcon icon2(pix2);
    ui->pushButton_Log->setIcon(icon2);
    ui->pushButton_Log->setIconSize(pix2.size());

    QPixmap pix3(QDir::currentPath() + "/pixMap/users_icon.png");
    QIcon icon3(pix3);
    ui->pushButton_users->setIcon(icon3);
    ui->pushButton_users->setIconSize(pix3.size());

    QPixmap pix4(QDir::currentPath() + "/pixMap/logout_icon.png");
    QIcon icon4(pix4);
    ui->pushButton_Logout->setIcon(icon4);
    ui->pushButton_Logout->setIconSize(pix4.size());

}

AdminMenu::~AdminMenu()
{
    delete ui;
}

void AdminMenu::on_pushButton_Inventory_clicked()
{
    this->hide();
    Manager *manager = new Manager();
    manager->sendUsername(name, admin);
    manager->setup();
    manager->showMaximized();
}

void AdminMenu::on_pushButton_Log_clicked()
{
    this->hide();
    MasterLog *masterLog = new MasterLog();
    masterLog->sendUsername(name, admin);
    masterLog->setup();
    masterLog->showMaximized();
}

void AdminMenu::on_pushButton_users_clicked()
{
    ManageUser *manageUser = new ManageUser();

    manageUser->show();
}

void AdminMenu::on_pushButton_Logout_clicked()
{
    this->hide();
    Login *login = new Login();
    login->show();
    return;
}
