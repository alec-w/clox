#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->lineCount = 0;
	chunk->lineCapacity = 0;
	chunk->lines = NULL;
	initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->lineCapacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(chunk->code, uint8_t, oldCapacity, chunk->capacity);
	}
	chunk->code[chunk->count] = byte;
	chunk->count++;

	if (chunk->lineCount == 0 || (chunk->lines[chunk->lineCount - 1] != line && chunk->lineCapacity < chunk->lineCount + 2)) {
		int oldLineCapacity = chunk->lineCapacity;
		chunk->lineCapacity = GROW_CAPACITY(oldLineCapacity);
		chunk->lines = GROW_ARRAY(chunk->lines, int, oldLineCapacity, chunk->lineCapacity);
	}

	if (chunk->lineCount == 0 || chunk->lines[chunk->lineCount - 1] != line) {
		chunk->lines[chunk->lineCount] = 1;
		chunk->lines[chunk->lineCount + 1] = line;
		chunk->lineCount += 2;
	} else {
		chunk->lines[chunk->lineCount - 2]++;
	}
}

int addConstant(Chunk* chunk, Value value) {
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int offset) {
	int passedOffsets = 0;
	for (int i = 0; i < chunk->lineCount; i+=2) {
		passedOffsets += chunk->lines[i];
		if (passedOffsets > offset) {
			return chunk->lines[i + 1];
		}
	}
}

