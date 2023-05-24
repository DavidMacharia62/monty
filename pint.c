#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
/**
 * pint - Prints the value at the top of the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number in the file.
 */
void pint(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", (*stack)->n);
}
