#include "globals.h"
#include "symtab.h"
#include "analyze.h"

static int location = 0;

static void traverse(TreeNode *t,
        void(*preProc)(TreeNode *),
        void(*postProc)(TreeNode *)){

    if (t != NULL){
        preProc(t);
        int i;
        for (i = 0; i < MAXCHILDREN; ++i) {
            traverse(t->child[i], preProc, postProc);
        }
        postProc(t);
        traverse(t->sibling, preProc, postProc);
    }
}

static void nullPorc(TreeNode *t){
    return;
}

static void insertNode(TreeNode *t){
    switch (t->nodekind) {
        case StmtK:
            switch (t->kind.stmt){
                case AssignK:
                case ReadK:
                    if (st_lookup(t->attr.name) == -1) {
                        st_insert(t->attr.name, t->lineno, location++);
                    }
                    else{
                        st_insert(t->attr.name, t->lineno, 0);
                    }
                    break;
                default:
                    break;
            }
            break;
        case ExpK:
            switch(t->kind.exp){
                case IdK:
                    if (st_lookup(t->attr.name) == -1) {
                        st_insert(t->attr.name, t->lineno, location++);
                    }
                    else{
                        st_insert(t->attr.name, t->lineno, 0);
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void buildSymtab(TreeNode * syntaxTree){
    traverse(syntaxTree, insertNode, nullPorc);
    if (TraceAnalyze) {
        fprintf(listing, "\nSymbol table:\n\n");
        printSymTab(listing);
    }
}

static void typeError(TreeNode *t, char *message){
    fprintf(listing, "Type error at line %d %s\n", t->lineno, message);
    Error = TRUE;
}

/***************************************************/
/*   it is called check, but also contains check   */
/***************************************************/
static void checkNode(TreeNode *t){
    switch (t->nodekind) {
        case StmtK:
            switch (t->kind.stmt){
                case IfK:
                    if (t->child[0]->type == Interger) {
                        typeError(t->child[0], "if test is not Boolean");
                    }
                    break;
                case AssignK:
                    if (t->child[0]->type != Interger) {
                        typeError(t->child[0], "assignment of non-interger value");
                    }
                    break;
                case WriteK:
                    break;
                case RepeatK:
					break;
                default:
                    break;
            }
            break;
        case ExpK:
            switch(t->kind.exp){
                case OpK:
                    if (t->child[0]->type != Interger ||
                            t->child[1]->type != Interger) {
                        typeError(t, "Op applied to non-interger");
                    }
                    if (t->attr.op == EQ || t->attr.op == LT) {
                        t->type = Boolean;
                    }
                    else{
                        t->type = Interger;
                    }
                    break;
                case ConstK:
                case IdK:
                    t->type = Interger;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}
