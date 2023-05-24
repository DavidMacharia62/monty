#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>

/* Structures */

/**
 * struct stack_s - Stack structure
 * @n: Integer value
 * @next: Pointer to next element
 *
 * Description: Structure representing a stack element
 */
typedef struct stack_s
{
	int n;
	struct stack_s *next;
} stack_t;

/* Global Variables */

extern stack_t *top;
extern int format;

/* Function Prototypes */

/* Monty Interpreter */
void process_file(const char *filename);
void process_instruction(char *opcode, unsigned int line_number);
void free_stack(void);

/* Stack Operations */
void push(int value);
void pall(void);
void pint(void);
void pop(void);
void swap(void);
void add(void);
void sub(void);
void mul(void);
void div_op(void);
void mod(void);
void pchar(void);
void pstr(void);
void rotl(void);
void rotr(void);
void stack(void);
void queue(void);

/* Utility Functions */
int is_integer(const char *str);
int is_valid_opcode(char *opcode);
int atoi_error(const char *str);
void error_usage_push(unsigned int line_number);
void error_push(unsigned int line_number);
void error_pint(unsigned int line_number);
void error_pop(unsigned int line_number);
void error_swap(unsigned int line_number);
void error_add(unsigned int line_number);
void error_sub(unsigned int line_number);
void error_mul(unsigned int line_number);
void error_div(unsigned int line_number);
void error_mod(unsigned int line_number);
void error_pchar(unsigned int line_number);
void error_pstr(unsigned int line_number);
void error_rotl(unsigned int line_number);
void error_rotr(unsigned int line_number);
void error_stack(unsigned int line_number);
void error_queue(unsigned int line_number);
void error_malloc(void);

#endif /* MONTY_H */
