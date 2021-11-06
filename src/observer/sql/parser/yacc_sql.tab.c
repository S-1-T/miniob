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


#line 140 "yacc_sql.tab.c"

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
    TEXT_T = 281,
    HELP = 282,
    EXIT = 283,
    DOT = 284,
    INTO = 285,
    VALUES = 286,
    FROM = 287,
    WHERE = 288,
    AND = 289,
    SET = 290,
    ON = 291,
    LOAD = 292,
    DATA = 293,
    INFILE = 294,
    UNIQUE = 295,
    EQ = 296,
    LT = 297,
    GT = 298,
    LE = 299,
    GE = 300,
    NE = 301,
    COUNT = 302,
    SUM = 303,
    AVG = 304,
    MAX = 305,
    MIN = 306,
    INNER = 307,
    JOIN = 308,
    ORDER = 309,
    BY = 310,
    ASC = 311,
    IS_ = 312,
    NOT = 313,
    NULL_T = 314,
    NULLABLE = 315,
    IN = 316,
    NUMBER = 317,
    FLOAT = 318,
    ID = 319,
    PATH = 320,
    SSS = 321,
    STAR = 322,
    STRING_V = 323
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 137 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _InsertTuple *tuples1;
  char *string;
  int number;
  float floats;
  char *position;

#line 272 "yacc_sql.tab.c"

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
#define YYLAST   310

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  303

#define YYUNDEFTOK  2
#define YYMAXUTOK   323


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
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   168,   168,   170,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   194,   199,   204,   210,   216,   222,   228,   234,   240,
     247,   255,   265,   267,   273,   280,   288,   290,   294,   301,
     336,   337,   338,   342,   345,   346,   347,   348,   349,   352,
     361,   370,   371,   375,   383,   385,   390,   393,   396,   399,
     405,   415,   426,   443,   465,   470,   472,   479,   488,   490,
     497,   507,   508,   509,   511,   513,   519,   525,   531,   537,
     543,   550,   556,   562,   570,   572,   580,   588,   596,   602,
     608,   614,   622,   624,   629,   631,   635,   637,   642,   653,
     662,   674,   684,   694,   705,   716,   742,   768,   794,   823,
     824,   825,   826,   827,   828,   829,   830,   831,   832,   836,
     837,   838,   839,   840,   844
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
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "UNIQUE", "EQ", "LT", "GT", "LE", "GE",
  "NE", "COUNT", "SUM", "AVG", "MAX", "MIN", "INNER", "JOIN", "ORDER",
  "BY", "ASC", "IS_", "NOT", "NULL_T", "NULLABLE", "IN", "NUMBER", "FLOAT",
  "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index",
  "index_attr_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "nullable", "number", "type", "ID_get", "insert",
  "tuple_list", "insert_rbrace", "value_list", "value", "delete", "update",
  "select", "select_begin", "order", "order_attr_list", "order_type",
  "join_list", "select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition", "comOp", "aggregation", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

#define YYPACT_NINF (-253)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -253,   159,  -253,    17,    86,  -253,   -44,    24,    44,    39,
      55,    31,    78,    85,   103,   117,   128,    96,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,    49,  -253,    73,    75,   132,
      77,    79,   142,   144,  -253,    84,    88,   114,  -253,  -253,
    -253,  -253,  -253,   111,  -253,  -253,  -253,  -253,  -253,     4,
    -253,   121,   138,   140,   122,    93,   157,   125,  -253,  -253,
     134,   133,   113,   109,    54,   -38,  -253,   118,   -16,   119,
     120,   145,  -253,   130,   169,     2,   192,   162,   176,    26,
     191,   193,   193,     1,   195,    -1,   198,  -253,   205,   196,
     194,   152,   206,    66,   215,  -253,  -253,  -253,   147,  -253,
     156,   197,  -253,    66,   219,    15,  -253,    71,  -253,  -253,
     163,   173,   133,   193,   193,   164,   193,   119,   212,  -253,
    -253,  -253,  -253,  -253,    -2,   166,   216,  -253,   217,    49,
     170,  -253,  -253,  -253,  -253,  -253,  -253,   175,   177,  -253,
      14,    60,     2,  -253,   133,   172,   193,   193,   220,    25,
     222,   223,   178,   186,  -253,  -253,   226,  -253,   205,   241,
     183,   187,  -253,  -253,   229,   184,    66,   232,   218,   156,
    -253,  -253,   215,  -253,  -253,   224,  -253,   197,   248,   249,
    -253,  -253,   193,   193,   190,   193,  -253,   221,   200,   253,
     193,  -253,  -253,  -253,   242,  -253,   199,   243,   229,   217,
    -253,   240,   201,    27,    49,   202,  -253,  -253,  -253,  -253,
    -253,   244,  -253,     2,   203,  -253,  -253,    51,   229,   259,
     247,  -253,   252,   266,   223,   215,   245,  -253,   238,  -253,
     193,   197,     7,  -253,  -253,  -253,   268,    66,  -253,   133,
      49,   208,   209,  -253,   225,  -253,   211,  -253,   258,  -253,
     217,   261,   250,  -253,   223,   227,   133,     3,   228,  -253,
     232,   156,   230,   133,   231,   276,   258,    11,   240,   233,
     223,   264,   251,  -253,  -253,   234,   258,  -253,   254,   133,
    -253,     2,     3,  -253,   235,   267,   197,   258,  -253,  -253,
     225,  -253,  -253
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,     0,    18,     0,     0,     0,
       0,     0,     0,     0,    23,     0,     0,     0,    24,    25,
      26,    22,    21,     0,   119,   120,   121,   122,   123,    84,
      76,     0,     0,     0,     0,     0,     0,     0,    29,    28,
       0,    94,     0,     0,     0,     0,    77,     0,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,     0,    84,
       0,    84,    84,    92,     0,     0,     0,    49,    36,     0,
       0,     0,     0,     0,     0,    56,    57,    58,     0,    59,
       0,    96,    60,     0,     0,     0,    85,     0,    79,    78,
       0,     0,    94,    84,    84,     0,    84,     0,     0,    44,
      47,    45,    46,    48,    40,     0,     0,    34,    54,     0,
       0,   109,   110,   111,   112,   113,   114,   115,     0,   117,
       0,     0,     0,    95,    94,     0,    84,    84,     0,     0,
       0,    92,     0,    65,    83,    80,     0,    82,    36,     0,
       0,     0,    41,    39,    32,     0,     0,     0,     0,     0,
     116,   118,     0,   100,    98,   101,    99,    96,     0,     0,
      86,    87,    84,    84,     0,    84,    93,     0,     0,     0,
      84,    37,    35,    43,     0,    42,     0,     0,    32,    54,
      53,    51,     0,     0,     0,     0,    97,    61,   124,    91,
      88,     0,    90,     0,     0,    62,    81,    40,    32,     0,
       0,    55,     0,     0,    92,     0,     0,   102,     0,   103,
      84,    96,    71,    38,    33,    30,     0,     0,    50,    94,
       0,     0,     0,    89,    74,    73,     0,    72,    68,    31,
      54,     0,     0,   104,    92,     0,    94,    71,     0,    66,
       0,     0,     0,    94,     0,     0,    68,    71,    51,     0,
      92,     0,     0,    63,    67,     0,    68,    52,   107,    94,
     105,     0,    71,    69,     0,     0,    96,    68,   108,   106,
      74,    70,    75
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,  -253,  -193,  -253,  -253,   123,   158,    59,  -253,
    -253,  -253,  -253,    10,    19,  -200,  -101,  -253,  -253,  -253,
     -99,  -253,  -252,  -240,   -10,  -129,   -85,  -150,  -122,  -179,
    -149,  -109,   236,  -253
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   207,    29,    30,   128,    98,   173,   204,
     134,    99,    31,   233,   211,   177,   110,    32,    33,    34,
      35,   199,   269,   258,   266,    61,    76,   122,    86,   153,
     111,   150,    62,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     163,   151,   138,   187,   116,   139,   118,   119,   216,   231,
     178,   196,   154,   255,   170,   230,   124,   255,   104,   120,
      42,   255,    74,    37,   284,    38,    91,   276,   125,    92,
     182,    43,   188,    75,   293,   244,   256,   286,   164,   165,
     285,   167,   193,   235,    74,   301,    94,    44,    95,   184,
     186,    96,   297,   121,   194,   115,   171,    39,   172,   257,
     270,   105,   254,   257,   106,   107,   108,   257,   109,    45,
     213,   190,   191,   105,   241,   209,   106,   107,   183,   156,
     109,    48,   157,   214,   249,   238,   105,    46,    49,   106,
     107,   236,    40,   109,    41,    47,    54,    55,    56,    57,
      58,    54,    55,    56,    57,    58,    50,   219,   220,   171,
     222,   172,   237,    59,   273,   226,    60,   300,    89,   105,
      51,   262,   106,   107,   185,   105,   109,   261,   106,   107,
     289,    52,   109,   158,    53,   159,   250,    63,   160,    64,
      65,    66,   296,    67,   275,    68,   260,    69,    70,    72,
      73,   281,    71,    77,    78,   253,    79,    81,    80,     2,
      82,    83,   279,     3,     4,    84,    85,   295,     5,     6,
       7,     8,     9,    10,    11,    88,   140,    87,    12,    13,
      14,   101,    93,    97,   100,   103,    15,    16,   141,   142,
     143,   144,   145,   146,   102,   112,    17,   141,   142,   143,
     144,   145,   146,   113,   147,   148,   114,   117,   149,   137,
     135,    74,   123,   147,   148,   126,   136,   149,   129,   130,
     131,   132,   133,   127,     5,   155,   162,   161,   166,   169,
     174,   152,   175,   180,   179,   176,   189,   192,   181,   195,
     198,   120,   197,   200,   202,   203,   205,   206,   208,   210,
     212,   217,   218,   215,   221,   224,   225,   223,   232,   227,
     229,   240,   245,   228,   246,   234,   239,   242,   247,   248,
     252,   259,   263,   264,   251,   267,   268,   265,   271,   283,
     274,   290,   272,   294,   299,   168,   243,   291,   287,   278,
     302,   201,   277,     0,   280,   282,     0,   288,   292,   298,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      90
};

static const yytype_int16 yycheck[] =
{
     122,   110,   103,   152,    89,   104,    91,    92,   187,   209,
     139,   161,   113,    10,    16,   208,    17,    10,    16,    18,
      64,    10,    18,     6,   276,     8,    64,   267,    29,    67,
      16,     7,   154,    29,   286,   228,    29,   277,   123,   124,
      29,   126,    17,    16,    18,   297,    62,     3,    64,   150,
     151,    67,   292,    52,    29,    29,    58,    40,    60,    56,
     260,    59,   241,    56,    62,    63,    64,    56,    66,    30,
     179,   156,   157,    59,   223,   176,    62,    63,    64,    64,
      66,     3,    67,   182,   234,   214,    59,    32,     3,    62,
      63,    64,     6,    66,     8,    64,    47,    48,    49,    50,
      51,    47,    48,    49,    50,    51,     3,   192,   193,    58,
     195,    60,   213,    64,   264,   200,    67,   296,    64,    59,
       3,   250,    62,    63,    64,    59,    66,   249,    62,    63,
     280,     3,    66,    62,    38,    64,   235,    64,    67,    64,
       8,    64,   291,    64,   266,     3,   247,     3,    64,    35,
      39,   273,    64,    32,    16,   240,    16,    64,    36,     0,
       3,    36,   271,     4,     5,    31,    33,   289,     9,    10,
      11,    12,    13,    14,    15,    66,    29,    64,    19,    20,
      21,    36,    64,    64,    64,    16,    27,    28,    41,    42,
      43,    44,    45,    46,    64,     3,    37,    41,    42,    43,
      44,    45,    46,    41,    57,    58,    30,    16,    61,     3,
      16,    18,    17,    57,    58,    17,    64,    61,    22,    23,
      24,    25,    26,    18,     9,     6,    53,    64,    64,    17,
      64,    34,    16,    58,    64,    18,    64,    17,    61,    17,
      54,    18,    64,    17,     3,    62,    59,    18,    64,    17,
      32,     3,     3,    29,    64,    55,     3,    36,    18,    17,
      17,    17,     3,    64,    17,    64,    64,    64,    16,     3,
      32,     3,    64,    64,    29,    64,    18,    52,    17,     3,
      53,    17,    32,    29,    17,   127,   227,    36,   278,   270,
     300,   168,    64,    -1,    64,    64,    -1,    64,    64,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    70,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    83,
      84,    91,    96,    97,    98,    99,   112,     6,     8,    40,
       6,     8,    64,     7,     3,    30,    32,    64,     3,     3,
       3,     3,     3,    38,    47,    48,    49,    50,    51,    64,
      67,   104,   111,    64,    64,     8,    64,    64,     3,     3,
      64,    64,    35,    39,    18,    29,   105,    32,    16,    16,
      36,    64,     3,    36,    31,    33,   107,    64,    66,    64,
     111,    64,    67,    64,    62,    64,    67,    64,    86,    90,
      64,    36,    64,    16,    16,    59,    62,    63,    64,    66,
      95,   109,     3,    41,    30,    29,   105,    16,   105,   105,
      18,    52,   106,    17,    17,    29,    17,    18,    85,    22,
      23,    24,    25,    26,    89,    16,    64,     3,    95,    99,
      29,    41,    42,    43,    44,    45,    46,    57,    58,    61,
     110,   110,    34,   108,    95,     6,    64,    67,    62,    64,
      67,    64,    53,   107,   105,   105,    64,   105,    86,    17,
      16,    58,    60,    87,    64,    16,    18,    94,   104,    64,
      58,    61,    16,    64,    95,    64,    95,   109,   107,    64,
     105,   105,    17,    17,    29,    17,   106,    64,    54,   100,
      17,    85,     3,    62,    88,    59,    18,    82,    64,    95,
      17,    93,    32,   110,    99,    29,   108,     3,     3,   105,
     105,    64,   105,    36,    55,     3,   105,    17,    64,    17,
      82,    94,    18,    92,    64,    16,    64,    95,   104,    64,
      17,   109,    64,    87,    82,     3,    17,    16,     3,   106,
      99,    29,    32,   105,   108,    10,    29,    56,   102,     3,
      95,   107,   104,    64,    64,    52,   103,    64,    18,   101,
      94,    17,    32,   106,    53,   107,   102,    64,    93,   110,
      64,   107,    64,     3,   101,    29,   102,    92,    64,   106,
      17,    36,    64,   101,    29,   107,   109,   102,    64,    17,
     108,   101,   103
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    81,    82,    82,    83,    84,    85,    85,    86,    86,
      87,    87,    87,    88,    89,    89,    89,    89,    89,    90,
      91,    92,    92,    93,    94,    94,    95,    95,    95,    95,
      96,    97,    98,    98,    99,   100,   100,   100,   101,   101,
     101,   102,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   105,   105,   105,   105,   105,
     105,   105,   106,   106,   107,   107,   108,   108,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   111,
     111,   111,   111,   111,   112
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     6,     8,     0,     3,     6,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
      10,     0,     6,     1,     0,     3,     1,     1,     1,     1,
       5,     8,     8,    13,     1,     0,     5,     7,     0,     4,
       6,     0,     1,     1,     0,     7,     1,     2,     4,     4,
       5,     7,     5,     5,     0,     3,     5,     5,     6,     8,
       6,     6,     0,     3,     0,     3,     0,     3,     3,     3,
       3,     3,     5,     5,     7,    10,    12,    10,    12,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1,     1,     8
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
#line 194 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1665 "yacc_sql.tab.c"
    break;

  case 22:
#line 199 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1673 "yacc_sql.tab.c"
    break;

  case 23:
#line 204 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1681 "yacc_sql.tab.c"
    break;

  case 24:
#line 210 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1689 "yacc_sql.tab.c"
    break;

  case 25:
#line 216 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1697 "yacc_sql.tab.c"
    break;

  case 26:
#line 222 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1705 "yacc_sql.tab.c"
    break;

  case 27:
#line 228 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1714 "yacc_sql.tab.c"
    break;

  case 28:
#line 234 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1722 "yacc_sql.tab.c"
    break;

  case 29:
#line 240 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1731 "yacc_sql.tab.c"
    break;

  case 30:
#line 248 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-3].string);
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 0);
            CONTEXT->index_attr_num = 0;
        }
#line 1743 "yacc_sql.tab.c"
    break;

  case 31:
#line 256 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-3].string);
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 1);
            CONTEXT->index_attr_num = 0;
        }
#line 1755 "yacc_sql.tab.c"
    break;

  case 33:
#line 268 "yacc_sql.y"
    {
        CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-1].string);
    }
#line 1763 "yacc_sql.tab.c"
    break;

  case 34:
#line 274 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-3].string), (yyvsp[-1].string));
	}
#line 1772 "yacc_sql.tab.c"
    break;

  case 35:
#line 281 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
            create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
            //临时变量清零	
            CONTEXT->value_length[0] = 0;
        }
#line 1783 "yacc_sql.tab.c"
    break;

  case 37:
#line 290 "yacc_sql.y"
                                   {    }
#line 1789 "yacc_sql.tab.c"
    break;

  case 38:
#line 295 "yacc_sql.y"
        {
            AttrInfo attribute;
            attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            CONTEXT->value_length[0]++;
        }
#line 1800 "yacc_sql.tab.c"
    break;

  case 39:
#line 302 "yacc_sql.y"
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
#line 1836 "yacc_sql.tab.c"
    break;

  case 40:
#line 336 "yacc_sql.y"
                { (yyval.number) = 0; }
#line 1842 "yacc_sql.tab.c"
    break;

  case 41:
#line 337 "yacc_sql.y"
               { (yyval.number) = 1; }
#line 1848 "yacc_sql.tab.c"
    break;

  case 42:
#line 338 "yacc_sql.y"
                 { (yyval.number) = 0; }
#line 1854 "yacc_sql.tab.c"
    break;

  case 43:
#line 342 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1860 "yacc_sql.tab.c"
    break;

  case 44:
#line 345 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1866 "yacc_sql.tab.c"
    break;

  case 45:
#line 346 "yacc_sql.y"
                 { (yyval.number) = FLOATS; }
#line 1872 "yacc_sql.tab.c"
    break;

  case 46:
#line 347 "yacc_sql.y"
                { (yyval.number) = DATES; }
#line 1878 "yacc_sql.tab.c"
    break;

  case 47:
#line 348 "yacc_sql.y"
                  { (yyval.number) = CHARS; }
#line 1884 "yacc_sql.tab.c"
    break;

  case 48:
#line 349 "yacc_sql.y"
                { (yyval.number) = TEXTS; }
#line 1890 "yacc_sql.tab.c"
    break;

  case 49:
#line 353 "yacc_sql.y"
    {
        char *temp=(yyvsp[0].string); 
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1899 "yacc_sql.tab.c"
    break;

  case 50:
#line 362 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_INSERT; //"insert";
            inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->tuples, CONTEXT->tuple_num);
            // 临时变量清零
            CONTEXT->value_length[0] = 0;
            CONTEXT->tuple_num = 0;
    }
#line 1911 "yacc_sql.tab.c"
    break;

  case 52:
#line 371 "yacc_sql.y"
                                                             {
    }
#line 1918 "yacc_sql.tab.c"
    break;

  case 53:
#line 375 "yacc_sql.y"
           {
        // 此规则用于表明读取到一个要 insert 的 tuple，并提高此操作的优先级
        InsertTuple tuple;
        insert_tuple_init(&tuple, CONTEXT->values, CONTEXT->value_length[0]);
        CONTEXT->tuples[CONTEXT->tuple_num++] = tuple;
        CONTEXT->value_length[0] = 0;
    }
#line 1930 "yacc_sql.tab.c"
    break;

  case 55:
#line 385 "yacc_sql.y"
                              { 
          // CONTEXT->values[CONTEXT->value_length++] = *$2;
      }
#line 1938 "yacc_sql.tab.c"
    break;

  case 56:
#line 390 "yacc_sql.y"
           {
        value_init_null(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++]);
    }
#line 1946 "yacc_sql.tab.c"
    break;

  case 57:
#line 393 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].number));
    }
#line 1954 "yacc_sql.tab.c"
    break;

  case 58:
#line 396 "yacc_sql.y"
          {
        value_init_float(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].floats));
    }
#line 1962 "yacc_sql.tab.c"
    break;

  case 59:
#line 399 "yacc_sql.y"
         {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].string));
    }
#line 1971 "yacc_sql.tab.c"
    break;

  case 60:
#line 406 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_DELETE;//"delete";
            deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
            deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
    }
#line 1983 "yacc_sql.tab.c"
    break;

  case 61:
#line 416 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_UPDATE;//"update";
            Value *value = &CONTEXT->values[0];
            updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
        }
#line 1995 "yacc_sql.tab.c"
    break;

  case 62:
#line 427 "yacc_sql.y"
     {
	    selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
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
#line 2016 "yacc_sql.tab.c"
    break;

  case 63:
#line 444 "yacc_sql.y"
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
#line 2039 "yacc_sql.tab.c"
    break;

  case 64:
#line 466 "yacc_sql.y"
        {
    	CONTEXT->select_length++;
    }
#line 2047 "yacc_sql.tab.c"
    break;

  case 66:
#line 472 "yacc_sql.y"
                                             {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2059 "yacc_sql.tab.c"
    break;

  case 67:
#line 479 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2071 "yacc_sql.tab.c"
    break;

  case 69:
#line 490 "yacc_sql.y"
                                          {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2083 "yacc_sql.tab.c"
    break;

  case 70:
#line 497 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2095 "yacc_sql.tab.c"
    break;

  case 71:
#line 507 "yacc_sql.y"
                { (yyval.number) = AscOrder; }
#line 2101 "yacc_sql.tab.c"
    break;

  case 72:
#line 508 "yacc_sql.y"
          { (yyval.number) = AscOrder; }
#line 2107 "yacc_sql.tab.c"
    break;

  case 73:
#line 509 "yacc_sql.y"
           { (yyval.number) = DescOrder; }
#line 2113 "yacc_sql.tab.c"
    break;

  case 75:
#line 514 "yacc_sql.y"
    {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
    }
#line 2121 "yacc_sql.tab.c"
    break;

  case 76:
#line 519 "yacc_sql.y"
         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2132 "yacc_sql.tab.c"
    break;

  case 77:
#line 525 "yacc_sql.y"
                   {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2143 "yacc_sql.tab.c"
    break;

  case 78:
#line 531 "yacc_sql.y"
                            {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), "*");
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2154 "yacc_sql.tab.c"
    break;

  case 79:
#line 537 "yacc_sql.y"
                          {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2165 "yacc_sql.tab.c"
    break;

  case 80:
#line 543 "yacc_sql.y"
                                             {
        RelAttr attr;
        // TODO: 更完善地支持 COUNT(expression) 聚合函数（ALL 和 DISTINCT）
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2177 "yacc_sql.tab.c"
    break;

  case 81:
#line 550 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2188 "yacc_sql.tab.c"
    break;

  case 82:
#line 556 "yacc_sql.y"
                                               {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2199 "yacc_sql.tab.c"
    break;

  case 83:
#line 562 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2210 "yacc_sql.tab.c"
    break;

  case 85:
#line 572 "yacc_sql.y"
                         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
    }
#line 2223 "yacc_sql.tab.c"
    break;

  case 86:
#line 580 "yacc_sql.y"
                                {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
    }
#line 2236 "yacc_sql.tab.c"
    break;

  case 87:
#line 588 "yacc_sql.y"
                                   {
             RelAttr attr;
             relation_attr_init(&attr, (yyvsp[-3].string), "*");
//             selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
         // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
         // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
      }
#line 2249 "yacc_sql.tab.c"
    break;

  case 88:
#line 596 "yacc_sql.y"
                                                   {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2260 "yacc_sql.tab.c"
    break;

  case 89:
#line 602 "yacc_sql.y"
                                                          {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2271 "yacc_sql.tab.c"
    break;

  case 90:
#line 608 "yacc_sql.y"
                                                     {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2282 "yacc_sql.tab.c"
    break;

  case 91:
#line 614 "yacc_sql.y"
                                                       {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
//        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2293 "yacc_sql.tab.c"
    break;

  case 93:
#line 624 "yacc_sql.y"
                        {	
//                selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
                selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
          }
#line 2302 "yacc_sql.tab.c"
    break;

  case 95:
#line 631 "yacc_sql.y"
                                     {	
                // CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
            }
#line 2310 "yacc_sql.tab.c"
    break;

  case 97:
#line 637 "yacc_sql.y"
                                   {
                // CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
            }
#line 2318 "yacc_sql.tab.c"
    break;

  case 98:
#line 643 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
#line 2333 "yacc_sql.tab.c"
    break;

  case 99:
#line 654 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 2];
            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 0, NULL, left_value, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
#line 2346 "yacc_sql.tab.c"
    break;

  case 100:
#line 663 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

        }
#line 2362 "yacc_sql.tab.c"
    break;

  case 101:
#line 675 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
#line 2376 "yacc_sql.tab.c"
    break;

  case 102:
#line 685 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
#line 2390 "yacc_sql.tab.c"
    break;

  case 103:
#line 695 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            RelAttr right_attr;
            relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-3].number), 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
#line 2405 "yacc_sql.tab.c"
    break;

  case 104:
#line 706 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
            RelAttr right_attr;
            relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-3].number), 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
#line 2420 "yacc_sql.tab.c"
    break;

  case 105:
#line 717 "yacc_sql.y"
        {
    	    selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-3].string));
	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
	    CONTEXT->condition_length[CONTEXT->select_length]);


	    //临时变量清零
	    CONTEXT->condition_length[CONTEXT->select_length]=0;
	    CONTEXT->from_length[CONTEXT->select_length]=0;
	    CONTEXT->value_length[CONTEXT->select_length] = 0;
	    CONTEXT->select_length--;

	    RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, (yyvsp[-9].string));
	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
	    	CONTEXT->selects[CONTEXT->select_length+1]);
	    Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

	    Condition condition;
	    condition_init(&condition, (yyvsp[-8].number), 1, &left_attr, NULL, 2, NULL, right_value);
	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

	    //处理子查询内存
	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
#line 2450 "yacc_sql.tab.c"
    break;

  case 106:
#line 743 "yacc_sql.y"
    {
            selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-3].string));
    	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
    	    CONTEXT->condition_length[CONTEXT->select_length]);


    	    //临时变量清零
    	    CONTEXT->condition_length[CONTEXT->select_length]=0;
    	    CONTEXT->from_length[CONTEXT->select_length]=0;
    	    CONTEXT->value_length[CONTEXT->select_length] = 0;
    	    CONTEXT->select_length--;

    	    RelAttr left_attr;
                relation_attr_init(&left_attr, (yyvsp[-11].string), (yyvsp[-9].string));
    	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
    	    	CONTEXT->selects[CONTEXT->select_length+1]);
    	    Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

    	    Condition condition;
    	    condition_init(&condition, (yyvsp[-8].number), 1, &left_attr, NULL, 2, NULL, right_value);
    	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

    	    //处理子查询内存
    	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
#line 2480 "yacc_sql.tab.c"
    break;

  case 107:
#line 769 "yacc_sql.y"
    {
    	    selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string));
	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
	    CONTEXT->condition_length[CONTEXT->select_length]);


	    //临时变量清零
	    CONTEXT->condition_length[CONTEXT->select_length]=0;
	    CONTEXT->from_length[CONTEXT->select_length]=0;
	    CONTEXT->value_length[CONTEXT->select_length] = 0;
	    CONTEXT->select_length--;

	    RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
		CONTEXT->selects[CONTEXT->select_length+1]);
	    Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

	    Condition condition;
	    condition_init(&condition, (yyvsp[-1].number), 2, NULL, left_value, 1, &right_attr, NULL);
	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

	    //处理子查询内存
	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
#line 2510 "yacc_sql.tab.c"
    break;

  case 108:
#line 795 "yacc_sql.y"
    {
            selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-7].string));
    	    selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions[CONTEXT->select_length],
    	    CONTEXT->condition_length[CONTEXT->select_length]);


    	    //临时变量清零
    	    CONTEXT->condition_length[CONTEXT->select_length]=0;
    	    CONTEXT->from_length[CONTEXT->select_length]=0;
    	    CONTEXT->value_length[CONTEXT->select_length] = 0;
    	    CONTEXT->select_length--;

    	    RelAttr right_attr;
    		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
    	    value_init_select(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++],
    		CONTEXT->selects[CONTEXT->select_length+1]);
    	    Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

    	    Condition condition;
    	    condition_init(&condition, (yyvsp[-3].number), 2, NULL, left_value, 1, &right_attr, NULL);
    	    CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

    	    //处理子查询内存
    	    memset(&CONTEXT->selects[CONTEXT->select_length+1], 0, sizeof(Selects));
    }
#line 2540 "yacc_sql.tab.c"
    break;

  case 109:
#line 823 "yacc_sql.y"
           { (yyval.number) = EQUAL_TO; }
#line 2546 "yacc_sql.tab.c"
    break;

  case 110:
#line 824 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2552 "yacc_sql.tab.c"
    break;

  case 111:
#line 825 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2558 "yacc_sql.tab.c"
    break;

  case 112:
#line 826 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2564 "yacc_sql.tab.c"
    break;

  case 113:
#line 827 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2570 "yacc_sql.tab.c"
    break;

  case 114:
#line 828 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2576 "yacc_sql.tab.c"
    break;

  case 115:
#line 829 "yacc_sql.y"
          { (yyval.number) = IS; }
#line 2582 "yacc_sql.tab.c"
    break;

  case 116:
#line 830 "yacc_sql.y"
              { (yyval.number) = IS_NOT; }
#line 2588 "yacc_sql.tab.c"
    break;

  case 117:
#line 831 "yacc_sql.y"
         { (yyval.number) = IN_OP; }
#line 2594 "yacc_sql.tab.c"
    break;

  case 118:
#line 832 "yacc_sql.y"
             { (yyval.number) = NOT_IN_OP; }
#line 2600 "yacc_sql.tab.c"
    break;

  case 119:
#line 836 "yacc_sql.y"
          { (yyval.number) = CountAggregate; }
#line 2606 "yacc_sql.tab.c"
    break;

  case 120:
#line 837 "yacc_sql.y"
          { (yyval.number) = SumAggregate; }
#line 2612 "yacc_sql.tab.c"
    break;

  case 121:
#line 838 "yacc_sql.y"
          { (yyval.number) = AvgAggregate; }
#line 2618 "yacc_sql.tab.c"
    break;

  case 122:
#line 839 "yacc_sql.y"
          { (yyval.number) = MaxAggregate; }
#line 2624 "yacc_sql.tab.c"
    break;

  case 123:
#line 840 "yacc_sql.y"
          { (yyval.number) = MinAggregate; }
#line 2630 "yacc_sql.tab.c"
    break;

  case 124:
#line 845 "yacc_sql.y"
        {
          CONTEXT->ssql->flag = SCF_LOAD_DATA;
            load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
        }
#line 2639 "yacc_sql.tab.c"
    break;


#line 2643 "yacc_sql.tab.c"

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
#line 850 "yacc_sql.y"

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
