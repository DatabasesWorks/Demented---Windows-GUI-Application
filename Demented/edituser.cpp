#include "edituser.h"
#include "ui_edituser.h"
#include "database.h"
#include "QMessageBox"

EditUser::EditUser(QWidget *parent, qint32 id) :
    QDialog(parent),
    ui(new Ui::EditUser)
{
    ui->setupUi(this);

    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);

    userID = id;

    ui->label_ID->setText(QString::number(id));

    Database conn;
    conn.connOpen("Employee");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "SELECT * from employeelist WHERE ID ='" << userID << "'";

    qry->prepare(queryString);

    qry->exec();
    while(qry->next())
    {
        ui->lineEdit_Name->setText(qry->value(3).toString());
        ui->lineEdit_Username->setText(qry->value(0).toString());
        ui->lineEdit_Password->setText(qry->value(1).toString());

        if(qry->value(2).toInt())
            ui->checkBox_admin->setChecked(true);
    }
    conn.connClose();
}

EditUser::~EditUser()
{
    delete ui;
}

void EditUser::on_pushButton_Cancel_clicked()
{
    this->hide();
}

void EditUser::on_pushButton_Save_clicked()
{
    QString name, user, pass, admin;
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

    queryStream << "UPDATE employeelist SET Name='" << name << "', Username='" << user << "', Password='" << pass
                << "', Admin='" << admin << "' WHERE ID=" << userID;


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
        QMessageBox::information(this, tr("Demented - Edit User"), "User Succesfully Updated");

    conn.connClose();

    this->hide();
}

void EditUser::on_checkBox_toggled(bool checked)
{
    if(checked)
        ui->lineEdit_Password->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
}
