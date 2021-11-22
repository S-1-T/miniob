/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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


#line 141 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 26,                    /* TEXT_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_SET = 35,                       /* SET  */
  YYSYMBOL_ON = 36,                        /* ON  */
  YYSYMBOL_LOAD = 37,                      /* LOAD  */
  YYSYMBOL_DATA = 38,                      /* DATA  */
  YYSYMBOL_INFILE = 39,                    /* INFILE  */
  YYSYMBOL_UNIQUE = 40,                    /* UNIQUE  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_COUNT = 47,                     /* COUNT  */
  YYSYMBOL_SUM = 48,                       /* SUM  */
  YYSYMBOL_AVG = 49,                       /* AVG  */
  YYSYMBOL_MAX = 50,                       /* MAX  */
  YYSYMBOL_MIN = 51,                       /* MIN  */
  YYSYMBOL_INNER = 52,                     /* INNER  */
  YYSYMBOL_JOIN = 53,                      /* JOIN  */
  YYSYMBOL_ORDER = 54,                     /* ORDER  */
  YYSYMBOL_BY = 55,                        /* BY  */
  YYSYMBOL_ASC = 56,                       /* ASC  */
  YYSYMBOL_IS_ = 57,                       /* IS_  */
  YYSYMBOL_NOT = 58,                       /* NOT  */
  YYSYMBOL_NULL_T = 59,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 60,                  /* NULLABLE  */
  YYSYMBOL_IN = 61,                        /* IN  */
  YYSYMBOL_GROUP = 62,                     /* GROUP  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_STRING_V = 69,                  /* STRING_V  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '+'  */
  YYSYMBOL_72_ = 72,                       /* '*'  */
  YYSYMBOL_73_ = 73,                       /* '/'  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command = 76,                   /* command  */
  YYSYMBOL_exit = 77,                      /* exit  */
  YYSYMBOL_help = 78,                      /* help  */
  YYSYMBOL_sync = 79,                      /* sync  */
  YYSYMBOL_begin = 80,                     /* begin  */
  YYSYMBOL_commit = 81,                    /* commit  */
  YYSYMBOL_rollback = 82,                  /* rollback  */
  YYSYMBOL_drop_table = 83,                /* drop_table  */
  YYSYMBOL_show_tables = 84,               /* show_tables  */
  YYSYMBOL_desc_table = 85,                /* desc_table  */
  YYSYMBOL_create_index = 86,              /* create_index  */
  YYSYMBOL_index_attr_list = 87,           /* index_attr_list  */
  YYSYMBOL_drop_index = 88,                /* drop_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_nullable = 92,                  /* nullable  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_ID_get = 95,                    /* ID_get  */
  YYSYMBOL_insert = 96,                    /* insert  */
  YYSYMBOL_tuple_list = 97,                /* tuple_list  */
  YYSYMBOL_insert_rbrace = 98,             /* insert_rbrace  */
  YYSYMBOL_value_list = 99,                /* value_list  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_update = 102,                   /* update  */
  YYSYMBOL_select = 103,                   /* select  */
  YYSYMBOL_select_begin = 104,             /* select_begin  */
  YYSYMBOL_group = 105,                    /* group  */
  YYSYMBOL_group_attr_list = 106,          /* group_attr_list  */
  YYSYMBOL_order = 107,                    /* order  */
  YYSYMBOL_order_attr_list = 108,          /* order_attr_list  */
  YYSYMBOL_order_type = 109,               /* order_type  */
  YYSYMBOL_join_list = 110,                /* join_list  */
  YYSYMBOL_select_attr = 111,              /* select_attr  */
  YYSYMBOL_attr_list = 112,                /* attr_list  */
  YYSYMBOL_rel_list = 113,                 /* rel_list  */
  YYSYMBOL_where = 114,                    /* where  */
  YYSYMBOL_condition_list = 115,           /* condition_list  */
  YYSYMBOL_condition = 116,                /* condition  */
  YYSYMBOL_expression = 117,               /* expression  */
  YYSYMBOL_comOp = 118,                    /* comOp  */
  YYSYMBOL_aggregation = 119,              /* aggregation  */
  YYSYMBOL_load_data = 120                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  295

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    72,    71,     2,    70,     2,    73,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   174,   174,   176,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   200,   205,   210,   216,   222,   228,   234,   240,   246,
     253,   261,   271,   273,   279,   286,   294,   296,   300,   307,
     342,   343,   344,   348,   351,   352,   353,   354,   355,   358,
     367,   376,   377,   381,   389,   391,   396,   399,   402,   405,
     411,   421,   432,   449,   471,   476,   478,   483,   490,   492,
     497,   504,   506,   513,   522,   524,   531,   541,   542,   543,
     545,   547,   553,   558,   563,   568,   573,   579,   584,   589,
     596,   598,   603,   608,   613,   618,   623,   628,   635,   637,
     641,   643,   646,   648,   652,   659,   663,   667,   671,   675,
     680,   686,   692,   717,   718,   719,   720,   721,   722,   723,
     724,   725,   726,   730,   731,   732,   733,   734,   738
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "UNIQUE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "COUNT", "SUM", "AVG", "MAX", "MIN", "INNER", "JOIN",
  "ORDER", "BY", "ASC", "IS_", "NOT", "NULL_T", "NULLABLE", "IN", "GROUP",
  "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "'-'", "'+'",
  "'*'", "'/'", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "index_attr_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "nullable", "number", "type", "ID_get",
  "insert", "tuple_list", "insert_rbrace", "value_list", "value", "delete",
  "update", "select", "select_begin", "group", "group_attr_list", "order",
  "order_attr_list", "order_type", "join_list", "select_attr", "attr_list",
  "rel_list", "where", "condition_list", "condition", "expression",
  "comOp", "aggregation", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-235)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -235,    85,  -235,     3,    95,  -235,   -46,    27,    41,    38,
      42,    18,    81,    89,   106,   116,   117,    94,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -235,  -235,   -26,  -235,    23,    66,   127,
      77,    84,   143,   144,  -235,    86,    92,   115,  -235,  -235,
    -235,  -235,  -235,   120,  -235,  -235,  -235,  -235,  -235,    51,
    -235,   128,   160,   161,   142,   114,   177,   145,  -235,  -235,
     151,   150,   119,   118,   -19,   -48,  -235,   121,    53,   122,
     123,   153,  -235,   125,   175,    -8,   189,   152,   164,    58,
     179,   178,   178,    -5,   180,    24,   181,  -235,   182,   140,
     183,   136,   199,    70,   194,  -235,  -235,  -235,   176,  -235,
    -235,   170,    82,  -235,    70,   200,    49,  -235,    93,  -235,
    -235,   146,   154,   150,   178,   178,   147,   178,   122,   191,
    -235,  -235,  -235,  -235,  -235,    -6,   148,   193,  -235,   192,
     -26,   149,    -8,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
     157,   155,  -235,    -8,    -8,    -8,    -8,    -8,   150,   156,
     178,   178,   201,    50,   202,   204,   158,   162,  -235,  -235,
     203,  -235,   182,   214,   163,   166,  -235,  -235,   209,   165,
      70,   211,   197,  -235,   170,  -235,  -235,   -23,   -23,  -235,
    -235,   102,   228,   229,  -235,  -235,   178,   178,   168,   178,
    -235,   198,   184,   186,   178,  -235,  -235,  -235,   218,  -235,
     171,   220,   209,   192,  -235,   223,   173,  -235,  -235,  -235,
    -235,  -235,   225,  -235,    -8,   185,   188,   241,  -235,    78,
     209,   242,   230,  -235,   232,   243,   204,   178,   170,    64,
     187,  -235,  -235,  -235,  -235,   246,    70,  -235,   150,  -235,
     205,   190,   195,  -235,     4,  -235,   192,   234,   206,   150,
      73,   235,  -235,   196,  -235,   236,   211,  -235,   207,   253,
     208,  -235,  -235,     6,   210,  -235,   223,   222,  -235,   235,
     236,     8,  -235,    -8,  -235,  -235,   212,   236,   170,     6,
    -235,   205,   236,  -235,  -235
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,     0,    18,     0,     0,     0,
       0,     0,     0,     0,    23,     0,     0,     0,    24,    25,
      26,    22,    21,     0,   123,   124,   125,   126,   127,    90,
      82,     0,     0,     0,     0,     0,     0,     0,    29,    28,
       0,   100,     0,     0,     0,     0,    83,     0,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,     0,    90,
       0,    90,    90,    98,     0,     0,     0,    49,    36,     0,
       0,     0,     0,     0,     0,    56,    57,    58,   110,    59,
     109,   102,     0,    60,     0,     0,     0,    91,     0,    85,
      84,     0,     0,   100,    90,    90,     0,    90,     0,     0,
      44,    47,    45,    46,    48,    40,     0,     0,    34,    54,
       0,     0,     0,   101,   113,   114,   115,   116,   117,   118,
     119,     0,   121,     0,     0,     0,     0,     0,   100,     0,
      90,    90,     0,     0,     0,    98,     0,    65,    89,    86,
       0,    88,    36,     0,     0,     0,    41,    39,    32,     0,
       0,     0,     0,   111,   102,   120,   122,   106,   105,   107,
     108,   104,     0,     0,    92,    93,    90,    90,     0,    90,
      99,     0,     0,    71,    90,    37,    35,    43,     0,    42,
       0,     0,    32,    54,    53,    51,     0,   103,    61,   128,
      97,    94,     0,    96,     0,     0,     0,     0,    87,    40,
      32,     0,     0,    55,     0,     0,    98,    90,   102,    68,
       0,    62,    38,    33,    30,     0,     0,    50,   100,    95,
      80,     0,     0,    66,    77,    31,    54,     0,     0,   100,
      68,    68,    79,     0,    78,    74,     0,   112,     0,     0,
       0,    69,    67,    77,     0,    72,    51,     0,    63,    68,
      74,    77,    52,     0,    70,    73,     0,    74,   102,    77,
      75,    80,    74,    81,    76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,  -235,
    -235,  -235,  -235,  -164,  -235,  -235,    90,   135,    35,  -235,
    -235,  -235,  -235,   -11,     0,  -198,  -102,  -235,  -235,  -235,
     167,  -235,  -234,  -235,  -217,  -208,   -24,   129,   -89,  -159,
    -118,  -177,  -138,    14,  -235,   213,  -235
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   211,    29,    30,   129,    98,   177,   208,
     135,    99,    31,   235,   215,   181,   110,    32,    33,    34,
      35,   203,   253,   227,   275,   265,   259,    61,    76,   123,
      86,   143,   111,   112,   157,    62,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     117,   139,   119,   120,   184,   167,   200,   217,   104,    37,
     174,    38,   158,   121,   262,   233,   262,    91,   262,    42,
      92,    54,    55,    56,    57,    58,   271,   272,    54,    55,
      56,    57,    58,   263,    43,   168,   169,   286,   171,    59,
     192,   125,    60,    39,    44,   284,    89,   122,   232,   155,
     156,   105,   175,   126,   176,   106,   107,   108,   266,   109,
     264,   250,   264,   285,   264,   280,   243,   197,    45,    74,
     290,   194,   195,   287,    46,   294,    74,   248,   213,   198,
      75,   292,   251,    47,    48,     2,   238,   116,    63,     3,
       4,   251,    49,   252,     5,     6,     7,     8,     9,    10,
      11,    40,   270,    41,    12,    13,    14,   220,   221,    50,
     223,   291,    15,    16,   160,   228,    94,   161,    95,    51,
      52,    96,    17,   144,   145,   146,   147,   148,   149,   105,
     257,    64,    53,   106,   107,    65,   175,   109,   176,   150,
     151,   269,    66,   152,   256,   288,    68,    69,   249,    67,
      72,    70,   153,   154,   155,   156,   162,    71,   163,    73,
      77,   164,   130,   131,   132,   133,   134,   187,   188,   189,
     190,   191,   153,   154,   155,   156,    78,    79,    80,    81,
      82,    83,    84,    85,    87,    88,    93,    97,   100,   101,
     102,   103,   113,   114,   115,   118,    74,   124,   127,   136,
     128,   137,   138,     5,   142,   141,   159,   166,   173,   179,
     180,   165,   170,   178,   183,   185,   186,   206,   196,   199,
     204,   193,   121,   201,   202,   209,   207,   210,   214,   216,
     212,   218,   219,   222,   224,   229,   230,   231,   236,   225,
     226,   234,   237,   240,   241,   244,   247,   245,   246,   255,
     239,   267,   254,   251,   274,   260,   278,   258,   283,   268,
     261,   273,   205,   172,   242,   282,   276,   293,     0,   182,
       0,   140,   277,   279,     0,   281,     0,   289,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90
};

static const yytype_int16 yycheck[] =
{
      89,   103,    91,    92,   142,   123,   165,   184,    16,     6,
      16,     8,   114,    18,    10,   213,    10,    65,    10,    65,
      68,    47,    48,    49,    50,    51,   260,   261,    47,    48,
      49,    50,    51,    29,     7,   124,   125,    29,   127,    65,
     158,    17,    68,    40,     3,   279,    65,    52,   212,    72,
      73,    59,    58,    29,    60,    63,    64,    65,   256,    67,
      56,   238,    56,   280,    56,   273,   230,    17,    30,    18,
     287,   160,   161,   281,    32,   292,    18,   236,   180,    29,
      29,   289,    18,    65,     3,     0,   224,    29,    65,     4,
       5,    18,     3,    29,     9,    10,    11,    12,    13,    14,
      15,     6,    29,     8,    19,    20,    21,   196,   197,     3,
     199,   288,    27,    28,    65,   204,    63,    68,    65,     3,
       3,    68,    37,    41,    42,    43,    44,    45,    46,    59,
     248,    65,    38,    63,    64,     8,    58,    67,    60,    57,
      58,   259,    65,    61,   246,   283,     3,     3,   237,    65,
      35,    65,    70,    71,    72,    73,    63,    65,    65,    39,
      32,    68,    22,    23,    24,    25,    26,   153,   154,   155,
     156,   157,    70,    71,    72,    73,    16,    16,    36,    65,
       3,    36,    31,    33,    65,    67,    65,    65,    65,    36,
      65,    16,     3,    41,    30,    16,    18,    17,    17,    16,
      18,    65,     3,     9,    34,    29,     6,    53,    17,    16,
      18,    65,    65,    65,    65,    58,    61,     3,    17,    17,
      17,    65,    18,    65,    62,    59,    63,    18,    17,    32,
      65,     3,     3,    65,    36,    17,    65,    17,    65,    55,
      54,    18,    17,    55,     3,     3,     3,    17,    16,     3,
      65,    17,    65,    18,    18,    65,     3,    52,    36,    53,
      65,    65,   172,   128,   229,   276,   266,   291,    -1,   140,
      -1,   104,    65,    65,    -1,    65,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    75,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    88,
      89,    96,   101,   102,   103,   104,   120,     6,     8,    40,
       6,     8,    65,     7,     3,    30,    32,    65,     3,     3,
       3,     3,     3,    38,    47,    48,    49,    50,    51,    65,
      68,   111,   119,    65,    65,     8,    65,    65,     3,     3,
      65,    65,    35,    39,    18,    29,   112,    32,    16,    16,
      36,    65,     3,    36,    31,    33,   114,    65,    67,    65,
     119,    65,    68,    65,    63,    65,    68,    65,    91,    95,
      65,    36,    65,    16,    16,    59,    63,    64,    65,    67,
     100,   116,   117,     3,    41,    30,    29,   112,    16,   112,
     112,    18,    52,   113,    17,    17,    29,    17,    18,    90,
      22,    23,    24,    25,    26,    94,    16,    65,     3,   100,
     104,    29,    34,   115,    41,    42,    43,    44,    45,    46,
      57,    58,    61,    70,    71,    72,    73,   118,   100,     6,
      65,    68,    63,    65,    68,    65,    53,   114,   112,   112,
      65,   112,    91,    17,    16,    58,    60,    92,    65,    16,
      18,    99,   111,    65,   116,    58,    61,   117,   117,   117,
     117,   117,   114,    65,   112,   112,    17,    17,    29,    17,
     113,    65,    62,   105,    17,    90,     3,    63,    93,    59,
      18,    87,    65,   100,    17,    98,    32,   115,     3,     3,
     112,   112,    65,   112,    36,    55,    54,   107,   112,    17,
      65,    17,    87,    99,    18,    97,    65,    17,   116,    65,
      55,     3,    92,    87,     3,    17,    16,     3,   113,   112,
     115,    18,    29,   106,    65,     3,   100,   114,    52,   110,
      65,    65,    10,    29,    56,   109,    99,    17,    53,   114,
      29,   106,   106,    65,    18,   108,    98,    65,     3,    65,
     109,    65,    97,    36,   106,   108,    29,   109,   116,    65,
     108,   115,   109,   110,   108
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    86,    87,    87,    88,    89,    90,    90,    91,    91,
      92,    92,    92,    93,    94,    94,    94,    94,    94,    95,
      96,    97,    97,    98,    99,    99,   100,   100,   100,   100,
     101,   102,   103,   103,   104,   105,   105,   105,   106,   106,
     106,   107,   107,   107,   108,   108,   108,   109,   109,   109,
     110,   110,   111,   111,   111,   111,   111,   111,   111,   111,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   119,   119,   120
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     6,     8,     0,     3,     6,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
      10,     0,     6,     1,     0,     3,     1,     1,     1,     1,
       5,     8,     9,    13,     1,     0,     4,     6,     0,     3,
       5,     0,     5,     7,     0,     4,     6,     0,     1,     1,
       0,     7,     1,     2,     4,     4,     5,     7,     5,     5,
       0,     3,     5,     5,     6,     8,     6,     6,     0,     3,
       0,     3,     0,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     8,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     1,     1,     1,     1,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 21: /* exit: EXIT SEMICOLON  */
#line 200 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1454 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 205 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1462 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 210 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 216 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1478 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 222 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1486 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 228 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1494 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 234 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1503 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 240 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1511 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 246 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1520 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 254 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-3].string);
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 0);
            CONTEXT->index_attr_num = 0;
        }
#line 1532 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 262 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-3].string);
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 1);
            CONTEXT->index_attr_num = 0;
        }
#line 1544 "yacc_sql.tab.c"
    break;

  case 33: /* index_attr_list: COMMA ID index_attr_list  */
#line 274 "yacc_sql.y"
    {
        CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-1].string);
    }
#line 1552 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID ON ID SEMICOLON  */
#line 280 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-3].string), (yyvsp[-1].string));
	}
#line 1561 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 287 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
            create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
            //临时变量清零	
            CONTEXT->value_length[0] = 0;
        }
#line 1572 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 296 "yacc_sql.y"
                                   {    }
#line 1578 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 301 "yacc_sql.y"
        {
            AttrInfo attribute;
            attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            CONTEXT->value_length[0]++;
        }
#line 1589 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type nullable  */
#line 308 "yacc_sql.y"
        {
            AttrInfo attribute;
            // 属性占用字节多一个用于表示是否为 NULL
            switch ((yyvsp[-1].number)) {
                case INTS: {
                    attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), sizeof(int) + 1, (yyvsp[0].number));
                }
                break;
                case FLOATS: {
                    attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), sizeof(float) + 1, (yyvsp[0].number));
                }
                break;
                case DATES: {
                    attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), sizeof(time_t) + 1, (yyvsp[0].number));
                }
                break;
                case CHARS: {
                    attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 5, (yyvsp[0].number));
                }
                case TEXTS: {
                    // TEXTS 字段实际上存储的是存储内容的页号
                    attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), sizeof(TextHeader) + 1, (yyvsp[0].number));
                }
                break;
                default: {
                    attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 5, (yyvsp[0].number));
                }
            }
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            CONTEXT->value_length[0]++;
        }
#line 1625 "yacc_sql.tab.c"
    break;

  case 40: /* nullable: %empty  */
#line 342 "yacc_sql.y"
                { (yyval.number) = 0; }
#line 1631 "yacc_sql.tab.c"
    break;

  case 41: /* nullable: NULLABLE  */
#line 343 "yacc_sql.y"
               { (yyval.number) = 1; }
#line 1637 "yacc_sql.tab.c"
    break;

  case 42: /* nullable: NOT NULL_T  */
#line 344 "yacc_sql.y"
                 { (yyval.number) = 0; }
#line 1643 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 348 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1649 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 351 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1655 "yacc_sql.tab.c"
    break;

  case 45: /* type: FLOAT_T  */
#line 352 "yacc_sql.y"
                 { (yyval.number) = FLOATS; }
#line 1661 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 353 "yacc_sql.y"
                { (yyval.number) = DATES; }
#line 1667 "yacc_sql.tab.c"
    break;

  case 47: /* type: STRING_T  */
#line 354 "yacc_sql.y"
                  { (yyval.number) = CHARS; }
#line 1673 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 355 "yacc_sql.y"
                { (yyval.number) = TEXTS; }
#line 1679 "yacc_sql.tab.c"
    break;

  case 49: /* ID_get: ID  */
#line 359 "yacc_sql.y"
    {
        char *temp=(yyvsp[0].string); 
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1688 "yacc_sql.tab.c"
    break;

  case 50: /* insert: INSERT INTO ID VALUES LBRACE value value_list insert_rbrace tuple_list SEMICOLON  */
#line 368 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_INSERT; //"insert";
            inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->tuples, CONTEXT->tuple_num);
            // 临时变量清零
            CONTEXT->value_length[0] = 0;
            CONTEXT->tuple_num = 0;
    }
#line 1700 "yacc_sql.tab.c"
    break;

  case 52: /* tuple_list: COMMA LBRACE value value_list insert_rbrace tuple_list  */
#line 377 "yacc_sql.y"
                                                             {
    }
#line 1707 "yacc_sql.tab.c"
    break;

  case 53: /* insert_rbrace: RBRACE  */
#line 381 "yacc_sql.y"
           {
        // 此规则用于表明读取到一个要 insert 的 tuple，并提高此操作的优先级
        InsertTuple tuple;
        insert_tuple_init(&tuple, CONTEXT->values, CONTEXT->value_length[0]);
        CONTEXT->tuples[CONTEXT->tuple_num++] = tuple;
        CONTEXT->value_length[0] = 0;
    }
#line 1719 "yacc_sql.tab.c"
    break;

  case 55: /* value_list: COMMA value value_list  */
#line 391 "yacc_sql.y"
                              { 
          // CONTEXT->values[CONTEXT->value_length++] = *$2;
      }
#line 1727 "yacc_sql.tab.c"
    break;

  case 56: /* value: NULL_T  */
#line 396 "yacc_sql.y"
           {
        value_init_null(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++]);
    }
#line 1735 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 399 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].number));
    }
#line 1743 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 402 "yacc_sql.y"
          {
        value_init_float(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].floats));
    }
#line 1751 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 405 "yacc_sql.y"
         {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].string));
    }
#line 1760 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 412 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_DELETE;//"delete";
            deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
            deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
    }
#line 1772 "yacc_sql.tab.c"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 422 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_UPDATE;//"update";
            Value *value = &CONTEXT->values[0];
            updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
        }
#line 1784 "yacc_sql.tab.c"
    break;

  case 62: /* select: select_begin select_attr FROM ID rel_list where group order SEMICOLON  */
#line 433 "yacc_sql.y"
     {
	    selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string));
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
#line 1805 "yacc_sql.tab.c"
    break;

  case 63: /* select: select_begin select_attr FROM ID INNER JOIN ID ON condition condition_list join_list where SEMICOLON  */
#line 450 "yacc_sql.y"
    {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-6].string));
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-9].string));
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
#line 1828 "yacc_sql.tab.c"
    break;

  case 64: /* select_begin: SELECT  */
#line 472 "yacc_sql.y"
        {
    	CONTEXT->select_length++;
    }
#line 1836 "yacc_sql.tab.c"
    break;

  case 66: /* group: GROUP BY ID group_attr_list  */
#line 478 "yacc_sql.y"
                                  {
	RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1846 "yacc_sql.tab.c"
    break;

  case 67: /* group: GROUP BY ID DOT ID group_attr_list  */
#line 483 "yacc_sql.y"
                                         {
	RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1856 "yacc_sql.tab.c"
    break;

  case 69: /* group_attr_list: COMMA ID group_attr_list  */
#line 492 "yacc_sql.y"
                               {
	RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1866 "yacc_sql.tab.c"
    break;

  case 70: /* group_attr_list: COMMA ID DOT ID group_attr_list  */
#line 497 "yacc_sql.y"
                                      {
	RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1876 "yacc_sql.tab.c"
    break;

  case 72: /* order: ORDER BY ID order_type order_attr_list  */
#line 506 "yacc_sql.y"
                                             {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 1888 "yacc_sql.tab.c"
    break;

  case 73: /* order: ORDER BY ID DOT ID order_type order_attr_list  */
#line 513 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 1900 "yacc_sql.tab.c"
    break;

  case 75: /* order_attr_list: COMMA ID order_type order_attr_list  */
#line 524 "yacc_sql.y"
                                          {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 1912 "yacc_sql.tab.c"
    break;

  case 76: /* order_attr_list: COMMA ID DOT ID order_type order_attr_list  */
#line 531 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 1924 "yacc_sql.tab.c"
    break;

  case 77: /* order_type: %empty  */
#line 541 "yacc_sql.y"
                { (yyval.number) = AscOrder; }
#line 1930 "yacc_sql.tab.c"
    break;

  case 78: /* order_type: ASC  */
#line 542 "yacc_sql.y"
          { (yyval.number) = AscOrder; }
#line 1936 "yacc_sql.tab.c"
    break;

  case 79: /* order_type: DESC  */
#line 543 "yacc_sql.y"
           { (yyval.number) = DescOrder; }
#line 1942 "yacc_sql.tab.c"
    break;

  case 81: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 548 "yacc_sql.y"
    {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
    }
#line 1950 "yacc_sql.tab.c"
    break;

  case 82: /* select_attr: STAR  */
#line 553 "yacc_sql.y"
         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1960 "yacc_sql.tab.c"
    break;

  case 83: /* select_attr: ID attr_list  */
#line 558 "yacc_sql.y"
                   {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1970 "yacc_sql.tab.c"
    break;

  case 84: /* select_attr: ID DOT STAR attr_list  */
#line 563 "yacc_sql.y"
                            {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1980 "yacc_sql.tab.c"
    break;

  case 85: /* select_attr: ID DOT ID attr_list  */
#line 568 "yacc_sql.y"
                          {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1990 "yacc_sql.tab.c"
    break;

  case 86: /* select_attr: aggregation LBRACE ID RBRACE attr_list  */
#line 573 "yacc_sql.y"
                                             {
        RelAttr attr;
        // TODO: 更完善地支持 COUNT(expression) 聚合函数（ALL 和 DISTINCT）
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2001 "yacc_sql.tab.c"
    break;

  case 87: /* select_attr: aggregation LBRACE ID DOT ID RBRACE attr_list  */
#line 579 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2011 "yacc_sql.tab.c"
    break;

  case 88: /* select_attr: aggregation LBRACE STAR RBRACE attr_list  */
#line 584 "yacc_sql.y"
                                               {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2021 "yacc_sql.tab.c"
    break;

  case 89: /* select_attr: aggregation LBRACE NUMBER RBRACE attr_list  */
#line 589 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2031 "yacc_sql.tab.c"
    break;

  case 91: /* attr_list: COMMA ID attr_list  */
#line 598 "yacc_sql.y"
                         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2041 "yacc_sql.tab.c"
    break;

  case 92: /* attr_list: COMMA ID DOT ID attr_list  */
#line 603 "yacc_sql.y"
                                {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2051 "yacc_sql.tab.c"
    break;

  case 93: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 608 "yacc_sql.y"
                                   {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
      }
#line 2061 "yacc_sql.tab.c"
    break;

  case 94: /* attr_list: COMMA aggregation LBRACE ID RBRACE attr_list  */
#line 613 "yacc_sql.y"
                                                   {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2071 "yacc_sql.tab.c"
    break;

  case 95: /* attr_list: COMMA aggregation LBRACE ID DOT ID RBRACE attr_list  */
#line 618 "yacc_sql.y"
                                                          {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2081 "yacc_sql.tab.c"
    break;

  case 96: /* attr_list: COMMA aggregation LBRACE STAR RBRACE attr_list  */
#line 623 "yacc_sql.y"
                                                     {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2091 "yacc_sql.tab.c"
    break;

  case 97: /* attr_list: COMMA aggregation LBRACE NUMBER RBRACE attr_list  */
#line 628 "yacc_sql.y"
                                                       {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2101 "yacc_sql.tab.c"
    break;

  case 99: /* rel_list: COMMA ID rel_list  */
#line 637 "yacc_sql.y"
                        {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
    }
#line 2109 "yacc_sql.tab.c"
    break;

  case 101: /* where: WHERE condition condition_list  */
#line 643 "yacc_sql.y"
                                     {
    }
#line 2116 "yacc_sql.tab.c"
    break;

  case 103: /* condition_list: AND condition condition_list  */
#line 648 "yacc_sql.y"
                                   {
    }
#line 2123 "yacc_sql.tab.c"
    break;

  case 104: /* condition: expression comOp expression  */
#line 652 "yacc_sql.y"
                                {
        Condition condition;
        condition_init(&condition, (yyvsp[-1].number), (yyvsp[-2].expression1), (yyvsp[0].expression1));
        CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
#line 2133 "yacc_sql.tab.c"
    break;

  case 105: /* expression: expression '+' expression  */
#line 659 "yacc_sql.y"
                                        {
        (yyval.expression1) = expression_create(EXPR, NULL, NULL, Plus, (yyvsp[-2].expression1), (yyvsp[0].expression1));
    }
#line 2141 "yacc_sql.tab.c"
    break;

  case 106: /* expression: expression '-' expression  */
#line 663 "yacc_sql.y"
                                          {
        (yyval.expression1) = expression_create(EXPR, NULL, NULL, Minus, (yyvsp[-2].expression1), (yyvsp[0].expression1));
    }
#line 2149 "yacc_sql.tab.c"
    break;

  case 107: /* expression: expression '*' expression  */
#line 667 "yacc_sql.y"
                                          {
        (yyval.expression1) = expression_create(EXPR, NULL, NULL, Mul, (yyvsp[-2].expression1), (yyvsp[0].expression1));
    }
#line 2157 "yacc_sql.tab.c"
    break;

  case 108: /* expression: expression '/' expression  */
#line 671 "yacc_sql.y"
                                          {
        (yyval.expression1) = expression_create(EXPR, NULL, NULL, Div, (yyvsp[-2].expression1), (yyvsp[0].expression1));
    }
#line 2165 "yacc_sql.tab.c"
    break;

  case 109: /* expression: value  */
#line 675 "yacc_sql.y"
            {
        Value *value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];
        (yyval.expression1) = expression_create(VAL, NULL, value, NOP, NULL, NULL);
    }
#line 2174 "yacc_sql.tab.c"
    break;

  case 110: /* expression: ID  */
#line 680 "yacc_sql.y"
         {
        RelAttr rel_attr;
        relation_attr_init(&rel_attr, NULL, (yyvsp[0].string));
        (yyval.expression1) = expression_create(ATTR, &rel_attr, NULL, NOP, NULL, NULL);
    }
#line 2184 "yacc_sql.tab.c"
    break;

  case 111: /* expression: ID DOT ID  */
#line 686 "yacc_sql.y"
                {
        RelAttr rel_attr;
        relation_attr_init(&rel_attr, (yyvsp[-2].string), (yyvsp[0].string));
        (yyval.expression1) = expression_create(ATTR, &rel_attr, NULL, NOP, NULL, NULL);
    }
#line 2194 "yacc_sql.tab.c"
    break;

  case 112: /* expression: LBRACE select_begin select_attr FROM ID rel_list where RBRACE  */
#line 692 "yacc_sql.y"
                                                                    {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-3].string));
        selects_append_conditions(
            &CONTEXT->selects[CONTEXT->select_length],
            CONTEXT->conditions[CONTEXT->select_length],
            CONTEXT->condition_length[CONTEXT->select_length]);

        //临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->from_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length[CONTEXT->select_length] = 0;
        CONTEXT->select_length--;

        value_init_select(
            &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
            CONTEXT->selects[CONTEXT->select_length+1]);
	    Value *value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];
        (yyval.expression1) = expression_create(SUB_QUERY, NULL, value, NOP, NULL, NULL);

        //处理子查询内存
        memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
#line 2221 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: EQ  */
#line 717 "yacc_sql.y"
       { (yyval.number) = EQUAL_TO; }
#line 2227 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: LT  */
#line 718 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2233 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: GT  */
#line 719 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2239 "yacc_sql.tab.c"
    break;

  case 116: /* comOp: LE  */
#line 720 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2245 "yacc_sql.tab.c"
    break;

  case 117: /* comOp: GE  */
#line 721 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2251 "yacc_sql.tab.c"
    break;

  case 118: /* comOp: NE  */
#line 722 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2257 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: IS_  */
#line 723 "yacc_sql.y"
          { (yyval.number) = IS; }
#line 2263 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: IS_ NOT  */
#line 724 "yacc_sql.y"
              { (yyval.number) = IS_NOT; }
#line 2269 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: IN  */
#line 725 "yacc_sql.y"
         { (yyval.number) = IN_OP; }
#line 2275 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: NOT IN  */
#line 726 "yacc_sql.y"
             { (yyval.number) = NOT_IN_OP; }
#line 2281 "yacc_sql.tab.c"
    break;

  case 123: /* aggregation: COUNT  */
#line 730 "yacc_sql.y"
          { (yyval.number) = CountAggregate; }
#line 2287 "yacc_sql.tab.c"
    break;

  case 124: /* aggregation: SUM  */
#line 731 "yacc_sql.y"
          { (yyval.number) = SumAggregate; }
#line 2293 "yacc_sql.tab.c"
    break;

  case 125: /* aggregation: AVG  */
#line 732 "yacc_sql.y"
          { (yyval.number) = AvgAggregate; }
#line 2299 "yacc_sql.tab.c"
    break;

  case 126: /* aggregation: MAX  */
#line 733 "yacc_sql.y"
          { (yyval.number) = MaxAggregate; }
#line 2305 "yacc_sql.tab.c"
    break;

  case 127: /* aggregation: MIN  */
#line 734 "yacc_sql.y"
          { (yyval.number) = MinAggregate; }
#line 2311 "yacc_sql.tab.c"
    break;

  case 128: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 739 "yacc_sql.y"
        {
          CONTEXT->ssql->flag = SCF_LOAD_DATA;
            load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
        }
#line 2320 "yacc_sql.tab.c"
    break;


#line 2324 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 744 "yacc_sql.y"

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
