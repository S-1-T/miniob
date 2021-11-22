/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    SELECT = 264,                  /* SELECT  */
    DESC = 265,                    /* DESC  */
    SHOW = 266,                    /* SHOW  */
    SYNC = 267,                    /* SYNC  */
    INSERT = 268,                  /* INSERT  */
    DELETE = 269,                  /* DELETE  */
    UPDATE = 270,                  /* UPDATE  */
    LBRACE = 271,                  /* LBRACE  */
    RBRACE = 272,                  /* RBRACE  */
    COMMA = 273,                   /* COMMA  */
    TRX_BEGIN = 274,               /* TRX_BEGIN  */
    TRX_COMMIT = 275,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 276,            /* TRX_ROLLBACK  */
    INT_T = 277,                   /* INT_T  */
    STRING_T = 278,                /* STRING_T  */
    FLOAT_T = 279,                 /* FLOAT_T  */
    DATE_T = 280,                  /* DATE_T  */
    TEXT_T = 281,                  /* TEXT_T  */
    HELP = 282,                    /* HELP  */
    EXIT = 283,                    /* EXIT  */
    DOT = 284,                     /* DOT  */
    INTO = 285,                    /* INTO  */
    VALUES = 286,                  /* VALUES  */
    FROM = 287,                    /* FROM  */
    WHERE = 288,                   /* WHERE  */
    AND = 289,                     /* AND  */
    SET = 290,                     /* SET  */
    ON = 291,                      /* ON  */
    LOAD = 292,                    /* LOAD  */
    DATA = 293,                    /* DATA  */
    INFILE = 294,                  /* INFILE  */
    UNIQUE = 295,                  /* UNIQUE  */
    EQ = 296,                      /* EQ  */
    LT = 297,                      /* LT  */
    GT = 298,                      /* GT  */
    LE = 299,                      /* LE  */
    GE = 300,                      /* GE  */
    NE = 301,                      /* NE  */
    COUNT = 302,                   /* COUNT  */
    SUM = 303,                     /* SUM  */
    AVG = 304,                     /* AVG  */
    MAX = 305,                     /* MAX  */
    MIN = 306,                     /* MIN  */
    INNER = 307,                   /* INNER  */
    JOIN = 308,                    /* JOIN  */
    ORDER = 309,                   /* ORDER  */
    BY = 310,                      /* BY  */
    ASC = 311,                     /* ASC  */
    IS_ = 312,                     /* IS_  */
    NOT = 313,                     /* NOT  */
    NULL_T = 314,                  /* NULL_T  */
    NULLABLE = 315,                /* NULLABLE  */
    IN = 316,                      /* IN  */
    GROUP = 317,                   /* GROUP  */
    NUMBER = 318,                  /* NUMBER  */
    FLOAT = 319,                   /* FLOAT  */
    ID = 320,                      /* ID  */
    PATH = 321,                    /* PATH  */
    SSS = 322,                     /* SSS  */
    STAR = 323,                    /* STAR  */
    STRING_V = 324                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 138 "yacc_sql.y"

  struct _Attr *attr;
  struct _Expression *expression1;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _InsertTuple *tuples1;
  char *string;
  int number;
  float floats;
  char *position;

#line 145 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
