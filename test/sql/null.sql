create table t (id int nullable, num int nullable, d date nullable);
insert into t values(1, 2, '2020-01-01');
insert into t values(1, null, null);
insert into t values(1, null, '2020-02-02');
insert into t values(null, 1, '2020-01-02');
create index idx on t (id);
select * from t where id is not null;
select * from t where num is not null;