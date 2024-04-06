#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

double memory = 0; // Memory variable

// Function declarations
void calculate(char *expression);
double evaluate(char *expression);
double parseExpression(char **expression);
double parseTerm(char **expression);
double parseFactor(char **expression);
double parseNumber(char **expression);
void handleMemory(char *expression);
double parseTrigFunction(char **expression);
double parseMathFunction(char **expression);

int main() {
    char expression[MAX_INPUT_LENGTH];

    printf("Terminal Calculator\n");
    printf("Enter an expression (e.g., 5 + 3) or 'quit' to exit: ");

    while (fgets(expression, sizeof(expression), stdin)) {
        if (strcmp(expression, "quit\n") == 0) {
            printf("Exiting...\n");
            break;
        }

        // Remove trailing newline character
        expression[strcspn(expression, "\n")] = 0;

        // Check for memory operations
        handleMemory(expression);

        // Calculate the result
        calculate(expression);

        printf("Enter another expression or 'quit' to exit: ");
    }

    return 0;
}

void calculate(char *expression) {
    double result = evaluate(expression);
    printf("Result: %.2lf\n", result);
}

double evaluate(char *expression) {
    return parseExpression(&expression);
}

double parseExpression(char **expression) {
    double result = parseTerm(expression);

    while (**expression == '+' || **expression == '-') {
        char op = *(*expression)++;
        double term = parseTerm(expression);

        if (op == '+')
            result += term;
        else if (op == '-')
            result -= term;
    }

    return result;
}

double parseTerm(char **expression) {
    double result = parseFactor(expression);

    while (**expression == '*' || **expression == '/') {
        char op = *(*expression)++;
        double factor = parseFactor(expression);

        if (op == '*')
            result *= factor;
        else if (op == '/') {
            if (factor == 0) {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
            result /= factor;
        }
    }

    return result;
}

double parseFactor(char **expression) {
    if (**expression == '(') {
        (*expression)++;
        double result = parseExpression(expression);
        if (**expression != ')') {
            printf("Error: Missing closing parenthesis\n");
            exit(EXIT_FAILURE);
        }
        (*expression)++;
        return result;
    } else if (**expression == 's' || **expression == 'c' || **expression == 't') {
        return parseTrigFunction(expression);
    } else if (**expression == 's' || **expression == 'l' || **expression == 'e') {
        return parseMathFunction(expression);
    }

    return parseNumber(expression);
}

double parseTrigFunction(char **expression) {
    char functionName[4] = "";
    sscanf(*expression, "%3s", functionName);

    if (strcmp(functionName, "sin") == 0) {
        *expression += 3;
        return sin(parseFactor(expression));
    } else if (strcmp(functionName, "cos") == 0) {
        *expression += 3;
        return cos(parseFactor(expression));
    } else if (strcmp(functionName, "tan") == 0) {
        *expression += 3;
        return tan(parseFactor(expression));
    } else {
        printf("Error: Invalid function\n");
        exit(EXIT_FAILURE);
    }
}

double parseMathFunction(char **expression) {
    char functionName[4] = "";
    sscanf(*expression, "%3s", functionName);

    if (strcmp(functionName, "sqrt") == 0) {
        *expression += 4;
        return sqrt(parseFactor(expression));
    } else if (strcmp(functionName, "log") == 0) {
        *expression += 3;
        return log(parseFactor(expression));
    } else if (strcmp(functionName, "exp") == 0) {
        *expression += 3;
        return exp(parseFactor(expression));
    } else {
        printf("Error: Invalid function\n");
        exit(EXIT_FAILURE);
    }
}

double parseNumber(char **expression) {
    double result = 0.0;
    char *start = *expression;
    while (**expression >= '0' && **expression <= '9') {
        (*expression)++;
    }

    if (**expression == '.') {
        (*expression)++;
        while (**expression >= '0' && **expression <= '9') {
            (*expression)++;
        }
    }

    if (*expression != start) {
        char number[MAX_INPUT_LENGTH];
        strncpy(number, start, *expression - start);
        number[*expression - start] = '\0';
        result = atof(number);
    } else {
        printf("Error: Invalid expression\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

void handleMemory(char *expression) {
    if (strcmp(expression, "MC") == 0) {
        memory = 0;
        printf("Memory Cleared\n");
        printf("Enter another expression or 'quit' to exit: ");
        exit(EXIT_SUCCESS);
    } else if (strcmp(expression, "MR") == 0) {
        printf("Memory Recall: %.2lf\n", memory);
        printf("Enter another expression or 'quit' to exit: ");
        exit(EXIT_SUCCESS);
    } else if (strstr(expression, "M+") != NULL) {
        memory += evaluate(expression + 2);
        printf("Memory Added\n");
        printf("Enter another expression or 'quit' to exit: ");
        exit(EXIT_SUCCESS);
    } else if (strstr(expression, "M-") != NULL) {
        memory -= evaluate(expression + 2);
        printf("Memory Subtracted\n");
        printf("Enter another expression or 'quit' to exit: ");
        exit(EXIT_SUCCESS);
    }
}
