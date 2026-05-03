#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_ROLLS 10000

int main(void) {
    int sides;
    int rolls[NUM_ROLLS];

    /* Get valid number of sides from user */
    do {
        printf("Enter the number of sides on the die (2 to 100): ");
        if (scanf("%d", &sides) != 1) {
            /* Clear invalid input */
            while (getchar() != '\n');
            sides = -1;
        }
        if (sides < 2 || sides > 100) {
            printf("Invalid input. Please enter a number between 2 and 100.\n");
        }
    } while (sides < 2 || sides > 100);

    /* Seed the random number generator */
    srand((unsigned int)time(NULL));

    /* Roll the die 10,000 times and print each result */
    printf("\nRolling a %d-sided die %d times...\n\n", sides, NUM_ROLLS);

    double sum = 0.0;

    for (int i = 0; i < NUM_ROLLS; i++) {
        rolls[i] = (rand() % sides) + 1;
        printf("Roll %5d: %d\n", i + 1, rolls[i]);
        sum += rolls[i];
    }

    /* Calculate mean */
    double mean = sum / NUM_ROLLS;

    /* Calculate variance using (N-1) in denominator */
    double sum_sq_diff = 0.0;
    for (int i = 0; i < NUM_ROLLS; i++) {
        double diff = rolls[i] - mean;
        sum_sq_diff += diff * diff;
    }

    double variance       = sum_sq_diff / (NUM_ROLLS - 1);
    double std_dev        = sqrt(variance);
    double std_error      = std_dev / sqrt((double)NUM_ROLLS);

    /* Print statistical results */
    printf("\n--- Statistical Results (%d rolls of a %d-sided die) ---\n", NUM_ROLLS, sides);
    printf("Mean:                    %.4f\n", mean);
    printf("Variance:                %.4f\n", variance);
    printf("Standard Deviation:      %.4f\n", std_dev);
    printf("Standard Error of Mean:  %.4f\n", std_error);

    return 0;
}