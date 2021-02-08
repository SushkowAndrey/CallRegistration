#include "account.h"
#include "ui_account.h"

Account::Account(QWidget *parent, int idAccount) :
    QMainWindow(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
    this->idAccount=idAccount;
    AccountValue();
    TableColumns();
    FillingTable();
}

Account::~Account()
{
    delete ui;
}

//заполнение аккаунта
void Account::AccountValue()
{
    DBConnect dbConnect;
    accountModel=dbConnect.SelectAccountModel(idAccount);
    ui->name->setText(accountModel.name);
    ui->position->setText(accountModel.position);
    ui->departament->setText(accountModel.departament);
    if (accountModel.typeUser=="1") ui->type_user->setText("Администратор");
    else if (accountModel.typeUser=="2") ui->type_user->setText("Пользователь");
}

void Account::TableColumns()
{
    //подготовка к заполнению
    //установка количества строк
    ui->table_appeal_citizens->setRowCount(3);
    //установка количества столбцов
    ui->table_appeal_citizens->setColumnCount(16);
    //названия колонок
    ui->table_appeal_citizens->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("№")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Дата")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("ФИО обратившегося")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Год рождения")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Контактные данные\n(адрес, телефон –\nпри предоставлении)")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("Тип гражданина")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(6, new QTableWidgetItem(tr("Медицинская организация")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(7, new QTableWidgetItem(tr("Содержание обращения")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(8, new QTableWidgetItem(tr("Результат")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(9, new QTableWidgetItem(tr("Дата и время передачи\nинформации,\n кому передано")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(10, new QTableWidgetItem(tr("Тип обращения")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(11, new QTableWidgetItem(tr("Признак закрытия")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(12, new QTableWidgetItem(tr("Анонимное")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(13, new QTableWidgetItem(tr("Комментарий")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(14, new QTableWidgetItem(tr("Дата закрытия")));
    ui->table_appeal_citizens->setHorizontalHeaderItem(15, new QTableWidgetItem(tr("Кто принял")));
    //изменить размер по содержимому
    ui->table_appeal_citizens->resizeColumnsToContents();
    //разрешена сортировка
    ui->table_appeal_citizens->setSortingEnabled(true);
}

void Account::FillingTable()
{
    DBConnect db;
    QVector <AppealCitizensModel> appealCitizensModel=db.TableAppealCitizens();
    for (int i=0;i<appealCitizensModel.size();i++)
    {
        ui->table_appeal_citizens->setItem(i, 0,new QTableWidgetItem(appealCitizensModel[i].id));
        ui->table_appeal_citizens->setItem(i, 1,new QTableWidgetItem(appealCitizensModel[i].dateRequest));
        ui->table_appeal_citizens->setItem(i, 2,new QTableWidgetItem(appealCitizensModel[i].applicant));
        ui->table_appeal_citizens->setItem(i, 3,new QTableWidgetItem(appealCitizensModel[i].yearBirth));
        ui->table_appeal_citizens->setItem(i, 4,new QTableWidgetItem(appealCitizensModel[i].contact));
        ui->table_appeal_citizens->setItem(i, 5,new QTableWidgetItem(appealCitizensModel[i].categoryCitizensId));
        ui->table_appeal_citizens->setItem(i, 6,new QTableWidgetItem(appealCitizensModel[i].medicalOrganizationId));
        ui->table_appeal_citizens->setItem(i, 7,new QTableWidgetItem(appealCitizensModel[i].description));
        ui->table_appeal_citizens->setItem(i, 8,new QTableWidgetItem(appealCitizensModel[i].result));
        ui->table_appeal_citizens->setItem(i, 9,new QTableWidgetItem(appealCitizensModel[i].transmitted));
        ui->table_appeal_citizens->setItem(i, 10,new QTableWidgetItem(appealCitizensModel[i].typeRequestId));
        ui->table_appeal_citizens->setItem(i, 11,new QTableWidgetItem(appealCitizensModel[i].signClosure));
        ui->table_appeal_citizens->setItem(i, 12,new QTableWidgetItem(appealCitizensModel[i].anonymousAppeal));
        ui->table_appeal_citizens->setItem(i, 13,new QTableWidgetItem(appealCitizensModel[i].comments));
        ui->table_appeal_citizens->setItem(i, 15,new QTableWidgetItem(appealCitizensModel[i].closingDate));
        ui->table_appeal_citizens->setItem(i, 16,new QTableWidgetItem(appealCitizensModel[i].tableUsersId));
    }

}



//выход из формы
void Account::on_pushButton_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Выход из программы", "Вы действительно хотите выйти?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    } else {
        //ничего не происходит
    }
}
