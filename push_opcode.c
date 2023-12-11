#include "monty.h"

void push_opcode(stack_t **stack, unsigned int line_number)
{
	char *arg = get_arg();
	int value = atoi(arg);
	
	if (value == 0 && strcmp(arg, "0") != 0) 
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	stack_t *new_node = malloc(sizeof(stack_t));
	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}
	*stack = new_node;
}

