#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top == -1) return -1;
    return stack[top--];
}

int precedence(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int main() {
    char infix[100], postfix[100];
    int i, j = 0;

    // Exact input prompt from the reference
    printf("Enter an expression : ");
    scanf("%s", infix);

    // Infix to Postfix Conversion
    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop(); // Discard the '('
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';

    // Print postfix expression matching the handwritten format
    printf("\nPostfix expression:\n%s\n", postfix);

    // Postfix to Three Address Code (TAC) Conversion
    char opStack[100][10];
    int opTop = -1;
    int tCount = 1;

    printf("\nThree Address Code:\n");
    for (i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            // Push operand to stack as a string
            char tempStr[2] = {postfix[i], '\0'};
            strcpy(opStack[++opTop], tempStr);
        } else {
            char op2[10], op1[10];
            // Pop the top two operands
            strcpy(op2, opStack[opTop--]);
            strcpy(op1, opStack[opTop--]);

            // Print the TAC instruction
            printf("t%d = %s%c%s\n", tCount, op1, postfix[i], op2);

            // Push the temporary variable (e.g., t1) back onto the stack
            sprintf(opStack[++opTop], "t%d", tCount);
            tCount++;
        }
    }

    return 0;
}







