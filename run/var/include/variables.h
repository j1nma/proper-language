#ifndef __VARIABLES_H
#define __VARIABLES_H

#include <stdint.h>

#define MAX_VARIABLES 1000
#define FLOAT_ERROR 0.00001
#define READ_STRING_SIZE 1024

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} variableType;

typedef union {
    int intValue;
    float floatValue;
    char *stringValue;
} variableValue;

typedef struct variable
{
    variableType type;
    variableValue value;
} variable;

void addVariableNameToId(int id, char *name);
variable getVariableFromId(int id);
char *getVariableType(variableType type);

variable createIntVariable(int value);
variable createFloatVariable(float value);
variable createStringVariable(char *value);

variable assignVariable(int id, variable v);

void printVariable(variable v);

void readVariable(variableType type, int elem);

void freeVariable(variable *v);

#endif
