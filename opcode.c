#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"
/**
 * execute_opcode - Executes the corresponding opcode function.
 * @opcode: Opcode to be executed.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in the file.
 */
void execute_opcode(char *opcode, stack_t **stack, unsigned int line_number)
{
    instruction_t opcodes[] = {
        {"push", push},
        {"pall", pall},
        {"pint", pint},
        {"pop", pop},
        {"swap", swap},
        {"add", add},
        {"nop", nop},
        {"sub", sub},
        {"div", divide},
        {"mul", mul},
        {"mod", mod},
        {NULL, NULL}
    };

    int i = 0;

    while (opcodes[i].opcode != NULL)
    {
        if (strcmp(opcode, opcodes[i].opcode) == 0)
        {
            opcodes[i].f(stack, line_number);
            return;
        }
        i++;
    }

    fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}

/**
 * read_monty_file - Reads and executes the Monty bytecode file.
 * @file_path: Path to the Monty bytecode file.
 */
void read_monty_file(const char *file_path)
{
    FILE *file = fopen(file_path, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int line_number = 0;
    stack_t *stack = NULL;

    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1)
    {
        line_number++;

        if (line[0] == '#' || line[0] == '\n')
            continue;

        char *opcode = strtok(line, " \t\n");

        if (opcode != NULL)
            execute_opcode(opcode, &stack, line_number);
    }

    free(line);
    fclose(file);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        return EXIT_FAILURE;
    }

    read_monty_file(argv[1]);

    return EXIT_SUCCESS;
}
