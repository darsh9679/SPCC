#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    DELIMITER,
    ERROR
} TokenType;

const char *keywords[] = {
    "if", "else", "while", "for", "do", "break", "continue",
    "return", "int", "float", "char", "void"
};
const int nKeywords = sizeof(keywords) / sizeof(keywords[0]);

int isKeyword(const char *s) {
    for (int i = 0; i < nKeywords; i++)
        if (strcmp(s, keywords[i]) == 0)
            return 1;
    return 0;
}

void printToken(TokenType type, const char *lexeme) {
    const char *names[] = {
        "Keyword", "Identifier", "Number",
        "Operator", "Delimiter", "Error"
    };
    printf("Token: %-10s | Type: %s\n", lexeme, names[type]);
}

void tokenize(const char *input) {
    int i = 0, len = strlen(input), count = 0;
    char buf[100];

    while (i < len) {
        // Skip whitespace
        if (isspace((unsigned char)input[i])) {
            i++;
            continue;
        }
        int b = 0;

        // Identifier or keyword
        if (isalpha((unsigned char)input[i]) || input[i] == '_') {
            while (isalnum((unsigned char)input[i]) || input[i] == '_')
                buf[b++] = input[i++];
            buf[b] = '\0';
            printToken(isKeyword(buf) ? KEYWORD : IDENTIFIER, buf);
        }
        // Number (integers only)
        else if (isdigit((unsigned char)input[i])) {
            while (isdigit((unsigned char)input[i]))
                buf[b++] = input[i++];
            buf[b] = '\0';
            printToken(NUMBER, buf);
        }
        // Operators: ==, <=, >=, != or single + - * / = < > !
        else if (strchr("+-*/=<>!", input[i])) {
            char c = input[i];
            buf[b++] = input[i++];
            // check for two‑char operator
            if ((c == '=' || c=='<' || c=='>' || c=='!') && input[i] == '=') {
                buf[b++] = input[i++];
            }
            buf[b] = '\0';
            printToken(OPERATOR, buf);
        }
        // Delimiters
        else if (strchr("();{},", input[i])) {
            buf[b++] = input[i++];
            buf[b] = '\0';
            printToken(DELIMITER, buf);
        }
        // Anything else is an error token
        else {
            buf[b++] = input[i++];
            buf[b] = '\0';
            printToken(ERROR, buf);
        }
        count++;
    }

    printf("Total number of tokens: %d\n", count);
}

int main(void) {
    char input[1024];

    printf("Enter a line of code:\n");
    if (!fgets(input, sizeof(input), stdin)) {
        perror("fgets");
        return EXIT_FAILURE;
    }

    tokenize(input);
    return EXIT_SUCCESS;
}
