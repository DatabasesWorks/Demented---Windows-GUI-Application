#ifndef MANAGEUSER_H
#define MANAGEUSER_H

#include <QDialog>

namespace Ui {
class ManageUser;
}

class ManageUser : public QDialog
{
    Q_OBJECT

public:
    explicit ManageUser(QWidget *parent = 0);

    qint32 id;
    ~ManageUser();

private slots:

    void on_tableView_users_clicked(const QModelIndex &index);

    void on_pushButton_Edit_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_Delete_clicked();

private:
    Ui::ManageUser *ui;
};

#endif // MANAGEUSER_H
