create table SUPPLIERS(
supplier_name varchar(255) not null,
supplier_id number(3),
city varchar(255),
address varchar(255),
contact_person varchar(255),
mobile number(11) not null unique,
constraint pkey primary key(supplier_id)
);
create table CUSTOMERS(
customer_id number(5),
first_name varchar(255),
last_name varchar(255),
mobile number(11) not null unique,
address varchar(255),
city varchar(255),
constraint c_key primary key(customer_id)
);

create table PRODUCTS(
product_id number(3),
product_name varchar(255),
supplier_id number(3),
product_category varchar(255),
price_per_unit number(10,2) not null,
manufactured_date date not null,
expiring_date date not null,
constraint p_key primary key(product_id),
constraint p_fk foreign key(supplier_id) references SUPPLIERS(supplier_id)
);

create table STOCKS(
product_id number(3),
quantity number(3),
supplier_id number(3),
constraint s_fk_p foreign key(product_id) references PRODUCTS(product_id),
constraint s_fk_s foreign key(supplier_id) references SUPPLIERS(supplier_id)
);
create table SALES(
product_id number(3),
date_of_sale date not null,
quanity number(3) not null,
price_per_unit number(10,2) not null,
total_amount number(10,2)
);
create table BILLS(
bill_id number(3),
customer_id number(3),
product_id number(3),
date_on_bill date,
quntity number(5),
price_per_uinit number(3),
total_amount number(10,2),
constraint b_fk_c foreign key(customer_id) references CUSTOMERS(customer_id),
constraints b_fk_p foreign key(product_id) references PRODUCTS(product_id)
);


create index customer_index on CUSTOMERS (first_name);
create index supplier_index on SUPPLIERS (city);
create index billr_index on BILLS (bill_id);
create sequence customer_number increment by 1 start with 1 maxvalue 1000;
create sequence supplier_number increment by 1 start with 1 maxvalue 1000;
create sequence bill_number increment by 1 start with 1 maxvalue 1000;
create synonym cust for CUSTOMERS;
create synonym sup for SUPPLIERS;
create synonym sto for STOCKS;
create synonym pro for PRODUCTS;
create synonym sa for SALES;
create synonym bi for BILLS;
create view all_customer as (select * from CUSTOMERS);
create view all_customer_mobile as (select first_name,last_name,mobile from CUSTOMERS);
create view all_supplier as (select * from SUPPLIERS);
create view all_supplier_city as (select supplier_id, city  from SUPPLIERS);
create view stock_qty as (select supplier_id, quantity, product_id from STOCKS);
create view price_view as (select product_name,product_id, price_per_unit from PRODUCTS);
create view product_expiry_date as (select product_name,product_id, expiring_date from PRODUCTS);
create view sales_view as (select * from SALES);
create view bill_view as (select * from BILLS);
