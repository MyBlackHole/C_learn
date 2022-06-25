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
#line 1 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
 /* -*-text-*- */

#define YYDEBUG 1
/*-------------------------------------------------------------------------
 * 
 * gram.y--
 *    POSTGRES SQL YACC rules/actions
 * 
 * Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *    $Header: /usr/local/cvsroot/postgres95/src/backend/parser/gram.y,v 1.2.2.1 1996/08/24 20:54:06 scrappy Exp $
 *
 * HISTORY
 *    AUTHOR		DATE		MAJOR EVENT
 *    Andrew Yu		Sept, 1994	POSTQUEL to SQL conversion
 *    Andrew Yu		Oct, 1994	lispy code conversion
 *
 * NOTES
 *    CAPITALS are used to represent terminal symbols.
 *    non-capitals are used to represent non-terminals.
 *
 *    if you use list, make sure the datum is a node so that the printing
 *    routines work
 *
 * WARNING
 *    sometimes we assign constants to makeStrings. Make sure we don't free
 *    those.
 *
 *-------------------------------------------------------------------------
 */
#include <string.h>
#include <ctype.h>
#include "postgres.h"
#include "nodes/parsenodes.h"
#include "parser/catalog_utils.h"
#include "parser/parse_query.h"
#include "utils/acl.h"
#include "catalog/catname.h"
#include "utils/elog.h"
#include "access/xact.h"

static char saved_relname[BUFSIZ];  /* need this for complex attributes */
static bool QueryIsRule = FALSE;

extern List *parsetree;

/*
 * If you need access to certain yacc-generated variables and find that 
 * they're static by default, uncomment the next line.  (this is not a
 * problem, yet.)
 */
/*#define __YYSCLASS*/

extern void yyerror(char message[]);

static char *xlateSqlType(char *);
static Node *makeA_Expr(int op, char *opname, Node *lexpr, Node *rexpr);

/* old versions of flex define this as a macro */
#if defined(yywrap)
#undef yywrap
#endif /* yywrap */

#line 137 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    ABORT_TRANS = 258,             /* ABORT_TRANS  */
    ACL = 259,                     /* ACL  */
    ADD = 260,                     /* ADD  */
    AFTER = 261,                   /* AFTER  */
    AGGREGATE = 262,               /* AGGREGATE  */
    ALL = 263,                     /* ALL  */
    ALTER = 264,                   /* ALTER  */
    AND = 265,                     /* AND  */
    APPEND = 266,                  /* APPEND  */
    ARCHIVE = 267,                 /* ARCHIVE  */
    ARCH_STORE = 268,              /* ARCH_STORE  */
    AS = 269,                      /* AS  */
    ASC = 270,                     /* ASC  */
    BACKWARD = 271,                /* BACKWARD  */
    BEFORE = 272,                  /* BEFORE  */
    BEGIN_TRANS = 273,             /* BEGIN_TRANS  */
    BINARY = 274,                  /* BINARY  */
    BY = 275,                      /* BY  */
    CAST = 276,                    /* CAST  */
    CHANGE = 277,                  /* CHANGE  */
    CLOSE = 278,                   /* CLOSE  */
    CLUSTER = 279,                 /* CLUSTER  */
    COLUMN = 280,                  /* COLUMN  */
    COMMIT = 281,                  /* COMMIT  */
    COPY = 282,                    /* COPY  */
    CREATE = 283,                  /* CREATE  */
    CURRENT = 284,                 /* CURRENT  */
    CURSOR = 285,                  /* CURSOR  */
    DATABASE = 286,                /* DATABASE  */
    DECLARE = 287,                 /* DECLARE  */
    DELETE = 288,                  /* DELETE  */
    DELIMITERS = 289,              /* DELIMITERS  */
    DESC = 290,                    /* DESC  */
    DISTINCT = 291,                /* DISTINCT  */
    DO = 292,                      /* DO  */
    DROP = 293,                    /* DROP  */
    END_TRANS = 294,               /* END_TRANS  */
    EXTEND = 295,                  /* EXTEND  */
    FETCH = 296,                   /* FETCH  */
    FOR = 297,                     /* FOR  */
    FORWARD = 298,                 /* FORWARD  */
    FROM = 299,                    /* FROM  */
    FUNCTION = 300,                /* FUNCTION  */
    GRANT = 301,                   /* GRANT  */
    GROUP = 302,                   /* GROUP  */
    HAVING = 303,                  /* HAVING  */
    HEAVY = 304,                   /* HEAVY  */
    IN = 305,                      /* IN  */
    INDEX = 306,                   /* INDEX  */
    INHERITS = 307,                /* INHERITS  */
    INSERT = 308,                  /* INSERT  */
    INSTEAD = 309,                 /* INSTEAD  */
    INTO = 310,                    /* INTO  */
    ISNULL = 311,                  /* ISNULL  */
    LANGUAGE = 312,                /* LANGUAGE  */
    LIGHT = 313,                   /* LIGHT  */
    LISTEN = 314,                  /* LISTEN  */
    LOAD = 315,                    /* LOAD  */
    MERGE = 316,                   /* MERGE  */
    MOVE = 317,                    /* MOVE  */
    NEW = 318,                     /* NEW  */
    NONE = 319,                    /* NONE  */
    NOT = 320,                     /* NOT  */
    NOTHING = 321,                 /* NOTHING  */
    NOTIFY = 322,                  /* NOTIFY  */
    NOTNULL = 323,                 /* NOTNULL  */
    OIDS = 324,                    /* OIDS  */
    ON = 325,                      /* ON  */
    OPERATOR = 326,                /* OPERATOR  */
    OPTION = 327,                  /* OPTION  */
    OR = 328,                      /* OR  */
    ORDER = 329,                   /* ORDER  */
    PNULL = 330,                   /* PNULL  */
    PRIVILEGES = 331,              /* PRIVILEGES  */
    PUBLIC = 332,                  /* PUBLIC  */
    PURGE = 333,                   /* PURGE  */
    P_TYPE = 334,                  /* P_TYPE  */
    RENAME = 335,                  /* RENAME  */
    REPLACE = 336,                 /* REPLACE  */
    RETRIEVE = 337,                /* RETRIEVE  */
    RETURNS = 338,                 /* RETURNS  */
    REVOKE = 339,                  /* REVOKE  */
    ROLLBACK = 340,                /* ROLLBACK  */
    RULE = 341,                    /* RULE  */
    SELECT = 342,                  /* SELECT  */
    SET = 343,                     /* SET  */
    SETOF = 344,                   /* SETOF  */
    STDIN = 345,                   /* STDIN  */
    STDOUT = 346,                  /* STDOUT  */
    STORE = 347,                   /* STORE  */
    TABLE = 348,                   /* TABLE  */
    TO = 349,                      /* TO  */
    TRANSACTION = 350,             /* TRANSACTION  */
    UPDATE = 351,                  /* UPDATE  */
    USING = 352,                   /* USING  */
    VACUUM = 353,                  /* VACUUM  */
    VALUES = 354,                  /* VALUES  */
    VERSION = 355,                 /* VERSION  */
    VIEW = 356,                    /* VIEW  */
    WHERE = 357,                   /* WHERE  */
    WITH = 358,                    /* WITH  */
    WORK = 359,                    /* WORK  */
    EXECUTE = 360,                 /* EXECUTE  */
    RECIPE = 361,                  /* RECIPE  */
    EXPLAIN = 362,                 /* EXPLAIN  */
    LIKE = 363,                    /* LIKE  */
    IDENT = 364,                   /* IDENT  */
    SCONST = 365,                  /* SCONST  */
    Op = 366,                      /* Op  */
    ICONST = 367,                  /* ICONST  */
    PARAM = 368,                   /* PARAM  */
    FCONST = 369,                  /* FCONST  */
    OP = 370,                      /* OP  */
    UMINUS = 371,                  /* UMINUS  */
    TYPECAST = 372,                /* TYPECAST  */
    REDUCE = 373                   /* REDUCE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ABORT_TRANS 258
#define ACL 259
#define ADD 260
#define AFTER 261
#define AGGREGATE 262
#define ALL 263
#define ALTER 264
#define AND 265
#define APPEND 266
#define ARCHIVE 267
#define ARCH_STORE 268
#define AS 269
#define ASC 270
#define BACKWARD 271
#define BEFORE 272
#define BEGIN_TRANS 273
#define BINARY 274
#define BY 275
#define CAST 276
#define CHANGE 277
#define CLOSE 278
#define CLUSTER 279
#define COLUMN 280
#define COMMIT 281
#define COPY 282
#define CREATE 283
#define CURRENT 284
#define CURSOR 285
#define DATABASE 286
#define DECLARE 287
#define DELETE 288
#define DELIMITERS 289
#define DESC 290
#define DISTINCT 291
#define DO 292
#define DROP 293
#define END_TRANS 294
#define EXTEND 295
#define FETCH 296
#define FOR 297
#define FORWARD 298
#define FROM 299
#define FUNCTION 300
#define GRANT 301
#define GROUP 302
#define HAVING 303
#define HEAVY 304
#define IN 305
#define INDEX 306
#define INHERITS 307
#define INSERT 308
#define INSTEAD 309
#define INTO 310
#define ISNULL 311
#define LANGUAGE 312
#define LIGHT 313
#define LISTEN 314
#define LOAD 315
#define MERGE 316
#define MOVE 317
#define NEW 318
#define NONE 319
#define NOT 320
#define NOTHING 321
#define NOTIFY 322
#define NOTNULL 323
#define OIDS 324
#define ON 325
#define OPERATOR 326
#define OPTION 327
#define OR 328
#define ORDER 329
#define PNULL 330
#define PRIVILEGES 331
#define PUBLIC 332
#define PURGE 333
#define P_TYPE 334
#define RENAME 335
#define REPLACE 336
#define RETRIEVE 337
#define RETURNS 338
#define REVOKE 339
#define ROLLBACK 340
#define RULE 341
#define SELECT 342
#define SET 343
#define SETOF 344
#define STDIN 345
#define STDOUT 346
#define STORE 347
#define TABLE 348
#define TO 349
#define TRANSACTION 350
#define UPDATE 351
#define USING 352
#define VACUUM 353
#define VALUES 354
#define VERSION 355
#define VIEW 356
#define WHERE 357
#define WITH 358
#define WORK 359
#define EXECUTE 360
#define RECIPE 361
#define EXPLAIN 362
#define LIKE 363
#define IDENT 364
#define SCONST 365
#define Op 366
#define ICONST 367
#define PARAM 368
#define FCONST 369
#define OP 370
#define UMINUS 371
#define TYPECAST 372
#define REDUCE 373

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 68 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"

    double 		dval;
    int			ival;
    char                chr;
    char		*str;
    bool		boolean;
    List		*list;
    Node		*node;
    Value		*value;

    Attr		*attr;

    ColumnDef		*coldef;
    TypeName		*typnam;
    DefElem		*defelt;
    ParamString		*param;
    SortBy		*sortby;
    IndexElem		*ielem;
    RangeVar		*range;
    RelExpr		*relexp;
    TimeRange		*trange;
    A_Indices		*aind;
    ResTarget		*target;
    ParamNo		*paramno;
	
    VersionStmt		*vstmt;
    DefineStmt		*dstmt;
    PurgeStmt		*pstmt;
    RuleStmt		*rstmt;
    AppendStmt		*astmt;

#line 458 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ABORT_TRANS = 3,                /* ABORT_TRANS  */
  YYSYMBOL_ACL = 4,                        /* ACL  */
  YYSYMBOL_ADD = 5,                        /* ADD  */
  YYSYMBOL_AFTER = 6,                      /* AFTER  */
  YYSYMBOL_AGGREGATE = 7,                  /* AGGREGATE  */
  YYSYMBOL_ALL = 8,                        /* ALL  */
  YYSYMBOL_ALTER = 9,                      /* ALTER  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_APPEND = 11,                    /* APPEND  */
  YYSYMBOL_ARCHIVE = 12,                   /* ARCHIVE  */
  YYSYMBOL_ARCH_STORE = 13,                /* ARCH_STORE  */
  YYSYMBOL_AS = 14,                        /* AS  */
  YYSYMBOL_ASC = 15,                       /* ASC  */
  YYSYMBOL_BACKWARD = 16,                  /* BACKWARD  */
  YYSYMBOL_BEFORE = 17,                    /* BEFORE  */
  YYSYMBOL_BEGIN_TRANS = 18,               /* BEGIN_TRANS  */
  YYSYMBOL_BINARY = 19,                    /* BINARY  */
  YYSYMBOL_BY = 20,                        /* BY  */
  YYSYMBOL_CAST = 21,                      /* CAST  */
  YYSYMBOL_CHANGE = 22,                    /* CHANGE  */
  YYSYMBOL_CLOSE = 23,                     /* CLOSE  */
  YYSYMBOL_CLUSTER = 24,                   /* CLUSTER  */
  YYSYMBOL_COLUMN = 25,                    /* COLUMN  */
  YYSYMBOL_COMMIT = 26,                    /* COMMIT  */
  YYSYMBOL_COPY = 27,                      /* COPY  */
  YYSYMBOL_CREATE = 28,                    /* CREATE  */
  YYSYMBOL_CURRENT = 29,                   /* CURRENT  */
  YYSYMBOL_CURSOR = 30,                    /* CURSOR  */
  YYSYMBOL_DATABASE = 31,                  /* DATABASE  */
  YYSYMBOL_DECLARE = 32,                   /* DECLARE  */
  YYSYMBOL_DELETE = 33,                    /* DELETE  */
  YYSYMBOL_DELIMITERS = 34,                /* DELIMITERS  */
  YYSYMBOL_DESC = 35,                      /* DESC  */
  YYSYMBOL_DISTINCT = 36,                  /* DISTINCT  */
  YYSYMBOL_DO = 37,                        /* DO  */
  YYSYMBOL_DROP = 38,                      /* DROP  */
  YYSYMBOL_END_TRANS = 39,                 /* END_TRANS  */
  YYSYMBOL_EXTEND = 40,                    /* EXTEND  */
  YYSYMBOL_FETCH = 41,                     /* FETCH  */
  YYSYMBOL_FOR = 42,                       /* FOR  */
  YYSYMBOL_FORWARD = 43,                   /* FORWARD  */
  YYSYMBOL_FROM = 44,                      /* FROM  */
  YYSYMBOL_FUNCTION = 45,                  /* FUNCTION  */
  YYSYMBOL_GRANT = 46,                     /* GRANT  */
  YYSYMBOL_GROUP = 47,                     /* GROUP  */
  YYSYMBOL_HAVING = 48,                    /* HAVING  */
  YYSYMBOL_HEAVY = 49,                     /* HEAVY  */
  YYSYMBOL_IN = 50,                        /* IN  */
  YYSYMBOL_INDEX = 51,                     /* INDEX  */
  YYSYMBOL_INHERITS = 52,                  /* INHERITS  */
  YYSYMBOL_INSERT = 53,                    /* INSERT  */
  YYSYMBOL_INSTEAD = 54,                   /* INSTEAD  */
  YYSYMBOL_INTO = 55,                      /* INTO  */
  YYSYMBOL_ISNULL = 56,                    /* ISNULL  */
  YYSYMBOL_LANGUAGE = 57,                  /* LANGUAGE  */
  YYSYMBOL_LIGHT = 58,                     /* LIGHT  */
  YYSYMBOL_LISTEN = 59,                    /* LISTEN  */
  YYSYMBOL_LOAD = 60,                      /* LOAD  */
  YYSYMBOL_MERGE = 61,                     /* MERGE  */
  YYSYMBOL_MOVE = 62,                      /* MOVE  */
  YYSYMBOL_NEW = 63,                       /* NEW  */
  YYSYMBOL_NONE = 64,                      /* NONE  */
  YYSYMBOL_NOT = 65,                       /* NOT  */
  YYSYMBOL_NOTHING = 66,                   /* NOTHING  */
  YYSYMBOL_NOTIFY = 67,                    /* NOTIFY  */
  YYSYMBOL_NOTNULL = 68,                   /* NOTNULL  */
  YYSYMBOL_OIDS = 69,                      /* OIDS  */
  YYSYMBOL_ON = 70,                        /* ON  */
  YYSYMBOL_OPERATOR = 71,                  /* OPERATOR  */
  YYSYMBOL_OPTION = 72,                    /* OPTION  */
  YYSYMBOL_OR = 73,                        /* OR  */
  YYSYMBOL_ORDER = 74,                     /* ORDER  */
  YYSYMBOL_PNULL = 75,                     /* PNULL  */
  YYSYMBOL_PRIVILEGES = 76,                /* PRIVILEGES  */
  YYSYMBOL_PUBLIC = 77,                    /* PUBLIC  */
  YYSYMBOL_PURGE = 78,                     /* PURGE  */
  YYSYMBOL_P_TYPE = 79,                    /* P_TYPE  */
  YYSYMBOL_RENAME = 80,                    /* RENAME  */
  YYSYMBOL_REPLACE = 81,                   /* REPLACE  */
  YYSYMBOL_RETRIEVE = 82,                  /* RETRIEVE  */
  YYSYMBOL_RETURNS = 83,                   /* RETURNS  */
  YYSYMBOL_REVOKE = 84,                    /* REVOKE  */
  YYSYMBOL_ROLLBACK = 85,                  /* ROLLBACK  */
  YYSYMBOL_RULE = 86,                      /* RULE  */
  YYSYMBOL_SELECT = 87,                    /* SELECT  */
  YYSYMBOL_SET = 88,                       /* SET  */
  YYSYMBOL_SETOF = 89,                     /* SETOF  */
  YYSYMBOL_STDIN = 90,                     /* STDIN  */
  YYSYMBOL_STDOUT = 91,                    /* STDOUT  */
  YYSYMBOL_STORE = 92,                     /* STORE  */
  YYSYMBOL_TABLE = 93,                     /* TABLE  */
  YYSYMBOL_TO = 94,                        /* TO  */
  YYSYMBOL_TRANSACTION = 95,               /* TRANSACTION  */
  YYSYMBOL_UPDATE = 96,                    /* UPDATE  */
  YYSYMBOL_USING = 97,                     /* USING  */
  YYSYMBOL_VACUUM = 98,                    /* VACUUM  */
  YYSYMBOL_VALUES = 99,                    /* VALUES  */
  YYSYMBOL_VERSION = 100,                  /* VERSION  */
  YYSYMBOL_VIEW = 101,                     /* VIEW  */
  YYSYMBOL_WHERE = 102,                    /* WHERE  */
  YYSYMBOL_WITH = 103,                     /* WITH  */
  YYSYMBOL_WORK = 104,                     /* WORK  */
  YYSYMBOL_EXECUTE = 105,                  /* EXECUTE  */
  YYSYMBOL_RECIPE = 106,                   /* RECIPE  */
  YYSYMBOL_EXPLAIN = 107,                  /* EXPLAIN  */
  YYSYMBOL_LIKE = 108,                     /* LIKE  */
  YYSYMBOL_IDENT = 109,                    /* IDENT  */
  YYSYMBOL_SCONST = 110,                   /* SCONST  */
  YYSYMBOL_Op = 111,                       /* Op  */
  YYSYMBOL_ICONST = 112,                   /* ICONST  */
  YYSYMBOL_PARAM = 113,                    /* PARAM  */
  YYSYMBOL_FCONST = 114,                   /* FCONST  */
  YYSYMBOL_OP = 115,                       /* OP  */
  YYSYMBOL_116_ = 116,                     /* '='  */
  YYSYMBOL_117_ = 117,                     /* '+'  */
  YYSYMBOL_118_ = 118,                     /* '-'  */
  YYSYMBOL_119_ = 119,                     /* '*'  */
  YYSYMBOL_120_ = 120,                     /* '/'  */
  YYSYMBOL_121_ = 121,                     /* '|'  */
  YYSYMBOL_122_ = 122,                     /* ';'  */
  YYSYMBOL_123_ = 123,                     /* ':'  */
  YYSYMBOL_124_ = 124,                     /* '<'  */
  YYSYMBOL_125_ = 125,                     /* '>'  */
  YYSYMBOL_UMINUS = 126,                   /* UMINUS  */
  YYSYMBOL_127_ = 127,                     /* '.'  */
  YYSYMBOL_128_ = 128,                     /* '['  */
  YYSYMBOL_129_ = 129,                     /* ']'  */
  YYSYMBOL_TYPECAST = 130,                 /* TYPECAST  */
  YYSYMBOL_REDUCE = 131,                   /* REDUCE  */
  YYSYMBOL_132_ = 132,                     /* '('  */
  YYSYMBOL_133_ = 133,                     /* ')'  */
  YYSYMBOL_134_ = 134,                     /* ','  */
  YYSYMBOL_YYACCEPT = 135,                 /* $accept  */
  YYSYMBOL_queryblock = 136,               /* queryblock  */
  YYSYMBOL_query = 137,                    /* query  */
  YYSYMBOL_stmt = 138,                     /* stmt  */
  YYSYMBOL_AddAttrStmt = 139,              /* AddAttrStmt  */
  YYSYMBOL_columnDef = 140,                /* columnDef  */
  YYSYMBOL_ClosePortalStmt = 141,          /* ClosePortalStmt  */
  YYSYMBOL_CopyStmt = 142,                 /* CopyStmt  */
  YYSYMBOL_copy_dirn = 143,                /* copy_dirn  */
  YYSYMBOL_copy_file_name = 144,           /* copy_file_name  */
  YYSYMBOL_opt_binary = 145,               /* opt_binary  */
  YYSYMBOL_opt_with_copy = 146,            /* opt_with_copy  */
  YYSYMBOL_copy_delimiter = 147,           /* copy_delimiter  */
  YYSYMBOL_CreateStmt = 148,               /* CreateStmt  */
  YYSYMBOL_OptTableElementList = 149,      /* OptTableElementList  */
  YYSYMBOL_tableElementList = 150,         /* tableElementList  */
  YYSYMBOL_OptArchiveType = 151,           /* OptArchiveType  */
  YYSYMBOL_archive_type = 152,             /* archive_type  */
  YYSYMBOL_OptLocation = 153,              /* OptLocation  */
  YYSYMBOL_OptArchiveLocation = 154,       /* OptArchiveLocation  */
  YYSYMBOL_OptInherit = 155,               /* OptInherit  */
  YYSYMBOL_DefineStmt = 156,               /* DefineStmt  */
  YYSYMBOL_def_rest = 157,                 /* def_rest  */
  YYSYMBOL_def_type = 158,                 /* def_type  */
  YYSYMBOL_def_name = 159,                 /* def_name  */
  YYSYMBOL_definition = 160,               /* definition  */
  YYSYMBOL_def_list = 161,                 /* def_list  */
  YYSYMBOL_def_elem = 162,                 /* def_elem  */
  YYSYMBOL_def_arg = 163,                  /* def_arg  */
  YYSYMBOL_DestroyStmt = 164,              /* DestroyStmt  */
  YYSYMBOL_FetchStmt = 165,                /* FetchStmt  */
  YYSYMBOL_opt_direction = 166,            /* opt_direction  */
  YYSYMBOL_fetch_how_many = 167,           /* fetch_how_many  */
  YYSYMBOL_GrantStmt = 168,                /* GrantStmt  */
  YYSYMBOL_privileges = 169,               /* privileges  */
  YYSYMBOL_operation_commalist = 170,      /* operation_commalist  */
  YYSYMBOL_operation = 171,                /* operation  */
  YYSYMBOL_grantee = 172,                  /* grantee  */
  YYSYMBOL_opt_with_grant = 173,           /* opt_with_grant  */
  YYSYMBOL_RevokeStmt = 174,               /* RevokeStmt  */
  YYSYMBOL_MoveStmt = 175,                 /* MoveStmt  */
  YYSYMBOL_opt_move_where = 176,           /* opt_move_where  */
  YYSYMBOL_opt_portal_name = 177,          /* opt_portal_name  */
  YYSYMBOL_IndexStmt = 178,                /* IndexStmt  */
  YYSYMBOL_ExtendStmt = 179,               /* ExtendStmt  */
  YYSYMBOL_RecipeStmt = 180,               /* RecipeStmt  */
  YYSYMBOL_ProcedureStmt = 181,            /* ProcedureStmt  */
  YYSYMBOL_opt_with_func = 182,            /* opt_with_func  */
  YYSYMBOL_def_args = 183,                 /* def_args  */
  YYSYMBOL_def_name_list = 184,            /* def_name_list  */
  YYSYMBOL_PurgeStmt = 185,                /* PurgeStmt  */
  YYSYMBOL_purge_quals = 186,              /* purge_quals  */
  YYSYMBOL_before_clause = 187,            /* before_clause  */
  YYSYMBOL_after_clause = 188,             /* after_clause  */
  YYSYMBOL_RemoveStmt = 189,               /* RemoveStmt  */
  YYSYMBOL_remove_type = 190,              /* remove_type  */
  YYSYMBOL_RemoveFuncStmt = 191,           /* RemoveFuncStmt  */
  YYSYMBOL_func_argtypes = 192,            /* func_argtypes  */
  YYSYMBOL_RemoveOperStmt = 193,           /* RemoveOperStmt  */
  YYSYMBOL_all_Op = 194,                   /* all_Op  */
  YYSYMBOL_MathOp = 195,                   /* MathOp  */
  YYSYMBOL_oper_argtypes = 196,            /* oper_argtypes  */
  YYSYMBOL_RenameStmt = 197,               /* RenameStmt  */
  YYSYMBOL_opt_name = 198,                 /* opt_name  */
  YYSYMBOL_opt_column = 199,               /* opt_column  */
  YYSYMBOL_RuleStmt = 200,                 /* RuleStmt  */
  YYSYMBOL_201_1 = 201,                    /* $@1  */
  YYSYMBOL_OptStmtList = 202,              /* OptStmtList  */
  YYSYMBOL_OptStmtBlock = 203,             /* OptStmtBlock  */
  YYSYMBOL_event_object = 204,             /* event_object  */
  YYSYMBOL_event = 205,                    /* event  */
  YYSYMBOL_opt_instead = 206,              /* opt_instead  */
  YYSYMBOL_NotifyStmt = 207,               /* NotifyStmt  */
  YYSYMBOL_ListenStmt = 208,               /* ListenStmt  */
  YYSYMBOL_TransactionStmt = 209,          /* TransactionStmt  */
  YYSYMBOL_ViewStmt = 210,                 /* ViewStmt  */
  YYSYMBOL_LoadStmt = 211,                 /* LoadStmt  */
  YYSYMBOL_CreatedbStmt = 212,             /* CreatedbStmt  */
  YYSYMBOL_DestroydbStmt = 213,            /* DestroydbStmt  */
  YYSYMBOL_ClusterStmt = 214,              /* ClusterStmt  */
  YYSYMBOL_VacuumStmt = 215,               /* VacuumStmt  */
  YYSYMBOL_ExplainStmt = 216,              /* ExplainStmt  */
  YYSYMBOL_explain_options = 217,          /* explain_options  */
  YYSYMBOL_OptimizableStmt = 218,          /* OptimizableStmt  */
  YYSYMBOL_AppendStmt = 219,               /* AppendStmt  */
  YYSYMBOL_insert_rest = 220,              /* insert_rest  */
  YYSYMBOL_opt_column_list = 221,          /* opt_column_list  */
  YYSYMBOL_columnList = 222,               /* columnList  */
  YYSYMBOL_columnElem = 223,               /* columnElem  */
  YYSYMBOL_exprList = 224,                 /* exprList  */
  YYSYMBOL_exprElem = 225,                 /* exprElem  */
  YYSYMBOL_DeleteStmt = 226,               /* DeleteStmt  */
  YYSYMBOL_ReplaceStmt = 227,              /* ReplaceStmt  */
  YYSYMBOL_CursorStmt = 228,               /* CursorStmt  */
  YYSYMBOL_RetrieveStmt = 229,             /* RetrieveStmt  */
  YYSYMBOL_result = 230,                   /* result  */
  YYSYMBOL_opt_unique = 231,               /* opt_unique  */
  YYSYMBOL_sort_clause = 232,              /* sort_clause  */
  YYSYMBOL_sortby_list = 233,              /* sortby_list  */
  YYSYMBOL_sortby = 234,                   /* sortby  */
  YYSYMBOL_OptUseOp = 235,                 /* OptUseOp  */
  YYSYMBOL_index_params = 236,             /* index_params  */
  YYSYMBOL_func_index = 237,               /* func_index  */
  YYSYMBOL_index_elem = 238,               /* index_elem  */
  YYSYMBOL_opt_class = 239,                /* opt_class  */
  YYSYMBOL_opt_inh_star = 240,             /* opt_inh_star  */
  YYSYMBOL_relation_name_list = 241,       /* relation_name_list  */
  YYSYMBOL_name_list = 242,                /* name_list  */
  YYSYMBOL_group_clause = 243,             /* group_clause  */
  YYSYMBOL_groupby_list = 244,             /* groupby_list  */
  YYSYMBOL_groupby = 245,                  /* groupby  */
  YYSYMBOL_having_clause = 246,            /* having_clause  */
  YYSYMBOL_from_clause = 247,              /* from_clause  */
  YYSYMBOL_from_list = 248,                /* from_list  */
  YYSYMBOL_from_val = 249,                 /* from_val  */
  YYSYMBOL_where_clause = 250,             /* where_clause  */
  YYSYMBOL_relation_expr = 251,            /* relation_expr  */
  YYSYMBOL_time_range = 252,               /* time_range  */
  YYSYMBOL_opt_range_start = 253,          /* opt_range_start  */
  YYSYMBOL_opt_range_end = 254,            /* opt_range_end  */
  YYSYMBOL_opt_array_bounds = 255,         /* opt_array_bounds  */
  YYSYMBOL_nest_array_bounds = 256,        /* nest_array_bounds  */
  YYSYMBOL_typname = 257,                  /* typname  */
  YYSYMBOL_Typename = 258,                 /* Typename  */
  YYSYMBOL_a_expr = 259,                   /* a_expr  */
  YYSYMBOL_opt_indirection = 260,          /* opt_indirection  */
  YYSYMBOL_expr_list = 261,                /* expr_list  */
  YYSYMBOL_attr = 262,                     /* attr  */
  YYSYMBOL_attrs = 263,                    /* attrs  */
  YYSYMBOL_res_target_list = 264,          /* res_target_list  */
  YYSYMBOL_res_target_el = 265,            /* res_target_el  */
  YYSYMBOL_res_target_list2 = 266,         /* res_target_list2  */
  YYSYMBOL_res_target_el2 = 267,           /* res_target_el2  */
  YYSYMBOL_opt_id = 268,                   /* opt_id  */
  YYSYMBOL_relation_name = 269,            /* relation_name  */
  YYSYMBOL_database_name = 270,            /* database_name  */
  YYSYMBOL_access_method = 271,            /* access_method  */
  YYSYMBOL_attr_name = 272,                /* attr_name  */
  YYSYMBOL_class = 273,                    /* class  */
  YYSYMBOL_index_name = 274,               /* index_name  */
  YYSYMBOL_var_name = 275,                 /* var_name  */
  YYSYMBOL_name = 276,                     /* name  */
  YYSYMBOL_date = 277,                     /* date  */
  YYSYMBOL_file_name = 278,                /* file_name  */
  YYSYMBOL_recipe_name = 279,              /* recipe_name  */
  YYSYMBOL_AexprConst = 280,               /* AexprConst  */
  YYSYMBOL_ParamNo = 281,                  /* ParamNo  */
  YYSYMBOL_NumConst = 282,                 /* NumConst  */
  YYSYMBOL_Iconst = 283,                   /* Iconst  */
  YYSYMBOL_Sconst = 284,                   /* Sconst  */
  YYSYMBOL_Id = 285,                       /* Id  */
  YYSYMBOL_SpecialRuleRelation = 286,      /* SpecialRuleRelation  */
  YYSYMBOL_Type = 287,                     /* Type  */
  YYSYMBOL_Pnull = 288                     /* Pnull  */
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
#define YYFINAL  139
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1030

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  135
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  154
/* YYNRULES -- Number of rules.  */
#define YYNRULES  368
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  611

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   373


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     132,   133,   119,   117,   134,   118,   127,   120,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   123,   122,
     124,   116,   125,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   128,     2,   129,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   121,     2,     2,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   126,   130,   131
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   216,   216,   218,   222,   223,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   265,   275,   291,   308,
     321,   323,   332,   333,   334,   337,   338,   341,   342,   348,
     349,   360,   374,   375,   379,   381,   386,   387,   390,   391,
     392,   395,   398,   401,   404,   407,   408,   419,   426,   434,
     435,   436,   439,   439,   439,   443,   447,   449,   453,   459,
     467,   468,   469,   470,   471,   488,   504,   514,   515,   516,
     519,   522,   523,   533,   541,   545,   549,   554,   557,   564,
     567,   570,   573,   576,   581,   584,   587,   592,   593,   605,
     620,   629,   640,   641,   644,   645,   659,   682,   698,   727,
     740,   741,   744,   745,   748,   760,   767,   773,   779,   785,
     792,   799,   800,   818,   827,   828,   829,   830,   831,   834,
     843,   844,   847,   856,   856,   858,   859,   860,   861,   862,
     863,   864,   867,   871,   873,   875,   887,   899,   900,   903,
     904,   918,   917,   933,   934,   935,   938,   940,   942,   946,
     954,   965,   966,   967,   968,   971,   972,   984,   992,  1014,
    1020,  1026,  1032,  1038,  1044,  1051,  1057,  1063,  1070,  1076,
    1092,  1109,  1125,  1141,  1157,  1173,  1177,  1192,  1201,  1204,
    1218,  1219,  1220,  1221,  1222,  1223,  1234,  1242,  1249,  1258,
    1259,  1263,  1265,  1269,  1278,  1280,  1285,  1287,  1296,  1315,
    1333,  1355,  1391,  1409,  1412,  1415,  1416,  1417,  1420,  1421,
    1424,  1426,  1430,  1436,  1442,  1443,  1444,  1445,  1446,  1447,
    1451,  1452,  1462,  1471,  1480,  1481,  1482,  1494,  1495,  1498,
    1500,  1502,  1506,  1507,  1510,  1511,  1514,  1521,  1527,  1528,
    1539,  1540,  1543,  1545,  1549,  1555,  1561,  1569,  1570,  1573,
    1581,  1589,  1600,  1606,  1614,  1615,  1618,  1619,  1622,  1624,
    1627,  1630,  1632,  1635,  1638,  1663,  1671,  1676,  1718,  1723,
    1725,  1727,  1729,  1731,  1733,  1735,  1737,  1739,  1741,  1743,
    1745,  1747,  1757,  1767,  1769,  1771,  1773,  1775,  1777,  1779,
    1786,  1797,  1804,  1811,  1813,  1815,  1817,  1819,  1823,  1830,
    1838,  1841,  1843,  1847,  1855,  1865,  1867,  1869,  1880,  1882,
    1884,  1899,  1906,  1913,  1933,  1935,  1937,  1953,  1960,  1967,
    1981,  1982,  1985,  1990,  2005,  2006,  2007,  2008,  2009,  2010,
    2011,  2013,  2014,  2015,  2017,  2024,  2031,  2038,  2040,  2048,
    2055,  2056,  2059,  2060,  2062,  2064,  2071,  2080,  2081
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
  "\"end of file\"", "error", "\"invalid token\"", "ABORT_TRANS", "ACL",
  "ADD", "AFTER", "AGGREGATE", "ALL", "ALTER", "AND", "APPEND", "ARCHIVE",
  "ARCH_STORE", "AS", "ASC", "BACKWARD", "BEFORE", "BEGIN_TRANS", "BINARY",
  "BY", "CAST", "CHANGE", "CLOSE", "CLUSTER", "COLUMN", "COMMIT", "COPY",
  "CREATE", "CURRENT", "CURSOR", "DATABASE", "DECLARE", "DELETE",
  "DELIMITERS", "DESC", "DISTINCT", "DO", "DROP", "END_TRANS", "EXTEND",
  "FETCH", "FOR", "FORWARD", "FROM", "FUNCTION", "GRANT", "GROUP",
  "HAVING", "HEAVY", "IN", "INDEX", "INHERITS", "INSERT", "INSTEAD",
  "INTO", "ISNULL", "LANGUAGE", "LIGHT", "LISTEN", "LOAD", "MERGE", "MOVE",
  "NEW", "NONE", "NOT", "NOTHING", "NOTIFY", "NOTNULL", "OIDS", "ON",
  "OPERATOR", "OPTION", "OR", "ORDER", "PNULL", "PRIVILEGES", "PUBLIC",
  "PURGE", "P_TYPE", "RENAME", "REPLACE", "RETRIEVE", "RETURNS", "REVOKE",
  "ROLLBACK", "RULE", "SELECT", "SET", "SETOF", "STDIN", "STDOUT", "STORE",
  "TABLE", "TO", "TRANSACTION", "UPDATE", "USING", "VACUUM", "VALUES",
  "VERSION", "VIEW", "WHERE", "WITH", "WORK", "EXECUTE", "RECIPE",
  "EXPLAIN", "LIKE", "IDENT", "SCONST", "Op", "ICONST", "PARAM", "FCONST",
  "OP", "'='", "'+'", "'-'", "'*'", "'/'", "'|'", "';'", "':'", "'<'",
  "'>'", "UMINUS", "'.'", "'['", "']'", "TYPECAST", "REDUCE", "'('", "')'",
  "','", "$accept", "queryblock", "query", "stmt", "AddAttrStmt",
  "columnDef", "ClosePortalStmt", "CopyStmt", "copy_dirn",
  "copy_file_name", "opt_binary", "opt_with_copy", "copy_delimiter",
  "CreateStmt", "OptTableElementList", "tableElementList",
  "OptArchiveType", "archive_type", "OptLocation", "OptArchiveLocation",
  "OptInherit", "DefineStmt", "def_rest", "def_type", "def_name",
  "definition", "def_list", "def_elem", "def_arg", "DestroyStmt",
  "FetchStmt", "opt_direction", "fetch_how_many", "GrantStmt",
  "privileges", "operation_commalist", "operation", "grantee",
  "opt_with_grant", "RevokeStmt", "MoveStmt", "opt_move_where",
  "opt_portal_name", "IndexStmt", "ExtendStmt", "RecipeStmt",
  "ProcedureStmt", "opt_with_func", "def_args", "def_name_list",
  "PurgeStmt", "purge_quals", "before_clause", "after_clause",
  "RemoveStmt", "remove_type", "RemoveFuncStmt", "func_argtypes",
  "RemoveOperStmt", "all_Op", "MathOp", "oper_argtypes", "RenameStmt",
  "opt_name", "opt_column", "RuleStmt", "$@1", "OptStmtList",
  "OptStmtBlock", "event_object", "event", "opt_instead", "NotifyStmt",
  "ListenStmt", "TransactionStmt", "ViewStmt", "LoadStmt", "CreatedbStmt",
  "DestroydbStmt", "ClusterStmt", "VacuumStmt", "ExplainStmt",
  "explain_options", "OptimizableStmt", "AppendStmt", "insert_rest",
  "opt_column_list", "columnList", "columnElem", "exprList", "exprElem",
  "DeleteStmt", "ReplaceStmt", "CursorStmt", "RetrieveStmt", "result",
  "opt_unique", "sort_clause", "sortby_list", "sortby", "OptUseOp",
  "index_params", "func_index", "index_elem", "opt_class", "opt_inh_star",
  "relation_name_list", "name_list", "group_clause", "groupby_list",
  "groupby", "having_clause", "from_clause", "from_list", "from_val",
  "where_clause", "relation_expr", "time_range", "opt_range_start",
  "opt_range_end", "opt_array_bounds", "nest_array_bounds", "typname",
  "Typename", "a_expr", "opt_indirection", "expr_list", "attr", "attrs",
  "res_target_list", "res_target_el", "res_target_list2", "res_target_el2",
  "opt_id", "relation_name", "database_name", "access_method", "attr_name",
  "class", "index_name", "var_name", "name", "date", "file_name",
  "recipe_name", "AexprConst", "ParamNo", "NumConst", "Iconst", "Sconst",
  "Id", "SpecialRuleRelation", "Type", "Pnull", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-437)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-351)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     856,   -47,   -48,    99,    36,    36,    19,   133,   452,    36,
     123,   874,    76,   127,    14,    97,   144,     4,   115,    14,
       4,     4,    97,   130,   195,     4,     4,   156,   139,   250,
     856,   142,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,     4,
    -437,  -437,  -437,  -437,  -437,   200,  -437,  -437,  -437,     4,
    -437,    36,   905,    36,  -437,  -437,    36,     4,    36,   905,
    -437,   133,  -437,     4,  -437,    36,    36,  -437,   450,  -437,
      36,  -437,    36,  -437,  -437,    36,  -437,  -437,     3,   209,
    -437,  -437,  -437,  -437,  -437,   230,   169,  -437,     4,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,   -50,  -437,    91,
     241,  -437,   243,   715,   221,  -437,    36,    36,   235,  -437,
    -437,  -437,   196,     4,   211,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,   184,  -437,  -437,   247,   306,
     189,   311,  -437,   197,   297,   226,  -437,   198,  -437,   205,
    -437,  -437,   206,  -437,  -437,   226,  -437,  -437,   291,  -437,
    -437,    36,    94,   210,   231,   291,  -437,   115,   115,  -437,
     338,   328,    36,    36,   -40,   467,  -437,   467,  -437,  -437,
     467,  -437,   467,   467,   467,   467,   393,   218,   -35,  -437,
     220,   217,   223,   224,  -437,  -437,   106,  -437,    -2,  -437,
    -437,   206,  -437,  -437,    20,  -437,   286,    -7,   -73,   274,
       4,  -437,    36,   271,   905,  -437,   324,   467,  -437,    36,
     -21,    36,  -437,    36,  -437,   270,  -437,    36,    50,   291,
    -437,  -437,  -437,  -437,  -437,  -437,   325,  -437,   357,  -437,
     861,   246,   876,  -437,   116,   116,   116,   136,   467,    36,
    -437,   268,  -437,   467,   467,    47,   467,   467,   467,   467,
     467,   467,   467,   467,  -437,   284,   467,   335,    44,   687,
      73,    36,  -437,   218,   -18,  -437,   256,   224,   121,   359,
     360,  -437,  -437,  -437,    64,  -437,   253,   206,   893,   295,
     329,  -437,   261,   275,    73,  -437,   288,   143,  -437,   315,
     610,   278,   206,   281,   279,   283,  -437,  -437,    -6,   147,
    -437,   218,   739,   276,  -437,  -437,    -6,    73,    36,  -437,
     861,  -437,   467,   629,   831,   876,   322,   154,   154,   116,
     116,   158,   158,   530,     4,  -437,     4,   226,  -437,   293,
    -437,  -437,   285,  -437,   610,   157,    36,   296,  -437,   294,
     293,  -437,    27,   226,    66,   307,    36,  -437,    36,  -437,
    -437,   330,  -437,  -437,    36,  -437,   326,  -437,  -437,  -437,
    -437,  -437,    36,   111,   376,    36,  -437,   893,  -437,   905,
     195,  -437,    36,  -437,    29,    36,  -437,   332,  -437,  -437,
      36,  -437,  -437,   -16,  -437,   610,   304,   739,  -437,  -437,
     831,   467,   218,  -437,   298,  -437,    10,    67,   390,   104,
    -437,  -437,   467,  -437,   -78,  -437,   231,  -437,  -437,  -437,
     467,  -437,   349,  -437,   410,  -437,  -437,   197,   431,   316,
    -437,  -437,  -437,  -437,  -437,   358,   319,   442,  -437,  -437,
    -437,   715,  -437,  -437,  -437,  -437,   409,  -437,  -437,   739,
     226,   110,   161,   595,  -437,     4,    36,  -437,  -437,  -437,
     115,  -437,   436,   412,  -437,  -437,   610,   334,   339,   331,
     610,    36,   115,  -437,   115,    36,     4,    36,   353,   381,
     -13,   402,  -437,  -437,  -437,  -437,   218,  -437,  -437,   341,
     347,    27,   467,   404,   -74,  -437,   334,  -437,  -437,  -437,
     423,   348,  -437,  -437,    88,   350,   352,   226,   362,   366,
     138,   369,   477,   226,  -437,  -437,   115,  -437,   361,  -437,
    -437,   373,   610,   485,  -437,   334,   377,  -437,   115,  -437,
      36,  -437,  -437,  -437,    36,   478,    36,  -437,  -437,  -437,
    -437,  -437,   115,   398,  -437,   404,   387,  -437,    27,    27,
    -437,   334,  -437,  -437,   163,   465,  -437,  -437,   115,  -437,
    -437,  -437,   391,  -437,    34,    -3,  -437,    88,  -437,   239,
    -437,    27,  -437,  -437,   134,  -437,  -437,  -437,  -437,   235,
    -437,  -437,  -437,  -437,  -437,  -437,   179,   405,  -437,  -437,
    -437
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   185,     0,   186,   341,     0,   187,    46,     0,     0,
       0,     0,   188,     0,    89,     0,     0,     0,     0,    89,
       0,     0,     0,   189,   227,     0,   195,     0,   199,     0,
       3,     4,     6,     7,     8,     9,    11,    12,    15,    16,
      27,    18,    17,    13,    22,    20,    21,    25,    24,    23,
      26,    29,   204,    19,    30,    31,    32,    33,    34,    10,
      35,    14,    28,   203,   205,   202,   201,   200,   179,     0,
     180,   181,   364,    38,   340,     0,   348,   182,    45,     0,
      71,     0,     0,     0,    69,   367,     0,     0,     0,     0,
      70,    46,   350,     0,   134,     0,     0,   136,     0,   137,
       0,   138,     0,   135,   183,     0,    88,    87,    92,    95,
     102,   100,   103,    99,   101,     0,    96,    97,     0,   365,
     366,   178,   343,   342,   363,   191,   352,   113,   177,   130,
       0,   184,   225,     0,     0,   196,     0,     0,     0,     1,
       2,     5,   248,     0,    48,   192,   344,    74,   151,   145,
     146,   147,   148,   149,   150,     0,    73,    72,     0,     0,
       0,     0,    67,     0,     0,   268,   193,     0,   143,     0,
     144,    85,   249,   250,   133,   268,    91,   362,   115,    90,
      94,     0,     0,   210,     0,   115,   112,     0,     0,   125,
     126,   127,     0,     0,     0,     0,   368,     0,   359,   355,
       0,   336,     0,     0,     0,     0,   338,   320,   224,   335,
       0,     0,   289,   357,   354,   356,   309,   358,     0,   118,
     353,   198,   197,   247,     0,   194,     0,     0,     0,     0,
       0,   161,    53,     0,     0,    68,     0,     0,   219,   141,
       0,     0,   117,     0,    86,     0,    98,     0,     0,   115,
     110,   132,   351,   131,   128,   129,     0,   226,     0,   357,
     317,     0,   307,   290,   300,   299,   298,     0,     0,     0,
     313,     0,   314,     0,     0,   308,     0,     0,     0,     0,
       0,     0,     0,     0,   288,     0,     0,   261,     0,     0,
       0,     0,   330,   320,   261,   329,     0,     0,   320,     0,
     160,    47,    41,    40,     0,   123,     0,   124,     0,     0,
       0,    55,     0,    52,     0,   190,    79,     0,    76,     0,
     267,     0,   140,     0,     0,   152,   251,   114,     0,     0,
     212,   320,     0,     0,   206,   111,     0,     0,     0,   303,
     315,   337,     0,   316,   305,   304,   297,   291,   292,   294,
     293,   295,   296,     0,     0,   334,     0,   268,   339,   323,
     325,   346,     0,   311,   321,     0,     0,   280,   301,   284,
     324,   332,     0,   268,     0,     0,     0,   159,   158,    43,
      44,    50,    42,   122,     0,   361,   121,    81,    82,   360,
      83,    80,     0,     0,    66,     0,    37,     0,    75,     0,
     227,   139,     0,   142,     0,     0,   104,   107,   106,   209,
       0,   213,   218,   261,   215,   216,     0,     0,   109,   302,
     306,     0,   320,   223,   260,   263,   266,   269,   253,     0,
     310,   312,     0,   285,     0,   286,     0,   328,   220,   333,
       0,    36,     0,   157,     0,    39,    84,     0,     0,     0,
     345,   173,   174,   171,   172,     0,     0,    57,    54,    78,
      77,     0,   154,   155,   153,   105,     0,    93,   211,     0,
     268,     0,     0,     0,   318,     0,     0,   265,   349,   270,
     275,   271,     0,   259,   327,   326,   322,   283,     0,     0,
     331,     0,     0,   120,     0,     0,     0,     0,     0,    62,
     261,     0,   214,   208,   217,   207,   320,   262,   264,     0,
     274,     0,     0,   229,     0,   278,   283,   287,   156,    49,
       0,     0,   241,   240,   246,     0,   346,   268,   170,     0,
       0,     0,    64,   268,   108,   319,   277,   273,   252,   254,
     257,   256,   258,     0,   222,   283,     0,   279,     0,   116,
       0,   243,   244,   347,     0,     0,     0,    65,    58,    59,
      60,    56,     0,     0,    51,   229,     0,   276,     0,     0,
     281,   283,   119,   245,     0,   176,   169,    61,     0,   221,
     272,   255,   228,   230,   239,   239,   282,   246,   175,     0,
      63,     0,   237,   238,     0,   233,   232,   242,   163,     0,
     162,   164,   231,   234,   235,   236,     0,   166,   165,   168,
     167
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -437,   496,  -437,  -437,  -437,  -329,  -437,  -437,  -437,  -437,
     437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,    52,    87,  -437,   137,   140,  -437,
    -437,   516,  -437,  -437,   517,  -437,   378,   207,  -437,  -437,
    -437,  -437,  -145,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,   364,   351,  -437,  -437,  -437,  -437,  -437,   446,
     -90,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -136,  -437,  -437,  -437,  -437,   152,   131,
     102,  -437,  -437,  -437,   340,  -437,   172,    17,  -437,     1,
      -1,  -437,  -437,  -437,     6,  -437,  -174,  -133,  -437,  -437,
      26,  -437,  -285,  -437,   122,  -152,  -437,  -437,  -437,  -437,
    -437,  -436,  -437,  -189,   354,  -279,  -437,  -172,   305,  -437,
     228,   141,   318,  -437,    33,   506,  -437,  -414,    56,   -41,
     132,   120,  -182,  -437,  -437,   413,  -155,  -437,   -98,   -15,
      -4,  -437,   598,  -437
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    29,    30,    31,    32,   311,    33,    34,   304,   381,
      79,   227,   445,    35,   312,   313,   499,   561,   532,   564,
     457,    36,   162,    89,   316,   235,   317,   318,   386,    37,
      38,   108,   178,    39,   115,   116,   117,   407,   467,    40,
      41,   185,   244,    42,    43,    44,    45,   448,   229,   306,
      46,   189,   190,   191,    47,   102,    48,   321,    49,   387,
     156,   324,    50,   442,   378,    51,   310,   600,   606,   527,
     455,   589,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,   138,    62,    63,   334,   248,   329,   330,   413,
     414,    64,    65,    66,    67,   287,   133,   544,   582,   583,
     595,   521,   522,   523,   551,   224,   171,   172,   483,   538,
     539,   513,   357,   424,   425,   238,   426,   481,   509,   566,
     435,   515,   367,   368,   206,   284,   365,   207,   359,   294,
     295,   208,   209,    73,   261,   145,   449,   360,   552,    75,
     477,   211,   251,   125,   219,   212,   213,   388,   214,   215,
     216,   123,    90,   217
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      74,    76,   222,   126,   221,    92,   253,   245,   170,   373,
     179,   176,   592,   122,   371,   485,   122,   122,   256,   375,
     285,   122,   122,   242,   476,   299,   356,   119,   356,   186,
     106,   356,   593,   119,   177,   196,    72,   302,   177,   259,
     250,   405,   158,   323,   184,    69,   293,   441,    68,   592,
     121,   487,   411,   128,   129,   545,   119,   107,   134,   135,
     305,   120,   177,   297,   175,   122,   458,   120,   194,   593,
     124,   406,   177,   198,   199,   122,   119,   146,   157,    76,
     547,   524,    92,   122,    92,   157,   249,   303,    72,   122,
     120,   146,    92,   463,   594,   307,    92,   187,    92,   286,
     300,    76,   142,    72,   335,   109,   322,    72,   188,   570,
     120,   198,   144,    72,   122,   177,   372,   292,   469,    72,
     160,   286,   196,    77,  -343,   396,   165,   110,   470,    91,
     110,   594,   220,    92,   155,   586,    72,   332,    72,   122,
     198,   163,   576,   474,   451,    72,   268,   111,   419,   333,
     111,   183,    78,    72,   379,   380,    72,   124,  -351,   177,
     198,   199,   366,   358,   452,   200,   210,    93,   202,   203,
     204,   104,   252,   252,   124,    72,   225,    92,   105,   205,
     112,   113,    72,   112,   113,   439,   479,   558,    92,   257,
     114,   550,   270,   114,    70,   480,   559,    72,   453,   118,
     293,   271,   560,    71,   272,   428,   159,   454,   161,   273,
     389,     9,    10,    72,   298,   533,   167,   297,   170,    72,
     173,   438,   174,   484,    92,   124,   122,   535,   314,   504,
     157,   132,    16,  -343,   131,    92,    92,    92,  -350,    92,
     281,   282,   137,   331,   274,   603,    20,   275,  -343,   283,
     139,   296,   276,   277,   278,   279,   280,   173,   604,   605,
     281,   282,   136,   309,   141,   341,    24,     9,    10,   339,
     143,     9,    10,   279,   280,    25,   398,   399,   281,   282,
     409,   410,  -351,  -351,   361,   180,    92,   361,    16,   382,
     431,   432,    16,   390,   505,   469,   587,   241,   510,   389,
     181,   173,    20,   182,   391,   598,    20,   170,   608,   218,
      92,   192,   173,   193,   226,   223,   228,   230,   503,   210,
     231,   232,    24,   529,   408,   233,    24,   236,   237,   234,
     239,    25,   408,    92,   361,    25,   488,   240,   489,   540,
     241,   243,   247,   177,   187,   188,   283,   288,   173,   289,
     122,   291,   122,   290,   567,   301,   297,   308,    24,   173,
     325,   326,    92,   327,   328,   416,   319,   599,   298,   336,
     361,   337,   314,   338,    92,   555,   342,   354,   270,   356,
     446,   565,   390,   374,   376,   377,   383,   423,   450,   427,
     272,   314,   392,   391,   394,   157,   540,   584,    92,   393,
      92,   465,   400,   268,   397,   296,   331,   269,   417,   395,
     369,   401,   403,   297,   297,   402,   546,   404,   430,   584,
     429,   574,   478,   440,   434,   361,   436,   444,   456,   447,
     274,   471,   475,   275,   369,   466,   297,   482,   276,   277,
     278,   279,   280,   491,   492,   494,   281,   282,   495,   270,
     416,   497,   496,   601,   498,   501,   511,   369,   271,    80,
     512,   272,   514,   607,   517,   252,   273,   361,   516,   530,
     609,   122,   478,   531,   534,   536,   537,   519,   543,   520,
     548,   549,   554,    81,  -350,   562,   433,    92,   194,   556,
     563,   526,   122,    92,   210,   568,   119,    82,   443,   557,
    -343,   274,   416,    83,   275,   569,   571,   541,   427,   276,
     277,   278,   279,   280,   578,   575,   580,   281,   282,   588,
     553,   252,   462,    84,   464,   591,   140,   610,   164,   528,
     120,    85,   195,   572,   493,   127,   460,   459,    86,   130,
     268,   254,   196,   418,   169,    87,   553,   577,   472,   260,
      92,   262,   361,    88,   263,   255,   264,   265,   266,   267,
     246,   168,   468,   590,   541,   585,   148,   149,   150,   151,
     152,   502,   461,   315,   153,   154,    72,   124,   197,   177,
     198,   199,   579,   553,   596,   200,   270,   585,   202,   203,
     204,   320,   602,   597,   581,   271,   370,   507,   272,   205,
     437,   166,   500,   273,   355,   268,   573,   258,   508,   103,
       0,   518,     0,     0,     0,   525,     0,   173,     0,     0,
     268,     0,   340,     0,     0,     0,     0,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   274,   268,
       0,   275,     0,   364,     0,     0,   276,   277,   278,   279,
     280,   270,     0,   421,   281,   282,     0,     0,     0,   422,
     271,     0,     0,   272,     0,     0,   270,     0,   273,     0,
       0,     0,     0,     0,   173,   271,     0,     0,   272,     0,
       0,     0,     0,   273,     0,   270,   415,     0,     0,     0,
       0,     0,     0,     0,   271,     0,   420,   272,     0,     0,
       0,     0,     0,   274,     0,     0,   275,     0,   194,     0,
       0,   276,   277,   278,   279,   280,   119,     0,   274,   281,
     282,   275,     0,     0,   506,     0,   276,   277,   278,   279,
     280,     0,     0,     0,   281,   282,   194,   274,     0,     0,
     275,     0,     0,     0,   119,   276,   277,   278,   279,   280,
     120,     0,   195,   281,   282,     0,     0,     0,     0,     0,
     194,     0,   196,     0,     0,     0,     0,     0,   119,     0,
       0,   415,     0,     0,     0,   473,     0,     0,   120,     0,
     195,     0,     0,     0,     0,     0,   486,     0,     0,     0,
     196,     0,     0,     0,   490,     0,    72,   124,   197,   177,
     198,   199,   120,     0,   195,   200,   362,     0,   202,   203,
     204,     0,     0,     0,   196,     0,     0,     0,     0,   205,
     363,     0,     0,   415,    72,   124,   197,   177,   198,   199,
       0,     0,     0,   200,   201,     0,   202,   203,   204,     0,
       0,     0,     0,     0,     0,     0,     0,   205,    72,   124,
     197,   177,   198,   199,     0,     0,     0,   200,   412,     1,
     202,   203,   204,     0,     0,     2,   542,     0,     0,     0,
       0,   205,     0,     0,     3,     0,     0,     0,     0,     4,
       5,    94,     6,     7,     8,     0,     0,   270,     9,    10,
       0,     0,     0,     0,    11,    12,    13,    14,     0,   272,
       0,     0,    15,     0,     0,    95,     0,     0,     0,    16,
       0,     0,     0,     0,     0,    17,    18,   270,    19,    96,
       0,     0,     0,    20,     0,    97,   271,     0,     0,   272,
       0,     0,   270,     0,    21,     0,     0,     0,     0,  -351,
      22,    23,   275,    24,   272,    98,     0,     0,   277,   278,
     279,   280,    25,    85,    26,   281,   282,     0,     0,     0,
      99,    27,     0,    28,     0,     0,     0,   100,     0,   274,
       0,     0,   275,     0,     0,   101,     0,   276,   277,   278,
     279,   280,   384,     0,     0,   281,   282,  -351,     0,     0,
       0,     0,     0,   277,   278,   279,   280,     0,     0,     0,
     281,   282,    72,   124,   168,   177,     0,   385,     0,   148,
     149,   150,   151,   152,    72,     0,   147,   153,   154,     0,
       0,   148,   149,   150,   151,   152,     0,     0,     0,   153,
     154
};

static const yytype_int16 yycheck[] =
{
       4,     5,   138,    18,   137,     9,   188,   181,    98,   294,
     108,     8,    15,    17,   293,   429,    20,    21,   192,   298,
      55,    25,    26,   175,    14,     5,    44,    29,    44,   127,
      16,    44,    35,    29,   112,    75,   109,    44,   112,   194,
     185,    47,    83,    64,    94,    93,   218,   376,    95,    15,
      17,   129,   331,    20,    21,   129,    29,    43,    25,    26,
     133,    63,   112,   218,   105,    69,   395,    63,    21,    35,
     110,    77,   112,   113,   114,    79,    29,    81,    82,    83,
     516,   495,    86,    87,    88,    89,   184,    94,   109,    93,
      63,    95,    96,    64,    97,   228,   100,     6,   102,   134,
      80,   105,    69,   109,   249,     8,   239,   109,    17,   545,
      63,   113,    79,   109,   118,   112,   134,   119,   134,   109,
      87,   134,    75,   104,   127,   314,    93,    33,   413,     9,
      33,    97,   136,   137,    82,   571,   109,    87,   109,   143,
     113,    89,   556,   422,    33,   109,    10,    53,   337,    99,
      53,   118,    19,   109,    90,    91,   109,   110,   111,   112,
     113,   114,    89,   119,    53,   118,   133,    44,   121,   122,
     123,    95,   187,   188,   110,   109,   143,   181,    51,   132,
      86,    87,   109,    86,    87,   119,   119,    49,   192,   193,
      96,   103,    56,    96,    95,   128,    58,   109,    87,    55,
     372,    65,    64,   104,    68,   357,    86,    96,    88,    73,
     308,    32,    33,   109,   218,   500,    96,   372,   308,   109,
     100,   373,   102,   119,   228,   110,   230,   506,   232,   119,
     234,    36,    53,   127,   104,   239,   240,   241,   132,   243,
     124,   125,   103,   247,   108,   111,    67,   111,   127,   128,
       0,   218,   116,   117,   118,   119,   120,   137,   124,   125,
     124,   125,   106,   230,   122,   269,    87,    32,    33,   133,
      70,    32,    33,   119,   120,    96,   133,   134,   124,   125,
     133,   134,   124,   125,   288,    76,   290,   291,    53,   304,
     133,   134,    53,   308,   133,   134,   133,   134,   480,   397,
      70,   181,    67,   134,   308,    66,    67,   397,   129,    88,
     314,    70,   192,    70,   103,   119,   132,    70,   470,   286,
      14,   132,    87,   497,   328,    14,    87,    30,   102,   132,
     132,    96,   336,   337,   338,    96,   434,   132,   436,   511,
     134,    50,   132,   112,     6,    17,   128,   127,   228,   132,
     354,   127,   356,   130,   536,    69,   511,    83,    87,   239,
     240,   241,   366,   243,    94,   332,    42,   128,   372,    44,
     374,    14,   376,   127,   378,   527,   108,    93,    56,    44,
     384,   533,   397,   127,    25,    25,   133,   354,   392,   356,
      68,   395,    97,   397,   133,   399,   568,   569,   402,    70,
     404,   405,    87,    10,   116,   372,   410,    14,   132,   134,
     290,   133,   133,   568,   569,   134,   514,   134,   133,   591,
     127,   554,   426,   116,   128,   429,   132,    97,    52,   103,
     108,   127,   134,   111,   314,   103,   591,    47,   116,   117,
     118,   119,   120,    94,    34,    14,   124,   125,   132,    56,
     417,   132,    94,   589,    12,    46,    20,   337,    65,     7,
      48,    68,   128,   599,   133,   480,    73,   471,   129,   116,
     606,   475,   476,    92,    72,   134,   129,   492,    74,   494,
      57,   133,   132,    31,   132,   116,   366,   491,    21,   127,
      13,   495,   496,   497,   461,   134,    29,    45,   378,   133,
     127,   108,   469,    51,   111,    20,   129,   511,   475,   116,
     117,   118,   119,   120,   116,    37,   129,   124,   125,    54,
     524,   536,   402,    71,   404,   134,    30,   122,    91,   496,
      63,    79,    65,   548,   447,    19,   399,   397,    86,    22,
      10,   190,    75,   336,    98,    93,   550,   562,   417,   195,
     554,   197,   556,   101,   200,   191,   202,   203,   204,   205,
     182,   111,   410,   578,   568,   569,   116,   117,   118,   119,
     120,   469,   400,   233,   124,   125,   109,   110,   111,   112,
     113,   114,   565,   587,   585,   118,    56,   591,   121,   122,
     123,   237,   591,   587,   568,    65,   291,   475,    68,   132,
     372,    95,   461,    73,   286,    10,   550,   194,   476,    11,
      -1,   491,    -1,    -1,    -1,   495,    -1,   497,    -1,    -1,
      10,    -1,   268,    -1,    -1,    -1,    -1,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   108,    10,
      -1,   111,    -1,   289,    -1,    -1,   116,   117,   118,   119,
     120,    56,    -1,   123,   124,   125,    -1,    -1,    -1,   129,
      65,    -1,    -1,    68,    -1,    -1,    56,    -1,    73,    -1,
      -1,    -1,    -1,    -1,   554,    65,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    73,    -1,    56,   332,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,   342,    68,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,   111,    -1,    21,    -1,
      -1,   116,   117,   118,   119,   120,    29,    -1,   108,   124,
     125,   111,    -1,    -1,   129,    -1,   116,   117,   118,   119,
     120,    -1,    -1,    -1,   124,   125,    21,   108,    -1,    -1,
     111,    -1,    -1,    -1,    29,   116,   117,   118,   119,   120,
      63,    -1,    65,   124,   125,    -1,    -1,    -1,    -1,    -1,
      21,    -1,    75,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      -1,   417,    -1,    -1,    -1,   421,    -1,    -1,    63,    -1,
      65,    -1,    -1,    -1,    -1,    -1,   432,    -1,    -1,    -1,
      75,    -1,    -1,    -1,   440,    -1,   109,   110,   111,   112,
     113,   114,    63,    -1,    65,   118,   119,    -1,   121,   122,
     123,    -1,    -1,    -1,    75,    -1,    -1,    -1,    -1,   132,
     133,    -1,    -1,   469,   109,   110,   111,   112,   113,   114,
      -1,    -1,    -1,   118,   119,    -1,   121,   122,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,   109,   110,
     111,   112,   113,   114,    -1,    -1,    -1,   118,   119,     3,
     121,   122,   123,    -1,    -1,     9,   512,    -1,    -1,    -1,
      -1,   132,    -1,    -1,    18,    -1,    -1,    -1,    -1,    23,
      24,     7,    26,    27,    28,    -1,    -1,    56,    32,    33,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    68,
      -1,    -1,    46,    -1,    -1,    31,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    59,    60,    56,    62,    45,
      -1,    -1,    -1,    67,    -1,    51,    65,    -1,    -1,    68,
      -1,    -1,    56,    -1,    78,    -1,    -1,    -1,    -1,   108,
      84,    85,   111,    87,    68,    71,    -1,    -1,   117,   118,
     119,   120,    96,    79,    98,   124,   125,    -1,    -1,    -1,
      86,   105,    -1,   107,    -1,    -1,    -1,    93,    -1,   108,
      -1,    -1,   111,    -1,    -1,   101,    -1,   116,   117,   118,
     119,   120,    89,    -1,    -1,   124,   125,   111,    -1,    -1,
      -1,    -1,    -1,   117,   118,   119,   120,    -1,    -1,    -1,
     124,   125,   109,   110,   111,   112,    -1,   114,    -1,   116,
     117,   118,   119,   120,   109,    -1,   111,   124,   125,    -1,
      -1,   116,   117,   118,   119,   120,    -1,    -1,    -1,   124,
     125
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,     3,     9,    18,    23,    24,    26,    27,    28,    32,
      33,    38,    39,    40,    41,    46,    53,    59,    60,    62,
      67,    78,    84,    85,    87,    96,    98,   105,   107,   136,
     137,   138,   139,   141,   142,   148,   156,   164,   165,   168,
     174,   175,   178,   179,   180,   181,   185,   189,   191,   193,
     197,   200,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   218,   219,   226,   227,   228,   229,    95,    93,
      95,   104,   109,   268,   285,   274,   285,   104,    19,   145,
       7,    31,    45,    51,    71,    79,    86,    93,   101,   158,
     287,   276,   285,    44,     7,    31,    45,    51,    71,    86,
      93,   101,   190,   287,    95,    51,    16,    43,   166,     8,
      33,    53,    86,    87,    96,   169,   170,   171,    55,    29,
      63,   269,   285,   286,   110,   278,   284,   166,   269,   269,
     169,   104,    36,   231,   269,   269,   106,   103,   217,     0,
     136,   122,   269,    70,   269,   270,   285,   111,   116,   117,
     118,   119,   120,   124,   125,   159,   195,   285,   274,   276,
     269,   276,   157,   159,   145,   269,   270,   276,   111,   194,
     195,   241,   242,   276,   276,   274,     8,   112,   167,   283,
      76,    70,   134,   269,    94,   176,   283,     6,    17,   186,
     187,   188,    70,    70,    21,    65,    75,   111,   113,   114,
     118,   119,   121,   122,   123,   132,   259,   262,   266,   267,
     269,   276,   280,   281,   283,   284,   285,   288,    88,   279,
     285,   242,   218,   119,   240,   269,   103,   146,   132,   183,
      70,    14,   132,    14,   132,   160,    30,   102,   250,   132,
     132,   134,   250,    50,   177,   241,   171,   132,   221,   283,
     177,   277,   284,   277,   188,   187,   241,   285,   280,   281,
     259,   269,   259,   259,   259,   259,   259,   259,    10,    14,
      56,    65,    68,    73,   108,   111,   116,   117,   118,   119,
     120,   124,   125,   128,   260,    55,   134,   230,   127,   132,
     130,   127,   119,   262,   264,   265,   269,   281,   285,     5,
      80,    69,    44,    94,   143,   133,   184,   242,    83,   269,
     201,   140,   149,   150,   285,   229,   159,   161,   162,    42,
     259,   192,   242,    64,   196,   276,   276,   276,    94,   222,
     223,   285,    87,    99,   220,   177,    44,    14,   127,   133,
     259,   285,   108,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,    93,   267,    44,   247,   119,   263,
     272,   285,   119,   133,   259,   261,    89,   257,   258,   276,
     263,   260,   134,   247,   127,   260,    25,    25,   199,    90,
      91,   144,   284,   133,    89,   114,   163,   194,   282,   283,
     284,   285,    97,    70,   133,   134,   258,   116,   133,   134,
      87,   133,   134,   133,   134,    47,    77,   172,   285,   133,
     134,   260,   119,   224,   225,   259,   269,   132,   172,   258,
     259,   123,   129,   269,   248,   249,   251,   269,   250,   127,
     133,   133,   134,   276,   128,   255,   132,   265,   250,   119,
     116,   140,   198,   276,    97,   147,   285,   103,   182,   271,
     285,    33,    53,    87,    96,   205,    52,   155,   140,   163,
     162,   231,   276,    64,   276,   285,   103,   173,   223,   134,
     247,   127,   224,   259,   260,   134,    14,   275,   285,   119,
     128,   252,    47,   243,   119,   272,   259,   129,   283,   283,
     259,    94,    34,   160,    14,   132,    94,   132,    12,   151,
     266,    46,   225,   250,   119,   133,   129,   249,   275,   253,
     277,    20,    48,   246,   128,   256,   129,   133,   276,   284,
     284,   236,   237,   238,   272,   276,   285,   204,   269,   241,
     116,    92,   153,   247,    72,   260,   134,   129,   244,   245,
     262,   285,   259,    74,   232,   129,   283,   256,    57,   133,
     103,   239,   273,   285,   132,   250,   127,   133,    49,    58,
      64,   152,   116,    13,   154,   250,   254,   277,   134,    20,
     256,   129,   284,   273,   242,    37,   272,   284,   116,   232,
     129,   245,   233,   234,   262,   285,   256,   133,    54,   206,
     284,   134,    15,    35,    97,   235,   235,   239,    66,   128,
     202,   218,   234,   111,   124,   125,   203,   218,   129,   218,
     122
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   135,   136,   136,   137,   137,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   139,   140,   141,   142,
     143,   143,   144,   144,   144,   145,   145,   146,   146,   147,
     147,   148,   149,   149,   150,   150,   151,   151,   152,   152,
     152,   153,   153,   154,   154,   155,   155,   156,   157,   158,
     158,   158,   159,   159,   159,   160,   161,   161,   162,   162,
     163,   163,   163,   163,   163,   164,   165,   166,   166,   166,
     167,   167,   167,   168,   169,   169,   169,   170,   170,   171,
     171,   171,   171,   171,   172,   172,   172,   173,   173,   174,
     175,   175,   176,   176,   177,   177,   178,   179,   180,   181,
     182,   182,   183,   183,   184,   185,   186,   186,   186,   186,
     186,   187,   188,   189,   190,   190,   190,   190,   190,   191,
     192,   192,   193,   194,   194,   195,   195,   195,   195,   195,
     195,   195,   196,   196,   196,   196,   197,   198,   198,   199,
     199,   201,   200,   202,   202,   202,   203,   203,   203,   204,
     204,   205,   205,   205,   205,   206,   206,   207,   208,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     210,   211,   212,   213,   214,   215,   215,   216,   217,   217,
     218,   218,   218,   218,   218,   218,   219,   220,   220,   221,
     221,   222,   222,   223,   224,   224,   225,   225,   225,   226,
     227,   228,   229,   230,   230,   231,   231,   231,   232,   232,
     233,   233,   234,   234,   235,   235,   235,   235,   235,   235,
     236,   236,   237,   238,   239,   239,   239,   240,   240,   241,
     242,   242,   243,   243,   244,   244,   245,   245,   246,   246,
     247,   247,   248,   248,   249,   249,   249,   250,   250,   251,
     251,   251,   252,   252,   253,   253,   254,   254,   255,   255,
     255,   256,   256,   256,   257,   257,   258,   258,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   259,   260,   260,
     260,   261,   261,   262,   262,   263,   263,   263,   264,   264,
     264,   265,   265,   265,   266,   266,   266,   267,   267,   267,
     268,   268,   269,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   280,   280,   280,   280,   281,
     282,   282,   283,   284,   285,   286,   286,   287,   288
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     7,     2,     2,     7,
       1,     1,     1,     1,     1,     1,     0,     2,     0,     3,
       0,    10,     1,     0,     3,     1,     3,     0,     1,     1,
       1,     3,     0,     3,     0,     4,     0,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     1,
       1,     1,     1,     1,     2,     3,     4,     1,     1,     0,
       1,     1,     0,     7,     2,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     2,     1,     0,     3,     6,
       4,     5,     1,     0,     2,     0,    10,     4,     3,    11,
       2,     0,     3,     2,     1,     3,     1,     1,     2,     2,
       0,     2,     2,     3,     1,     1,     1,     1,     1,     6,
       1,     0,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     9,     1,     0,     1,
       0,     0,    13,     1,     1,     3,     1,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     0,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       5,     2,     3,     3,     4,     1,     2,     3,     2,     0,
       1,     1,     1,     1,     1,     1,     5,     4,     4,     3,
       0,     3,     1,     2,     3,     1,     1,     3,     1,     4,
       6,    11,     9,     3,     0,     1,     3,     0,     3,     0,
       1,     3,     2,     2,     2,     2,     2,     1,     1,     0,
       1,     1,     5,     2,     1,     2,     0,     1,     0,     1,
       1,     3,     3,     0,     1,     3,     1,     1,     2,     0,
       2,     0,     3,     1,     3,     2,     1,     2,     0,     1,
       2,     2,     5,     3,     1,     0,     1,     0,     3,     4,
       0,     3,     4,     0,     1,     2,     2,     4,     2,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     3,     4,     3,     3,     3,     4,     2,     2,     1,
       4,     3,     4,     2,     2,     3,     3,     2,     4,     6,
       0,     1,     3,     3,     3,     1,     3,     3,     3,     1,
       1,     4,     2,     3,     3,     1,     1,     3,     1,     3,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
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
yyparse (void)
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
  case 2: /* queryblock: query queryblock  */
#line 217 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { parsetree = lcons((yyvsp[-1].node), parsetree); }
#line 2300 "y.tab.c"
    break;

  case 3: /* queryblock: query  */
#line 219 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { parsetree = lcons((yyvsp[0].node), NIL); }
#line 2306 "y.tab.c"
    break;

  case 5: /* query: stmt ';'  */
#line 223 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                {  (yyval.node) = (yyvsp[-1].node);  }
#line 2312 "y.tab.c"
    break;

  case 36: /* AddAttrStmt: ALTER TABLE relation_name opt_inh_star ADD COLUMN columnDef  */
#line 266 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    AddAttrStmt *n = makeNode(AddAttrStmt);
		    n->relname = (yyvsp[-4].str);
		    n->inh = (yyvsp[-3].boolean);
		    n->colDef = (yyvsp[0].coldef);
		    (yyval.node) = (Node *)n;
		}
#line 2324 "y.tab.c"
    break;

  case 37: /* columnDef: Id Typename  */
#line 276 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  
		    (yyval.coldef) = makeNode(ColumnDef);
		    (yyval.coldef)->colname = (yyvsp[-1].str);
		    (yyval.coldef)->typename = (yyvsp[0].typnam);
		}
#line 2334 "y.tab.c"
    break;

  case 38: /* ClosePortalStmt: CLOSE opt_id  */
#line 292 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  
		    ClosePortalStmt *n = makeNode(ClosePortalStmt);
		    n->portalname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 2344 "y.tab.c"
    break;

  case 39: /* CopyStmt: COPY opt_binary relation_name opt_with_copy copy_dirn copy_file_name copy_delimiter  */
#line 309 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    CopyStmt *n = makeNode(CopyStmt);
		    n->binary = (yyvsp[-5].boolean);
		    n->relname = (yyvsp[-4].str);
		    n->oids = (yyvsp[-3].boolean);
		    n->direction = (yyvsp[-2].ival);
		    n->filename = (yyvsp[-1].str);
		    n->delimiter = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 2359 "y.tab.c"
    break;

  case 40: /* copy_dirn: TO  */
#line 322 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.ival) = TO; }
#line 2365 "y.tab.c"
    break;

  case 41: /* copy_dirn: FROM  */
#line 324 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.ival) = FROM; }
#line 2371 "y.tab.c"
    break;

  case 42: /* copy_file_name: Sconst  */
#line 332 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = (yyvsp[0].str); }
#line 2377 "y.tab.c"
    break;

  case 43: /* copy_file_name: STDIN  */
#line 333 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = NULL; }
#line 2383 "y.tab.c"
    break;

  case 44: /* copy_file_name: STDOUT  */
#line 334 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = NULL; }
#line 2389 "y.tab.c"
    break;

  case 45: /* opt_binary: BINARY  */
#line 337 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.boolean) = TRUE; }
#line 2395 "y.tab.c"
    break;

  case 46: /* opt_binary: %empty  */
#line 338 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.boolean) = FALSE; }
#line 2401 "y.tab.c"
    break;

  case 47: /* opt_with_copy: WITH OIDS  */
#line 341 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.boolean) = TRUE; }
#line 2407 "y.tab.c"
    break;

  case 48: /* opt_with_copy: %empty  */
#line 342 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.boolean) = FALSE; }
#line 2413 "y.tab.c"
    break;

  case 49: /* copy_delimiter: USING DELIMITERS Sconst  */
#line 348 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str);}
#line 2419 "y.tab.c"
    break;

  case 50: /* copy_delimiter: %empty  */
#line 349 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                       { (yyval.str) = "\t"; }
#line 2425 "y.tab.c"
    break;

  case 51: /* CreateStmt: CREATE TABLE relation_name '(' OptTableElementList ')' OptInherit OptArchiveType OptLocation OptArchiveLocation  */
#line 362 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    CreateStmt *n = makeNode(CreateStmt);
		    n->relname = (yyvsp[-7].str);
		    n->tableElts = (yyvsp[-5].list);
		    n->inhRelnames = (yyvsp[-3].list);
		    n->archiveType = (yyvsp[-2].ival);
		    n->location = (yyvsp[-1].ival);
		    n->archiveLoc = (yyvsp[0].ival);
		    (yyval.node) = (Node *)n;
		}
#line 2440 "y.tab.c"
    break;

  case 52: /* OptTableElementList: tableElementList  */
#line 374 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[0].list); }
#line 2446 "y.tab.c"
    break;

  case 53: /* OptTableElementList: %empty  */
#line 375 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NULL; }
#line 2452 "y.tab.c"
    break;

  case 54: /* tableElementList: tableElementList ',' columnDef  */
#line 380 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].coldef)); }
#line 2458 "y.tab.c"
    break;

  case 55: /* tableElementList: columnDef  */
#line 382 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].coldef), NIL); }
#line 2464 "y.tab.c"
    break;

  case 56: /* OptArchiveType: ARCHIVE '=' archive_type  */
#line 386 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.ival) = (yyvsp[0].ival); }
#line 2470 "y.tab.c"
    break;

  case 57: /* OptArchiveType: %empty  */
#line 387 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.ival) = ARCH_NONE; }
#line 2476 "y.tab.c"
    break;

  case 58: /* archive_type: HEAVY  */
#line 390 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.ival) = ARCH_HEAVY; }
#line 2482 "y.tab.c"
    break;

  case 59: /* archive_type: LIGHT  */
#line 391 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.ival) = ARCH_LIGHT; }
#line 2488 "y.tab.c"
    break;

  case 60: /* archive_type: NONE  */
#line 392 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.ival) = ARCH_NONE; }
#line 2494 "y.tab.c"
    break;

  case 61: /* OptLocation: STORE '=' Sconst  */
#line 396 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.ival) = smgrin((yyvsp[0].str));  }
#line 2500 "y.tab.c"
    break;

  case 62: /* OptLocation: %empty  */
#line 398 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.ival) = -1;  }
#line 2506 "y.tab.c"
    break;

  case 63: /* OptArchiveLocation: ARCH_STORE '=' Sconst  */
#line 402 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.ival) = smgrin((yyvsp[0].str));  }
#line 2512 "y.tab.c"
    break;

  case 64: /* OptArchiveLocation: %empty  */
#line 404 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.ival) = -1;  }
#line 2518 "y.tab.c"
    break;

  case 65: /* OptInherit: INHERITS '(' relation_name_list ')'  */
#line 407 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.list) = (yyvsp[-1].list); }
#line 2524 "y.tab.c"
    break;

  case 66: /* OptInherit: %empty  */
#line 408 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.list) = NIL; }
#line 2530 "y.tab.c"
    break;

  case 67: /* DefineStmt: CREATE def_type def_rest  */
#line 420 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyvsp[0].dstmt)->defType = (yyvsp[-1].ival);
		    (yyval.node) = (Node *)(yyvsp[0].dstmt);
		}
#line 2539 "y.tab.c"
    break;

  case 68: /* def_rest: def_name definition  */
#line 427 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.dstmt) = makeNode(DefineStmt);
		    (yyval.dstmt)->defname = (yyvsp[-1].str);
		    (yyval.dstmt)->definition = (yyvsp[0].list);
		}
#line 2549 "y.tab.c"
    break;

  case 69: /* def_type: OPERATOR  */
#line 434 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = OPERATOR; }
#line 2555 "y.tab.c"
    break;

  case 70: /* def_type: Type  */
#line 435 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = P_TYPE; }
#line 2561 "y.tab.c"
    break;

  case 71: /* def_type: AGGREGATE  */
#line 436 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = AGGREGATE; }
#line 2567 "y.tab.c"
    break;

  case 75: /* definition: '(' def_list ')'  */
#line 443 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[-1].list); }
#line 2573 "y.tab.c"
    break;

  case 76: /* def_list: def_elem  */
#line 448 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].defelt), NIL); }
#line 2579 "y.tab.c"
    break;

  case 77: /* def_list: def_list ',' def_elem  */
#line 450 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].defelt)); }
#line 2585 "y.tab.c"
    break;

  case 78: /* def_elem: def_name '=' def_arg  */
#line 454 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.defelt) = makeNode(DefElem);
		    (yyval.defelt)->defname = (yyvsp[-2].str);
		    (yyval.defelt)->arg = (Node *)(yyvsp[0].node);
		}
#line 2595 "y.tab.c"
    break;

  case 79: /* def_elem: def_name  */
#line 460 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.defelt) = makeNode(DefElem);
		    (yyval.defelt)->defname = (yyvsp[0].str);
		    (yyval.defelt)->arg = (Node *)NULL;
		}
#line 2605 "y.tab.c"
    break;

  case 80: /* def_arg: Id  */
#line 467 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                {  (yyval.node) = (Node *)makeString((yyvsp[0].str)); }
#line 2611 "y.tab.c"
    break;

  case 81: /* def_arg: all_Op  */
#line 468 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                {  (yyval.node) = (Node *)makeString((yyvsp[0].str)); }
#line 2617 "y.tab.c"
    break;

  case 82: /* def_arg: NumConst  */
#line 469 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                {  (yyval.node) = (Node *)(yyvsp[0].value); /* already a Value */ }
#line 2623 "y.tab.c"
    break;

  case 83: /* def_arg: Sconst  */
#line 470 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                {  (yyval.node) = (Node *)makeString((yyvsp[0].str)); }
#line 2629 "y.tab.c"
    break;

  case 84: /* def_arg: SETOF Id  */
#line 471 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                { 
				   TypeName *n = makeNode(TypeName);
				   n->name = (yyvsp[0].str);
				   n->setof = TRUE;
				   n->arrayBounds = NULL;
				   (yyval.node) = (Node *)n;
				}
#line 2641 "y.tab.c"
    break;

  case 85: /* DestroyStmt: DROP TABLE relation_name_list  */
#line 489 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    DestroyStmt *n = makeNode(DestroyStmt);
		    n->relNames = (yyvsp[0].list);
		    (yyval.node) = (Node *)n;
		}
#line 2651 "y.tab.c"
    break;

  case 86: /* FetchStmt: FETCH opt_direction fetch_how_many opt_portal_name  */
#line 505 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    FetchStmt *n = makeNode(FetchStmt);
		    n->direction = (yyvsp[-2].ival);
		    n->howMany = (yyvsp[-1].ival);
		    n->portalname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
	        }
#line 2663 "y.tab.c"
    break;

  case 87: /* opt_direction: FORWARD  */
#line 514 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = FORWARD; }
#line 2669 "y.tab.c"
    break;

  case 88: /* opt_direction: BACKWARD  */
#line 515 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = BACKWARD; }
#line 2675 "y.tab.c"
    break;

  case 89: /* opt_direction: %empty  */
#line 516 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = FORWARD; /* default */ }
#line 2681 "y.tab.c"
    break;

  case 90: /* fetch_how_many: Iconst  */
#line 520 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
               { (yyval.ival) = (yyvsp[0].ival);
		 if ((yyvsp[0].ival) <= 0) elog(WARN,"Please specify nonnegative count for fetch"); }
#line 2688 "y.tab.c"
    break;

  case 91: /* fetch_how_many: ALL  */
#line 522 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = 0; /* 0 means fetch all tuples*/}
#line 2694 "y.tab.c"
    break;

  case 92: /* fetch_how_many: %empty  */
#line 523 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = 1; /*default*/ }
#line 2700 "y.tab.c"
    break;

  case 93: /* GrantStmt: GRANT privileges ON relation_name_list TO grantee opt_with_grant  */
#line 534 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
           {
		(yyval.node) = (Node*)makeAclStmt((yyvsp[-5].str),(yyvsp[-3].list),(yyvsp[-1].str),'+');
		free((yyvsp[-5].str));
		free((yyvsp[-1].str));
           }
#line 2710 "y.tab.c"
    break;

  case 94: /* privileges: ALL PRIVILEGES  */
#line 542 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		 (yyval.str) = aclmakepriv("rwaR",0);
		}
#line 2718 "y.tab.c"
    break;

  case 95: /* privileges: ALL  */
#line 546 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		 (yyval.str) = aclmakepriv("rwaR",0);
		}
#line 2726 "y.tab.c"
    break;

  case 96: /* privileges: operation_commalist  */
#line 549 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                 {
		(yyval.str) = (yyvsp[0].str);
		}
#line 2734 "y.tab.c"
    break;

  case 97: /* operation_commalist: operation  */
#line 554 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                               {
			(yyval.str) = aclmakepriv("",(yyvsp[0].chr));
			}
#line 2742 "y.tab.c"
    break;

  case 98: /* operation_commalist: operation_commalist ',' operation  */
#line 558 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        {
				(yyval.str) = aclmakepriv((yyvsp[-2].str),(yyvsp[0].chr));
				free((yyvsp[-2].str));
			}
#line 2751 "y.tab.c"
    break;

  case 99: /* operation: SELECT  */
#line 564 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                      {
		(yyval.chr) = ACL_MODE_RD_CHR;
		}
#line 2759 "y.tab.c"
    break;

  case 100: /* operation: INSERT  */
#line 567 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                     {
		(yyval.chr) = ACL_MODE_AP_CHR;
		}
#line 2767 "y.tab.c"
    break;

  case 101: /* operation: UPDATE  */
#line 570 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                     {
		(yyval.chr) = ACL_MODE_WR_CHR;
		}
#line 2775 "y.tab.c"
    break;

  case 102: /* operation: DELETE  */
#line 573 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                     {
		(yyval.chr) = ACL_MODE_WR_CHR;
		}
#line 2783 "y.tab.c"
    break;

  case 103: /* operation: RULE  */
#line 576 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                   {
		(yyval.chr) = ACL_MODE_RU_CHR;
		}
#line 2791 "y.tab.c"
    break;

  case 104: /* grantee: PUBLIC  */
#line 581 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                     {
		(yyval.str) = aclmakeuser("A","");
		}
#line 2799 "y.tab.c"
    break;

  case 105: /* grantee: GROUP Id  */
#line 584 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                       {
		(yyval.str) = aclmakeuser("G",(yyvsp[0].str));
		}
#line 2807 "y.tab.c"
    break;

  case 106: /* grantee: Id  */
#line 587 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                 {
		(yyval.str) = aclmakeuser("U",(yyvsp[0].str));
	 	}
#line 2815 "y.tab.c"
    break;

  case 108: /* opt_with_grant: WITH GRANT OPTION  */
#line 594 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
                    yyerror("WITH GRANT OPTION is not supported.  Only relation owners can set privileges");
                }
#line 2823 "y.tab.c"
    break;

  case 109: /* RevokeStmt: REVOKE privileges ON relation_name_list FROM grantee  */
#line 606 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
              {
		(yyval.node) = (Node*)makeAclStmt((yyvsp[-4].str),(yyvsp[-2].list),(yyvsp[0].str),'-');
		free((yyvsp[-4].str));
		free((yyvsp[0].str));
              }
#line 2833 "y.tab.c"
    break;

  case 110: /* MoveStmt: MOVE opt_direction opt_move_where opt_portal_name  */
#line 621 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    MoveStmt *n = makeNode(MoveStmt);
		    n->direction = (yyvsp[-2].ival);
		    n->to = FALSE;
		    n->where = (yyvsp[-1].ival);
		    n->portalname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 2846 "y.tab.c"
    break;

  case 111: /* MoveStmt: MOVE opt_direction TO Iconst opt_portal_name  */
#line 630 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    MoveStmt *n = makeNode(MoveStmt);
		    n->direction = (yyvsp[-3].ival);
		    n->to = TRUE;
		    n->where = (yyvsp[-1].ival);
		    n->portalname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 2859 "y.tab.c"
    break;

  case 112: /* opt_move_where: Iconst  */
#line 640 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = (yyvsp[0].ival); }
#line 2865 "y.tab.c"
    break;

  case 113: /* opt_move_where: %empty  */
#line 641 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.ival) = 1; /* default */ }
#line 2871 "y.tab.c"
    break;

  case 114: /* opt_portal_name: IN name  */
#line 644 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = (yyvsp[0].str);}
#line 2877 "y.tab.c"
    break;

  case 115: /* opt_portal_name: %empty  */
#line 645 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = NULL; }
#line 2883 "y.tab.c"
    break;

  case 116: /* IndexStmt: CREATE INDEX index_name ON relation_name USING access_method '(' index_params ')'  */
#line 661 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    /* should check that access_method is valid,
		       etc ... but doesn't */
		    IndexStmt *n = makeNode(IndexStmt);
		    n->idxname = (yyvsp[-7].str);
		    n->relname = (yyvsp[-5].str);
		    n->accessMethod = (yyvsp[-3].str);
		    n->indexParams = (yyvsp[-1].list);
		    n->withClause = NIL;
		    n->whereClause = NULL;
		    (yyval.node) = (Node *)n;
		}
#line 2900 "y.tab.c"
    break;

  case 117: /* ExtendStmt: EXTEND INDEX index_name where_clause  */
#line 683 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    ExtendStmt *n = makeNode(ExtendStmt);
		    n->idxname = (yyvsp[-1].str);
		    n->whereClause = (yyvsp[0].node);
		    (yyval.node) = (Node *)n;
		}
#line 2911 "y.tab.c"
    break;

  case 118: /* RecipeStmt: EXECUTE RECIPE recipe_name  */
#line 699 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    RecipeStmt *n;
		    if (!IsTransactionBlock())
			elog(WARN, "EXECUTE RECIPE may only be used in begin/end transaction blocks.");

		    n = makeNode(RecipeStmt);
		    n->recipeName = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 2925 "y.tab.c"
    break;

  case 119: /* ProcedureStmt: CREATE FUNCTION def_name def_args RETURNS def_arg opt_with_func AS Sconst LANGUAGE Sconst  */
#line 729 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    ProcedureStmt *n = makeNode(ProcedureStmt);
		    n->funcname = (yyvsp[-8].str);
		    n->defArgs = (yyvsp[-7].list);
		    n->returnType = (Node *)(yyvsp[-5].node);
		    n->withClause = (yyvsp[-4].list);
		    n->as = (yyvsp[-2].str);
		    n->language = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 2940 "y.tab.c"
    break;

  case 120: /* opt_with_func: WITH definition  */
#line 740 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[0].list); }
#line 2946 "y.tab.c"
    break;

  case 121: /* opt_with_func: %empty  */
#line 741 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NIL; }
#line 2952 "y.tab.c"
    break;

  case 122: /* def_args: '(' def_name_list ')'  */
#line 744 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[-1].list); }
#line 2958 "y.tab.c"
    break;

  case 123: /* def_args: '(' ')'  */
#line 745 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NIL; }
#line 2964 "y.tab.c"
    break;

  case 125: /* PurgeStmt: PURGE relation_name purge_quals  */
#line 761 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyvsp[0].pstmt)->relname = (yyvsp[-1].str);
		    (yyval.node) = (Node *)(yyvsp[0].pstmt);
		}
#line 2973 "y.tab.c"
    break;

  case 126: /* purge_quals: before_clause  */
#line 768 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.pstmt) = makeNode(PurgeStmt);
		    (yyval.pstmt)->beforeDate = (yyvsp[0].str);
		    (yyval.pstmt)->afterDate = NULL;
		}
#line 2983 "y.tab.c"
    break;

  case 127: /* purge_quals: after_clause  */
#line 774 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.pstmt) = makeNode(PurgeStmt);
		    (yyval.pstmt)->beforeDate = NULL;
		    (yyval.pstmt)->afterDate = (yyvsp[0].str);
		}
#line 2993 "y.tab.c"
    break;

  case 128: /* purge_quals: before_clause after_clause  */
#line 780 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.pstmt) = makeNode(PurgeStmt);
		    (yyval.pstmt)->beforeDate = (yyvsp[-1].str);
		    (yyval.pstmt)->afterDate = (yyvsp[0].str);
		}
#line 3003 "y.tab.c"
    break;

  case 129: /* purge_quals: after_clause before_clause  */
#line 786 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.pstmt) = makeNode(PurgeStmt);
		    (yyval.pstmt)->beforeDate = (yyvsp[0].str);
		    (yyval.pstmt)->afterDate = (yyvsp[-1].str);
		}
#line 3013 "y.tab.c"
    break;

  case 130: /* purge_quals: %empty  */
#line 792 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.pstmt) = makeNode(PurgeStmt);
		    (yyval.pstmt)->beforeDate = NULL;
		    (yyval.pstmt)->afterDate = NULL;
		}
#line 3023 "y.tab.c"
    break;

  case 131: /* before_clause: BEFORE date  */
#line 799 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 3029 "y.tab.c"
    break;

  case 132: /* after_clause: AFTER date  */
#line 800 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 3035 "y.tab.c"
    break;

  case 133: /* RemoveStmt: DROP remove_type name  */
#line 819 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    RemoveStmt *n = makeNode(RemoveStmt);
		    n->removeType = (yyvsp[-1].ival);
		    n->name = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 3046 "y.tab.c"
    break;

  case 134: /* remove_type: AGGREGATE  */
#line 827 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        {  (yyval.ival) = AGGREGATE; }
#line 3052 "y.tab.c"
    break;

  case 135: /* remove_type: Type  */
#line 828 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        {  (yyval.ival) = P_TYPE; }
#line 3058 "y.tab.c"
    break;

  case 136: /* remove_type: INDEX  */
#line 829 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        {  (yyval.ival) = INDEX; }
#line 3064 "y.tab.c"
    break;

  case 137: /* remove_type: RULE  */
#line 830 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        {  (yyval.ival) = RULE; }
#line 3070 "y.tab.c"
    break;

  case 138: /* remove_type: VIEW  */
#line 831 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        {  (yyval.ival) = VIEW; }
#line 3076 "y.tab.c"
    break;

  case 139: /* RemoveFuncStmt: DROP FUNCTION name '(' func_argtypes ')'  */
#line 835 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    RemoveFuncStmt *n = makeNode(RemoveFuncStmt);
		    n->funcname = (yyvsp[-3].str);
		    n->args = (yyvsp[-1].list);
		    (yyval.node) = (Node *)n;
	        }
#line 3087 "y.tab.c"
    break;

  case 140: /* func_argtypes: name_list  */
#line 843 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[0].list); }
#line 3093 "y.tab.c"
    break;

  case 141: /* func_argtypes: %empty  */
#line 844 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NIL; }
#line 3099 "y.tab.c"
    break;

  case 142: /* RemoveOperStmt: DROP OPERATOR all_Op '(' oper_argtypes ')'  */
#line 848 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    RemoveOperStmt *n = makeNode(RemoveOperStmt);
		    n->opname = (yyvsp[-3].str);
		    n->args = (yyvsp[-1].list);
		    (yyval.node) = (Node *)n;
		}
#line 3110 "y.tab.c"
    break;

  case 145: /* MathOp: '+'  */
#line 858 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        { (yyval.str) = "+"; }
#line 3116 "y.tab.c"
    break;

  case 146: /* MathOp: '-'  */
#line 859 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        { (yyval.str) = "-"; }
#line 3122 "y.tab.c"
    break;

  case 147: /* MathOp: '*'  */
#line 860 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        { (yyval.str) = "*"; }
#line 3128 "y.tab.c"
    break;

  case 148: /* MathOp: '/'  */
#line 861 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        { (yyval.str) = "/"; }
#line 3134 "y.tab.c"
    break;

  case 149: /* MathOp: '<'  */
#line 862 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        { (yyval.str) = "<"; }
#line 3140 "y.tab.c"
    break;

  case 150: /* MathOp: '>'  */
#line 863 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        { (yyval.str) = ">"; }
#line 3146 "y.tab.c"
    break;

  case 151: /* MathOp: '='  */
#line 864 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                        { (yyval.str) = "="; }
#line 3152 "y.tab.c"
    break;

  case 152: /* oper_argtypes: name  */
#line 868 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		   elog(WARN, "parser: argument type missing (use NONE for unary operators)");
		}
#line 3160 "y.tab.c"
    break;

  case 153: /* oper_argtypes: name ',' name  */
#line 872 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = makeList(makeString((yyvsp[-2].str)), makeString((yyvsp[0].str)), -1); }
#line 3166 "y.tab.c"
    break;

  case 154: /* oper_argtypes: NONE ',' name  */
#line 874 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = makeList(NULL, makeString((yyvsp[0].str)), -1); }
#line 3172 "y.tab.c"
    break;

  case 155: /* oper_argtypes: name ',' NONE  */
#line 876 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = makeList(makeString((yyvsp[-2].str)), NULL, -1); }
#line 3178 "y.tab.c"
    break;

  case 156: /* RenameStmt: ALTER TABLE relation_name opt_inh_star RENAME opt_column opt_name TO name  */
#line 889 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    RenameStmt *n = makeNode(RenameStmt);
		    n->relname = (yyvsp[-6].str);
		    n->inh = (yyvsp[-5].boolean);
		    n->column = (yyvsp[-2].str);
		    n->newname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 3191 "y.tab.c"
    break;

  case 157: /* opt_name: name  */
#line 899 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 3197 "y.tab.c"
    break;

  case 158: /* opt_name: %empty  */
#line 900 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = NULL; }
#line 3203 "y.tab.c"
    break;

  case 159: /* opt_column: COLUMN  */
#line 903 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = COLUMN; }
#line 3209 "y.tab.c"
    break;

  case 160: /* opt_column: %empty  */
#line 904 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = 0; }
#line 3215 "y.tab.c"
    break;

  case 161: /* $@1: %empty  */
#line 918 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
           { QueryIsRule=TRUE; }
#line 3221 "y.tab.c"
    break;

  case 162: /* RuleStmt: CREATE RULE name AS $@1 ON event TO event_object where_clause DO opt_instead OptStmtList  */
#line 921 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    RuleStmt *n = makeNode(RuleStmt);
		    n->rulename = (yyvsp[-10].str);
		    n->event = (yyvsp[-6].ival);
		    n->object = (yyvsp[-4].attr);
		    n->whereClause = (yyvsp[-3].node);
		    n->instead = (yyvsp[-1].boolean);
		    n->actions = (yyvsp[0].list);
		    (yyval.node) = (Node *)n;
		}
#line 3236 "y.tab.c"
    break;

  case 163: /* OptStmtList: NOTHING  */
#line 933 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.list) = NIL; }
#line 3242 "y.tab.c"
    break;

  case 164: /* OptStmtList: OptimizableStmt  */
#line 934 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.list) = lcons((yyvsp[0].node), NIL); }
#line 3248 "y.tab.c"
    break;

  case 165: /* OptStmtList: '[' OptStmtBlock ']'  */
#line 935 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.list) = (yyvsp[-1].list); }
#line 3254 "y.tab.c"
    break;

  case 166: /* OptStmtBlock: OptimizableStmt  */
#line 939 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].node), NIL); }
#line 3260 "y.tab.c"
    break;

  case 167: /* OptStmtBlock: OptimizableStmt ';'  */
#line 941 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[-1].node), NIL); }
#line 3266 "y.tab.c"
    break;

  case 168: /* OptStmtBlock: OptStmtBlock OptimizableStmt  */
#line 943 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
               {  (yyval.list) = lappend((yyvsp[-1].list), (yyvsp[0].node)); }
#line 3272 "y.tab.c"
    break;

  case 169: /* event_object: relation_name '.' attr_name  */
#line 947 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.attr) = makeNode(Attr);
		    (yyval.attr)->relname = (yyvsp[-2].str);
		    (yyval.attr)->paramNo = NULL;
		    (yyval.attr)->attrs = lcons(makeString((yyvsp[0].str)), NIL);
		    (yyval.attr)->indirection = NIL;
		}
#line 3284 "y.tab.c"
    break;

  case 170: /* event_object: relation_name  */
#line 955 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.attr) = makeNode(Attr);
		    (yyval.attr)->relname = (yyvsp[0].str);
		    (yyval.attr)->paramNo = NULL;
		    (yyval.attr)->attrs = NIL;
		    (yyval.attr)->indirection = NIL;
		}
#line 3296 "y.tab.c"
    break;

  case 171: /* event: SELECT  */
#line 965 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = CMD_SELECT; }
#line 3302 "y.tab.c"
    break;

  case 172: /* event: UPDATE  */
#line 966 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = CMD_UPDATE; }
#line 3308 "y.tab.c"
    break;

  case 173: /* event: DELETE  */
#line 967 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = CMD_DELETE; }
#line 3314 "y.tab.c"
    break;

  case 174: /* event: INSERT  */
#line 968 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = CMD_INSERT; }
#line 3320 "y.tab.c"
    break;

  case 175: /* opt_instead: INSTEAD  */
#line 971 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.boolean) = TRUE; }
#line 3326 "y.tab.c"
    break;

  case 176: /* opt_instead: %empty  */
#line 972 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.boolean) = FALSE; }
#line 3332 "y.tab.c"
    break;

  case 177: /* NotifyStmt: NOTIFY relation_name  */
#line 985 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    NotifyStmt *n = makeNode(NotifyStmt);
		    n->relname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 3342 "y.tab.c"
    break;

  case 178: /* ListenStmt: LISTEN relation_name  */
#line 993 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    ListenStmt *n = makeNode(ListenStmt);
		    n->relname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 3352 "y.tab.c"
    break;

  case 179: /* TransactionStmt: ABORT_TRANS TRANSACTION  */
#line 1015 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = ABORT_TRANS; 
		    (yyval.node) = (Node *)n;
		}
#line 3362 "y.tab.c"
    break;

  case 180: /* TransactionStmt: BEGIN_TRANS TRANSACTION  */
#line 1021 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = BEGIN_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3372 "y.tab.c"
    break;

  case 181: /* TransactionStmt: BEGIN_TRANS WORK  */
#line 1027 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = BEGIN_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3382 "y.tab.c"
    break;

  case 182: /* TransactionStmt: COMMIT WORK  */
#line 1033 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = END_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3392 "y.tab.c"
    break;

  case 183: /* TransactionStmt: END_TRANS TRANSACTION  */
#line 1039 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = END_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3402 "y.tab.c"
    break;

  case 184: /* TransactionStmt: ROLLBACK WORK  */
#line 1045 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = ABORT_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3412 "y.tab.c"
    break;

  case 185: /* TransactionStmt: ABORT_TRANS  */
#line 1052 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = ABORT_TRANS; 
		    (yyval.node) = (Node *)n;
		}
#line 3422 "y.tab.c"
    break;

  case 186: /* TransactionStmt: BEGIN_TRANS  */
#line 1058 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = BEGIN_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3432 "y.tab.c"
    break;

  case 187: /* TransactionStmt: COMMIT  */
#line 1064 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = END_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3442 "y.tab.c"
    break;

  case 188: /* TransactionStmt: END_TRANS  */
#line 1071 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = END_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3452 "y.tab.c"
    break;

  case 189: /* TransactionStmt: ROLLBACK  */
#line 1077 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    TransactionStmt *n = makeNode(TransactionStmt); 
		    n->command = ABORT_TRANS;
		    (yyval.node) = (Node *)n;
		}
#line 3462 "y.tab.c"
    break;

  case 190: /* ViewStmt: CREATE VIEW name AS RetrieveStmt  */
#line 1093 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    ViewStmt *n = makeNode(ViewStmt);
		    n->viewname = (yyvsp[-2].str);
		    n->query = (Query *)(yyvsp[0].node);
		    (yyval.node) = (Node *)n;
		}
#line 3473 "y.tab.c"
    break;

  case 191: /* LoadStmt: LOAD file_name  */
#line 1110 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    LoadStmt *n = makeNode(LoadStmt);
		    n->filename = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 3483 "y.tab.c"
    break;

  case 192: /* CreatedbStmt: CREATE DATABASE database_name  */
#line 1126 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    CreatedbStmt *n = makeNode(CreatedbStmt);
		    n->dbname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 3493 "y.tab.c"
    break;

  case 193: /* DestroydbStmt: DROP DATABASE database_name  */
#line 1142 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    DestroydbStmt *n = makeNode(DestroydbStmt);
		    n->dbname = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 3503 "y.tab.c"
    break;

  case 194: /* ClusterStmt: CLUSTER index_name ON relation_name  */
#line 1158 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		   ClusterStmt *n = makeNode(ClusterStmt);
		   n->relname = (yyvsp[0].str);
		   n->indexname = (yyvsp[-2].str);
		   (yyval.node) = (Node*)n;
		}
#line 3514 "y.tab.c"
    break;

  case 195: /* VacuumStmt: VACUUM  */
#line 1174 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
               {
                   (yyval.node) = (Node *)makeNode(VacuumStmt);
               }
#line 3522 "y.tab.c"
    break;

  case 196: /* VacuumStmt: VACUUM relation_name  */
#line 1178 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
               {
                   VacuumStmt *n = makeNode(VacuumStmt);
                   n->vacrel = (yyvsp[0].str);
                   (yyval.node) = (Node *)n;
               }
#line 3532 "y.tab.c"
    break;

  case 197: /* ExplainStmt: EXPLAIN explain_options OptimizableStmt  */
#line 1193 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    ExplainStmt *n = makeNode(ExplainStmt);
		    n->query = (Query*)(yyvsp[0].node);
		    n->options = (yyvsp[-1].list);
		    (yyval.node) = (Node *)n;
		}
#line 3543 "y.tab.c"
    break;

  case 198: /* explain_options: WITH name_list  */
#line 1202 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = (yyvsp[0].list); }
#line 3549 "y.tab.c"
    break;

  case 199: /* explain_options: %empty  */
#line 1204 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = NIL; }
#line 3555 "y.tab.c"
    break;

  case 206: /* AppendStmt: INSERT INTO relation_name opt_column_list insert_rest  */
#line 1235 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyvsp[0].astmt)->relname = (yyvsp[-2].str);
		    (yyvsp[0].astmt)->cols = (yyvsp[-1].list);
		    (yyval.node) = (Node *)(yyvsp[0].astmt);
                }
#line 3565 "y.tab.c"
    break;

  case 207: /* insert_rest: VALUES '(' exprList ')'  */
#line 1243 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.astmt) = makeNode(AppendStmt);
		    (yyval.astmt)->exprs = (yyvsp[-1].list);
		    (yyval.astmt)->fromClause = NIL;
		    (yyval.astmt)->whereClause = NULL;
		}
#line 3576 "y.tab.c"
    break;

  case 208: /* insert_rest: SELECT exprList from_clause where_clause  */
#line 1250 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.astmt) = makeNode(AppendStmt);
		    (yyval.astmt)->exprs = (yyvsp[-2].list);
		    (yyval.astmt)->fromClause = (yyvsp[-1].list);
		    (yyval.astmt)->whereClause = (yyvsp[0].node);
		}
#line 3587 "y.tab.c"
    break;

  case 209: /* opt_column_list: '(' columnList ')'  */
#line 1258 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[-1].list); }
#line 3593 "y.tab.c"
    break;

  case 210: /* opt_column_list: %empty  */
#line 1259 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NIL; }
#line 3599 "y.tab.c"
    break;

  case 211: /* columnList: columnList ',' columnElem  */
#line 1264 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].node)); }
#line 3605 "y.tab.c"
    break;

  case 212: /* columnList: columnElem  */
#line 1266 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].node), NIL); }
#line 3611 "y.tab.c"
    break;

  case 213: /* columnElem: Id opt_indirection  */
#line 1270 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    Ident *id = makeNode(Ident);
		    id->name = (yyvsp[-1].str);
		    id->indirection = (yyvsp[0].list);
		    (yyval.node) = (Node *)id;
		}
#line 3622 "y.tab.c"
    break;

  case 214: /* exprList: exprList ',' exprElem  */
#line 1279 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].node)); }
#line 3628 "y.tab.c"
    break;

  case 215: /* exprList: exprElem  */
#line 1281 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].node), NIL); }
#line 3634 "y.tab.c"
    break;

  case 216: /* exprElem: a_expr  */
#line 1286 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = (Node *)(yyvsp[0].node);  }
#line 3640 "y.tab.c"
    break;

  case 217: /* exprElem: relation_name '.' '*'  */
#line 1288 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    Attr *n = makeNode(Attr);
		    n->relname = (yyvsp[-2].str);
		    n->paramNo = NULL;
		    n->attrs = lcons(makeString("*"), NIL);
		    n->indirection = NIL;
		    (yyval.node) = (Node *)n;
		}
#line 3653 "y.tab.c"
    break;

  case 218: /* exprElem: '*'  */
#line 1297 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    Attr *n = makeNode(Attr);
		    n->relname = "*";
		    n->paramNo = NULL;
		    n->attrs = NIL;
		    n->indirection = NIL;
		    (yyval.node) = (Node *)n;
		}
#line 3666 "y.tab.c"
    break;

  case 219: /* DeleteStmt: DELETE FROM relation_name where_clause  */
#line 1317 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    DeleteStmt *n = makeNode(DeleteStmt);
		    n->relname = (yyvsp[-1].str);
		    n->whereClause = (yyvsp[0].node);
		    (yyval.node) = (Node *)n;
		}
#line 3677 "y.tab.c"
    break;

  case 220: /* ReplaceStmt: UPDATE relation_name SET res_target_list from_clause where_clause  */
#line 1337 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    ReplaceStmt *n = makeNode(ReplaceStmt);
		    n->relname = (yyvsp[-4].str);
		    n->targetList = (yyvsp[-2].list);
		    n->fromClause = (yyvsp[-1].list);
		    n->whereClause = (yyvsp[0].node);
		    (yyval.node) = (Node *)n;
                }
#line 3690 "y.tab.c"
    break;

  case 221: /* CursorStmt: DECLARE name opt_binary CURSOR FOR SELECT opt_unique res_target_list2 from_clause where_clause sort_clause  */
#line 1358 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    CursorStmt *n = makeNode(CursorStmt);

		    /* from PORTAL name */
		    /*
		     *  15 august 1991 -- since 3.0 postgres does locking
		     *  right, we discovered that portals were violating
		     *  locking protocol.  portal locks cannot span xacts.
		     *  as a short-term fix, we installed the check here. 
		     *				-- mao
		     */
		    if (!IsTransactionBlock())
			elog(WARN, "Named portals may only be used in begin/end transaction blocks.");

		    n->portalname = (yyvsp[-9].str);
		    n->binary = (yyvsp[-8].boolean);
		    n->unique = (yyvsp[-4].str);
		    n->targetList = (yyvsp[-3].list);
		    n->fromClause = (yyvsp[-2].list);
		    n->whereClause = (yyvsp[-1].node);
		    n->orderClause = (yyvsp[0].list);
		    (yyval.node) = (Node *)n;
		}
#line 3718 "y.tab.c"
    break;

  case 222: /* RetrieveStmt: SELECT opt_unique res_target_list2 result from_clause where_clause group_clause having_clause sort_clause  */
#line 1395 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    RetrieveStmt *n = makeNode(RetrieveStmt);
		    n->unique = (yyvsp[-7].str);
		    n->targetList = (yyvsp[-6].list);
		    n->into = (yyvsp[-5].str);
		    n->fromClause = (yyvsp[-4].list);
		    n->whereClause = (yyvsp[-3].node);
		    n->groupClause = (yyvsp[-2].list);
		    n->havingClause = (yyvsp[-1].node);
		    n->orderClause = (yyvsp[0].list);
		    (yyval.node) = (Node *)n;
		}
#line 3735 "y.tab.c"
    break;

  case 223: /* result: INTO TABLE relation_name  */
#line 1410 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.str)= (yyvsp[0].str);  /* should check for archive level */  }
#line 3741 "y.tab.c"
    break;

  case 224: /* result: %empty  */
#line 1412 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.str) = NULL;  }
#line 3747 "y.tab.c"
    break;

  case 225: /* opt_unique: DISTINCT  */
#line 1415 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                { (yyval.str) = "*"; }
#line 3753 "y.tab.c"
    break;

  case 226: /* opt_unique: DISTINCT ON Id  */
#line 1416 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                { (yyval.str) = (yyvsp[0].str); }
#line 3759 "y.tab.c"
    break;

  case 227: /* opt_unique: %empty  */
#line 1417 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                { (yyval.str) = NULL;}
#line 3765 "y.tab.c"
    break;

  case 228: /* sort_clause: ORDER BY sortby_list  */
#line 1420 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                        { (yyval.list) = (yyvsp[0].list); }
#line 3771 "y.tab.c"
    break;

  case 229: /* sort_clause: %empty  */
#line 1421 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NIL; }
#line 3777 "y.tab.c"
    break;

  case 230: /* sortby_list: sortby  */
#line 1425 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].sortby), NIL); }
#line 3783 "y.tab.c"
    break;

  case 231: /* sortby_list: sortby_list ',' sortby  */
#line 1427 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].sortby)); }
#line 3789 "y.tab.c"
    break;

  case 232: /* sortby: Id OptUseOp  */
#line 1431 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.sortby) = makeNode(SortBy);
		    (yyval.sortby)->name = (yyvsp[-1].str);
		    (yyval.sortby)->useOp = (yyvsp[0].str);
		}
#line 3799 "y.tab.c"
    break;

  case 233: /* sortby: attr OptUseOp  */
#line 1437 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
                  yyerror("parse error: use 'sort by attribute_name'");
                }
#line 3807 "y.tab.c"
    break;

  case 234: /* OptUseOp: USING Op  */
#line 1442 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = (yyvsp[0].str); }
#line 3813 "y.tab.c"
    break;

  case 235: /* OptUseOp: USING '<'  */
#line 1443 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = "<"; }
#line 3819 "y.tab.c"
    break;

  case 236: /* OptUseOp: USING '>'  */
#line 1444 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = ">"; }
#line 3825 "y.tab.c"
    break;

  case 237: /* OptUseOp: ASC  */
#line 1445 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = "<"; }
#line 3831 "y.tab.c"
    break;

  case 238: /* OptUseOp: DESC  */
#line 1446 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = ">"; }
#line 3837 "y.tab.c"
    break;

  case 239: /* OptUseOp: %empty  */
#line 1447 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = "<"; /*default*/ }
#line 3843 "y.tab.c"
    break;

  case 240: /* index_params: index_elem  */
#line 1451 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = lcons((yyvsp[0].ielem),NIL); }
#line 3849 "y.tab.c"
    break;

  case 241: /* index_params: func_index  */
#line 1452 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = lcons((yyvsp[0].ielem),NIL); }
#line 3855 "y.tab.c"
    break;

  case 242: /* func_index: name '(' name_list ')' opt_class  */
#line 1463 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.ielem) = makeNode(IndexElem);
		    (yyval.ielem)->name = (yyvsp[-4].str);
		    (yyval.ielem)->args = (yyvsp[-2].list);
		    (yyval.ielem)->class = (yyvsp[0].str);
		}
#line 3866 "y.tab.c"
    break;

  case 243: /* index_elem: attr_name opt_class  */
#line 1472 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.ielem) = makeNode(IndexElem);
		    (yyval.ielem)->name = (yyvsp[-1].str);
		    (yyval.ielem)->args = NIL;
		    (yyval.ielem)->class = (yyvsp[0].str);
		}
#line 3877 "y.tab.c"
    break;

  case 245: /* opt_class: WITH class  */
#line 1481 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = (yyvsp[0].str); }
#line 3883 "y.tab.c"
    break;

  case 246: /* opt_class: %empty  */
#line 1482 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = NULL; }
#line 3889 "y.tab.c"
    break;

  case 247: /* opt_inh_star: '*'  */
#line 1494 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.boolean) = TRUE; }
#line 3895 "y.tab.c"
    break;

  case 248: /* opt_inh_star: %empty  */
#line 1495 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.boolean) = FALSE; }
#line 3901 "y.tab.c"
    break;

  case 250: /* name_list: name  */
#line 1501 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list)=lcons(makeString((yyvsp[0].str)),NIL); }
#line 3907 "y.tab.c"
    break;

  case 251: /* name_list: name_list ',' name  */
#line 1503 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list)=lappend((yyvsp[-2].list),makeString((yyvsp[0].str))); }
#line 3913 "y.tab.c"
    break;

  case 252: /* group_clause: GROUP BY groupby_list  */
#line 1506 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[0].list); }
#line 3919 "y.tab.c"
    break;

  case 253: /* group_clause: %empty  */
#line 1507 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NIL; }
#line 3925 "y.tab.c"
    break;

  case 254: /* groupby_list: groupby  */
#line 1510 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = lcons((yyvsp[0].node), NIL); }
#line 3931 "y.tab.c"
    break;

  case 255: /* groupby_list: groupby_list ',' groupby  */
#line 1511 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].node)); }
#line 3937 "y.tab.c"
    break;

  case 256: /* groupby: Id  */
#line 1515 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		   Ident *n = makeNode(Ident);
		   n->name = (yyvsp[0].str);
		   n->indirection = NULL;
		   (yyval.node) = (Node*)n;
		}
#line 3948 "y.tab.c"
    break;

  case 257: /* groupby: attr  */
#line 1522 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		   (yyval.node) = (Node*)(yyvsp[0].attr);
		}
#line 3956 "y.tab.c"
    break;

  case 258: /* having_clause: HAVING a_expr  */
#line 1527 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 3962 "y.tab.c"
    break;

  case 259: /* having_clause: %empty  */
#line 1528 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.node) = NULL; }
#line 3968 "y.tab.c"
    break;

  case 260: /* from_clause: FROM from_list  */
#line 1539 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = (yyvsp[0].list); }
#line 3974 "y.tab.c"
    break;

  case 261: /* from_clause: %empty  */
#line 1540 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.list) = NIL; }
#line 3980 "y.tab.c"
    break;

  case 262: /* from_list: from_list ',' from_val  */
#line 1544 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].range)); }
#line 3986 "y.tab.c"
    break;

  case 263: /* from_list: from_val  */
#line 1546 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].range), NIL); }
#line 3992 "y.tab.c"
    break;

  case 264: /* from_val: relation_expr AS var_name  */
#line 1550 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.range) = makeNode(RangeVar);
		    (yyval.range)->relExpr = (yyvsp[-2].relexp);
		    (yyval.range)->name = (yyvsp[0].str);
		}
#line 4002 "y.tab.c"
    break;

  case 265: /* from_val: relation_expr var_name  */
#line 1556 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.range) = makeNode(RangeVar);
		    (yyval.range)->relExpr = (yyvsp[-1].relexp);
		    (yyval.range)->name = (yyvsp[0].str);
		}
#line 4012 "y.tab.c"
    break;

  case 266: /* from_val: relation_expr  */
#line 1562 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.range) = makeNode(RangeVar);
		    (yyval.range)->relExpr = (yyvsp[0].relexp);
		    (yyval.range)->name = NULL;
		}
#line 4022 "y.tab.c"
    break;

  case 267: /* where_clause: WHERE a_expr  */
#line 1569 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 4028 "y.tab.c"
    break;

  case 268: /* where_clause: %empty  */
#line 1570 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.node) = NULL;  /* no qualifiers */ }
#line 4034 "y.tab.c"
    break;

  case 269: /* relation_expr: relation_name  */
#line 1574 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    /* normal relations */
		    (yyval.relexp) = makeNode(RelExpr);
		    (yyval.relexp)->relname = (yyvsp[0].str);
		    (yyval.relexp)->inh = FALSE;
		    (yyval.relexp)->timeRange = NULL;
		}
#line 4046 "y.tab.c"
    break;

  case 270: /* relation_expr: relation_name '*'  */
#line 1582 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    /* inheiritance query */
		    (yyval.relexp) = makeNode(RelExpr);
		    (yyval.relexp)->relname = (yyvsp[-1].str);
		    (yyval.relexp)->inh = TRUE;
		    (yyval.relexp)->timeRange = NULL;
		}
#line 4058 "y.tab.c"
    break;

  case 271: /* relation_expr: relation_name time_range  */
#line 1590 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    /* time-qualified query */
		    (yyval.relexp) = makeNode(RelExpr);
		    (yyval.relexp)->relname = (yyvsp[-1].str);
		    (yyval.relexp)->inh = FALSE;
		    (yyval.relexp)->timeRange = (yyvsp[0].trange);
		}
#line 4070 "y.tab.c"
    break;

  case 272: /* time_range: '[' opt_range_start ',' opt_range_end ']'  */
#line 1601 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.trange) = makeNode(TimeRange);
		    (yyval.trange)->startDate = (yyvsp[-3].str);
		    (yyval.trange)->endDate = (yyvsp[-1].str);
		}
#line 4080 "y.tab.c"
    break;

  case 273: /* time_range: '[' date ']'  */
#line 1607 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.trange) = makeNode(TimeRange);
		    (yyval.trange)->startDate = (yyvsp[-1].str);
		    (yyval.trange)->endDate = NULL;
		}
#line 4090 "y.tab.c"
    break;

  case 275: /* opt_range_start: %empty  */
#line 1615 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = "epoch"; }
#line 4096 "y.tab.c"
    break;

  case 277: /* opt_range_end: %empty  */
#line 1619 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = "now"; }
#line 4102 "y.tab.c"
    break;

  case 278: /* opt_array_bounds: '[' ']' nest_array_bounds  */
#line 1623 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.list) = lcons(makeInteger(-1), (yyvsp[0].list)); }
#line 4108 "y.tab.c"
    break;

  case 279: /* opt_array_bounds: '[' Iconst ']' nest_array_bounds  */
#line 1625 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.list) = lcons(makeInteger((yyvsp[-2].ival)), (yyvsp[0].list)); }
#line 4114 "y.tab.c"
    break;

  case 280: /* opt_array_bounds: %empty  */
#line 1627 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.list) = NIL; }
#line 4120 "y.tab.c"
    break;

  case 281: /* nest_array_bounds: '[' ']' nest_array_bounds  */
#line 1631 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.list) = lcons(makeInteger(-1), (yyvsp[0].list)); }
#line 4126 "y.tab.c"
    break;

  case 282: /* nest_array_bounds: '[' Iconst ']' nest_array_bounds  */
#line 1633 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.list) = lcons(makeInteger((yyvsp[-2].ival)), (yyvsp[0].list)); }
#line 4132 "y.tab.c"
    break;

  case 283: /* nest_array_bounds: %empty  */
#line 1635 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  (yyval.list) = NIL; }
#line 4138 "y.tab.c"
    break;

  case 284: /* typname: name  */
#line 1639 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    char *tname = xlateSqlType((yyvsp[0].str));
		    (yyval.typnam) = makeNode(TypeName);
		    (yyval.typnam)->name = tname;

		    /* Is this the name of a complex type? If so, implement
		     * it as a set.
		     */
		    if (!strcmp(saved_relname, tname)) {
		 	/* This attr is the same type as the relation 
			 * being defined. The classic example: create
			 * emp(name=text,mgr=emp)
			 */
			(yyval.typnam)->setof = TRUE;
		    }else if (get_typrelid((Type)type(tname))
				!= InvalidOid) {
			 /* (Eventually add in here that the set can only 
			  * contain one element.)
			  */
			(yyval.typnam)->setof = TRUE;
	    	    } else {
			(yyval.typnam)->setof = FALSE;
		    }
		}
#line 4167 "y.tab.c"
    break;

  case 285: /* typname: SETOF name  */
#line 1664 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.typnam) = makeNode(TypeName);
		    (yyval.typnam)->name = (yyvsp[0].str);
		    (yyval.typnam)->setof = TRUE;
		}
#line 4177 "y.tab.c"
    break;

  case 286: /* Typename: typname opt_array_bounds  */
#line 1672 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    (yyval.typnam) = (yyvsp[-1].typnam);
		    (yyval.typnam)->arrayBounds = (yyvsp[0].list);
		}
#line 4186 "y.tab.c"
    break;

  case 287: /* Typename: name '(' Iconst ')'  */
#line 1677 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    /*
		     * The following implements char() and varchar().
		     * We do it here instead of the 'typname:' production
		     * because we don't want to allow arrays of varchar().
		     * I haven't thought about whether that will work or not.
		      *                             - ay 6/95
		     */
		    (yyval.typnam) = makeNode(TypeName);
		    if (!strcasecmp((yyvsp[-3].str), "char")) {
			(yyval.typnam)->name = "bpchar"; /*  strdup("bpchar"); */
		    } else if (!strcasecmp((yyvsp[-3].str), "varchar")) {
			(yyval.typnam)->name = "varchar"; /* strdup("varchar"); */
		    } else {
			yyerror("parse error");
		    }
		    if ((yyvsp[-1].ival) < 1) {
			elog(WARN, "length for '%s' type must be at least 1",
			     (yyvsp[-3].str));
		    } else if ((yyvsp[-1].ival) > 4096) {
			/* we can store a char() of length up to the size
			   of a page (8KB) - page headers and friends but
			   just to be safe here...  - ay 6/95 */
			elog(WARN, "length for '%s' type cannot exceed 4096",
			     (yyvsp[-3].str));
		    }
		    /* we actually implement this sort of like a varlen, so
		       the first 4 bytes is the length. (the difference
		       between this and "text" is that we blank-pad and 
		       truncate where necessary */
		    (yyval.typnam)->typlen = 4 + (yyvsp[-1].ival);
		}
#line 4223 "y.tab.c"
    break;

  case 288: /* a_expr: attr opt_indirection  */
#line 1719 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyvsp[-1].attr)->indirection = (yyvsp[0].list);
		    (yyval.node) = (Node *)(yyvsp[-1].attr);
		}
#line 4232 "y.tab.c"
    break;

  case 289: /* a_expr: AexprConst  */
#line 1724 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = (yyvsp[0].node);  }
#line 4238 "y.tab.c"
    break;

  case 290: /* a_expr: '-' a_expr  */
#line 1726 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "-", NULL, (yyvsp[0].node)); }
#line 4244 "y.tab.c"
    break;

  case 291: /* a_expr: a_expr '+' a_expr  */
#line 1728 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4250 "y.tab.c"
    break;

  case 292: /* a_expr: a_expr '-' a_expr  */
#line 1730 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4256 "y.tab.c"
    break;

  case 293: /* a_expr: a_expr '/' a_expr  */
#line 1732 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4262 "y.tab.c"
    break;

  case 294: /* a_expr: a_expr '*' a_expr  */
#line 1734 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4268 "y.tab.c"
    break;

  case 295: /* a_expr: a_expr '<' a_expr  */
#line 1736 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4274 "y.tab.c"
    break;

  case 296: /* a_expr: a_expr '>' a_expr  */
#line 1738 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, ">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4280 "y.tab.c"
    break;

  case 297: /* a_expr: a_expr '=' a_expr  */
#line 1740 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4286 "y.tab.c"
    break;

  case 298: /* a_expr: ':' a_expr  */
#line 1742 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, ":", NULL, (yyvsp[0].node)); }
#line 4292 "y.tab.c"
    break;

  case 299: /* a_expr: ';' a_expr  */
#line 1744 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, ";", NULL, (yyvsp[0].node)); }
#line 4298 "y.tab.c"
    break;

  case 300: /* a_expr: '|' a_expr  */
#line 1746 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "|", NULL, (yyvsp[0].node)); }
#line 4304 "y.tab.c"
    break;

  case 301: /* a_expr: AexprConst TYPECAST Typename  */
#line 1748 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    /* AexprConst can be either A_Const or ParamNo */
		    if (nodeTag((yyvsp[-2].node)) == T_A_Const) {
			((A_Const *)(yyvsp[-2].node))->typename = (yyvsp[0].typnam);
		    }else {
			((ParamNo *)(yyvsp[-2].node))->typename = (yyvsp[0].typnam);
		    }
		    (yyval.node) = (Node *)(yyvsp[-2].node);
		}
#line 4318 "y.tab.c"
    break;

  case 302: /* a_expr: CAST AexprConst AS Typename  */
#line 1758 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    /* AexprConst can be either A_Const or ParamNo */
		    if (nodeTag((yyvsp[-2].node)) == T_A_Const) {
			((A_Const *)(yyvsp[-2].node))->typename = (yyvsp[0].typnam);
		    }else {
			((ParamNo *)(yyvsp[-2].node))->typename = (yyvsp[0].typnam);
		    }
		    (yyval.node) = (Node *)(yyvsp[-2].node);
		}
#line 4332 "y.tab.c"
    break;

  case 303: /* a_expr: '(' a_expr ')'  */
#line 1768 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = (yyvsp[-1].node); }
#line 4338 "y.tab.c"
    break;

  case 304: /* a_expr: a_expr Op a_expr  */
#line 1770 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, (yyvsp[-1].str), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4344 "y.tab.c"
    break;

  case 305: /* a_expr: a_expr LIKE a_expr  */
#line 1772 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "~~", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4350 "y.tab.c"
    break;

  case 306: /* a_expr: a_expr NOT LIKE a_expr  */
#line 1774 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, "!~~", (yyvsp[-3].node), (yyvsp[0].node)); }
#line 4356 "y.tab.c"
    break;

  case 307: /* a_expr: Op a_expr  */
#line 1776 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, (yyvsp[-1].str), NULL, (yyvsp[0].node)); }
#line 4362 "y.tab.c"
    break;

  case 308: /* a_expr: a_expr Op  */
#line 1778 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OP, (yyvsp[0].str), (yyvsp[-1].node), NULL); }
#line 4368 "y.tab.c"
    break;

  case 309: /* a_expr: Id  */
#line 1780 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   /* could be a column name or a relation_name */
		    Ident *n = makeNode(Ident);
		    n->name = (yyvsp[0].str);
		    n->indirection = NULL;
		    (yyval.node) = (Node *)n;
		}
#line 4379 "y.tab.c"
    break;

  case 310: /* a_expr: name '(' '*' ')'  */
#line 1787 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    FuncCall *n = makeNode(FuncCall);
		    Ident *star = makeNode(Ident);

		    /* cheap hack for aggregate (eg. count) */
		    star->name = "oid"; 
		    n->funcname = (yyvsp[-3].str);
		    n->args = lcons(star, NIL);
		    (yyval.node) = (Node *)n;
		}
#line 4394 "y.tab.c"
    break;

  case 311: /* a_expr: name '(' ')'  */
#line 1798 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    FuncCall *n = makeNode(FuncCall);
		    n->funcname = (yyvsp[-2].str);
		    n->args = NIL;
		    (yyval.node) = (Node *)n;
		}
#line 4405 "y.tab.c"
    break;

  case 312: /* a_expr: name '(' expr_list ')'  */
#line 1805 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    FuncCall *n = makeNode(FuncCall);
		    n->funcname = (yyvsp[-3].str);
		    n->args = (yyvsp[-1].list);
		    (yyval.node) = (Node *)n;
		}
#line 4416 "y.tab.c"
    break;

  case 313: /* a_expr: a_expr ISNULL  */
#line 1812 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(ISNULL, NULL, (yyvsp[-1].node), NULL); }
#line 4422 "y.tab.c"
    break;

  case 314: /* a_expr: a_expr NOTNULL  */
#line 1814 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(NOTNULL, NULL, (yyvsp[-1].node), NULL); }
#line 4428 "y.tab.c"
    break;

  case 315: /* a_expr: a_expr AND a_expr  */
#line 1816 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(AND, NULL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4434 "y.tab.c"
    break;

  case 316: /* a_expr: a_expr OR a_expr  */
#line 1818 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(OR, NULL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 4440 "y.tab.c"
    break;

  case 317: /* a_expr: NOT a_expr  */
#line 1820 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = makeA_Expr(NOT, NULL, NULL, (yyvsp[0].node)); }
#line 4446 "y.tab.c"
    break;

  case 318: /* opt_indirection: '[' a_expr ']' opt_indirection  */
#line 1824 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    A_Indices *ai = makeNode(A_Indices);
		    ai->lidx = NULL;
		    ai->uidx = (yyvsp[-2].node);
		    (yyval.list) = lcons(ai, (yyvsp[0].list));
		}
#line 4457 "y.tab.c"
    break;

  case 319: /* opt_indirection: '[' a_expr ':' a_expr ']' opt_indirection  */
#line 1831 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    A_Indices *ai = makeNode(A_Indices);
		    ai->lidx = (yyvsp[-4].node);
		    ai->uidx = (yyvsp[-2].node);
		    (yyval.list) = lcons(ai, (yyvsp[0].list));
		}
#line 4468 "y.tab.c"
    break;

  case 320: /* opt_indirection: %empty  */
#line 1838 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.list) = NIL; }
#line 4474 "y.tab.c"
    break;

  case 321: /* expr_list: a_expr  */
#line 1842 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons((yyvsp[0].node), NIL); }
#line 4480 "y.tab.c"
    break;

  case 322: /* expr_list: expr_list ',' a_expr  */
#line 1844 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].node)); }
#line 4486 "y.tab.c"
    break;

  case 323: /* attr: relation_name '.' attrs  */
#line 1848 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.attr) = makeNode(Attr);
		    (yyval.attr)->relname = (yyvsp[-2].str);
		    (yyval.attr)->paramNo = NULL;
		    (yyval.attr)->attrs = (yyvsp[0].list);
		    (yyval.attr)->indirection = NULL;
		}
#line 4498 "y.tab.c"
    break;

  case 324: /* attr: ParamNo '.' attrs  */
#line 1856 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.attr) = makeNode(Attr);
		    (yyval.attr)->relname = NULL;
		    (yyval.attr)->paramNo = (yyvsp[-2].paramno);
		    (yyval.attr)->attrs = (yyvsp[0].list);
		    (yyval.attr)->indirection = NULL;
		}
#line 4510 "y.tab.c"
    break;

  case 325: /* attrs: attr_name  */
#line 1866 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lcons(makeString((yyvsp[0].str)), NIL); }
#line 4516 "y.tab.c"
    break;

  case 326: /* attrs: attrs '.' attr_name  */
#line 1868 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), makeString((yyvsp[0].str))); }
#line 4522 "y.tab.c"
    break;

  case 327: /* attrs: attrs '.' '*'  */
#line 1870 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { (yyval.list) = lappend((yyvsp[-2].list), makeString("*")); }
#line 4528 "y.tab.c"
    break;

  case 328: /* res_target_list: res_target_list ',' res_target_el  */
#line 1881 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.list) = lappend((yyvsp[-2].list),(yyvsp[0].target));  }
#line 4534 "y.tab.c"
    break;

  case 329: /* res_target_list: res_target_el  */
#line 1883 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.list) = lcons((yyvsp[0].target), NIL);  }
#line 4540 "y.tab.c"
    break;

  case 330: /* res_target_list: '*'  */
#line 1885 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    ResTarget *rt = makeNode(ResTarget);
		    Attr *att = makeNode(Attr);
		    att->relname = "*";
		    att->paramNo = NULL;
		    att->attrs = NULL;
		    att->indirection = NIL;
		    rt->name = NULL;
		    rt->indirection = NULL;
		    rt->val = (Node *)att;
		    (yyval.list) = lcons(rt, NIL);
		}
#line 4557 "y.tab.c"
    break;

  case 331: /* res_target_el: Id opt_indirection '=' a_expr  */
#line 1900 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.target) = makeNode(ResTarget);
		    (yyval.target)->name = (yyvsp[-3].str);
		    (yyval.target)->indirection = (yyvsp[-2].list);
		    (yyval.target)->val = (Node *)(yyvsp[0].node);
		}
#line 4568 "y.tab.c"
    break;

  case 332: /* res_target_el: attr opt_indirection  */
#line 1907 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.target) = makeNode(ResTarget);
		    (yyval.target)->name = NULL;
		    (yyval.target)->indirection = (yyvsp[0].list);
		    (yyval.target)->val = (Node *)(yyvsp[-1].attr);
		}
#line 4579 "y.tab.c"
    break;

  case 333: /* res_target_el: relation_name '.' '*'  */
#line 1914 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   
		    Attr *att = makeNode(Attr);
		    att->relname = (yyvsp[-2].str);
		    att->paramNo = NULL;
		    att->attrs = lcons(makeString("*"), NIL);
		    att->indirection = NIL;
		    (yyval.target) = makeNode(ResTarget);
		    (yyval.target)->name = NULL;
		    (yyval.target)->indirection = NULL;
		    (yyval.target)->val = (Node *)att;
		}
#line 4595 "y.tab.c"
    break;

  case 334: /* res_target_list2: res_target_list2 ',' res_target_el2  */
#line 1934 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.list) = lappend((yyvsp[-2].list), (yyvsp[0].target));  }
#line 4601 "y.tab.c"
    break;

  case 335: /* res_target_list2: res_target_el2  */
#line 1936 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.list) = lcons((yyvsp[0].target), NIL);  }
#line 4607 "y.tab.c"
    break;

  case 336: /* res_target_list2: '*'  */
#line 1938 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    ResTarget *rt = makeNode(ResTarget);
		    Attr *att = makeNode(Attr);
		    att->relname = "*";
		    att->paramNo = NULL;
		    att->attrs = NULL;
		    att->indirection = NIL;
		    rt->name = NULL;
		    rt->indirection = NULL;
		    rt->val = (Node *)att;
		    (yyval.list) = lcons(rt, NIL);
		}
#line 4624 "y.tab.c"
    break;

  case 337: /* res_target_el2: a_expr AS Id  */
#line 1954 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.target) = makeNode(ResTarget);
		    (yyval.target)->name = (yyvsp[0].str);
		    (yyval.target)->indirection = NULL;
		    (yyval.target)->val = (Node *)(yyvsp[-2].node);
		}
#line 4635 "y.tab.c"
    break;

  case 338: /* res_target_el2: a_expr  */
#line 1961 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.target) = makeNode(ResTarget);
		    (yyval.target)->name = NULL;
		    (yyval.target)->indirection = NULL;
		    (yyval.target)->val = (Node *)(yyvsp[0].node);
		}
#line 4646 "y.tab.c"
    break;

  case 339: /* res_target_el2: relation_name '.' '*'  */
#line 1968 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    Attr *att = makeNode(Attr);
		    att->relname = (yyvsp[-2].str);
		    att->paramNo = NULL;
		    att->attrs = lcons(makeString("*"), NIL);
		    att->indirection = NIL;
		    (yyval.target) = makeNode(ResTarget);
		    (yyval.target)->name = NULL;
		    (yyval.target)->indirection = NULL;
		    (yyval.target)->val = (Node *)att;
		}
#line 4662 "y.tab.c"
    break;

  case 340: /* opt_id: Id  */
#line 1981 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = (yyvsp[0].str); }
#line 4668 "y.tab.c"
    break;

  case 341: /* opt_id: %empty  */
#line 1982 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                                { (yyval.str) = NULL; }
#line 4674 "y.tab.c"
    break;

  case 342: /* relation_name: SpecialRuleRelation  */
#line 1986 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
                   (yyval.str) = (yyvsp[0].str);
                   strcpy(saved_relname, (yyvsp[0].str));
	        }
#line 4683 "y.tab.c"
    break;

  case 343: /* relation_name: Id  */
#line 1991 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    /* disallow refs to magic system tables */
  		    if (strcmp(LogRelationName, (yyvsp[0].str)) == 0
  		       || strcmp(VariableRelationName, (yyvsp[0].str)) == 0
  		       || strcmp(TimeRelationName, (yyvsp[0].str)) == 0
  		       || strcmp(MagicRelationName, (yyvsp[0].str)) == 0) {
			elog(WARN, "%s cannot be accessed by users", (yyvsp[0].str));
		    } else {
			(yyval.str) = (yyvsp[0].str);
		    }
		    strcpy(saved_relname, (yyvsp[0].str));
		}
#line 4700 "y.tab.c"
    break;

  case 344: /* database_name: Id  */
#line 2005 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4706 "y.tab.c"
    break;

  case 345: /* access_method: Id  */
#line 2006 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4712 "y.tab.c"
    break;

  case 346: /* attr_name: Id  */
#line 2007 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4718 "y.tab.c"
    break;

  case 347: /* class: Id  */
#line 2008 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4724 "y.tab.c"
    break;

  case 348: /* index_name: Id  */
#line 2009 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4730 "y.tab.c"
    break;

  case 349: /* var_name: Id  */
#line 2010 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4736 "y.tab.c"
    break;

  case 350: /* name: Id  */
#line 2011 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4742 "y.tab.c"
    break;

  case 351: /* date: Sconst  */
#line 2013 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4748 "y.tab.c"
    break;

  case 352: /* file_name: Sconst  */
#line 2014 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4754 "y.tab.c"
    break;

  case 353: /* recipe_name: Id  */
#line 2015 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4760 "y.tab.c"
    break;

  case 354: /* AexprConst: Iconst  */
#line 2018 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  
		    A_Const *n = makeNode(A_Const);
		    n->val.type = T_Integer;
		    n->val.val.ival = (yyvsp[0].ival);
		    (yyval.node) = (Node *)n;
		}
#line 4771 "y.tab.c"
    break;

  case 355: /* AexprConst: FCONST  */
#line 2025 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  
		    A_Const *n = makeNode(A_Const);
		    n->val.type = T_Float;
		    n->val.val.dval = (yyvsp[0].dval);
		    (yyval.node) = (Node *)n;
		}
#line 4782 "y.tab.c"
    break;

  case 356: /* AexprConst: Sconst  */
#line 2032 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {  
		    A_Const *n = makeNode(A_Const);
		    n->val.type = T_String;
		    n->val.val.str = (yyvsp[0].str);
		    (yyval.node) = (Node *)n;
		}
#line 4793 "y.tab.c"
    break;

  case 357: /* AexprConst: ParamNo  */
#line 2039 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {   (yyval.node) = (Node *)(yyvsp[0].paramno);  }
#line 4799 "y.tab.c"
    break;

  case 358: /* AexprConst: Pnull  */
#line 2041 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {	
		    A_Const *n = makeNode(A_Const);
		    n->val.type = T_Null;
		    (yyval.node) = (Node *)n;
		}
#line 4809 "y.tab.c"
    break;

  case 359: /* ParamNo: PARAM  */
#line 2049 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                {
		    (yyval.paramno) = makeNode(ParamNo);
		    (yyval.paramno)->number = (yyvsp[0].ival);
		}
#line 4818 "y.tab.c"
    break;

  case 360: /* NumConst: Iconst  */
#line 2055 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.value) = makeInteger((yyvsp[0].ival)); }
#line 4824 "y.tab.c"
    break;

  case 361: /* NumConst: FCONST  */
#line 2056 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.value) = makeFloat((yyvsp[0].dval)); }
#line 4830 "y.tab.c"
    break;

  case 362: /* Iconst: ICONST  */
#line 2059 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.ival) = (yyvsp[0].ival); }
#line 4836 "y.tab.c"
    break;

  case 363: /* Sconst: SCONST  */
#line 2060 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4842 "y.tab.c"
    break;

  case 364: /* Id: IDENT  */
#line 2062 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 4848 "y.tab.c"
    break;

  case 365: /* SpecialRuleRelation: CURRENT  */
#line 2065 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    if (QueryIsRule)
			(yyval.str) = "*CURRENT*";
		    else 
			elog(WARN,"CURRENT used in non-rule query");
		}
#line 4859 "y.tab.c"
    break;

  case 366: /* SpecialRuleRelation: NEW  */
#line 2072 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"
                { 
		    if (QueryIsRule)
			(yyval.str) = "*NEW*";
		    else 
			elog(WARN,"NEW used in non-rule query"); 
		}
#line 4870 "y.tab.c"
    break;


#line 4874 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2084 "/media/black/Data/Documents/Code/C/C_learn/dome/postgres95/src/backend/parser/gram.y"


static Node *makeA_Expr(int op, char *opname, Node *lexpr, Node *rexpr)
{
    A_Expr *a = makeNode(A_Expr);
    a->oper = op;
    a->opname = opname;
    a->lexpr = lexpr;
    a->rexpr = rexpr;
    return (Node *)a;
}

static char *
xlateSqlType(char *name)
{
    if (!strcasecmp(name,"int") ||
	!strcasecmp(name,"integer"))
	return "int4"; /* strdup("int4") --   strdup leaks memory here */
    else if (!strcasecmp(name, "smallint"))
	return "int2";
    else if (!strcasecmp(name, "float") ||
	     !strcasecmp(name, "real"))
	return "float4";
    else
	return name;
}

void parser_init(Oid *typev, int nargs)
{
    QueryIsRule = false;
    saved_relname[0]= '\0';

    param_type_init(typev, nargs);
}

