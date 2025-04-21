#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// --- Token definitions ---
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_STAR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    int value;  // only valid for TOKEN_NUMBER
} Token;

// --- Globals for lexer/parser ---
const char *input;
int pos = 0;
Token current_token;

// --- Error handler ---
void error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

// --- Lexer: advance to next token ---
void next_token() {
    // skip whitespace
    while (isspace((unsigned char)input[pos])) pos++;

    char c = input[pos];
    if (isdigit((unsigned char)c)) {
        int val = 0;
        while (isdigit((unsigned char)input[pos])) {
            val = val * 10 + (input[pos++] - '0');
        }
        current_token.type  = TOKEN_NUMBER;
        current_token.value = val;
    }
    else if (c == '+') {
        pos++;
        current_token.type = TOKEN_PLUS;
    }
    else if (c == '*') {
        pos++;
        current_token.type = TOKEN_STAR;
    }
    else if (c == '(') {
        pos++;
        current_token.type = TOKEN_LPAREN;
    }
    else if (c == ')') {
        pos++;
        current_token.type = TOKEN_RPAREN;
    }
    else if (c == '\0') {
        current_token.type = TOKEN_END;
    }
    else {
        pos++;
        current_token.type = TOKEN_INVALID;
    }
}

// Forward declarations for recursive‑descent
int parse_expression();
int parse_term();
int parse_factor();

// expression := term { '+' term }
int parse_expression() {
    int result = parse_term();
    while (current_token.type == TOKEN_PLUS) {
        next_token();
        result += parse_term();
    }
    return result;
}

// term := factor { '*' factor }
int parse_term() {
    int result = parse_factor();
    while (current_token.type == TOKEN_STAR) {
        next_token();
        result *= parse_factor();
    }
    return result;
}

// factor := NUMBER | '(' expression ')'
int parse_factor() {
    if (current_token.type == TOKEN_NUMBER) {
        int val = current_token.value;
        next_token();
        return val;
    }
    else if (current_token.type == TOKEN_LPAREN) {
        next_token();  // consume '('
        int val = parse_expression();
        if (current_token.type != TOKEN_RPAREN)
            error("Expected ')'");
        next_token();  // consume ')'
        return val;
    }
    else {
        error("Expected number or '('");
        return 0;  // never reached
    }
}

// entry point: initialize and parse
int evaluate(const char *expr) {
    input = expr;
    pos = 0;
    next_token();
    int result = parse_expression();
    if (current_token.type != TOKEN_END)
        error("Unexpected input after end of expression");
    return result;
}

int main(void) {
    char buffer[256];
    printf("Enter an expression: ");
    if (!fgets(buffer, sizeof(buffer), stdin))
        return 0;
    int result = evaluate(buffer);
    printf("Result: %d\n", result);
    return 0;
}
