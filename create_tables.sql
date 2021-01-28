//категория граждан
create table category_citizens
(
    id                   integer not null
    primary key autoincrement,
    title text not null
);

//медицинская организация
create table medical_organization
(
    id                   integer not null
    primary key autoincrement,
    name_organization text not null
);

//населенный пункт
create table locality
(
    id                   integer not null
    primary key autoincrement,
    name_locality text not null
);

//операторы
create table table_users
(
    id                    integer not null
    primary key autoincrement,
    lastName              text    not null,
    name                  text    not null,
    middleName            text    not null,
    position              text    not null,
    email                 text    not null,
    password              text    not null,
    type_user             integer not null,
    active                integer default 1
);

//районы Воронежской области
create table_region
(
    id                   integer not null
    primary key autoincrement,
    name_region text not null
);

//тип обращения
create type_request
(
    id                   integer not null
    primary key autoincrement,
    reason text not null
);



























//таблица организации
create table table_organization
(
    id                   integer not null
    primary key autoincrement,
    name                 text    not null,
    inn                  text    not null,
    address              text    not null,
    telephone            text    not null,
    director             text    not null,
    license_type         text,
    license_number       text,
    license_date         date,
    license_organization text,
    type_organization    text    not null,
    active               integer default 1
);
//типы организаций
0 Контролирующий орган
1 Федеральное учреждение
2 Региональное учреждение
3 Казенное предприятие
4 Общество с ограниченной ответственностью
5 Открытое акционерное общество
6 Закрытое акционерное общество
7 Индивидуальный предприниматель

//типы лицензий
1-Медицинская
2-Фармацевтическая
3-Медицинская и фармацевтическая

//поиск организации по номеру id
SELECT  name, inn, address, telephone, director, type_organization, license_type, license_number, license_date, license_organization FROM table_organization WHERE id = 1




//таблица пользователя, связана с организацией через id
create table table_person
(
    id                    integer not null
    primary key autoincrement,
    lastName              text    not null,
    name                  text    not null,
    middleName            text    not null,
    position              text    not null,
    email                 text    not null,
    password              text    not null,
    type_user             integer not null,
    active                integer default 1,
    table_organization_id integer not null
    references table_organization
);
//добавление пользователя
INSERT INTO table_person (lastName, name, middleName, position, email, password) VALUES ('123', '123', '123', '123', '123', '123')

//проверка при входе в личный кабинет
SELECT email FROM table_person WHERE email='123' AND password='123' AND active=1
// заполнение информации о пользоватете
SELECT lastName, name, middleName, position, email, type_user FROM table_person WHERE id = 1

//конкретный пользователь
SELECT id, lastName, name, middleName, position, email, password
FROM table_person
WHERE email='123' AND password='123' AND active='1'







//рецепт
create table table_recipe
(
    num_recipe    integer not null
        primary key autoincrement,
    hospital      integer not null,
    series        text    not null,
    date_recipe   date    not null,
    age           int     not null,
    pacient       text    not null,
    date_birthday date    not null,
    address       text    not null,
    user_hospital text    not null,
    drug_MNN      text    not null,
    apteka        text    not null,
    drug_TN       int     not null,
    user_apteka   text    not null,
    date_release  date    not null,
    result        int default 0 not null
);
