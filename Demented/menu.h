#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include "manager.h"

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:

    QString name;
    bool admin;

    explicit menu(QWidget *parent = 0, QString name = "", bool isAdmin = false);
    ~menu();

private slots:
    void on_pushButton_Inventory_clicked();

    void on_pushButton_Logout_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H
