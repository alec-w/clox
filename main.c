#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    
    writeConstant(&chunk, 1.1, 1);
    writeConstant(&chunk, 1.2, 1);
    writeConstant(&chunk, 1.2, 2);
    writeConstant(&chunk, 1.3, 3);

    writeChunk(&chunk, OP_RETURN, 3);

    disassembleChunk(&chunk, "test chunk");

    freeChunk(&chunk);
    return 0;
}

