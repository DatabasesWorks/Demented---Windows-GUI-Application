#ifndef ITEMSELECT_H
#define ITEMSELECT_H

#include <QDialog>
#include "objectinfo.h"
#include "manager.h"
#include <QDebug>

namespace Ui {
class itemSelect;
}

class itemSelect : public QDialog
{
    Q_OBJECT

public:
    explicit itemSelect(QWidget *parent = 0, QString currentUser = "");

    objectInfo *object;
    QString user;
    Manager *prevManager;

    void sendManager(Manager *temp)
    {
        prevManager = temp;
    }

    void sendObject(objectInfo *objectPassed)
    {
        object = objectPassed;
    }

    void setup();

    ~itemSelect();

private slots:
    void on_spinBox_TQ_valueChanged(int arg1);

    void on_spinBox_XS_valueChanged(int arg1);

    void on_spinBox_S_valueChanged(int arg1);

    void on_spinBox_M_valueChanged(int arg1);

    void on_spinBox_L_valueChanged(int arg1);

    void on_spinBox_XL_valueChanged(int arg1);

    void on_spinBox_xxl_valueChanged(int arg1);

    void on_checkBox_tax_toggled(bool checked);

    void on_pushButton_clicked();

    void on_commandLinkButton_Go_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Edit_clicked();

private:
    Ui::itemSelect *ui;
};

#endif // ITEMSELECT_H
