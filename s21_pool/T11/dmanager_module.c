#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door* doors);
void sort(struct door doors[DOORS_COUNT]);
void close(struct door doors[DOORS_COUNT]);
void output(struct door doors[DOORS_COUNT]);


int main() {
    struct door doors[DOORS_COUNT];
    initialize_doors(doors);
    sort(doors);
    close(doors);
    output(doors);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void sort(struct door doors[DOORS_COUNT]) {
    struct door tmp;

    for (int i = 0; i < DOORS_COUNT; i++) {
        for (int j = 14; i < j; j--) {
            if (doors[j - 1].id > doors[j].id) {
                tmp = doors[j - 1];
                doors[j - 1] = doors[j];
                doors[j] = tmp;
            }
        }
    }
}

void close(struct door doors[DOORS_COUNT]) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].status = 0;
    }
}

void output(struct door doors[DOORS_COUNT]) {
    for (int i = 0; i <  DOORS_COUNT; i++) {
        printf("id двери %d, статус двери %d\n", doors[i].id, doors[i].status);
    }
}
