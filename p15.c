#include <stdio.h>
#include <string.h>

char input[100];
int i, error;

void E();
void Eprime();
void T();
void Tprime();
void F();

void E() {
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        i++;
        T();
        Eprime();
    }
    // Epsilon rule does nothing
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        i++;
        F();
        Tprime();
    }
    // Epsilon rule does nothing
}

void F() {
    if (input[i] == '(') {
        i++;
        E();
        if (input[i] == ')') {
            i++;
        } else {
            error = 1;
        }
    } else if (input[i] == 'i') {
        i++;
    } else {
        error = 1;
    }
}

int main() {
    // Printing the grammar exactly as expected
    printf("Grammar:\n");
    printf("E -> TE'\n");
    printf("E' -> +TE' | e\n");
    printf("T -> FT'\n");
    printf("T' -> *FT' | e\n");
    printf("F -> (E) | i\n\n");

    // Loop to take multiple inputs just like the handwritten output
    while(1) {
        i = 0;
        error = 0;
        printf("* Enter the input : ");
        if (scanf("%s", input) != 1) break;

        E();

        // Check if the whole string was read and no errors were found
        if (strlen(input) == i && error == 0) {
            printf("\nString is ACCEPTED\n\n");
        } else {
            printf("\nString is NOT ACCEPTED\n\n");
        }
    }
    return 0;
}



