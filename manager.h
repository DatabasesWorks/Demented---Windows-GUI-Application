#ifndef MANAGER_H
#define MANAGER_H

#include <QMainWindow>
#include "database.h"
#include "login.h"
#include "menu.h"
#include "adminmenu.h"
#include <QProgressBar>



namespace Ui {
class Manager;
}

class Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();

    QString currentUser;
    bool admin;
    QProgressBar *progressBar;
    qint32 newCatNum = 1000;

    void sendUsername(QString user, bool isAdmin)
    {
        currentUser = user;
        admin = isAdmin;
    }
    void on_pushButton_clicked_helper()
    {
        on_pushButton_clicked();
    }

    void on_pushButton_import_clicked_helper()
    {
        on_pushButton_import_clicked();
    }

    void setup();

    void incrementCatNum();

private slots:
    void on_pushButton_Clear_clicked();

    void on_pushButton_logout_clicked();

    void on_tableView_Master_doubleClicked(const QModelIndex &index);

    void on_pushButton_Menu_clicked();

    void on_pushButton_clicked();

    void on_pushButton_import_clicked();

private:
    Ui::Manager *ui;
};

#endif // MANAGER_H


