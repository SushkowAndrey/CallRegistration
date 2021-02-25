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
    //сортировка по дате
    ui->table_appeal_citizens->sortItems(1, Qt::AscendingOrder);
    //запрет редактирования первой колонки
    //запрет редактирования данных
    //ui->table_appeal_citizens->column()
            //setEditTriggers(QAbstractItemView::NoEditTriggers);
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
        //дата обращения
        QDateEdit *dateRequest =new QDateEdit();
        //всплывающий календарь
        dateRequest->setCalendarPopup(true);
        dateRequest->setDate(QDate::fromString(appealCitizensModel[i].dateRequest, "dd.MM.yyyy"));
        ui->table_appeal_citizens->setCellWidget(i, 1, dateRequest);
        ui->table_appeal_citizens->setItem(i, 1,new QTableWidgetItem(appealCitizensModel[i].dateRequest));
        //ФИО заявителя
        ui->table_appeal_citizens->setItem(i, 2,new QTableWidgetItem(appealCitizensModel[i].applicant));
        //год рождения
        ui->table_appeal_citizens->setItem(i, 3,new QTableWidgetItem(appealCitizensModel[i].yearBirth));
        //контактные данные
        ui->table_appeal_citizens->setItem(i, 4,new QTableWidgetItem(appealCitizensModel[i].contact));
        //выплывающий список в меню
        //категория граждан
        QComboBox * categoryCitizens = new QComboBox();  
        QStringList valuesCategoryCitizens=db.CategoryCitizens();
        categoryCitizens->addItems(valuesCategoryCitizens);
        ui->table_appeal_citizens->setCellWidget(i, 5, categoryCitizens);
        categoryCitizens->setCurrentIndex(appealCitizensModel[i].categoryCitizensId);
        categoryCitizens->currentText();
        //categoryCitizens->currentIndexChanged(categoryCitizens->currentIndex());
        //connect(categoryCitizens, SIGNAL(currentIndexChanged(int)),this, SLOT(changed(i)));
        //Log::SaveLog("psdfsdf " + QString::number(a), this);    //запись лога
        //ui->table_appeal_citizens->setItem(i, 5,new QTableWidgetItem(QString::number(changed(categoryCitizens->currentIndex()))));
        //ui->table_appeal_citizens->setItem(i, 5,new QTableWidgetItem(QString::number(categoryCitizens->currentIndex())));
        //выплывающий список в меню
        //медицинская организация
        QComboBox * medicalOrganization = new QComboBox();
        QStringList valuesMedicalOrganization=db.MedicalOrganization();
        medicalOrganization->addItems(valuesMedicalOrganization);
        ui->table_appeal_citizens->setCellWidget(i, 6, medicalOrganization);
        medicalOrganization->setCurrentIndex(appealCitizensModel[i].medicalOrganizationId);
        medicalOrganization->currentText();
        ui->table_appeal_citizens->setItem(i, 6,new QTableWidgetItem(appealCitizensModel[i].medicalOrganizationId));
        //описание
        ui->table_appeal_citizens->setItem(i, 7,new QTableWidgetItem(appealCitizensModel[i].description));
        //результат
        ui->table_appeal_citizens->setItem(i, 8,new QTableWidgetItem(appealCitizensModel[i].result));
        //кому передано
        ui->table_appeal_citizens->setItem(i, 9,new QTableWidgetItem(appealCitizensModel[i].transmitted));
        //выплывающий список в меню
        //тип обращения
        QComboBox * typeRequestId = new QComboBox();
        QStringList valuesTypeRequestId=db.TypeRequestId();
        typeRequestId->addItems(valuesTypeRequestId);
        ui->table_appeal_citizens->setCellWidget(i, 10, typeRequestId);
        typeRequestId->setCurrentIndex(appealCitizensModel[i].typeRequestId);
        typeRequestId->currentText();
        ui->table_appeal_citizens->setItem(i, 10,new QTableWidgetItem(QString::number(appealCitizensModel[i].typeRequestId)));
        //признак закрытия
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
        connect(ui->table_appeal_citizens, SIGNAL(stateChanged(int state)), this, SLOT(check(QTableWidgetItem*)));
        //ui->table_appeal_citizens->setItem(i, 12,new QTableWidgetItem(appealCitizensModel[i].anonymousAppeal));
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
        //комментарии
        ui->table_appeal_citizens->setItem(i, 13,new QTableWidgetItem(appealCitizensModel[i].comments));
        //дата закрытия
        QDateEdit *closingDate =new QDateEdit();
        //всплывающий календарь
        closingDate->setCalendarPopup(true);
        closingDate->setDate(QDate::fromString(appealCitizensModel[i].closingDate, "dd.MM.yyyy"));
        ui->table_appeal_citizens->setCellWidget(i, 14, closingDate);
        ui->table_appeal_citizens->setItem(i, 14,new QTableWidgetItem(appealCitizensModel[i].closingDate));
        //пользователь
        QComboBox * TableUsersId = new QComboBox();
        QStringList valuesTableUsersId=db.TableUsersId();
        TableUsersId->addItems(valuesTableUsersId);
        ui->table_appeal_citizens->setCellWidget(i, 15, TableUsersId);
        TableUsersId->setCurrentIndex(appealCitizensModel[i].tableUsersId);
        TableUsersId->currentText();
        ui->table_appeal_citizens->setItem(i, 15,new QTableWidgetItem(appealCitizensModel[i].tableUsersId));
    }
    ui->table_appeal_citizens->setSortingEnabled(true);
}




int Account::changed(int i)
{
   /* QComboBox* combo = new QComboBox();
    DBConnect db;
    QStringList valuesCategoryCitizens=db.CategoryCitizens();
    combo->addItems(valuesCategoryCitizens);
    ui->table_appeal_citizens->setCellWidget(i, 5, combo);
    return combo->currentIndex();*/
}



void Account::on_pushButton_add_appeal_citizens_clicked()
{
    int newRow=ui->table_appeal_citizens->rowCount();
    ui->table_appeal_citizens->insertRow(newRow);
    QString dateRequest = QDate::currentDate().toString("dd.MM.yyyy");
    AppealCitizensModel appealCitizensModel(0, dateRequest, idAccount);
    DBConnect db;
    if(db.AddAppealCitizens(appealCitizensModel)) ui->statusbar->showMessage("строка добавлена");
    else ui->statusbar->showMessage("строка НЕ добавлена");
    //заполнение строки
    ui->table_appeal_citizens->setItem(newRow, 0,new QTableWidgetItem(QString::number(newRow+1).rightJustified(6, ' ')));
    //дата обращения
    QDateEdit *dateRequestAdd =new QDateEdit();
    //всплывающий календарь
    dateRequestAdd->setCalendarPopup(true);
    dateRequestAdd->setDate(QDate::fromString(dateRequest, "dd.MM.yyyy"));
    ui->table_appeal_citizens->setCellWidget(newRow+1, 1, dateRequestAdd);
    Log::SaveLog("ID "+QString::number(newRow+1), this);    //запись лога
    ui->table_appeal_citizens->setItem(newRow, 1,new QTableWidgetItem(dateRequest));
//доработать

}

void Account::ColorRow()
{/*в процессе
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
    }*/
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
{/*
    ui->table_appeal_citizens->currentRow();
    AppealCitizensModel appealCitizensModelDuplicate(QString applicant, int categoryCitizensId, QString yearBirth, QString contact, int medicalOrganizationId, int typeRequestId,
                                QString description, QString dateRequest, QString transmitted, QString result, int tableUsersId,
                                int signClosure, int anonymousAppeal, QString closingDate, QString comments);
*/
}

//изменение данных таблицы
void Account::on_table_appeal_citizens_itemChanged(QTableWidgetItem *item)
{
    QString data=item->text();
    DBConnect db;
    db.EditingApplicant(data, ui->table_appeal_citizens->currentRow(), ui->table_appeal_citizens->currentColumn());
}
