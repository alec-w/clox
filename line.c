#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "line.h"

void initLineArray(LineArray* array) {
    array->lines = NULL;
    array->capacity = 0;
    array->count = 0;
}

void writeLineArray(LineArray* array, int line) {
    if (array->count == 0 || array->lines[array->count - 1].line != line) {
        if (array->capacity < array->count + 1) {
            int oldCapacity = array->capacity;
            array->capacity = GROW_CAPACITY(oldCapacity);
            array->lines = GROW_ARRAY(Line, array->lines,
                oldCapacity, array->capacity);
        }

        array->lines[array->count] = (Line) { .line = line, .count = 1 };
        array->count++;
    } else {
        array->lines[array->count - 1].count++;
    }
}

void freeLineArray(LineArray* array) {
    FREE_ARRAY(Line, array->lines, array->capacity);
    initLineArray(array);
}

int getLine(LineArray* array, int index) {
    int runningIndex = 0;
    for (int i = 0; i < array->count; i++) {
        runningIndex += array->lines[i].count;
        if (runningIndex >= index) {
            return array->lines[i].line;
        }
    }
    return 0;
}

