#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDate>
#include <QTime>

#include "log.h"

void Log::SaveLog(QString textOne)
{
    QDate cdate = QDate::currentDate(); // возвращаем текущую дату
    QTime ctime = QTime::currentTime(); // возвращаем текущее время

    QFile fileLog("log.txt");
    if (fileLog.open(QIODevice::Append)) {
        QTextStream outFile(&fileLog);
        outFile <<cdate.toString() + " "+ ctime.toString()+ " - " + textOne << Qt::endl;
    } else {
        //QMessageBox::critical(parent, "Ошибка лога","Проверьте правильность записи лога");
    }
}

void Log::SaveLog(QString textOne, QWidget *parent)
{
    QDate cdate = QDate::currentDate(); // возвращаем текущую дату
    QTime ctime = QTime::currentTime(); // возвращаем текущее время

    QFile fileLog("log.txt");
    if (fileLog.open(QIODevice::Append)) {
        QTextStream outFile(&fileLog);
        outFile <<cdate.toString() + " "+ ctime.toString()+ " - " + textOne << Qt::endl;
    } else {
        QMessageBox::critical(parent, "Ошибка лога","Проверьте правильность записи лога");
    }
}

void Log:: SaveLog(QString textOne, QString textTwo, QWidget *parent)
{
     QDate cdate = QDate::currentDate(); // возвращаем текущую дату
     QTime ctime = QTime::currentTime(); // возвращаем текущее время

     QFile fileLog("log.txt");
     if (fileLog.open(QIODevice::Append)) {
         QTextStream outFile(&fileLog);
         outFile <<cdate.toString() + " "+ ctime.toString()+ " - " + textOne + " "+ textTwo << Qt::endl;
     } else {
        QMessageBox::critical(parent, "Ошибка лога","Проверьте правильность записи лога");
     }
}

void Log:: SaveLog(QString textOne, QString textTwo, QString textThree, QWidget *parent)
{
    QDate cdate = QDate::currentDate(); // возвращаем текущую дату
    QTime ctime = QTime::currentTime(); // возвращаем текущее время

    QFile fileLog("log.txt");
    if (fileLog.open(QIODevice::Append)) {
        QTextStream outFile(&fileLog);
        outFile <<cdate.toString() + " "+ ctime.toString()+ " - " + textOne + " "+ textTwo + " "+ textThree<< Qt::endl;
    } else {
        QMessageBox::critical(parent, "Ошибка лога","Проверьте правильность записи лога");
    }
}
