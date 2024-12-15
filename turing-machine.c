
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLANK '_' // Define blank symbol
#define MAX_STATES 13
#define MAX_SYMBOLS 5

// Movement Directions
typedef enum { LEFT = -1,
               RIGHT = 1,
               HALT = 0,
               HANG = 0 } Direction;

// Transition Structure
typedef struct {
    int nextState;
    char writeSymbol;
    Direction moveDirection;
} Transition;

// State Structure
typedef struct {
    Transition transitions[MAX_SYMBOLS];
} State;

// Symbol Index Mapping: a -> 0, A -> 1, b -> 2, B -> 3, BLANK -> 4
int getSymbolIndex(char symbol) {
    switch (symbol) {
    case 'a':
        return 0;
    case 'A':
        return 1;
    case 'b':
        return 2;
    case 'B':
        return 3;
    case BLANK:
        return 4;
    default:
        return -1;
    }
}

// Initialize the Transition Table
void initializeStates(State states[]) {
    // q1 transitions
    states[1].transitions[0] = (Transition){2, 'A', RIGHT};   // a -> q2, A, R
    states[1].transitions[1] = (Transition){2, 'A', RIGHT};   // A -> q2, A, R
    states[1].transitions[2] = (Transition){7, 'B', RIGHT};   // b -> q7, B, R
    states[1].transitions[3] = (Transition){7, 'B', RIGHT};   // B -> q7, B, R
    states[1].transitions[4] = (Transition){-1, BLANK, HANG}; // BLANK -> Hang

    // q2 transitions
    states[2].transitions[0] = (Transition){2, 'a', RIGHT};   // a -> q2, a, R
    states[2].transitions[1] = (Transition){4, 'A', LEFT};    // A -> q4, A, R
    states[2].transitions[2] = (Transition){3, 'B', LEFT};    // b -> q3, B, L
    states[2].transitions[3] = (Transition){2, 'B', RIGHT};   // B -> q2, B, R
    states[2].transitions[4] = (Transition){4, BLANK, RIGHT}; // BLANK -> Hang

    // q3 transitions
    states[3].transitions[0] = (Transition){4, 'a', LEFT};    // a -> q4, a, L
    states[3].transitions[1] = (Transition){5, 'A', RIGHT};   // A -> q5, A, R
    states[3].transitions[2] = (Transition){-1, BLANK, HANG}; // b -> Hang
    states[3].transitions[3] = (Transition){3, 'B', LEFT};    // B -> q3, B, L
    states[3].transitions[4] = (Transition){-1, BLANK, HANG}; // BLANK -> Hang

    // q4 transitions
    states[4].transitions[0] = (Transition){4, 'a', LEFT};    // a -> q4, a, L
    states[4].transitions[1] = (Transition){1, 'A', RIGHT};   // A -> q1, A, R
    states[4].transitions[2] = (Transition){4, 'B', RIGHT};   // b -> q4, B, R
    states[4].transitions[3] = (Transition){1, 'B', RIGHT};   // B -> q1, B, R
    states[4].transitions[4] = (Transition){-1, BLANK, HALT}; // BLANK -> Halt

    // q5 transitions
    states[5].transitions[0] = (Transition){6, 'A', RIGHT};   // a -> q6, A, R
    states[5].transitions[1] = (Transition){-1, BLANK, HANG}; // A -> Hang
    states[5].transitions[2] = (Transition){6, 'B', RIGHT};   // b -> q6, B, R
    states[5].transitions[3] = (Transition){5, 'B', RIGHT};   // B -> q5, B, R
    states[5].transitions[4] = (Transition){-1, BLANK, HALT}; // BLANK -> Halt

    // q6 transitions
    states[6].transitions[0] = (Transition){6, 'A', RIGHT};   // a -> q6, A, R
    states[6].transitions[1] = (Transition){-1, BLANK, HANG}; // A -> Hang
    states[6].transitions[2] = (Transition){1, 'B', LEFT};    // b -> q1, B, L
    states[6].transitions[3] = (Transition){12, 'B', LEFT};   // B -> q12, B, L
    states[6].transitions[4] = (Transition){12, BLANK, LEFT}; // BLANK -> q12, BLANK, L

    // q7 transitions
    states[7].transitions[0] = (Transition){8, 'A', LEFT};    // a -> q8, A, L
    states[7].transitions[1] = (Transition){7, 'A', RIGHT};   // A -> q7, A, R
    states[7].transitions[2] = (Transition){7, 'b', RIGHT};   // b -> q7, b, R
    states[7].transitions[3] = (Transition){9, 'B', RIGHT};   // B -> q9, B, R
    states[7].transitions[4] = (Transition){9, BLANK, RIGHT}; // BLANK -> Hang

    // q8 transitions
    states[8].transitions[0] = (Transition){-1, BLANK, HANG}; // a -> Hang
    states[8].transitions[1] = (Transition){8, 'A', LEFT};    // A -> q8, A, L
    states[8].transitions[2] = (Transition){9, 'b', LEFT};    // b -> q9, b, L
    states[8].transitions[3] = (Transition){10, 'B', RIGHT};  // B -> q10, B, R
    states[8].transitions[4] = (Transition){-1, BLANK, HANG}; // BLANK -> Hang

    // q9 transitions
    states[9].transitions[0] = (Transition){9, 'A', RIGHT};   // a -> q9, A, R
    states[9].transitions[1] = (Transition){1, 'A', RIGHT};   // A -> q1, A, R
    states[9].transitions[2] = (Transition){9, 'b', LEFT};    // b -> q9, b, L
    states[9].transitions[3] = (Transition){1, 'B', RIGHT};   // B -> q1, B, R
    states[9].transitions[4] = (Transition){-1, BLANK, HALT}; // BLANK -> Halt

    // q10 transitions
    states[10].transitions[0] = (Transition){11, 'A', RIGHT};  // a -> q11, A, R
    states[10].transitions[1] = (Transition){10, 'A', RIGHT};  // A -> q10, A, R
    states[10].transitions[2] = (Transition){11, 'B', RIGHT};  // b -> q11, B, R
    states[10].transitions[3] = (Transition){-1, BLANK, HALT}; // BLANK -> Halt

    // q11 transitions
    states[11].transitions[0] = (Transition){1, 'A', LEFT};    // a -> q1, A, L
    states[11].transitions[1] = (Transition){12, 'A', LEFT};   // A -> q12, A, L
    states[11].transitions[2] = (Transition){11, 'B', RIGHT};  // b -> q11, B, R
    states[11].transitions[3] = (Transition){-1, BLANK, HANG}; // B -> Hang
    states[11].transitions[4] = (Transition){12, BLANK, LEFT}; // BLANK -> q12, BLANK, L

    // q12 transitions
    states[12].transitions[0] = (Transition){-1, BLANK, HANG}; // a -> Hang
    states[12].transitions[1] = (Transition){1, 'A', RIGHT};   // A -> q1, A, R
    states[12].transitions[2] = (Transition){-1, BLANK, HANG}; // b -> Hang
    states[12].transitions[3] = (Transition){1, 'B', RIGHT};   // B -> q1, B, R
    states[12].transitions[4] = (Transition){-1, BLANK, HALT}; // BLANK -> Halt
}

// Simulate the Turing Machine
int simulateTuringMachine(State states[], char tape[], int startState) {
    int currentState = startState;
    int head = 0;

    printf("Initial Tape: %s\n", tape);

    while (currentState != -1) { // -1 represents "Hang"
        char currentSymbol = tape[head];
        int symbolIndex = getSymbolIndex(currentSymbol);

        // print start state and reading symbol
        printf("State: q%d, Reading: %c\n", currentState, tape[head]);
        printf("Writing: %c\n", states[currentState].transitions[symbolIndex].writeSymbol);
        printf("Head: %d\n", head + 1);
        printf("Tape:\n%s\n", tape);

        for (int i = 0; i < head; i++) {
            printf(" ");
        }

        printf("^\n");

        printf("\n");

        if (symbolIndex == -1 || currentState >= MAX_STATES) {
            printf("Error: Invalid state or symbol encountered.\n");
            break;
        }

        Transition transition = states[currentState].transitions[symbolIndex];

        if (transition.moveDirection == HALT) {

            // if q1 reads a blank, hang and return
            if (currentState == 1 && currentSymbol == BLANK) {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 2 && currentSymbol == BLANK) {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 3 && (currentSymbol == 'b' || currentSymbol == BLANK)) {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 4 && currentSymbol == BLANK) {
                printf("Tape Accepted!\n");
                return 1;

            } else if (currentState == 5 && currentSymbol == BLANK) {
                printf("Tape Accepted!\n");
                return 1;

            } else if (currentState == 5 && currentSymbol == 'A') {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 6 && currentSymbol == 'A') {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 7 && currentSymbol == BLANK) {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 8 && (currentSymbol == 'a' || currentSymbol == BLANK)) {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 9 && currentSymbol == BLANK) {
                printf("Tape Accepted!\n");
                return 1;

            } else if (currentState == 10 && currentSymbol == BLANK) {
                printf("Tape Accepted!\n");
                return 1;

            } else if (currentState == 10 && currentSymbol == 'B') {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 11 && currentSymbol == 'B') {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;

            } else if (currentState == 12 && currentSymbol == BLANK) {
                printf("Tape Accepted!\n");
                return 1;

            } else if (currentState == 12 && (currentSymbol == 'a' || currentSymbol == 'A' || currentSymbol == 'b' || currentSymbol == 'B')) {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;
            } else {
                printf("Tape Rejected! Encountered Hang.\n");
                return 0;
            }

            // return 0;
        }

        // Perform transition
        tape[head] = transition.writeSymbol; // Write symbol
        currentState = transition.nextState; // Move to next state
        head += transition.moveDirection;    // Move head

        // Ensure head doesn't move out of tape bounds
        if (head < 0)
            head = 0;

        // printf("State: q%d, Reading: %c\n", currentState, tape[head]);
        // printf("Head: %d\n", head + 1);
        // printf("Tape:\n%s\n", tape);

        // for (int i = 0; i < head; i++) {
        //     printf(" ");
        // }

        // printf("^\n");

        // printf("\n");

        // printf("Current State: %d\n", currentState);
    }

    printf("Tape Rejected! Encountered Hang.\n");
    return 0;
}

void divider() {
    printf("\n");
    for (int i = 0; i < 40; i++) {
        printf("=");
    }
    printf("\n");
    printf("\n");
}

int main() {
    State states[MAX_STATES];
    initializeStates(states);
    int startState = 1; // Start at q1

    // Initialize tape
    // Equal
    printf("Tape 1 \n");
    char tape1[100] = "a_"; // Example tape 1

    if (simulateTuringMachine(states, tape1, startState)) {
        printf("Characters are Equal!\n");
    } else {
        printf("Characters are Not Equal!\n");
    }

    divider();

    // Initialize tape
    // Equal
    printf("Tape 2 \n");
    char tape2[100] = "ba___"; // Example tape 2
    if (simulateTuringMachine(states, tape2, startState)) {
        printf("Characters are Equal!\n");
    } else {
        printf("Characters are Not Equal!\n");
    }

    divider();

    // yawa

    // Not Equal
    printf("Tape 3 \n");
    char tape3[100] = "baaaabba___"; // Example tape 1

    if (simulateTuringMachine(states, tape3, startState)) {
        printf("Characters are Equal!\n");
    } else {
        printf("Characters are Not Equal!\n");
    }

    divider();

    // Initialize tape
    // Equal
    printf("Tape 4 \n");
    char tape4[100] = "bbaaaabbba___"; // Example tape 2
    if (simulateTuringMachine(states, tape4, startState)) {
        printf("Characters are Equal!\n");
    } else {
        printf("Characters are Not Equal!\n");
    }

    divider();

    // Initialize tape
    // Equal
    printf("Tape 5 \n");
    char tape5[100] = "abab___"; // Example tape 2
    if (simulateTuringMachine(states, tape5, startState)) {
        printf("Characters are Equal!\n");
    } else {
        printf("Characters are Not Equal!\n");
    }

    divider();

    // gcc -o turing-machine turing-machine.c

    return 0;
}
