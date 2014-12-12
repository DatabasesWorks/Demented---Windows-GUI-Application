#include "edit.h"
#include "ui_edit.h"
#include "database.h"
#include <QMessageBox>

Edit::Edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit)
{
    ui->setupUi(this);
}

void Edit :: Setup(objectInfo *passedObject, QString passedUser)
{
    object = passedObject;
    user = passedUser;

    if(object->type == "Patch" || object->type == "Embroided Patch" || object->type == "Back Patch")
    {
        ui->lineEdit_XS->setEnabled(false);
        ui->lineEdit_S->setEnabled(false);
        ui->lineEdit_M->setEnabled(false);
        ui->lineEdit_L->setEnabled(false);
        ui->lineEdit_XL->setEnabled(false);
        ui->lineEdit_XXL->setEnabled(false);
        ui->lineEdit_TQ->setEnabled(true);
    }

    ui->label_catNum->setText(object->catNum);
    ui->lineEdit_Type->setText(object->type);
    ui->lineEdit_Band->setText(object->band);
    ui->lineEdit_Album->setText(object->album);
    ui->lineEdit_Location->setText(object->location);
    ui->lineEdit_XS->setText(QString::number(object->XS));
    ui->lineEdit_S->setText(QString::number(object->S));
    ui->lineEdit_M->setText(QString::number(object->M));
    ui->lineEdit_L->setText(QString::number(object->L));
    ui->lineEdit_XL->setText(QString::number(object->XL));
    ui->lineEdit_XXL->setText(QString::number(object->XXL));
    ui->lineEdit_TQ->setText(QString::number(object->TQ));
    ui->lineEdit_Price->setText(QString::number(object->price));

}

Edit::~Edit()
{
    delete ui;
}

void Edit::on_lineEdit_XS_editingFinished()
{
    QString TQ = QString::number(ui->lineEdit_XS->text().toInt() + ui->lineEdit_S->text().toInt() + ui->lineEdit_M->text().toInt()
            + ui->lineEdit_L->text().toInt() + ui->lineEdit_XL->text().toInt() + ui->lineEdit_XXL->text().toInt());
    ui->lineEdit_TQ->setText(TQ);
}

void Edit::on_lineEdit_S_editingFinished()
{
    QString TQ = QString::number(ui->lineEdit_XS->text().toInt() + ui->lineEdit_S->text().toInt() + ui->lineEdit_M->text().toInt()
            + ui->lineEdit_L->text().toInt() + ui->lineEdit_XL->text().toInt() + ui->lineEdit_XXL->text().toInt());
    ui->lineEdit_TQ->setText(TQ);
}

void Edit::on_lineEdit_M_editingFinished()
{
    QString TQ = QString::number(ui->lineEdit_XS->text().toInt() + ui->lineEdit_S->text().toInt() + ui->lineEdit_M->text().toInt()
            + ui->lineEdit_L->text().toInt() + ui->lineEdit_XL->text().toInt() + ui->lineEdit_XXL->text().toInt());
    ui->lineEdit_TQ->setText(TQ);
}

void Edit::on_lineEdit_L_editingFinished()
{
    QString TQ = QString::number(ui->lineEdit_XS->text().toInt() + ui->lineEdit_S->text().toInt() + ui->lineEdit_M->text().toInt()
            + ui->lineEdit_L->text().toInt() + ui->lineEdit_XL->text().toInt() + ui->lineEdit_XXL->text().toInt());
    ui->lineEdit_TQ->setText(TQ);
}

void Edit::on_lineEdit_XL_editingFinished()
{
    QString TQ = QString::number(ui->lineEdit_XS->text().toInt() + ui->lineEdit_S->text().toInt() + ui->lineEdit_M->text().toInt()
            + ui->lineEdit_L->text().toInt() + ui->lineEdit_XL->text().toInt() + ui->lineEdit_XXL->text().toInt());
    ui->lineEdit_TQ->setText(TQ);
}

void Edit::on_lineEdit_XXL_editingFinished()
{
    QString TQ = QString::number(ui->lineEdit_XS->text().toInt() + ui->lineEdit_S->text().toInt() + ui->lineEdit_M->text().toInt()
            + ui->lineEdit_L->text().toInt() + ui->lineEdit_XL->text().toInt() + ui->lineEdit_XXL->text().toInt());
    ui->lineEdit_TQ->setText(TQ);
}

void Edit::on_pushButton_Update_clicked()
{
    QDateTime current = current.currentDateTime();
    QString timeStamp, action, notes, type, band, album, location;
    double amount;
    qint32 XS, S, M, L, XL, XXL, TQ, catNum;

    timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");
    action = "Edit";
    catNum = object->catNum.toInt();
    type = ui->lineEdit_Type->text();
    band = ui->lineEdit_Band->text();
    album = ui->lineEdit_Album->text();
    location = ui->lineEdit_Location->text();
    amount = ui->lineEdit_Price->text().toDouble();
    XS = ui->lineEdit_XS->text().toInt();
    S = ui->lineEdit_S->text().toInt();
    M = ui->lineEdit_M->text().toInt();
    L = ui->lineEdit_L->text().toInt();
    XL = ui->lineEdit_XL->text().toInt();
    XXL = ui->lineEdit_XXL->text().toInt();
    TQ = ui->lineEdit_TQ->text().toInt();

    QTextStream sstream(&notes);

    sstream << "Item was EDITED, Previous Description:\n"
            << "Type: " << object->type << "\n"
            << "Band: " << object->band << "\n"
            << "Album: " << object->album << "\n"
            << "Base Price: " << object->price << "\n"
            << "Location: " << object->location << "\n"
            << "XS(Quantity): " << object->XS << "\n"
            << "S(Quantity): " << object->S << "\n"
            << "M(Quantity): " << object->M << "\n"
            << "L(Quantity): " << object->L << "\n"
            << "XL(Quantity): " << object->XL << "\n";

    {
        Database conn;
        if(!conn.connOpen("Log"))
        {
            qDebug()<<"Failed to open Data";
            return;
        }

        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "INSERT INTO Log ('Time Stamp', 'User', 'Action', 'Catalog Number', 'XS(Quantity)'"
                    << ", 'S(Quantity)', 'M(Quantity)', 'L(Quantity)', 'XL(Quantity)', 'XXL(Quantity)', 'Total Quantity', 'Notes')"
                    << " VALUES ('"+timeStamp+"', '"+user+"', '"+action+"', "
                    << catNum << "," << XS << "," << S << "," << M << "," << L << "," << XL << "," << XXL << "," << TQ << ", '"+notes+"')";


        qry->prepare(queryString);

        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }

        conn.connClose();
    }
    {
        Database conn;
        if(!conn.connOpen("Inventory"))
        {
            qDebug()<<"Failed to open Data";
            return;
        }

        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "UPDATE Inventory SET Type='" << type << "', Band='" << band << "', Album='" << album
                    << "', Price='" << amount << "', Location='" << location << "', 'XS(Quantity)'='" << XS
                    << "', 'S(Quantity)'='" << S << "', 'M(Quantity)'='" << M << "', 'L(Quantity)'='" << L
                    << "', 'XL(Quantity)'='" << XL << "', 'XXL(Quantity)'='" << XXL << "', 'Total Quantity'='" << TQ
                    << "' WHERE Catalog_Number=" << catNum;


        qry->prepare(queryString);

        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }
        else
            QMessageBox::information(this, tr("Demented - Edit"), "Item Succesfully Updated");

        conn.connClose();
    }

    prevManager->on_pushButton_clicked_helper();
    this->hide();
}

void Edit::on_pushButton_cancel_clicked()
{
    this->hide();
}
