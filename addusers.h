#ifndef ADDUSERS_H
#define ADDUSERS_H

#include <QDialog>

namespace Ui {
class AddUsers;
}

class AddUsers : public QDialog
{
    Q_OBJECT

public:
    explicit AddUsers(QWidget *parent = 0);
    ~AddUsers();

private slots:
    void on_checkBox_toggled(bool checked);

    void on_pushButton_Save_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::AddUsers *ui;
};

#endif // ADDUSERS_H
