//
// Created by ceci on 2022/5/25.
//

#include "temp.h"
#include "parse.h"
#include "globals.h"
#include "scan.h"
#include "util.h"
#include <stdlib.h>

// FIRST(exp) = {number}
// FIRST(f') = {+, (}
// FIRST(f) = {number}

//exp: val
//f: val
//fp: inh, syn

static TokenType token; /* holds current token */

static void syntaxError(const char *message) {
    fprintf(listing, "\n>>> ");
    fprintf(listing, "Syntax error at line %d: %s", lineno, message);
    Error = TRUE;
}

static void match(TokenType expected) {
    if (token == expected) token = getToken();
    else {
        syntaxError("expected token -> ");
        printToken(expected, "none");
        syntaxError("but match unexpected token -> ");
        printToken(token, tokenString);
        fprintf(listing, "      ");
    }
}

int exp();
int fp(int i);
int f();

int exp() {
    int fp_inh, f_val, exp_val, fp_syn;
    if (token == NUM) {
        f_val = f();
        fp_inh = f_val;
        fp_syn = fp(fp_inh);
        exp_val = fp_syn;
        printf("result: %d", exp_val);
    } else {
        printf("error\n");
        exit(0);
    }
    return exp_val;
}

int fp(int i) {
    int f1p_inh, fp_inh, f_val, fp_syn, f1p_syn, exp_val;
    f1p_inh = i;
    if (token == PLUS) {
        match(token);
        f_val = f();
        f1p_inh = fp_inh + f_val;
        f1p_syn = fp(f1p_inh);
        fp_syn = f1p_syn;
    } else if (token == LPAREN) {
        match(LPAREN);
        exp_val = exp();
        match(RPAREN);
        fp_syn = exp_val;
    } else if (token == END){
        fp_syn = fp_inh;
    } else {
        printf("error\n");
        exit(0);
    }
    return fp_syn;
}

int f() {
    int f_val, number;
    if (token == NUM) {
        number = atoi(copyString(tokenString));
        f_val = number;
    }
    return f_val;
}
