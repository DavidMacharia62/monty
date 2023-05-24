#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
/**
 * mul - Multiplies the second top element of the stack with the top element.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in the file.
 */
void mul(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL || (*stack)->next == NULL)
    {
        fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
        exit(EXIT_FAILURE);
    }

    (*stack)->next->n *= (*stack)->n;
    pop(stack, line_number);
}
