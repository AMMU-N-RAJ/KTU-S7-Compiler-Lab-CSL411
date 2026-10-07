                                                                                                                                                                                                                 
#include <stdio.h>
#include <string.h>

char input[20], stack[20];
int i = 0, j = 0, len = 0;

void check() {
    int k;

    // Check for handle E -> i
    for (k = 0; k < j; k++) {
        if (stack[k] == 'i') {
            stack[k] = 'E';
            stack[k + 1] = '\0';
            printf("\n%-15s | %-16s |", "", "reduce: E->i");
        }
    }

    // Check for handle E -> E+E
    for (k = 0; k < j - 2; k++) {
        if (stack[k] == 'E' && stack[k + 1] == '+' && stack[k + 2] == 'E') {
            stack[k] = 'E';
            stack[k + 1] = '\0';
            stack[k + 2] = '\0';
            j = j - 2; // Decrease stack pointer after reduction
            printf("\n%-15s | %-16s |", "", "reduce: E->E+E");
            check(); // Recursive call to check for new handles
            return;
        }
    }

    // Check for handle E -> E*E
    for (k = 0; k < j - 2; k++) {
        if (stack[k] == 'E' && stack[k + 1] == '*' && stack[k + 2] == 'E') {
            stack[k] = 'E';
            stack[k + 1] = '\0';
            stack[k + 2] = '\0';
            j = j - 2;
            printf("\n%-15s | %-16s |", "", "Reduce: E->E*E");
            check();
            return;
        }
    }

    // Check for handle E -> (E)
    for (k = 0; k < j - 2; k++) {
        if (stack[k] == '(' && stack[k + 1] == 'E' && stack[k + 2] == ')') {
            stack[k] = 'E';
            stack[k + 1] = '\0';
            stack[k + 2] = '\0';
            j = j - 2;
            printf("\n%-15s | %-16s |", "", "reduce: E->(E)");
            check();
            return;
        }
    }
}

int main() {
    // Print the grammar exactly as shown in the output image
    printf("Grammar:\n");
    printf("E -> E+E\n");
    printf("E -> E*E\n");
    printf("E -> (E)\n");
    printf("E -> i\n\n");

    printf("Enter the input string: ");
    scanf("%s", input);
    len = strlen(input);

    // Print table headers
    printf("\n%-15s | %-16s | %-10s\n", "Stack", "Input", "Action");
    printf("--------------------------------------------------\n");

    // Process the input string character by character
    for (i = 0; i < len; i++) {
        char stack_str[30], input_str[30];

        // Format the stack and input strings for printing before shifting
        if (j == 0) sprintf(stack_str, "stack:");
        else sprintf(stack_str, "Stack: %s", stack);

        sprintf(input_str, "input: %s", &input[i]);

        // Print the shift step
        printf("%-15s | %-16s | %-10s", stack_str, input_str, "Shift");

        // Perform Shift operation
        stack[j] = input[i];
        stack[j + 1] = '\0';
        j++;

        // Check for any possible reductions
        check();
        printf("\n--------------------------------------------------\n");
    }

    // Print the final state of the stack after input is consumed
    char stack_str[30], input_str[30];
    sprintf(stack_str, "Stack: %s", stack);
    sprintf(input_str, "Input:");
    printf("%-15s | %-16s | %-10s\n", stack_str, input_str, "");
    printf("--------------------------------------------------\n");

    // Check if the final stack contains only the start symbol 'E'
    if (stack[0] == 'E' && stack[1] == '\0') {
        printf("\nString Accepted\n");
    } else {
        printf("\nString Not Accepted\n");
    }

    return 0;
}
