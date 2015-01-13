#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char token;

int exp();
int term();
int factor();

void error(){
    fprintf(stderr, "Error\n");
    exit(1);
}

void match(char expectedToken){
    if (token == expectedToken){
        token = getchar();
    }
    else{
        error();
    }
}

int main(){
    int result;
    token = getchar();

    result = exp();
    if (token == '\n'){
        printf("Result = %d\n", result);
    }
    else{
        error();
    }
	getchar();
    return 0;
}

int exp(){
    int temp = term();
    while((token == '+') || (token == '-')){
        switch(token){
            case '+':
                match('+');
                temp += term();
                break;
            case '-':
                match('-');
                temp -= term();
                break;
        }
    }
    return temp;
}

int term(){
    int temp = factor();
    while (token == '*') {
        match('*');
        temp *= factor();
    }
    return temp;
}

int factor(){
    int temp;
    if (token == '('){
        match('(');
        temp = exp();
        match(')');
    }
    else if(isdigit(token)){
        ungetc(token, stdin);
        scanf("%d", &temp);
        token = getchar();
    }
    else{
        error();
    }
    return temp;
}
