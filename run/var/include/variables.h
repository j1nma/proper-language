#ifndef __VARIABLES_H
#define __VARIABLES_H

#include <stdint.h>

#define MAX_VARIABLES 1000

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

variable assignVariable(int id, variable assigned);

void printVariable(variable v);

void freeVariable(variable *v);

#endif
