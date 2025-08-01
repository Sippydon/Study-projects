#include "list.h"
#include "door_struct.h"
#include <stdio.h>
#include <stdlib.h>

void add_door_test(struct node* list);
void remove_door_test(struct node* list);

int main() {
    struct node* list = malloc(sizeof(struct node));

    add_door_test(list);
    remove_door_test(list);

    return 0;
}

void add_door_test(struct node* list) {
    struct door* door_root = malloc(sizeof(struct door));
    door_root -> id = 0; door_root -> status = 0;
    struct door* door1 = malloc(sizeof(struct door));
    struct door* door2 = malloc(sizeof(struct door));
    struct door* door3 = malloc(sizeof(struct door));

    struct node* tmp;

    list = init(door_root);

    printf("ADD_DOOR_TEST...\n");
    door1 -> id = 12; door1 -> status = 0;
    tmp = add_door(list, door1);

    printf("CASE 1...\n");
    if (tmp -> value -> id == 12 && tmp -> value -> status == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 2...\n");
    door2 -> id = 123; door2 -> status = 0;
    tmp = add_door(tmp, door2);
    if (tmp -> value -> id == 123 && tmp -> value -> status == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 3...\n");
    door3 -> id = 1234; door3 -> status = 0;
    tmp = add_door(tmp, door3);
    if (tmp -> value -> id == 1234 && tmp -> value -> status == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    struct node* cpp = find_door(door1 -> id, list);
    if (cpp -> value -> id == door1 -> id) {
        free(door1);
    }


    destroy(list);

    free(door_root);
    free(door2);
    free(door3);
}

void remove_door_test(struct node* list) {
    struct node* tmp;
    struct door* door_root = malloc(sizeof(struct door));
    door_root -> id = 123; door_root -> status = 0;
    struct door* door1 = malloc(sizeof(struct door));
    door1 -> id = 12; door1 -> status = 0;
    struct door* door2 = malloc(sizeof(struct door));
    door2 -> id = 123; door2 -> status = 0;
    struct door* door3 = malloc(sizeof(struct door));
    door3 -> id = 1234; door3 -> status = 0;
    list = init(door_root);
    tmp = add_door(list, door1);
    tmp = add_door(tmp, door2);
    tmp = add_door(tmp, door3);

    printf("REMOVE_DOOR_TEST...\n");

    printf("CASE 1...\n");
    tmp = remove_door(list -> next, list);
    if (tmp -> value -> id == 123 && tmp -> value -> status == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 2...\n");
    tmp = remove_door(list -> next, list);
    if (tmp -> value -> id == 123 && tmp -> value -> status == 0) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 3...\n");
    tmp = remove_door(list -> next, list);
    if (tmp -> next == NULL) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    printf("CASE 4...\n");
    tmp = remove_door(list, list);
    if (tmp == NULL) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    destroy(list);
    free(door_root);
    free(door1);
    free(door2);
    free(door3);
}
