#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    Log::SaveLog("Запуск программы", this);    //запись лога
    //по умолчанию первый индекс (c полем логина и пароля)
    ui->stackedWidget->setCurrentIndex(0);
    //переключение полей через TAB
    TabSwitching();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TabSwitching() {
    //курсор по умолчанию
    ui->name->setFocus();
    setTabOrder(ui->name, ui->position);
    setTabOrder(ui->position, ui->departament);
    setTabOrder(ui->departament, ui->email);
    setTabOrder(ui->email, ui->password);
    setTabOrder(ui->password, ui->repeate_password);
    setTabOrder(ui->repeate_password, ui->radioButton_admin);
    setTabOrder(ui->radioButton_admin, ui->radioButton_user);
    setTabOrder(ui->radioButton_user, ui->pushButton_registration);
    setTabOrder(ui->pushButton_registration, ui->pushButton_back_2);
}

//закрыть окно
void MainWindow::on_pushButton_close_clicked()
{
    this->close();
}

//очистить содржимое
void MainWindow::on_pushButton_clear_clicked()
{
    ui->input_login->clear();
    ui->input_password->clear();
}

void MainWindow::on_pushButton_recover_clicked()
{
    //переход на другое окно для восстановления активности пользователя
    ui->stackedWidget->setCurrentIndex(1);
    Log::SaveLog("Восстановление пользователя или пароля", this);    //запись лога
}

void MainWindow::on_pushButton_back_clicked()
{
    //переход на поле с логином и паролем назад
    ui->stackedWidget->setCurrentIndex(0);
}

//выход из поля регистрации
void MainWindow::on_pushButton_back_2_clicked()
{
    //переход на поле с вариантами работы с пользователем
    ui->stackedWidget->setCurrentIndex(1);
}

//вход в ЛК
void MainWindow::on_pushButton_authorization_clicked()
{
    QString login=ui->input_login->text();
    QString password=ui->input_password->text();
    if (login.size()==0||password.size()==0)
    {
        ui->invalid_data->setText("Введите логин и/или пароль");
    } else {
    Log::SaveLog("Попытка аутентификации пользователя с логином", login, this);    //запись лога
    //модель базы данных
    DBConnect dbConnect;
    AccountModel accountModel=dbConnect.SelectAccountModel(login, password);
    if (accountModel.id>0) {
    //открытие личного кабинета пользователя
    account = new Account (this, accountModel.id);
    this->close();
    account->show();
    Log::SaveLog("Вход в личный кабинет пользователя с логином "+login, this);    //запись лога
    } else {
        ui->invalid_data->setText("Неверные идентификационные данные или пользователь неактивен");
        Log::SaveLog("Неверные идентификационные данные или пользователь неактивен", this);    //запись лога
    }
    }
}

void MainWindow::on_pushButton_registration_user_clicked()
{
    //переход на поле с регистрацией
    ui->stackedWidget->setCurrentIndex(2);
}

//регистрация пользователя
void MainWindow::on_pushButton_registration_clicked()
{
    //заполнение параметров
    QString name=ui->name->text();
    QString position=ui->position->text();
    QString departament=ui->departament->text();
    QString email=ui->email->text();
    QString password=ui->password->text();
    QString repeatePassword=ui->repeate_password->text();
    QString typeUser;
    if (ui->radioButton_admin->isChecked()) typeUser="1";
    else if (ui->radioButton_user->isChecked())typeUser="2";
    //проверка введенных данных
    bool flagData=true;
    if (name.size()==0||position.size()==0||departament.size()==0||email.size()==0||password.size()==0||repeatePassword.size()==0||typeUser.size()==0)
    {
        ui->warning->setText("Проверьте заполнение данных");
        flagData = false;
    }
    //совпадение пароля
    bool flagPasswordRepeate=true;
    if (password!=repeatePassword)
    {
        ui->warning->setText("Выбранные пароли не совпадают");
        flagPasswordRepeate=false;
    }
    bool flagUserRepeate=true;
    DBConnect dbConnect;
    if (dbConnect.CheckUser(name, position, email, departament))
    {
        ui->warning->setText("Такой пользователь уже зарегистрирован");
        flagUserRepeate=false;
    }
    AccountModel accountModel(name,position, email, password, typeUser, departament);
    //DBConnect dbConnect;
    if (flagData&&flagPasswordRepeate&&flagUserRepeate) {
    //if (dbConnect.RegistrationUser(accountModel))
    //{
        //подтверждение регистрации вводом пароля администратора
        checkPasswordAdmin = new CheckPasswordAdmin (this, accountModel);
        checkPasswordAdmin->exec();
        //QMessageBox::information(this, "Результат","Успешная регистрация пользователя "+ email);
        //Log::SaveLog("Пользователь с логином - ", email, " зарегистрирован", this);    //запись лога
    }
    //else {
        //QMessageBox::critical(this, "Результат","Пользователь "+ email + " не зарегистрирован");
    //}
}

//очистить введенные регистрационные данные
void MainWindow::on_pushButton_clear_2_clicked()
{
    ui->name->clear();
    ui->position->clear();
    ui->departament->clear();
    ui->email->clear();
    ui->password->clear();
    ui->repeate_password->clear();
}














