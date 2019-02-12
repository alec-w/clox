#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
	initVM();
	Chunk chunk;
	initChunk(&chunk);
	writeConstant(&chunk, 1.0, 20);
	writeChunk(&chunk, OP_RETURN, 1);
	interpret(&chunk);
	freeVM();
	freeChunk(&chunk);
	return 0;
}

