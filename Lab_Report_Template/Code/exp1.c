#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define keyword_count 13
#define operator_count 7
#define symbol_count 17

char *keywords[20] = {"int", "float", "double", "char", "return", "switch", "for", "if",
                      "while", "do", "continue", "break", "goto"};
char operators[15] = {'+', '-', '*', '/', '^', '%', '='};
char symbols[25] = {';', ':', '{', '}', '(', ')', ',', '?', '+', '-', '*', '/', '^', '%', '=',
                   '[', ']'};

int isOperator(char s[]) {
        for(int i = 0; i < operator_count; i++) {
                if(operators[i] == s[0])
                        return 1;
        }
        return 0;
}

int isSymbol(char s[], int len) { 
        if(len == 1) {
                for(int i = 0; i < symbol_count; i++) {
                        if(symbols[i] == s[0])
                                return 1;
                }
        }
        return 0;
}

int isSymbolChar(char s) { 
        for(int i = 0; i < symbol_count; i++) {
                if(symbols[i] == s)
                        return 1;
        }
        return 0;
}

void preprocess(char *s, char **tokens, int *t_c) {
        int curr_len = 0;
        for(int i = 0; s[i] != '\0'; i++) {
                if(isSymbolChar(s[i])) {
                        tokens[*t_c][curr_len++] = '\0';

                        curr_len = 0;   (*t_c)++;

                        tokens[*t_c][curr_len++] = s[i];
                        tokens[*t_c][curr_len] = '\0';
                        curr_len = 0;   (*t_c)++;
                }

                else {
                        tokens[*t_c][curr_len++] = s[i];
                }
        }
        (*t_c)++;
        return;
}

int isKeyword(char s[]) {
        for(int i = 0; i < keyword_count; i++) {
                if(strcmp(keywords[i],s) == 0) {
                        return 1;
                }
        }
        return 0;
}

int isIdentifier(char s[]) {
        if(!isalpha(s[0]) && s[0] != '_') {
                return 0;
        }
        for(int i = 1; i < s[i] != '\0'; i++) {
                if(!isalpha(s[i]) && !isdigit(s[i]) && s[i] != '_') {
                        return 0;
                }
        }
        return 1;
}

int isLiteral(char s[], int len) {

        if(s[0] == '\'' && s[len-1] == '\'' || s[0] == '"' && s[len-1] == '"') {
                return 1;
        }
        else if(isdigit(s[0])) {
                for(int i = 0; s[i] != '\0'; i++) {
                        if(!isdigit(s[i])) {
                                return 0;
                        }
                }
                return 1;
        }
}

int main() {
        char **tokens = (char**)malloc(sizeof(char*)*50);
        for(int i = 0; i < 50; i++) {
                tokens[i] = (char*)malloc(sizeof(char)*10);
        }

        int token_count = 0;
        char s[100];
        FILE *fp = fopen("input.c", "r");

        while(fscanf(fp, "%s", s) == 1) {
                //preprocess the input line
                preprocess(s, tokens, &token_count);
        }

        for(int i = 0; i < token_count; i++) {
                if(isKeyword(tokens[i])) {
                        printf("< %s\t\t, keyword\t>\n", tokens[i]);
                }
                else if(isOperator(tokens[i])) {
                        printf("< %s\t\t, operator\t>\n", tokens[i]);
                }
                else if(isSymbol(tokens[i], strlen(tokens[i]))) {
                        printf("< %s\t\t, symbol\t>\n", tokens[i]);
                }
                else if(isLiteral(tokens[i], strlen(tokens[i]))) {
                        printf("< %s\t\t, literal\t>\n", tokens[i]);
                }
                else if(isIdentifier(tokens[i])) {
                        printf("< %s\t\t, identifier\t>\n", tokens[i]);
                }
        }
        return 0;
}
