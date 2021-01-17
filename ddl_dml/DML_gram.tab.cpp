/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "DML_gram.y"

#include "DDL_public.h"
#include "Node.h"
#include "DML_gram.tab.h"

extern int yylex();
extern int yyerror(const char * format,...);
extern void strcopy(char*& src,char*& dest);

void set_node(int type);
void dividetypes(vector<int>& v,int sum);
void divideToNum(vector<int>& v,int sum);

struct yy_buffer_state;
#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif
extern void yy_switch_to_buffer (YY_BUFFER_STATE new_buffer);
extern YY_BUFFER_STATE yy_scan_string ( const char *yy_str  );

DDLStmt g_DDLStmt;


/* Line 371 of yacc.c  */
#line 93 "DML_gram.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "DML_gram.tab.h".  */
#ifndef YY_YY_DML_GRAM_TAB_H_INCLUDED
# define YY_YY_DML_GRAM_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LF = 258,
     RF = 259,
     ST = 260,
     FM = 261,
     WH = 262,
     UPT = 263,
     DEL = 264,
     IST = 265,
     VAL = 266,
     INTO = 267,
     SET = 268,
     WHSPLIT = 269,
     T_LT = 270,
     T_LE = 271,
     T_GT = 272,
     T_GE = 273,
     T_EQ = 274,
     T_NE = 275,
     IN = 276,
     ORDER = 277,
     BY = 278,
     ORTYPE = 279,
     DISTINCT = 280,
     AGGRET = 281,
     EXIT = 282,
     NUMBER = 283,
     PARA_STRING = 284,
     SUBQUERY = 285,
     NATURAL = 286,
     DML_JOIN = 287,
     MULTI = 288,
     EXEC = 289,
     DISCARD = 290,
     USE = 291,
     NAME = 292,
     INTNUM = 293,
     BOOL = 294,
     APPROXNUM = 295,
     DDL_OR = 296,
     XOR = 297,
     ANDOP = 298,
     COMPARISON = 299,
     SHIFT = 300,
     TABLE = 301,
     CREATE = 302,
     PRIMARY = 303,
     KEY = 304,
     NOT = 305,
     NULLX = 306,
     INT_DDL = 307,
     FLOAT_DDL = 308,
     STRING_DDL = 309,
     VARCHAR_DDL = 310,
     REAL = 311,
     TEXT = 312,
     DATABASE = 313,
     DROP = 314,
     ALTER = 315,
     INDEX = 316,
     COLUMN = 317,
     CONSTRAINT = 318,
     ADD = 319,
     MODIFY = 320,
     TYPE = 321,
     UNIQUE = 322,
     ON = 323,
     CONNECT = 324,
     TO = 325,
     RESET = 326
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 27 "DML_gram.y"

	M_DML::Attribute *attribute;
	M_DML::OrderNode *orderNode;
	M_DML::Relation *relation;
	M_DML::Operator *soperator;
	M_DML::SelList	*selList;
	M_DML::FromList *fromList;
	M_DML::Condition *condision;
	M_DML::OrderList *orderList;
	M_DML::GroupList *groupList;
	M_DML::Query *query;
	M_DML::Number* rNumber;
	M_DML::ParaString* pString;
	
	M_DML::Name* name;
    vector<M_DML::Name*>* nameList;
    
	string* text;
	int type;
	
	M_DML::Insert* insert;
	vector<string>* values;
	
	M_DML::Delete* del;
	
	M_DML::Update* upd;
	string* attr_index[2];
	map<string, string>* attr_indexs;

	PhyPlanNode* phyNode;
	vector<PhyPlanNode*>* phyNodes; 

	NodeStorage* nodestorage;

	/* ddl */
	int					intval;
	double				floatval;
	char*				strval;
	int					subtok;
	CreateTableStmt*	createtablestmt;


/* Line 387 of yacc.c  */
#line 250 "DML_gram.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_DML_GRAM_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 278 "DML_gram.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
/* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
    yytype_int16 yyss_alloc;
    YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   196

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNRULES -- Number of states.  */
#define YYNSTATES  217

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   326

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
        {
                0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
                2,     2,     2,     2,     2,     2,     2,     2,     2,    76,
                2,     2,    73,     2,    74,     2,    75,     2,     2,     2,
                2,     2,     2,     2,     2,     2,     2,     2,     2,    72,
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
                65,    66,    67,    68,    69,    70,    71
        };

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    22,
      26,    30,    32,    35,    37,    39,    41,    43,    46,    49,
      51,    56,    62,    65,    68,    71,    74,    76,    78,    81,
      84,    89,    92,    94,    98,   102,   104,   106,   110,   112,
     116,   118,   122,   124,   127,   129,   133,   138,   140,   145,
     148,   150,   154,   162,   164,   168,   170,   174,   178,   180,
     182,   186,   188,   190,   191,   194,   196,   198,   200,   202,
     204,   206,   208,   215,   217,   221,   225,   231,   233,   237,
     238,   242,   246,   249,   251,   253,   258,   260,   264,   270,
     279,   281,   285,   289,   293,   298,   302,   306,   310,   316,
     321,   329,   338,   340,   344,   348,   351,   353,   355,   357,
     359,   361,   363
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      78,     0,    -1,    79,    -1,    83,    72,    -1,    85,    72,
      -1,    80,    72,    -1,    81,    72,    -1,   110,    72,    -1,
      84,    -1,    33,    82,    34,    -1,    33,    82,    35,    -1,
      83,    -1,    83,    82,    -1,    86,    -1,    87,    -1,    88,
      -1,   103,    -1,    27,    72,    -1,    36,    37,    -1,    89,
      -1,     9,     6,    37,    93,    -1,     8,    37,    13,   105,
      93,    -1,    90,    92,    -1,    89,    93,    -1,    89,    97,
      -1,     5,    91,    -1,   100,    -1,    73,    -1,    25,    91,
      -1,     6,   100,    -1,     6,     3,    89,     4,    -1,     7,
      94,    -1,    95,    -1,    95,    14,    94,    -1,   101,   127,
      96,    -1,   101,    -1,   109,    -1,     3,    89,     4,    -1,
     108,    -1,    22,    23,    98,    -1,    99,    -1,    99,    74,
      98,    -1,   102,    -1,   102,    24,    -1,   101,    -1,   101,
      74,   100,    -1,   101,    31,    32,   100,    -1,   102,    -1,
      26,     3,   102,     4,    -1,   101,    37,    -1,    37,    -1,
      37,    75,    37,    -1,    10,    12,    37,    11,     3,   104,
       4,    -1,   107,    -1,   107,    74,   104,    -1,   106,    -1,
     106,    74,   105,    -1,    37,    19,   107,    -1,   108,    -1,
     109,    -1,    76,    37,    76,    -1,    38,    -1,    40,    -1,
      -1,   110,   111,    -1,   112,    -1,   118,    -1,   119,    -1,
     121,    -1,   122,    -1,   125,    -1,   126,    -1,    47,    46,
      37,     3,   113,     4,    -1,   114,    -1,   113,    74,   114,
      -1,    37,   117,   116,    -1,    48,    49,     3,   115,     4,
      -1,    37,    -1,   115,    74,    37,    -1,    -1,   116,    50,
      51,    -1,   116,    48,    49,    -1,   116,    67,    -1,    52,
      -1,    53,    -1,    54,     3,    38,     4,    -1,    55,    -1,
      47,    58,    37,    -1,    47,    61,    37,    68,    37,    -1,
      47,    61,    37,    68,    37,     3,   120,     4,    -1,    37,
      -1,   120,    74,    37,    -1,    59,    46,    37,    -1,    59,
      58,    37,    -1,    60,    46,    37,   123,    -1,    59,    63,
      37,    -1,    64,    37,   117,    -1,    59,    62,    37,    -1,
      60,    62,    37,    66,   117,    -1,    65,    37,   117,   116,
      -1,    64,    63,    37,    67,     3,   124,     4,    -1,    64,
      63,    37,    48,    49,     3,   124,     4,    -1,    37,    -1,
     124,    74,    37,    -1,    69,    70,    37,    -1,    69,    71,
      -1,    15,    -1,    16,    -1,    17,    -1,    18,    -1,    19,
      -1,    20,    -1,    21,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   155,   161,   165,   169,   173,   180,   184,
     204,   211,   216,   224,   229,   233,   237,   244,   251,   259,
     290,   326,   364,   370,   375,   384,   391,   401,   408,   416,
     426,   434,   442,   447,   459,   493,   500,   506,   513,   522,
     529,   535,   543,   549,   558,   564,   569,   580,   584,   590,
     599,   605,   616,   645,   650,   658,   664,   673,   683,   687,
     694,   703,   708,   718,   719,   722,   723,   724,   725,   726,
     727,   728,   734,   743,   747,   754,   762,   776,   786,   800,
     801,   802,   803,   807,   808,   809,   810,   815,   824,   830,
     839,   843,   851,   857,   867,   874,   879,   887,   894,   902,
     911,   917,   926,   932,   941,   949,   956,   960,   964,   968,
     972,   976,   980
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LF", "RF", "ST", "FM", "WH", "UPT",
  "DEL", "IST", "VAL", "INTO", "SET", "WHSPLIT", "T_LT", "T_LE", "T_GT",
  "T_GE", "T_EQ", "T_NE", "IN", "ORDER", "BY", "ORTYPE", "DISTINCT",
  "AGGRET", "EXIT", "NUMBER", "PARA_STRING", "SUBQUERY", "NATURAL",
  "DML_JOIN", "MULTI", "EXEC", "DISCARD", "USE", "NAME", "INTNUM", "BOOL",
  "APPROXNUM", "DDL_OR", "XOR", "ANDOP", "COMPARISON", "SHIFT", "TABLE",
  "CREATE", "PRIMARY", "KEY", "NOT", "NULLX", "INT_DDL", "FLOAT_DDL",
  "STRING_DDL", "VARCHAR_DDL", "REAL", "TEXT", "DATABASE", "DROP", "ALTER",
  "INDEX", "COLUMN", "CONSTRAINT", "ADD", "MODIFY", "TYPE", "UNIQUE", "ON",
  "CONNECT", "TO", "RESET", "';'", "'*'", "','", "'.'", "'\\''", "$accept",
  "command", "utility", "dowork", "cancelwork", "dmls", "dml", "exit",
  "chooseDB", "query", "delete", "update", "stmt", "st_list", "st_nodes",
  "fm_list", "wh_list", "whname_list", "whname", "whvalue", "order",
  "order_list", "order_node", "name_list", "table_attr", "attr_name",
  "insert", "value_list", "set_list", "set_value", "insert_value",
  "para_string", "number", "DDL_commands", "DDL_command",
  "create_table_stmt", "create_col_list", "create_definition",
  "column_list", "column_atts", "data_type", "create_database",
  "create_index", "col_list_index", "drop_stmt", "alter_stmt",
  "alter_behind", "col_list_alter", "open_db", "disconnect_db", "op", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,    59,    42,    44,    46,    39
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
        {
                0,    77,    78,    78,    78,    78,    78,    78,    79,    80,
                81,    82,    82,    83,    83,    83,    83,    84,    85,    86,
                87,    88,    89,    89,    89,    90,    91,    91,    91,    92,
                92,    93,    94,    94,    95,    96,    96,    96,    96,    97,
                98,    98,    99,    99,   100,   100,   100,   101,   101,   101,
                102,   102,   103,   104,   104,   105,   105,   106,   107,   107,
                108,   109,   109,   110,   110,   111,   111,   111,   111,   111,
                111,   111,   112,   113,   113,   114,   114,   115,   115,   116,
                116,   116,   116,   117,   117,   117,   117,   118,   119,   119,
                120,   120,   121,   121,   122,   123,   123,   123,   123,   123,
                123,   123,   124,   124,   125,   126,   127,   127,   127,   127,
                127,   127,   127
        };

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
        {
                0,     2,     1,     2,     2,     2,     2,     2,     1,     3,
                3,     1,     2,     1,     1,     1,     1,     2,     2,     1,
                4,     5,     2,     2,     2,     2,     1,     1,     2,     2,
                4,     2,     1,     3,     3,     1,     1,     3,     1,     3,
                1,     3,     1,     2,     1,     3,     4,     1,     4,     2,
                1,     3,     7,     1,     3,     1,     3,     3,     1,     1,
                3,     1,     1,     0,     2,     1,     1,     1,     1,     1,
                1,     1,     6,     1,     3,     3,     5,     1,     3,     0,
                3,     3,     2,     1,     1,     4,     1,     3,     5,     8,
                1,     3,     3,     3,     4,     3,     3,     3,     5,     4,
                7,     8,     1,     3,     3,     2,     1,     1,     1,     1,
                1,     1,     1
        };

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
        {
                63,     0,     0,     0,     0,     0,     0,     0,     0,     2,
                0,     0,     0,     8,     0,    13,    14,    15,    19,     0,
                16,     0,     0,     0,    50,    27,    25,    26,    44,    47,
                0,     0,     0,    17,     0,    11,    18,     1,     5,     6,
                3,     4,     0,     0,    23,    24,     0,    22,     0,     0,
                0,     0,     7,    64,    65,    66,    67,    68,    69,    70,
                71,    28,     0,     0,     0,    49,     0,     0,     0,     0,
                9,    10,    12,    31,    32,     0,     0,     0,    29,     0,
                0,     0,     0,     0,     0,     0,   105,     0,    51,     0,
                45,     0,     0,    55,    20,     0,     0,   106,   107,   108,
                109,   110,   111,   112,     0,    39,    40,    42,     0,     0,
                87,     0,    92,    93,     0,   104,    48,    46,     0,    21,
                0,     0,    33,     0,    61,    62,     0,    34,    35,    38,
                36,     0,    43,    30,     0,     0,     0,     0,     0,     0,
                94,    57,    58,    59,    56,     0,    53,     0,     0,    41,
                0,     0,     0,    73,    88,     0,     0,     0,     0,     0,
                0,    52,     0,    37,    60,    83,    84,     0,    86,    79,
                0,    72,     0,     0,    97,    95,     0,    96,     0,    79,
                54,     0,    75,     0,    74,    90,     0,     0,     0,     0,
                99,     0,     0,     0,    82,    77,     0,    89,     0,    98,
                0,     0,    85,    81,    80,    76,     0,    91,     0,   102,
                0,    78,     0,   100,     0,   101,   103
        };

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
        {
                -1,     8,     9,    10,    11,    34,    35,    13,    14,    15,
                16,    17,    18,    19,    26,    47,    44,    73,    74,   127,
                45,   105,   106,    27,    28,    29,    20,   145,    92,    93,
                146,   142,   143,    21,    53,    54,   152,   153,   196,   182,
                169,    55,    56,   186,    57,    58,   140,   210,    59,    60,
                104
        };

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -142
static const yytype_int16 yypact[] =
        {
                35,   -17,    -9,    15,    43,   -13,   103,    24,    63,  -142,
                25,    26,    27,  -142,    31,  -142,  -142,  -142,    11,   112,
                -142,    19,   -17,    66,    44,  -142,  -142,  -142,   -21,  -142,
                107,    84,    86,  -142,    -8,   103,  -142,  -142,  -142,  -142,
                -142,  -142,    13,    99,  -142,  -142,    10,  -142,     6,    48,
                78,   -29,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
                -142,  -142,    88,    89,    95,  -142,    13,    91,   122,   119,
                -142,  -142,  -142,  -142,   117,    65,    88,   127,  -142,    96,
                97,    98,   100,   101,   102,   104,  -142,   132,  -142,    13,
                -142,   121,   122,    68,  -142,   140,    13,  -142,  -142,  -142,
                -142,  -142,  -142,  -142,    -3,  -142,    70,   123,    83,   142,
                -142,    80,  -142,  -142,    36,  -142,  -142,  -142,   -16,  -142,
                91,   -16,  -142,   127,  -142,  -142,   109,  -142,   113,  -142,
                -142,    88,  -142,  -142,    56,   114,    47,    87,   -12,   115,
                -142,  -142,  -142,  -142,  -142,   149,    81,    85,    82,  -142,
                62,   105,    -2,  -142,   153,   120,   124,   125,    62,   126,
                62,  -142,   -16,  -142,  -142,  -142,  -142,   156,  -142,  -142,
                157,  -142,    56,   128,  -142,  -142,   106,  -142,   -19,  -142,
                -142,   129,   -18,   131,  -142,  -142,     0,    62,   130,   161,
                -18,   162,   133,   118,  -142,  -142,     1,  -142,   134,  -142,
                167,   136,  -142,  -142,  -142,  -142,   137,  -142,   136,  -142,
                2,  -142,     3,  -142,   138,  -142,  -142
        };

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
        {
                -142,  -142,  -142,  -142,  -142,   141,   177,  -142,  -142,  -142,
                -142,  -142,   -65,  -142,   158,  -142,   -54,    90,  -142,  -142,
                -142,    50,  -142,   -35,   -39,   -61,  -142,    16,    64,  -142,
                67,    79,    92,  -142,  -142,  -142,  -142,    17,  -142,     8,
                -141,  -142,  -142,  -142,  -142,  -142,  -142,   -20,  -142,  -142,
                -142
        };

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
        {
                123,    87,   171,    75,   197,   205,   213,   215,    22,    23,
                64,    78,   108,    77,    94,   107,    65,   177,    42,   179,
                24,    31,   124,    23,   125,   158,    70,    71,    30,   188,
                192,    90,   193,    43,    24,   124,    23,   125,   119,    23,
                1,    85,    86,     2,     3,     4,   199,    24,   189,   194,
                24,   159,    79,    66,   117,    32,    25,    75,   147,    33,
                126,    36,     5,    37,    80,   128,    48,    81,     6,    62,
                107,     7,   172,   126,   198,   206,   214,   214,    49,    50,
                97,    98,    99,   100,   101,   102,   103,   133,    51,   163,
                42,    52,    42,   150,    82,   136,   137,    38,    39,    40,
                138,   139,    65,    41,   151,    43,    83,    43,     1,   155,
                156,     2,     3,     4,   165,   166,   167,   168,    46,    63,
                67,    68,    76,    69,    84,    24,    88,    89,    91,    42,
                95,    96,     1,   109,   110,   111,   116,   112,   113,   114,
                118,   115,   120,   121,   131,   134,   148,   132,   135,   157,
                65,   154,   160,   161,   170,   162,   173,   174,   164,   181,
                183,   175,   176,   178,   201,   185,   202,   191,   195,   204,
                208,   207,   187,   209,   211,   216,    72,    12,   180,   200,
                61,   149,   203,   129,   144,   141,   122,   190,   212,   184,
                0,     0,     0,     0,     0,     0,   130
        };

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-142)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
        {
                3,    62,     4,    42,     4,     4,     4,     4,    25,    26,
                31,    46,    77,     3,    68,    76,    37,   158,     7,   160,
                37,     6,    38,    26,    40,    37,    34,    35,    37,    48,
                48,    66,    50,    22,    37,    38,    26,    40,    92,    26,
                5,    70,    71,     8,     9,    10,   187,    37,    67,    67,
                37,    63,    46,    74,    89,    12,    73,    96,   123,    72,
                76,    37,    27,     0,    58,   104,    47,    61,    33,     3,
                131,    36,    74,    76,    74,    74,    74,    74,    59,    60,
                15,    16,    17,    18,    19,    20,    21,     4,    69,     4,
                7,    72,     7,    37,    46,    59,    60,    72,    72,    72,
                64,    65,    37,    72,    48,    22,    58,    22,     5,    62,
                63,     8,     9,    10,    52,    53,    54,    55,     6,    75,
                13,    37,    23,    37,    46,    37,    37,    32,    37,     7,
                11,    14,     5,    37,    37,    37,     4,    37,    37,    37,
                19,    37,    74,     3,    74,     3,    37,    24,    68,    62,
                37,    37,    37,     4,    49,    74,     3,    37,    76,     3,
                3,    37,    37,    37,     3,    37,     4,    38,    37,    51,
                3,    37,    66,    37,    37,    37,    35,     0,   162,    49,
                22,   131,    49,   104,   120,   118,    96,   179,   208,   172,
                -1,    -1,    -1,    -1,    -1,    -1,   104
        };

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
        {
                0,     5,     8,     9,    10,    27,    33,    36,    78,    79,
                80,    81,    83,    84,    85,    86,    87,    88,    89,    90,
                103,   110,    25,    26,    37,    73,    91,   100,   101,   102,
                37,     6,    12,    72,    82,    83,    37,     0,    72,    72,
                72,    72,     7,    22,    93,    97,     6,    92,    47,    59,
                60,    69,    72,   111,   112,   118,   119,   121,   122,   125,
                126,    91,     3,    75,    31,    37,    74,    13,    37,    37,
                34,    35,    82,    94,    95,   101,    23,     3,   100,    46,
                58,    61,    46,    58,    46,    70,    71,   102,    37,    32,
                100,    37,   105,   106,    93,    11,    14,    15,    16,    17,
                18,    19,    20,    21,   127,    98,    99,   102,    89,    37,
                37,    37,    37,    37,    37,    37,     4,   100,    19,    93,
                74,     3,    94,     3,    38,    40,    76,    96,   101,   108,
                109,    74,    24,     4,     3,    68,    59,    60,    64,    65,
                123,   107,   108,   109,   105,   104,   107,    89,    37,    98,
                37,    48,   113,   114,    37,    62,    63,    62,    37,    63,
                37,     4,    74,     4,    76,    52,    53,    54,    55,   117,
                49,     4,    74,     3,    37,    37,    37,   117,    37,   117,
                104,     3,   116,     3,   114,    37,   120,    66,    48,    67,
                116,    38,    48,    50,    67,    37,   115,     4,    74,   117,
                49,     3,     4,    49,    51,     4,    74,    37,     3,    37,
                124,    37,   124,     4,    74,     4,    37
        };

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
/* This is here to suppress warnings from the GCC cpp's
   -Wunused-macros.  Normally we don't worry about that warning, but
   some users do, and we want to make it easy for users to remove
   YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
    YYUSE (yyvaluep);

    if (!yymsg)
        yymsg = "Deleting";
    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
    {

        default:
            break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
    yynewstate:
    /* In all cases, when you get here, the value and location stacks
       have just been pushed.  So pushing a state here evens the stacks.  */
    yyssp++;

    yysetstate:
    *yyssp = yystate;

    if (yyss + yystacksize - 1 <= yyssp)
    {
        /* Get the current used size of the three stacks, in elements.  */
        YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
        {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
        goto yyexhaustedlab;
# else
        /* Extend the stack our own way.  */
        if (YYMAXDEPTH <= yystacksize)
            goto yyexhaustedlab;
        yystacksize *= 2;
        if (YYMAXDEPTH < yystacksize)
            yystacksize = YYMAXDEPTH;

        {
            yytype_int16 *yyss1 = yyss;
            union yyalloc *yyptr =
                    (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
            if (! yyptr)
                goto yyexhaustedlab;
            YYSTACK_RELOCATE (yyss_alloc, yyss);
            YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
            if (yyss1 != yyssa)
                YYSTACK_FREE (yyss1);
        }
# endif
#endif /* no yyoverflow */

        yyssp = yyss + yysize - 1;
        yyvsp = yyvs + yysize - 1;

        YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                (unsigned long int) yystacksize));

        if (yyss + yystacksize - 1 <= yyssp)
            YYABORT;
    }

    YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
        yychar = YYLEX;
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

    /* Discard the shifted token.  */
    yychar = YYEMPTY;

    yystate = yyn;
    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    *++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
    yyreduce:
    /* yyn is the number of a rule to reduce with.  */
    yylen = yyr2[yyn];

    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  Assigning to YYVAL
       unconditionally makes the parser a bit smaller, and it avoids a
       GCC warning that YYVAL may be used uninitialized.  */
    yyval = yyvsp[1-yylen];


    YY_REDUCE_PRINT (yyn);
    switch (yyn)
    {
        case 3:
/* Line 1792 of yacc.c  */
#line 156 "DML_gram.y"
        {
            //此处调用执行函数即可,执行函数将返回错误状态码，需要获取并传入printError函数
            SqlGlobal::getInstance()->turnPnode2Exec((yyvsp[(1) - (2)].phyNode));
            YYACCEPT;
        }
            break;

        case 4:
/* Line 1792 of yacc.c  */
#line 162 "DML_gram.y"
        {
            YYACCEPT;
        }
            break;

        case 5:
/* Line 1792 of yacc.c  */
#line 166 "DML_gram.y"
        {
            YYACCEPT;
        }
            break;

        case 6:
/* Line 1792 of yacc.c  */
#line 170 "DML_gram.y"
        {
            YYACCEPT;
        }
            break;

        case 7:
/* Line 1792 of yacc.c  */
#line 174 "DML_gram.y"
        {
            YYACCEPT;
        }
            break;

        case 9:
/* Line 1792 of yacc.c  */
#line 185 "DML_gram.y"
        {
            //dmls内即为各物理计划树根节点
            if(PhysicalPlan::canFinish(*(yyvsp[(2) - (3)].phyNodes)))
            {
                //说明可以完成事务
                for (PhyPlanNode* root : *(yyvsp[(2) - (3)].phyNodes))
                {
                    //调用执行函数
                    SqlGlobal::getInstance()->turnPnode2Exec(root);
                }
            }
            else
            {
                cout<<"违反事务"<<endl;
            }
        }
            break;

        case 10:
/* Line 1792 of yacc.c  */
#line 205 "DML_gram.y"
        {
            cout<<"已取消事务"<<endl;
        }
            break;

        case 11:
/* Line 1792 of yacc.c  */
#line 212 "DML_gram.y"
        {
            (yyval.phyNodes) = new vector<PhyPlanNode*>;
            (yyval.phyNodes)->push_back((yyvsp[(1) - (1)].phyNode));
        }
            break;

        case 12:
/* Line 1792 of yacc.c  */
#line 217 "DML_gram.y"
        {
            (yyvsp[(2) - (2)].phyNodes)->push_back((yyvsp[(1) - (2)].phyNode));
            (yyval.phyNodes) = (yyvsp[(2) - (2)].phyNodes);
        }
            break;

        case 13:
/* Line 1792 of yacc.c  */
#line 225 "DML_gram.y"
        {
            //$$即为物理计划根节点
            (yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
        }
            break;

        case 14:
/* Line 1792 of yacc.c  */
#line 230 "DML_gram.y"
        {
            (yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
        }
            break;

        case 15:
/* Line 1792 of yacc.c  */
#line 234 "DML_gram.y"
        {
            (yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
        }
            break;

        case 16:
/* Line 1792 of yacc.c  */
#line 238 "DML_gram.y"
        {
            (yyval.phyNode) = (yyvsp[(1) - (1)].phyNode);
        }
            break;

        case 17:
/* Line 1792 of yacc.c  */
#line 245 "DML_gram.y"
        {
            YYACCEPT;
        }
            break;

        case 18:
/* Line 1792 of yacc.c  */
#line 252 "DML_gram.y"
        {
            string dbName = string((yyvsp[(2) - (2)].strval));//使用的数据库名
            SqlGlobal::getInstance()->useDB(dbName);
        }
            break;

        case 19:
/* Line 1792 of yacc.c  */
#line 260 "DML_gram.y"
        {
            if(!SqlGlobal::getInstance()->preCheck()){
                //未通过预判断
                YYACCEPT;
            }
            M_DML::Query* query = (yyvsp[(1) - (1)].query);
            //query->showInfo();


            SqlGrammer sqlgrammer;
            sqlgrammer.root = query->transform2Grammer();
            //cout << "-------------------------------"<<endl;
            //sqlgrammer.showInfo();
            sqlgrammer.optimiza();
            //cout << "-------------------------------"<<endl;


            PhysicalPlan physicalPlan;
            physicalPlan.root = sqlgrammer.transform2PhysicPlan();
            //physicalPlan.showPlan();

            (yyval.phyNode) = physicalPlan.root;


            //cout<<endl;
            //YYACCEPT;
        }
            break;

        case 20:
/* Line 1792 of yacc.c  */
#line 291 "DML_gram.y"
        {
            if(!SqlGlobal::getInstance()->preCheck()){
                //未通过预判断
                YYACCEPT;
            }

            M_DML::Delete * del = new M_DML::Delete();
            del->tableName = std::string((yyvsp[(3) - (4)].strval));
            del->condition = (yyvsp[(4) - (4)].condision);
            //del->showInfo();

            //$$ = new Delete();
            //$$->tableName = $3;
            //$$->condition = $4;
            //$$->showInfo();

            SqlGrammer sqlgrammer;
            //sqlgrammer.root = $$->transform2Grammer();
            sqlgrammer.root = del->transform2Grammer();
            //cout << "-------------------------------"<<endl;
            //sqlgrammer.showInfo();
            //cout << "-------------------------------"<<endl;

            PhysicalPlan physicalPlan;
            physicalPlan.root = sqlgrammer.transform2PhysicPlan();
            physicalPlan.showPlan();

            (yyval.phyNode) = physicalPlan.root;

            //cout<<endl;
            //YYACCEPT;
        }
            break;

        case 21:
/* Line 1792 of yacc.c  */
#line 327 "DML_gram.y"
        {
            if(!SqlGlobal::getInstance()->preCheck()){
                //未通过预判断
                YYACCEPT;
            }

            M_DML::Update* upt = new M_DML::Update();
            upt->tableName = std::string((yyvsp[(2) - (5)].strval));
            upt->attr_indexs = *(yyvsp[(4) - (5)].attr_indexs);
            upt->condition = (yyvsp[(5) - (5)].condision);
            upt->showInfo();

            //$$ = new Update();
            //$$->tableName = $2;
            //$$->attr_indexs = $4;
            //$$->condition = $5;
            //$$->showInfo();

            SqlGrammer sqlgrammer;
            //sqlgrammer.root = $$->transform2Grammer();
            sqlgrammer.root = upt->transform2Grammer();
            //cout << "-------------------------------"<<endl;
            //sqlgrammer.showInfo();
            //cout << "-------------------------------"<<endl;

            PhysicalPlan physicalPlan;
            physicalPlan.root = sqlgrammer.transform2PhysicPlan();
            //physicalPlan.showPlan();

            (yyval.phyNode) = physicalPlan.root;

            //cout<<endl;
            //YYACCEPT;
        }
            break;

        case 22:
/* Line 1792 of yacc.c  */
#line 365 "DML_gram.y"
        {
            (yyval.query) = new M_DML::Query();
            (yyval.query)->selList = (yyvsp[(1) - (2)].selList);
            (yyval.query)->fromList = (yyvsp[(2) - (2)].fromList);
        }
            break;

        case 23:
/* Line 1792 of yacc.c  */
#line 371 "DML_gram.y"
        {
            (yyvsp[(1) - (2)].query)->condition = (yyvsp[(2) - (2)].condision);
            (yyval.query) = (yyvsp[(1) - (2)].query);
        }
            break;

        case 24:
/* Line 1792 of yacc.c  */
#line 376 "DML_gram.y"
        {
            (yyvsp[(1) - (2)].query)->orderList = (yyvsp[(2) - (2)].orderList);
            (yyval.query) = (yyvsp[(1) - (2)].query);
        }
            break;

        case 25:
/* Line 1792 of yacc.c  */
#line 385 "DML_gram.y"
        {
            (yyval.selList) = (yyvsp[(2) - (2)].selList);
        }
            break;

        case 26:
/* Line 1792 of yacc.c  */
#line 392 "DML_gram.y"
        {
            (yyval.selList) = new M_DML::SelList();
            for(int m=0;m<(yyvsp[(1) - (1)].nameList)->size();m++){
                M_DML::Attribute* attr = new M_DML::Attribute();
                M_DML::Name* name = (yyvsp[(1) - (1)].nameList)->at(m);
                attr->setName(name);
                (yyval.selList)->addAttribute(attr);
            }
        }
            break;

        case 27:
/* Line 1792 of yacc.c  */
#line 402 "DML_gram.y"
        {
            (yyval.selList) = new M_DML::SelList();
            M_DML::Attribute* attr = new M_DML::Attribute();
            attr->attrName = "*";
            (yyval.selList)->addAttribute(attr);
        }
            break;

        case 28:
/* Line 1792 of yacc.c  */
#line 409 "DML_gram.y"
        {
            cout<<"distinct，暂不进行处理"<<endl;
        }
            break;

        case 29:
/* Line 1792 of yacc.c  */
#line 417 "DML_gram.y"
        {
            (yyval.fromList) = new M_DML::FromList();
            for(int m=0;m<(yyvsp[(2) - (2)].nameList)->size();m++){
                M_DML::Relation* rl = new M_DML::Relation();
                rl->relationName = (yyvsp[(2) - (2)].nameList)->at(m)->attrName;
                rl->alias = (yyvsp[(2) - (2)].nameList)->at(m)->alias;
                (yyval.fromList)->addNode(rl);
            }
        }
            break;

        case 30:
/* Line 1792 of yacc.c  */
#line 427 "DML_gram.y"
        {
            cout<<"子查询，暂不进行处理"<<endl;
        }
            break;

        case 31:
/* Line 1792 of yacc.c  */
#line 435 "DML_gram.y"
        {
            (yyval.condision) = (yyvsp[(2) - (2)].condision);
        }
            break;

        case 32:
/* Line 1792 of yacc.c  */
#line 443 "DML_gram.y"
        {
            //可能有多个condition
            (yyval.condision) = (yyvsp[(1) - (1)].condision);
        }
            break;

        case 33:
/* Line 1792 of yacc.c  */
#line 448 "DML_gram.y"
        {
            M_DML::Condition* condition = new M_DML::Condition();
            condition->lCnode = (yyvsp[(3) - (3)].condision);

            condition->soperator = (yyvsp[(2) - (3)].soperator);
            condition->rCnode = (yyvsp[(1) - (3)].condision);
            (yyval.condision) = condition;
        }
            break;

        case 34:
/* Line 1792 of yacc.c  */
#line 460 "DML_gram.y"
        {
            //【】op【】:a=b
            M_DML::Condition* condition = new M_DML::Condition();
            (yyval.condision) = condition;
            M_DML::Attribute* lattr = new M_DML::Attribute();
            lattr->setName((yyvsp[(1) - (3)].name));
            condition->Lattr = lattr;

            int ttype = (yyvsp[(3) - (3)].nodestorage)->type;
            if(ttype == NUMBER){

                condition->rNumber = (yyvsp[(3) - (3)].nodestorage)->rNumber;

            }else if(ttype == PARA_STRING){

                condition->pString = (yyvsp[(3) - (3)].nodestorage)->pString;

            }else if(ttype == NAME){

                M_DML::Attribute* rattr = new M_DML::Attribute();
                rattr->setName((yyvsp[(3) - (3)].nodestorage)->name);
                condition->Rattr = rattr;

            }else if(ttype == SUBQUERY){
                //子查询
                condition->query = (yyvsp[(3) - (3)].nodestorage)->query;
            }
            condition->soperator = (yyvsp[(2) - (3)].soperator);
        }
            break;

        case 35:
/* Line 1792 of yacc.c  */
#line 494 "DML_gram.y"
        {
            //where a=【】,可为表名,数字，子查询
            (yyval.nodestorage) = new NodeStorage();
            (yyval.nodestorage)->name = (yyvsp[(1) - (1)].name);
            (yyval.nodestorage)->type = NAME;
        }
            break;

        case 36:
/* Line 1792 of yacc.c  */
#line 501 "DML_gram.y"
        {
            (yyval.nodestorage) = new NodeStorage();
            (yyval.nodestorage)->rNumber = (yyvsp[(1) - (1)].rNumber);
            (yyval.nodestorage)->type = NUMBER;
        }
            break;

        case 37:
/* Line 1792 of yacc.c  */
#line 507 "DML_gram.y"
        {
            (yyval.nodestorage) = new NodeStorage();
            (yyval.nodestorage)->query = (yyvsp[(2) - (3)].query);
            (yyval.nodestorage)->type = SUBQUERY;

        }
            break;

        case 38:
/* Line 1792 of yacc.c  */
#line 514 "DML_gram.y"
        {
            (yyval.nodestorage) = new NodeStorage();
            (yyval.nodestorage)->pString = (yyvsp[(1) - (1)].pString);
            (yyval.nodestorage)->type = PARA_STRING;
        }
            break;

        case 39:
/* Line 1792 of yacc.c  */
#line 523 "DML_gram.y"
        {
            (yyval.orderList) = (yyvsp[(3) - (3)].orderList);
        }
            break;

        case 40:
/* Line 1792 of yacc.c  */
#line 530 "DML_gram.y"
        {
            //可能有多个排序节点
            (yyval.orderList) = new M_DML::OrderList();
            (yyval.orderList)->addOrderNode((yyvsp[(1) - (1)].orderNode));
        }
            break;

        case 41:
/* Line 1792 of yacc.c  */
#line 536 "DML_gram.y"
        {
            (yyvsp[(3) - (3)].orderList)->addOrderNode((yyvsp[(1) - (3)].orderNode));
            (yyval.orderList) = (yyvsp[(3) - (3)].orderList);
        }
            break;

        case 42:
/* Line 1792 of yacc.c  */
#line 544 "DML_gram.y"
        {
            //排序节点,可带rule也可不带
            (yyval.orderNode) = new M_DML::OrderNode();
            (yyval.orderNode)->attr.setName((yyvsp[(1) - (1)].name)->attrName,(yyvsp[(1) - (1)].name)->tableName);
        }
            break;

        case 43:
/* Line 1792 of yacc.c  */
#line 550 "DML_gram.y"
        {
            (yyval.orderNode) = new M_DML::OrderNode();
            (yyval.orderNode)->attr.setName((yyvsp[(1) - (2)].name)->attrName,(yyvsp[(1) - (2)].name)->tableName);
            (yyval.orderNode)->rule = *(yyvsp[(2) - (2)].text);
        }
            break;

        case 44:
/* Line 1792 of yacc.c  */
#line 559 "DML_gram.y"
        {
            //名字列表
            (yyval.nameList) = new vector<M_DML::Name*>;
            (yyval.nameList)->push_back((yyvsp[(1) - (1)].name));
        }
            break;

        case 45:
/* Line 1792 of yacc.c  */
#line 565 "DML_gram.y"
        {
            (yyvsp[(3) - (3)].nameList)->push_back((yyvsp[(1) - (3)].name));
            (yyval.nameList) = (yyvsp[(3) - (3)].nameList);
        }
            break;

        case 46:
/* Line 1792 of yacc.c  */
#line 570 "DML_gram.y"
        {
            M_DML::Name *name = new M_DML::Name();
            name->attrName = "@natural@";//@natural@作为指示符
            (yyvsp[(4) - (4)].nameList)->push_back(name);
            (yyvsp[(4) - (4)].nameList)->push_back((yyvsp[(1) - (4)].name));
            (yyval.nameList) = (yyvsp[(4) - (4)].nameList);
        }
            break;

        case 47:
/* Line 1792 of yacc.c  */
#line 581 "DML_gram.y"
        {
            (yyval.name) = (yyvsp[(1) - (1)].name);
        }
            break;

        case 48:
/* Line 1792 of yacc.c  */
#line 585 "DML_gram.y"
        {
            M_DML::Name* name = (yyvsp[(3) - (4)].name);
            name->aggFunc = *(yyvsp[(1) - (4)].text);
            (yyval.name) = name;
        }
            break;

        case 49:
/* Line 1792 of yacc.c  */
#line 591 "DML_gram.y"
        {
            M_DML::Name* name = (yyvsp[(1) - (2)].name);
            name->alias = std::string((yyvsp[(2) - (2)].strval));
            (yyval.name) = name;
        }
            break;

        case 50:
/* Line 1792 of yacc.c  */
#line 600 "DML_gram.y"
        {
            M_DML::Name* name = new M_DML::Name();
            name->attrName = std::string((yyvsp[(1) - (1)].strval));
            (yyval.name) = name;
        }
            break;

        case 51:
/* Line 1792 of yacc.c  */
#line 606 "DML_gram.y"
        {
            M_DML::Name* name = new M_DML::Name();
            name->tableName = std::string((yyvsp[(1) - (3)].strval));
            name->attrName = std::string((yyvsp[(3) - (3)].strval));

            (yyval.name) = name;
        }
            break;

        case 52:
/* Line 1792 of yacc.c  */
#line 617 "DML_gram.y"
        {
            if(!SqlGlobal::getInstance()->preCheck()){
                //未通过预判断
                YYACCEPT;
            }

            M_DML::Insert * insert = new M_DML::Insert();
            insert->attributes = *(yyvsp[(6) - (7)].values);
            insert->tableName = std::string((yyvsp[(3) - (7)].strval));
            insert->showInfo();

            SqlGrammer sqlgrammer;
            sqlgrammer.root = insert->transform2Grammer();
            //cout << "-------------------------------"<<endl;
            //sqlgrammer.showInfo();
            //cout << "-------------------------------"<<endl;

            PhysicalPlan physicalPlan;
            physicalPlan.root = sqlgrammer.transform2PhysicPlan();
            physicalPlan.showPlan();

            (yyval.phyNode) = physicalPlan.root;

            cout<<endl;
        }
            break;

        case 53:
/* Line 1792 of yacc.c  */
#line 646 "DML_gram.y"
        {
            (yyval.values) = new vector<string>;
            (yyval.values)->push_back(*(yyvsp[(1) - (1)].text));
        }
            break;

        case 54:
/* Line 1792 of yacc.c  */
#line 651 "DML_gram.y"
        {
            (yyvsp[(3) - (3)].values)->push_back(*(yyvsp[(1) - (3)].text));
            (yyval.values) = (yyvsp[(3) - (3)].values);
        }
            break;

        case 55:
/* Line 1792 of yacc.c  */
#line 659 "DML_gram.y"
        {
            (yyval.attr_indexs) = new map<string,string>;
            string **tmp = (yyvsp[(1) - (1)].attr_index);
            (yyval.attr_indexs)->insert(pair<string, string>(*tmp[0], *tmp[1]));
        }
            break;

        case 56:
/* Line 1792 of yacc.c  */
#line 665 "DML_gram.y"
        {
            string **tmp = (yyvsp[(1) - (3)].attr_index);
            (yyvsp[(3) - (3)].attr_indexs)->insert(pair<string,string>(*tmp[0],*tmp[1]));
            (yyval.attr_indexs) = (yyvsp[(3) - (3)].attr_indexs);
        }
            break;

        case 57:
/* Line 1792 of yacc.c  */
#line 674 "DML_gram.y"
        {
            string** tmp = (yyval.attr_index);
            string* pre = new string((yyvsp[(1) - (3)].strval));
            tmp[0] = pre;
            tmp[1] = (yyvsp[(3) - (3)].text);
        }
            break;

        case 58:
/* Line 1792 of yacc.c  */
#line 684 "DML_gram.y"
        {
            (yyval.text) = &(yyvsp[(1) - (1)].pString)->parameter;
        }
            break;

        case 59:
/* Line 1792 of yacc.c  */
#line 688 "DML_gram.y"
        {
            (yyval.text) = &(yyvsp[(1) - (1)].rNumber)->number;
        }
            break;

        case 60:
/* Line 1792 of yacc.c  */
#line 695 "DML_gram.y"
        {
            M_DML::ParaString* pstring = new M_DML::ParaString();
            pstring->parameter = "\'" + std::string((yyvsp[(2) - (3)].strval)) +"\'";
            (yyval.pString) = pstring;
        }
            break;

        case 61:
/* Line 1792 of yacc.c  */
#line 704 "DML_gram.y"
        {
            (yyval.rNumber) = new M_DML::Number();
            (yyval.rNumber)->number = to_string((yyvsp[(1) - (1)].intval));
        }
            break;

        case 62:
/* Line 1792 of yacc.c  */
#line 709 "DML_gram.y"
        {
            (yyval.rNumber) = new M_DML::Number();
            (yyval.rNumber)->number = to_string((yyvsp[(1) - (1)].floatval));
        }
            break;

        case 72:
/* Line 1792 of yacc.c  */
#line 735 "DML_gram.y"
        {
            //if(g_DD:Stmt.createtable->tablename == nullptr)
            set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_TABLE);
            g_DDLStmt.createtable->tablename = (yyvsp[(3) - (6)].strval);
        }
            break;

        case 73:
/* Line 1792 of yacc.c  */
#line 744 "DML_gram.y"
        {
            (yyval.intval) = 1;
        }
            break;

        case 74:
/* Line 1792 of yacc.c  */
#line 748 "DML_gram.y"
        {
            (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1;
        }
            break;

        case 75:
/* Line 1792 of yacc.c  */
#line 755 "DML_gram.y"
        {
            ColDef newCol;
            strcopy((yyvsp[(1) - (3)].strval),newCol.name);
            newCol.datatype = (yyvsp[(2) - (3)].intval);
            dividetypes(newCol.constypes,(yyvsp[(3) - (3)].intval));
            g_DDLStmt.createtable->cols.push_back(newCol);
        }
            break;

        case 76:
/* Line 1792 of yacc.c  */
#line 763 "DML_gram.y"
        {
            vector<int> temp;
            divideToNum(temp,(yyvsp[(4) - (5)].intval));
            for(int i = 0;i < temp.size();i++)
            {
                //g_DDLStmt.createtable->cols[temp[i]].constypes.push_back(DDL_CONS_TYPE::DDL_CONS_PRIKEY);
                int flag = DDL_CONS_TYPE::DDL_CONS_PRIKEY;
                g_DDLStmt.createtable->cols[temp[i]].constypes.push_back(flag);
            }
        }
            break;

        case 77:
/* Line 1792 of yacc.c  */
#line 777 "DML_gram.y"
        {
            for(int i = 0;i < g_DDLStmt.createtable->cols.size();i++)
            {
                if(strcmp(g_DDLStmt.createtable->cols[i].name,(yyvsp[(1) - (1)].strval)) == 0)
                {
                    (yyval.intval) = pow(2,i);break;
                }
            }
        }
            break;

        case 78:
/* Line 1792 of yacc.c  */
#line 787 "DML_gram.y"
        {
            for(int i = 0;i < g_DDLStmt.createtable->cols.size();i++)
            {
                if(strcmp(g_DDLStmt.createtable->cols[i].name,(yyvsp[(3) - (3)].strval)) == 0)
                {
                    int temp = pow(2,i);
                    (yyval.intval) = (yyvsp[(1) - (3)].intval) + temp;break;
                }
            }
        }
            break;

        case 79:
/* Line 1792 of yacc.c  */
#line 800 "DML_gram.y"
        { (yyval.intval) = 0; }
            break;

        case 80:
/* Line 1792 of yacc.c  */
#line 801 "DML_gram.y"
        { (yyval.intval) = (yyvsp[(1) - (3)].intval) + DDL_CONS_TYPE::DDL_CONS_NOTNULL; }
            break;

        case 81:
/* Line 1792 of yacc.c  */
#line 802 "DML_gram.y"
        { (yyval.intval) = (yyvsp[(1) - (3)].intval) + DDL_CONS_TYPE::DDL_CONS_PRIKEY;}
            break;

        case 82:
/* Line 1792 of yacc.c  */
#line 803 "DML_gram.y"
        { (yyval.intval) = (yyvsp[(1) - (2)].intval) + DDL_CONS_TYPE::DDL_CONS_UNIQUE;}
            break;

        case 83:
/* Line 1792 of yacc.c  */
#line 807 "DML_gram.y"
        { (yyval.intval) = DDL_DATA_TYPE::DDL_INT; }
            break;

        case 84:
/* Line 1792 of yacc.c  */
#line 808 "DML_gram.y"
        { (yyval.intval) = DDL_DATA_TYPE::DDL_FLOAT; }
            break;

        case 85:
/* Line 1792 of yacc.c  */
#line 809 "DML_gram.y"
        { (yyval.intval) = -(yyvsp[(3) - (4)].intval); }
            break;

        case 86:
/* Line 1792 of yacc.c  */
#line 810 "DML_gram.y"
        { (yyval.intval) = DDL_DATA_TYPE::DDL_VARCHAR; }
            break;

        case 87:
/* Line 1792 of yacc.c  */
#line 816 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_DATABASE);
            strcopy((yyvsp[(3) - (3)].strval),g_DDLStmt.createdatabase->databasename);
        }
            break;

        case 88:
/* Line 1792 of yacc.c  */
#line 825 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_INDEX);
            strcopy((yyvsp[(3) - (5)].strval),g_DDLStmt.createindex->indexname);
            strcopy((yyvsp[(5) - (5)].strval),g_DDLStmt.createindex->tablename);
        }
            break;

        case 89:
/* Line 1792 of yacc.c  */
#line 831 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_CREATE_INDEX);
            strcopy((yyvsp[(3) - (8)].strval),g_DDLStmt.createindex->indexname);
            strcopy((yyvsp[(5) - (8)].strval),g_DDLStmt.createindex->tablename);
        }
            break;

        case 90:
/* Line 1792 of yacc.c  */
#line 840 "DML_gram.y"
        {
            g_DDLStmt.createindex->colnames.push_back((yyvsp[(1) - (1)].strval));
        }
            break;

        case 91:
/* Line 1792 of yacc.c  */
#line 844 "DML_gram.y"
        {
            g_DDLStmt.createindex->colnames.push_back((yyvsp[(3) - (3)].strval));
        }
            break;

        case 92:
/* Line 1792 of yacc.c  */
#line 852 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_DROP);
            g_DDLStmt.dropstmt->dropType = DROPTYPE::TABLE;
            strcopy((yyvsp[(3) - (3)].strval),g_DDLStmt.dropstmt->dropname);
        }
            break;

        case 93:
/* Line 1792 of yacc.c  */
#line 858 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_DROP);
            g_DDLStmt.dropstmt->dropType = DROPTYPE::DATABASE;
            strcopy((yyvsp[(3) - (3)].strval),g_DDLStmt.dropstmt->dropname);
        }
            break;

        case 94:
/* Line 1792 of yacc.c  */
#line 868 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_ALTER);
            strcopy((yyvsp[(3) - (4)].strval),g_DDLStmt.alterstmt->tablename);
        }
            break;

        case 95:
/* Line 1792 of yacc.c  */
#line 875 "DML_gram.y"
        {
            g_DDLStmt.alterstmt->altertype = ALTERTYPE::DROP_CONSTRAINT;
            strcopy((yyvsp[(3) - (3)].strval),g_DDLStmt.alterstmt->constraintname);
        }
            break;

        case 96:
/* Line 1792 of yacc.c  */
#line 880 "DML_gram.y"
        {
            g_DDLStmt.alterstmt->altertype = ALTERTYPE::ADD_COL;
            ColDef newCol;
            strcopy((yyvsp[(2) - (3)].strval),newCol.name);
            newCol.datatype = (yyvsp[(3) - (3)].intval);
            g_DDLStmt.alterstmt->cols.push_back(newCol);
        }
            break;

        case 97:
/* Line 1792 of yacc.c  */
#line 888 "DML_gram.y"
        {
            g_DDLStmt.alterstmt->altertype = ALTERTYPE::DROP_COL;
            ColDef newCol;
            strcopy((yyvsp[(3) - (3)].strval),newCol.name);
            g_DDLStmt.alterstmt->cols.push_back(newCol);
        }
            break;

        case 98:
/* Line 1792 of yacc.c  */
#line 895 "DML_gram.y"
        {
            g_DDLStmt.alterstmt->altertype = ALTERTYPE::ALTER_COL;
            ColDef newCol;
            strcopy((yyvsp[(3) - (5)].strval),newCol.name);
            newCol.datatype = (yyvsp[(5) - (5)].intval);
            g_DDLStmt.alterstmt->cols.push_back(newCol);
        }
            break;

        case 99:
/* Line 1792 of yacc.c  */
#line 903 "DML_gram.y"
        {
            g_DDLStmt.alterstmt->altertype = ALTERTYPE::MODIFY_COL;
            g_DDLStmt.alterstmt->modifytype = (yyvsp[(4) - (4)].intval);
            ColDef newCol;
            strcopy((yyvsp[(2) - (4)].strval),newCol.name);
            newCol.datatype = (yyvsp[(3) - (4)].intval);
            g_DDLStmt.alterstmt->cols.push_back(newCol);
        }
            break;

        case 100:
/* Line 1792 of yacc.c  */
#line 912 "DML_gram.y"
        {
            g_DDLStmt.alterstmt->altertype = ALTERTYPE::ADD_CONSTRAINT;
            strcopy((yyvsp[(3) - (7)].strval),g_DDLStmt.alterstmt->constraintname);
            g_DDLStmt.alterstmt->constrainttype = DDL_CONS_TYPE::DDL_CONS_UNIQUE;
        }
            break;

        case 101:
/* Line 1792 of yacc.c  */
#line 918 "DML_gram.y"
        {
            g_DDLStmt.alterstmt->altertype = ALTERTYPE::ADD_CONSTRAINT;
            strcopy((yyvsp[(3) - (8)].strval),g_DDLStmt.alterstmt->constraintname);
            g_DDLStmt.alterstmt->constrainttype = DDL_CONS_TYPE::DDL_CONS_PRIKEY;
        }
            break;

        case 102:
/* Line 1792 of yacc.c  */
#line 927 "DML_gram.y"
        {
            ColDef newCol;
            strcopy((yyvsp[(1) - (1)].strval),newCol.name);
            g_DDLStmt.alterstmt->cols.push_back(newCol);
        }
            break;

        case 103:
/* Line 1792 of yacc.c  */
#line 933 "DML_gram.y"
        {
            ColDef newCol;
            strcopy((yyvsp[(3) - (3)].strval),newCol.name);
            g_DDLStmt.alterstmt->cols.push_back(newCol);
        }
            break;

        case 104:
/* Line 1792 of yacc.c  */
#line 942 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_OPEN_DB);
            strcopy((yyvsp[(3) - (3)].strval),g_DDLStmt.opendbstmt->dbName);
        }
            break;

        case 105:
/* Line 1792 of yacc.c  */
#line 950 "DML_gram.y"
        {
            set_node(DDL_SQL_TYPE::DDL_TYPE_CONNECT_RESET);
        }
            break;

        case 106:
/* Line 1792 of yacc.c  */
#line 957 "DML_gram.y"
        {
            (yyval.soperator) = (yyvsp[(1) - (1)].soperator);
        }
            break;

        case 107:
/* Line 1792 of yacc.c  */
#line 961 "DML_gram.y"
        {
            (yyval.soperator) = (yyvsp[(1) - (1)].soperator);
        }
            break;

        case 108:
/* Line 1792 of yacc.c  */
#line 965 "DML_gram.y"
        {
            (yyval.soperator) = (yyvsp[(1) - (1)].soperator);
        }
            break;

        case 109:
/* Line 1792 of yacc.c  */
#line 969 "DML_gram.y"
        {
            (yyval.soperator) = (yyvsp[(1) - (1)].soperator);
        }
            break;

        case 110:
/* Line 1792 of yacc.c  */
#line 973 "DML_gram.y"
        {
            (yyval.soperator) = (yyvsp[(1) - (1)].soperator);
        }
            break;

        case 111:
/* Line 1792 of yacc.c  */
#line 977 "DML_gram.y"
        {
            (yyval.soperator) = (yyvsp[(1) - (1)].soperator);
        }
            break;

        case 112:
/* Line 1792 of yacc.c  */
#line 981 "DML_gram.y"
        {
            (yyval.soperator) = (yyvsp[(1) - (1)].soperator);
        }
            break;


/* Line 1792 of yacc.c  */
#line 2745 "DML_gram.tab.cpp"
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

    /* Now `shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
    if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTOKENS];

    goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
    yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus)
    {
        ++yynerrs;
#if ! YYERROR_VERBOSE
        yyerror (YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (yymsgp);
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
                        yytoken, &yylval);
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (/*CONSTCOND*/ 0)
        goto yyerrorlab;

    /* Do not reclaim the symbols of the rule which action triggered
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
    yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
                    yystos[yystate], yyvsp);
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
    yyerror (YY_("memory exhausted"));
    yyresult = 2;
    /* Fall through.  */
#endif

    yyreturn:
    if (yychar != YYEMPTY)
    {
        /* Make sure we have latest lookahead translation.  See comments at
           user semantic actions for why this is necessary.  */
        yytoken = YYTRANSLATE (yychar);
        yydestruct ("Cleanup: discarding lookahead",
                    yytoken, &yylval);
    }
    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    YYPOPSTACK (yylen);
    YY_STACK_PRINT (yyss, yyssp);
    while (yyssp != yyss)
    {
        yydestruct ("Cleanup: popping",
                    yystos[*yyssp], yyvsp);
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
    /* Make sure YYID is used.  */
    return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 986 "DML_gram.y"


/*DML*/

int parser_dml_sql(string sql){

    yy_switch_to_buffer(yy_scan_string(sql.c_str()));
    if(yyparse())
        return -1;
    else{
        return 1;
    }
}

string getInputSql(){
    //获取输入的sql语句
    string sql;
    getline(cin, sql);
    while (sql.empty()) {
        getline(cin, sql);
    }
    while (sql.back() != ';') {
        string tmp;
        getline(cin, tmp);
        sql += " " + tmp;
    }
    return sql;
}

/* DDL */
//解析成功返回1，解析不成功返回-1
int parser_ddl_sql(string sql){

    //由于会重复调用此函数，因此先释放已申请的空间
    delete g_DDLStmt.createdatabase;
    delete g_DDLStmt.createindex;
    delete g_DDLStmt.createtable;
    delete g_DDLStmt.dropstmt;
    delete g_DDLStmt.alterstmt;
    delete g_DDLStmt.opendbstmt;
    g_DDLStmt.stmttype = 0;

    //在解析之前，先申请空间
    g_DDLStmt.createtable = new CreateTableStmt;
    g_DDLStmt.createdatabase = new CreateDatabaseStmt;
    g_DDLStmt.createindex = new CreateIndex;
    g_DDLStmt.dropstmt = new DropStmt;
    g_DDLStmt.alterstmt = new AlterStmt;
    g_DDLStmt.opendbstmt = new OpenDBStmt;

    yy_switch_to_buffer(yy_scan_string(sql.c_str()));
    if(yyparse())
        return -1;
    else{
        return 1;
    }
}

//为g_DDLStmt申请结点空间,好像我已经把申请空间放外边了，直接全申请了，这个已经鸡肋了
void set_node(int type){
    g_DDLStmt.stmttype = type;
    //switch(type){
    //	case DDL_TYPE_CREATE_TABLE:
    //		//g_DDLStmt.createtable = new CreateTableStmt;  直接在外面申请所有的空间
    //		break;
    //	case DDL_TYPE_CREATE_DATABASE:
    //		break；
    //	default:
    //		cout<<"申请结点空间时出错"<<endl;break;
    //}
}

//将一个数据类型和拆分成一个个类型
void dividetypes(vector<int>& v,int sum){
    //首先将num转换成二进制
    vector<int> binaryint;
    while(1){
        binaryint.push_back((sum%2));
        if(sum/2 == 0) break;
        else sum = sum/2;
    }
    //得到了二进制的倒序
    for(int i = 0;i < binaryint.size();i++){
        if(binaryint[i] == 0) continue;
        v.push_back(pow(2,i));
    }
}

void divideToNum(vector<int>& v,int sum){
    //首先将num转换成二进制
    vector<int> binaryint;
    while(1){
        binaryint.push_back((sum%2));
        if(sum/2 == 0) break;
        else sum = sum/2;
    }
    //得到了二进制的倒序
    for(int i = 0;i < binaryint.size();i++){
        if(binaryint[i] == 0) continue;
        v.push_back(i);
    }
}