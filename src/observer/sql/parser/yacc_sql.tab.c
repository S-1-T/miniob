/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t tuple_num;
  Value values[MAX_NUM];
  InsertTuple tuples[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  char id[MAX_NUM];
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
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->tuple_num = 0;
//  context->ssql->sstr.insertion.value_num = 0;
  context->ssql->sstr.errors = str;
  printf("parse sql failed. error=%s\n", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 132 "yacc_sql.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    TABLE = 261,
    TABLES = 262,
    INDEX = 263,
    SELECT = 264,
    DESC = 265,
    SHOW = 266,
    SYNC = 267,
    INSERT = 268,
    DELETE = 269,
    UPDATE = 270,
    LBRACE = 271,
    RBRACE = 272,
    COMMA = 273,
    TRX_BEGIN = 274,
    TRX_COMMIT = 275,
    TRX_ROLLBACK = 276,
    INT_T = 277,
    STRING_T = 278,
    FLOAT_T = 279,
    DATE_T = 280,
    HELP = 281,
    EXIT = 282,
    DOT = 283,
    INTO = 284,
    VALUES = 285,
    FROM = 286,
    WHERE = 287,
    AND = 288,
    SET = 289,
    ON = 290,
    LOAD = 291,
    DATA = 292,
    INFILE = 293,
    UNIQUE = 294,
    EQ = 295,
    LT = 296,
    GT = 297,
    LE = 298,
    GE = 299,
    NE = 300,
    COUNT = 301,
    SUM = 302,
    AVG = 303,
    MAX = 304,
    MIN = 305,
    INNER = 306,
    JOIN = 307,
    ORDER = 308,
    BY = 309,
    ASC = 310,
    NOT = 311,
    NULL_T = 312,
    NULLABLE = 313,
    NUMBER = 314,
    FLOAT = 315,
    ID = 316,
    PATH = 317,
    SSS = 318,
    STAR = 319,
    STRING_V = 320
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 126 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _InsertTuple *tuples1;
  char *string;
  int number;
  float floats;
  char *position;

#line 261 "yacc_sql.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYLAST   267

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  263

#define YYUNDEFTOK  2
#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   156,   156,   158,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   182,   187,   192,   198,   204,   210,   216,   222,   228,
     235,   240,   248,   255,   264,   266,   270,   281,   316,   317,
     318,   322,   325,   326,   327,   328,   331,   340,   349,   350,
     354,   362,   364,   369,   372,   375,   378,   384,   394,   404,
     420,   436,   438,   445,   454,   456,   463,   473,   474,   475,
     477,   479,   485,   490,   495,   500,   505,   511,   516,   521,
     528,   530,   537,   544,   551,   556,   561,   566,   573,   575,
     579,   581,   585,   587,   592,   613,   633,   653,   675,   696,
     717,   739,   740,   741,   742,   743,   744,   748,   749,   750,
     751,   752,   756
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "TABLE",
  "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD",
  "DATA", "INFILE", "UNIQUE", "EQ", "LT", "GT", "LE", "GE", "NE", "COUNT",
  "SUM", "AVG", "MAX", "MIN", "INNER", "JOIN", "ORDER", "BY", "ASC", "NOT",
  "NULL_T", "NULLABLE", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "create_table", "attr_def_list",
  "attr_def", "nullable", "number", "type", "ID_get", "insert",
  "tuple_list", "insert_rbrace", "value_list", "value", "delete", "update",
  "select", "order", "order_attr_list", "order_type", "join_list",
  "select_attr", "attr_list", "rel_list", "where", "condition_list",
  "condition", "comOp", "aggregation", "load_data", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320
};
# endif

#define YYPACT_NINF (-216)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -216,    95,  -216,    18,    10,    14,   -49,    58,    63,    43,
      37,    13,    82,    87,    89,    90,    94,    49,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,    42,    50,   104,    52,
      56,  -216,  -216,  -216,  -216,  -216,    16,  -216,    99,   102,
     116,   117,  -216,    76,    80,   125,  -216,  -216,  -216,  -216,
    -216,   134,   144,   138,   113,   172,   141,    78,   -26,  -216,
     118,   -44,  -216,  -216,   147,   148,   120,   115,   121,   123,
     150,  -216,   126,    19,   167,   168,   168,     7,   171,    -7,
     173,   175,    75,   186,   152,   164,  -216,   176,   146,   179,
     135,   194,   -22,  -216,    12,  -216,  -216,   137,   149,   148,
     168,   168,   139,   168,    98,  -216,  -216,  -216,    39,  -216,
     122,   166,  -216,    98,   196,   121,   187,  -216,  -216,  -216,
    -216,    -8,   142,   189,  -216,   168,   168,   190,     5,   191,
     188,   151,   156,  -216,  -216,   193,  -216,   195,   153,  -216,
    -216,  -216,  -216,  -216,  -216,    83,    88,    75,  -216,   148,
     154,   176,   208,   157,   160,  -216,  -216,   201,   158,  -216,
    -216,   168,   168,   159,   168,  -216,   192,   169,   218,   168,
      98,   205,   122,  -216,  -216,   197,  -216,   166,   221,   223,
    -216,  -216,  -216,   211,  -216,   226,   213,  -216,  -216,   214,
    -216,    75,   174,  -216,  -216,   195,  -216,   215,    93,   177,
    -216,  -216,  -216,   -15,  -216,   229,   168,   166,     1,  -216,
     220,   231,   209,  -216,  -216,  -216,  -216,  -216,   198,  -216,
     178,  -216,   222,    98,  -216,   180,   199,   148,    -1,   181,
    -216,   195,  -216,   182,   241,   222,     4,   205,   210,  -216,
    -216,   185,   222,   215,    75,    -1,  -216,  -216,   166,   222,
     198,  -216,  -216
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,   107,   108,   109,   110,   111,    80,    72,     0,     0,
       0,     0,    23,     0,     0,     0,    24,    25,    26,    22,
      21,     0,     0,     0,     0,     0,     0,     0,     0,    73,
       0,     0,    29,    28,     0,    90,     0,     0,     0,     0,
       0,    27,     0,    80,     0,    80,    80,    88,     0,     0,
       0,     0,     0,     0,     0,     0,    46,    34,     0,     0,
       0,     0,     0,    81,     0,    75,    74,     0,     0,    90,
      80,    80,     0,    80,     0,    53,    54,    55,     0,    56,
       0,    92,    57,     0,     0,     0,     0,    42,    45,    43,
      44,    38,     0,     0,    32,    80,    80,     0,     0,     0,
      88,     0,    61,    79,    76,     0,    78,    51,     0,   101,
     102,   103,   104,   105,   106,     0,     0,     0,    91,    90,
       0,    34,     0,     0,     0,    39,    37,     0,     0,    82,
      83,    80,    80,     0,    80,    89,     0,     0,     0,    80,
       0,     0,     0,    96,    94,    97,    95,    92,     0,     0,
      35,    33,    41,     0,    40,     0,     0,    87,    84,     0,
      86,     0,     0,    59,    77,    51,    50,    48,     0,     0,
      93,    58,   112,    38,    30,     0,    80,    92,    67,    52,
       0,     0,     0,    98,    99,    36,    31,    85,    70,    69,
       0,    68,    64,     0,    47,     0,     0,    90,    67,     0,
      62,    51,   100,     0,     0,    64,    67,     0,     0,    60,
      63,     0,    64,    48,     0,    67,    65,    49,    92,    64,
      70,    66,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,    86,   127,    35,  -216,  -216,
    -216,  -216,    -3,     6,  -186,  -110,  -216,  -216,  -216,  -216,
    -158,  -215,    -6,  -216,   -83,   119,  -108,  -181,  -152,  -113,
     200,  -216
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   126,    97,   166,   193,   131,
      98,    31,   221,   207,   181,   120,    32,    33,    34,   178,
     240,   232,   237,    48,    69,   109,    93,   158,   121,   155,
      49,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     103,   142,   105,   106,   147,   187,   210,   156,   163,   229,
     111,   229,    50,   159,   229,    88,    39,    89,    40,   219,
      90,   112,   172,   245,    36,   107,    37,   143,   144,   230,
     146,   252,   251,   173,    67,    85,   228,    67,    86,   135,
     259,   164,   136,   165,    68,   184,   186,   102,   164,   217,
     165,   188,   169,   170,   231,   247,   231,    38,   108,   231,
      41,    42,    43,    44,    45,    51,    52,   148,    54,   208,
     205,   137,    53,   138,    55,    46,   139,   260,    47,   149,
     150,   151,   152,   153,   154,    56,    61,   250,   197,   198,
      57,   200,    58,    59,   256,     2,   204,    60,   223,     3,
       4,   261,   258,    62,     5,     6,     7,     8,     9,    10,
      11,    63,    64,    65,    12,    13,    14,    66,    71,    72,
      73,    15,    16,   241,    41,    42,    43,    44,    45,   244,
      70,    17,   115,   227,   116,   117,   118,    74,   119,    83,
     115,    75,   116,   117,   183,   115,   119,   116,   117,   185,
     115,   119,   116,   117,   222,   115,   119,   116,   117,    76,
      78,   119,   149,   150,   151,   152,   153,   154,   127,   128,
     129,   130,    77,    79,    80,    81,    82,    91,    95,    87,
      92,    94,    96,   104,    99,   100,    67,   101,   110,   122,
     113,   114,   123,   124,   125,   132,   133,   134,   140,   157,
     145,   141,   160,   167,   162,   168,   107,   171,   174,   177,
     179,   191,   176,   180,   182,   189,   192,   194,   195,   196,
     199,   203,   206,   202,   211,   209,   212,   201,   213,   214,
     215,   216,   226,   220,   234,   218,   233,   235,   224,   238,
     239,   242,   246,   248,   249,   254,   255,   190,   225,   236,
     257,   243,   161,   253,   262,     0,     0,     0,     0,   175,
       0,     0,     0,     0,     0,     0,     0,    84
};

static const yytype_int16 yycheck[] =
{
      83,   109,    85,    86,   114,   157,   187,   120,    16,    10,
      17,    10,    61,   123,    10,    59,     6,    61,     8,   205,
      64,    28,    17,   238,     6,    18,     8,   110,   111,    28,
     113,   246,    28,    28,    18,    61,   217,    18,    64,    61,
     255,    56,    64,    58,    28,   155,   156,    28,    56,   201,
      58,   159,   135,   136,    55,   241,    55,    39,    51,    55,
      46,    47,    48,    49,    50,     7,     3,    28,    31,   182,
     180,    59,    29,    61,    61,    61,    64,   258,    64,    40,
      41,    42,    43,    44,    45,     3,    37,   245,   171,   172,
       3,   174,     3,     3,   252,     0,   179,     3,   208,     4,
       5,   259,   254,    61,     9,    10,    11,    12,    13,    14,
      15,    61,     8,    61,    19,    20,    21,    61,    16,     3,
       3,    26,    27,   233,    46,    47,    48,    49,    50,   237,
      31,    36,    57,   216,    59,    60,    61,    61,    63,    61,
      57,    61,    59,    60,    61,    57,    63,    59,    60,    61,
      57,    63,    59,    60,    61,    57,    63,    59,    60,    34,
      16,    63,    40,    41,    42,    43,    44,    45,    22,    23,
      24,    25,    38,    35,    61,     3,    35,    30,    63,    61,
      32,    61,    61,    16,    61,    35,    18,    61,    17,     3,
      17,    16,    40,    29,    18,    16,    61,     3,    61,    33,
      61,    52,     6,    61,    17,    16,    18,    17,    17,    53,
      17,     3,    61,    18,    61,    61,    59,    57,    17,    61,
      61,     3,    17,    54,     3,    28,     3,    35,    17,     3,
      17,    17,     3,    18,     3,    61,    16,    28,    61,    61,
      18,    61,    61,    61,     3,    35,    61,   161,   213,    51,
     253,    52,   125,   247,   260,    -1,    -1,    -1,    -1,   140,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    67,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    87,    92,    93,    94,   107,     6,     8,    39,     6,
       8,    46,    47,    48,    49,    50,    61,    64,    99,   106,
      61,     7,     3,    29,    31,    61,     3,     3,     3,     3,
       3,    37,    61,    61,     8,    61,    61,    18,    28,   100,
      31,    16,     3,     3,    61,    61,    34,    38,    16,    35,
      61,     3,    35,    61,   106,    61,    64,    61,    59,    61,
      64,    30,    32,   102,    61,    63,    61,    82,    86,    61,
      35,    61,    28,   100,    16,   100,   100,    18,    51,   101,
      17,    17,    28,    17,    16,    57,    59,    60,    61,    63,
      91,   104,     3,    40,    29,    18,    81,    22,    23,    24,
      25,    85,    16,    61,     3,    61,    64,    59,    61,    64,
      61,    52,   102,   100,   100,    61,   100,    91,    28,    40,
      41,    42,    43,    44,    45,   105,   105,    33,   103,    91,
       6,    82,    17,    16,    56,    58,    83,    61,    16,   100,
     100,    17,    17,    28,    17,   101,    61,    53,    95,    17,
      18,    90,    61,    61,    91,    61,    91,   104,   102,    61,
      81,     3,    59,    84,    57,    17,    61,   100,   100,    61,
     100,    35,    54,     3,   100,    91,    17,    89,   105,    28,
     103,     3,     3,    17,     3,    17,    17,   104,    61,    90,
      18,    88,    61,    91,    61,    83,     3,   100,   103,    10,
      28,    55,    97,    16,     3,    28,    51,    98,    61,    18,
      96,    91,    61,    52,   102,    97,    61,    90,    61,     3,
      96,    28,    97,    89,    35,    61,    96,    88,   104,    97,
     103,    96,    98
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    78,    79,    80,    81,    81,    82,    82,    83,    83,
      83,    84,    85,    85,    85,    85,    86,    87,    88,    88,
      89,    90,    90,    91,    91,    91,    91,    92,    93,    94,
      94,    95,    95,    95,    96,    96,    96,    97,    97,    97,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
     100,   100,   100,   100,   100,   100,   100,   100,   101,   101,
     102,   102,   103,   103,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     106,   106,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     6,     8,     0,     3,     6,     3,     0,     1,
       2,     1,     1,     1,     1,     1,     1,    10,     0,     6,
       1,     0,     3,     1,     1,     1,     1,     5,     8,     8,
      13,     0,     5,     7,     0,     4,     6,     0,     1,     1,
       0,     7,     1,     2,     4,     4,     5,     7,     5,     5,
       0,     3,     5,     5,     6,     8,     6,     6,     0,     3,
       0,     3,     0,     3,     3,     3,     3,     3,     5,     5,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     8
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 21:
#line 182 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1628 "yacc_sql.tab.c"
    break;

  case 22:
#line 187 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1636 "yacc_sql.tab.c"
    break;

  case 23:
#line 192 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1644 "yacc_sql.tab.c"
    break;

  case 24:
#line 198 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1652 "yacc_sql.tab.c"
    break;

  case 25:
#line 204 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1660 "yacc_sql.tab.c"
    break;

  case 26:
#line 210 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1668 "yacc_sql.tab.c"
    break;

  case 27:
#line 216 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1677 "yacc_sql.tab.c"
    break;

  case 28:
#line 222 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1685 "yacc_sql.tab.c"
    break;

  case 29:
#line 228 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1694 "yacc_sql.tab.c"
    break;

  case 30:
#line 236 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 0);
        }
#line 1703 "yacc_sql.tab.c"
    break;

  case 31:
#line 241 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
        }
#line 1712 "yacc_sql.tab.c"
    break;

  case 32:
#line 249 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-3].string), (yyvsp[-1].string));
		}
#line 1721 "yacc_sql.tab.c"
    break;

  case 33:
#line 256 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
            // CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
            create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
            //临时变量清零	
            CONTEXT->value_length = 0;
        }
#line 1733 "yacc_sql.tab.c"
    break;

  case 35:
#line 266 "yacc_sql.y"
                                   {    }
#line 1739 "yacc_sql.tab.c"
    break;

  case 36:
#line 271 "yacc_sql.y"
        {
            AttrInfo attribute;
            attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
            // strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
            CONTEXT->value_length++;
        }
#line 1754 "yacc_sql.tab.c"
    break;

  case 37:
#line 282 "yacc_sql.y"
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
                break;
                default: {
                    attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 5, (yyvsp[0].number));
                }
            }
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
            // strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
            // CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
            CONTEXT->value_length++;
        }
#line 1790 "yacc_sql.tab.c"
    break;

  case 38:
#line 316 "yacc_sql.y"
                { (yyval.number) = 0; }
#line 1796 "yacc_sql.tab.c"
    break;

  case 39:
#line 317 "yacc_sql.y"
               { (yyval.number) = 1; }
#line 1802 "yacc_sql.tab.c"
    break;

  case 40:
#line 318 "yacc_sql.y"
                 { (yyval.number) = 0; }
#line 1808 "yacc_sql.tab.c"
    break;

  case 41:
#line 322 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1814 "yacc_sql.tab.c"
    break;

  case 42:
#line 325 "yacc_sql.y"
          { (yyval.number)=INTS; }
#line 1820 "yacc_sql.tab.c"
    break;

  case 43:
#line 326 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1826 "yacc_sql.tab.c"
    break;

  case 44:
#line 327 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1832 "yacc_sql.tab.c"
    break;

  case 45:
#line 328 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1838 "yacc_sql.tab.c"
    break;

  case 46:
#line 332 "yacc_sql.y"
    {
        char *temp=(yyvsp[0].string); 
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1847 "yacc_sql.tab.c"
    break;

  case 47:
#line 341 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_INSERT; //"insert";
            inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->tuples, CONTEXT->tuple_num);
            // 临时变量清零
            CONTEXT->value_length = 0;
            CONTEXT->tuple_num = 0;
    }
#line 1859 "yacc_sql.tab.c"
    break;

  case 49:
#line 350 "yacc_sql.y"
                                                             {
    }
#line 1866 "yacc_sql.tab.c"
    break;

  case 50:
#line 354 "yacc_sql.y"
           {
        // 此规则用于表明读取到一个要 insert 的 tuple，并提高此操作的优先级
        InsertTuple tuple;
        insert_tuple_init(&tuple, CONTEXT->values, CONTEXT->value_length);
        CONTEXT->tuples[CONTEXT->tuple_num++] = tuple;
        CONTEXT->value_length = 0;
    }
#line 1878 "yacc_sql.tab.c"
    break;

  case 52:
#line 364 "yacc_sql.y"
                              { 
          // CONTEXT->values[CONTEXT->value_length++] = *$2;
      }
#line 1886 "yacc_sql.tab.c"
    break;

  case 53:
#line 369 "yacc_sql.y"
           {
        value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    }
#line 1894 "yacc_sql.tab.c"
    break;

  case 54:
#line 372 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
    }
#line 1902 "yacc_sql.tab.c"
    break;

  case 55:
#line 375 "yacc_sql.y"
          {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
    }
#line 1910 "yacc_sql.tab.c"
    break;

  case 56:
#line 378 "yacc_sql.y"
         {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    }
#line 1919 "yacc_sql.tab.c"
    break;

  case 57:
#line 385 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_DELETE;//"delete";
            deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
            deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
                    CONTEXT->conditions, CONTEXT->condition_length);
            CONTEXT->condition_length = 0;	
    }
#line 1931 "yacc_sql.tab.c"
    break;

  case 58:
#line 395 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_UPDATE;//"update";
            Value *value = &CONTEXT->values[0];
            updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
                    CONTEXT->conditions, CONTEXT->condition_length);
            CONTEXT->condition_length = 0;
        }
#line 1943 "yacc_sql.tab.c"
    break;

  case 59:
#line 405 "yacc_sql.y"
        {
            // CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
            selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));

            selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

            CONTEXT->ssql->flag=SCF_SELECT;//"select";
            // CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

            //临时变量清零
            CONTEXT->condition_length=0;
            CONTEXT->from_length=0;
            CONTEXT->select_length=0;
            CONTEXT->value_length = 0;
    }
#line 1963 "yacc_sql.tab.c"
    break;

  case 60:
#line 421 "yacc_sql.y"
    {
        // CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
        selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-6].string));
        selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-9].string));
        selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
        CONTEXT->ssql->flag=SCF_SELECT;//"select";
        // CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

        //临时变量清零
        CONTEXT->condition_length=0;
        CONTEXT->from_length=0;
        CONTEXT->select_length=0;
        CONTEXT->value_length = 0;
    }
#line 1982 "yacc_sql.tab.c"
    break;

  case 62:
#line 438 "yacc_sql.y"
                                             {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 1994 "yacc_sql.tab.c"
    break;

  case 63:
#line 445 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 2006 "yacc_sql.tab.c"
    break;

  case 65:
#line 456 "yacc_sql.y"
                                          {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 2018 "yacc_sql.tab.c"
    break;

  case 66:
#line 463 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->ssql->sstr.selection, &order_attr);
    }
#line 2030 "yacc_sql.tab.c"
    break;

  case 67:
#line 473 "yacc_sql.y"
                { (yyval.number) = AscOrder; }
#line 2036 "yacc_sql.tab.c"
    break;

  case 68:
#line 474 "yacc_sql.y"
          { (yyval.number) = AscOrder; }
#line 2042 "yacc_sql.tab.c"
    break;

  case 69:
#line 475 "yacc_sql.y"
           { (yyval.number) = DescOrder; }
#line 2048 "yacc_sql.tab.c"
    break;

  case 71:
#line 480 "yacc_sql.y"
    {
        selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
    }
#line 2056 "yacc_sql.tab.c"
    break;

  case 72:
#line 485 "yacc_sql.y"
         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2066 "yacc_sql.tab.c"
    break;

  case 73:
#line 490 "yacc_sql.y"
                   {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2076 "yacc_sql.tab.c"
    break;

  case 74:
#line 495 "yacc_sql.y"
                            {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), "*");
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2086 "yacc_sql.tab.c"
    break;

  case 75:
#line 500 "yacc_sql.y"
                          {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2096 "yacc_sql.tab.c"
    break;

  case 76:
#line 505 "yacc_sql.y"
                                             {
        RelAttr attr;
        // TODO: 更完善地支持 COUNT(expression) 聚合函数（ALL 和 DISTINCT）
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2107 "yacc_sql.tab.c"
    break;

  case 77:
#line 511 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2117 "yacc_sql.tab.c"
    break;

  case 78:
#line 516 "yacc_sql.y"
                                               {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2127 "yacc_sql.tab.c"
    break;

  case 79:
#line 521 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2137 "yacc_sql.tab.c"
    break;

  case 81:
#line 530 "yacc_sql.y"
                         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
    }
#line 2149 "yacc_sql.tab.c"
    break;

  case 82:
#line 537 "yacc_sql.y"
                                {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
    }
#line 2161 "yacc_sql.tab.c"
    break;

  case 83:
#line 544 "yacc_sql.y"
                                   {
             RelAttr attr;
             relation_attr_init(&attr, (yyvsp[-3].string), "*");
             selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
         // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
         // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
      }
#line 2173 "yacc_sql.tab.c"
    break;

  case 84:
#line 551 "yacc_sql.y"
                                                   {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2183 "yacc_sql.tab.c"
    break;

  case 85:
#line 556 "yacc_sql.y"
                                                          {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2193 "yacc_sql.tab.c"
    break;

  case 86:
#line 561 "yacc_sql.y"
                                                     {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2203 "yacc_sql.tab.c"
    break;

  case 87:
#line 566 "yacc_sql.y"
                                                       {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2213 "yacc_sql.tab.c"
    break;

  case 89:
#line 575 "yacc_sql.y"
                        {	
                selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
          }
#line 2221 "yacc_sql.tab.c"
    break;

  case 91:
#line 581 "yacc_sql.y"
                                     {	
                // CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
            }
#line 2229 "yacc_sql.tab.c"
    break;

  case 93:
#line 587 "yacc_sql.y"
                                   {
                // CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
            }
#line 2237 "yacc_sql.tab.c"
    break;

  case 94:
#line 593 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

            Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

            Condition condition;
            condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->condition_length++] = condition;
            // $$ = ( Condition *)malloc(sizeof( Condition));
            // $$->left_is_attr = 1;
            // $$->left_attr.relation_name = NULL;
            // $$->left_attr.attribute_name= $1;
            // $$->comp = CONTEXT->comp;
            // $$->right_is_attr = 0;
            // $$->right_attr.relation_name = NULL;
            // $$->right_attr.attribute_name = NULL;
            // $$->right_value = *$3;

        }
#line 2262 "yacc_sql.tab.c"
    break;

  case 95:
#line 614 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
            Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

            Condition condition;
            condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->condition_length++] = condition;
            // $$ = ( Condition *)malloc(sizeof( Condition));
            // $$->left_is_attr = 0;
            // $$->left_attr.relation_name=NULL;
            // $$->left_attr.attribute_name=NULL;
            // $$->left_value = *$1;
            // $$->comp = CONTEXT->comp;
            // $$->right_is_attr = 0;
            // $$->right_attr.relation_name = NULL;
            // $$->right_attr.attribute_name = NULL;
            // $$->right_value = *$3;

        }
#line 2286 "yacc_sql.tab.c"
    break;

  case 96:
#line 634 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->condition_length++] = condition;
            // $$=( Condition *)malloc(sizeof( Condition));
            // $$->left_is_attr = 1;
            // $$->left_attr.relation_name=NULL;
            // $$->left_attr.attribute_name=$1;
            // $$->comp = CONTEXT->comp;
            // $$->right_is_attr = 1;
            // $$->right_attr.relation_name=NULL;
            // $$->right_attr.attribute_name=$3;

        }
#line 2310 "yacc_sql.tab.c"
    break;

  case 97:
#line 654 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->condition_length++] = condition;

            // $$=( Condition *)malloc(sizeof( Condition));
            // $$->left_is_attr = 0;
            // $$->left_attr.relation_name=NULL;
            // $$->left_attr.attribute_name=NULL;
            // $$->left_value = *$1;
            // $$->comp=CONTEXT->comp;
            
            // $$->right_is_attr = 1;
            // $$->right_attr.relation_name=NULL;
            // $$->right_attr.attribute_name=$3;
        
        }
#line 2336 "yacc_sql.tab.c"
    break;

  case 98:
#line 676 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
            Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

            Condition condition;
            condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->condition_length++] = condition;

            // $$=( Condition *)malloc(sizeof( Condition));
            // $$->left_is_attr = 1;
            // $$->left_attr.relation_name=$1;
            // $$->left_attr.attribute_name=$3;
            // $$->comp=CONTEXT->comp;
            // $$->right_is_attr = 0;   //属性值
            // $$->right_attr.relation_name=NULL;
            // $$->right_attr.attribute_name=NULL;
            // $$->right_value =*$5;			
                            
    }
#line 2361 "yacc_sql.tab.c"
    break;

  case 99:
#line 697 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

            RelAttr right_attr;
            relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->condition_length++] = condition;
            // $$=( Condition *)malloc(sizeof( Condition));
            // $$->left_is_attr = 0;//属性值
            // $$->left_attr.relation_name=NULL;
            // $$->left_attr.attribute_name=NULL;
            // $$->left_value = *$1;
            // $$->comp =CONTEXT->comp;
            // $$->right_is_attr = 1;//属性
            // $$->right_attr.relation_name = $3;
            // $$->right_attr.attribute_name = $5;
                                    
    }
#line 2386 "yacc_sql.tab.c"
    break;

  case 100:
#line 718 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
            RelAttr right_attr;
            relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->condition_length++] = condition;
            // $$=( Condition *)malloc(sizeof( Condition));
            // $$->left_is_attr = 1;		//属性
            // $$->left_attr.relation_name=$1;
            // $$->left_attr.attribute_name=$3;
            // $$->comp =CONTEXT->comp;
            // $$->right_is_attr = 1;		//属性
            // $$->right_attr.relation_name=$5;
            // $$->right_attr.attribute_name=$7;
    }
#line 2409 "yacc_sql.tab.c"
    break;

  case 101:
#line 739 "yacc_sql.y"
           { CONTEXT->comp = EQUAL_TO; }
#line 2415 "yacc_sql.tab.c"
    break;

  case 102:
#line 740 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2421 "yacc_sql.tab.c"
    break;

  case 103:
#line 741 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2427 "yacc_sql.tab.c"
    break;

  case 104:
#line 742 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2433 "yacc_sql.tab.c"
    break;

  case 105:
#line 743 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2439 "yacc_sql.tab.c"
    break;

  case 106:
#line 744 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2445 "yacc_sql.tab.c"
    break;

  case 107:
#line 748 "yacc_sql.y"
          { (yyval.number) = CountAggregate; }
#line 2451 "yacc_sql.tab.c"
    break;

  case 108:
#line 749 "yacc_sql.y"
          { (yyval.number) = SumAggregate; }
#line 2457 "yacc_sql.tab.c"
    break;

  case 109:
#line 750 "yacc_sql.y"
          { (yyval.number) = AvgAggregate; }
#line 2463 "yacc_sql.tab.c"
    break;

  case 110:
#line 751 "yacc_sql.y"
          { (yyval.number) = MaxAggregate; }
#line 2469 "yacc_sql.tab.c"
    break;

  case 111:
#line 752 "yacc_sql.y"
          { (yyval.number) = MinAggregate; }
#line 2475 "yacc_sql.tab.c"
    break;

  case 112:
#line 757 "yacc_sql.y"
        {
          CONTEXT->ssql->flag = SCF_LOAD_DATA;
            load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
        }
#line 2484 "yacc_sql.tab.c"
    break;


#line 2488 "yacc_sql.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 762 "yacc_sql.y"

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
