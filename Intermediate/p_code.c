/*lua's operator is more like p code*/
/* general code */

void genCode(SyntaxTree t){
    char codestr[CODESTR];

    if (t != NULL) {
        switch (t->kind){
            case OpKind:
                switch (t->op){
                    case Plus:
                        genCode(t->lchild);
                        genCode(t->rchild);
                        emitCode("adi");
                        break;
                    case Assign:
                        sprintf(codestr "%s %s", "lda", t->strval);
                        emitCode(codestr);
                        genCode(t->lchild);
                        emitCode("stn");
                        break;
                    default:
                        break;
                }
                break;
            case ConstK:
                sprint(codestr, "%s %s", "ldc", t->strval);
                emitCode(codestr);
                break;
            case IdKind:
                sprintf(codestr, "%s %s", "lod", t->strval);
                emitCode(codestr);
                break;
            default:
                emitCode(error);
                break;
        }
    }
}

void genCode(SyntaxTree t, int isAddr){
    char codestr[CODESTR];
    if(t != NULL){
        switch (t->kind){
            case OpKind:
                switch (t->op){
                    case Plus:
                        if (isAddr){
                            emitCode("error");
                        }
                        genCode(t->lchild, FALSE);
                        genCode(t->rchild, FALSE);
                        emitCode("Plus");
                    case Assign:
                        if (isAddr){
                            emitCode("error");
                        }
                        genCode(t->lchild, TRUE);
                        genCode(t->rchild, FALSE);
                        emitCode("stn");
                        break;
                    case Subs:
                        sprintf(codestr, "%s %s", "lda", t->strval);
                        emitCode(codestr);
                        genCode(t->lchild, FALSE);
                        sprintf(codestr, "%s %s(%s)", "ixa", "elem_size", t->strval);
                        emitCode(codestr);
                        if(isAddr == FALSE){
                            emitCode("ind 0");
                        }
                        break;
                }
            case ConstK:
                if (isAddr){
                    emitCode("error");
                }
                else{
                    sprintf(codestr, "%s %s", "ldc", t->strval);
                    emitCode(codestr);
                }
                break;
            case IdKind:
                if (isAddr){
                    sprintf(codestr, "%s %s", "lda", t->strval);
                }
                else{
                    sprintf(codestr, "%s %s", "lod", t->strval);
                }
                emitCode(codestr);
                break;
            default:
                emitCode("Error");
        }
    }
}

void genCode(SyntaxTree t, char *label){
    char codestr[CODESIZE];
    char *lab1, lab2;

    if (t != NULL) {
        switch (t->kind){
            case ExpKind:
                if (t->val == 0){
                    emitCode("ldc false");
                }
                else{
                    emitCode("ldc true");
                }
                break;
            case IfKind:
                genCode(t->child[0], label);
                lab1 = genLabel();
                sprintf(codestr, "%s %s", "fjp", lab1);
                emitCode(codestr);
                genCode(t->child[1], label);
                if (t->child[2] != NULL){
                    lab2 = genLabel();
                    sprintf(codestr, "%s %s", "ujp", lab2);
                    emitCode(codestr);
                }
                sprintf(codestr, "%s %s", "lab", lab1);
                emitCode(codestr);
                if (t->child[2] != NULL){
                    genCode(t->child[2], label);
                    sprintf(codestr, "%s %s", "lab", lab2);
                    emitCode(codestr);
                }
                break;
            case WhileKind:
                lab1 = genLabel();
                sprintf(codestr, "%s %s", "lab", lab1);
                emitCode(codestr);
                genCode(t->child[0], label);
                lab2 = genLabel();
                sprintf(codestr, "%s %s", "fjp", lab2);
                emitCode(codestr);
                genCode(t->child[1], lab2);
                sprintf(codestr, "%s %s", "ujp", lab1);
                emitCode(codestr);
                sprintf(codestr, "%s %s", "lab", lab2);
                emitCode(codestr);
                break;
            case BreakKind:
                sprintf(codestr, "%s %s", "ujp", label);
                emitCode(codestr);
                break;
            case OtherKind:
                emitCode("Other");
                break;
            default:
                emitCode("Error");
                break;
        }
    }
}
