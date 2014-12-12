#include "addusers.h"
#include "ui_addusers.h"
#include "database.h"
#include <QMessageBox>

AddUsers::AddUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUsers)
{
    ui->setupUi(this);
    qint32 newID;

    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);

    Database conn;
    conn.connOpen("Employee");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "SELECT DISTINCT ID from employeelist";

    qry->prepare(queryString);

    qry->exec();
    while(qry->next())
    {
       newID = qry->value(0).toInt();
    }
    ++newID;

    ui->label_ID->setText(QString::number(newID));
    conn.connClose();

}

AddUsers::~AddUsers()
{
    delete ui;
}

void AddUsers::on_checkBox_toggled(bool checked)
{
    if(checked)
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
}

void AddUsers::on_pushButton_Save_clicked()
{
    QString name, user, pass, admin;
    qint32 ID = ui->label_ID->text().toInt();
    name = ui->lineEdit_Name->text();
    user = ui->lineEdit_Username->text();
    pass = ui->lineEdit_Password->text();

    if(ui->checkBox_admin->isChecked())
        admin = "1";
    else
        admin = "0";

    Database conn;
    if(!conn.connOpen("Employee"))
    {
        qDebug()<<"Failed to open Data";
        return;
    }

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO employeelist (Username, Password, Admin, Name, ID) "
                << "VALUES ('" << user << "', '" << pass << "', '" << admin << "', '"
                << name << "', '" << ID << "')";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
        QMessageBox::information(this, tr("Demented - Add User"), "User Succesfully Added");

    conn.connClose();

    this->hide();
}

void AddUsers::on_pushButton_Cancel_clicked()
{
    this->hide();
}
