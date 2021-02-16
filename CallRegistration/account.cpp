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
    DBConnect db;
    ui->table_appeal_citizens->setRowCount(db.CountOrganization());
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
    ui->table_appeal_citizens->resizeRowsToContents();
}


void Account::FillingTable()
{
    ui->table_appeal_citizens->setSortingEnabled(false);
    DBConnect db;
    appealCitizensModel=db.TableAppealCitizens();
    for (int i=0;i<appealCitizensModel.size();i++)
    {
        //дополнение id пробелами справа, для корректной сортировки. Всего 6 символов для заполнения данными
        ui->table_appeal_citizens->setItem(i, 0,new QTableWidgetItem(QString::number(appealCitizensModel[i].id).rightJustified(6, ' ')));
        QDateEdit *dateRequest =new QDateEdit();
        //всплывающий календарь
        dateRequest->setCalendarPopup(true);
        //дата обращения
        dateRequest->setDate(QDate::fromString(appealCitizensModel[i].dateRequest, "dd.MM.yyyy"));
        ui->table_appeal_citizens->setCellWidget(i, 1, dateRequest);
        ui->table_appeal_citizens->setItem(i, 2,new QTableWidgetItem(appealCitizensModel[i].applicant));
        ui->table_appeal_citizens->setItem(i, 3,new QTableWidgetItem(appealCitizensModel[i].yearBirth));
        ui->table_appeal_citizens->setItem(i, 4,new QTableWidgetItem(appealCitizensModel[i].contact));
        //////////////////////////////////////////
        //выплывающий список в меню - не работает
        //категория граждан
        QComboBox * categoryCitizens = new QComboBox();
        QStringList fonts;
        fonts << "Arial" << "Helvetica" << "Times" << "Courier";
        categoryCitizens->addItems(fonts);
        ui->table_appeal_citizens->setCellWidget(i, 5, categoryCitizens);
        //categoryCitizens->itemText(appealCitizensModel[i].categoryCitizensId.toInt());
        //ui->table_appeal_citizens->setItem(i, 5,new QTableWidgetItem((categoryCitizens->itemText(appealCitizensModel[i].categoryCitizensId.toInt()))));
        ui->table_appeal_citizens->setItem(i, 5,new QTableWidgetItem((categoryCitizens->itemText(appealCitizensModel[i].categoryCitizensId))));
        /////////////////////////////////////////////
        ui->table_appeal_citizens->setItem(i, 6,new QTableWidgetItem(appealCitizensModel[i].medicalOrganizationId));
        ui->table_appeal_citizens->setItem(i, 7,new QTableWidgetItem(appealCitizensModel[i].description));
        ui->table_appeal_citizens->setItem(i, 8,new QTableWidgetItem(appealCitizensModel[i].result));
        ui->table_appeal_citizens->setItem(i, 9,new QTableWidgetItem(appealCitizensModel[i].transmitted));
        ui->table_appeal_citizens->setItem(i, 10,new QTableWidgetItem(appealCitizensModel[i].typeRequestId));
        ui->table_appeal_citizens->setItem(i, 11,new QTableWidgetItem(appealCitizensModel[i].signClosure));
        //чек-бокс
        //признак закрытия
        QCheckBox *signClosure=new QCheckBox();
        ui->table_appeal_citizens->setCellWidget(i, 11, signClosure);
        //проверка нажатия флажков (одного или нескольких)
        if (appealCitizensModel[i].signClosure=="1")
        {
            signClosure->setCheckState(Qt::Checked);
            ui->table_appeal_citizens->item(i, 11)->setBackground(Qt::yellow);
        } else if (appealCitizensModel[i].signClosure=="0")
        {
            signClosure->setCheckState(Qt::Unchecked);
        }
        ui->table_appeal_citizens->setItem(i, 12,new QTableWidgetItem(appealCitizensModel[i].anonymousAppeal));
        //чек-бокс
        //анонимное или нет
        QCheckBox *anonymousAppeal=new QCheckBox();
        ui->table_appeal_citizens->setCellWidget(i, 12, anonymousAppeal);
        //проверка нажатия флажков (одного или нескольких)
        if (appealCitizensModel[i].anonymousAppeal=="1")
        {
            anonymousAppeal->setCheckState(Qt::Checked);
        } else if (appealCitizensModel[i].anonymousAppeal=="0")
        {
            anonymousAppeal->setCheckState(Qt::Unchecked);
        }
        ui->table_appeal_citizens->setItem(i, 13,new QTableWidgetItem(appealCitizensModel[i].comments));
        ui->table_appeal_citizens->setItem(i, 15,new QTableWidgetItem(appealCitizensModel[i].closingDate));
        ui->table_appeal_citizens->setItem(i, 16,new QTableWidgetItem(appealCitizensModel[i].tableUsersId));
    }
    ui->table_appeal_citizens->setSortingEnabled(true);
}


void Account::on_pushButton_add_appeal_citizens_clicked()
{
    //
    ui->table_appeal_citizens->insertRow(ui->table_appeal_citizens->rowCount());
    QString dateRequest = QDate::currentDate().toString("dd.MM.yyyy");
    AppealCitizensModel appealCitizensModel(QString::number(1), dateRequest, QString::number(idAccount));
    DBConnect db;
    if(db.AddAppealCitizens(appealCitizensModel)) ui->statusbar->showMessage("строка добавлена");
    else ui->statusbar->showMessage("строка НЕ добавлена");
    FillingTable();
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

/*
ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
QComboBox *box = new QComboBox;
//добавим значения ключей как элементы списка,
//а сами ключи - как userData
foreach(QString index, values.keys())
    box->addItem(values.value(index), index);
//по горизонтали растянем, по вертикали - как решит программа :)
box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
//вставляем в таблицу QTableWidget в колонку №5
ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, 5, box);


int valuesColNum = 5;
for(int i = 0; i < ui->tableWidget->rowCount(); ++i) {
    QComboBox *box;
    box = qobject_cast<QComboBox*>(
        ui->tableWidget->cellWidget(i,valuesColNum));
    qDebug() << i << "строка:";
    qDebug() << "значение ключа:" << box->currentText() << "ключ:" << box->currentData().toString();
}
*/




void Account::on_search_textChanged(const QString &arg1)
{





}



















