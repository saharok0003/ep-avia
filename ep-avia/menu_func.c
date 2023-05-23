#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "other_headers.h"
#include "structures.h"

void read_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines("avia.db"))) return;

    FILE *in = fopen(main_file, "r");
    FILE *in_tmp = fopen(temp_file, "w");

    char str[1000];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in);
        fprintf(in_tmp, "%s", str);
    }

    fclose(in); fclose(in_tmp);
    printf("File '%s' opened!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void close_file(){
    if (remove(temp_file) == 0) printf("The file is closed successfully.");
    else printf("The file is not closed.");
    getcharLock(2);
}

void save_file(){
    int file_lines = 0;
    if(!(file_lines=filenlines(temp_file))) {
        printf("Open File first!");
        return;
    }

    FILE *in = fopen(main_file, "w");
    FILE *in_tmp = fopen(temp_file, "r");

    char str[1000];
    for(int i=0; i<file_lines; i++){
        fgets(str, sizeof(str), in_tmp);
        fprintf(in, "%s", str);
    }

    fclose(in); fclose(in_tmp);
    printf("File '%s' saved!\nPress ENTER to go back...\n", main_file);
    getcharLock(2);
}

void add_note(){
    int file_lines = 0;
    avia* avia_array = get_temp_structure(&file_lines);
    int newID = avia_array[file_lines - 1].id + 1;
    free(avia_array);
    printf("New ID: %d\n", newID);

    char ticket[100];
    printf("Ticket: ");
    scanf("%s", ticket);

    char flight[100];
    printf("Flight: ");
    scanf("%s", flight);

    int place_idID = 0;
    printf("Place_id ID: ");
    scanf("%d", &place_idID);

    int destination_idID=0;
    printf("Destination ID: ");
    scanf("%d", &destination_idID);

    char data[10];
    printf("Date : ");
    scanf("%s", data);

    int timeID = 0;
    printf("Time ID: ");
    scanf("%d", &timeID);

    float price = 0;
    printf("Price: ");
    scanf("%f", &price);

    FILE *tmp = fopen(temp_file, "a");
    fprintf(tmp, "%d;%s;%s;%d;%d;%s;%d;%.2f;\n", newID, ticket, flight, place_idID, destination_idID, data, timeID, price);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void delete_note(){
    int file_lines = 0;
    avia* avia_array = get_temp_structure(&file_lines);
    file_print(avia_array, file_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_note_index(avia_array, file_lines, id_to_remove))==-1) return;
    FILE *tmp = fopen(temp_file, "w");
    int i;
    for(i = 0; avia_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%s;%s;%d;%d;%s;%d;%.2f;\n",
                avia_array[i].id,
                avia_array[i].ticket,
                avia_array[i].flight,
                avia_array[i].place_id,
                avia_array[i].destination_id,
                avia_array[i].data,
                avia_array[i].time,
                avia_array[i].price
                );
    for(i++;i < file_lines; i++)
        fprintf(tmp, "%d;%s;%s;%d;%d;%s;%d;%.2f;\n",
                avia_array[i].id,
                avia_array[i].ticket,
                avia_array[i].flight,
                avia_array[i].place_id,
                avia_array[i].destination_id,
                avia_array[i].data,
                avia_array[i].time,
                avia_array[i].price
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}


void edit_note(){
    int file_lines = 0;
    avia* avia_array = get_temp_structure(&file_lines);
    file_print(avia_array, file_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_note_index(avia_array, file_lines, id_to_edit))==-1) return;
    printf("\n\nEditing ID: %d\n", index);

    printf("New Ticket: ");
    scanf("%s", avia_array[index].ticket);

    printf("New Flight: ");
    scanf("%s", avia_array[index].flight);

    printf("New Place ID: ");
    scanf("%d", &avia_array[index].place_id);

    printf("New Destination Id: ");
    scanf("%d", &avia_array[index].destination_id);

    printf("New Date: ");
    scanf("%s", avia_array[index].data);

    printf("New Time");
    scanf("%d",&avia_array[index].time);

    printf("New Price: ");
    scanf("%f", &avia_array[index].price);


    FILE *tmp = fopen(temp_file, "w");
    for(int i=0; i<file_lines; i++){
    fprintf(tmp, "%d;%s;%s;%d;%d;%s;%d;%.2f;\n",
            avia_array[i].id,
            avia_array[i].ticket,
            avia_array[i].flight,
            avia_array[i].place_id,
            avia_array[i].destination_id,
            avia_array[i].data,
            avia_array[i].time,
            avia_array[i].price
            );
    }
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void display_dictionary(const char* filename){
    print_dict(filename);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void edit_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to edit: ");
    int id_to_edit = 0;
    scanf("%d", &id_to_edit);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_edit, 1))==-1) return;
    printf("\nEditing ID: %d\n", id_to_edit);
    printf("New value: ");
    char str[1001]; char temp;
    scanf("%c",&temp); scanf("%[^\n]",str);
    strcpy(dict_array[index].value, str);
    FILE *in = fopen(filename, "w");
    for(int i=0; i<dict_lines; i++){
    fprintf(in, "%d;%s;\n",
            dict_array[i].id,
            dict_array[i].value
            );
    }
    fclose(in);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void add_note_dictionary(const char* filename){
    int file_lines = 0;
    dictionary* dictionary_ = read_dictionary_(filename, &file_lines);
    int newID = dictionary_[file_lines - 1].id + 1;
    free(dictionary_);

    printf("New ID: %d\n", newID);
    char value[1000];
    printf("New value: ");
    scanf("%s", value);

    FILE *tmp = fopen(filename, "a");
    fprintf(tmp, "%d;%s;\n", newID, value);
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void delete_element_dictionary(const char* filename){
    int dict_lines=-1;
    print_dict(filename);
    dictionary* dict_array = read_dictionary_(filename, &dict_lines);
    printf("\nChoose index to remove: ");
    int id_to_remove = 0;
    scanf("%d", &id_to_remove);
    int index = 0;
    if((index = _get_dictionary_index(dict_array, dict_lines, id_to_remove, 1))==-1) return;
    FILE *tmp = fopen(filename, "w");
    int i;
    for(i = 0; dict_array[i].id != id_to_remove; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    for(i++;  i < dict_lines; i++)
        fprintf(tmp, "%d;%s;\n",
                dict_array[i].id,
                dict_array[i].value
                );
    fclose(tmp);
    printf("\nPress ENTER to go back...");
    getcharLock(2);

}

void file_display(){
    int file_lines = 0;
    avia* avia_array = get_temp_structure(&file_lines);
    file_print(avia_array, file_lines);
    printf("\nPress ENTER to go back...");
    getcharLock(2);
}

void export_txt(){
    int file_lines = 0;
    avia* avia_array = get_temp_structure(&file_lines);
    FILE *out = fopen("out.txt", "w");
    int place_id_lines=-1, destination_id_lines=-1;
    dictionary* place_id_array = read_dictionary_(src_file, &place_id_lines);
    dictionary* destination_id_array = read_dictionary_(dest_file, &destination_id_lines);

    for(int i=0; i<file_lines; i++){
        char tmp_place[100] = "*!?no_value\0";
        char tmp_destination[100] = "*!?no_value\0";
        int place_id_ind = _get_dictionary_index(place_id_array, place_id_lines, avia_array[i].place_id, 0);
        int destination_id_ind = _get_dictionary_index(destination_id_array, destination_id_lines, avia_array[i].destination_id, 0);
        if(place_id_ind != -1) strcpy(tmp_place, place_id_array[place_id_ind].value);
        if(destination_id_ind != -1) strcpy(tmp_destination, destination_id_array[destination_id_ind].value);

        fprintf(out, "%3d\%3s\%3s\t%-20s\t%-12s\t%s\t%-2d\t%.2f\n",
                avia_array[i].id,
                avia_array[i].ticket,
                avia_array[i].flight,
                tmp_place, tmp_destination,
                avia_array[i].data,
                avia_array[i].time,
                avia_array[i].price);
    }
    fclose(out);
    printf("\nData exported to 'out.txt'\n");
    printf("Press ENTER to go back...\n");
    getcharLock(2);
}

void about(){
    printf("Programm is made for processing data from files and writing the results back");
    printf("\nPress ENTER to go back...\n");
    getcharLock(2);
}
