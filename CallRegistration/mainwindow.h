#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "log.h"
#include "account.h"
#include "dbconnect.h"
#include "checkpasswordadmin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //указатель на форму пользователя, которая будет открываться из данного окна
    Account *account;
    //указатель на форму проверки пароля администратора
    CheckPasswordAdmin *checkPasswordAdmin;
private slots:
    //закрыть текущее окно
    void on_pushButton_close_clicked();
    //очистка введенных данных логина и пароля
    void on_pushButton_clear_clicked();
    //восстановление пользователя или пароля
    void on_pushButton_recover_clicked();
    //переход на поле с логином и паролем назад
    void on_pushButton_back_clicked();
    //авторизация пользователя-ввод логина и пароля и вход в окно пользователя
    void on_pushButton_authorization_clicked();
    //регистрация нового пользователя
    void on_pushButton_registration_user_clicked();

    void on_pushButton_back_2_clicked();
    //регистрация пользователя после ввода информации
    void on_pushButton_registration_clicked();
    //очистить информацию о регистрируемом пользователе
    void on_pushButton_clear_2_clicked();

private:
    Ui::MainWindow *ui;
    //переключение через Tab
    void TabSwitching();
};
#endif // MAINWINDOW_H
