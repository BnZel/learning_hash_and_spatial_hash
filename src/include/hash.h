#ifndef HASH_H
#define HASH_H

#include "node.h"

typedef struct 
{
    Node **buckets;     // pointer to linked list (buckets)
    int size;           // number of buckets
    int count;          // number of elements in hash table

} Hash_Table;


Hash_Table *init_table(int size);
int hash_function(int bucket_size, int key_ID);
void insert_key(Hash_Table *table, int key_ID, char name[50], double coords[3]);
void delete_key(Hash_Table *table, int key_ID);
void display_table(Hash_Table *table);

//////////////////////////////////////// SPATIAL HASHING ////////////////////////////////////////

typedef struct 
{
    Node **buckets;
    int size;
    int spacing;
    int count;
    int x;
    int y;
    int z;

} Grid;

Grid *init_grid(int size);
int spatial_hash_function(Grid *grid);
int calculate_spacing(int size);
int calculate_bucket(double coords[3], int spacing);
void spatial_insert(Grid *grid, int key_ID, char name[50], double coords[3]);
void spatial_delete(Grid *grid, double coords[3]);
void spatial_display_table(Grid *grid);

#endif