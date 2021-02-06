//операторы
create table table_users
(
    id                    integer not null
    primary key autoincrement,
    name                  text    not null,
    position              text    not null,
    email                 text    not null unique,
    password              text    not null,
    type_user             text not null,
    active                integer default 1, 
    departament           text not null,
);
//типы пользователя
1-Администратор
2-Пользователь
//добавление данных
INSERT INTO table_users (name, position, email, password, type_user) VALUES ('Сушков Андрей Сергеевич', 'Начальник ОМБЛС и ССОК', 'andreysushkow@mail.ru', '31415926', 1)
//проверка при входе в личный кабинет
SELECT id FROM table_users WHERE email='andreysushkow@mail.ru' AND password='31415926' AND active=1
//добавление колонки
ALTER TABLE table_users ADD COLUMN departament text
//регистрация пользователя
INSERT INTO table_users (name, position, email, password, type_user, departament) VALUES ('Иванов Иван Иванович', 'Специалист', 'mail@mail.ru', '1', '1', 'ОКК')
//проверка правильности пароля администратора
SELECT id FROM table_users WHERE password='31415926' AND active=1 AND type_user='1'
//проверка наличия такого же пользователя в базе (проверяется по имени, должности, почте и отделу)
SELECT id FROM table_users WHERE email='123' AND active=1
//информация о пользоватете по id
SELECT name, position, email, password, type_user, departament FROM table_users WHERE id=1 AND active=1
//блокировка пользователя
UPDATE table_users SET active = 0 WHERE email='123' AND type_user='2'
____________________________________________________________
//категория граждан
create table category_citizens
(
    id                   integer not null
    primary key autoincrement,
    title text not null
);
//добавление данных
INSERT INTO category_citizens (title) VALUES ('РЛ (диабет)')
____________________________________________________________
//медицинская организация
create table medical_organization
(
    id                   integer not null
    primary key autoincrement,
    division text not null,
    name_organization text not null,
    region text not null

);
____________________________________________________________
//тип обращения
create table type_request
(
    id                   integer not null
    primary key autoincrement,
    reason text not null
);
//добавление данных
INSERT INTO type_request (reason) VALUES ('Отсутствие лп в аптеке')
____________________________________________________________
//название препарата
create table medicinal_product
(
    id                   integer not null
    primary key autoincrement,
    name_drug text not null,
    group_drug text not null
);
____________________________________________________________
create table appeal_citizens_medicinal_product
(
    id                   integer not null
    primary key autoincrement,
    appeal_citizens_id integer not null,
    medicinal_product_id integer not null
);
//добавление данных
INSERT INTO appeal_citizens_medicinal_product (appeal_citizens_id, medicinal_product_id) VALUES (1, 2)
____________________________________________________________
create table appeal_citizens
(    
    id integer not null primary key autoincrement,
    applicant text,
    category_citizens_id integer references category_citizens,
    year_birth text,
    contact text,
    medical_organization_id integer references medical_organization,
    type_request_id integer not null references type_request,
    description text, //описание
    date_request date, //дата обращения
    transmitted text, //кому передано
    result text,
    table_users_id integer not null references table_users,
    sign_closure integer default 0,
    anonymous_appeal integer default 0,
    closing_date date,
    comments text
);
____________________________________________________________