create table t (a int, b int);
load data infile "../test/sql/dataset/t5.csv" into table t;
create index idx on t (a, b);