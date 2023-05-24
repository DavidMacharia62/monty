#include <stdio.h>
#include <stdlib.h>
#include "monty.h"
/**
 * pop - Removes the top element of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number in the file.
 */
void pop(stack_t **stack, unsigned int line_number)
{
    if (*stack == NULL)
    {
        fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
        exit(EXIT_FAILURE);
    }

    stack_t *top = *stack;
    *stack = (*stack)->next;

    if (*stack != NULL)
        (*stack)->prev = NULL;

    free(top);
}
