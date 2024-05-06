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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    PROGRAM = 258,                 /* PROGRAM  */
    FUNCTION = 259,                /* FUNCTION  */
    PROCEDURE = 260,               /* PROCEDURE  */
    TO = 261,                      /* TO  */
    DOWNTO = 262,                  /* DOWNTO  */
    ARRAY = 263,                   /* ARRAY  */
    TYPE = 264,                    /* TYPE  */
    CONST = 265,                   /* CONST  */
    RECORD = 266,                  /* RECORD  */
    STRING = 267,                  /* STRING  */
    IF = 268,                      /* IF  */
    THEN = 269,                    /* THEN  */
    ELSE = 270,                    /* ELSE  */
    OF = 271,                      /* OF  */
    WHILE = 272,                   /* WHILE  */
    DO = 273,                      /* DO  */
    FOR = 274,                     /* FOR  */
    REPEAT = 275,                  /* REPEAT  */
    UNTIL = 276,                   /* UNTIL  */
    BEGIN_ = 277,                  /* BEGIN_  */
    END = 278,                     /* END  */
    ADDOP = 279,                   /* ADDOP  */
    NOT = 280,                     /* NOT  */
    PLUS = 281,                    /* PLUS  */
    CASE = 282,                    /* CASE  */
    UMINUS = 283,                  /* UMINUS  */
    CONSTASSIGNOP = 284,           /* CONSTASSIGNOP  */
    ID = 285,                      /* ID  */
    CHAR = 286,                    /* CHAR  */
    INT_NUM = 287,                 /* INT_NUM  */
    REAL_NUM = 288,                /* REAL_NUM  */
    RELOP = 289,                   /* RELOP  */
    MULOP = 290,                   /* MULOP  */
    STRING_ = 291,                 /* STRING_  */
    VAR = 292,                     /* VAR  */
    SUBCATALOG = 293,              /* SUBCATALOG  */
    ASSIGNOP = 294                 /* ASSIGNOP  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define PROGRAM 258
#define FUNCTION 259
#define PROCEDURE 260
#define TO 261
#define DOWNTO 262
#define ARRAY 263
#define TYPE 264
#define CONST 265
#define RECORD 266
#define STRING 267
#define IF 268
#define THEN 269
#define ELSE 270
#define OF 271
#define WHILE 272
#define DO 273
#define FOR 274
#define REPEAT 275
#define UNTIL 276
#define BEGIN_ 277
#define END 278
#define ADDOP 279
#define NOT 280
#define PLUS 281
#define CASE 282
#define UMINUS 283
#define CONSTASSIGNOP 284
#define ID 285
#define CHAR 286
#define INT_NUM 287
#define REAL_NUM 288
#define RELOP 289
#define MULOP 290
#define STRING_ 291
#define VAR 292
#define SUBCATALOG 293
#define ASSIGNOP 294

/* Value type.  */


extern YYSTYPE yylval;


int yyparse (ast::AST *Ast);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
