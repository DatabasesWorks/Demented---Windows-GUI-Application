#include "manager.h"
#include "ui_manager.h"
#include "login.h"
#include "itemselect.h"
#include "objectinfo.h"
#include "import.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QGraphicsOpacityEffect>

Manager::Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);

    progressBar = new QProgressBar(ui->statusbar);
    progressBar->setMaximumSize(250,40);
    ui->statusbar->addPermanentWidget(progressBar);

    setTabOrder(ui->lineEdit_band_name, ui->lineEdit_Album);
    setTabOrder(ui->lineEdit_Album, ui->lineEdit_price_min);
    setTabOrder(ui->lineEdit_price_min, ui->lineEdit_price_max);

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Inventory");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from Inventory");
    qry->exec();
    while(qry->next())
    {
        newCatNum = qry->value(12).toInt();
    }
    ++newCatNum;

    model->setQuery(*qry);
    ui->tableView_Master->setModel(model);

    Database conn1;

    conn1.connOpen("Inventory");
    QSqlQuery * qry1 = new QSqlQuery(conn1.mydb);

    ui->comboBox_Type->addItem("Select a Type");

    qry1->prepare("SELECT DISTINCT Type from Inventory");
    qry1->exec();
    while(qry1->next())
    {
        ui->comboBox_Type->addItem(qry1->value(0).toString());
    }

    QModelIndex index = ui->comboBox_Type->model()->index(0, 0);
    QVariant v(0);
    ui->comboBox_Type->model()->setData(index, v, Qt::UserRole - 1);

    conn.connClose();
    conn1.connClose();

    qDebug() << (model->rowCount());
}

void Manager :: setup()
{
    ui->label_Welcome->setText("<b><font size=\"4\">Welcome, " + currentUser + "</font></b>");
}

Manager::~Manager()
{
    delete ui;
}

void Manager::on_pushButton_clicked()
{
    progressBar->setValue(0);
    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Inventory");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);


    QString Band_Name = ui->lineEdit_band_name->text();
    QString Album = ui->lineEdit_Album->text();
    QString Type = ui->comboBox_Type->currentText();
    qint32 minPrice = 0;
    if(!ui->lineEdit_price_min->text().isEmpty())
        minPrice = ui->lineEdit_price_min->text().toInt();
    qint32 maxPrice = 99999;
    progressBar->setValue(25);
    if(!ui->lineEdit_price_max->text().isEmpty())
        maxPrice = ui->lineEdit_price_max->text().toInt();

    if(Type == "Select a Type")
        Type = "";

    qint32 xs_int = 999;
    qint32 s_int = 999;
    qint32 m_int = 999;
    qint32 l_int = 999;
    qint32 xl_int = 999;
    qint32 xxl_int = 999;
    progressBar->setValue(50);
    if(!ui->checkBox_XS->isChecked() && !ui->checkBox_S->isChecked() && !ui->checkBox_M->isChecked() &&
            !ui->checkBox_L->isChecked() && !ui->checkBox_XL->isChecked() && !ui->checkBox_xxl->isChecked())
    {
        QString queryString;
        QTextStream queryStream(&queryString);
        queryStream
                << "SELECT * FROM Inventory WHERE \"Price\" >= '"
                << minPrice << "' AND \"Price\" <= '"
                << maxPrice << "' AND Band LIKE '%"+Band_Name+"%' AND Album LIKE '%"+Album+"%' AND Type LIKE '"+Type+"%'";
        qry->prepare(queryString);
    }
    else
    {
        if(ui->checkBox_XS->isChecked())
            xs_int = 0;
        if(ui->checkBox_S->isChecked())
            s_int = 0;
        if(ui->checkBox_M->isChecked())
            m_int = 0;
        if(ui->checkBox_L->isChecked())
            l_int = 0;
        if(ui->checkBox_XL->isChecked())
            xl_int = 0;
        if(ui->checkBox_xxl->isChecked())
            xxl_int = 0;

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream
                << "SELECT * FROM Inventory WHERE \"XS(Quantity)\" > '"
                   << xs_int << "' AND \"Price\" >= '"
                   << minPrice << "' AND \"Price\" <= '"
                   << maxPrice << "' AND Band LIKE '%" << Band_Name << "%' AND Album LIKE '%"+Album+"%' AND Type LIKE '"+Type+"%' OR \"S(Quantity)\" > '"
                   << s_int << "' AND \"Price\" >= '"
                   << minPrice << "' AND \"Price\" <= '"
                   << maxPrice << "' AND Band LIKE '%" << Band_Name << "%' AND Album LIKE '%"+Album+"%' AND Type LIKE '"+Type+"%' OR \"M(Quantity)\" > '"
                   << m_int << "' AND \"Price\" >= '"
                   << minPrice << "' AND \"Price\" <= '"
                   << maxPrice << "' AND Band LIKE '%" << Band_Name << "%' AND Album LIKE '%"+Album+"%' AND Type LIKE '"+Type+"%' OR \"L(Quantity)\" > '"
                   << l_int << "' AND \"Price\" >= '"
                   << minPrice << "' AND \"Price\" <= '"
                   << maxPrice << "' AND Band LIKE '%" << Band_Name << "%' AND Album LIKE '%"+Album+"%' AND Type LIKE '"+Type+"%' OR \"XL(Quantity)\" > '"
                   << xl_int << "' AND \"Price\" >= '"
                   << minPrice << "' AND \"Price\" <= '"
                   << maxPrice << "' AND Band LIKE '%" << Band_Name << "%' AND Album LIKE '%"+Album+"%' AND Type LIKE '"+Type+"%' OR \"XXL(Quantity)\" > '"
                   << xxl_int << "' AND \"Price\" >= '"
                   << minPrice << "' AND \"Price\" <= '"
                   << maxPrice << "' AND Band LIKE '%" << Band_Name << "%' AND Album LIKE '%"+Album+"%' AND Type LIKE '"+Type+"%'";
        qry->prepare(queryString);

    }
    progressBar->setValue(75);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    model->setQuery(*qry);
    ui->tableView_Master->setModel(model);

    qint32 i = (model->rowCount());
    QString str;

    str.append(QString("%1").arg(i));
    progressBar->setValue(100);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
         opacityEffect->setOpacity(1.0);
         ui->statusbar->setGraphicsEffect(opacityEffect);
         QPropertyAnimation* anim = new QPropertyAnimation(this);
         anim->setTargetObject(opacityEffect);
         anim->setPropertyName("opacity");
         anim->setDuration(4000);
         anim->setStartValue(opacityEffect->opacity());
         anim->setEndValue(0);
         anim->setEasingCurve(QEasingCurve::OutQuad);
         anim->start(QAbstractAnimation::DeleteWhenStopped);


    ui->label_results->setText(str + " Results Found!");

}

void Manager::on_pushButton_Clear_clicked()
{
    //Clearing Text Fields
    progressBar->setValue(0);

    ui->lineEdit_Album->clear();
    ui->lineEdit_band_name->clear();
    ui->lineEdit_price_max->clear();
    ui->lineEdit_price_min->clear();
    ui->label_results->clear();

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Inventory");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);
    progressBar->setValue(25);
    qry->prepare("SELECT * FROM Inventory");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_Master->setModel(model);

    ui->comboBox_Type->setCurrentIndex(0);
    progressBar->setValue(50);
    ui->checkBox_XS->setChecked(false);
    ui->checkBox_S->setChecked(false);
    ui->checkBox_M->setChecked(false);
    progressBar->setValue(75);
    ui->checkBox_L->setChecked(false);
    ui->checkBox_XL->setChecked(false);
    ui->checkBox_xxl->setChecked(false);
    progressBar->setValue(100);

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
         opacityEffect->setOpacity(1.0);
         ui->statusbar->setGraphicsEffect(opacityEffect);
         QPropertyAnimation* anim = new QPropertyAnimation(this);
         anim->setTargetObject(opacityEffect);
         anim->setPropertyName("opacity");
         anim->setDuration(4000);
         anim->setStartValue(opacityEffect->opacity());
         anim->setEndValue(0);
         anim->setEasingCurve(QEasingCurve::OutQuad);
         anim->start(QAbstractAnimation::DeleteWhenStopped);
    qDebug() << (model->rowCount());

}


void Manager::on_pushButton_logout_clicked()
{
    this->hide();
    Login *login = new Login();
    login->show();
    return;
}

void Manager::on_tableView_Master_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    itemSelect *item = new itemSelect(0, currentUser);

    QString tempType = index.sibling(row, 0).data(Qt::DisplayRole).toString();
    QString tempBand = index.sibling(row, 1).data(Qt::DisplayRole).toString();
    QString tempAlbum = index.sibling(row, 2).data(Qt::DisplayRole).toString();
    double_t tempPrice = index.sibling(row, 3).data(Qt::DisplayRole).toDouble();
    QString tempLocation = index.sibling(row, 4).data(Qt::DisplayRole).toString();
    qint32 tempXS = index.sibling(row, 5).data(Qt::DisplayRole).toInt();
    qint32 tempS = index.sibling(row, 6).data(Qt::DisplayRole).toInt();
    qint32 tempM = index.sibling(row, 7).data(Qt::DisplayRole).toInt();
    qint32 tempL = index.sibling(row, 8).data(Qt::DisplayRole).toInt();
    qint32 tempXL = index.sibling(row, 9).data(Qt::DisplayRole).toInt();
    QString tempCatNum = index.sibling(row, 12).data(Qt::DisplayRole).toString();
    qint32 tempTQ = index.sibling(row, 11).data(Qt::DisplayRole).toInt();
    qint32 tempXXL = index.sibling(row, 10).data(Qt::DisplayRole).toInt();

    objectInfo *object = new objectInfo(tempType, tempBand, tempAlbum, tempPrice,
                                        tempLocation, tempXS, tempS, tempM, tempL,
                                        tempXL, tempXXL, tempCatNum, tempTQ);

    item->sendObject(object);
    item->sendManager(this);
    item->setup();
    item->show();

}


void Manager::on_pushButton_Menu_clicked()
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

void Manager::on_pushButton_import_clicked()
{
    Import *import = new Import(0, currentUser);
    import->setup(newCatNum);
    import->sendManager(this);
    import->show();
}

void Manager :: incrementCatNum()
{
    ++newCatNum;
}
