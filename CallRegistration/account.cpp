#include "account.h"
#include "ui_account.h"

Account::Account(QWidget *parent, int idAccount) :
    QMainWindow(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
    this->idAccount=idAccount;
    //изменние цвета в рработе
    connect (ui->table_appeal_citizens, SIGNAL(cellChanged(int, int)), this, SLOT(ColorRow()));
    AccountValue();
    TableColumns();
    FillingTable();
    ColorRow();
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
    //запрет редактирования первой колонки

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
        //выплывающий список в меню
        //категория граждан
        QComboBox * categoryCitizens = new QComboBox();  
        QStringList valuesCategoryCitizens=db.CategoryCitizens();
        categoryCitizens->addItems(valuesCategoryCitizens);
        ui->table_appeal_citizens->setCellWidget(i, 5, categoryCitizens);
        categoryCitizens->setCurrentIndex(appealCitizensModel[i].categoryCitizensId);
        categoryCitizens->currentText();
        //выплывающий список в меню
        //медицинская организация
        QComboBox * medicalOrganization = new QComboBox();
        QStringList valuesmedicalOrganization=db.MedicalOrganization();
        medicalOrganization->addItems(valuesmedicalOrganization);
        ui->table_appeal_citizens->setCellWidget(i, 6, medicalOrganization);
        medicalOrganization->setCurrentIndex(appealCitizensModel[i].medicalOrganizationId);
        medicalOrganization->currentText();
        ui->table_appeal_citizens->setItem(i, 7,new QTableWidgetItem(appealCitizensModel[i].description));
        ui->table_appeal_citizens->setItem(i, 8,new QTableWidgetItem(appealCitizensModel[i].result));
        ui->table_appeal_citizens->setItem(i, 9,new QTableWidgetItem(appealCitizensModel[i].transmitted));
        ui->table_appeal_citizens->setItem(i, 10,new QTableWidgetItem(QString::number(appealCitizensModel[i].typeRequestId)));
        ui->table_appeal_citizens->setItem(i, 11,new QTableWidgetItem(appealCitizensModel[i].signClosure));
        //чек-бокс
        //признак закрытия
        QCheckBox *signClosure=new QCheckBox();
        ui->table_appeal_citizens->setCellWidget(i, 11, signClosure);
        //проверка нажатия флажков (одного или нескольких)
        if (appealCitizensModel[i].signClosure==1)
        {
            signClosure->setCheckState(Qt::Checked);
        } else if (appealCitizensModel[i].signClosure==0)
        {
            signClosure->setCheckState(Qt::Unchecked);
        }
        ui->table_appeal_citizens->setItem(i, 12,new QTableWidgetItem(appealCitizensModel[i].anonymousAppeal));
        //чек-бокс
        //анонимное или нет
        QCheckBox *anonymousAppeal=new QCheckBox();
        ui->table_appeal_citizens->setCellWidget(i, 12, anonymousAppeal);
        //проверка нажатия флажков (одного или нескольких)
        if (appealCitizensModel[i].anonymousAppeal==1)
        {
            anonymousAppeal->setCheckState(Qt::Checked);
        } else if (appealCitizensModel[i].anonymousAppeal==0)
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
    AppealCitizensModel appealCitizensModel(0, dateRequest, idAccount);
    DBConnect db;
    if(db.AddAppealCitizens(appealCitizensModel)) ui->statusbar->showMessage("строка добавлена");
    else ui->statusbar->showMessage("строка НЕ добавлена");
    FillingTable();
}

void Account::ColorRow()
{
    for (int i=0;i<appealCitizensModel.size();i++)
    {
        if (appealCitizensModel[i].signClosure==1)
        {
            ui->table_appeal_citizens->item(i, 7)->setBackground(Qt::yellow);
            ui->table_appeal_citizens->item(i, 8)->setBackground(Qt::yellow);
            ui->table_appeal_citizens->item(i, 9)->setBackground(Qt::yellow);
            ui->table_appeal_citizens->item(i, 10)->setBackground(Qt::yellow);
            ui->table_appeal_citizens->item(i, 11)->setBackground(Qt::yellow);
        } else if (appealCitizensModel[i].anonymousAppeal==0)
        {
            ui->table_appeal_citizens->item(i, 7)->setBackground(Qt::red);
            ui->table_appeal_citizens->item(i, 8)->setBackground(Qt::red);
            ui->table_appeal_citizens->item(i, 9)->setBackground(Qt::red);
            ui->table_appeal_citizens->item(i, 10)->setBackground(Qt::red);
            ui->table_appeal_citizens->item(i, 11)->setBackground(Qt::red);
        }
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

//дублирование выделенного обращения в работе
void Account::on_pushButton_duplicate_clicked()
{
    ui->table_appeal_citizens->currentRow();
    AppealCitizensModel appealCitizensModelDuplicate(QString applicant, int categoryCitizensId, QString yearBirth, QString contact, int medicalOrganizationId, int typeRequestId,
                                QString description, QString dateRequest, QString transmitted, QString result, int tableUsersId,
                                int signClosure, int anonymousAppeal, QString closingDate, QString comments);

}

//изменение данных таблицы
void Account::on_table_appeal_citizens_itemChanged(QTableWidgetItem *item)
{
    QString data=item->text();
    DBConnect db;
    db.EditingApplicant(data, ui->table_appeal_citizens->currentRow(), ui->table_appeal_citizens->currentColumn());
}
