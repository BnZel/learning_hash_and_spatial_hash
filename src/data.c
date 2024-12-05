#include "./include/data.h"

int update_ID(Data *data, int new_ID){ return data->ID = new_ID; }

char update_name(Data *data, char new_name[50])
{ 
    new_name = strcpy(data->name, new_name);
    return new_name; 
}

void update_coords(Data *data, double new_coords[3])
{ 
    int size = sizeof(data->coords)/sizeof(data->coords[0]);
    for(int i=0; i<size; i++){ data->coords[i] = new_coords[i];}
}

void display_data(Data *data)
{
    printf("ID: %i | Name: %s | Coords (x: %f, y: %f, z: %f)\n", 
            data->ID, 
            data->name, 
            data->coords[0], 
            data->coords[1],
            data->coords[2]
        );
}