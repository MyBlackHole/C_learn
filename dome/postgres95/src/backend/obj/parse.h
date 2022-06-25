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

#line 335 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
