 GNU nano 7.2                                                                                                                                                                                                                     p14.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n;
char prod[20][20];
char firstResult[20];
char followResult[20];
int visitedFollow[256];

// Function to add a character to a set only if it doesn't already exist
void addToSet(char set[], char val) {
    for (int i = 0; i < strlen(set); i++) {
        if (set[i] == val) return;
    }
    int len = strlen(set);
    set[len] = val;
    set[len + 1] = '\0';
}

// Recursive function to calculate the FIRST set
void findFirst(char c, char result[]) {
    // If it's a terminal, FIRST is the terminal itself
    if (!isupper(c)) {
        addToSet(result, c);
        return;
    }

    // Check all productions for the given non-terminal
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            if (prod[i][2] == '#') {
                addToSet(result, '#');
            } else {
                for (int j = 2; j < strlen(prod[i]); j++) {
                    char temp[20] = "";
                    findFirst(prod[i][j], temp);

                    int hasEpsilon = 0;
                    for (int k = 0; k < strlen(temp); k++) {
                        if (temp[k] == '#') hasEpsilon = 1;
                        else addToSet(result, temp[k]);
                    }

                    if (!hasEpsilon) break;

                    // If we reach the end and all previous derived epsilon, add epsilon
                    if (j == strlen(prod[i]) - 1 && hasEpsilon) {
                        addToSet(result, '#');
                    }
                }
            }
        }
    }
}

// Recursive function to calculate the FOLLOW set
void findFollow(char c, char result[]) {
    // Start symbol always contains '$' in its FOLLOW set
    if (prod[0][0] == c) {
        addToSet(result, '$');
    }

    // Prevent infinite recursion loops
    if (visitedFollow[c]) return;
    visitedFollow[c] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {
                if (j + 1 < strlen(prod[i])) {
                    int hasEpsilon = 1;
                    for (int k = j + 1; k < strlen(prod[i]); k++) {
                        char tempFirst[20] = "";
                        findFirst(prod[i][k], tempFirst);

                        hasEpsilon = 0;
                        for (int m = 0; m < strlen(tempFirst); m++) {
                            if (tempFirst[m] == '#') hasEpsilon = 1;
                            else addToSet(result, tempFirst[m]);
                        }
                        if (!hasEpsilon) break;
                    }
                    // If the remaining string can derive epsilon, add FOLLOW of LHS
                    if (hasEpsilon) {
                        char tempFollow[20] = "";
                        findFollow(prod[i][0], tempFollow);
                        for (int m = 0; m < strlen(tempFollow); m++) {
                            addToSet(result, tempFollow[m]);
                        }
                    }
                } else {
                    // If the symbol is at the end of the production, add FOLLOW of LHS
                    if (prod[i][0] != c) {
                        char tempFollow[20] = "";
                        findFollow(prod[i][0], tempFollow);
                        for (int m = 0; m < strlen(tempFollow); m++) {
                            addToSet(result, tempFollow[m]);
                        }
                    }
                }
            }
        }
    }
    visitedFollow[c] = 0; // Backtrack
}

// Function to print the sets matching the exact required format
void printSet(char set[]) {
    printf("{ ");
    for (int i = 0; i < strlen(set); i++) {
        printf("%c ", set[i]);
    }
    printf("}\n");
}

int main() {
    printf("Enter number of productions :");
    scanf("%d", &n);
    printf("Enter productions (Example: E=TR):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    char nt;
    // Loop to continuously process queries just like the handwritten output
    while (1) {
        printf("\nEnter the non-terminal to find FIRST and FOLLOW: ");
        if (scanf(" %c", &nt) != 1) break;

        memset(firstResult, 0, sizeof(firstResult));
        findFirst(nt, firstResult);
        printf("FIRST(%c)= ", nt);
        printSet(firstResult);

        memset(followResult, 0, sizeof(followResult));
        memset(visitedFollow, 0, sizeof(visitedFollow)); // Reset loop tracker
        findFollow(nt, followResult);
        printf("FOLLOW(%c)= ", nt);
        printSet(followResult);
    }
    return 0;
}
