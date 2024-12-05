#include "./include/node.h"

Node *search_list(Node *node, int ID)
{    
    while(node != NULL)
    {
        if(node->data->ID == ID)
        {
            return node;
        }
        node = node->next;        
    }   

    return NULL;
}

void insert_node(Node **head, int ID, char name[50], double coords[3])
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->next = *head;
    *head = new_node;

    new_node->data = (Data *)malloc(sizeof(Data));
    new_node->data->ID = ID;
    strcpy(new_node->data->name, name);

    for(int i=0; i<3; i++)
    {
        new_node->data->coords[i] = coords[i];
    }
}

Node *delete_node(Node **node)
{
    if(node == NULL){ 
        return NULL; 
    }

    Node *delete_node = *node;
    *node = (*node)->next;

    free(delete_node->data); 
    free(delete_node);

    return *node;
}

void display_nodes(Node *node)
{
    while(node != NULL)
    {
        printf(
                "(ID: %d | Name: %s | Coordinates: [%f, %f, %f])\n",
                node->data->ID,
                node->data->name,
                node->data->coords[0],
                node->data->coords[1],
                node->data->coords[2]
            );

        node = node->next;
    }
}