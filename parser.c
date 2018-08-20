#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

/* If we are compiling on Windows compile these functions */
#if defined(_WIN32)
#include <string.h>

#define BUFSIZ_ 2048
static char input[BUFSIZ_];

/* Fake readline function */
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, BUFSIZ_, stdin);
    char* cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

/* Fake add_history function */
void add_history(char* unused) { }

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#endif

/* int number_of_nodes(mpc_ast_t* t) { */
/*     int total = 1; */
/*     if (t->children_num >= 1) { */
/*         for (int i = 0; i < t->children_num; i++) { */
/*             total += number_of_nodes(t->children[i]); */
/*         } */
/*     } */
/*     return total; */
/* } */

long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    if (strcmp(op, "%") == 0) { return x % y; }
    if (strcmp(op, "^") == 0) { return pow(x, y); }
    if (strcmp(op, "min") == 0) {
        if (x < y) {
            return x;
        } else {
            return y;
        }
    }
    if (strcmp(op, "max") == 0) {
        if (x > y) {
            return x;
        } else {
            return y;
        }
    }
    return 0;
}

long eval(mpc_ast_t* t) {
    /* If tagged as number return it directly */
    if (strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    /* The operator is always second child */
    char* op = t->children[1]->contents;

    /* We store the third child in `x` */
    long x = eval(t->children[2]);

    /* Iterate the remaning children and combining. */
    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}

int main(int argc, char** argv) {

    /* Create some parsers */
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("lispy");

    /* Define them with the following language */
    mpca_lang(MPCA_LANG_DEFAULT,
      "                                                                    \
        number   : /-?[0-9]+/ ;                                            \
        operator : '+' | '-' | '*' | '/' | '%' | '^' | \"min\" | \"max\" ; \
        expr     : <number> | '(' <operator> <expr>+ ')' ;                 \
        lispy    : /^/ <operator> <expr>+ /$/ ;                            \
      ",
      Number, Operator, Expr, Lispy);

    puts("Lispy Version 0.0.0.0.3");
    puts("Press Ctrl+c to Exit\n");

    while (1) {

        /* Now in either case readline will be correctly defined */
        char* input = readline("lispy> ");
        add_history(input);

        /* Attempt to parse the user input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
        } else {
            /* Otherwise print the error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    /* Undefine and delete our parsers */
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}
