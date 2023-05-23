#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "structures.h"


void getcharLock(int loops){
    for(int i = 0; i < loops; i++ ) getchar();
}

void clearscreen(){
    printf("\n"); system("cls");
}

int filenlines(const char *filename)
{
    FILE *in = fopen(filename, "r");
    if(!in) {
        printf("Error... File '%s' not found!\nPress any key to continue...\n", filename);
        getcharLock(2); return 0;
    }
    int file_lines=0;
    char str[1000];
    do {
        fgets(str, sizeof(str), in);
    } while(!feof(in) && ++file_lines);
    return file_lines+1;
}

avia* get_temp_structure(int* file_lines_){
    int file_lines = 0;
    if(!(file_lines=filenlines(temp_file))) return 0;

    FILE *in = fopen(temp_file, "r");
    avia* avia_array = (avia*)malloc(sizeof(avia) * file_lines);

    char str[1000];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        avia_array[i].id = atoi(strtok(str, ";"));
        strcpy(avia_array[i].ticket,strtok(NULL, ";"));
        strcpy(avia_array[i].flight,strtok(NULL, ";"));
        avia_array[i].place_id=atoi(strtok(NULL, ";"));
        avia_array[i].destination_id=atoi(strtok(NULL, ";"));
        strcpy(avia_array[i].data, strtok(NULL, ";"));
        avia_array[i].time = atoi(strtok(NULL, ";"));
        avia_array[i].price = atof(strtok(NULL, ";"));
    }
    fclose(in);
    *file_lines_ = file_lines;
    return avia_array;
}

dictionary* read_dictionary_(const char *filename, int *lines){
    int file_lines = 0;
    if(!(file_lines = filenlines(filename))) return 0;
    FILE *in = fopen(filename, "r");

    char str[1000];
    dictionary* dictionary_array = (dictionary*)malloc(sizeof(dictionary) * file_lines);
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        dictionary_array[i].id = atoi(strtok(str, ";"));
        strcpy(dictionary_array[i].value, strtok(NULL, ";"));
    }
    *lines = file_lines;
    return dictionary_array;
}

int _get_dictionary_index(dictionary* dictionary_, int lines, int id, int mode){
    for(int i=0; i<lines; i++){
        if(dictionary_[i].id == id) return i;
    }
    if(mode){
        clearscreen();
        printf("Error... dictionary note id %d does not exist!\nPress ENTER to go back...", id);
        getcharLock(2);
    }
    return -1;
}

void file_print(avia* avia_array, int length){
    int place_id_lines=-1, destination_id_lines=-1;
    dictionary* place_id_array = read_dictionary_(src_file, &place_id_lines);
    dictionary* destination_id_array = read_dictionary_(dest_file, &destination_id_lines);

    printf(" id\tticket flight\t place\t\t\t destination\tdata\t\t time\tprice\n\n");
    for(int i=0; i<length; i++){
        char tmp_place_id[100] = "*!?no_value\0";
        char tmp_destination_id[100] = "*!?no_value\0";
        int place_id_ind = _get_dictionary_index(place_id_array, place_id_lines, avia_array[i].place_id, 0);
        int destination_id_ind = _get_dictionary_index(destination_id_array, destination_id_lines, avia_array[i].destination_id, 0);
        if(place_id_ind != -1) strcpy(tmp_place_id, place_id_array[place_id_ind].value);
        if(destination_id_ind != -1) strcpy(tmp_destination_id, destination_id_array[destination_id_ind].value);


        printf(" %3d\t%3s\t%3s\t%-20s\t%-12s\t%-2s\t%-2d\t%.2f\n",
               avia_array[i].id,
               avia_array[i].ticket,
               avia_array[i].flight,
               tmp_place_id, tmp_destination_id,
               avia_array[i].data,
               avia_array[i].time,
               avia_array[i].price);
    }
}

void print_dict(const char* filename){
    int dict_lines=-1;
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("Dictionary %s\n\n", filename);
    printf(" id  value\n\n");
    for(int i=0; i<dict_lines; i++){
        printf("%-4d%s\n",
               dict_array[i].id,
               dict_array[i].value
               );
    }
}

int _get_note_index(avia* avia_array, int file_length, int id){
    for(int i=0; i<file_length; i++)
        if(avia_array[i].id == id) return i;
    clearscreen();
    printf("Error... Note id %d does not exist!\nPress ENTER to go back...", id);
    getcharLock(2);
    return -1;
}
