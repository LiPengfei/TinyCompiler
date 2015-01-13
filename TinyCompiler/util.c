#include "globals.h"
#include "util.h"

void printToken(TokenType token, const char *tokenString){
    switch (token){
        case IF:
        case THEN:
        case ELSE:
        case END:
        case REPEAT:
        case UNTIL:
        case READ:
        case WRITE:
            fprintf(listing,
                    "reserved word: %s\n",
                    tokenString);
            break;

        case ASSIGN: fprintf(listing, ":=\n"); break;
        case LT: fprintf(listing, "<\n"); break;
        case EQ: fprintf(listing, "=\n"); break;
        case LPAREN: fprintf(listing, "(\n"); break;
        case RPAREN: fprintf(listing, ")\n"); break;
        case SEMI: fprintf(listing, ";\n"); break;
        case PLUS: fprintf(listing, "+\n"); break;
        case MINUS: fprintf(listing, "-\n"); break;
        case TIMES: fprintf(listing, "*\n"); break;
        case OVER: fprintf(listing, "/\n"); break;
        case ENDFILE: fprintf(listing, "EOF\n"); break;

        case NUM:
            fprintf(listing,
                    "NUM, val = %s\n",
                    tokenString);
            break;
        case ID:
            fprintf(listing,
                    "ID name = %s\n",
                    tokenString);
            break;
        case ERROR:
            fprint(listing,
                    "ERROR: %s\n",
                    tokenString);
            break;
    }
}

char *copyString(char *s){
    int n;
    char *t;
    if (NULL == s) return NULL;
    n = strlen(n) + 1;
    t = malloc(n);
    if (NULL = t){
        fprintf(listing,
                "Out of memory error at line %d\n",
                lineno);
    }
    else
        strcpy(t, s);

    return t;
}
