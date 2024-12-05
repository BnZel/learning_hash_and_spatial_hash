#ifndef DATA_H
#define DATA_H

#include <string.h>

typedef struct 
{
    int ID;
    char name[50];
    float coords[3];
} Data;

int update_ID(Data *data, int new_id);
char update_name(Data *data, char new_name[50]);
void update_coords(Data *data, double new_coords[3]);
void display_data(Data *data);

#endif