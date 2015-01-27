#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 0
#endif

#define MAXRESERVED 8

typedef enum {
    ENDFILE, ERROR,
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,
    ID, NUM,
    ASSIGN, EQ, LT, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI
} TokenType;

extern FILE *source;
extern FILE *listing;
extern FILE *Code;

extern int lineno;

/***************************************************/
/**************syntax tree for parsing**************/
/***************************************************/
typedef enum { StmtK, ExpK } NodeKind;
typedef enum {IfK, RepeatK, AssignK, ReadK, WriteK} StmtKind;
typedef enum {OpK, ConstK, IdK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void, Interger, Boolean} ExpType;

#define MAXCHILDREN 3
typedef struct treeNode {
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    int lineno;
    NodeKind nodekind;
    union {StmtKind stmt; ExpKind exp;} kind;
    union {TokenType op; int val; char *name;} attr;
    ExpType type;  /* for type checking of exps*/
} TreeNode;

/***************************************************/
/***************Flags for tracing*******************/
/***************************************************/
extern int EchoSource;
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceCode;
extern int Error;

#endif
