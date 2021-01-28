#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    Log::SaveLog("Запуск программы", this);    //запись лога
}

MainWindow::~MainWindow()
{
    delete ui;
}

