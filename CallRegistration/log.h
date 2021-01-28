#ifndef LOG_H
#define LOG_H
#include<QString>
#include <QMessageBox>

//журнал-лог для записи этапов программы
class Log
{
public:
    Log();
    static void SaveLog(QString textOne, QWidget *parent);
    static void SaveLog(QString textOne, QString textTwo, QWidget *parent);
    static void SaveLog(QString textOne, QString textTwo, QString textThree, QWidget *parent);
};

#endif // LOG_H
