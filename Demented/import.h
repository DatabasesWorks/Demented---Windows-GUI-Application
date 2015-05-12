#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>
#include "manager.h"
#include "objectinfo.h"
#include <QDebug>

namespace Ui {
class Import;
}

class Import : public QDialog
{
    Q_OBJECT

public:
    explicit Import(QWidget *parent = 0, QString currentUser = "");
    ~Import();

    void setup(qint32 newCatNum);
    QString user;
    Manager *prevManager;

    void sendManager(Manager *temp)
    {
        prevManager = temp;
    }

private slots:

    void on_pushButton_import_clicked();

    void on_spinBox_XS_valueChanged(int arg1);

    void on_spinBox_S_valueChanged(int arg1);

    void on_spinBox_M_valueChanged(int arg1);

    void on_spinBox_L_valueChanged(int arg1);

    void on_spinBox_XL_valueChanged(int arg1);

    void on_spinBox_XXL_valueChanged(int arg1);

    void on_comboBox_Type_currentIndexChanged(const QString &arg1);

    void on_lineEdit_band_editingFinished();

    void on_pushButton_cancel_clicked();

private:
    Ui::Import *ui;
};

#endif // IMPORT_H
