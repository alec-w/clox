#ifndef clox_line_h
#define clox_line_h

#include "common.h"

typedef struct {
    int line;
    int count;
} Line;

typedef struct {
    int capacity;
    int count;
    Line* lines;
} LineArray;

void initLineArray(LineArray* array);
void writeLineArray(LineArray* array, int line);
void freeLineArray(LineArray* array);

#endif
