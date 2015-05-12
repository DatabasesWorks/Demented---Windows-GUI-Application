#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>

namespace Ui {
class EditUser;
}

class EditUser : public QDialog
{
    Q_OBJECT

public:
    explicit EditUser(QWidget *parent = 0, qint32 id = 0);

    qint32 userID;
    ~EditUser();

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Save_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::EditUser *ui;
};

#endif // EDITUSER_H
