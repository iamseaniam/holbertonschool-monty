#include "monty.h"

instruction_t instructions[] = {
    {"push", push},
    {"pall", pall},
    // add other instructions here
    {NULL, NULL}
};

int is_number(char *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    if (str[0] == '-')
        i++;
    for (; str[i]; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
    }
    return (1);
}

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
        if (strcmp(opcode, "push") == 0)
        {
            char *arg = strtok(NULL, "\n\t\r ");
            if (arg == NULL || !is_number(arg))
            {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                exit(EXIT_FAILURE);
            }
            line_number = atoi(arg);
        }
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