drop table tmp_t1;
drop table tmp_t2;
create table tmp_t1 (i int, f float, c char(10));
create table tmp_t2 (i int, f float, c char(10));
load data infile "../test/sql/dataset/t2.csv" into table tmp_t1;
load data infile "../test/sql/dataset/t4.csv" into table tmp_t2;