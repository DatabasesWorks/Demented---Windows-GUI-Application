#include "logobject.h"
#include "ui_logobject.h"
#include "database.h"
#include "QMessageBox"

LogObject::LogObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogObject)
{
    ui->setupUi(this);
}

void LogObject :: setup()
{
    ui->label_catNum->setText(QString::number(CatNum));
    ui->label_timeStamp->setText(TimeStamp);
    ui->label_user->setText(User);
    ui->label_action->setText(Action);
    ui->label_amount->setText(QString::number(Amount));
    ui->label_XS->setText(QString::number(XS));
    ui->label_S->setText(QString::number(S));
    ui->label_M->setText(QString::number(M));
    ui->label_L->setText(QString::number(L));
    ui->label_XL->setText(QString::number(XL));
    ui->label_XXL->setText(QString::number(XXL));
    ui->label_TQ->setText(QString::number(TQ));
    ui->label_Notes->setText(Notes);

    Database conn;

    conn.connOpen("Inventory");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "SELECT * from Inventory WHERE Catalog_Number=" << CatNum;
    qry->prepare(queryString);
    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());

    }
    while(qry->next())
    {
        ui->label_type->setText(qry->value(0).toString());
        ui->label_band->setText(qry->value(1).toString());
        ui->label_album->setText(qry->value(2).toString());
        ui->label_basePrice->setText(qry->value(3).toString());
        ui->label_location->setText(qry->value(4).toString());
    }
    conn.connClose();
}

LogObject::~LogObject()
{
    delete ui;
}
