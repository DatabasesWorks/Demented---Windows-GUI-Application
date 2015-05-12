#include "masterlog.h"
#include "ui_masterlog.h"
#include "database.h"
#include "adminmenu.h"
#include "menu.h"
#include "logobject.h"
#include <QDateTime>
#include <QMessageBox>

MasterLog::MasterLog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterLog)
{
    ui->setupUi(this);



    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Log");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from Log");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_Log->setModel(model);
}

void MasterLog :: setup()
{
    ui->label_Welcome->setText("<b><font size=\"4\">Welcome, " + currentUser + "</font></b>");

    Database conn;

    conn.connOpen("Log");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    ui->comboBox_User->addItem("Select a User");

    qry->prepare("SELECT DISTINCT User from Log");
    qry->exec();
    while(qry->next())
    {
        ui->comboBox_User->addItem(qry->value(0).toString());
    }

    QModelIndex index = ui->comboBox_User->model()->index(0, 0);
    QVariant v(0);
    ui->comboBox_User->model()->setData(index, v, Qt::UserRole - 1);

    conn.connClose();

    Database conn1;

    conn1.connOpen("Log");
    QSqlQuery * qry1 = new QSqlQuery(conn1.mydb);

    ui->comboBox_Action->addItem("Select an Action");

    qry1->prepare("SELECT DISTINCT Action from Log");
    qry1->exec();
    while(qry1->next())
    {
        ui->comboBox_Action->addItem(qry1->value(0).toString());
    }

    QModelIndex index1 = ui->comboBox_Action->model()->index(0, 0);
    QVariant v1(0);
    ui->comboBox_Action->model()->setData(index1, v1, Qt::UserRole - 1);

    conn1.connClose();

    bool firstRun = true;
    Database conn2;

    conn2.connOpen("Log");
    QSqlQuery * qry2 = new QSqlQuery(conn2.mydb);

    qry2->prepare("SELECT DISTINCT \"Time Stamp\" from Log");
    qry2->exec();

    while(qry2->next())
    {
        QDateTime myDate = QDateTime::fromString(qry2->value(0).toString(),"yyyy-MM-dd HH:mm:ss");
        if(firstRun)
            ui->dateTimeEdit_from->setDateTime(myDate);
        firstRun = false;
        ui->dateTimeEdit_to->setDateTime(myDate);
    }

    conn2.connClose();
}

MasterLog::~MasterLog()
{
    delete ui;
}

void MasterLog::on_pushButton_Menu_clicked()
{
    this->hide();
    if(admin)
    {
        AdminMenu *adminMenu = new AdminMenu(0, currentUser, admin);
        adminMenu->show();
    }
    else
    {
        menu *mainMenu = new menu(0, currentUser, admin);
        mainMenu->show();
    }
}

void MasterLog::on_pushButton_Logout_clicked()
{
    this->hide();
    Login *login = new Login();
    login->show();
    return;
}

void MasterLog::on_tableView_Log_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QString tempTimeStamp = index.sibling(row, 0).data(Qt::DisplayRole).toString();
    QString tempUser = index.sibling(row, 1).data(Qt::DisplayRole).toString();
    QString tempAction = index.sibling(row, 2).data(Qt::DisplayRole).toString();
    qint32 tempCatNum = index.sibling(row, 3).data(Qt::DisplayRole).toInt();
    double tempAmount = index.sibling(row, 4).data(Qt::DisplayRole).toDouble();
    qint32 tempXS = index.sibling(row, 5).data(Qt::DisplayRole).toInt();
    qint32 tempS = index.sibling(row, 6).data(Qt::DisplayRole).toInt();
    qint32 tempM = index.sibling(row, 7).data(Qt::DisplayRole).toInt();
    qint32 tempL = index.sibling(row, 8).data(Qt::DisplayRole).toInt();
    qint32 tempXL = index.sibling(row, 9).data(Qt::DisplayRole).toInt();
    qint32 tempXXL = index.sibling(row, 10).data(Qt::DisplayRole).toInt();
    qint32 tempTQ = index.sibling(row, 11).data(Qt::DisplayRole).toInt();
    QString tempNotes = index.sibling(row, 12).data(Qt::DisplayRole).toString();

    LogObject *logObject = new LogObject();

    logObject->sendLogObject(tempTimeStamp, tempUser, tempAction, tempCatNum, tempAmount,
                             tempXS, tempS, tempM, tempL, tempXL, tempXXL, tempTQ, tempNotes);
    logObject->setup();
    logObject->show();
}

void MasterLog::on_pushButton_Search_clicked()
{
    QString from = ui->dateTimeEdit_from->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString to = ui->dateTimeEdit_to->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Log");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "SELECT * from log WHERE \"Time Stamp\" >= '"+from+"'";
    queryStream << " AND \"Time Stamp\" <= '"+to+"'";

    if(ui->comboBox_User->currentText() != "Select a User")
    {
        queryStream << " AND User='"+ui->comboBox_User->currentText()+"'";
    }

    if(ui->comboBox_Action->currentText() != "Select an Action")
    {
        queryStream << " AND Action='"+ui->comboBox_Action->currentText()+"'";
    }
    if(ui->lineEdit_CatNum->text() != "")
    {
        queryStream << " AND \"Catalog Number\"='"+ui->lineEdit_CatNum->text()+"'";
    }

    qry->prepare(queryString);
    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    model->setQuery(*qry);
    ui->tableView_Log->setModel(model);

    conn.connClose();
}

void MasterLog::on_pushButton_Clear_clicked()
{
    bool firstRun = true;
    Database conn2;

    conn2.connOpen("Log");
    QSqlQuery * qry2 = new QSqlQuery(conn2.mydb);

    qry2->prepare("SELECT DISTINCT \"Time Stamp\" from Log");
    qry2->exec();

    while(qry2->next())
    {
        QDateTime myDate = QDateTime::fromString(qry2->value(0).toString(),"yyyy-MM-dd HH:mm:ss");
        if(firstRun)
            ui->dateTimeEdit_from->setDateTime(myDate);
        firstRun = false;
        ui->dateTimeEdit_to->setDateTime(myDate);
    }

    conn2.connClose();

    ui->comboBox_User->setCurrentIndex(0);
    ui->comboBox_Action->setCurrentIndex(0);
    ui->lineEdit_CatNum->clear();

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Log");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from Log");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_Log->setModel(model);
}
