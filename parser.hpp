/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DECLARE = 258,
     IN = 259,
     END = 260,
     ASSIGN = 261,
     IF = 262,
     THEN = 263,
     ENDIF = 264,
     ELSE = 265,
     WHILE = 266,
     DO = 267,
     ENDWHILE = 268,
     GET = 269,
     PUT = 270,
     PLUS = 271,
     MINUS = 272,
     TIMES = 273,
     DIV = 274,
     MOD = 275,
     EQ = 276,
     DIFF = 277,
     LE = 278,
     GE = 279,
     LEQ = 280,
     GEQ = 281,
     num = 282,
     identifier = 283,
     SEM = 284
   };
#endif
/* Tokens.  */
#define DECLARE 258
#define IN 259
#define END 260
#define ASSIGN 261
#define IF 262
#define THEN 263
#define ENDIF 264
#define ELSE 265
#define WHILE 266
#define DO 267
#define ENDWHILE 268
#define GET 269
#define PUT 270
#define PLUS 271
#define MINUS 272
#define TIMES 273
#define DIV 274
#define MOD 275
#define EQ 276
#define DIFF 277
#define LE 278
#define GE 279
#define LEQ 280
#define GEQ 281
#define num 282
#define identifier 283
#define SEM 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 11 "src/parser.y"
{
	string num;
	string identifier;
}
/* Line 1529 of yacc.c.  */
#line 112 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

