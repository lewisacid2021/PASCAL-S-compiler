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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"

#include "parser.h"
using namespace ast;
using std::string;
extern "C"			
{					
    void yyerror(const char *s);
    extern int yylex(void);
    extern int line_count;
    extern bool new_line_flag;
    extern int yyleng;
    extern int last_line_count;
}
extern std::string cur_line_info;
extern std::string last_line_info;
extern int lex_error_flag;
int semantic_error_flag = 0;

int error_flag=0;

void yyerror(AST* Ast,const char *msg);


#line 95 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_FUNCTION = 4,                   /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 5,                  /* PROCEDURE  */
  YYSYMBOL_TO = 6,                         /* TO  */
  YYSYMBOL_DOWNTO = 7,                     /* DOWNTO  */
  YYSYMBOL_ARRAY = 8,                      /* ARRAY  */
  YYSYMBOL_TYPE = 9,                       /* TYPE  */
  YYSYMBOL_CONST = 10,                     /* CONST  */
  YYSYMBOL_RECORD = 11,                    /* RECORD  */
  YYSYMBOL_STRING = 12,                    /* STRING  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_THEN = 14,                      /* THEN  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_OF = 16,                        /* OF  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_DO = 18,                        /* DO  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_REPEAT = 20,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 21,                     /* UNTIL  */
  YYSYMBOL_BEGIN_ = 22,                    /* BEGIN_  */
  YYSYMBOL_END = 23,                       /* END  */
  YYSYMBOL_ADDOP = 24,                     /* ADDOP  */
  YYSYMBOL_NOT = 25,                       /* NOT  */
  YYSYMBOL_PLUS = 26,                      /* PLUS  */
  YYSYMBOL_CASE = 27,                      /* CASE  */
  YYSYMBOL_UMINUS = 28,                    /* UMINUS  */
  YYSYMBOL_CONSTASSIGNOP = 29,             /* CONSTASSIGNOP  */
  YYSYMBOL_ID = 30,                        /* ID  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_INT_NUM = 32,                   /* INT_NUM  */
  YYSYMBOL_REAL_NUM = 33,                  /* REAL_NUM  */
  YYSYMBOL_RELOP = 34,                     /* RELOP  */
  YYSYMBOL_MULOP = 35,                     /* MULOP  */
  YYSYMBOL_STRING_ = 36,                   /* STRING_  */
  YYSYMBOL_VAR = 37,                       /* VAR  */
  YYSYMBOL_SUBCATALOG = 38,                /* SUBCATALOG  */
  YYSYMBOL_ASSIGNOP = 39,                  /* ASSIGNOP  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '.'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_45_ = 45,                       /* '='  */
  YYSYMBOL_46_ = 46,                       /* ':'  */
  YYSYMBOL_47_ = 47,                       /* '['  */
  YYSYMBOL_48_ = 48,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_program_head = 51,              /* program_head  */
  YYSYMBOL_program_body = 52,              /* program_body  */
  YYSYMBOL_id_list = 53,                   /* id_list  */
  YYSYMBOL_const_declarations = 54,        /* const_declarations  */
  YYSYMBOL_const_declaration = 55,         /* const_declaration  */
  YYSYMBOL_const_value = 56,               /* const_value  */
  YYSYMBOL_record_declarations = 57,       /* record_declarations  */
  YYSYMBOL_record_declaration = 58,        /* record_declaration  */
  YYSYMBOL_var_declarations = 59,          /* var_declarations  */
  YYSYMBOL_var_declaration = 60,           /* var_declaration  */
  YYSYMBOL_type = 61,                      /* type  */
  YYSYMBOL_array_type = 62,                /* array_type  */
  YYSYMBOL_periods = 63,                   /* periods  */
  YYSYMBOL_period = 64,                    /* period  */
  YYSYMBOL_string_type = 65,               /* string_type  */
  YYSYMBOL_subprogram_declarations = 66,   /* subprogram_declarations  */
  YYSYMBOL_subprogram_declaration = 67,    /* subprogram_declaration  */
  YYSYMBOL_subprogram_body = 68,           /* subprogram_body  */
  YYSYMBOL_subprogram_head = 69,           /* subprogram_head  */
  YYSYMBOL_formal_parameter = 70,          /* formal_parameter  */
  YYSYMBOL_parameter_lists = 71,           /* parameter_lists  */
  YYSYMBOL_parameter_list = 72,            /* parameter_list  */
  YYSYMBOL_var_parameter = 73,             /* var_parameter  */
  YYSYMBOL_value_parameter = 74,           /* value_parameter  */
  YYSYMBOL_compound_statement = 75,        /* compound_statement  */
  YYSYMBOL_statement_list = 76,            /* statement_list  */
  YYSYMBOL_statement = 77,                 /* statement  */
  YYSYMBOL_assignop_statement = 78,        /* assignop_statement  */
  YYSYMBOL_procedure_call = 79,            /* procedure_call  */
  YYSYMBOL_ifstatement = 80,               /* ifstatement  */
  YYSYMBOL_else_part = 81,                 /* else_part  */
  YYSYMBOL_loopstatement = 82,             /* loopstatement  */
  YYSYMBOL_variable_list = 83,             /* variable_list  */
  YYSYMBOL_variable = 84,                  /* variable  */
  YYSYMBOL_id_varparts = 85,               /* id_varparts  */
  YYSYMBOL_id_varpart = 86,                /* id_varpart  */
  YYSYMBOL_expression_list = 87,           /* expression_list  */
  YYSYMBOL_expression = 88,                /* expression  */
  YYSYMBOL_simple_expression = 89,         /* simple_expression  */
  YYSYMBOL_term = 90,                      /* term  */
  YYSYMBOL_factor = 91                     /* factor  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  218

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      42,    43,     2,     2,    44,     2,    41,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    40,
       2,    45,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   139,   139,   149,   155,   158,   163,   173,   180,   187,
     191,   198,   211,   223,   229,   235,   240,   245,   251,   256,
     272,   279,   282,   289,   298,   308,   312,   319,   327,   335,
     343,   348,   354,   360,   411,   426,   439,   447,   452,   459,
     463,   471,   478,   487,   497,   508,   512,   519,   526,   533,
     539,   546,   553,   561,   568,   575,   582,   588,   594,   600,
     606,   613,   618,   626,   631,   635,   641,   648,   658,   662,
     669,   677,   684,   694,   704,   710,   718,   729,   735,   746,
     753,   762,   772,   782,   789,   796,   803,   809,   815,   821,
     828,   835,   842,   848,   878,   886,   894,   920,   928,   935,
     944,   951,   960
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "FUNCTION",
  "PROCEDURE", "TO", "DOWNTO", "ARRAY", "TYPE", "CONST", "RECORD",
  "STRING", "IF", "THEN", "ELSE", "OF", "WHILE", "DO", "FOR", "REPEAT",
  "UNTIL", "BEGIN_", "END", "ADDOP", "NOT", "PLUS", "CASE", "UMINUS",
  "CONSTASSIGNOP", "ID", "CHAR", "INT_NUM", "REAL_NUM", "RELOP", "MULOP",
  "STRING_", "VAR", "SUBCATALOG", "ASSIGNOP", "';'", "'.'", "'('", "')'",
  "','", "'='", "':'", "'['", "']'", "$accept", "program", "program_head",
  "program_body", "id_list", "const_declarations", "const_declaration",
  "const_value", "record_declarations", "record_declaration",
  "var_declarations", "var_declaration", "type", "array_type", "periods",
  "period", "string_type", "subprogram_declarations",
  "subprogram_declaration", "subprogram_body", "subprogram_head",
  "formal_parameter", "parameter_lists", "parameter_list", "var_parameter",
  "value_parameter", "compound_statement", "statement_list", "statement",
  "assignop_statement", "procedure_call", "ifstatement", "else_part",
  "loopstatement", "variable_list", "variable", "id_varparts",
  "id_varpart", "expression_list", "expression", "simple_expression",
  "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-129)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-78)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,    20,    29,    61,    22,  -129,    24,    37,    98,  -129,
     -11,    69,    84,  -129,   102,    92,   130,  -129,   101,    60,
      62,   118,   121,   137,  -129,   143,  -129,   112,   145,   122,
     124,  -129,  -129,  -129,  -129,  -129,   131,   166,    86,   138,
      11,   150,  -129,  -129,  -129,  -129,  -129,  -129,    62,   137,
       6,   137,   151,   152,   123,   140,    61,  -129,   172,  -129,
      -2,   139,   137,   141,  -129,  -129,  -129,  -129,   100,   142,
     142,    80,    80,   155,   123,    26,  -129,    -1,  -129,  -129,
    -129,  -129,  -129,   148,  -129,    92,  -129,   137,   149,   137,
     158,     2,   160,     6,    -3,   147,   154,    95,    95,    95,
     153,  -129,  -129,  -129,  -129,    80,  -129,   177,    27,   161,
    -129,   179,   162,   -12,    44,    50,  -129,   123,    80,   176,
       3,  -129,   164,    -4,  -129,   163,   156,  -129,   137,   103,
       9,  -129,  -129,  -129,     6,  -129,    95,  -129,   161,   161,
    -129,    80,   157,   123,    95,    95,    95,    80,    80,    95,
     123,    80,    80,  -129,   115,   117,   125,  -129,   169,    80,
    -129,  -129,  -129,  -129,   165,   174,   158,   191,  -129,  -129,
    -129,     6,    -3,  -129,   168,  -129,   127,  -129,   194,   161,
     161,   161,    91,    91,  -129,  -129,   159,  -129,  -129,   180,
    -129,    80,  -129,    52,  -129,  -129,  -129,     6,  -129,  -129,
    -129,  -129,   123,  -129,    80,    80,  -129,  -129,  -129,  -129,
    -129,  -129,   193,   195,   123,   123,  -129,  -129
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     9,     0,     1,     0,     0,    21,     5,
       0,     0,     0,     2,     0,    25,    22,     8,     0,     0,
       0,    10,     0,     0,    39,     0,     4,     0,     0,     0,
       0,    20,    15,    18,    19,    12,     0,     0,     0,     0,
       0,     0,     3,     7,    13,    16,    14,    17,     0,     0,
       0,    26,     0,     0,    61,     0,     9,     6,     0,    11,
       0,     0,     0,    38,    29,    28,    30,    32,     0,    45,
      45,     0,     0,     0,    61,    63,    58,     0,    55,    56,
      57,    59,    60,     0,    40,    25,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      77,    97,    94,    95,    96,     0,    98,     0,    85,    86,
      92,     0,     0,     0,     0,    76,    53,    61,     0,     0,
       0,    23,     0,     0,    35,     0,     0,    27,     0,     0,
       0,    48,    49,    50,     0,    44,     0,   101,    87,    88,
      92,     0,     0,    61,     0,     0,     0,     0,     0,     0,
      61,     0,     0,    64,     0,    98,     0,    82,     0,     0,
      78,    54,    62,    42,     0,     0,     0,     0,    31,    37,
      51,     0,     0,    46,     0,   102,     0,   100,    68,    89,
      90,    91,    84,    83,    93,    70,     0,    71,    66,     0,
      65,     0,    80,     0,    24,    36,    34,     0,    52,    47,
      43,    99,    61,    67,     0,     0,    77,    75,    81,    79,
      33,    69,     0,     0,    61,    61,    73,    72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -129,  -129,  -129,  -129,   -10,   167,  -129,   170,  -129,  -129,
     129,   -42,   -88,  -129,  -129,    46,  -129,  -129,  -129,  -129,
    -129,   146,  -129,    43,  -129,    89,   -34,   171,  -113,  -129,
    -129,  -129,  -129,  -129,  -129,   -51,  -129,  -129,  -128,   -70,
      25,   -87,   -89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     7,    38,     8,    12,    35,    15,    16,
      24,    39,    65,    66,   123,   124,    67,    40,    55,    86,
      56,    95,   130,   131,   132,   133,    76,    77,    78,    79,
      80,    81,   203,    82,   154,   106,   115,   160,   156,   157,
     108,   109,   110
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,   107,   111,    83,   161,   127,    57,    60,   137,   152,
     140,   138,   139,   176,    61,    52,    53,    62,    63,    17,
      91,    88,   116,    83,     1,   125,   164,    17,   117,     5,
     178,   193,    18,    54,   128,   142,    64,   185,    89,   117,
     166,    68,    89,    89,   167,   120,   174,   175,   162,   172,
       4,   144,   173,   145,    11,   146,   147,   179,   180,   181,
     184,   148,     9,   155,    10,   -77,    83,   -77,   114,    97,
      98,     6,    99,   -77,   100,   101,   102,   103,    13,    68,
     104,   186,   187,   198,   129,   163,   105,   153,    29,   211,
      30,   158,    83,    31,    32,    33,   191,   159,    34,    83,
     209,   216,   217,    27,    28,    97,    98,    14,    99,   210,
     100,   101,   102,   103,    20,   144,   104,   145,   129,   146,
      97,   208,   105,   136,    21,   100,   101,   102,   103,    23,
      28,   104,    50,    22,   212,   213,    71,   105,   207,    25,
      72,    26,    73,    74,    28,    54,    93,    28,    36,   171,
      37,    83,    42,    75,    44,    45,    46,    47,   188,   189,
     -74,   -74,   129,    83,    83,   204,   205,    17,   190,   191,
     201,   191,   182,   183,    41,    43,    48,    49,    51,    58,
      84,    69,    70,    87,    94,   112,    90,   118,    92,   121,
     122,   143,   126,   134,   135,   141,   149,   150,    54,   192,
     177,   151,   165,   168,   169,   194,   195,   197,   200,   202,
     206,   214,   196,   215,   119,   199,    96,   170,    59,     0,
       0,     0,     0,    85,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113
};

static const yytype_int16 yycheck[] =
{
      10,    71,    72,    54,   117,    93,    40,    49,    97,    21,
      99,    98,    99,   141,     8,     4,     5,    11,    12,    30,
      62,    23,    23,    74,     3,    23,    23,    30,    40,     0,
     143,   159,    43,    22,    37,   105,    30,   150,    40,    40,
      44,    51,    40,    40,    48,    87,   134,   136,   118,    40,
      30,    24,    43,    26,    30,    28,    29,   144,   145,   146,
     149,    34,    40,   114,    42,    39,   117,    41,    42,    25,
      26,    10,    28,    47,    30,    31,    32,    33,    41,    89,
      36,   151,   152,   171,    94,   119,    42,    43,    26,   202,
      28,    41,   143,    31,    32,    33,    44,    47,    36,   150,
      48,   214,   215,    43,    44,    25,    26,     9,    28,   197,
      30,    31,    32,    33,    45,    24,    36,    26,   128,    28,
      25,   191,    42,    28,    40,    30,    31,    32,    33,    37,
      44,    36,    46,    31,   204,   205,    13,    42,   189,     9,
      17,    40,    19,    20,    44,    22,    46,    44,    30,    46,
      29,   202,    40,    30,    32,    33,    32,    33,    43,    44,
      43,    44,   172,   214,   215,     6,     7,    30,    43,    44,
      43,    44,   147,   148,    31,    30,    45,    11,    40,    29,
      40,    30,    30,    11,    42,    30,    47,    39,    47,    40,
      32,    14,    32,    46,    40,    42,    35,    18,    22,    30,
      43,    39,    38,    40,    48,    40,    32,    16,    40,    15,
      30,    18,   166,    18,    85,   172,    70,   128,    48,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    50,    51,    30,     0,    10,    52,    54,    40,
      42,    30,    55,    41,     9,    57,    58,    30,    43,    53,
      45,    40,    31,    37,    59,     9,    40,    43,    44,    26,
      28,    31,    32,    33,    36,    56,    30,    29,    53,    60,
      66,    31,    40,    30,    32,    33,    32,    33,    45,    11,
      46,    40,     4,     5,    22,    67,    69,    75,    29,    56,
      60,     8,    11,    12,    30,    61,    62,    65,    53,    30,
      30,    13,    17,    19,    20,    30,    75,    76,    77,    78,
      79,    80,    82,    84,    40,    54,    68,    11,    23,    40,
      47,    60,    47,    46,    42,    70,    70,    25,    26,    28,
      30,    31,    32,    33,    36,    42,    84,    88,    89,    90,
      91,    88,    30,    76,    42,    85,    23,    40,    39,    59,
      60,    40,    32,    63,    64,    23,    32,    61,    37,    53,
      71,    72,    73,    74,    46,    40,    28,    91,    90,    90,
      91,    42,    88,    14,    24,    26,    28,    29,    34,    35,
      18,    39,    21,    43,    83,    84,    87,    88,    41,    47,
      86,    77,    88,    75,    23,    38,    44,    48,    40,    48,
      74,    46,    40,    43,    61,    91,    87,    43,    77,    90,
      90,    90,    89,    89,    91,    77,    88,    88,    43,    44,
      43,    44,    30,    87,    40,    32,    64,    16,    61,    72,
      40,    43,    15,    81,     6,     7,    30,    84,    88,    48,
      61,    77,    88,    88,    18,    18,    77,    77
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    56,    56,    56,    56,    56,
      56,    57,    57,    58,    58,    59,    59,    60,    60,    61,
      61,    61,    61,    62,    63,    63,    64,    65,    65,    66,
      66,    67,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    74,    75,    76,    76,    77,    77,    77,    77,
      77,    77,    78,    79,    79,    79,    79,    80,    81,    81,
      82,    82,    82,    82,    83,    83,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     6,     5,     3,     5,     3,     1,     0,
       3,     5,     3,     2,     2,     1,     2,     2,     1,     1,
       1,     0,     1,     7,     8,     0,     3,     5,     3,     1,
       1,     4,     1,     6,     3,     1,     3,     4,     1,     0,
       3,     2,     3,     6,     4,     0,     3,     3,     1,     1,
       1,     2,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     0,     3,     1,     3,     4,     4,     5,     0,     2,
       4,     4,     8,     8,     1,     3,     2,     0,     2,     3,
       2,     3,     1,     3,     3,     1,     1,     2,     2,     3,
       3,     3,     1,     3,     1,     1,     1,     1,     1,     4,
       3,     2,     2
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
        yyerror (Ast, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, Ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, ast::AST *Ast)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (Ast);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, ast::AST *Ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, Ast);
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
                 int yyrule, ast::AST *Ast)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], Ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, Ast); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, ast::AST *Ast)
{
  YY_USE (yyvaluep);
  YY_USE (Ast);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (ast::AST *Ast)
{
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
      yychar = yylex ();
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
  case 2: /* program: program_head program_body '.'  */
#line 140 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // prgram -> program_head program_body '.'
	    ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child((yyvsp[-2].program_head_node));
        headnode->append_child((yyvsp[-1].program_body_node));

        Ast->set_root(headnode);
    }
#line 1337 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 3: /* program_head: PROGRAM ID '(' id_list ')' ';'  */
#line 149 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
                                              {
        // program_head -> PROGRAM ID '(' id_list ')' ';'
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.program_head_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.program_head_node)->append_child(leaf_node);
    }
#line 1349 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 4: /* program_head: PROGRAM ID '(' ')' ';'  */
#line 155 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
                                {
        // program_head -> PROGRAM ID '('  ')' ';'
        (yyval.program_head_node) = new ProgramHead();
    }
#line 1358 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 5: /* program_head: PROGRAM ID ';'  */
#line 158 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
                       {
        // program_head -> PROGRAM ID ';'
        (yyval.program_head_node) = new ProgramHead();
    }
#line 1367 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 6: /* program_body: const_declarations record_declarations var_declarations subprogram_declarations compound_statement  */
#line 163 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
                                                                                                                  {
        // program_body -> const_declarations type_declarations var_declarations subprogram_declarations compound_statement
        (yyval.program_body_node) = new ProgramBody();
        (yyval.program_body_node)->append_child((yyvsp[-4].const_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-3].record_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-2].var_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-1].subprogram_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 1381 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 7: /* id_list: id_list ',' ID  */
#line 173 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
                         { 
        // id_list -> id_list ',' ID
        // 插入idlist node以及叶子节点
        (yyval.idlist_node) = new IdList(IdList::GrammarType::MULTIPLE_ID);
        LeafNode* leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::NAME);
        (yyval.idlist_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.idlist_node)->append_child(leaf_node);
    }
#line 1394 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 8: /* id_list: ID  */
#line 180 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
           {
        // id_list -> ID
        (yyval.idlist_node) = new IdList(IdList::GrammarType::SINGLE_ID);
        LeafNode* leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::NAME);
        (yyval.idlist_node)->append_child(leaf_node);
    }
#line 1405 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 9: /* const_declarations: %empty  */
#line 187 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
                    {
        // const_declarations -> ε
        (yyval.const_declarations_node) = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
    }
#line 1414 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 10: /* const_declarations: CONST const_declaration ';'  */
#line 192 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_declarations -> CONST const_declaration ';'
        (yyval.const_declarations_node) = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        (yyval.const_declarations_node)->append_child((yyvsp[-1].const_declaration_node));
    }
#line 1424 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 11: /* const_declaration: const_declaration ';' ID '=' const_value  */
#line 199 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_declaration -> const_declaration ';' ID '=' const_value
        (yyval.const_declaration_node) = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, (yyvsp[0].const_value_node)->type());
        (yyval.const_declaration_node)->append_child((yyvsp[-4].const_declaration_node));
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*(yyvsp[0].const_value_node), LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        
    }
#line 1441 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 12: /* const_declaration: ID '=' const_value  */
#line 212 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_declaration -> ID '=' const_value
        (yyval.const_declaration_node) = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, (yyvsp[0].const_value_node)->type());
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*(yyvsp[0].const_value_node), LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
    }
#line 1456 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 13: /* const_value: PLUS INT_NUM  */
#line 225 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_value -> + INT_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1465 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 14: /* const_value: UMINUS INT_NUM  */
#line 230 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_value -> - INT_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
        (yyval.const_value_node)->set_uminus();
    }
#line 1475 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 15: /* const_value: INT_NUM  */
#line 236 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_value -> INT_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1484 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 16: /* const_value: PLUS REAL_NUM  */
#line 241 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_value -> REAL_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1493 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 17: /* const_value: UMINUS REAL_NUM  */
#line 246 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_value -> REAL_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
        (yyval.const_value_node)->set_uminus();
    }
#line 1503 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 18: /* const_value: REAL_NUM  */
#line 252 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_value -> REAL_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1512 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 19: /* const_value: STRING_  */
#line 257 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_variable -> string
        if((yyvsp[0].token_info).value.get<string>() == "TRUE"){
            //boolean true
            (yyval.const_value_node) = new ConstValue(true);
        }
        else if((yyvsp[0].token_info).value.get<string>() == "FALSE"){
            //boolean false
            (yyval.const_value_node) = new ConstValue(false);
        }
        else {
            //字符
            (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
        }
    }
#line 1532 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 20: /* const_value: CHAR  */
#line 273 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_variable -> CHAR | TRUE | FALSE
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1541 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 21: /* record_declarations: %empty  */
#line 279 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.record_declarations_node) = new RecordDeclarations(RecordDeclarations::GrammarType::EPSILON);
    }
#line 1549 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 22: /* record_declarations: record_declaration  */
#line 283 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // record_declarations -> ε | record_declaration
        (yyval.record_declarations_node) = new RecordDeclarations(RecordDeclarations::GrammarType::DECLARATION);
        (yyval.record_declarations_node)->append_child((yyvsp[0].record_declaration_node));
    }
#line 1559 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 23: /* record_declaration: TYPE CHAR CONSTASSIGNOP RECORD var_declaration END ';'  */
#line 290 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // record_declaration -> def-record | record_declaration def-record
        (yyval.record_declaration_node) = new RecordDeclaration(RecordDeclaration::GrammarType::SINGLE_DECLARATION);
        LeafNode* leaf_node = new LeafNode((yyvsp[-5].token_info).value, LeafNode::LeafType::NAME);
        (yyval.record_declaration_node)->append_child(leaf_node);
        (yyval.record_declaration_node)->append_child((yyvsp[-2].var_declaration_node));

    }
#line 1572 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 24: /* record_declaration: record_declaration TYPE CHAR CONSTASSIGNOP RECORD var_declaration END ';'  */
#line 299 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.record_declaration_node) = new RecordDeclaration(RecordDeclaration::GrammarType::MULTI_DECLARATION);
        (yyval.record_declaration_node)->append_child((yyvsp[-7].record_declaration_node));
        LeafNode* leaf_node = new LeafNode((yyvsp[-5].token_info).value, LeafNode::LeafType::NAME);
        (yyval.record_declaration_node)->append_child(leaf_node);
        (yyval.record_declaration_node)->append_child((yyvsp[-2].var_declaration_node));
    }
#line 1584 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 25: /* var_declarations: %empty  */
#line 308 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declarations -> ε
        (yyval.var_declarations_node) = new VarDeclarations(VarDeclarations::GrammarType::EPSILON);
    }
#line 1593 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 26: /* var_declarations: VAR var_declaration ';'  */
#line 313 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declarations -> VAR var_declaration ';'
        (yyval.var_declarations_node) = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        (yyval.var_declarations_node)->append_child((yyvsp[-1].var_declaration_node));
    }
#line 1603 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 27: /* var_declaration: var_declaration ';' id_list ':' type  */
#line 320 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declaration -> var_declaration ';' id_list ':' type
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        (yyval.var_declaration_node)->append_child((yyvsp[-4].var_declaration_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[0].type_node));
    }
#line 1615 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 28: /* var_declaration: id_list ':' type  */
#line 328 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declaration -> id_list ':' type
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        (yyval.var_declaration_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[0].type_node));
    }
#line 1626 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 29: /* type: ID  */
#line 336 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // type -> ID
        // 由于我们将integer等都设为保留字，都识别为ID（integer char boolean string real）
        (yyval.type_node) = new TypeNode(TypeNode::VarType::ID_TYPE, (yyvsp[0].token_info).value.get<string>());
        //IdTypeNode* idnode = new IdTypeNode($1.value.get());
        //$$->append_child(idnode);
    }
#line 1638 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 30: /* type: array_type  */
#line 344 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.type_node) = new TypeNode(TypeNode::VarType::ARRAY_TYPE, "array");
        (yyval.type_node)->append_child((yyvsp[0].array_node));
    }
#line 1647 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 31: /* type: RECORD var_declaration END ';'  */
#line 349 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // recordtype -> record var_declaration end;
        (yyval.type_node) = new TypeNode(TypeNode::VarType::RECORD_TYPE, "record");
        (yyval.type_node)->append_child((yyvsp[-2].var_declaration_node));
    }
#line 1657 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 32: /* type: string_type  */
#line 355 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.type_node) = new TypeNode(TypeNode::VarType::STRING_TYPE, "string");
        (yyval.type_node)->append_child((yyvsp[0].string_node));
    }
#line 1666 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 33: /* array_type: ARRAY '[' periods ']' OF type  */
#line 361 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        (yyval.array_node) = new ArrayTypeNode();
        if ((yyvsp[0].type_node)->GetVarType() == TypeNode::VarType::STRING_TYPE || (yyvsp[0].type_node)->GetVarType() == TypeNode::VarType::RECORD_TYPE){
            // 不支持数组的元素类型为string
            // 不支持在array的type中声明record
            (yyval.array_node) -> set_type("error");
        }
        else if((yyvsp[0].type_node)->GetVarType() == TypeNode::VarType::ID_TYPE){
            (yyval.array_node) -> set_type((yyvsp[0].type_node)->get_type_name());
        }
        else {
            (yyval.array_node) -> set_type("array");
        }
        // 添加数组信息
        ArrayType* at = new ArrayType();
        at->SetDimension((yyvsp[-3].periods_node)->get_dm());
        (yyval.array_node)->set_info(at);

        (yyval.array_node)->append_child((yyvsp[-3].periods_node));
        (yyval.array_node)->append_child((yyvsp[0].type_node));
    }
#line 1692 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 34: /* periods: periods ',' period  */
#line 412 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // periods -> periods ',' period
        (yyval.periods_node) = new PeriodsNode(PeriodsNode::PeriodType::MULTI);
        
        // 插入新的维度
        std::vector<ArrayType::Dimension> dim;
        dim = (yyvsp[-2].periods_node)->get_dm();
        ArrayType::Dimension nd((yyvsp[0].period_node)->get_lowb(), (yyvsp[0].period_node)->get_upb());
        dim.emplace_back(nd);
        (yyval.periods_node)->set_dm(dim);

        (yyval.periods_node)->append_child((yyvsp[-2].periods_node));
        (yyval.periods_node)->append_child((yyvsp[0].period_node));
    }
#line 1711 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 35: /* periods: period  */
#line 427 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // periods -> period
        (yyval.periods_node) = new PeriodsNode(PeriodsNode::PeriodType::SINGLE);
        
        // 底层新建维度vector
        std::vector<ArrayType::Dimension> dim;
        ArrayType::Dimension nd((yyvsp[0].period_node)->get_lowb(), (yyvsp[0].period_node)->get_upb());
        dim.emplace_back(nd);
        (yyval.periods_node)->set_dm(dim);
        (yyval.periods_node)->append_child((yyvsp[0].period_node));
    }
#line 1727 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 36: /* period: INT_NUM SUBCATALOG INT_NUM  */
#line 440 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        (yyval.period_node) = new PeriodNode((yyvsp[-2].token_info).value.get<int>(), (yyvsp[0].token_info).value.get<int>());
        (yyval.period_node)->append_child(new LeafNode((yyvsp[-2].token_info).value.get<int>(), LeafNode::LeafType::VALUE));
        (yyval.period_node)->append_child(new LeafNode((yyvsp[0].token_info).value.get<int>(), LeafNode::LeafType::VALUE));
    }
#line 1738 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 37: /* string_type: STRING '[' INT_NUM ']'  */
#line 448 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        StringType* string_info = new StringType(StringType::GrammarType::LIMIT, (yyvsp[-1].token_info).value.get<int>());
        (yyval.string_node) = new StringTypeNode(string_info);
    }
#line 1747 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 38: /* string_type: STRING  */
#line 453 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        StringType* string_info = new StringType(StringType::GrammarType::NOLIMIT, 0);
        (yyval.string_node) = new StringTypeNode(string_info);
    }
#line 1756 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 39: /* subprogram_declarations: %empty  */
#line 459 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_declarations -> ε
        (yyval.subprogram_declarations_node) = new SubprogramDeclarations();
    }
#line 1765 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 40: /* subprogram_declarations: subprogram_declarations subprogram_declaration ';'  */
#line 464 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_declarations -> subprogram_declarations subprogram_declaration ';'
        (yyval.subprogram_declarations_node) = new SubprogramDeclarations();
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-2].subprogram_declarations_node));
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-1].subprogram_declaration_node));
    }
#line 1776 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 41: /* subprogram_declaration: subprogram_head subprogram_body  */
#line 472 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_declaration -> subprogram_head subprogram_body
        (yyval.subprogram_declaration_node) = new SubprogramDeclaration();
        (yyval.subprogram_declaration_node)->append_child((yyvsp[-1].subprogram_head_node));
        (yyval.subprogram_declaration_node)->append_child((yyvsp[0].subprogram_body_node));
    }
#line 1787 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 42: /* subprogram_body: const_declarations var_declarations compound_statement  */
#line 479 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_body -> const_declarations var_declarations compound_statement
        (yyval.subprogram_body_node) = new SubprogramBody();
        (yyval.subprogram_body_node)->append_child((yyvsp[-2].const_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[-1].var_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 1799 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 43: /* subprogram_head: FUNCTION ID formal_parameter ':' type ';'  */
#line 488 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_head -> FUNCTION ID formal_parameter ':' standrad_type ';'
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_id((yyvsp[-4].token_info).value.get<string>());
        LeafNode *leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-3].formal_param_node));
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].type_node));
    }
#line 1813 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 44: /* subprogram_head: PROCEDURE ID formal_parameter ';'  */
#line 498 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_head -> PROCEDURE ID formal_parameter ';'
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::PROC);
        LeafNode *leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.subprogram_head_node)->set_id((yyvsp[-2].token_info).value.get<string>());
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].formal_param_node));
    }
#line 1826 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 45: /* formal_parameter: %empty  */
#line 508 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // formal_parameter -> ε
        (yyval.formal_param_node) = new FormalParam();
    }
#line 1835 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 46: /* formal_parameter: '(' parameter_lists ')'  */
#line 513 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // formal_parameter -> '(' parameter_lists ')'
        (yyval.formal_param_node) = new FormalParam();
        (yyval.formal_param_node)->append_child((yyvsp[-1].paramlists_node));
    }
#line 1845 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 47: /* parameter_lists: parameter_lists ';' parameter_list  */
#line 520 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // parameter_lists -> parameter_lists ';' parameter_list
        (yyval.paramlists_node) = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        (yyval.paramlists_node)->append_child((yyvsp[-2].paramlists_node));
        (yyval.paramlists_node)->append_child((yyvsp[0].paramlist_node));
    }
#line 1856 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 48: /* parameter_lists: parameter_list  */
#line 527 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {  
        // parameter_lists -> parameter_list
        (yyval.paramlists_node) = new ParamLists(ParamLists::GrammarType::SINGLE_PARAM_LIST);
        (yyval.paramlists_node)->append_child((yyvsp[0].paramlist_node));
    }
#line 1866 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 49: /* parameter_list: var_parameter  */
#line 534 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // parameter_list -> var_parameter
        (yyval.paramlist_node) = new ParamList(ParamList::ParamType::VarParam);
        (yyval.paramlist_node)->append_child((yyvsp[0].var_param_node));
    }
#line 1876 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 50: /* parameter_list: value_parameter  */
#line 540 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // parameter_list -> value_parameter
        (yyval.paramlist_node) = new ParamList(ParamList::ParamType::ValueParam);
        (yyval.paramlist_node)->append_child((yyvsp[0].value_param_node));
    }
#line 1886 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 51: /* var_parameter: VAR value_parameter  */
#line 547 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // var_parameter -> VAR value_parameter
        (yyval.var_param_node) = new VarParam();
        (yyval.var_param_node)->append_child((yyvsp[0].value_param_node));
    }
#line 1896 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 52: /* value_parameter: id_list ':' type  */
#line 554 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // value_parameter -> id_list ':' standrad_type
        (yyval.value_param_node) = new ValueParam();
        (yyval.value_param_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.value_param_node)->append_child((yyvsp[0].type_node));
    }
#line 1907 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 53: /* compound_statement: BEGIN_ statement_list END  */
#line 562 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // compound_statement -> Begin statement_list end
        (yyval.compound_statement_node) = new CompoundStatement();
        (yyval.compound_statement_node)->append_child((yyvsp[-1].statement_list_node));
    }
#line 1917 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 54: /* statement_list: statement_list ';' statement  */
#line 569 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement_list -> statement_list ';' statement
        (yyval.statement_list_node) = new StatementList();
        (yyval.statement_list_node)->append_child((yyvsp[-2].statement_list_node));
        (yyval.statement_list_node)->append_child((yyvsp[0].statement_node));
    }
#line 1928 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 55: /* statement_list: statement  */
#line 576 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement_list -> statement
        (yyval.statement_list_node) = new StatementList();
        (yyval.statement_list_node)->append_child((yyvsp[0].statement_node));
    }
#line 1938 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 56: /* statement: assignop_statement  */
#line 583 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        //statement -> AssignopStatement
        (yyval.statement_node) = new Statement(Statement::StatementType::ASSIGN_OP_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[0].assignop_statement_node));
    }
#line 1948 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 57: /* statement: procedure_call  */
#line 589 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> call_procedure_statement
        (yyval.statement_node) = new Statement(Statement::StatementType::PROCEDURE_CALL);
        (yyval.statement_node)->append_child((yyvsp[0].procedure_call_node));
    }
#line 1958 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 58: /* statement: compound_statement  */
#line 595 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> compound_statement
        (yyval.statement_node) = new Statement(Statement::StatementType::COMPOUND_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 1968 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 59: /* statement: ifstatement  */
#line 601 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // statement -> IF expression THEN statement else_part
        (yyval.statement_node) = new Statement(Statement::StatementType::IF_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[0].ifstatement_node));
    }
#line 1978 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 60: /* statement: loopstatement  */
#line 607 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> CASE expression OF case_body END
        (yyval.statement_node) = new Statement(Statement::StatementType::LOOP_STATEMENT);
        (yyval.statement_node)->append_child((yyvsp[0].loopstatement_node));
    }
#line 1988 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 61: /* statement: %empty  */
#line 613 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> ε
        (yyval.statement_node) = new Statement(Statement::StatementType::EPSILON);
    }
#line 1997 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 62: /* assignop_statement: variable ASSIGNOP expression  */
#line 619 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // assignop_statement -> variable ASSIGNOP expression
        (yyval.assignop_statement_node) = new AssignopStatement(AssignopStatement::LeftType::VARIABLE);
        (yyval.assignop_statement_node)->append_child((yyvsp[-2].variable_node));
        (yyval.assignop_statement_node)->append_child((yyvsp[0].expression_node));
    }
#line 2008 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 63: /* procedure_call: ID  */
#line 627 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // procedure_call -> id
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, (yyvsp[0].token_info).value.get<string>());
    }
#line 2017 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 64: /* procedure_call: ID '(' ')'  */
#line 632 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, (yyvsp[-2].token_info).value.get<string>());
    }
#line 2025 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 65: /* procedure_call: ID '(' expression_list ')'  */
#line 636 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // procedure_call -> id ( expression_list )
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::EXP_LIST, (yyvsp[-3].token_info).value.get<string>());
        (yyval.procedure_call_node)->append_child((yyvsp[-1].expression_list_node));
    }
#line 2035 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 66: /* procedure_call: ID '(' variable_list ')'  */
#line 642 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // procedure_call -> id ( expression_list )
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::VAR_LIST, (yyvsp[-3].token_info).value.get<string>());
        (yyval.procedure_call_node)->append_child((yyvsp[-1].variablelist_node));
    }
#line 2045 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 67: /* ifstatement: IF expression THEN statement else_part  */
#line 649 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // if_statement -> if expression then statement else_part
        (yyval.ifstatement_node) = new IfStatement();
        (yyval.ifstatement_node)->append_child((yyvsp[-3].expression_node));
        (yyval.ifstatement_node)->append_child((yyvsp[-1].statement_node));
        (yyval.ifstatement_node)->append_child((yyvsp[0].elsepart_node));
    }
#line 2057 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 68: /* else_part: %empty  */
#line 658 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // else_part -> ε | else statement
        (yyval.elsepart_node) = new ElsePart(ElsePart::ELSEType::EPSILON);
    }
#line 2066 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 69: /* else_part: ELSE statement  */
#line 663 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // else_part -> else statement
        (yyval.elsepart_node) = new ElsePart(ElsePart::ELSEType::ELSE_STATEMENT);
        (yyval.elsepart_node)->append_child((yyvsp[0].statement_node));
    }
#line 2076 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 70: /* loopstatement: WHILE expression DO statement  */
#line 670 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> WHILE expression DO statement
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::WHILE_);
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));

    }
#line 2088 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 71: /* loopstatement: REPEAT statement_list UNTIL expression  */
#line 678 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> repeat statement until expression
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::REPEAT_);
        (yyval.loopstatement_node)->append_child((yyvsp[-2].statement_list_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].expression_node));
    }
#line 2099 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 72: /* loopstatement: FOR ID ASSIGNOP expression DOWNTO expression DO statement  */
#line 685 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> FOR ID ASSIGNOP expression downto expression DO statement
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        LeafNode *leaf_node = new LeafNode((yyvsp[-6].token_info).value, LeafNode::LeafType::NAME); 
        (yyval.loopstatement_node)->append_child(leaf_node);
        (yyval.loopstatement_node)->append_child((yyvsp[-4].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
    }
#line 2113 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 73: /* loopstatement: FOR ID ASSIGNOP expression TO expression DO statement  */
#line 695 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::FORUP);
        LeafNode *leaf_node = new LeafNode((yyvsp[-6].token_info).value, LeafNode::LeafType::NAME); 
        (yyval.loopstatement_node)->append_child(leaf_node);
        (yyval.loopstatement_node)->append_child((yyvsp[-4].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
    }
#line 2126 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 74: /* variable_list: variable  */
#line 705 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    { 
        // variable_list -> variable
        (yyval.variablelist_node) = new VariableList(VariableList::GrammarType::VAR_);
        (yyval.variablelist_node)->append_child((yyvsp[0].variable_node));
    }
#line 2136 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 75: /* variable_list: variable_list ',' variable  */
#line 711 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // variable_list -> variable_list ',' variable
        (yyval.variablelist_node) = new VariableList(VariableList::GrammarType::VAR_LIST_VAR);
        (yyval.variablelist_node)->append_child((yyvsp[-2].variablelist_node));
        (yyval.variablelist_node)->append_child((yyvsp[0].variable_node));
    }
#line 2147 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 76: /* variable: ID id_varparts  */
#line 719 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // variable -> ID id_varparts
        (yyval.variable_node) = new Variable();
        LeafNode *leaf_node = new LeafNode((yyvsp[-1].token_info).value, LeafNode::LeafType::NAME);
        // 变量的类型需要符号表来进行判断
        (yyval.variable_node)->append_child(leaf_node);
        (yyval.variable_node)->append_child((yyvsp[0].idvarparts_node));
    }
#line 2160 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 77: /* id_varparts: %empty  */
#line 729 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // id_varparts -> ε.
        (yyval.idvarparts_node) = new IDVarParts();
        std::vector<std::string> *name_list = new std::vector<std::string>;
        (yyval.idvarparts_node)->set_pointer(name_list);
    }
#line 2171 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 78: /* id_varparts: id_varparts id_varpart  */
#line 736 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // id_varparts -> id_varparts id_varpart.
        (yyval.idvarparts_node) = new IDVarParts();
        std::vector<std::string> *name_list = (yyvsp[-1].idvarparts_node)->get_pointer();
        name_list->emplace_back((yyvsp[0].idvarpart_node)->get_part_name());
        (yyval.idvarparts_node)->set_pointer(name_list);
        (yyval.idvarparts_node)->append_child((yyvsp[-1].idvarparts_node));
        (yyval.idvarparts_node)->append_child((yyvsp[0].idvarpart_node));
    }
#line 2185 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 79: /* id_varpart: '[' expression_list ']'  */
#line 747 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // id_varpart -> [expression_list].
        (yyval.idvarpart_node) = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        
        (yyval.idvarpart_node)->append_child((yyvsp[-1].expression_list_node));
    }
#line 2196 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 80: /* id_varpart: '.' ID  */
#line 754 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // id_varpart -> .id.
        (yyval.idvarpart_node) = new IDVarPart(IDVarPart::GrammarType::_ID);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::NAME);
        (yyval.idvarpart_node)->set_part_name((yyvsp[0].token_info).value.get<string>());
        (yyval.idvarpart_node)->append_child(leaf_node);
    }
#line 2208 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 81: /* expression_list: expression_list ',' expression  */
#line 763 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression_list -> expression_list ',' expression
        
        std::vector<std::string> *type_list = (yyvsp[-2].expression_list_node)->get_types();
        type_list->emplace_back((yyvsp[0].expression_node)->GetExpType());
        (yyval.expression_list_node) = new ExpressionList(ExpressionList::ExpressionType::MULTIPLE, type_list);
        (yyval.expression_list_node)->append_child((yyvsp[-2].expression_list_node));
        (yyval.expression_list_node)->append_child((yyvsp[0].expression_node));
    }
#line 2222 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 82: /* expression_list: expression  */
#line 773 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression_list -> expression
        std::string type = (yyvsp[0].expression_node)->GetExpType();
        std::vector<std::string> *type_list = new std::vector<std::string>;
        type_list->emplace_back(type);
        (yyval.expression_list_node) = new ExpressionList(ExpressionList::ExpressionType::SINGLE, type_list);
        (yyval.expression_list_node)->append_child((yyvsp[0].expression_node));
    }
#line 2235 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 83: /* expression: simple_expression RELOP simple_expression  */
#line 783 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression -> simple_expression RELOP simple_expression.
        (yyval.expression_node) = new Expression(Expression::GrammarType::DOUBLE, (yyvsp[-1].token_info).value.get<string>(), "bool");
        (yyval.expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.expression_node)->append_child((yyvsp[0].simple_expression_node));
    }
#line 2246 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 84: /* expression: simple_expression CONSTASSIGNOP simple_expression  */
#line 790 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression -> simple_expression '=' simple_expression.
        (yyval.expression_node) = new Expression(Expression::GrammarType::DOUBLE, "=", "bool");
        (yyval.expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.expression_node)->append_child((yyvsp[0].simple_expression_node));
    }
#line 2257 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 85: /* expression: simple_expression  */
#line 797 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression -> simple_expression.
        (yyval.expression_node) = new Expression(Expression::GrammarType::SINGLE, " ", (yyvsp[0].simple_expression_node)->GetExpType());
        (yyval.expression_node)->append_child((yyvsp[0].simple_expression_node));
    }
#line 2267 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 86: /* simple_expression: term  */
#line 804 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // simple_expression -> term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::SINGLE, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2277 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 87: /* simple_expression: PLUS term  */
#line 810 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // simple_expression -> + term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2287 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 88: /* simple_expression: UMINUS term  */
#line 816 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // simple_expression -> - term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2297 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 89: /* simple_expression: simple_expression ADDOP term  */
#line 822 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // simple_expression -> simple_expression or term.、
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::OR_, "bool");
        (yyval.simple_expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2308 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 90: /* simple_expression: simple_expression PLUS term  */
#line 829 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    { 
        // simple_expression -> simple_expression + term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2319 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 91: /* simple_expression: simple_expression UMINUS term  */
#line 836 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2329 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 92: /* term: factor  */
#line 843 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // term -> factor.
        (yyval.term_node) = new Term(Term::SymbolType::SINGLE, (yyvsp[0].factor_node)->GetFacType());
        (yyval.term_node)->append_child((yyvsp[0].factor_node));
    }
#line 2339 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 93: /* term: term MULOP factor  */
#line 849 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {  
        // term -> term mulop factor. 
        (yyval.term_node) = new Term;
        std::string sym_type = (yyvsp[-1].token_info).value.get<string>();
        if(sym_type == "*"){
            (yyval.term_node)->SetSymType(Term::SymbolType::MULTIPLY);
            (yyval.term_node)->SetTerType("REAL");
        }
        if(sym_type == "/"){
            (yyval.term_node)->SetSymType(Term::SymbolType::DEVIDE);
            (yyval.term_node)->SetTerType("REAL");
        }
        if(sym_type == "mod"){
            (yyval.term_node)->SetSymType(Term::SymbolType::MOD);
            (yyval.term_node)->SetTerType("REAL");
        }
        if(sym_type == "and"){
            (yyval.term_node)->SetSymType(Term::SymbolType::AND);
            (yyval.term_node)->SetTerType("BOOL");
        }
        if(sym_type == "div"){
            (yyval.term_node)->SetSymType(Term::SymbolType::DEVIDE);
            (yyval.term_node)->SetTerType("REAL");
        }
        (yyval.term_node)->append_child((yyvsp[-2].term_node));
        (yyval.term_node)->append_child((yyvsp[0].factor_node));
    }
#line 2371 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 94: /* factor: INT_NUM  */
#line 879 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> num
        (yyval.factor_node) = new Factor(Factor::GrammerType::NUM);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("INT");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2383 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 95: /* factor: REAL_NUM  */
#line 887 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> num
        (yyval.factor_node) = new Factor(Factor::GrammerType::NUM);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("INT");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2395 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 96: /* factor: STRING_  */
#line 895 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> STRING
        if((yyvsp[0].token_info).value.get<string>() == "TRUE"){
            //boolean true
            (yyval.factor_node) = new Factor(Factor::GrammerType::BOOL);
            LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
            (yyval.factor_node)->SetFacType("BOOL");
            
        }
        else if((yyvsp[0].token_info).value.get<string>() == "FALSE"){
            //boolean false
            (yyval.factor_node) = new Factor(Factor::GrammerType::BOOL);
            LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
            (yyval.factor_node)->SetFacType("BOOL");
            (yyval.factor_node)->append_child(leaf_node);
        }
        else {
            //字符
            (yyval.factor_node) = new Factor(Factor::GrammerType::STR);
            LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
            (yyval.factor_node)->SetFacType("STRING");
            (yyval.factor_node)->append_child(leaf_node);
        }
        
    }
#line 2425 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 97: /* factor: CHAR  */
#line 921 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> char
        (yyval.factor_node) = new Factor(Factor::GrammerType::CHAR_);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("CHAR");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2437 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 98: /* factor: variable  */
#line 929 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> variable.
        (yyval.factor_node) = new Factor(Factor::GrammerType::VARIABLE);
        // $$->SetFacType("STRING");
        (yyval.factor_node)->append_child((yyvsp[0].variable_node));
    }
#line 2448 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 99: /* factor: ID '(' expression_list ')'  */
#line 936 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.factor_node) = new Factor(Factor::GrammerType::ID_EXP_LIST);
        LeafNode *leaf_node = new LeafNode((yyvsp[-3].token_info).value, LeafNode::LeafType::NAME);
        // 类型需要靠符号表确认
        // $$->SetFacType("STRING");
        (yyval.factor_node)->append_child(leaf_node);
        (yyval.factor_node)->append_child((yyvsp[-1].expression_list_node));
    }
#line 2461 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 100: /* factor: '(' expression ')'  */
#line 945 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> (expression).
        (yyval.factor_node) = new Factor(Factor::GrammerType::EXP);
        (yyval.factor_node)->SetFacType((yyvsp[-1].expression_node)->GetExpType());
        (yyval.factor_node)->append_child((yyvsp[-1].expression_node));
    }
#line 2472 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 101: /* factor: NOT factor  */
#line 952 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> not factor.
        // 类型检查
        (yyval.factor_node) = new Factor(Factor::GrammerType::NOT_);
        (yyval.factor_node)->SetUminus();
        (yyval.factor_node)->SetFacType((yyvsp[0].factor_node)->GetFacType());
        (yyval.factor_node)->append_child((yyvsp[0].factor_node));
    }
#line 2485 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 102: /* factor: UMINUS factor  */
#line 961 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> not factor.
        // 类型检查
        (yyval.factor_node) = new Factor(Factor::GrammerType::UMINUS_);
        (yyval.factor_node)->SetUminus();
        (yyval.factor_node)->SetFacType((yyvsp[0].factor_node)->GetFacType());
        (yyval.factor_node)->append_child((yyvsp[0].factor_node));
    }
#line 2498 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;


#line 2502 "/root/works/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"

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
      yyerror (Ast, YY_("syntax error"));
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
                      yytoken, &yylval, Ast);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, Ast);
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
  yyerror (Ast, YY_("memory exhausted"));
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
                  yytoken, &yylval, Ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, Ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 975 "/root/works/PASCAL-S-compiler/build/../scripts/parser.y"

 

void yyerror(ast::AST* Ast,const char *msg){
    if(strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    error_flag = 1;
     Ast->set_root(nullptr);
    
}

/*void yynote(std::string msg ,int line){
    fprintf(stderr,"%d:\033[01;32m \tnote\033[0m : previous definition of \"%s\" was here\n", line, msg.c_str());
}

void yyerror_var(AST* real_ast,int line){
    fprintf(stderr,"%d:\033[01;31m \terror\033[0m : %s\n", line, "redifinition of variable");
    error_flag = 1;
    real_ast->set_root(nullptr);
}

void location_pointer_refresh(){
    int length = cur_line_info.size()-yyleng;
    if(length<0)
        length=0;
    memset(location_pointer,' ',length);
    memcpy(location_pointer+length,"^\n\0",3);
} */
int yywrap(){
    return 1;
} 
