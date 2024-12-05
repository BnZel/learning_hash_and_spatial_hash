#include "./include/hash.h"
#include "./include/node.h"
#include <stdlib.h>

Hash_Table *init_table(int size)
{
    Hash_Table *table = (Hash_Table *) malloc(sizeof(Hash_Table));
    table->buckets = (Node **) calloc(size, sizeof(Node *));
    table->size = size;
    table->count = 0;

    return table;
}

int hash_function(int bucket, int key)
{
    int hash = key % bucket;
    return hash;
}

void insert_key(Hash_Table *table, int key_ID, char name[50], double coords[2])
{
    int index = hash_function(table->size, key_ID);
    insert_node(&table->buckets[index], key_ID, name, coords);
    table->count++;
}

void delete_key(Hash_Table *table, int key_ID)
{
    int index = hash_function(table->size, key_ID);
    delete_node(&table->buckets[index]);
}

void display_table(Hash_Table *table)
{
    printf("########################################################################################\n");
    printf("Size: %d | Count: %d\n\n", table->size, table->count);

    for(int i=0; i<table->size; i++)
    {
        printf("Hash %d: ", i);

        Node *current = table->buckets[i];
        if(current == NULL) {
            printf("[Empty]\n");
        }
        else{
            while(current != NULL)
            {
                printf(
                    "(ID: %d | Name: %s | Coordinates: [%f, %f, %f])\n",
                        current->data->ID,
                        current->data->name,
                        current->data->coords[0],
                        current->data->coords[1],
                        current->data->coords[2]
                    );

                current = current->next;
            }
        }

        printf("\n");
    }
    printf("########################################################################################\n");

}

//////////////////////////////////////// SPATIAL HASHING ////////////////////////////////////////
Grid *init_grid(int size)
{
    Grid *spatial_table = (Grid *)malloc(sizeof(Grid));
    spatial_table->buckets = (Node **)calloc(size, sizeof(Node *));

    spatial_table->size = size;
    spatial_table->spacing = calculate_spacing(size);

    spatial_table->count = 0;

    spatial_table->x = 0;
    spatial_table->y = 0;
    spatial_table->z = 0;

    return spatial_table;
}

int spatial_hash_function(Grid *grid)
{
    int spatial_hash = (grid->x * 92837111) ^ (grid->y * 689287499) ^ (grid->z * 283923481);
    return abs(spatial_hash) % grid->size;
}

int calculate_spacing(int size) { return 2*size; }

int calculate_bucket(double coords[3], int spacing)
{
    int x_i = (int) floor(coords[0] / spacing);
    int y_i = (int) floor(coords[1] / spacing);
    int z_i = (int) floor(coords[2] / spacing);

    int i = (x_i * coords[1] + y_i) * coords[2] + z_i;
    return i;
}

void spatial_insert(Grid *grid, int key_ID, char name[50], double coords[3])
{
    grid->x = coords[0];
    grid->y = coords[1];
    grid->z = coords[2];

    int bucket_index = calculate_bucket(coords, grid->size);
    int hash_index = spatial_hash_function(grid);
    int combined_index = (bucket_index + hash_index) % grid->size;

    insert_node(&grid->buckets[combined_index], key_ID, name, coords);
    grid->count++;
}

void spatial_delete(Grid *grid, double coords[3])
{
    grid->x = coords[0];
    grid->y = coords[1];
    grid->z = coords[2];

    int bucket_index = calculate_bucket(coords, grid->size);
    int hash_index = spatial_hash_function(grid);
    int combined_index = (bucket_index + hash_index) % grid->size;

    delete_node(&grid->buckets[combined_index]);
    grid->count--; 
}

void spatial_display_table(Grid *grid)
{
  printf("\n################################ SPATIAL GRID ################################\n");
    printf("Grid Size: %d | Item Count: %d | Spacing: %d\n\n", grid->size, grid->count, grid->spacing);

    for (int i = 0; i < grid->size; i++) {
        printf("Bucket %d: ", i);

        Node *current = grid->buckets[i];
        if (current == NULL) {
            printf("[Empty]\n");
        } 
        else {
            while (current != NULL) {
                printf(
                       "(ID: %d | Name: %s | Coordinates: [%f, %f, %f])\n",
                       current->data->ID,
                       current->data->name,
                       current->data->coords[0],
                       current->data->coords[1],
                       current->data->coords[2]
                    );
                
                current = current->next;
            }
        }

        printf("\n");
    }

    printf("###############################################################################\n");
}