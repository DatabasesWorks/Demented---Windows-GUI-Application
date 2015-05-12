#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QPalette>
#include "menu.h"
#include "adminmenu.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    QPixmap pix(QDir::currentPath() + "/pixMap/LOGO.jpg");
    ui->label_pic->setPixmap(pix);

    QPalette palette = ui->label_username->palette();
    palette.setColor(ui->label_username->foregroundRole(), Qt::white);
    ui->label_username->setPalette(palette);

    palette = ui->label_password->palette();
    palette.setColor(ui->label_password->foregroundRole(), Qt::white);
    ui->label_password->setPalette(palette);

    palette = ui->label_status->palette();
    palette.setColor(ui->label_status->foregroundRole(), Qt::white);
    ui->label_status->setPalette(palette);

    palette = ui->groupBox->palette();
    palette.setColor(ui->groupBox->foregroundRole(), Qt::white);
    ui->groupBox->setPalette(palette);

    palette = ui->label_Build->palette();
    palette.setColor(ui->label_Build->foregroundRole(), Qt::white);
    ui->label_Build->setPalette(palette);

    if(!connOpen())
        ui->label_status->setText("Database Failed to connect");
    else
        ui->label_status->setText("Connected to Database..");

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString password, username, name;
    bool admin = false;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();

    Database conn;
    if(!conn.connOpen("Employee"))
    {
        qDebug()<<"Failed to open Data";
        return;
    }

    QSqlQuery *qry = new QSqlQuery(conn.mydb);
    qry->prepare("select * from employeelist where Username = '"+username +"' and Password='"+password +"'");

    if(qry->exec())
    {
        int count = 0;
        while(qry->next())
        {
            name = qry->value(3).toString();
            admin = qry->value(2).toBool();
            count++;
        }
        if(count == 1)
        {
            ui->label_status->setText("Username and Password Correct");

            if(admin)
            {
                qDebug()<<"IS ADMIN\n";
                qDebug()<< admin;
                connClose();
                this->hide();
                AdminMenu *adminMenu = new AdminMenu(0, name, true);
                adminMenu->show();

            }
            else
            {
                qDebug()<<"NOT ADMIN";

                connClose();
                this->hide();

                menu *mainMenu = new menu(0, name, false);
                mainMenu->show();

            }
        }
        else if(count > 1)
            ui->label_status->setText("Duplicate Username and Password");
        else if(count < 1)
            ui->label_status->setText("Incorrect Username and Password");
        else
            ui->label_status->setText("ERROR" );
    }
}
