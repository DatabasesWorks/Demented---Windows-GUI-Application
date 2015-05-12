#ifndef LOGOBJECT_H
#define LOGOBJECT_H

#include <QDialog>

namespace Ui {
class LogObject;
}

class LogObject : public QDialog
{
    Q_OBJECT

public:
    explicit LogObject(QWidget *parent = 0);
    ~LogObject();

    QString TimeStamp;
    QString User;
    QString Action;
    qint32 CatNum;
    double Amount;
    qint32 XS;
    qint32 S;
    qint32 M;
    qint32 L;
    qint32 XL;
    qint32 XXL;
    qint32 TQ;
    QString Notes;

    void setup();
    void sendLogObject(QString tempTimeStamp, QString tempUser, QString tempAction, qint32 tempCatNum, double tempAmount,
                     qint32 tempXS, qint32 tempS, qint32 tempM, qint32 tempL, qint32 tempXL, qint32 tempXXL, qint32 tempTQ, QString tempNotes)
    {
        TimeStamp = tempTimeStamp;
        User = tempUser;
        Action = tempAction;
        CatNum = tempCatNum;
        Amount = tempAmount;
        XS = tempXS;
        S = tempS;
        M = tempM;
        L = tempL;
        XL = tempXL;
        XXL = tempXXL;
        TQ = tempTQ;
        Notes = tempNotes;
    }

private:
    Ui::LogObject *ui;


};

#endif // LOGOBJECT_H
