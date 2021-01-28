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
    name                  text    not null,
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

//тип обращения
create medicinal_product
(
    id                   integer not null
    primary key autoincrement,
    name_drug text not null
);

create appeal_citizens_medicinal_product
(
    id                   integer not null
    primary key autoincrement,
    appeal_citizens_id integer not null,
    medicinal_product_id integer not null
);

appeal_citizens
(    
    id integer not null primary key autoincrement,
    applicant text,
    category_citizens_id integer references category_citizens,
    year_birth text,
    telephone text,
    table_region_id integer references table_region,
    locality_id integer references locality
    street text,
    house text,
    flat text,
    trustee text,
    medical_organization_id integer references medical_organization,
    type_request_id integer not null references type_request,
    description text,
    date_request date,
    transmitted text,
    result text,
    table_users_id integer not null references table_users,
    sign_closure integer default 0,
    anonymous_appeal integer default 0,
    closing_date date,
    comments text
);