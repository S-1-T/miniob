
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <assert.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length[MAX_NUM];
  size_t from_length[MAX_NUM];
  size_t value_length[MAX_NUM];
  size_t tuple_num;
  size_t index_attr_num;
  Value values[MAX_NUM];
  InsertTuple tuples[MAX_NUM];
  Condition conditions[MAX_NUM][MAX_NUM];
  Selects selects[MAX_NUM];
  char id[MAX_NUM];
  char *index_attrs[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;

  for (int i=0; i<MAX_NUM; i++) {
  	context->condition_length[i] = 0;
  	context->from_length[i] = 0;
  	context->value_length[i] = 0;
  }

  context->select_length = 0;
  context->tuple_num = 0;
//  context->ssql->sstr.insertion.value_num = 0;
  context->ssql->sstr.errors = str;
  context->index_attr_num = 0;
  printf("parse sql failed. error=%s\n", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        UNIQUE
        EQ
        LT
        GT
        LE
        GE
        NE
        COUNT
        SUM
        AVG
        MAX
        MIN
        INNER
        JOIN
        ORDER
        BY
        ASC
        IS_
        NOT
        NULL_T
        NULLABLE
        IN
        GROUP

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _InsertTuple *tuples1;
  char *string;
  int number;
  float floats;
  char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;
%type <number> aggregation;
%type <number> order_type;
%type <number> nullable;
%type <number> comOp

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
      select  
    | insert
    | update
    | delete
    | create_table
    | drop_table
    | show_tables
    | desc_table
    | create_index	
    | drop_index
    | sync
    | begin
    | commit
    | rollback
    | load_data
    | help
    | exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON 
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = $7;
            create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 0);
            CONTEXT->index_attr_num = 0;
        }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = $8;
            create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 1);
            CONTEXT->index_attr_num = 0;
        }
    ;

index_attr_list:
    /* empty */
    | COMMA ID index_attr_list
    {
        CONTEXT->index_attrs[CONTEXT->index_attr_num++] = $2;
    }

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID SEMICOLON
	{
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3, $5);
	}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
        {
            CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
            create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
            //临时变量清零	
            CONTEXT->value_length[0] = 0;
        }
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE nullable
        {
            AttrInfo attribute;
            attr_info_init(&attribute, CONTEXT->id, $2, $4 + 1, $6);
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            CONTEXT->value_length[0]++;
        }
    |ID_get type nullable
        {
            AttrInfo attribute;
            // 属性占用字节多一个用于表示是否为 NULL
            switch ($2) {
                case INTS: {
                    attr_info_init(&attribute, CONTEXT->id, $2, sizeof(int) + 1, $3);
                }
                break;
                case FLOATS: {
                    attr_info_init(&attribute, CONTEXT->id, $2, sizeof(float) + 1, $3);
                }
                break;
                case DATES: {
                    attr_info_init(&attribute, CONTEXT->id, $2, sizeof(time_t) + 1, $3);
                }
                break;
                case CHARS: {
                    attr_info_init(&attribute, CONTEXT->id, $2, 5, $3);
                }
                case TEXTS: {
                    // TEXTS 字段实际上存储的是存储内容的页号
                    attr_info_init(&attribute, CONTEXT->id, $2, sizeof(TextHeader) + 1, $3);
                }
                break;
                default: {
                    attr_info_init(&attribute, CONTEXT->id, $2, 5, $3);
                }
            }
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            CONTEXT->value_length[0]++;
        }
    ;

nullable:
    /* empty */ { $$ = 0; }
    | NULLABLE { $$ = 1; }
    | NOT NULL_T { $$ = 0; }
    ;

number:
        NUMBER {$$ = $1;}
        ;
type:
    INT_T { $$ = INTS; }
       | FLOAT_T { $$ = FLOATS; }
       | DATE_T { $$ = DATES; }
       | STRING_T { $$ = CHARS; }
       | TEXT_T { $$ = TEXTS; }
       ;
ID_get:
    ID 
    {
        char *temp=$1; 
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
    ;

    
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list insert_rbrace tuple_list SEMICOLON
        {
            CONTEXT->ssql->flag=SCF_INSERT; //"insert";
            inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->tuples, CONTEXT->tuple_num);
            // 临时变量清零
            CONTEXT->value_length[0] = 0;
            CONTEXT->tuple_num = 0;
    };

tuple_list:
    | COMMA LBRACE value value_list insert_rbrace tuple_list {
    }

insert_rbrace:
    RBRACE {
        // 此规则用于表明读取到一个要 insert 的 tuple，并提高此操作的优先级
        InsertTuple tuple;
        insert_tuple_init(&tuple, CONTEXT->values, CONTEXT->value_length[0]);
        CONTEXT->tuples[CONTEXT->tuple_num++] = tuple;
        CONTEXT->value_length[0] = 0;
    }

value_list:
    /* empty */
    | COMMA value value_list  { 
          // CONTEXT->values[CONTEXT->value_length++] = *$2;
      };

value:
    NULL_T {
        value_init_null(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++]);
    }
    |NUMBER{
        value_init_integer(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], $1);
    }
    |FLOAT{
        value_init_float(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], $1);
    }
    |SSS {
        $1 = substr($1,1,strlen($1)-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], $1);
    };

delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
        {
            CONTEXT->ssql->flag = SCF_DELETE;//"delete";
            deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
            deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
        {
            CONTEXT->ssql->flag = SCF_UPDATE;//"update";
            Value *value = &CONTEXT->values[0];
            updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
        }
    ;

select:				/*  select 语句的语法解析树*/
     select_begin select_attr FROM ID rel_list where group order SEMICOLON
     {
	    selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $4);
	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
	    	CONTEXT->condition_length[CONTEXT->select_length]);
        CONTEXT->ssql->flag=SCF_SELECT;//"select";

        //临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length]=0;
        CONTEXT->from_length[CONTEXT->select_length]=0;
        CONTEXT->select_length--;
        CONTEXT->value_length[CONTEXT->select_length] = 0;

        assert(CONTEXT->select_length == 0);
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[1];
        memset(&CONTEXT->selects[1], 0, sizeof(Selects));
    }
    | select_begin select_attr FROM ID INNER JOIN ID ON condition condition_list join_list where SEMICOLON
    {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $7);
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $4);
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
            CONTEXT->condition_length[CONTEXT->select_length]);
        CONTEXT->ssql->flag=SCF_SELECT;//"select";
        // CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

        //临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length]=0;
        CONTEXT->from_length[CONTEXT->select_length]=0;
        CONTEXT->select_length--;
        CONTEXT->value_length[CONTEXT->select_length] = 0;

        assert(CONTEXT->select_length == 0);
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[1];
        memset(&CONTEXT->selects[1], 0, sizeof(Selects));
    }
    ;

select_begin:
    SELECT
    	{
    	CONTEXT->select_length++;
    };

group:
    /* empty */
    | GROUP BY ID group_attr_list {
	RelAttr attr;
	relation_attr_init(&attr, NULL, $3);
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | GROUP BY ID DOT ID group_attr_list {
	RelAttr attr;
	relation_attr_init(&attr, $3, $5);
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    ;

group_attr_list:
    /* empty */
    | COMMA ID group_attr_list {
	RelAttr attr;
	relation_attr_init(&attr, NULL, $2);
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | COMMA ID DOT ID group_attr_list {
	RelAttr attr;
	relation_attr_init(&attr, $2, $4);
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    ;

order:
    /* empty */
    | ORDER BY ID order_type order_attr_list {
        RelAttr attr;
        relation_attr_init(&attr, NULL, $3);
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, $4);
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
    | ORDER BY ID DOT ID order_type order_attr_list {
        RelAttr attr;
        relation_attr_init(&attr, $3, $5);
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, $6);
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
    ;

order_attr_list:
    /* empty */
    | COMMA ID order_type order_attr_list {
        RelAttr attr;
        relation_attr_init(&attr, NULL, $2);
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, $3);
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
    | COMMA ID DOT ID order_type order_attr_list {
        RelAttr attr;
        relation_attr_init(&attr, $2, $4);
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, $5);
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
    ;

order_type:
    /* empty */ { $$ = AscOrder; }
    | ASC { $$ = AscOrder; }
    | DESC { $$ = DescOrder; };

join_list:
    /* empty */
    | INNER JOIN ID ON condition condition_list join_list
    {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $3);
    };

select_attr:
    STAR {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | ID attr_list {
        RelAttr attr;
        relation_attr_init(&attr, NULL, $1);
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | ID DOT STAR attr_list {
        RelAttr attr;
        relation_attr_init(&attr, $1, "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | ID DOT ID attr_list {
        RelAttr attr;
        relation_attr_init(&attr, $1, $3);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | aggregation LBRACE ID RBRACE attr_list {
        RelAttr attr;
        // TODO: 更完善地支持 COUNT(expression) 聚合函数（ALL 和 DISTINCT）
        relation_attr_init_with_aggregation(&attr, NULL, $3, $1);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | aggregation LBRACE ID DOT ID RBRACE attr_list {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, $3, $5, $1);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | aggregation LBRACE STAR RBRACE attr_list {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", $1);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | aggregation LBRACE NUMBER RBRACE attr_list {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, $3, $1);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    ;

attr_list:
    /* empty */
    | COMMA ID attr_list {
        RelAttr attr;
        relation_attr_init(&attr, NULL, $2);
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | COMMA ID DOT ID attr_list {
        RelAttr attr;
        relation_attr_init(&attr, $2, $4);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
     | COMMA ID DOT STAR attr_list {
        RelAttr attr;
        relation_attr_init(&attr, $2, "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
      }
    | COMMA aggregation LBRACE ID RBRACE attr_list {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, $4, $2);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | COMMA aggregation LBRACE ID DOT ID RBRACE attr_list {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, $4, $6, $2);
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | COMMA aggregation LBRACE STAR RBRACE attr_list {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", $2);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | COMMA aggregation LBRACE NUMBER RBRACE attr_list {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, $4, $2);
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    ;

rel_list:
    /* empty */
    | COMMA ID rel_list {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $2);
    }
    ;
where:
    /* empty */ 
    | WHERE condition condition_list {
     }
    ;
condition_list:
    /* empty */
    | AND condition condition_list {
     }
    ;
condition:
    ID comOp value 
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, $1);

            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, $2, 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
        |value comOp value 
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 2];
            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, $2, 0, NULL, left_value, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
        |ID comOp ID 
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, $1);
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, $3);

            Condition condition;
            condition_init(&condition, $2, 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

        }
    |value comOp ID
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, $3);

            Condition condition;
            condition_init(&condition, $2, 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
    |ID DOT ID comOp value
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, $1, $3);
            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, $4, 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
    |value comOp ID DOT ID
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            RelAttr right_attr;
            relation_attr_init(&right_attr, $3, $5);

            Condition condition;
            condition_init(&condition, $2, 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
    |ID DOT ID comOp ID DOT ID
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, $1, $3);
            RelAttr right_attr;
            relation_attr_init(&right_attr, $5, $7);

            Condition condition;
            condition_init(&condition, $4, 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
    |ID comOp LBRACE select_begin select_attr FROM ID rel_list where RBRACE
    	{
    	    selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $7);
	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
	    CONTEXT->condition_length[CONTEXT->select_length]);


	    //临时变量清零
	    CONTEXT->condition_length[CONTEXT->select_length]=0;
	    CONTEXT->from_length[CONTEXT->select_length]=0;
	    CONTEXT->value_length[CONTEXT->select_length] = 0;
	    CONTEXT->select_length--;

	    RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, $1);
	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
	    	CONTEXT->selects[CONTEXT->select_length+1]);
	    Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

	    Condition condition;
	    condition_init(&condition, $2, 1, &left_attr, NULL, 2, NULL, right_value);
	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

	    //处理子查询内存
	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
    |ID DOT ID comOp LBRACE select_begin select_attr FROM ID rel_list where RBRACE
    {
            selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $9);
    	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
    	    CONTEXT->condition_length[CONTEXT->select_length]);


    	    //临时变量清零
    	    CONTEXT->condition_length[CONTEXT->select_length]=0;
    	    CONTEXT->from_length[CONTEXT->select_length]=0;
    	    CONTEXT->value_length[CONTEXT->select_length] = 0;
    	    CONTEXT->select_length--;

    	    RelAttr left_attr;
                relation_attr_init(&left_attr, $1, $3);
    	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
    	    	CONTEXT->selects[CONTEXT->select_length+1]);
    	    Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

    	    Condition condition;
    	    condition_init(&condition, $4, 1, &left_attr, NULL, 2, NULL, right_value);
    	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

    	    //处理子查询内存
    	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
    |LBRACE select_begin select_attr FROM ID rel_list where RBRACE comOp ID
    {
    	    selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $5);
	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
	    CONTEXT->condition_length[CONTEXT->select_length]);


	    //临时变量清零
	    CONTEXT->condition_length[CONTEXT->select_length]=0;
	    CONTEXT->from_length[CONTEXT->select_length]=0;
	    CONTEXT->value_length[CONTEXT->select_length] = 0;
	    CONTEXT->select_length--;

	    RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $10);
	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
		CONTEXT->selects[CONTEXT->select_length+1]);
	    Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

	    Condition condition;
	    condition_init(&condition, $9, 2, NULL, left_value, 1, &right_attr, NULL);
	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

	    //处理子查询内存
	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
    |LBRACE select_begin select_attr FROM ID rel_list where RBRACE comOp ID DOT ID
    {
            selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $5);
    	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
    	    CONTEXT->condition_length[CONTEXT->select_length]);


    	    //临时变量清零
    	    CONTEXT->condition_length[CONTEXT->select_length]=0;
    	    CONTEXT->from_length[CONTEXT->select_length]=0;
    	    CONTEXT->value_length[CONTEXT->select_length] = 0;
    	    CONTEXT->select_length--;

    	    RelAttr right_attr;
    		relation_attr_init(&right_attr, $10, $12);
    	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
    		CONTEXT->selects[CONTEXT->select_length+1]);
    	    Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

    	    Condition condition;
    	    condition_init(&condition, $9, 2, NULL, left_value, 1, &right_attr, NULL);
    	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

    	    //处理子查询内存
    	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
    ;

comOp:
        EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IS_ { $$ = IS; }
    | IS_ NOT { $$ = IS_NOT; }
    | IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN_OP; }
    ;

aggregation:
    COUNT { $$ = CountAggregate; }
    | SUM { $$ = SumAggregate; }
    | AVG { $$ = AvgAggregate; }
    | MAX { $$ = MaxAggregate; }
    | MIN { $$ = MinAggregate; }
    ;

load_data:
        LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
        {
          CONTEXT->ssql->flag = SCF_LOAD_DATA;
            load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
        }
        ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
    ParserContext context;
    memset(&context, 0, sizeof(context));

    yyscan_t scanner;
    yylex_init_extra(&context, &scanner);
    context.ssql = sqls;
    scan_string(s, scanner);
    int result = yyparse(scanner);
    yylex_destroy(scanner);
    return result;
}
