#include "monty.h"

void pall_opcode(stack_t **stack, unsigned int line_number);
void push_opcode(stack_t **stack, unsigned int line_number);

instruction_t instructions[] = {
	{"push", push_opcode},
	{"pall", pall_opcode},
};
