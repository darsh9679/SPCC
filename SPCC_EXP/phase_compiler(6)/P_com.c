#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LEN 100

// Stack structure for operands
typedef struct {
    int top;
    char items[MAX_EXPR_LEN][10]; // stack of strings
} Stack;

void push(Stack *s, const char *item) {
    if (s->top >= MAX_EXPR_LEN - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    strcpy(s->items[++(s->top)], item);
}

char* pop(Stack *s) {
    if (s->top < 0) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

void generateCode(char postfix[]) {
    Stack s;
    s.top = -1;
    char op1[10], op2[10], result[10];
    int tempVar = 1; // Temporary register counter

    printf("\nGenerated Assembly Code:\n");

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            // If it's an operand (letter or number), push it
            char operand[2] = {postfix[i], '\0'};
            push(&s, operand);
        } else {
            // It's an operator
            strcpy(op2, pop(&s));  // second operand
            strcpy(op1, pop(&s));  // first operand
            sprintf(result, "T%d", tempVar);  // temp result var name

            printf("MOV R%d, %s\n", tempVar, op1);
            switch (postfix[i]) {
                case '+': printf("ADD R%d, %s\n", tempVar, op2); break;
                case '-': printf("SUB R%d, %s\n", tempVar, op2); break;
                case '*': printf("MUL R%d, %s\n", tempVar, op2); break;
                case '/': printf("DIV R%d, %s\n", tempVar, op2); break;
                default:
                    printf("Invalid operator: %c\n", postfix[i]);
                    exit(1);
            }

            push(&s, result);
            tempVar++;
        }
    }

    printf("MOV RESULT, %s\n", pop(&s));
}

int main() {
    char postfix[MAX_EXPR_LEN];
    printf("Enter postfix expression: ");
    scanf("%s", postfix);
    generateCode(postfix);
    return 0;
}
