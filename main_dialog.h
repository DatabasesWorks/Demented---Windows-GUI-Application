#ifndef MAIN_DIALOG_H
#define MAIN_DIALOG_H

#include <QDialog>

namespace Ui {
class Main_Dialog;
}

class Main_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Main_Dialog(QWidget *parent = 0);
    ~Main_Dialog();

private:
    Ui::Main_Dialog *ui;
};

#endif // MAIN_DIALOG_H
