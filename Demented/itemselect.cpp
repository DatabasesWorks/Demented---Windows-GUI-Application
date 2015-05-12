#include "itemselect.h"
#include "ui_itemselect.h"
#include "edit.h"
#include "database.h"
#include <QtMath>
#include <qmath.h>
#include <math.h>
#include <QDateTime>
#include <QMessageBox>

itemSelect::itemSelect(QWidget *parent, QString currentUser) :
    QDialog(parent),
    ui(new Ui::itemSelect)
{
    user = currentUser;
    ui->setupUi(this);
}

void itemSelect :: setup()
{
    ui->label_type->setText(object->type);
    ui->label_band->setText(object->band);
    ui->label_album->setText(object->album);
    ui->label_location->setText(object->location);
    ui->label_catNum->setText(object->catNum);
    ui->label_price->setNum(object->price);
    ui->label_XS->setNum(object->XS);
    ui->label_S->setNum(object->S);
    ui->label_M->setNum(object->M);
    ui->label_L->setNum(object->L);
    ui->label_XL->setNum(object->XL);
    ui->label_xxl->setNum(object->XXL);
    ui->label_TQ->setNum(object->TQ);
    ui->lineEdit_Total->setText("0.00");

    ui->spinBox_XS->setMaximum(object->XS);
    ui->spinBox_S->setMaximum(object->S);
    ui->spinBox_M->setMaximum(object->M);
    ui->spinBox_L->setMaximum(object->L);
    ui->spinBox_XL->setMaximum(object->XL);
    ui->spinBox_xxl->setMaximum(object->XXL);
    ui->spinBox_TQ->setMaximum(object->TQ);

    bool isClothes = false;

    if(object->XS == 0)
        ui->spinBox_XS->setEnabled(false);
    else
        isClothes = true;

    if(object->S == 0)
        ui->spinBox_S->setEnabled(false);
    else
        isClothes = true;

    if(object->M == 0)
        ui->spinBox_M->setEnabled(false);
    else
        isClothes = true;

    if(object->L == 0)
        ui->spinBox_L->setEnabled(false);
    else
        isClothes = true;

    if(object->XL == 0)
        ui->spinBox_XL->setEnabled(false);
    else
        isClothes = true;

    if(object->XXL == 0)
        ui->spinBox_xxl->setEnabled(false);
    else
        isClothes = true;

    if(isClothes)
        ui->spinBox_TQ->setEnabled(false);
}

itemSelect::~itemSelect()
{
    delete ui;
}

void itemSelect::on_spinBox_TQ_valueChanged(int arg1)
{
    double_t converted = arg1;

    double_t total = converted * object->price;

    if(ui->checkBox_tax->isChecked())
        total = (total * .095) + total;

    QString total_Str = QString::number(total, 'f', 2);

    ui->lineEdit_Total->setText(total_Str);
}

void itemSelect::on_spinBox_XS_valueChanged(int arg1)
{
    qint32 total;
    qint32 s = ui->spinBox_S->value();
    qint32 m = ui->spinBox_M->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_xxl->value();

    total = arg1 + s + m + l + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void itemSelect::on_spinBox_S_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 m = ui->spinBox_M->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_xxl->value();

    total = arg1 + xs + m + l + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void itemSelect::on_spinBox_M_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 s = ui->spinBox_S->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_xxl->value();

    total = arg1 + xs + s + l + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void itemSelect::on_spinBox_L_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 s = ui->spinBox_S->value();
    qint32 m = ui->spinBox_M->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_xxl->value();

    total = arg1 + xs + s + m + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void itemSelect::on_spinBox_XL_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 s = ui->spinBox_S->value();
    qint32 m = ui->spinBox_M->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xxl = ui->spinBox_xxl->value();

    total = arg1 + xs + s + m + l + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void itemSelect::on_spinBox_xxl_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 s = ui->spinBox_S->value();
    qint32 m = ui->spinBox_M->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xl = ui->spinBox_XL->value();

    total = arg1 + xs + s + m + l + xl;

    ui->spinBox_TQ->setRange(total, total);
}

void itemSelect::on_checkBox_tax_toggled(bool checked)
{
    double_t converted = ui->spinBox_TQ->value();

    double_t total = converted * object->price;
    if(checked)
        total = (total * .095) + total;

    QString total_Str = QString::number(total, 'f', 2);

    ui->lineEdit_Total->setText(total_Str);
}

void itemSelect::on_pushButton_clicked()
{
    ui->spinBox_XS->setValue(0);
    ui->spinBox_S->setValue(0);
    ui->spinBox_M->setValue(0);
    ui->spinBox_L->setValue(0);
    ui->spinBox_XL->setValue(0);
    ui->spinBox_xxl->setValue(0);
    ui->spinBox_TQ->setValue(0);
    ui->lineEdit_Total->setText("0.00");
    ui->checkBox_tax->setChecked(false);
}

void itemSelect::on_commandLinkButton_Go_clicked()
{
    QDateTime current = current.currentDateTime();
    QString timeStamp, action, notes;
    double amount;
    qint32 XS, S, M, L, XL, XXL, TQ, catNum;

    timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");
    action = "Sell";
    catNum = object->catNum.toInt();
    amount = ui->lineEdit_Total->text().toDouble();
    XS = ui->spinBox_XS->value();
    S = ui->spinBox_S->value();
    M = ui->spinBox_M->value();
    L = ui->spinBox_L->value();
    XL = ui->spinBox_XL->value();
    XXL = ui->spinBox_xxl->value();
    TQ = ui->spinBox_TQ->value();
    notes = ui->textEdit_Notes->toPlainText();


    Database conn;
    if(!conn.connOpen("Log"))
    {
        qDebug()<<"Failed to open Data";
        return;
    }

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO Log ('Time Stamp', 'User', 'Action', 'Catalog Number', 'Amount', 'XS(Quantity)'"
                << ", 'S(Quantity)', 'M(Quantity)', 'L(Quantity)', 'XL(Quantity)', 'XXL(Quantity)', 'Total Quantity', 'Notes')"
                << " VALUES ('"+timeStamp+"', '"+user+"', '"+action+"', "
                << catNum << "," << amount << "," << XS << "," << S << "," << M << "," << L << "," << XL << "," << XXL << "," << TQ << "," << "'"+notes+"'" << ")";


    qry->prepare(queryString);

    if(qry->exec())
    {
        QMessageBox::information(this, tr("Transaction"), "Transaction Complete!");

    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }

    conn.connClose();

    qint32 newXS, newS, newM, newL, newXL, newXXL, newTQ;


    newXS = object->XS - XS;
    newS = object->S - S;
    newM = object->M - M;
    newL = object->L - L;
    newXL = object->XL;
    newXXL = object->XXL - XXL;
    newTQ = object->TQ - TQ;

    this->hide();

    Database conn1;
    if(!conn1.connOpen("Inventory"))
    {
        qDebug()<<"Failed to open Data";
        return;
    }

    QSqlQuery * qry1 = new QSqlQuery(conn1.mydb);

    QString queryString1;
    QTextStream queryStream1(&queryString1);


    queryStream1 << "UPDATE Inventory SET 'XS(Quantity)'='" << newXS << "'" << ", 'S(Quantity)'='" << newS << "'"
                 << ", 'M(Quantity)'='" << newM << "', 'L(Quantity)'='" << newL << "'"
                 << ", 'XL(Quantity)'='" << newXL << "', 'XXL(Quantity)'='" << newXXL << "', 'Total Quantity'='" << newTQ << "'"
                 << " WHERE " << "Catalog_Number='" << catNum << "';";


    qry1->prepare(queryString1);

    if(!qry1->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry1->lastError().text());
    }

    conn1.connClose();

    prevManager->on_pushButton_clicked_helper();
}


void itemSelect::on_pushButton_Delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Demented - Delete",
                                  "Are you sure you want to DELETE this item from your inventory?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
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

            queryStream << "DELETE FROM Inventory WHERE \"Catalog_Number\"='" << ui->label_catNum->text() << "'";

            qry->prepare(queryString);

            if(qry->exec())
            {
                QMessageBox::information(this, tr("Demented - Delete"), "Item Deleted");
            }
            else
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }

            conn.connClose();
        }
        {
            QDateTime current = current.currentDateTime();
            QString timeStamp, action, notes;
            double amount;
            qint32 XS, S, M, L, XL, XXL, TQ, catNum;

            timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");
            action = "Delete";
            catNum = object->catNum.toInt();
            amount = ui->lineEdit_Total->text().toDouble();
            XS = ui->spinBox_XS->value();
            S = ui->spinBox_S->value();
            M = ui->spinBox_M->value();
            L = ui->spinBox_L->value();
            XL = ui->spinBox_XL->value();
            XXL = ui->spinBox_xxl->value();
            TQ = ui->spinBox_TQ->value();

            QTextStream sstream(&notes);

            sstream << "Item is Deleted, Previous Description:\n"
                    << "Type: " << ui->label_type->text() << "\n"
                    << "Band: " << ui->label_band->text() << "\n"
                    << "Album: " << ui->label_album->text() << "\n"
                    << "Base Price: " << ui->label_price->text() << "\n"
                    << "Location: " << ui->label_location->text() << "\n";

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

        prevManager->on_pushButton_clicked_helper();
        this->hide();
    }

}

void itemSelect::on_pushButton_Edit_clicked()
{
    Edit *edit = new Edit();

    this->hide();
    edit->sendManager(prevManager);
    edit->Setup(object, user);
    edit->show();
}
