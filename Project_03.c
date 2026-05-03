#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

#define NUM_ROLLS 10000

int main(void) {
    int sides;
    int rolls[NUM_ROLLS];

    /* Get valid number of sides from user */
    do {
        printf("Enter the number of sides on the die (2 to 100): ");
        if (scanf("%d", &sides) != 1) {
            /* Clear invalid input (handles EOF safely) */
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            sides = -1;
        }
        if (sides < 2 || sides > 100) {
            printf("Invalid input. Please enter a number between 2 and 100.\n");
        }
    } while (sides < 2 || sides > 100);

    /* Seed the random number generator (XOR with address reduces identical runs) */
    srand((unsigned int)time(NULL) ^ (unsigned int)(uintptr_t)&sides);

    /* Roll the die 10,000 times and print each result */
    printf("\nRolling a %d-sided die %d times...\n\n", sides, NUM_ROLLS);

    double sum = 0.0;

    for (int i = 0; i < NUM_ROLLS; i++) {
        rolls[i] = (int)((double)rand() / (RAND_MAX + 1.0) * sides) + 1;
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

    /* Theoretical expected values for validation */
    double expected_mean     = (sides + 1) / 2.0;
    double expected_variance = (sides * sides - 1) / 12.0;

    /* Print statistical results */
    printf("\n--- Statistical Results (%d rolls of a %d-sided die) ---\n", NUM_ROLLS, sides);
    printf("Mean:                    %.4f\n", mean);
    printf("Expected Mean:           %.4f\n", expected_mean);
    printf("\nVariance:                %.4f\n", variance);
    printf("Expected Variance:       %.4f\n", expected_variance);
    printf("\nStandard Deviation:      %.4f\n", std_dev);
    printf("Standard Error of Mean:  %.4f\n", std_error);

    return 0;
}