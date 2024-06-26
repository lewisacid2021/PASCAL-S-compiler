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
#line 1 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"

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

int error_flag = 0;

void yyerror(const char *s, int line);
void yyerror(ast::AST* Ast,const char *msg);


#line 94 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"

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
  YYSYMBOL_BOOL = 39,                      /* BOOL  */
  YYSYMBOL_ASSIGNOP = 40,                  /* ASSIGNOP  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* '.'  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_46_ = 46,                       /* ':'  */
  YYSYMBOL_47_ = 47,                       /* '['  */
  YYSYMBOL_48_ = 48,                       /* ']'  */
  YYSYMBOL_49_ = 49,                       /* '='  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_program = 51,                   /* program  */
  YYSYMBOL_program_head = 52,              /* program_head  */
  YYSYMBOL_program_body = 53,              /* program_body  */
  YYSYMBOL_id_list = 54,                   /* id_list  */
  YYSYMBOL_const_declarations = 55,        /* const_declarations  */
  YYSYMBOL_const_declaration = 56,         /* const_declaration  */
  YYSYMBOL_const_value = 57,               /* const_value  */
  YYSYMBOL_record_declarations = 58,       /* record_declarations  */
  YYSYMBOL_record_declaration = 59,        /* record_declaration  */
  YYSYMBOL_var_declarations = 60,          /* var_declarations  */
  YYSYMBOL_var_declaration = 61,           /* var_declaration  */
  YYSYMBOL_type = 62,                      /* type  */
  YYSYMBOL_array_type = 63,                /* array_type  */
  YYSYMBOL_periods = 64,                   /* periods  */
  YYSYMBOL_period = 65,                    /* period  */
  YYSYMBOL_string_type = 66,               /* string_type  */
  YYSYMBOL_subprogram_declarations = 67,   /* subprogram_declarations  */
  YYSYMBOL_subprogram_declaration = 68,    /* subprogram_declaration  */
  YYSYMBOL_subprogram_body = 69,           /* subprogram_body  */
  YYSYMBOL_subprogram_head = 70,           /* subprogram_head  */
  YYSYMBOL_formal_parameter = 71,          /* formal_parameter  */
  YYSYMBOL_parameter_lists = 72,           /* parameter_lists  */
  YYSYMBOL_parameter_list = 73,            /* parameter_list  */
  YYSYMBOL_var_parameter = 74,             /* var_parameter  */
  YYSYMBOL_value_parameter = 75,           /* value_parameter  */
  YYSYMBOL_compound_statement = 76,        /* compound_statement  */
  YYSYMBOL_statement_list = 77,            /* statement_list  */
  YYSYMBOL_statement = 78,                 /* statement  */
  YYSYMBOL_assignop_statement = 79,        /* assignop_statement  */
  YYSYMBOL_procedure_call = 80,            /* procedure_call  */
  YYSYMBOL_ifstatement = 81,               /* ifstatement  */
  YYSYMBOL_else_part = 82,                 /* else_part  */
  YYSYMBOL_loopstatement = 83,             /* loopstatement  */
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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   421

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  166
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  325

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
      43,    44,     2,     2,    45,     2,    42,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    41,
       2,    49,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    94,   101,   107,   115,   126,   135,   144,
     149,   157,   171,   184,   190,   196,   201,   206,   212,   217,
     222,   227,   234,   238,   246,   255,   266,   271,   279,   288,
     297,   304,   310,   317,   324,   348,   363,   376,   385,   391,
     399,   404,   413,   421,   431,   442,   454,   459,   464,   472,
     480,   488,   495,   503,   511,   520,   528,   536,   544,   551,
     558,   565,   572,   580,   586,   595,   601,   606,   621,   632,
     637,   645,   654,   662,   673,   700,   710,   721,   728,   740,
     747,   757,   767,   777,   785,   793,   801,   808,   815,   822,
     830,   838,   846,   854,   884,   893,   902,   910,   919,   929,
     938,   946,   956,   964,   974,   988,   997,  1006,  1015,  1021,
    1030,  1036,  1042,  1048,  1056,  1063,  1071,  1076,  1081,  1092,
    1103,  1114,  1122,  1131,  1140,  1147,  1155,  1163,  1174,  1188,
    1202,  1208,  1214,  1221,  1229,  1243,  1253,  1262,  1273,  1280,
    1291,  1298,  1305,  1315,  1322,  1330,  1336,  1344,  1353,  1361,
    1369,  1376,  1383,  1391,  1400,  1410,  1421,  1432,  1443,  1451,
    1460,  1468,  1478,  1485,  1493,  1504,  1511
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
  "STRING_", "VAR", "SUBCATALOG", "BOOL", "ASSIGNOP", "';'", "'.'", "'('",
  "')'", "','", "':'", "'['", "']'", "'='", "$accept", "program",
  "program_head", "program_body", "id_list", "const_declarations",
  "const_declaration", "const_value", "record_declarations",
  "record_declaration", "var_declarations", "var_declaration", "type",
  "array_type", "periods", "period", "string_type",
  "subprogram_declarations", "subprogram_declaration", "subprogram_body",
  "subprogram_head", "formal_parameter", "parameter_lists",
  "parameter_list", "var_parameter", "value_parameter",
  "compound_statement", "statement_list", "statement",
  "assignop_statement", "procedure_call", "ifstatement", "else_part",
  "loopstatement", "variable", "id_varparts", "id_varpart",
  "expression_list", "expression", "simple_expression", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-183)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-153)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     172,    96,    99,    31,   237,    95,  -183,   176,   -20,   192,
    -183,   179,    68,  -183,    51,    67,    17,    36,  -183,   216,
     228,   297,  -183,    78,  -183,   285,   181,   211,    41,  -183,
     348,   227,   284,   289,   298,   177,  -183,   309,   308,   311,
     316,  -183,   321,  -183,   322,   103,   163,   300,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,  -183,   301,   170,   341,  -183,
       9,   179,   225,   336,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,  -183,  -183,   348,   348,   243,   179,   215,
     256,    33,   178,   183,   353,   114,    31,  -183,   357,  -183,
    -183,  -183,  -183,    13,    15,   179,   330,  -183,   337,  -183,
    -183,   344,   152,   215,   283,   250,   326,  -183,   326,   312,
     312,   352,   353,   230,  -183,    28,  -183,  -183,  -183,  -183,
    -183,   349,  -183,  -183,   228,  -183,   179,   350,   360,    16,
      80,   361,  -183,  -183,  -183,  -183,   354,  -183,   156,   105,
     351,    26,   159,   328,   328,   328,   355,  -183,  -183,  -183,
    -183,  -183,   312,  -183,    30,   186,   359,  -183,    20,   128,
     149,   151,   292,    58,   268,  -183,   353,   312,   374,    91,
    -183,    12,     8,  -183,  -183,    22,  -183,   356,  -183,  -183,
    -183,  -183,   188,  -183,    38,    93,  -183,  -183,  -183,   215,
     215,   291,  -183,  -183,   328,   328,  -183,   359,  -183,   359,
    -183,   115,    48,   353,   353,   328,   328,   328,   312,   312,
     328,   353,   353,   312,   312,   353,   312,   312,   363,    44,
    -183,   369,   155,  -183,  -183,  -183,  -183,  -183,   364,   368,
     370,   360,   360,   385,   360,    19,  -183,  -183,  -183,   215,
     296,   187,   187,  -183,   365,   366,   367,   164,  -183,  -183,
    -183,  -183,    46,  -183,  -183,   394,   394,   359,   359,   359,
     362,   362,  -183,  -183,  -183,   404,   255,  -183,  -183,   312,
    -183,   312,  -183,  -183,    23,  -183,  -183,  -183,  -183,  -183,
     215,   215,   304,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,   312,  -183,   353,  -183,  -183,   312,   312,
     312,   312,  -183,  -183,   312,  -183,  -183,  -183,  -183,  -183,
    -183,   393,   395,   100,   396,   353,   353,   353,   353,   353,
    -183,  -183,  -183,  -183,  -183
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     9,     0,     0,     1,     0,     0,    22,
     110,     0,   113,     5,     0,     0,     0,     0,     2,     0,
      26,    23,     8,     0,   111,     0,     0,     0,     0,   114,
       0,     0,   115,    10,     0,     0,    40,     0,     0,     0,
       0,   112,     0,     4,     0,     0,     0,     0,    21,    15,
      18,    20,    19,   120,   117,    12,     0,     0,     0,   121,
       0,    27,     0,     0,   105,     7,   107,   108,   109,   106,
       3,    13,    16,    14,    17,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,     0,     9,     6,     0,   118,
     119,   116,    11,     0,     0,     0,    39,    30,     0,    31,
      33,     0,     0,     0,     0,   143,    46,   144,    46,     0,
       0,     0,    63,    65,    60,     0,    57,    58,    59,    61,
      62,     0,   136,    41,    26,    42,     0,     0,   131,     0,
       0,     0,   126,   125,   127,    29,     0,   124,     0,     0,
       0,     0,     0,     0,     0,     0,    77,    99,    94,    95,
      98,    97,     0,   100,     0,    85,    86,    92,     0,     0,
       0,     0,     0,    75,    63,    55,    63,     0,     0,     0,
      24,     0,     0,    36,   132,     0,    32,     0,   123,   122,
      28,   145,     0,    47,     0,     0,    50,    51,    52,     0,
     141,     0,   142,    45,     0,     0,   103,    87,    92,    88,
      92,     0,     0,    63,    63,     0,     0,     0,     0,     0,
       0,    63,    63,     0,     0,    63,     0,     0,    66,     0,
      82,     0,     0,    78,   153,    56,    64,    43,     0,     0,
       0,     0,     0,     0,   133,     0,    38,   148,    53,   151,
       0,   146,     0,    48,     0,     0,     0,     0,    96,   104,
     165,    76,     0,   166,   102,    69,    69,    89,    90,    91,
      84,    83,    93,   158,    71,     0,     0,    72,   159,   160,
      67,     0,    80,   162,     0,    25,   135,    37,   134,    35,
       0,     0,     0,   149,   150,    54,   147,    49,   138,   139,
     140,   137,    44,   164,   101,    63,   154,    68,     0,     0,
       0,     0,   161,    81,   163,    79,   128,   129,   130,    34,
      70,     0,     0,     0,     0,    63,    63,    63,    63,    63,
     155,   156,   157,    74,    73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,  -183,  -183,     0,   329,  -183,    -1,  -183,  -183,
     288,   -63,   -78,  -183,   287,   -58,  -183,  -183,  -183,  -183,
    -183,   203,  -183,    59,  -183,   235,   -61,   306,   -79,  -183,
    -183,  -183,   165,  -183,   -84,  -183,  -183,  -182,   -50,   138,
    -141,  -137
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     3,     8,    60,     9,    17,    53,    20,    21,
      36,    61,    98,    99,   172,   173,   100,    62,    85,   125,
      86,   140,   185,   186,   187,   188,   114,   115,   224,   117,
     118,   119,   296,   120,   153,   163,   223,   219,   220,   155,
     156,   157
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     121,    87,   102,   197,   199,   116,   196,   198,   200,   231,
      79,    23,    25,   229,    28,    93,   128,   174,    30,   252,
     281,   211,    18,   234,   304,   136,   138,   190,   121,   164,
      55,   203,   130,   161,   103,   282,   127,    32,   212,   239,
     274,     7,    44,    22,   204,   269,    31,   293,   171,   253,
     230,   165,    26,   232,    39,    80,   233,   248,   249,   154,
     158,    81,   129,   169,   257,   258,   259,   232,   271,   166,
     235,   305,   191,   262,    89,    90,    92,    33,    39,   104,
     121,    22,   121,    39,   240,    45,    39,   225,   270,   271,
     294,   271,   254,    81,   241,    27,    12,     4,    22,     6,
     221,   317,   202,   176,    69,   222,   181,   227,    29,    24,
      22,   244,   245,   247,   228,   122,   250,   226,   318,   121,
     121,    22,    38,    39,   255,   256,     5,   121,   121,   213,
      81,   121,   263,   264,   242,    22,    13,   243,    14,   184,
     143,   144,   182,   145,    70,   146,   147,   148,   149,   183,
     215,   150,   217,   134,   151,   123,   273,   179,   152,   251,
     192,   283,   285,   265,   266,   291,   267,   268,   214,    81,
     216,    76,   -57,   278,   279,     1,   278,    15,    59,   105,
     143,   144,   184,   145,   107,   146,   147,   148,   149,   237,
     166,   150,   -57,   135,   151,    71,    72,   180,   152,    77,
     193,    19,   306,   307,   309,   292,    16,    22,   106,    22,
     205,   121,   206,   108,   207,   208,   310,    22,    22,   302,
     209,   303,    41,    94,   182,    42,    95,    96,    54,    82,
      83,   121,   121,   121,   121,   121,   320,   321,   322,   323,
     324,   184,   184,   302,    91,    97,    34,    84,   311,   312,
     313,   314,    43,    46,   302,    47,   299,   101,    48,    49,
      50,   300,   301,    51,    94,    35,    52,    95,    96,    46,
     -77,    47,   -77,   162,    48,    49,    50,   -77,    10,    51,
      11,   109,    52,  -152,   137,   110,    97,   111,   112,  -152,
      84,    94,   246,   139,    95,    96,   -46,   284,   113,    94,
     286,   287,    95,    96,    94,   308,    37,    95,    96,   141,
    -152,   142,    94,    97,    56,    95,    96,   143,   144,    57,
     145,    97,   146,   147,   148,   149,    97,    58,   150,    40,
      39,   151,    73,    74,    97,   152,   218,   143,   144,    63,
     145,    65,   146,   147,   148,   149,   260,   261,   150,    64,
      75,   151,    78,   143,   194,   152,   195,    66,   146,   147,
     148,   149,    67,    68,   150,    88,   109,   151,   126,   139,
     110,   152,   111,   112,    46,    84,    47,   131,   132,    48,
      49,    50,   159,   113,    51,   133,   205,    52,   206,   167,
     207,   170,   171,   177,   210,   178,    84,   189,   201,   272,
     276,   280,   277,   -76,   236,   275,   288,   289,   290,   295,
     298,   315,   168,   316,   319,   124,   175,   238,   160,     0,
       0,   297
};

static const yytype_int16 yycheck[] =
{
      84,    62,    80,   144,   145,    84,   143,   144,   145,     1,
       1,    11,    12,     1,    14,    78,     1,     1,     1,   201,
       1,     1,    42,     1,     1,   103,   104,     1,   112,     1,
      31,     1,    95,   112,     1,    16,    23,     1,    18,     1,
     222,    10,     1,    30,    14,     1,    29,     1,    32,     1,
      38,    23,     1,    45,    45,    46,    48,   194,   195,   109,
     110,    61,    47,   126,   205,   206,   207,    45,    45,    41,
      48,    48,    46,   210,    75,    76,    77,    41,    45,    46,
     164,    30,   166,    45,    46,    44,    45,   166,    44,    45,
      44,    45,    44,    93,     1,    44,     1,     1,    30,     0,
      42,     1,   152,    23,     1,    47,     1,   168,    41,    41,
      30,   189,   190,   191,    23,     1,     1,   167,    18,   203,
     204,    30,    44,    45,   203,   204,    30,   211,   212,     1,
     130,   215,   211,   212,    41,    30,    41,    44,    43,   139,
      25,    26,    37,    28,    41,    30,    31,    32,    33,    44,
       1,    36,     1,     1,    39,    41,     1,     1,    43,    44,
       1,   239,   240,   213,   214,     1,   216,   217,    40,   169,
      21,     1,    21,   231,   232,     3,   234,     1,     1,     1,
      25,    26,   182,    28,     1,    30,    31,    32,    33,     1,
      41,    36,    41,    41,    39,    32,    33,    41,    43,    29,
      41,     9,   280,   281,   282,    41,    30,    30,    30,    30,
      24,   295,    26,    30,    28,    29,   295,    30,    30,   269,
      34,   271,    41,     8,    37,    44,    11,    12,     1,     4,
       5,   315,   316,   317,   318,   319,   315,   316,   317,   318,
     319,   241,   242,   293,     1,    30,    30,    22,   298,   299,
     300,   301,    41,    26,   304,    28,     1,     1,    31,    32,
      33,     6,     7,    36,     8,    37,    39,    11,    12,    26,
      40,    28,    42,    43,    31,    32,    33,    47,    41,    36,
      43,    13,    39,    15,     1,    17,    30,    19,    20,    21,
      22,     8,     1,    43,    11,    12,    46,     1,    30,     8,
     241,   242,    11,    12,     8,     1,     9,    11,    12,   106,
      42,   108,     8,    30,    30,    11,    12,    25,    26,    30,
      28,    30,    30,    31,    32,    33,    30,    29,    36,    44,
      45,    39,    32,    33,    30,    43,    44,    25,    26,    30,
      28,    30,    30,    31,    32,    33,   208,   209,    36,    41,
      49,    39,    11,    25,    26,    43,    28,    41,    30,    31,
      32,    33,    41,    41,    36,    29,    13,    39,    11,    43,
      17,    43,    19,    20,    26,    22,    28,    47,    41,    31,
      32,    33,    30,    30,    36,    41,    24,    39,    26,    40,
      28,    41,    32,    32,    35,    41,    22,    46,    43,    30,
      32,    16,    32,    40,    48,    41,    41,    41,    41,    15,
       6,    18,   124,    18,    18,    86,   129,   182,   112,    -1,
      -1,   256
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    51,    52,     1,    30,     0,    10,    53,    55,
      41,    43,     1,    41,    43,     1,    30,    56,    42,     9,
      58,    59,    30,    54,    41,    54,     1,    44,    54,    41,
       1,    29,     1,    41,    30,    37,    60,     9,    44,    45,
      44,    41,    44,    41,     1,    44,    26,    28,    31,    32,
      33,    36,    39,    57,     1,    57,    30,    30,    29,     1,
      54,    61,    67,    30,    41,    30,    41,    41,    41,     1,
      41,    32,    33,    32,    33,    49,     1,    29,    11,     1,
      46,    54,     4,     5,    22,    68,    70,    76,    29,    57,
      57,     1,    57,    61,     8,    11,    12,    30,    62,    63,
      66,     1,    62,     1,    46,     1,    30,     1,    30,    13,
      17,    19,    20,    30,    76,    77,    78,    79,    80,    81,
      83,    84,     1,    41,    55,    69,    11,    23,     1,    47,
      61,    47,    41,    41,     1,    41,    62,     1,    62,    43,
      71,    71,    71,    25,    26,    28,    30,    31,    32,    33,
      36,    39,    43,    84,    88,    89,    90,    91,    88,    30,
      77,    78,    43,    85,     1,    23,    41,    40,    60,    61,
      41,    32,    64,    65,     1,    64,    23,    32,    41,     1,
      41,     1,    37,    44,    54,    72,    73,    74,    75,    46,
       1,    46,     1,    41,    26,    28,    91,    90,    91,    90,
      91,    43,    88,     1,    14,    24,    26,    28,    29,    34,
      35,     1,    18,     1,    40,     1,    21,     1,    44,    87,
      88,    42,    47,    86,    78,    78,    88,    76,    23,     1,
      38,     1,    45,    48,     1,    48,    48,     1,    75,     1,
      46,     1,    41,    44,    62,    62,     1,    62,    91,    91,
       1,    44,    87,     1,    44,    78,    78,    90,    90,    90,
      89,    89,    91,    78,    78,    88,    88,    88,    88,     1,
      44,    45,    30,     1,    87,    41,    32,    32,    65,    65,
      16,     1,    16,    62,     1,    62,    73,    73,    41,    41,
      41,     1,    41,     1,    44,    15,    82,    82,     6,     1,
       6,     7,    88,    88,     1,    48,    62,    62,     1,    62,
      78,    88,    88,    88,    88,    18,    18,     1,    18,    18,
      78,    78,    78,    78,    78
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    52,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      62,    62,    62,    62,    63,    64,    64,    65,    66,    66,
      67,    67,    68,    69,    70,    70,    71,    71,    71,    72,
      72,    73,    73,    74,    75,    76,    77,    77,    78,    78,
      78,    78,    78,    78,    79,    80,    80,    80,    81,    82,
      82,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    55,    55,    56,    56,    56,    56,
      56,    60,    61,    61,    61,    61,    61,    61,    63,    63,
      63,    63,    63,    63,    64,    65,    67,    70,    70,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    74,    75,
      75,    75,    76,    77,    81,    83,    83,    83,    83,    83,
      80,    87,    86,    86,    91,    91,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     6,     5,     3,     5,     3,     1,     0,
       3,     5,     3,     2,     2,     1,     2,     2,     1,     1,
       1,     1,     0,     1,     7,     8,     0,     2,     5,     4,
       1,     1,     3,     1,     6,     3,     1,     3,     4,     1,
       0,     3,     2,     3,     6,     4,     0,     2,     3,     3,
       1,     1,     1,     2,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     0,     3,     1,     3,     4,     5,     0,
       2,     4,     4,     8,     8,     2,     3,     0,     2,     3,
       2,     3,     1,     3,     3,     1,     1,     2,     2,     3,
       3,     3,     1,     3,     1,     1,     2,     1,     1,     1,
       1,     4,     3,     2,     2,     6,     6,     6,     6,     6,
       3,     4,     5,     3,     3,     3,     5,     3,     5,     5,
       3,     2,     5,     5,     4,     4,     4,     4,     6,     6,
       6,     2,     3,     4,     3,     3,     3,     6,     6,     6,
       6,     4,     4,     2,     2,     2,     3,     3,     2,     3,
       3,     2,     3,     3,     5,     8,     8,     8,     4,     4,
       4,     3,     2,     3,     4,     3,     3
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
#line 85 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // prgram -> program_head program_body '.'
	    ProgramStruct* headnode = new ProgramStruct();
        headnode->append_child((yyvsp[-2].program_head_node));
        headnode->append_child((yyvsp[-1].program_body_node));

        Ast->set_root(headnode);
    }
#line 1423 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 3: /* program_head: PROGRAM ID '(' id_list ')' ';'  */
#line 94 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
                                              {
        // program_head -> PROGRAM ID '(' id_list ')' ';'
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.program_head_node)->append_child(leaf_node);
        (yyval.program_head_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.program_head_node)->set_rownum(line_count);
    }
#line 1436 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 4: /* program_head: PROGRAM ID '(' ')' ';'  */
#line 101 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
                                {
        // program_head -> PROGRAM ID '('  ')' ';'
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode((yyvsp[-3].token_info).value, LeafNode::LeafType::NAME);
        (yyval.program_head_node)->append_child(leaf_node);
        (yyval.program_head_node)->set_rownum(line_count);
    }
#line 1448 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 5: /* program_head: PROGRAM ID ';'  */
#line 107 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
                       {
        // program_head -> PROGRAM ID ';'
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode((yyvsp[-1].token_info).value, LeafNode::LeafType::NAME);
        (yyval.program_head_node)->append_child(leaf_node);
        (yyval.program_head_node)->set_rownum(line_count);
    }
#line 1460 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 6: /* program_body: const_declarations record_declarations var_declarations subprogram_declarations compound_statement  */
#line 115 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
                                                                                                                  {
        // program_body -> const_declarations type_declarations var_declarations subprogram_declarations compound_statement
        (yyval.program_body_node) = new ProgramBody();
        (yyval.program_body_node)->set_rownum(line_count);
        (yyval.program_body_node)->append_child((yyvsp[-4].const_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-3].record_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-2].var_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[-1].subprogram_declarations_node));
        (yyval.program_body_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 1475 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 7: /* id_list: id_list ',' ID  */
#line 126 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
                         { 
        // id_list -> id_list ',' ID
        // 插入idlist node以及叶子节点
        (yyval.idlist_node) = new IdList(IdList::GrammarType::MULTIPLE_ID);
        (yyval.idlist_node)->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::NAME);
        (yyval.idlist_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.idlist_node)->append_child(leaf_node);
    }
#line 1489 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 8: /* id_list: ID  */
#line 136 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // id_list -> ID
        (yyval.idlist_node) = new IdList(IdList::GrammarType::SINGLE_ID);
        (yyval.idlist_node)->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::NAME);
        (yyval.idlist_node)->append_child(leaf_node);
    }
#line 1501 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 9: /* const_declarations: %empty  */
#line 144 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
                    {
        // const_declarations -> ε
        (yyval.const_declarations_node) = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
        (yyval.const_declarations_node)->set_rownum(line_count);
    }
#line 1511 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 10: /* const_declarations: CONST const_declaration ';'  */
#line 150 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_declarations -> CONST const_declaration ';'
        (yyval.const_declarations_node) = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        (yyval.const_declarations_node)->set_rownum(line_count);
        (yyval.const_declarations_node)->append_child((yyvsp[-1].const_declaration_node));
    }
#line 1522 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 11: /* const_declaration: const_declaration ';' ID CONSTASSIGNOP const_value  */
#line 158 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_declaration -> const_declaration ';' ID '=' const_value
        (yyval.const_declaration_node) = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, (yyvsp[0].const_value_node)->type());
        (yyval.const_declaration_node)->set_rownum(line_count);
        (yyval.const_declaration_node)->append_child((yyvsp[-4].const_declaration_node));
        //初始化 id 叶子节点
        LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*(yyvsp[0].const_value_node), LeafNode::LeafType::VALUE);
        (yyval.const_declaration_node)->append_child(leaf_node);
        
    }
#line 1540 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 12: /* const_declaration: ID CONSTASSIGNOP const_value  */
#line 172 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_declaration -> ID '=' const_value
        (yyval.const_declaration_node) = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, (yyvsp[0].const_value_node)->type());
        //初始化 id 叶子节点
        (yyval.const_declaration_node)->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        //初始化 const_value 叶子节点
        leaf_node = new LeafNode(*(yyvsp[0].const_value_node), LeafNode::LeafType::VALUE);
        (yyval.const_declaration_node)->append_child(leaf_node);
    }
#line 1556 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 13: /* const_value: PLUS INT_NUM  */
#line 186 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_value -> + INT_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1565 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 14: /* const_value: UMINUS INT_NUM  */
#line 191 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_value -> - INT_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
        (yyval.const_value_node)->set_uminus();
    }
#line 1575 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 15: /* const_value: INT_NUM  */
#line 197 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_value -> INT_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1584 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 16: /* const_value: PLUS REAL_NUM  */
#line 202 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_value -> REAL_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1593 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 17: /* const_value: UMINUS REAL_NUM  */
#line 207 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_value -> REAL_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
        (yyval.const_value_node)->set_uminus();
    }
#line 1603 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 18: /* const_value: REAL_NUM  */
#line 213 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // const_value -> REAL_NUM
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1612 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 19: /* const_value: BOOL  */
#line 218 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_value -> BOOL
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1621 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 20: /* const_value: STRING_  */
#line 223 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_variable -> string
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1630 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 21: /* const_value: CHAR  */
#line 228 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // const_variable -> CHAR 
        (yyval.const_value_node) = new ConstValue((yyvsp[0].token_info).value);
    }
#line 1639 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 22: /* record_declarations: %empty  */
#line 234 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.record_declarations_node) = new RecordDeclarations(RecordDeclarations::GrammarType::EPSILON);
        (yyval.record_declarations_node)->set_rownum(line_count);
    }
#line 1648 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 23: /* record_declarations: record_declaration  */
#line 239 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // record_declarations -> ε | record_declaration
        (yyval.record_declarations_node) = new RecordDeclarations(RecordDeclarations::GrammarType::DECLARATION);
        (yyval.record_declarations_node)->set_rownum(line_count);
        (yyval.record_declarations_node)->append_child((yyvsp[0].record_declaration_node));
    }
#line 1659 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 24: /* record_declaration: TYPE ID CONSTASSIGNOP RECORD var_declaration END ';'  */
#line 247 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // record_declaration -> def-record | record_declaration def-record
        (yyval.record_declaration_node) = new RecordDeclaration(RecordDeclaration::GrammarType::SINGLE_DECLARATION);
        (yyval.record_declaration_node)->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode((yyvsp[-5].token_info).value, LeafNode::LeafType::NAME);
        (yyval.record_declaration_node)->append_child(leaf_node);
        (yyval.record_declaration_node)->append_child((yyvsp[-2].var_declaration_node));
    }
#line 1672 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 25: /* record_declaration: record_declaration TYPE ID CONSTASSIGNOP RECORD var_declaration END ';'  */
#line 256 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.record_declaration_node) = new RecordDeclaration(RecordDeclaration::GrammarType::MULTI_DECLARATION);
        (yyval.record_declaration_node)->set_rownum(line_count);
        (yyval.record_declaration_node)->append_child((yyvsp[-7].record_declaration_node));
        LeafNode* leaf_node = new LeafNode((yyvsp[-5].token_info).value, LeafNode::LeafType::NAME);
        (yyval.record_declaration_node)->append_child(leaf_node);
        (yyval.record_declaration_node)->append_child((yyvsp[-2].var_declaration_node));
    }
#line 1685 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 26: /* var_declarations: %empty  */
#line 266 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declarations -> ε
        (yyval.var_declarations_node) = new VarDeclarations(VarDeclarations::GrammarType::EPSILON);
        (yyval.var_declarations_node)->set_rownum(line_count);
    }
#line 1695 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 27: /* var_declarations: VAR var_declaration  */
#line 272 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declarations -> VAR var_declaration ';'
        (yyval.var_declarations_node) = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        (yyval.var_declarations_node)->set_rownum(line_count);
        (yyval.var_declarations_node)->append_child((yyvsp[0].var_declaration_node));
    }
#line 1706 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 28: /* var_declaration: var_declaration id_list ':' type ';'  */
#line 280 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declaration -> var_declaration ';' id_list ':' type
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        (yyval.var_declaration_node)->append_child((yyvsp[-4].var_declaration_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-3].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-1].type_node));
    }
#line 1719 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 29: /* var_declaration: id_list ':' type ';'  */
#line 289 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // var_declaration -> id_list ':' type
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        (yyval.var_declaration_node)->append_child((yyvsp[-3].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-1].type_node));
    }
#line 1731 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 30: /* type: ID  */
#line 298 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // type -> ID
        // 由于我们将integer等都设为保留字，都识别为ID（integer char boolean string real）
        (yyval.type_node) = new TypeNode(TypeNode::VarType::ID_TYPE, (yyvsp[0].token_info).value.get<string>());
        (yyval.type_node)->set_rownum(line_count);
    }
#line 1742 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 31: /* type: array_type  */
#line 305 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.type_node) = new TypeNode(TypeNode::VarType::ARRAY_TYPE, "array");
        (yyval.type_node)->set_rownum(line_count);
        (yyval.type_node)->append_child((yyvsp[0].array_node));
    }
#line 1752 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 32: /* type: RECORD var_declaration END  */
#line 311 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // recordtype -> record var_declaration end;
        (yyval.type_node) = new TypeNode(TypeNode::VarType::RECORD_TYPE, "record");
        (yyval.type_node)->set_rownum(line_count);
        (yyval.type_node)->append_child((yyvsp[-1].var_declaration_node));
    }
#line 1763 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 33: /* type: string_type  */
#line 318 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.type_node) = new TypeNode(TypeNode::VarType::STRING_TYPE, "string");
        (yyval.type_node)->set_rownum(line_count);
        (yyval.type_node)->append_child((yyvsp[0].string_node));
    }
#line 1773 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 34: /* array_type: ARRAY '[' periods ']' OF type  */
#line 325 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        (yyval.array_node) = new ArrayTypeNode();
        (yyval.array_node)->set_rownum(line_count);
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
#line 1800 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 35: /* periods: periods ',' period  */
#line 349 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // periods -> periods ',' period
        (yyval.periods_node) = new PeriodsNode(PeriodsNode::PeriodType::MULTI);
        (yyval.periods_node)->set_rownum(line_count);
        // 插入新的维度
        std::vector<ArrayType::Dimension> dim;
        dim = (yyvsp[-2].periods_node)->get_dm();
        ArrayType::Dimension nd((yyvsp[0].period_node)->get_lowb(), (yyvsp[0].period_node)->get_upb());
        dim.emplace_back(nd);
        (yyval.periods_node)->set_dm(dim);

        (yyval.periods_node)->append_child((yyvsp[-2].periods_node));
        (yyval.periods_node)->append_child((yyvsp[0].period_node));
    }
#line 1819 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 36: /* periods: period  */
#line 364 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // periods -> period
        (yyval.periods_node) = new PeriodsNode(PeriodsNode::PeriodType::SINGLE);
        (yyval.periods_node)->set_rownum(line_count);
        // 底层新建维度vector
        std::vector<ArrayType::Dimension> dim;
        ArrayType::Dimension nd((yyvsp[0].period_node)->get_lowb(), (yyvsp[0].period_node)->get_upb());
        dim.emplace_back(nd);
        (yyval.periods_node)->set_dm(dim);
        (yyval.periods_node)->append_child((yyvsp[0].period_node));
    }
#line 1835 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 37: /* period: INT_NUM SUBCATALOG INT_NUM  */
#line 377 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        (yyval.period_node) = new PeriodNode((yyvsp[-2].token_info).value.get<int>(), (yyvsp[0].token_info).value.get<int>());
        (yyval.period_node)->set_rownum(line_count);
        (yyval.period_node)->append_child(new LeafNode((yyvsp[-2].token_info).value.get<int>(), LeafNode::LeafType::VALUE));
        (yyval.period_node)->append_child(new LeafNode((yyvsp[0].token_info).value.get<int>(), LeafNode::LeafType::VALUE));
    }
#line 1847 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 38: /* string_type: STRING '[' INT_NUM ']'  */
#line 386 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        StringType* string_info = new StringType(StringType::GrammarType::LIMIT, (yyvsp[-1].token_info).value.get<int>());
        (yyval.string_node) = new StringTypeNode(string_info);
        (yyval.string_node)->set_rownum(line_count);
    }
#line 1857 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 39: /* string_type: STRING  */
#line 392 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        StringType* string_info = new StringType(StringType::GrammarType::NOLIMIT, 0);
        (yyval.string_node) = new StringTypeNode(string_info);
        (yyval.string_node)->set_rownum(line_count);
    }
#line 1867 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 40: /* subprogram_declarations: %empty  */
#line 399 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_declarations -> ε
        (yyval.subprogram_declarations_node) = new SubprogramDeclarations();
        (yyval.subprogram_declarations_node)->set_rownum(line_count);
    }
#line 1877 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 41: /* subprogram_declarations: subprogram_declarations subprogram_declaration ';'  */
#line 405 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_declarations -> subprogram_declarations subprogram_declaration ';'
        (yyval.subprogram_declarations_node) = new SubprogramDeclarations();
        (yyval.subprogram_declarations_node)->set_rownum(line_count);
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-2].subprogram_declarations_node));
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-1].subprogram_declaration_node));
    }
#line 1889 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 42: /* subprogram_declaration: subprogram_head subprogram_body  */
#line 414 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_declaration -> subprogram_head subprogram_body
        (yyval.subprogram_declaration_node) = new SubprogramDeclaration();
        (yyval.subprogram_declaration_node)->set_rownum(line_count);
        (yyval.subprogram_declaration_node)->append_child((yyvsp[-1].subprogram_head_node));
        (yyval.subprogram_declaration_node)->append_child((yyvsp[0].subprogram_body_node));
    }
#line 1901 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 43: /* subprogram_body: const_declarations var_declarations compound_statement  */
#line 422 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_body -> const_declarations var_declarations compound_statement
        (yyval.subprogram_body_node) = new SubprogramBody();
        (yyval.subprogram_body_node)->set_rownum(line_count);
        (yyval.subprogram_body_node)->append_child((yyvsp[-2].const_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[-1].var_declarations_node));
        (yyval.subprogram_body_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 1914 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 44: /* subprogram_head: FUNCTION ID formal_parameter ':' type ';'  */
#line 432 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_head -> FUNCTION ID formal_parameter ':' standrad_type ';'
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        (yyval.subprogram_head_node)->set_id((yyvsp[-4].token_info).value.get<string>());
        LeafNode *leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-3].formal_param_node));
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].type_node));
    }
#line 1929 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 45: /* subprogram_head: PROCEDURE ID formal_parameter ';'  */
#line 443 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // subprogram_head -> PROCEDURE ID formal_parameter ';'
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::PROC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.subprogram_head_node)->set_id((yyvsp[-2].token_info).value.get<string>());
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].formal_param_node));
    }
#line 1943 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 46: /* formal_parameter: %empty  */
#line 454 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // formal_parameter -> ε
        (yyval.formal_param_node) = new FormalParam();
        (yyval.formal_param_node)->set_rownum(line_count);
    }
#line 1953 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 47: /* formal_parameter: '(' ')'  */
#line 460 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.formal_param_node) = new FormalParam();
        (yyval.formal_param_node)->set_rownum(line_count);
    }
#line 1962 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 48: /* formal_parameter: '(' parameter_lists ')'  */
#line 465 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // formal_parameter -> '(' parameter_lists ')'
        (yyval.formal_param_node) = new FormalParam();
        (yyval.formal_param_node)->set_rownum(line_count);
        (yyval.formal_param_node)->append_child((yyvsp[-1].paramlists_node));
    }
#line 1973 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 49: /* parameter_lists: parameter_lists ';' parameter_list  */
#line 473 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // parameter_lists -> parameter_lists ';' parameter_list
        (yyval.paramlists_node) = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        (yyval.paramlists_node)->set_rownum(line_count);
        (yyval.paramlists_node)->append_child((yyvsp[-2].paramlists_node));
        (yyval.paramlists_node)->append_child((yyvsp[0].paramlist_node));
    }
#line 1985 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 50: /* parameter_lists: parameter_list  */
#line 481 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {  
        // parameter_lists -> parameter_list
        (yyval.paramlists_node) = new ParamLists(ParamLists::GrammarType::SINGLE_PARAM_LIST);
        (yyval.paramlists_node)->set_rownum(line_count);
        (yyval.paramlists_node)->append_child((yyvsp[0].paramlist_node));
    }
#line 1996 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 51: /* parameter_list: var_parameter  */
#line 489 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // parameter_list -> var_parameter
        (yyval.paramlist_node) = new ParamList(ParamList::ParamType::VarParam);
        (yyval.paramlist_node)->set_rownum(line_count);
        (yyval.paramlist_node)->append_child((yyvsp[0].var_param_node));
    }
#line 2007 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 52: /* parameter_list: value_parameter  */
#line 496 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // parameter_list -> value_parameter
        (yyval.paramlist_node) = new ParamList(ParamList::ParamType::ValueParam);
        (yyval.paramlist_node)->set_rownum(line_count);
        (yyval.paramlist_node)->append_child((yyvsp[0].value_param_node));
    }
#line 2018 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 53: /* var_parameter: VAR value_parameter  */
#line 504 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // var_parameter -> VAR value_parameter
        (yyval.var_param_node) = new VarParam();
        (yyval.var_param_node)->set_rownum(line_count);
        (yyval.var_param_node)->append_child((yyvsp[0].value_param_node));
    }
#line 2029 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 54: /* value_parameter: id_list ':' type  */
#line 512 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // value_parameter -> id_list ':' standrad_type
        (yyval.value_param_node) = new ValueParam();
        (yyval.value_param_node)->set_rownum(line_count);
        (yyval.value_param_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.value_param_node)->append_child((yyvsp[0].type_node));
    }
#line 2041 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 55: /* compound_statement: BEGIN_ statement_list END  */
#line 521 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // compound_statement -> Begin statement_list end
        (yyval.compound_statement_node) = new CompoundStatement();
        (yyval.compound_statement_node)->set_rownum(line_count);
        (yyval.compound_statement_node)->append_child((yyvsp[-1].statement_list_node));
    }
#line 2052 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 56: /* statement_list: statement_list ';' statement  */
#line 529 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement_list -> statement_list ';' statement
        (yyval.statement_list_node) = new StatementList();
        (yyval.statement_list_node)->set_rownum(line_count);
        (yyval.statement_list_node)->append_child((yyvsp[-2].statement_list_node));
        (yyval.statement_list_node)->append_child((yyvsp[0].statement_node));
    }
#line 2064 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 57: /* statement_list: statement  */
#line 537 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement_list -> statement
        (yyval.statement_list_node) = new StatementList();
        (yyval.statement_list_node)->set_rownum(line_count);
        (yyval.statement_list_node)->append_child((yyvsp[0].statement_node));
    }
#line 2075 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 58: /* statement: assignop_statement  */
#line 545 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        //statement -> AssignopStatement
        (yyval.statement_node) = new Statement(Statement::StatementType::ASSIGN_OP_STATEMENT);
        (yyval.statement_node)->set_rownum(line_count);
        (yyval.statement_node)->append_child((yyvsp[0].assignop_statement_node));
    }
#line 2086 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 59: /* statement: procedure_call  */
#line 552 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> call_procedure_statement
        (yyval.statement_node) = new Statement(Statement::StatementType::PROCEDURE_CALL);
        (yyval.statement_node)->set_rownum(line_count);
        (yyval.statement_node)->append_child((yyvsp[0].procedure_call_node));
    }
#line 2097 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 60: /* statement: compound_statement  */
#line 559 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> compound_statement
        (yyval.statement_node) = new Statement(Statement::StatementType::COMPOUND_STATEMENT);
        (yyval.statement_node)->set_rownum(line_count);
        (yyval.statement_node)->append_child((yyvsp[0].compound_statement_node));
    }
#line 2108 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 61: /* statement: ifstatement  */
#line 566 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // statement -> IF expression THEN statement else_part
        (yyval.statement_node) = new Statement(Statement::StatementType::IF_STATEMENT);
        (yyval.statement_node)->set_rownum(line_count);
        (yyval.statement_node)->append_child((yyvsp[0].ifstatement_node));
    }
#line 2119 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 62: /* statement: loopstatement  */
#line 573 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> CASE expression OF case_body END
        (yyval.statement_node) = new Statement(Statement::StatementType::LOOP_STATEMENT);
        (yyval.statement_node)->set_rownum(line_count);
        (yyval.statement_node)->append_child((yyvsp[0].loopstatement_node));
    }
#line 2130 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 63: /* statement: %empty  */
#line 580 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> ε
        (yyval.statement_node) = new Statement(Statement::StatementType::EPSILON);
        (yyval.statement_node)->set_rownum(line_count);
    }
#line 2140 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 64: /* assignop_statement: variable ASSIGNOP expression  */
#line 587 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // assignop_statement -> variable ASSIGNOP expression
        (yyval.assignop_statement_node) = new AssignopStatement(AssignopStatement::LeftType::VARIABLE);
        (yyval.assignop_statement_node)->set_rownum(line_count);
        (yyval.assignop_statement_node)->append_child((yyvsp[-2].variable_node));
        (yyval.assignop_statement_node)->append_child((yyvsp[0].expression_node));
    }
#line 2152 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 65: /* procedure_call: ID  */
#line 596 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // procedure_call -> id
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, (yyvsp[0].token_info).value.get<string>());
        (yyval.procedure_call_node)->set_rownum(line_count);
    }
#line 2162 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 66: /* procedure_call: ID '(' ')'  */
#line 602 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::NO_LIST, (yyvsp[-2].token_info).value.get<string>());
        (yyval.procedure_call_node)->set_rownum(line_count);
    }
#line 2171 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 67: /* procedure_call: ID '(' expression_list ')'  */
#line 607 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // procedure_call -> id ( expression_list )
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::EXP_LIST, (yyvsp[-3].token_info).value.get<string>());
        (yyval.procedure_call_node)->set_rownum(line_count);
        (yyval.procedure_call_node)->append_child((yyvsp[-1].expression_list_node));
    }
#line 2182 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 68: /* ifstatement: IF expression THEN statement else_part  */
#line 622 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // if_statement -> if expression then statement else_part
        (yyval.ifstatement_node) = new IfStatement();
        (yyval.ifstatement_node)->set_rownum(line_count);
        (yyval.ifstatement_node)->append_child((yyvsp[-3].expression_node));
        (yyval.ifstatement_node)->append_child((yyvsp[-1].statement_node));
        (yyval.ifstatement_node)->append_child((yyvsp[0].elsepart_node));
    }
#line 2195 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 69: /* else_part: %empty  */
#line 632 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // else_part -> ε | else statement
        (yyval.elsepart_node) = new ElsePart(ElsePart::ELSEType::EPSILON);
        (yyval.elsepart_node)->set_rownum(line_count);
    }
#line 2205 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 70: /* else_part: ELSE statement  */
#line 638 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // else_part -> else statement
        (yyval.elsepart_node) = new ElsePart(ElsePart::ELSEType::ELSE_STATEMENT);
        (yyval.elsepart_node)->set_rownum(line_count);
        (yyval.elsepart_node)->append_child((yyvsp[0].statement_node));
    }
#line 2216 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 71: /* loopstatement: WHILE expression DO statement  */
#line 646 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> WHILE expression DO statement
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::WHILE_);
        (yyval.loopstatement_node)->set_rownum(line_count);
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));

    }
#line 2229 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 72: /* loopstatement: REPEAT statement_list UNTIL expression  */
#line 655 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> repeat statement until expression
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::REPEAT_);
        (yyval.loopstatement_node)->set_rownum(line_count);
        (yyval.loopstatement_node)->append_child((yyvsp[-2].statement_list_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].expression_node));
    }
#line 2241 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 73: /* loopstatement: FOR ID ASSIGNOP expression DOWNTO expression DO statement  */
#line 663 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // statement -> FOR ID ASSIGNOP expression downto expression DO statement
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        (yyval.loopstatement_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-6].token_info).value, LeafNode::LeafType::NAME); 
        (yyval.loopstatement_node)->append_child(leaf_node);
        (yyval.loopstatement_node)->append_child((yyvsp[-4].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
    }
#line 2256 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 74: /* loopstatement: FOR ID ASSIGNOP expression TO expression DO statement  */
#line 674 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::FORUP);
        (yyval.loopstatement_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-6].token_info).value, LeafNode::LeafType::NAME); 
        (yyval.loopstatement_node)->append_child(leaf_node);
        (yyval.loopstatement_node)->append_child((yyvsp[-4].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
    }
#line 2270 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 75: /* variable: ID id_varparts  */
#line 701 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // variable -> ID id_varparts
        (yyval.variable_node) = new Variable();
        (yyval.variable_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-1].token_info).value, LeafNode::LeafType::NAME);
        // 变量的类型需要符号表来进行判断
        (yyval.variable_node)->append_child(leaf_node);
        (yyval.variable_node)->append_child((yyvsp[0].idvarparts_node));
    }
#line 2284 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 76: /* variable: ID '(' ')'  */
#line 711 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // variable -> ID id_varparts
        (yyval.variable_node) = new Variable();
        (yyval.variable_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        // 变量的类型需要符号表来进行判断
        (yyval.variable_node)->append_child(leaf_node);
    }
#line 2297 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 77: /* id_varparts: %empty  */
#line 721 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // id_varparts -> ε.
        (yyval.idvarparts_node) = new IDVarParts();
        (yyval.idvarparts_node)->set_rownum(line_count);
        std::vector<std::string> *name_list = new std::vector<std::string>;
        (yyval.idvarparts_node)->set_pointer(name_list);
    }
#line 2309 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 78: /* id_varparts: id_varparts id_varpart  */
#line 729 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // id_varparts -> id_varparts id_varpart.
        (yyval.idvarparts_node) = new IDVarParts();
        (yyval.idvarparts_node)->set_rownum(line_count);
        std::vector<std::string> *name_list = (yyvsp[-1].idvarparts_node)->get_pointer();
        name_list->emplace_back((yyvsp[0].idvarpart_node)->get_part_name());
        (yyval.idvarparts_node)->set_pointer(name_list);
        (yyval.idvarparts_node)->append_child((yyvsp[-1].idvarparts_node));
        (yyval.idvarparts_node)->append_child((yyvsp[0].idvarpart_node));
    }
#line 2324 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 79: /* id_varpart: '[' expression_list ']'  */
#line 741 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // id_varpart -> [expression_list].
        (yyval.idvarpart_node) = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        (yyval.idvarpart_node)->set_rownum(line_count);
        (yyval.idvarpart_node)->append_child((yyvsp[-1].expression_list_node));
    }
#line 2335 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 80: /* id_varpart: '.' ID  */
#line 748 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // id_varpart -> .id.
        (yyval.idvarpart_node) = new IDVarPart(IDVarPart::GrammarType::_ID);
        (yyval.idvarpart_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::NAME);
        (yyval.idvarpart_node)->set_part_name((yyvsp[0].token_info).value.get<string>());
        (yyval.idvarpart_node)->append_child(leaf_node);
    }
#line 2348 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 81: /* expression_list: expression_list ',' expression  */
#line 758 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression_list -> expression_list ',' expression
        
        std::vector<std::string> *type_list = (yyvsp[-2].expression_list_node)->get_types();
        type_list->emplace_back((yyvsp[0].expression_node)->GetExpType());
        (yyval.expression_list_node) = new ExpressionList(ExpressionList::ExpressionType::MULTIPLE, type_list);
        (yyval.expression_list_node)->append_child((yyvsp[-2].expression_list_node));
        (yyval.expression_list_node)->append_child((yyvsp[0].expression_node));
    }
#line 2362 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 82: /* expression_list: expression  */
#line 768 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression_list -> expression
        std::string type = (yyvsp[0].expression_node)->GetExpType();
        std::vector<std::string> *type_list = new std::vector<std::string>;
        type_list->emplace_back(type);
        (yyval.expression_list_node) = new ExpressionList(ExpressionList::ExpressionType::SINGLE, type_list);
        (yyval.expression_list_node)->append_child((yyvsp[0].expression_node));
    }
#line 2375 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 83: /* expression: simple_expression RELOP simple_expression  */
#line 778 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression -> simple_expression RELOP simple_expression.
        (yyval.expression_node) = new Expression(Expression::GrammarType::DOUBLE, (yyvsp[-1].token_info).value.get<string>(), "unknown");
        (yyval.expression_node)->set_rownum(line_count);
        (yyval.expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.expression_node)->append_child((yyvsp[0].simple_expression_node));
    }
#line 2387 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 84: /* expression: simple_expression CONSTASSIGNOP simple_expression  */
#line 786 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression -> simple_expression '=' simple_expression.
        (yyval.expression_node) = new Expression(Expression::GrammarType::DOUBLE, "=", "unknown");
        (yyval.expression_node)->set_rownum(line_count);
        (yyval.expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.expression_node)->append_child((yyvsp[0].simple_expression_node));
    }
#line 2399 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 85: /* expression: simple_expression  */
#line 794 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // expression -> simple_expression.
        (yyval.expression_node) = new Expression(Expression::GrammarType::SINGLE, " ", (yyvsp[0].simple_expression_node)->GetExpType());
        (yyval.expression_node)->set_rownum(line_count);
        (yyval.expression_node)->append_child((yyvsp[0].simple_expression_node));
    }
#line 2410 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 86: /* simple_expression: term  */
#line 802 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // simple_expression -> term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::SINGLE, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->set_rownum(line_count);
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2421 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 87: /* simple_expression: PLUS term  */
#line 809 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // simple_expression -> + term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->set_rownum(line_count);
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2432 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 88: /* simple_expression: UMINUS term  */
#line 816 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // simple_expression -> - term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, (yyvsp[0].term_node)->GetTerType());
        (yyval.simple_expression_node)->set_rownum(line_count);
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2443 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 89: /* simple_expression: simple_expression ADDOP term  */
#line 823 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // simple_expression -> simple_expression or term.、
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::OR_, "unknown");
        (yyval.simple_expression_node)->set_rownum(line_count);
        (yyval.simple_expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2455 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 90: /* simple_expression: simple_expression PLUS term  */
#line 831 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { 
        // simple_expression -> simple_expression + term.
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::PLUS_, "unknown");
        (yyval.simple_expression_node)->set_rownum(line_count);
        (yyval.simple_expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2467 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 91: /* simple_expression: simple_expression UMINUS term  */
#line 839 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.simple_expression_node) = new SimpleExpression(SimpleExpression::SymbolType::MINUS_, "unknown");
        (yyval.simple_expression_node)->set_rownum(line_count);
        (yyval.simple_expression_node)->append_child((yyvsp[-2].simple_expression_node));
        (yyval.simple_expression_node)->append_child((yyvsp[0].term_node));
    }
#line 2478 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 92: /* term: factor  */
#line 847 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // term -> factor.
        
        (yyval.term_node) = new Term(Term::SymbolType::SINGLE, (yyvsp[0].factor_node)->GetFacType());
        (yyval.term_node)->set_rownum(line_count);
        (yyval.term_node)->append_child((yyvsp[0].factor_node));
    }
#line 2490 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 93: /* term: term MULOP factor  */
#line 855 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {  
        // term -> term mulop factor. 
        (yyval.term_node) = new Term;
        (yyval.term_node)->set_rownum(line_count);
        std::string sym_type = (yyvsp[-1].token_info).value.get<string>();
        if(sym_type == "*"){
            (yyval.term_node)->SetSymType(Term::SymbolType::MULTIPLY);
            (yyval.term_node)->SetTerType("unknown");
        }
        if(sym_type == "/"){
            (yyval.term_node)->SetSymType(Term::SymbolType::DEVIDE);
            (yyval.term_node)->SetTerType("unknown");
        }
        if(sym_type == "mod"){
            (yyval.term_node)->SetSymType(Term::SymbolType::MOD);
            (yyval.term_node)->SetTerType("unknown");
        }
        if(sym_type == "and"){
            (yyval.term_node)->SetSymType(Term::SymbolType::AND);
            (yyval.term_node)->SetTerType("unknown");
        }
        if(sym_type == "div"){
            (yyval.term_node)->SetSymType(Term::SymbolType::DEVIDE);
            (yyval.term_node)->SetTerType("unknown");
        }
        (yyval.term_node)->append_child((yyvsp[-2].term_node));
        (yyval.term_node)->append_child((yyvsp[0].factor_node));
    }
#line 2523 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 94: /* factor: INT_NUM  */
#line 885 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> num
        (yyval.factor_node) = new Factor(Factor::GrammerType::NUM);
        (yyval.factor_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("integer");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2536 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 95: /* factor: REAL_NUM  */
#line 894 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> num
        (yyval.factor_node) = new Factor(Factor::GrammerType::NUM);
        (yyval.factor_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("real");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2549 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 96: /* factor: PLUS factor  */
#line 903 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> num
        (yyval.factor_node) = new Factor(Factor::GrammerType::UPLUS);
        (yyval.factor_node)->set_rownum(line_count);
        (yyval.factor_node)->SetFacType((yyvsp[0].factor_node)->GetFacType());
        (yyval.factor_node)->append_child((yyvsp[0].factor_node));
    }
#line 2561 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 97: /* factor: BOOL  */
#line 911 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> BOOL
        (yyval.factor_node) = new Factor(Factor::GrammerType::BOOL);
        (yyval.factor_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("boolean");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2574 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 98: /* factor: STRING_  */
#line 920 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
    // factor -> STRING
        //字符
        (yyval.factor_node) = new Factor(Factor::GrammerType::STR);
        (yyval.factor_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("string");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2588 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 99: /* factor: CHAR  */
#line 930 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> char
        (yyval.factor_node) = new Factor(Factor::GrammerType::CHAR_);
        (yyval.factor_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[0].token_info).value, LeafNode::LeafType::VALUE);
        (yyval.factor_node)->SetFacType("char");
        (yyval.factor_node)->append_child(leaf_node);
    }
#line 2601 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 100: /* factor: variable  */
#line 939 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> variable.
        (yyval.factor_node) = new Factor(Factor::GrammerType::VARIABLE);
        (yyval.factor_node)->set_rownum(line_count);
        (yyval.factor_node)->SetFacType("unknown");
        (yyval.factor_node)->append_child((yyvsp[0].variable_node));
    }
#line 2613 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 101: /* factor: ID '(' expression_list ')'  */
#line 947 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        (yyval.factor_node) = new Factor(Factor::GrammerType::ID_EXP_LIST);
        (yyval.factor_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-3].token_info).value, LeafNode::LeafType::NAME);
        // 类型需要靠符号表确认
        (yyval.factor_node)->SetFacType("unknown");
        (yyval.factor_node)->append_child(leaf_node);
        (yyval.factor_node)->append_child((yyvsp[-1].expression_list_node));
    }
#line 2627 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 102: /* factor: '(' expression ')'  */
#line 957 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {
        // factor -> (expression).
        (yyval.factor_node) = new Factor(Factor::GrammerType::EXP);
        (yyval.factor_node)->set_rownum(line_count);
        (yyval.factor_node)->SetFacType((yyvsp[-1].expression_node)->GetExpType());
        (yyval.factor_node)->append_child((yyvsp[-1].expression_node));
    }
#line 2639 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 103: /* factor: NOT factor  */
#line 965 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> not factor.
        // 类型检查
        (yyval.factor_node) = new Factor(Factor::GrammerType::NOT_);
        (yyval.factor_node)->set_rownum(line_count);
        (yyval.factor_node)->SetUminus();
        (yyval.factor_node)->SetFacType((yyvsp[0].factor_node)->GetFacType());
        (yyval.factor_node)->append_child((yyvsp[0].factor_node));
    }
#line 2653 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 104: /* factor: UMINUS factor  */
#line 975 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {   
        // factor -> not factor.
        // 类型检查
        (yyval.factor_node) = new Factor(Factor::GrammerType::UMINUS_);
        (yyval.factor_node)->set_rownum(line_count);
        (yyval.factor_node)->SetUminus();
        (yyval.factor_node)->SetFacType((yyvsp[0].factor_node)->GetFacType());
        (yyval.factor_node)->append_child((yyvsp[0].factor_node));
    }
#line 2667 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 105: /* program_head: PROGRAM error '(' id_list ')' ';'  */
#line 989 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少主程序名 
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode();
        (yyval.program_head_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.program_head_node)->append_child(leaf_node);
        (yyval.program_head_node)->set_rownum(line_count);
        yyerror("Grammar Error: missing program name", line_count);
    }
#line 2680 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 106: /* program_head: PROGRAM ID '(' id_list ')' error  */
#line 998 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少主程序名 
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode();
        (yyval.program_head_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.program_head_node)->append_child(leaf_node);
        (yyval.program_head_node)->set_rownum(line_count);
        yyerror("Grammar Error: missing semicolon", line_count);
    }
#line 2693 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 107: /* program_head: PROGRAM ID error id_list ')' ';'  */
#line 1007 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少左括号 
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.program_head_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.program_head_node)->append_child(leaf_node);
        (yyval.program_head_node)->set_rownum(line_count);
        yyerror("Grammar Error: missing a left bracket", line_count);
    }
#line 2706 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 108: /* program_head: PROGRAM ID '(' error ')' ';'  */
#line 1016 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR idlist识别失败 
        (yyval.program_head_node) = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program identifier list missing or imcomplete", line_count);
    }
#line 2716 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 109: /* program_head: PROGRAM ID '(' id_list error ';'  */
#line 1022 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少右括号 
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.program_head_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.program_head_node)->append_child(leaf_node);
        (yyval.program_head_node)->set_rownum(line_count);
        yyerror("Grammar Error: missing a right bracket", line_count);
    }
#line 2729 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 110: /* program_head: PROGRAM error ';'  */
#line 1031 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR program head 
        (yyval.program_head_node) = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program head imcomplete", line_count);
    }
#line 2739 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 111: /* program_head: PROGRAM ID error ';'  */
#line 1037 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR idlist缺失 
        (yyval.program_head_node) = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program identifier list missing or imcomplete", line_count);
    }
#line 2749 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 112: /* program_head: PROGRAM ID '(' error ';'  */
#line 1043 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR idlist缺失 
        (yyval.program_head_node) = new ProgramHead();
        error_flag = 1;
        yyerror("Grammar Error: program identifier list missing or imcomplete", line_count);
    }
#line 2759 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 113: /* program_head: PROGRAM ID error  */
#line 1049 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR idlist缺失 
        (yyval.program_head_node) = new ProgramHead();
        LeafNode* leaf_node = new LeafNode((yyvsp[-1].token_info).value, LeafNode::LeafType::NAME);
        (yyval.program_head_node)->append_child(leaf_node);
        yyerror("Grammar Error: missing a semicolon", line_count - 1);
    }
#line 2770 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 114: /* const_declarations: CONST error ';'  */
#line 1057 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 常量定义出现错误 
        (yyval.const_declarations_node) = new ConstDeclarations(ConstDeclarations::GrammarType::EPSILON);
        (yyval.const_declarations_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: fatal error in const declarations", line_count);
    }
#line 2781 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 115: /* const_declarations: CONST const_declaration error  */
#line 1064 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.const_declarations_node) = new ConstDeclarations(ConstDeclarations::GrammarType::DECLARATION); 
        (yyval.const_declarations_node)->set_rownum(line_count);
        (yyval.const_declarations_node)->append_child((yyvsp[-1].const_declaration_node));
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
#line 2792 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 116: /* const_declaration: const_declaration ';' ID CONSTASSIGNOP error  */
#line 1072 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //常数初始化右值缺失 
        error_flag = 1;
        yyerror("Grammar Error: constant definition missing initial r-value", line_count);
    }
#line 2801 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 117: /* const_declaration: ID CONSTASSIGNOP error  */
#line 1077 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //常数初始化右值缺失 
        error_flag = 1;
        yyerror("Grammar Error: constant definition missing initial r-value", line_count);
    }
#line 2810 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 118: /* const_declaration: const_declaration error ID '=' const_value  */
#line 1082 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.const_declaration_node) = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, (yyvsp[0].const_value_node)->type());
        (yyval.const_declaration_node)->set_rownum(line_count);
        (yyval.const_declaration_node)->append_child((yyvsp[-4].const_declaration_node));
        LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        leaf_node = new LeafNode(*(yyvsp[0].const_value_node), LeafNode::LeafType::VALUE);
        (yyval.const_declaration_node)->append_child(leaf_node);
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
#line 2825 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 119: /* const_declaration: const_declaration ';' ID error const_value  */
#line 1093 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号） 
        (yyval.const_declaration_node) = new ConstDeclaration(ConstDeclaration::GrammarType::MULTIPLE_ID, (yyvsp[0].const_value_node)->type());
        (yyval.const_declaration_node)->set_rownum(line_count);
        (yyval.const_declaration_node)->append_child((yyvsp[-4].const_declaration_node));
        LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        leaf_node = new LeafNode(*(yyvsp[0].const_value_node), LeafNode::LeafType::VALUE);
        (yyval.const_declaration_node)->append_child(leaf_node);
        yyerror("Grammar Error: missing a equal sign",line_count);
    }
#line 2840 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 120: /* const_declaration: ID error const_value  */
#line 1104 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少等号（常量的初始化用的是等号，而不是赋值号） 
        (yyval.const_declaration_node) = new ConstDeclaration(ConstDeclaration::GrammarType::SINGLE_ID, (yyvsp[0].const_value_node)->type());
        (yyval.const_declaration_node)->set_rownum(line_count);
        LeafNode* leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.const_declaration_node)->append_child(leaf_node);
        leaf_node = new LeafNode(*(yyvsp[0].const_value_node), LeafNode::LeafType::VALUE);
        (yyval.const_declaration_node)->append_child(leaf_node);
        yyerror("Grammar Error: missing a equal sign", line_count);
    }
#line 2854 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 121: /* var_declarations: VAR error  */
#line 1115 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 变量定义出现错误 
        (yyval.var_declarations_node) = new VarDeclarations(VarDeclarations::GrammarType::DECLARATION);
        (yyval.var_declarations_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: fatal error in variant declarations", line_count);
    }
#line 2865 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 122: /* var_declaration: var_declaration id_list ':' type error  */
#line 1123 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        (yyval.var_declaration_node)->append_child((yyvsp[-4].var_declaration_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-3].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-1].type_node));
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
#line 2878 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 123: /* var_declaration: var_declaration id_list error type ';'  */
#line 1132 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少冒号 
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        (yyval.var_declaration_node)->append_child((yyvsp[-4].var_declaration_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-3].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-1].type_node));
        yyerror("Grammar Error: missing a colon", line_count);
    }
#line 2891 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 124: /* var_declaration: var_declaration id_list ':' error  */
#line 1141 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR type识别失败 
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::MULTIPLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing a type", line_count);
    }
#line 2902 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 125: /* var_declaration: id_list ':' error ';'  */
#line 1148 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR type识别失败 
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        (yyval.var_declaration_node)->append_child((yyvsp[-3].idlist_node));
        error_flag = 1;
        yyerror("missing a type", line_count);
    }
#line 2914 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 126: /* var_declaration: id_list error type ';'  */
#line 1156 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少冒号 
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        (yyval.var_declaration_node)->append_child((yyvsp[-3].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-1].type_node));
        yyerror("Grammar Error: missing a colon", line_count);
    }
#line 2926 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 127: /* var_declaration: id_list ':' type error  */
#line 1164 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.var_declaration_node) = new VarDeclaration(VarDeclaration::GrammarType::SINGLE_DECL);
        (yyval.var_declaration_node)->set_rownum(line_count);
        (yyval.var_declaration_node)->append_child((yyvsp[-3].idlist_node));
        (yyval.var_declaration_node)->append_child((yyvsp[-1].type_node));
        yyerror("Grammar Error: missing a semicolon", line_count - 1);
    }
#line 2938 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 128: /* array_type: ARRAY error periods ']' OF type  */
#line 1175 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少左中括号 
        (yyval.array_node) = new ArrayTypeNode();
        (yyval.array_node)->set_rownum(line_count);
        if((yyvsp[0].type_node)->GetVarType() == TypeNode::VarType::ID_TYPE){
            (yyval.array_node) -> set_type((yyvsp[0].type_node)->get_type_name());
        }
        ArrayType* at = new ArrayType();
        at->SetDimension((yyvsp[-3].periods_node)->get_dm());
        (yyval.array_node)->set_info(at);
        (yyval.array_node)->append_child((yyvsp[-3].periods_node));
        (yyval.array_node)->append_child((yyvsp[0].type_node));
        yyerror("Grammar Error: missing a left square bracket", line_count);
    }
#line 2956 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 129: /* array_type: ARRAY '[' periods ']' error type  */
#line 1189 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少OF关键字 
        (yyval.array_node) = new ArrayTypeNode();
        (yyval.array_node)->set_rownum(line_count);
        if((yyvsp[0].type_node)->GetVarType() == TypeNode::VarType::ID_TYPE){
            (yyval.array_node) -> set_type((yyvsp[0].type_node)->get_type_name());
        }
        ArrayType* at = new ArrayType();
        at->SetDimension((yyvsp[-3].periods_node)->get_dm());
        (yyval.array_node)->set_info(at);
        (yyval.array_node)->append_child((yyvsp[-3].periods_node));
        (yyval.array_node)->append_child((yyvsp[0].type_node));
        yyerror("Grammar Error: missing keyword \"OF\" ", line_count);
    }
#line 2974 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 130: /* array_type: ARRAY '[' periods ']' OF error  */
#line 1203 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 数组元素类型识别失败 
        (yyval.array_node) = new ArrayTypeNode();
        error_flag = 1;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
#line 2984 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 131: /* array_type: ARRAY error  */
#line 1209 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的数组类型 
        (yyval.array_node) = new ArrayTypeNode();
        error_flag = 1;
        yyerror("Grammar Error: incomplete array type", line_count);
    }
#line 2994 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 132: /* array_type: ARRAY '[' error  */
#line 1215 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的数组类型 
        (yyval.array_node) = new ArrayTypeNode();
        (yyval.array_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete array type", line_count);
    }
#line 3005 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 133: /* array_type: ARRAY '[' periods error  */
#line 1222 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的数组类型 
        (yyval.array_node) = new ArrayTypeNode();
        (yyval.array_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete array type",line_count);
    }
#line 3016 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 134: /* periods: periods error period  */
#line 1230 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少逗号 
        (yyval.periods_node) = new PeriodsNode(PeriodsNode::PeriodType::MULTI);
        (yyval.periods_node)->set_rownum(line_count);
        std::vector<ArrayType::Dimension> dim;
        dim = (yyvsp[-2].periods_node)->get_dm();
        ArrayType::Dimension nd((yyvsp[0].period_node)->get_lowb(), (yyvsp[0].period_node)->get_upb());
        dim.emplace_back(nd);
        (yyval.periods_node)->set_dm(dim);
        (yyval.periods_node)->append_child((yyvsp[-2].periods_node));
        (yyval.periods_node)->append_child((yyvsp[0].period_node));
        yyerror("Grammar Error: missing a comma ", line_count);
    }
#line 3033 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 135: /* period: INT_NUM error INT_NUM  */
#line 1244 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    {     
        // period -> INT_NUM SUBCATALOG INT_NUMe
        (yyval.period_node) = new PeriodNode((yyvsp[-2].token_info).value.get<int>(), (yyvsp[0].token_info).value.get<int>());
        (yyval.period_node)->set_rownum(line_count);
        (yyval.period_node)->append_child(new LeafNode((yyvsp[-2].token_info).value.get<int>(), LeafNode::LeafType::VALUE));
        (yyval.period_node)->append_child(new LeafNode((yyvsp[0].token_info).value.get<int>(), LeafNode::LeafType::VALUE));
        yyerror("Grammar Error: missing range dot .. ", line_count);
    }
#line 3046 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 136: /* subprogram_declarations: subprogram_declarations subprogram_declaration error  */
#line 1254 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.subprogram_declarations_node) = new SubprogramDeclarations();
        (yyval.subprogram_declarations_node)->set_rownum(line_count);
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-2].subprogram_declarations_node));
        (yyval.subprogram_declarations_node)->append_child((yyvsp[-1].subprogram_declaration_node));
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
#line 3058 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 137: /* subprogram_head: FUNCTION ID formal_parameter ':' type error  */
#line 1263 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        (yyval.subprogram_head_node)->set_id((yyvsp[-4].token_info).value.get<string>());
        LeafNode *leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-3].formal_param_node));
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].type_node));
         yyerror("Grammar Error: missing semicolon", line_count);
    }
#line 3073 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 138: /* subprogram_head: FUNCTION error formal_parameter ':' type ';'  */
#line 1274 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 函数名缺失 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing function name", line_count);
    }
#line 3084 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 139: /* subprogram_head: FUNCTION ID formal_parameter error type ';'  */
#line 1281 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少冒号 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        (yyval.subprogram_head_node)->set_id((yyvsp[-4].token_info).value.get<string>());
        LeafNode *leaf_node = new LeafNode((yyvsp[-4].token_info).value, LeafNode::LeafType::NAME);
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-3].formal_param_node));
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].type_node));
        yyerror("Grammar Error: missing a colon", line_count);
    }
#line 3099 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 140: /* subprogram_head: FUNCTION ID formal_parameter ':' error ';'  */
#line 1292 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少基本类型关键字 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
#line 3110 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 141: /* subprogram_head: FUNCTION ID formal_parameter error  */
#line 1299 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少基本类型关键字 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        error_flag =1 ;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
#line 3121 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 142: /* subprogram_head: PROCEDURE ID formal_parameter error  */
#line 1306 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        (yyval.subprogram_head_node)->set_id((yyvsp[-2].token_info).value.get<string>());
        LeafNode *leaf_node = new LeafNode((yyvsp[-2].token_info).value, LeafNode::LeafType::NAME);
        (yyval.subprogram_head_node)->append_child(leaf_node);
        (yyval.subprogram_head_node)->append_child((yyvsp[-1].formal_param_node));
        yyerror("Grammar Error: missing a semicolon", line_count);
    }
#line 3135 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 143: /* subprogram_head: FUNCTION error  */
#line 1316 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的函数头 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::FUNC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete function head", line_count);
    }
#line 3146 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 144: /* subprogram_head: PROCEDURE error  */
#line 1323 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的过程头 
        (yyval.subprogram_head_node) = new SubprogramHead(SubprogramHead::SubprogramType::PROC);
        (yyval.subprogram_head_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete procedure head", line_count);
    }
#line 3157 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 145: /* formal_parameter: '(' error  */
#line 1331 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的形参列表
        (yyval.formal_param_node) = new FormalParam();
        (yyval.formal_param_node)->set_rownum(line_count);
        yyerror("Grammar Error: incomplete formal parameter list", line_count);
    }
#line 3167 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 146: /* formal_parameter: '(' parameter_lists error  */
#line 1337 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 右括号缺失
        (yyval.formal_param_node) = new FormalParam();
        (yyval.formal_param_node)->set_rownum(line_count);
        (yyval.formal_param_node)->append_child((yyvsp[-1].paramlists_node));
        yyerror("Grammar Error: missing a right bracket", line_count);
    }
#line 3178 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 147: /* parameter_lists: parameter_lists error parameter_list  */
#line 1345 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
        (yyval.paramlists_node) = new ParamLists(ParamLists::GrammarType::MULTIPLE_PARAM_LIST);
        (yyval.paramlists_node)->set_rownum(line_count);
        (yyval.paramlists_node)->append_child((yyvsp[-2].paramlists_node));
        (yyval.paramlists_node)->append_child((yyvsp[0].paramlist_node));
		yyerror("Grammar Error: missing a semicolon", line_count);
	}
#line 3190 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 148: /* var_parameter: VAR error  */
#line 1354 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的引用参数列表 
        (yyval.var_param_node) = new VarParam();
        (yyval.var_param_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete refereced parameter list", line_count);
	}
#line 3201 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 149: /* value_parameter: id_list error type  */
#line 1362 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少分号 
       (yyval.value_param_node) = new ValueParam();
        (yyval.value_param_node)->set_rownum(line_count);
        (yyval.value_param_node)->append_child((yyvsp[-2].idlist_node));
        (yyval.value_param_node)->append_child((yyvsp[0].type_node));
        yyerror("Grammar Error: missing a colon", line_count);
    }
#line 3213 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 150: /* value_parameter: id_list ':' error  */
#line 1370 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少基本类型关键字 
        (yyval.value_param_node) = new ValueParam();
        (yyval.value_param_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
#line 3224 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 151: /* value_parameter: id_list error  */
#line 1377 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少基本类型关键字 
        (yyval.value_param_node) = new ValueParam();
        error_flag = 1;
        (yyval.value_param_node)->set_rownum(line_count);
        yyerror("Grammar Error: missing a base type keyword", line_count);
    }
#line 3235 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 152: /* compound_statement: BEGIN_ statement_list error  */
#line 1384 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少END关键字  
        (yyval.compound_statement_node) = new CompoundStatement();
        (yyval.compound_statement_node)->set_rownum(line_count);
        (yyval.compound_statement_node)->append_child((yyvsp[-1].statement_list_node));
        yyerror("Grammar Error: missing keyword \"end\"", line_count);
	}
#line 3246 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 153: /* statement_list: statement_list error statement  */
#line 1392 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺失分号 这里引发了3个规约规约冲突  
        (yyval.statement_list_node) = new StatementList();
        (yyval.statement_list_node)->set_rownum(line_count);
        (yyval.statement_list_node)->append_child((yyvsp[-2].statement_list_node));
        (yyval.statement_list_node)->append_child((yyvsp[0].statement_node));
        yyerror("Grammar Error: missing a semicolon  ", line_count);
    }
#line 3258 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 154: /* ifstatement: IF expression error statement else_part  */
#line 1401 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少then关键字  
        (yyval.ifstatement_node) = new IfStatement();
        (yyval.ifstatement_node)->set_rownum(line_count);
        (yyval.ifstatement_node)->append_child((yyvsp[-3].expression_node));
        (yyval.ifstatement_node)->append_child((yyvsp[-1].statement_node));
        (yyval.ifstatement_node)->append_child((yyvsp[0].elsepart_node));
        yyerror("Grammar Error: missing keyword \"then\"", line_count);
	}
#line 3271 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 155: /* loopstatement: FOR ID error expression TO expression DO statement  */
#line 1411 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少赋值号  
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        (yyval.loopstatement_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-6].token_info).value, LeafNode::LeafType::NAME); 
        (yyval.loopstatement_node)->append_child(leaf_node);
        (yyval.loopstatement_node)->append_child((yyvsp[-4].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
        yyerror("Grammar Error: missing assignop \":=\"", line_count);
    }
#line 3286 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 156: /* loopstatement: FOR ID ASSIGNOP expression error expression DO statement  */
#line 1422 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少关键字to  
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        (yyval.loopstatement_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-6].token_info).value, LeafNode::LeafType::NAME); 
        (yyval.loopstatement_node)->append_child(leaf_node);
        (yyval.loopstatement_node)->append_child((yyvsp[-4].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
        yyerror("Grammar Error: missing keywrod \"to\"", line_count);
    }
#line 3301 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 157: /* loopstatement: FOR ID ASSIGNOP expression TO expression error statement  */
#line 1433 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少关键字do  
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::FORDOWN);
        (yyval.loopstatement_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-6].token_info).value, LeafNode::LeafType::NAME); 
        (yyval.loopstatement_node)->append_child(leaf_node);
        (yyval.loopstatement_node)->append_child((yyvsp[-4].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
        yyerror("Grammar Error: missing keywrod \"do\"", line_count);
    }
#line 3316 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 158: /* loopstatement: WHILE expression error statement  */
#line 1444 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少关键字do  
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::WHILE_);
        (yyval.loopstatement_node)->set_rownum(line_count);
        (yyval.loopstatement_node)->append_child((yyvsp[-2].expression_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].statement_node));
        yyerror("Grammar Error: missing keywrod \"do\"", line_count);
    }
#line 3328 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 159: /* loopstatement: REPEAT statement error expression  */
#line 1452 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少关键字until  
        (yyval.loopstatement_node) = new LoopStatement(LoopStatement::LoopType::REPEAT_);
        (yyval.loopstatement_node)->set_rownum(line_count);
        (yyval.loopstatement_node)->append_child((yyvsp[-2].statement_node));
        (yyval.loopstatement_node)->append_child((yyvsp[0].expression_node));
        yyerror("Grammar Error: missing keywrod \"until\"", line_count);
	}
#line 3340 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 160: /* procedure_call: ID '(' expression_list error  */
#line 1461 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少右括号  
        (yyval.procedure_call_node) = new ProcedureCall(ProcedureCall::ProcedureType::EXP_LIST, (yyvsp[-3].token_info).value.get<string>());
        (yyval.procedure_call_node)->set_rownum(line_count);
        (yyval.procedure_call_node)->append_child((yyvsp[-1].expression_list_node));
        yyerror("Grammar Error: missing a right bracket", line_count);
    }
#line 3351 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 161: /* expression_list: expression_list error expression  */
#line 1469 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少逗号 这里引发了一个移进规约冲突 
        std::vector<std::string> *type_list = (yyvsp[-2].expression_list_node)->get_types();
        type_list->emplace_back((yyvsp[0].expression_node)->GetExpType());
        (yyval.expression_list_node) = new ExpressionList(ExpressionList::ExpressionType::MULTIPLE, type_list);
        (yyval.expression_list_node)->append_child((yyvsp[-2].expression_list_node));
        (yyval.expression_list_node)->append_child((yyvsp[0].expression_node));
        yyerror("Grammar Error: missing a comma", line_count);
    }
#line 3364 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 162: /* id_varpart: '[' error  */
#line 1479 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 不完整的数组下标列表 
        (yyval.idvarpart_node) = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        (yyval.idvarpart_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: incomplete expression list of array subindex", line_count);
    }
#line 3375 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 163: /* id_varpart: '[' expression_list error  */
#line 1486 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺失右中括号 
		(yyval.idvarpart_node) = new IDVarPart(IDVarPart::GrammarType::EXP_LIST);
        (yyval.idvarpart_node)->set_rownum(line_count);
        (yyval.idvarpart_node)->append_child((yyvsp[-1].expression_list_node));
        yyerror("Grammar Error: missing a right square bracket", line_count);
	}
#line 3386 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 164: /* factor: ID '(' expression_list error  */
#line 1494 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少右括号 这里引发了一个移进规约冲突
        (yyval.factor_node) = new Factor(Factor::GrammerType::ID_EXP_LIST);
        (yyval.factor_node)->set_rownum(line_count);
        LeafNode *leaf_node = new LeafNode((yyvsp[-3].token_info).value, LeafNode::LeafType::NAME);
        // 类型需要靠符号表确认
        (yyval.factor_node)->SetFacType("unknown");
        (yyval.factor_node)->append_child(leaf_node);
        (yyval.factor_node)->append_child((yyvsp[-1].expression_list_node));
        yyerror("Grammar Error: missing a right bracket", line_count);
	}
#line 3401 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 165: /* factor: ID '(' error  */
#line 1505 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 函数调用的表达式列表缺失
        (yyval.factor_node) = new Factor(Factor::GrammerType::EXP);
        (yyval.factor_node)->set_rownum(line_count);
        error_flag = 1;
        yyerror("Grammar Error: missing actual parameter list of function call", line_count);
	}
#line 3412 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;

  case 166: /* factor: '(' expression error  */
#line 1512 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"
    { //ERROR 缺少右括号
        (yyval.factor_node) = new Factor(Factor::GrammerType::EXP);
        (yyval.factor_node)->set_rownum(line_count);
        (yyval.factor_node)->SetFacType((yyvsp[-1].expression_node)->GetExpType());
        (yyval.factor_node)->append_child((yyvsp[-1].expression_node));
        yyerror("Grammar Error: missing a right bracket", line_count);
    }
#line 3424 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"
    break;


#line 3428 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.tab.cpp"

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

#line 1521 "/home/lm/shared_compiler/PASCAL-S-compiler/build/../scripts/parser.y"

 

void yyerror(ast::AST* Ast,const char *msg){
    if(strcmp(msg,"syntax error")!=0)   // 当非debug模式且传入的是默认报错时不输出 
        fprintf(stderr,"%d,%ld:\033[01;31m \terror\033[0m : %s\n", line_count,cur_line_info.size(),msg);   
    
}

void yyerror(const char *s, int line){
	string errorInformation;//定义错误信息
	errorInformation += string(s);//添加错误信息
	cout << errorInformation << " at line " << line << endl;
}

int yywrap(){
    return 1;
} 
