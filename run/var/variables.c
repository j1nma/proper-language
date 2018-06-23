#include "include/variables.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

/* symbol/variable table where objects of program are allocated */
variable *variableTable[MAX_VARIABLES] = {0};

/* symbol/variable table where objects' names of program are allocated */
char *variableNameTable[MAX_VARIABLES] = {0};

void addVariableNameToId(int id, char *name)
{
    variableNameTable[id] = name;
}

variable getVariableFromId(int id)
{
    if (variableTable[id] == NULL)
    {
        fprintf(stderr, "Error: '%s' variable name not found.\n", variableNameTable[id]);
        exit(1);
    }
    return *variableTable[id];
}

char *getVariableType(variableType type)
{
    switch (type)
    {
    case TYPE_INT:
        return "integer";
    case TYPE_FLOAT:
        return "float";
    case TYPE_STRING:
        return "string";
    default:
        return "unknown";
    }
    return "";
}

variable createIntVariable(int value)
{
    variable v;
    v.type = TYPE_INT;
    v.value.intValue = value;
    return v;
}

variable createFloatVariable(float value)
{
    variable v;
    v.type = TYPE_FLOAT;
    v.value.floatValue = value;
    return v;
}

variable createStringVariable(char *value)
{
    variable v;
    v.type = TYPE_STRING;
    v.value.stringValue = malloc(strlen(value) + 1);
    strcpy(v.value.stringValue, value);
    return v;
}

variable assignVariable(int id, variable v)
{

    variable *res = malloc(4 * sizeof(*variableTable[0]));
    res->type = v.type;

    switch (v.type)
    {
    case TYPE_INT:
        res->value.intValue = v.value.intValue;
        break;

    case TYPE_FLOAT:
        res->value.floatValue = v.value.floatValue;
        break;

    case TYPE_STRING:
        res->value.stringValue = malloc(strlen(v.value.stringValue) + 1);
        strcpy(res->value.stringValue, v.value.stringValue);
        break;
    }

    freeVariable(variableTable[id]);
    variableTable[id] = res;

    return *res;
}

void printVariable(variable v)
{
    switch (v.type)
    {
    case TYPE_INT:
        printf("%d", v.value.intValue);
        break;
    case TYPE_FLOAT:
        printf("%f", v.value.floatValue);
        break;
    case TYPE_STRING:
        printf("%s", v.value.stringValue);
        break;
    }

    printf("\n");
}

void readVariable(variableType type, int id)
{
    if (type == TYPE_INT || type == TYPE_FLOAT)
    {
        double num;

        /* lg double [footnote] number with up to six digits of precision */
        scanf("%lg", &num);

        while (getchar() != '\n')
            ;

        if (ABS(num - (long)num) < FLOAT_ERROR)
        {
            assignVariable(id, createIntVariable((int)num));
        }
        else
        {
            assignVariable(id, createFloatVariable(num));
        }
    }
    else if (type == TYPE_STRING)
    {
        char *str = malloc(READ_STRING_SIZE);

        /* The buffer length is 1024, which includes room for the possible 
        1023 characters plus the null terminator: */
        scanf("%1023[^\n]", str);

        while (getchar() != '\n')
            ;

        assignVariable(id, createStringVariable(str));

        free(str);
    }
}

void freeVariable(variable *v)
{
    if (v == NULL)
        return;

    switch (v->type)
    {
    case TYPE_STRING:
        free(v->value.stringValue);
        break;
    default:
        /* nothing to be freed for TYPE_INT and TYPE_INT */
        break;
    }
}
