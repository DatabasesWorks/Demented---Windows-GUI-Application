#include "import.h"
#include "ui_import.h"
#include <QMessageBox>

Import::Import(QWidget *parent, QString currentUser) :
    QDialog(parent),
    ui(new Ui::Import)
{
    user = currentUser;
    ui->setupUi(this);
}

void Import :: setup(qint32 newCatNum)
{
    ui->label_catNum->setText(QString::number(newCatNum));
    ui->comboBox_Type->addItem("Select a Type");
    ui->comboBox_Type->addItem("Shirt");
    ui->comboBox_Type->addItem("Tank Top");
    ui->comboBox_Type->addItem("Long Sleeve");
    ui->comboBox_Type->addItem("Baseball T");
    ui->comboBox_Type->addItem("Hoodie");
    ui->comboBox_Type->addItem("Girl Shirt");
    ui->comboBox_Type->addItem("Onesie");
    ui->comboBox_Type->addItem("Cutup Shirt");
    ui->comboBox_Type->addItem("Patch");
    ui->comboBox_Type->addItem("Back Patch");
    ui->comboBox_Type->addItem("Embroided Patch");

    QModelIndex index = ui->comboBox_Type->model()->index(0, 0);
    QVariant v(0);
    ui->comboBox_Type->model()->setData(index, v, Qt::UserRole - 1);

    ui->spinBox_TQ->setEnabled(false);
}

Import::~Import()
{
    delete ui;
}


void Import::on_pushButton_import_clicked()
{
    QDateTime current = current.currentDateTime();
    QString timeStamp, action, notes, band, album, location, type;
    double price;
    qint32 XS, S, M, L, XL, XXL, TQ, catNum;

    timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");
    action = "Import";
    catNum = ui->label_catNum->text().toInt();
    price = ui->lineEdit_basePrice->text().toDouble();
    XS = ui->spinBox_XS->value();
    S = ui->spinBox_S->value();
    M = ui->spinBox_M->value();
    L = ui->spinBox_L->value();
    XL = ui->spinBox_XL->value();
    XXL = ui->spinBox_XXL->value();
    TQ = ui->spinBox_TQ->value();

    notes = ui->textEdit_Notes->toPlainText();
    band = ui->lineEdit_band->text();
    album = ui->lineEdit_album->text();
    location = ui->lineEdit_Location->text();
    type = ui->comboBox_Type->currentText();

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

        queryStream << "INSERT INTO Inventory (Type, Band, Album, Price, Location, \"XS(Quantity)\", "
                    << "\"S(Quantity)\", \"M(Quantity)\", \"L(Quantity)\", \"XL(Quantity)\", \"XXL(Quantity)\", \"Total Quantity\", Catalog_Number) "
                    << "values ('" << type << "', '" << band << "', '" << album << "', '" << price << "', '" << location <<  "', '" << XS << "', '"
                    << S << "', '" << M << "', '" << L << "', '" << XL << "', '" << XXL << "', '" << TQ << "', '" << catNum << "')";

        qry->prepare(queryString);
        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }

        conn.connClose();
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Database conn1;
    if(!conn1.connOpen("Log"))
    {
        qDebug()<<"Failed to open Data";
        return;
    }

    QSqlQuery * qry1 = new QSqlQuery(conn1.mydb);

    QString queryString1;
    QTextStream queryStream1(&queryString1);

    queryStream1 << "INSERT INTO Log ('Time Stamp', 'User', 'Action', 'Catalog Number', 'Amount', 'XS(Quantity)'"
                << ", 'S(Quantity)', 'M(Quantity)', 'L(Quantity)', 'XL(Quantity)', 'XXL(Quantity)', 'Total Quantity', 'Notes')"
                << " VALUES ('"+timeStamp+"', '"+user+"', '"+action+"', "
                << catNum << "," << price << "," << XS << "," << S << "," << M << "," << L << "," << XL << ","
                << XXL << "," << TQ << "," << "'"+notes+"'" << ")";
        /////FUCKED UP HERE

    qry1->prepare(queryString1);

    if(!qry1->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry1->lastError().text());
    }

    conn1.connClose();


    prevManager->incrementCatNum();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Demented - Import Success", "Would you like to add another item?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        this->hide();
        prevManager->on_pushButton_import_clicked_helper();
    }
    else
        prevManager->on_pushButton_clicked_helper();
        this->hide();
}

void Import::on_spinBox_XS_valueChanged(int arg1)
{
    qint32 total;
    qint32 s = ui->spinBox_S->value();
    qint32 m = ui->spinBox_M->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_XXL->value();

    total = arg1 + s + m + l + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void Import::on_spinBox_S_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 m = ui->spinBox_M->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_XXL->value();

    total = arg1 + xs + m + l + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void Import::on_spinBox_M_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 s = ui->spinBox_S->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_XXL->value();

    total = arg1 + xs + s + l + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void Import::on_spinBox_L_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 s = ui->spinBox_S->value();
    qint32 m = ui->spinBox_M->value();
    qint32 xl = ui->spinBox_XL->value();
    qint32 xxl = ui->spinBox_XXL->value();

    total = arg1 + xs + s + m + xl + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void Import::on_spinBox_XL_valueChanged(int arg1)
{
    qint32 total;
    qint32 xs = ui->spinBox_XS->value();
    qint32 s = ui->spinBox_S->value();
    qint32 m = ui->spinBox_M->value();
    qint32 l = ui->spinBox_L->value();
    qint32 xxl = ui->spinBox_XXL->value();

    total = arg1 + xs + s + m + l + xxl;

    ui->spinBox_TQ->setRange(total, total);
}

void Import::on_spinBox_XXL_valueChanged(int arg1)
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

void Import::on_comboBox_Type_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "Shirt")
    {
        ui->lineEdit_basePrice->setText("18");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Tank Top")
    {
        ui->lineEdit_basePrice->setText("17");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Girl Shirt")
    {
        ui->lineEdit_basePrice->setText("16");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Onesie")
    {
        ui->lineEdit_basePrice->setText("16");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Cutup Shirt")
    {
        ui->lineEdit_basePrice->setText("25");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Hoodie")
    {
        ui->lineEdit_basePrice->setText("35");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Long Sleeve")
    {
        ui->lineEdit_basePrice->setText("25");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Baseball T")
    {
        ui->lineEdit_basePrice->setText("20");
        ui->spinBox_XS->setEnabled(true);
        ui->spinBox_S->setEnabled(true);
        ui->spinBox_M->setEnabled(true);
        ui->spinBox_L->setEnabled(true);
        ui->spinBox_XL->setEnabled(true);
        ui->spinBox_XXL->setEnabled(true);
        ui->spinBox_TQ->setEnabled(false);
    }
    else if(arg1 == "Back Patch")
    {
        ui->lineEdit_basePrice->setText("13");
        ui->spinBox_XS->setEnabled(false);
        ui->spinBox_S->setEnabled(false);
        ui->spinBox_M->setEnabled(false);
        ui->spinBox_L->setEnabled(false);
        ui->spinBox_XL->setEnabled(false);
        ui->spinBox_XXL->setEnabled(false);
        ui->spinBox_TQ->setEnabled(true);
    }
    else if(arg1 == "Embroided Patch")
    {
        ui->lineEdit_basePrice->setText("6");
        ui->spinBox_XS->setEnabled(false);
        ui->spinBox_S->setEnabled(false);
        ui->spinBox_M->setEnabled(false);
        ui->spinBox_L->setEnabled(false);
        ui->spinBox_XL->setEnabled(false);
        ui->spinBox_XXL->setEnabled(false);
        ui->spinBox_TQ->setEnabled(true);
    }
    else if(arg1 == "Patch")
    {
        ui->lineEdit_basePrice->setText("4");
        ui->spinBox_XS->setEnabled(false);
        ui->spinBox_S->setEnabled(false);
        ui->spinBox_M->setEnabled(false);
        ui->spinBox_L->setEnabled(false);
        ui->spinBox_XL->setEnabled(false);
        ui->spinBox_XXL->setEnabled(false);
        ui->spinBox_TQ->setEnabled(true);
    }
}

void Import::on_lineEdit_band_editingFinished()
{
    if(ui->lineEdit_band->text().left(3) == "The" || ui->lineEdit_band->text().left(3) == "the")
        ui->lineEdit_Location->setText(ui->lineEdit_band->text().mid(4,1));
    else
        ui->lineEdit_Location->setText(ui->lineEdit_band->text().left(1));
}

void Import::on_pushButton_cancel_clicked()
{
    this->hide();
}
