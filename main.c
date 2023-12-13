#include "monty.h"

instruction_t instructions[] = {
	{"push", push},
	{"pall", pall},
	{NULL, NULL}
};

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *opcode;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, "\n\t\r ");
		if (opcode == NULL || opcode[0] == '#') // skip blank lines and comments
			continue;
		execute_opcode(&stack, opcode, line_number);
	}

	free(line);
	fclose(file);
	return (EXIT_SUCCESS);
}

void execute_opcode(stack_t **stack, char *opcode, unsigned int line_number)
{
	int i = 0;

	while (instructions[i].opcode != NULL)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			return;
		}
		i++;
	}
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}