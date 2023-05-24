#include "monty.h"

stack_t *top = NULL;
int format = 0; /* 0 for stack, 1 for queue */

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: monty file\n");
        exit(EXIT_FAILURE);
    }

    process_file(argv[1]);
    free_stack();

    return 0;
}

void process_file(const char *filename)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int line_number = 0;

    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, file)) != -1)
    {
        line_number++;
        process_instruction(line, line_number);
    }

    free(line);
    fclose(file);
}

void process_instruction(char *instruction, unsigned int line_number)
{
    char *opcode;
    int value;

    opcode = strtok(instruction, " \t\n");
    if (opcode == NULL || opcode[0] == '#')
        return;

    if (strcmp(opcode, "push") == 0)
    {
        value = atoi_error(strtok(NULL, " \t\n"));
        push(value);
    }
    else if (strcmp(opcode, "pall") == 0)
        pall();
    else if (strcmp(opcode, "pint") == 0)
        pint();
    else if (strcmp(opcode, "pop") == 0)
        pop();
    else if (strcmp(opcode, "swap") == 0)
        swap();
    else if (strcmp(opcode, "add") == 0)
        add();
    else if (strcmp(opcode, "sub") == 0)
        sub();
    else if (strcmp(opcode, "mul") == 0)
        mul();
    else if (strcmp(opcode, "div") == 0)
        div_op();
    else if (strcmp(opcode, "mod") == 0)
        mod();
    else if (strcmp(opcode, "pchar") == 0)
        pchar();
    else if (strcmp(opcode, "pstr") == 0)
        pstr();
    else if (strcmp(opcode, "rotl") == 0)
        rotl();
    else if (strcmp(opcode, "rotr") == 0)
        rotr();
    else if (strcmp(opcode, "stack") == 0)
        stack();
    else if (strcmp(opcode, "queue") == 0)
        queue();
    else
    {
        fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
        exit(EXIT_FAILURE);
    }
}

void free_stack(void)
{
    stack_t *temp;

    while (top != NULL)
    {
        temp = top;
        top = top->next;
        free(temp);
    }
}

void push(int value)
{
    stack_t *new_node;

    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
        error_malloc();

    new_node->n = value;
    new_node->next = top;
    top = new_node;
}

void pall(void)
{
    stack_t *temp;

    temp = top;
    while (temp != NULL)
    {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}

void pint(void)
{
    if (top == NULL)
        error_pint(0);

    printf("%d\n", top->n);
}

void pop(void)
{
    stack_t *temp;

    if (top == NULL)
        error_pop(0);

    temp = top;
    top = top->next;
    free(temp);
}

void swap(void)
{
    int temp;

    if (top == NULL || top->next == NULL)
        error_swap(0);

    temp = top->n;
    top->n = top->next->n;
    top->next->n = temp;
}

void add(void)
{
    stack_t *temp;

    if (top == NULL || top->next == NULL)
        error_add(0);

    temp = top;
    top = top->next;
    top->n += temp->n;
    free(temp);
}

void sub(void)
{
    stack_t *temp;

    if (top == NULL || top->next == NULL)
        error_sub(0);

    temp = top;
    top = top->next;
    top->n -= temp->n;
    free(temp);
}

void mul(void)
{
    stack_t *temp;

    if (top == NULL || top->next == NULL)
        error_mul(0);

    temp = top;
    top = top->next;
    top->n *= temp->n;
    free(temp);
}

void div_op(void)
{
    stack_t *temp;

    if (top == NULL || top->next == NULL)
        error_div(0);

    if (top->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", 0);
        exit(EXIT_FAILURE);
    }

    temp = top;
    top = top->next;
    top->n /= temp->n;
    free(temp);
}

void mod(void)
{
    stack_t *temp;

    if (top == NULL || top->next == NULL)
        error_mod(0);

    if (top->n == 0)
    {
        fprintf(stderr, "L%d: division by zero\n", 0);
        exit(EXIT_FAILURE);
    }

    temp = top;
    top = top->next;
    top->n %= temp->n;
    free(temp);
}

void pchar(void)
{
    if (top == NULL)
        error_pchar(0);

    if (top->n < 0 || top->n > 127)
    {
        fprintf(stderr, "L%d: can't pchar, value out of range\n", 0);
        exit(EXIT_FAILURE);
    }

    printf("%c\n", top->n);
}

void pstr(void)
{
    stack_t *temp;

    temp = top;
    while (temp != NULL && temp->n != 0 && (temp->n >= 0 && temp->n <= 127))
    {
        printf("%c", temp->n);
        temp = temp->next;
    }
    printf("\n");
}

void rotl(void)
{
    stack_t *last;

    if (top == NULL || top->next == NULL)
        return;

    last = top;
    while (last->next != NULL)
        last = last->next;

    last->next = top;
    top = top->next;
    last->next->next = NULL;
}

void rotr(void)
{
    stack_t *last, *second_last;

    if (top == NULL || top->next == NULL)
        return;

    last = top;
    second_last = NULL;
    while (last->next != NULL)
    {
        second_last = last;
        last = last->next;
    }

    last->next = top;
    top = last;
    second_last->next = NULL;
}

void stack(void)
{
    format = 0;
}

void queue(void)
{
    format = 1;
}

int is_integer(const char *str)
{
    if (str == NULL || *str == '\0' || isspace(*str))
        return 0;

    char *endptr;
    strtol(str, &endptr, 10);

    return (*endptr == '\0');
}

int is_valid_opcode(char *opcode)
{
    if (opcode == NULL || opcode[0] == '\0' || opcode[0] == '#')
        return 0;

    return 1;
}

int atoi_error(const char *str)
{
    if (!is_integer(str))
    {
        fprintf(stderr, "L%d: usage: push integer\n", 0);
        exit(EXIT_FAILURE);
    }

    return atoi(str);
}

void error_usage_push(unsigned int line_number)
{
    fprintf(stderr, "L%d: usage: push integer\n", line_number);
    exit(EXIT_FAILURE);
}

void error_push(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't push, stack overflow\n", line_number);
    exit(EXIT_FAILURE);
}

void error_pint(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
    exit(EXIT_FAILURE);
}

void error_pop(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
    exit(EXIT_FAILURE);
}

void error_swap(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_add(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_sub(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_mul(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't mul, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_div(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't div, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_mod(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_pchar(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
    exit(EXIT_FAILURE);
}

void error_pstr(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't pstr, stack empty\n", line_number);
    exit(EXIT_FAILURE);
}

void error_rotl(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't rotl, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_rotr(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't rotr, stack too short\n", line_number);
    exit(EXIT_FAILURE);
}

void error_stack(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't use stack on an empty stack\n", line_number);
    exit(EXIT_FAILURE);
}

void error_queue(unsigned int line_number)
{
    fprintf(stderr, "L%d: can't use queue on an empty stack\n", line_number);
    exit(EXIT_FAILURE);
}

void error_malloc(void)
{
    fprintf(stderr, "Error: malloc failed\n");
    exit(EXIT_FAILURE);
}
