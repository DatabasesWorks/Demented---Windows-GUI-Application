#include "manageuser.h"
#include "ui_manageuser.h"
#include "database.h"
#include "edituser.h"
#include "addusers.h"
#include <QMessageBox>

ManageUser::ManageUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageUser)
{
    ui->setupUi(this);

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Employee");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT Name, ID from employeelist");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_users->setModel(model);
    conn.connClose();

}

ManageUser::~ManageUser()
{
    delete ui;
}



void ManageUser::on_tableView_users_clicked(const QModelIndex &index)
{


    ui->pushButton_Edit->setEnabled(true);
    ui->pushButton_Delete->setEnabled(true);

    int row = index.row();
    //QString name = index.sibling(row, 0).data(Qt::DisplayRole).toString();
    id = index.sibling(row, 1).data(Qt::DisplayRole).toInt();


}

void ManageUser::on_pushButton_Edit_clicked()
{
    this->hide();
    EditUser *editUser = new EditUser(0, id);
    editUser->show();
}

void ManageUser::on_pushButton_Exit_clicked()
{
    this->hide();
}

void ManageUser::on_pushButton_Add_clicked()
{
    this->hide();

    AddUsers *adder = new AddUsers();

    adder->show();

}

void ManageUser::on_pushButton_Delete_clicked()
{
    this->hide();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Demented - Delete",
                                  "Are you sure you want to DELETE this user from your database?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        Database conn;
        if(!conn.connOpen("Employee"))
        {
            qDebug()<<"Failed to open Data";
            return;
        }

        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "DELETE FROM employeelist WHERE \"ID\"='" << id << "'";

        qry->prepare(queryString);

        if(qry->exec())
        {
            QMessageBox::information(this, tr("Demented - Delete"), "User Deleted");
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }

        conn.connClose();
    }
}
