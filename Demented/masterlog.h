#ifndef MASTERLOG_H
#define MASTERLOG_H

#include <QMainWindow>

namespace Ui {
class MasterLog;
}

class MasterLog : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterLog(QWidget *parent = 0);
    ~MasterLog();

    QString currentUser;
    bool admin;

    void setup();
    void sendUsername(QString user, bool isAdmin)
    {
        currentUser = user;
        admin = isAdmin;
    }

private slots:
    void on_pushButton_Menu_clicked();

    void on_pushButton_Logout_clicked();

    void on_tableView_Log_doubleClicked(const QModelIndex &index);

    void on_pushButton_Search_clicked();

    void on_pushButton_Clear_clicked();

private:
    Ui::MasterLog *ui;
};

#endif // MASTERLOG_H
