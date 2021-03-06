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
    Log::SaveLog("Закрытие окна входа в личный кабинет", this);    //запись лога
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
    Log::SaveLog("Выход из программы", this);    //запись лога
    this->close();
}

//очистить содeржимое
void MainWindow::on_pushButton_clear_clicked()
{
    Log::SaveLog("Очистка введенного логина и пароля", this);    //запись лога
    ui->input_login->clear();
    ui->input_password->clear();
}

void MainWindow::on_pushButton_recover_clicked()
{
    //переход на другое окно для восстановления активности пользователя
    ui->stackedWidget->setCurrentIndex(1);
    Log::SaveLog("Работа администратора с пользователем", this);    //запись лога
}

void MainWindow::on_pushButton_back_0_clicked()
{
    //переход на поле с логином и паролем назад
    ui->stackedWidget->setCurrentIndex(0);
}

//выход из поля регистрации
void MainWindow::on_pushButton_back_1_clicked()
{
    ui->invalid_data->clear();
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

//переход на поле с регистрацией
void MainWindow::on_pushButton_registration_user_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//регистрация пользователя
void MainWindow::on_pushButton_registration_clicked()
{
    Log::SaveLog("Регистрация пользователя", this);    //запись лога
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
    if (dbConnect.CheckUser(email))
    {
        ui->warning->setText("Пользователь с таким Email уже зарегистрирован");
        Log::SaveLog("Пользователь с Email "+email+" уже зарегистрирован", this);    //запись лога
        flagUserRepeate=false;
    }
    AccountModel accountModel(name,position, email, password, typeUser, departament);
    if (flagData&&flagPasswordRepeate&&flagUserRepeate) {
        Log::SaveLog("Попытка регистрации пользователя",accountModel.name, this);    //запись лога
        //очистка данных
        ui->name->clear();
        ui->position->clear();
        ui->departament->clear();
        ui->email->clear();
        ui->password->clear();
        ui->repeate_password->clear();
        //открытие окна ввода пароля администратором
        checkPasswordAdmin = new CheckPasswordAdmin (this, accountModel, true);
        checkPasswordAdmin->exec();
    }
}

//очистить введенные регистрационные данные
void MainWindow::on_pushButton_clear_2_clicked()
{
    Log::SaveLog("Очистка регистрационных данных", this);    //запись лога
    ui->name->clear();
    ui->position->clear();
    ui->departament->clear();
    ui->email->clear();
    ui->password->clear();
    ui->repeate_password->clear();
}


void MainWindow::on_pushButton_block_clicked()
{
    //переход на поле с блокировкой
    ui->stackedWidget->setCurrentIndex(3);
}

//назад в операции пользователя из блокировки пользователя
void MainWindow::on_pushButton_back_2_clicked()
{
    ui->warning_2->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_block_it_clicked()
{
    Log::SaveLog("Блокировка пользователя", this);    //запись лога
    //заполнение параметров
    QString email=ui->email_block->text();
    //проверка введенных данных
    if (email.size()==0)
    {
        ui->warning_2->setText("Проверьте заполнение данных");
    } else {
    bool flagUserRepeate=true;
    DBConnect dbConnect;
    if (!dbConnect.CheckUser(email))
    {
        ui->warning_2->setText("Пользователя с таким Email не существует или заблокирован");
        Log::SaveLog("Пользователь с Email "+email+" не существует или заблокирован", this);    //запись лога
        flagUserRepeate=false;
    }
    if (flagUserRepeate) {
        Log::SaveLog("Попытка блокировки пользователя", email, this);    //запись лога
        ui->email_block->clear();
        checkPasswordAdmin = new CheckPasswordAdmin (this, email, "Блокировка");
        checkPasswordAdmin->exec();
    }
    }
}

void MainWindow::on_pushButton_activate_clicked()
{
    //переход на поле с активацией
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_active_it_clicked()
{
    Log::SaveLog("Активация пользователя", this);    //запись лога
    //заполнение параметров
    QString email=ui->email_activate->text();
    //проверка введенных данных
    if (email.size()==0)
    {
        ui->warning_3->setText("Проверьте заполнение данных");
    } else {
    bool flagUserRepeate=true;
    DBConnect dbConnect;
    if (!dbConnect.CheckUser(email))
    {
        ui->warning_3->setText("Пользователя с таким Email не существует");
        flagUserRepeate=false;
    }
    //проверка активации пользователя
    bool flagUserActive=true;
    //DBConnect dbConnect;
    if (dbConnect.CheckActive(email))
    {
        ui->warning_3->setText("Пользователя с таким Email уже активен");
        Log::SaveLog("Пользователь с Email "+email+" уже активен", this);    //запись лога
        flagUserRepeate=false;
    }
    if (flagUserRepeate&&flagUserActive) {
        Log::SaveLog("Попытка активации пользователя",email, this);    //запись лога
        ui->email_activate->clear();
        checkPasswordAdmin = new CheckPasswordAdmin (this, email, 1);
        checkPasswordAdmin->exec();
    }
    }
}

//назад в операции пользователя из активности пользователя
void MainWindow::on_pushButton_back_3_clicked()
{
    ui->warning_3->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

//окно смены пароля пользователя
void MainWindow::on_pushButton_password_user_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

//назад в операции пользователя из смены пароля пользователя
void MainWindow::on_pushButton_back_4_clicked()
{
    ui->warning_4->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_change_password_user_clicked()
{
    Log::SaveLog("Смена пароля пользователя", this);    //запись лога
    //заполнение параметров
    QString email=ui->email_change_password->text();
    QString newPassword=ui->new_password->text();
    QString repeatNewPassword=ui->repeate_new_password->text();
    //проверка введенных данных
    if (email.size()==0&&newPassword.size()==0&&repeatNewPassword.size()==0)
    {
        ui->warning_4->setText("Проверьте заполнение данных");
    } else {
    bool flagUserRepeate=true;
    DBConnect dbConnect;
    if (!dbConnect.CheckUser(email))
    {
        ui->warning_4->setText("Пользователя с таким Email не существует");
        flagUserRepeate=false;
    }
    //совпадение пароля
    bool flagPasswordRepeate=true;
    if (newPassword!=repeatNewPassword)
    {
        ui->warning->setText("Выбранные пароли не совпадают");
        flagPasswordRepeate=false;
    }
    if (flagUserRepeate&&flagPasswordRepeate) {
        Log::SaveLog("Попытка смены пароля пользователя",email, this);    //запись лога
        AccountModel accountModel(email, newPassword);
        ui->email_change_password->clear();
        ui->new_password->clear();
        ui->repeate_new_password->clear();
        checkPasswordAdmin = new CheckPasswordAdmin (this, accountModel, 1);
        checkPasswordAdmin->exec();
    }
    }

}

//показать/скрыть пароль при смене пароля
void MainWindow::on_show_password_stateChanged(int arg1)
{
    if (arg1==2)
    {
        ui->new_password->setEchoMode(QLineEdit::Normal);
        ui->repeate_new_password->setEchoMode(QLineEdit::Normal);
    } else if (arg1==0) {
        ui->new_password->setEchoMode(QLineEdit::Password);
        ui->repeate_new_password->setEchoMode(QLineEdit::Password);
    }
}
