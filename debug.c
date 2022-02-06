#include <stdio.h>

#include "debug.h"
#include "value.h"
#include "line.h"

void disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    int previousOffset = 0;
    for (int offset = 0; offset < chunk->count;) {
        int newOffset = disassembleInstruction(chunk, offset, previousOffset);
        previousOffset = offset;
        offset = newOffset;
    }
}

static int constantInstruction(const char* name, Chunk* chunk, int offset) {
    int constant = chunk->code[offset + 1];
    uint8_t code = chunk->code[offset];
    if (code == OP_CONSTANT_LONG) {
        constant = ((int)chunk->code[offset + 1] << 24)
            + ((int)chunk->code[offset + 2] << 16)
            + ((int)chunk->code[offset + 3] << 8)
            + ((int)chunk->code[offset + 4]);

    }
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + (code == OP_CONSTANT ? 2 : 5);
}

static int simpleInstruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassembleInstruction(Chunk* chunk, int offset, int previousOffset) {
    printf("%04d ", offset);
    int line = getLine(chunk, offset);
    if (offset > 0 && line == getLine(chunk, previousOffset)) {
        printf("   | ");
    } else {
        printf("%4d ", line);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_CONSTANT_LONG:
            return constantInstruction("OP_CONSTANT_LONG", chunk, offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

