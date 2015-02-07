#include "globals.h"

#define NO_PARSE FALSE
#define NO_ANALYSE FALSE
#define NO_CODE FALSE

#include "util.h"

#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYSE
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif
#endif

int lineno = 0;
FILE *source;
FILE *listing;
FILE *code;

int EchoSource = TRUE;
int TraceScan = TRUE;
int TraceParse = TRUE;
int TraceAnalyze = TRUE;
int TraceCode = TRUE;

int Error = FALSE;

int main(int argc, const char *argv[]) {
    TreeNode *syntaxTree;
    char pgm[20];
    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename> \n", argv[0]);
        exit(1);
    }
    strcpy(pgm, argv[1]);
    if (strchr(pgm, '.') == NULL) {
        strcat(pgm, ".tny");
    }
    source = fopen(pgm, "r");
    if (source == NULL) {
        fprintf(stderr, "File %s not found\n", pgm);
        exit(1);
    }
    listing = stdout;
    fprintf(listing, "\nTINY COMPILATION: %s\n", pgm);
#if NO_PARSE
    while (getToken() != ENDFILE);
#else
    syntaxTree = parse();
    if (TraceParse) {
        fprintf(listing, "\nSyntax tree:\n");
        printTree(syntaxTree);
    }
#if !NO_ANALYSE
    if (!Error) {
        fprintf(listing, "\nBuilding Symbol Table ...\n");
        buildSymtab(syntaxTree);
        fprintf(listing, "\nChecking Types...\n");
        typeCheck(syntaxTree);
        fprintf(listing, "\nType Checking Finished\n");
    }
#if !NO_CODE
    if (!Error) {
        char *codefile;
        int fnlen = strcspn(pgm, ".");
        codefile = (char *) calloc(fnlen + 4, sizeof(char));
        strncpy(codefile, pgm, fnlen);
        strcat(codefile, ".tm");
        code = fopen(codefile, "w");
        if (code == NULL) {
            printf("Unable to open %s\n", codefile);
            exit(1);
        }
        codeGen(syntaxTree, codefile);
        fclose(code);
    }
#else
#endif
#endif
#endif
    fclose(source);
    return 0;
}
