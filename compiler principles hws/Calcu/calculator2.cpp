/* Simple integer arithmetic calculator according to the EBNF:
  <exp> → <term> { <addop> <term> }
  <addop> → + | -
  <term> → <factor> { <mulop> <factor> }
  <mulop> → *
  <factor> → ( <exp> ) | Number
  Inputs a line of text from stdin.
  Outputs “error” or the result.
*/

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

char token; /* global token variable */
/*function prototype for recursive calls*/
int exp(void);
int term(void);
int factor(void);

void error(void){
    fprintf(stderr, "error\n");
    exit(1);
}

void match(char expectedToken){
    if (token==expectedToken) {
        token = getchar();
        printf("match token: %c\n", token);
    }
    else
        error();
}

int exp(void){
    int temp=term();
    while ( (token=='+') || (token=='-') )
        switch (token){
            case '+':
                match ('+');
                temp+=term();
                break;
            case '-':
                match ('-');
                temp-=term();
                break;
        }
    return temp;
}

int term(void){
    int temp=factor();
    while (token=='*'){
        match('*');
        temp*=factor();
    }
    if (token=='/'){
        match('/');
        temp/=factor();
    }
    return temp;
}

int factor(void){
    int temp;
    if (token=='('){
        match ('(');
        temp = exp();
        match(')');
    }
    else if (token>=48 && token<=57){ // if (isdigit(token))
        ungetc(token,stdin);
        scanf("%d",&temp);
        token = fgetchar();
    } else
        error();
    return temp;
}

int main(){
    int result;
    FILE *fp;
    fp = freopen("C:\\Users\\99288\\Desktop\\Calcu\\file.txt","r",stdin);

    token=getchar(); /*load token with first character for lookahead*/
    while(token != '\n')
        result = exp();

    if (token=='\n')     /*check for end of line*/
        printf("Result = %d\n", result);
    else
        error();        /*extraneous chars on line*/

    fclose(fp);

    return 0;
}