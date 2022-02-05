#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "line.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
    initLineArray(&chunk->lines);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeValueArray(&chunk->constants);
    freeLineArray(&chunk->lines);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
            oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;

    writeLineArray(&chunk->lines, line); 
}

void writeConstant(Chunk* chunk, Value value, int line) {
    writeValueArray(&chunk->constants, value);
    int constant = chunk->constants.count - 1;

    if (chunk->constants.count - 1 <= UINT8_MAX) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, constant, line);
    } else {
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, (constant >> 24) & UINT8_MAX, line);
        writeChunk(chunk, (constant >> 16) & UINT8_MAX, line);
        writeChunk(chunk, (constant >> 8) & UINT8_MAX, line);
        writeChunk(chunk, constant & UINT8_MAX, line);
    }
}

