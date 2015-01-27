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
}
