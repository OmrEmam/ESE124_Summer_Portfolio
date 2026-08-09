#include <stdio.h>

int main(void) {
    // Variables to store the current input and the immediately preceding input
    int current, previous;
    
    // Flag to track whether at least one number has been entered previously (0 = false, 1 = true)
    int has_previous = 0;
    
    // Counters to keep track of positive numbers, negative numbers, and zeros
    int positiveCount = 0, negativeCount = 0, zeroCount = 0;

    // Infinite loop to continuously accept and process user inputs
    while (1) {
        // Prompt the user to enter an integer and read the input
        printf("Enter an integer: ");
        scanf("%d", &current);

        // Classify the input and increment the corresponding counter
        if (current > 0) {
            positiveCount++;
        } else if (current < 0) {
            negativeCount++;
        } else {
            zeroCount++;
        }

        // Termination condition: exit the loop if the current number equals the previous number
        if (has_previous && current == previous) {
            break;
        }

        // Save the current input as the previous input for the next iteration
        previous = current;
        // Mark that a previous input now exists
        has_previous = 1;
    }

    // Output the final count for each category
    printf("Positive: %d\n", positiveCount);
    printf("Negative: %d\n", negativeCount);
    printf("Zero: %d\n", zeroCount);

    return 0;
}
