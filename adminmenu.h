#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QDialog>
#include "manager.h"


namespace Ui {
class AdminMenu;
}

class AdminMenu : public QDialog
{
    Q_OBJECT

public:
    explicit AdminMenu(QWidget *parent = 0, QString userPassed = "", bool isAdmin = false);

    QString name;
    bool admin;
    ~AdminMenu();

private slots:
    void on_pushButton_Inventory_clicked();

    void on_pushButton_Log_clicked();

    void on_pushButton_users_clicked();

    void on_pushButton_Logout_clicked();

private:
    Ui::AdminMenu *ui;
};

#endif // ADMINMENU_H
