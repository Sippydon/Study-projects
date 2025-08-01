#include "door_struct.h"
#include <stdlib.h>
#include "list.h"
#include <stdio.h>

struct node* init(struct door* door) {
    struct node *node = malloc(sizeof(struct node));

    node -> next = NULL;
    node -> value = door;

    return node;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* node;

    if (elem -> next != NULL) {
        node = init(door);
        node -> next = elem -> next;
        elem -> next = node;
    } else {
        node = init(door);
        elem -> next = node;
    }

    return node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* node = root;

    while (node -> next) {
        if (node -> value -> id == door_id) {
            break;
        }
        node = node -> next;
    }

    return node;
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* res = root;
    if (root != NULL && elem != NULL) {
        if (root -> next == elem) {
            root -> next = elem -> next;
            free(elem);
        } else if (root != elem) {
            while (root -> next != elem) {
                root = root -> next;
            }

            root -> next = elem -> next;
            free(elem);

        } else {
            res = NULL;
            free(root);
        }
    }

    return res;
}

void destroy(struct node* root) {
    struct node* temp = root;
    while (temp != NULL) {
        root = temp;
        temp = temp -> next;
        free(root);
    }
}
