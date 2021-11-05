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
    GROUP = 317,
    NUMBER = 318,
    FLOAT = 319,
    ID = 320,
    PATH = 321,
    SSS = 322,
    STAR = 323,
    STRING_V = 324
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 138 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _InsertTuple *tuples1;
  char *string;
  int number;
  float floats;
  char *position;

#line 273 "yacc_sql.tab.c"

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
#define YYLAST   335

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  317

#define YYUNDEFTOK  2
#define YYMAXUTOK   324


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
      65,    66,    67,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   169,   169,   171,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   195,   200,   205,   211,   217,   223,   229,   235,   241,
     248,   256,   266,   268,   274,   281,   289,   291,   295,   302,
     337,   338,   339,   343,   346,   347,   348,   349,   350,   353,
     362,   371,   372,   376,   384,   386,   391,   394,   397,   400,
     406,   416,   427,   444,   466,   471,   473,   478,   485,   487,
     492,   499,   501,   508,   517,   519,   526,   536,   537,   538,
     540,   542,   548,   553,   558,   563,   568,   574,   579,   584,
     591,   593,   598,   603,   608,   613,   618,   623,   630,   632,
     636,   638,   641,   643,   647,   658,   667,   679,   689,   699,
     710,   721,   747,   773,   799,   828,   829,   830,   831,   832,
     833,   834,   835,   836,   837,   841,   842,   843,   844,   845,
     849
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
  "BY", "ASC", "IS_", "NOT", "NULL_T", "NULLABLE", "IN", "GROUP", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index",
  "index_attr_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "nullable", "number", "type", "ID_get", "insert",
  "tuple_list", "insert_rbrace", "value_list", "value", "delete", "update",
  "select", "select_begin", "group", "group_attr_list", "order",
  "order_attr_list", "order_type", "join_list", "select_attr", "attr_list",
  "rel_list", "where", "condition_list", "condition", "comOp",
  "aggregation", "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324
};
# endif

#define YYPACT_NINF (-279)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -279,   160,  -279,    13,   118,  -279,   -45,    22,    27,    14,
      23,   -28,    65,    66,    72,    84,    92,    64,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,    49,  -279,    38,    46,   123,
      62,    80,   146,   149,  -279,    89,    90,   124,  -279,  -279,
    -279,  -279,  -279,   114,  -279,  -279,  -279,  -279,  -279,    25,
    -279,   130,   151,   169,   140,   134,   192,   164,  -279,  -279,
     171,   170,   139,   141,    93,    36,  -279,   142,    98,   150,
     152,   180,  -279,   153,   203,    -7,   217,   181,   191,    59,
     207,   206,   206,    -4,   208,    11,   209,  -279,   210,   188,
     211,   165,   226,    69,   222,  -279,  -279,  -279,    77,  -279,
     148,   198,  -279,    69,   227,    44,  -279,   133,  -279,  -279,
     172,   182,   170,   206,   206,   173,   206,   150,   219,  -279,
    -279,  -279,  -279,  -279,     7,   174,   218,  -279,   223,    49,
     175,  -279,  -279,  -279,  -279,  -279,  -279,   184,   183,  -279,
      15,   119,    -7,  -279,   170,   178,   206,   206,   228,    30,
     229,   230,   185,   187,  -279,  -279,   234,  -279,   210,   244,
     189,   194,  -279,  -279,   236,   190,    69,   239,   225,   148,
    -279,  -279,   222,  -279,  -279,   231,  -279,   198,   255,   256,
    -279,  -279,   206,   206,   196,   206,  -279,   232,   212,   215,
     206,  -279,  -279,  -279,   245,  -279,   199,   246,   236,   223,
    -279,   247,   201,    26,    49,   205,  -279,  -279,  -279,  -279,
    -279,   254,  -279,    -7,   213,   220,   269,  -279,    88,   236,
     270,   257,  -279,   260,   274,   230,   222,   250,  -279,   248,
    -279,   206,   198,    63,   216,  -279,  -279,  -279,  -279,   279,
      69,  -279,   170,    49,   221,   224,  -279,   233,   235,   237,
    -279,     5,  -279,   223,   266,   252,  -279,   230,   238,   170,
      76,   272,  -279,   240,  -279,   275,   239,   148,   241,   170,
     242,   284,   243,  -279,  -279,     8,   249,  -279,   247,   251,
     230,   271,   258,  -279,   272,   275,     6,  -279,   263,   170,
    -279,    -7,  -279,  -279,   253,   275,   259,   278,   198,     8,
    -279,  -279,  -279,   233,   275,  -279,  -279
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
      26,    22,    21,     0,   125,   126,   127,   128,   129,    90,
      82,     0,     0,     0,     0,     0,     0,     0,    29,    28,
       0,   100,     0,     0,     0,     0,    83,     0,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,     0,    90,
       0,    90,    90,    98,     0,     0,     0,    49,    36,     0,
       0,     0,     0,     0,     0,    56,    57,    58,     0,    59,
       0,   102,    60,     0,     0,     0,    91,     0,    85,    84,
       0,     0,   100,    90,    90,     0,    90,     0,     0,    44,
      47,    45,    46,    48,    40,     0,     0,    34,    54,     0,
       0,   115,   116,   117,   118,   119,   120,   121,     0,   123,
       0,     0,     0,   101,   100,     0,    90,    90,     0,     0,
       0,    98,     0,    65,    89,    86,     0,    88,    36,     0,
       0,     0,    41,    39,    32,     0,     0,     0,     0,     0,
     122,   124,     0,   106,   104,   107,   105,   102,     0,     0,
      92,    93,    90,    90,     0,    90,    99,     0,     0,    71,
      90,    37,    35,    43,     0,    42,     0,     0,    32,    54,
      53,    51,     0,     0,     0,     0,   103,    61,   130,    97,
      94,     0,    96,     0,     0,     0,     0,    87,    40,    32,
       0,     0,    55,     0,     0,    98,     0,     0,   108,     0,
     109,    90,   102,    68,     0,    62,    38,    33,    30,     0,
       0,    50,   100,     0,     0,     0,    95,    80,     0,     0,
      66,    77,    31,    54,     0,     0,   110,    98,     0,   100,
      68,    68,    79,     0,    78,    74,     0,     0,     0,   100,
       0,     0,     0,    69,    67,    77,     0,    72,    51,     0,
      98,     0,     0,    63,    68,    74,    77,    52,   113,   100,
     111,     0,    70,    73,     0,    74,     0,     0,   102,    77,
      75,   114,   112,    80,    74,    81,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -184,  -279,  -279,   128,   176,    70,  -279,
    -279,  -279,  -279,     9,    28,  -197,  -100,  -279,  -279,  -279,
     -99,  -279,  -245,  -279,  -278,  -263,   -14,  -128,   -85,  -151,
    -122,  -179,  -150,  -109,   261,  -279
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   207,    29,    30,   128,    98,   173,   204,
     134,    99,    31,   234,   211,   177,   110,    32,    33,    34,
      35,   199,   260,   226,   287,   275,   269,    61,    76,   122,
      86,   153,   111,   150,    62,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     163,   151,   187,   138,   116,   139,   118,   119,   216,   104,
     196,   178,   232,   154,   120,   272,   272,   303,   272,    37,
      42,    38,   295,   170,   231,   283,   284,   310,   124,    43,
      44,   182,   188,   305,   273,   304,   316,    47,   164,   165,
     125,   167,   236,    74,    45,   247,   314,   193,   121,   302,
     184,   186,   105,    39,    75,    46,   106,   107,   108,   194,
     109,   274,   274,   257,   274,   171,   276,   172,    48,    49,
     213,   190,   191,   242,   105,    50,   209,    74,   106,   107,
     183,   258,   109,   214,   252,   105,   239,    51,   115,   106,
     107,   237,   259,   109,   258,    52,    54,    55,    56,    57,
      58,    91,    53,    63,    92,   282,   140,   219,   220,   156,
     222,    64,   157,   238,    59,   227,   279,    60,   141,   142,
     143,   144,   145,   146,    40,   265,    41,    66,   105,   313,
     264,    65,   106,   107,   147,   148,   109,   253,   149,   299,
      54,    55,    56,    57,    58,    67,   171,   281,   172,    68,
     263,   308,    69,    73,    70,    71,   256,   291,    89,    72,
       2,    94,    77,    95,     3,     4,    96,    78,   289,     5,
       6,     7,     8,     9,    10,    11,    80,   307,   105,    12,
      13,    14,   106,   107,   185,    79,   109,    15,    16,   141,
     142,   143,   144,   145,   146,    82,   158,    17,   159,    81,
      83,   160,    84,    85,    87,   147,   148,    93,    88,   149,
     129,   130,   131,   132,   133,    97,   101,   100,   102,   103,
     112,   114,   113,   117,    74,   123,   126,   135,   127,   137,
     136,     5,   152,   155,   175,   162,   169,   161,   166,   174,
     179,   176,   180,   189,   181,   192,   195,   202,   120,   198,
     197,   200,   203,   205,   206,   208,   210,   212,   217,   218,
     215,   221,   228,   230,   229,   233,   235,   224,   223,   225,
     240,   241,   245,   248,   249,   244,   250,   251,   243,   254,
     255,   261,   262,   277,   278,   268,   266,   293,   300,   267,
     258,   280,   306,   286,   301,   312,   201,   297,   246,   315,
     270,     0,   271,   168,   288,   285,   290,   292,   294,     0,
       0,     0,     0,     0,   296,     0,   298,     0,   309,     0,
       0,     0,     0,     0,   311,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90
};

static const yytype_int16 yycheck[] =
{
     122,   110,   152,   103,    89,   104,    91,    92,   187,    16,
     161,   139,   209,   113,    18,    10,    10,   295,    10,     6,
      65,     8,   285,    16,   208,   270,   271,   305,    17,     7,
       3,    16,   154,   296,    29,    29,   314,    65,   123,   124,
      29,   126,    16,    18,    30,   229,   309,    17,    52,   294,
     150,   151,    59,    40,    29,    32,    63,    64,    65,    29,
      67,    56,    56,   242,    56,    58,   263,    60,     3,     3,
     179,   156,   157,   223,    59,     3,   176,    18,    63,    64,
      65,    18,    67,   182,   235,    59,   214,     3,    29,    63,
      64,    65,    29,    67,    18,     3,    47,    48,    49,    50,
      51,    65,    38,    65,    68,    29,    29,   192,   193,    65,
     195,    65,    68,   213,    65,   200,   267,    68,    41,    42,
      43,    44,    45,    46,     6,   253,     8,    65,    59,   308,
     252,     8,    63,    64,    57,    58,    67,   236,    61,   290,
      47,    48,    49,    50,    51,    65,    58,   269,    60,     3,
     250,   301,     3,    39,    65,    65,   241,   279,    65,    35,
       0,    63,    32,    65,     4,     5,    68,    16,   277,     9,
      10,    11,    12,    13,    14,    15,    36,   299,    59,    19,
      20,    21,    63,    64,    65,    16,    67,    27,    28,    41,
      42,    43,    44,    45,    46,     3,    63,    37,    65,    65,
      36,    68,    31,    33,    65,    57,    58,    65,    67,    61,
      22,    23,    24,    25,    26,    65,    36,    65,    65,    16,
       3,    30,    41,    16,    18,    17,    17,    16,    18,     3,
      65,     9,    34,     6,    16,    53,    17,    65,    65,    65,
      65,    18,    58,    65,    61,    17,    17,     3,    18,    62,
      65,    17,    63,    59,    18,    65,    17,    32,     3,     3,
      29,    65,    17,    17,    65,    18,    65,    55,    36,    54,
      65,    17,     3,     3,    17,    55,    16,     3,    65,    29,
      32,    65,     3,    17,    32,    52,    65,     3,    17,    65,
      18,    53,    29,    18,    36,    17,   168,   288,   228,   313,
      65,    -1,    65,   127,   276,    65,    65,    65,    65,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    65,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    27,    28,    37,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      85,    92,    97,    98,    99,   100,   115,     6,     8,    40,
       6,     8,    65,     7,     3,    30,    32,    65,     3,     3,
       3,     3,     3,    38,    47,    48,    49,    50,    51,    65,
      68,   107,   114,    65,    65,     8,    65,    65,     3,     3,
      65,    65,    35,    39,    18,    29,   108,    32,    16,    16,
      36,    65,     3,    36,    31,    33,   110,    65,    67,    65,
     114,    65,    68,    65,    63,    65,    68,    65,    87,    91,
      65,    36,    65,    16,    16,    59,    63,    64,    65,    67,
      96,   112,     3,    41,    30,    29,   108,    16,   108,   108,
      18,    52,   109,    17,    17,    29,    17,    18,    86,    22,
      23,    24,    25,    26,    90,    16,    65,     3,    96,   100,
      29,    41,    42,    43,    44,    45,    46,    57,    58,    61,
     113,   113,    34,   111,    96,     6,    65,    68,    63,    65,
      68,    65,    53,   110,   108,   108,    65,   108,    87,    17,
      16,    58,    60,    88,    65,    16,    18,    95,   107,    65,
      58,    61,    16,    65,    96,    65,    96,   112,   110,    65,
     108,   108,    17,    17,    29,    17,   109,    65,    62,   101,
      17,    86,     3,    63,    89,    59,    18,    83,    65,    96,
      17,    94,    32,   113,   100,    29,   111,     3,     3,   108,
     108,    65,   108,    36,    55,    54,   103,   108,    17,    65,
      17,    83,    95,    18,    93,    65,    16,    65,    96,   107,
      65,    17,   112,    65,    55,     3,    88,    83,     3,    17,
      16,     3,   109,   100,    29,    32,   108,   111,    18,    29,
     102,    65,     3,    96,   110,   107,    65,    65,    52,   106,
      65,    65,    10,    29,    56,   105,    95,    17,    32,   109,
      53,   110,    29,   102,   102,    65,    18,   104,    94,   113,
      65,   110,    65,     3,    65,   105,    65,    93,    65,   109,
      17,    36,   102,   104,    29,   105,    29,   110,   112,    65,
     104,    65,    17,   111,   105,   106,   104
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    82,    83,    83,    84,    85,    86,    86,    87,    87,
      88,    88,    88,    89,    90,    90,    90,    90,    90,    91,
      92,    93,    93,    94,    95,    95,    96,    96,    96,    96,
      97,    98,    99,    99,   100,   101,   101,   101,   102,   102,
     102,   103,   103,   103,   104,   104,   104,   105,   105,   105,
     106,   106,   107,   107,   107,   107,   107,   107,   107,   107,
     108,   108,   108,   108,   108,   108,   108,   108,   109,   109,
     110,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     115
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
       5,     8,     9,    13,     1,     0,     4,     6,     0,     3,
       5,     0,     5,     7,     0,     4,     6,     0,     1,     1,
       0,     7,     1,     2,     4,     4,     5,     7,     5,     5,
       0,     3,     5,     5,     6,     8,     6,     6,     0,     3,
       0,     3,     0,     3,     3,     3,     3,     3,     5,     5,
       7,    10,    12,    10,    12,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     1,     1,     1,     1,
       8
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
#line 195 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1677 "yacc_sql.tab.c"
    break;

  case 22:
#line 200 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1685 "yacc_sql.tab.c"
    break;

  case 23:
#line 205 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1693 "yacc_sql.tab.c"
    break;

  case 24:
#line 211 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1701 "yacc_sql.tab.c"
    break;

  case 25:
#line 217 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1709 "yacc_sql.tab.c"
    break;

  case 26:
#line 223 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1717 "yacc_sql.tab.c"
    break;

  case 27:
#line 229 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1726 "yacc_sql.tab.c"
    break;

  case 28:
#line 235 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1734 "yacc_sql.tab.c"
    break;

  case 29:
#line 241 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1743 "yacc_sql.tab.c"
    break;

  case 30:
#line 249 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-3].string);
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 0);
            CONTEXT->index_attr_num = 0;
        }
#line 1755 "yacc_sql.tab.c"
    break;

  case 31:
#line 257 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_CREATE_INDEX; //"create_index";
            CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-3].string);
            create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 
                CONTEXT->index_attrs, CONTEXT->index_attr_num, 1);
            CONTEXT->index_attr_num = 0;
        }
#line 1767 "yacc_sql.tab.c"
    break;

  case 33:
#line 269 "yacc_sql.y"
    {
        CONTEXT->index_attrs[CONTEXT->index_attr_num++] = (yyvsp[-1].string);
    }
#line 1775 "yacc_sql.tab.c"
    break;

  case 34:
#line 275 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
		drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-3].string), (yyvsp[-1].string));
	}
#line 1784 "yacc_sql.tab.c"
    break;

  case 35:
#line 282 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
            create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
            //临时变量清零	
            CONTEXT->value_length[0] = 0;
        }
#line 1795 "yacc_sql.tab.c"
    break;

  case 37:
#line 291 "yacc_sql.y"
                                   {    }
#line 1801 "yacc_sql.tab.c"
    break;

  case 38:
#line 296 "yacc_sql.y"
        {
            AttrInfo attribute;
            attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
            create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
            CONTEXT->value_length[0]++;
        }
#line 1812 "yacc_sql.tab.c"
    break;

  case 39:
#line 303 "yacc_sql.y"
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
#line 1848 "yacc_sql.tab.c"
    break;

  case 40:
#line 337 "yacc_sql.y"
                { (yyval.number) = 0; }
#line 1854 "yacc_sql.tab.c"
    break;

  case 41:
#line 338 "yacc_sql.y"
               { (yyval.number) = 1; }
#line 1860 "yacc_sql.tab.c"
    break;

  case 42:
#line 339 "yacc_sql.y"
                 { (yyval.number) = 0; }
#line 1866 "yacc_sql.tab.c"
    break;

  case 43:
#line 343 "yacc_sql.y"
               {(yyval.number) = (yyvsp[0].number);}
#line 1872 "yacc_sql.tab.c"
    break;

  case 44:
#line 346 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1878 "yacc_sql.tab.c"
    break;

  case 45:
#line 347 "yacc_sql.y"
                 { (yyval.number) = FLOATS; }
#line 1884 "yacc_sql.tab.c"
    break;

  case 46:
#line 348 "yacc_sql.y"
                { (yyval.number) = DATES; }
#line 1890 "yacc_sql.tab.c"
    break;

  case 47:
#line 349 "yacc_sql.y"
                  { (yyval.number) = CHARS; }
#line 1896 "yacc_sql.tab.c"
    break;

  case 48:
#line 350 "yacc_sql.y"
                { (yyval.number) = TEXTS; }
#line 1902 "yacc_sql.tab.c"
    break;

  case 49:
#line 354 "yacc_sql.y"
    {
        char *temp=(yyvsp[0].string); 
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1911 "yacc_sql.tab.c"
    break;

  case 50:
#line 363 "yacc_sql.y"
        {
            CONTEXT->ssql->flag=SCF_INSERT; //"insert";
            inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->tuples, CONTEXT->tuple_num);
            // 临时变量清零
            CONTEXT->value_length[0] = 0;
            CONTEXT->tuple_num = 0;
    }
#line 1923 "yacc_sql.tab.c"
    break;

  case 52:
#line 372 "yacc_sql.y"
                                                             {
    }
#line 1930 "yacc_sql.tab.c"
    break;

  case 53:
#line 376 "yacc_sql.y"
           {
        // 此规则用于表明读取到一个要 insert 的 tuple，并提高此操作的优先级
        InsertTuple tuple;
        insert_tuple_init(&tuple, CONTEXT->values, CONTEXT->value_length[0]);
        CONTEXT->tuples[CONTEXT->tuple_num++] = tuple;
        CONTEXT->value_length[0] = 0;
    }
#line 1942 "yacc_sql.tab.c"
    break;

  case 55:
#line 386 "yacc_sql.y"
                              { 
          // CONTEXT->values[CONTEXT->value_length++] = *$2;
      }
#line 1950 "yacc_sql.tab.c"
    break;

  case 56:
#line 391 "yacc_sql.y"
           {
        value_init_null(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++]);
    }
#line 1958 "yacc_sql.tab.c"
    break;

  case 57:
#line 394 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].number));
    }
#line 1966 "yacc_sql.tab.c"
    break;

  case 58:
#line 397 "yacc_sql.y"
          {
        value_init_float(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].floats));
    }
#line 1974 "yacc_sql.tab.c"
    break;

  case 59:
#line 400 "yacc_sql.y"
         {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length]++], (yyvsp[0].string));
    }
#line 1983 "yacc_sql.tab.c"
    break;

  case 60:
#line 407 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_DELETE;//"delete";
            deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
            deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
    }
#line 1995 "yacc_sql.tab.c"
    break;

  case 61:
#line 417 "yacc_sql.y"
        {
            CONTEXT->ssql->flag = SCF_UPDATE;//"update";
            Value *value = &CONTEXT->values[0];
            updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
                    CONTEXT->conditions[0], CONTEXT->condition_length[0]);
            CONTEXT->condition_length[0] = 0;
        }
#line 2007 "yacc_sql.tab.c"
    break;

  case 62:
#line 428 "yacc_sql.y"
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
#line 2028 "yacc_sql.tab.c"
    break;

  case 63:
#line 445 "yacc_sql.y"
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
#line 2051 "yacc_sql.tab.c"
    break;

  case 64:
#line 467 "yacc_sql.y"
        {
    	CONTEXT->select_length++;
    }
#line 2059 "yacc_sql.tab.c"
    break;

  case 66:
#line 473 "yacc_sql.y"
                                  {
	RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2069 "yacc_sql.tab.c"
    break;

  case 67:
#line 478 "yacc_sql.y"
                                         {
	RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2079 "yacc_sql.tab.c"
    break;

  case 69:
#line 487 "yacc_sql.y"
                               {
	RelAttr attr;
	relation_attr_init(&attr, NULL, (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2089 "yacc_sql.tab.c"
    break;

  case 70:
#line 492 "yacc_sql.y"
                                      {
	RelAttr attr;
	relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_group_by(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2099 "yacc_sql.tab.c"
    break;

  case 72:
#line 501 "yacc_sql.y"
                                             {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2111 "yacc_sql.tab.c"
    break;

  case 73:
#line 508 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2123 "yacc_sql.tab.c"
    break;

  case 75:
#line 519 "yacc_sql.y"
                                          {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2135 "yacc_sql.tab.c"
    break;

  case 76:
#line 526 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
        OrderBy order_attr;
        order_attr_init(&order_attr, &attr, (yyvsp[-1].number));
        selects_append_order_by(&CONTEXT->selects[CONTEXT->select_length], &order_attr);
    }
#line 2147 "yacc_sql.tab.c"
    break;

  case 77:
#line 536 "yacc_sql.y"
                { (yyval.number) = AscOrder; }
#line 2153 "yacc_sql.tab.c"
    break;

  case 78:
#line 537 "yacc_sql.y"
          { (yyval.number) = AscOrder; }
#line 2159 "yacc_sql.tab.c"
    break;

  case 79:
#line 538 "yacc_sql.y"
           { (yyval.number) = DescOrder; }
#line 2165 "yacc_sql.tab.c"
    break;

  case 81:
#line 543 "yacc_sql.y"
    {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
    }
#line 2173 "yacc_sql.tab.c"
    break;

  case 82:
#line 548 "yacc_sql.y"
         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2183 "yacc_sql.tab.c"
    break;

  case 83:
#line 553 "yacc_sql.y"
                   {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2193 "yacc_sql.tab.c"
    break;

  case 84:
#line 558 "yacc_sql.y"
                            {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2203 "yacc_sql.tab.c"
    break;

  case 85:
#line 563 "yacc_sql.y"
                          {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2213 "yacc_sql.tab.c"
    break;

  case 86:
#line 568 "yacc_sql.y"
                                             {
        RelAttr attr;
        // TODO: 更完善地支持 COUNT(expression) 聚合函数（ALL 和 DISTINCT）
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2224 "yacc_sql.tab.c"
    break;

  case 87:
#line 574 "yacc_sql.y"
                                                    {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2234 "yacc_sql.tab.c"
    break;

  case 88:
#line 579 "yacc_sql.y"
                                               {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2244 "yacc_sql.tab.c"
    break;

  case 89:
#line 584 "yacc_sql.y"
                                                 {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2254 "yacc_sql.tab.c"
    break;

  case 91:
#line 593 "yacc_sql.y"
                         {
        RelAttr attr;
        relation_attr_init(&attr, NULL, (yyvsp[-1].string));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2264 "yacc_sql.tab.c"
    break;

  case 92:
#line 598 "yacc_sql.y"
                                {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2274 "yacc_sql.tab.c"
    break;

  case 93:
#line 603 "yacc_sql.y"
                                   {
        RelAttr attr;
        relation_attr_init(&attr, (yyvsp[-3].string), "*");
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
      }
#line 2284 "yacc_sql.tab.c"
    break;

  case 94:
#line 608 "yacc_sql.y"
                                                   {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, (yyvsp[-2].string), (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2294 "yacc_sql.tab.c"
    break;

  case 95:
#line 613 "yacc_sql.y"
                                                          {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, (yyvsp[-4].string), (yyvsp[-2].string), (yyvsp[-6].number));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2304 "yacc_sql.tab.c"
    break;

  case 96:
#line 618 "yacc_sql.y"
                                                     {
        RelAttr attr;
        relation_attr_init_with_aggregation(&attr, NULL, "*", (yyvsp[-4].number));
	selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2314 "yacc_sql.tab.c"
    break;

  case 97:
#line 623 "yacc_sql.y"
                                                       {
        RelAttr attr;
        relation_attr_init_with_number_aggregation(&attr, (yyvsp[-2].number), (yyvsp[-4].number));
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 2324 "yacc_sql.tab.c"
    break;

  case 99:
#line 632 "yacc_sql.y"
                        {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
    }
#line 2332 "yacc_sql.tab.c"
    break;

  case 101:
#line 638 "yacc_sql.y"
                                     {
     }
#line 2339 "yacc_sql.tab.c"
    break;

  case 103:
#line 643 "yacc_sql.y"
                                   {
     }
#line 2346 "yacc_sql.tab.c"
    break;

  case 104:
#line 648 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
#line 2361 "yacc_sql.tab.c"
    break;

  case 105:
#line 659 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 2];
            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 0, NULL, left_value, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
#line 2374 "yacc_sql.tab.c"
    break;

  case 106:
#line 668 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;

        }
#line 2390 "yacc_sql.tab.c"
    break;

  case 107:
#line 680 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];
            RelAttr right_attr;
            relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
        }
#line 2404 "yacc_sql.tab.c"
    break;

  case 108:
#line 690 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
            Value *right_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            Condition condition;
            condition_init(&condition, (yyvsp[-1].number), 1, &left_attr, NULL, 0, NULL, right_value);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
#line 2418 "yacc_sql.tab.c"
    break;

  case 109:
#line 700 "yacc_sql.y"
        {
            Value *left_value = &CONTEXT->values[CONTEXT->value_length[CONTEXT->select_length] - 1];

            RelAttr right_attr;
            relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-3].number), 0, NULL, left_value, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
#line 2433 "yacc_sql.tab.c"
    break;

  case 110:
#line 711 "yacc_sql.y"
        {
            RelAttr left_attr;
            relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
            RelAttr right_attr;
            relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

            Condition condition;
            condition_init(&condition, (yyvsp[-3].number), 1, &left_attr, NULL, 1, &right_attr, NULL);
            CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++] = condition;
    }
#line 2448 "yacc_sql.tab.c"
    break;

  case 111:
#line 722 "yacc_sql.y"
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
#line 2478 "yacc_sql.tab.c"
    break;

  case 112:
#line 748 "yacc_sql.y"
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
#line 2508 "yacc_sql.tab.c"
    break;

  case 113:
#line 774 "yacc_sql.y"
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
#line 2538 "yacc_sql.tab.c"
    break;

  case 114:
#line 800 "yacc_sql.y"
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
#line 2568 "yacc_sql.tab.c"
    break;

  case 115:
#line 828 "yacc_sql.y"
           { (yyval.number) = EQUAL_TO; }
#line 2574 "yacc_sql.tab.c"
    break;

  case 116:
#line 829 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2580 "yacc_sql.tab.c"
    break;

  case 117:
#line 830 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2586 "yacc_sql.tab.c"
    break;

  case 118:
#line 831 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2592 "yacc_sql.tab.c"
    break;

  case 119:
#line 832 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2598 "yacc_sql.tab.c"
    break;

  case 120:
#line 833 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2604 "yacc_sql.tab.c"
    break;

  case 121:
#line 834 "yacc_sql.y"
          { (yyval.number) = IS; }
#line 2610 "yacc_sql.tab.c"
    break;

  case 122:
#line 835 "yacc_sql.y"
              { (yyval.number) = IS_NOT; }
#line 2616 "yacc_sql.tab.c"
    break;

  case 123:
#line 836 "yacc_sql.y"
         { (yyval.number) = IN_OP; }
#line 2622 "yacc_sql.tab.c"
    break;

  case 124:
#line 837 "yacc_sql.y"
             { (yyval.number) = NOT_IN_OP; }
#line 2628 "yacc_sql.tab.c"
    break;

  case 125:
#line 841 "yacc_sql.y"
          { (yyval.number) = CountAggregate; }
#line 2634 "yacc_sql.tab.c"
    break;

  case 126:
#line 842 "yacc_sql.y"
          { (yyval.number) = SumAggregate; }
#line 2640 "yacc_sql.tab.c"
    break;

  case 127:
#line 843 "yacc_sql.y"
          { (yyval.number) = AvgAggregate; }
#line 2646 "yacc_sql.tab.c"
    break;

  case 128:
#line 844 "yacc_sql.y"
          { (yyval.number) = MaxAggregate; }
#line 2652 "yacc_sql.tab.c"
    break;

  case 129:
#line 845 "yacc_sql.y"
          { (yyval.number) = MinAggregate; }
#line 2658 "yacc_sql.tab.c"
    break;

  case 130:
#line 850 "yacc_sql.y"
        {
          CONTEXT->ssql->flag = SCF_LOAD_DATA;
            load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
        }
#line 2667 "yacc_sql.tab.c"
    break;


#line 2671 "yacc_sql.tab.c"

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
#line 855 "yacc_sql.y"

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
