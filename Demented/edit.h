#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include "objectinfo.h"
#include "manager.h"

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = 0);
    ~Edit();

    objectInfo *object;
    QString user;

    Manager *prevManager;

    void sendManager(Manager *temp)
    {
        prevManager = temp;
    }

    void Setup(objectInfo *passedObject, QString passedUser);

private slots:
    void on_lineEdit_XS_editingFinished();

    void on_lineEdit_S_editingFinished();

    void on_lineEdit_M_editingFinished();

    void on_lineEdit_L_editingFinished();

    void on_lineEdit_XL_editingFinished();

    void on_lineEdit_XXL_editingFinished();

    void on_pushButton_Update_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
