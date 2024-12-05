#ifndef NODE_H
#define NODE_H

#include "data.h"
#include <stdbool.h>

typedef struct 
{
    Data *data;
    struct Node *next;
} Node;

Node *search_list(Node *node, int ID);
void insert_node(Node **head, int ID, char name[50], double coords[3]);
Node *delete_node(Node **node);
void display_nodes(Node *node);

#endif