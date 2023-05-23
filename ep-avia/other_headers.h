#ifndef OTHER_HEADERS_H
#define OTHER_HEADERS_H


#include "structures.h"

void getcharLock(int);
void clearscreen();

int filenlines(const char*);
avia* get_temp_structure(int*);
dictionary* read_dictionary_(const char*, int*);
void print_dict(const char*);
int _get_dictionary_index(dictionary*, int, int, int);
void file_print(avia*, int);
int _get_note_index(avia*, int, int );

#endif // OTHER_HEADERS_H
