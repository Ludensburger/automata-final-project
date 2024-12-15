#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
#define BLANK '_'
#define Z_0 'Z'

typedef enum {
    q1,
    q2,
    q3
} State;

typedef struct {
    char stack[STACK_SIZE];
    int top;
} Stack;

void initializeStack(Stack *s) {
    s->top = -1;
}

void push(Stack *s, char value) {
    if (s->top < STACK_SIZE - 1) {
        s->stack[++s->top] = value;
    } else {
        printf("Stack overflow!\n");
        exit(1);
    }
}

char pop(Stack *s) {
    if (s->top >= 0) {
        return s->stack[s->top--];
    } else {
        printf("Stack underflow!\n");
        exit(1);
    }
}

char peek(Stack *s) {
    if (s->top >= 0) {
        return s->stack[s->top];
    } else {
        printf("Stack is empty!\n");
        exit(1);
    }
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void printStack(Stack *s) {

    printf("\n");
    printf("Stack (top to bottom):\n");
    for (int i = s->top; i >= 0; i--) {
        printf("| %c |\n", s->stack[i]);
    }

    // printf("\n");
}

int simulatePDA(char input[]) {
    State currentState = q1;
    Stack stack;
    initializeStack(&stack);

    int inputLength = strlen(input);
    int i = 0;

    while (i < inputLength) {
        char currentSymbol = input[i];

        // Print start state and reading symbol
        printf("====================================\n");
        printf("State: q%d, Reading: %c\n", currentState + 1, currentSymbol);
        printf("Head Position: %d\n", i + 1);
        printf("Tape:\n%s\n", input);

        for (int j = 0; j < i; j++) {
            printf(" ");
        }
        printf("^\n");

        switch (currentState) {

        case q1:
            // printf("IM IN Q1\n");
            if (currentSymbol == BLANK || currentSymbol == '_') {
                push(&stack, Z_0);
                // printf("Pushed Z_0 to stack\n");
                currentState = q2;
            } else {
                return 0; // Reject if the input does not start with '_'
            }
            break;

        case q2:
            // printf("IM IN Q2\n");
            // input is 0
            if (currentSymbol == '0') {

                // check top if it is Z_0
                if (peek(&stack) == Z_0 || peek(&stack) == currentSymbol) {
                    push(&stack, currentSymbol);
                    // printf("0 Pushed to stack\n");
                    currentState = q2;
                } else if (peek(&stack) == '1') {
                    pop(&stack);
                    // printf("1 Popped from stack\n");
                    currentState = q2;
                }

            }

            // input is 1
            else if (currentSymbol == '1') {
                // check top if it is Z_0
                if (peek(&stack) == Z_0 || peek(&stack) == currentSymbol) {
                    push(&stack, currentSymbol);
                    // printf("1 Pushed to stack\n");
                    currentState = q2;
                } else if (peek(&stack) == '0') {
                    pop(&stack);
                    // printf("0 Popped from stack\n");
                    currentState = q2;
                }
            }

            // input is _
            else if (currentSymbol == BLANK || currentSymbol == '_') {
                // debug print this is top
                printf("DEBUG: Top: %c\n", peek(&stack));

                if (peek(&stack) == Z_0 || peek(&stack) == currentSymbol) {
                    printf("Z remains. Stack is Empty\n");
                    currentState = q3;
                    return 1;

                } else if (peek(&stack) != Z_0) {
                    printf("Z_0 is not on top of stack\n");
                    return 0;
                }

                currentState = q3;
            }
            break;

        case q3:
            // printf("IM IN Q3\n");
            return 1; // Accept if we reach state q3

        default:
            return 0; // Reject if we reach an unknown state
        }

        i++;
        printStack(&stack); // Print the stack after each transition for debugging
    }

    return 0; // Reject if we reach the end of the input without accepting
}

int main() {

    char input1[] = "_00111_"; // First input string
    if (simulatePDA(input1)) {
        printf("TAPE 1 accepted!\n");
    } else {
        printf("TAPE 1 rejected!\n");
    }

    printf("\n");
    printf("\n");

    char input2[] = "_0101_"; // Second input string
    if (simulatePDA(input2)) {
        printf("TAPE 2 accepted!\n");
    } else {
        printf("TAPE 2 rejected!\n");
    }

    printf("\n");
    printf("\n");

    char input3[] = "_111000_"; // Third input string
    if (simulatePDA(input3)) {
        printf("TAPE 3 accepted!\n");
    } else {
        printf("TAPE 3 rejected!\n");
    }

    printf("\n");
    printf("\n");

    return 0;
}
