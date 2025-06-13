#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_RETURN,
} OpCode;

typedef struct {
	int line;
	int count;
} LineCount;

typedef struct {
	int count;
	int capacity;
	int line_count;
	int line_capacity;
	uint8_t* code;
	LineCount* lines;
	ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);
int getLine(Chunk*chunk, int offset);

#endif
