#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
/**
 * sub - Subtracts the top element of the stack from the second top element.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in the file.
 */
void sub(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n -= (*stack)->n;
    f_pop(stack, line_number);
}
