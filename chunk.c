#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	chunk->line_count = 0;
	chunk->line_capacity=0;
	chunk->globalCount = 0;
	chunk->globalIndices = NULL;
	initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);

	}

	if (chunk->line_capacity <= chunk->line_count) {
		int oldCapacity = chunk->line_capacity;
		chunk->line_capacity = GROW_CAPACITY(oldCapacity);
		chunk->lines = GROW_ARRAY(LineCount, chunk->lines, oldCapacity, chunk->line_capacity);
	}

	if (chunk->lines[chunk->line_count].line == line) {
		chunk->lines[chunk->line_count].count++;
	} else {
		LineCount l = {.line=line, .count=1};
		chunk->lines[chunk->line_count] = l;
		chunk->line_count += 1;
	}


	

	chunk->code[chunk->count] = byte;
	chunk->count++;
}

void freeChunk(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(LineCount, chunk->lines, chunk->capacity);
	FREE_ARRAY(ObjString*, chunk->globalIndices, chunk->globalCount);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int offset) {
	int offset_count = offset;
	int i = 0;
	while (offset_count >= 0 && i < chunk->line_count) {
		offset_count -= chunk->lines[i].count;
		if (offset_count < 0) return chunk->lines[i].line;
		i++;
	}
	return -1;
}

