#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
    int amount, number, low, high;

    printf("Size of list: ");
    scanf("%d", &amount);
    printf("Lowest value: ");
    scanf("%d", &low);
    printf("Highest value: ");
    scanf("%d", &high);

    if (high - low < 1) {
        printf("High must never be lower than low.\n");
        return 1;
    }

    if (amount <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    time_t seconds;
    time(&seconds);
    srand((unsigned) seconds);

    FILE* file = fopen("list.txt", "w");
    if (file == NULL) {
        printf("File couldn't be created.\n");
        return 1;
    }

    for (int i=0; i<amount; i++) {
        // The "+1" allows for inclusivity on both ends
        // The "rand() % (high - low)" always returns as [0, difference>
        // The "+low" shifts the entire spectrum towards [low, high>
        // If low is negative, high follows it to the left on a number line; If low is positive, high follows to the right on a number line. Simple arithmetic.
        // Final result is always within [low, high] 
        number = (rand() % (high - low + 1)) + low;

        fprintf(file, "%d\n", number);
    }
    fclose(file);

    return 0;
}