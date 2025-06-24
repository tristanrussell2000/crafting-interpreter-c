#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"
#include "table.h"

#define STACK_MAX 256

typedef struct {
	Chunk* chunk;
	uint8_t* ip; // Instruction Pointer
	Value stack[STACK_MAX];
	Value* stackTop;
	Value* globals;
	Table strings;
	Obj* objects; // Pointer to head of list of objects
} VM;

typedef enum {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM(void);
void freeVM(void);
InterpretResult interpret(const char* source);
void push(Value value);
Value pop(void);

#endif
