/*
*
* Driver Code 
*
*/

#include "./src/include/data.h"
#include "./src/include/node.h"
#include "./src/include/hash.h"

#include <stdio.h>

// Hash_Table structure should work too
// for second argument since it points to the same data types
void export_to_csv(char filename[50], Grid *spatial_hash)
{
    printf("EXPORTING DATA TO CSV....\n");

    FILE *fptr;
    fptr = fopen(filename, "w+");
    fprintf(fptr, "ID, name, x, y, z\n");

    for(int i=0; i<spatial_hash->size; i++)
    {
        Node *current = spatial_hash->buckets[i];
        while(current != NULL)
        {
            fprintf(
                    fptr, 
                    "%d, %s, %f, %f, %f\n", 
                    current->data->ID,
                    current->data->name,
                    current->data->coords[0],
                    current->data->coords[1],
                    current->data->coords[2]
                );
            
            current = current->next;
        }
    }

    fclose(fptr);

    printf("DONE...\n");
}



int main(void)
{
    Hash_Table *table = init_table(6);

    double coords_A[3] = {2.1, 0.2, 0.0};
    double coords_B[3] = {8.3, 14.4, 0.0};
    double coords_C[3] = {5.5, 2.9, 0.0};
    double coords_D[3] = {17.7, 4.8, 0.0};

    insert_key(table, 5, "Hello World!", coords_A);
    insert_key(table, 6, "Hello World?", coords_B);
    insert_key(table, 7, "Hello World!?", coords_C);
    insert_key(table, 8, "Goodbye World!", coords_D);

    Node *search_result = search_list(table->buckets[5], 5);

    if (search_result != NULL) {
        printf("Found ID %d\n", search_result->data->ID);
    } 
    else{
        printf("Not found...\n");
    }

    // delete_key(table, 6);
    // search_result = search_list(table->buckets[6], 6);

    // if (search_result != NULL) {
    //     printf("Found ID %d\n", search_result->data->ID);
    // } 
    // else{
    //     printf("Not found...\n");
    // }

    display_table(table);

    export_to_csv("./hash_data.csv", table);

//////////////////////////////////////// SPATIAL HASHING ////////////////////////////////////////

    double s_coords_A[3] = {5.10, 9.0, 21.75};
    double s_coords_B[3] = {6.56, 10.10, 1.12};
    double s_coords_C[3] = {14.14, 40.81, 11.18};
    double s_coords_D[3] = {23.09, 5.11, 24.26};

    Grid *spatial_hash = init_grid(6);

    spatial_insert(spatial_hash, 0, "Spatial Hash!", s_coords_A);
    spatial_insert(spatial_hash, 1, "Spatial Hash?", s_coords_B);
    spatial_insert(spatial_hash, 2, "Spatial Hash!?", s_coords_C);
    spatial_insert(spatial_hash, 3, "Spatial Hash!?!?", s_coords_D);

    spatial_display_table(spatial_hash);

    // spatial_delete(spatial_hash, s_coords_A);
    // spatial_display_table(spatial_hash);    

    export_to_csv("./spatial_data.csv", spatial_hash);

    return 0;
}