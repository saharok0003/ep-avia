#ifndef STRUCTURES_H
#define STRUCTURES_H

#define main_file "avia.db"
#define temp_file "avia_tmp.db"
#define src_file "src.db"
#define dest_file "dest.db"

typedef struct{
    int id;
    char ticket[100];
    char flight[100];
    int place_id;
    int destination_id;
    char data[10];
    int time;
    float price;
} avia;

typedef struct{
    int id;
    char value[1000];
} dictionary;

#endif // STRUCTURES_H
