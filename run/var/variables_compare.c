#include "include/variables_compare.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int compareVariableTypes(variableType t1, variableType t2);
static int compareVariableWithInt(variable intVar, variable other);
static int compareVariableWithFloat(variable floatVar, variable other);
static int compareVariableWithString(variable strVar, variable other);

int compare(variable v1, variable v2)
{
    switch (v1.type)
    {
    case TYPE_INT:
        return compareVariableWithInt(v1, v2);
    case TYPE_FLOAT:
        return compareVariableWithFloat(v1, v2);
    case TYPE_STRING:
        return compareVariableWithString(v1, v2);
    default:
        printf("Error: non-matching variable types.\n");
        exit(0);
    }
}

/* A distintion is being made here: a float and integer can be compared with each other */
static int compareVariableTypes(variableType t1, variableType t2)
{
    return t1 == t2 || (t1 == TYPE_INT && t2 == TYPE_FLOAT) || (t1 == TYPE_FLOAT && t2 == TYPE_INT);
}

static int compareVariableWithInt(variable v, variable intVariable)
{

    float floatDiff = 0;

    switch (v.type)
    {
    case TYPE_INT:
        return v.value.intValue - intVariable.value.intValue;

    case TYPE_FLOAT:
        floatDiff = v.value.floatValue - intVariable.value.intValue;
        return fabs(floatDiff) < FLOAT_ERROR ? 0 : floatDiff;

    default:
        printf("Error: unknown variable type for first variable.\n");
        exit(0);
    }
}

static int compareVariableWithFloat(variable v, variable floatVariable)
{
    float floatDiff = 0;

    switch (v.type)
    {
    case TYPE_INT:
        return -compareVariableWithInt(floatVariable, v);

    case TYPE_FLOAT:
        floatDiff = v.value.floatValue - floatVariable.value.floatValue;
        return fabs(floatDiff) < FLOAT_ERROR ? 0 : floatDiff;

    default:
        printf("Error: unknown variable type for first variable.\n");
        exit(0);
    }
}

static int compareVariableWithString(variable v, variable stringVariable)
{
    switch (v.type)
    {
    case TYPE_STRING:
        return strcmp(v.value.stringValue, stringVariable.value.stringValue);
    default:
        printf("Error: unknown variable type for first variable.\n");
        exit(0);
    }
}

int equals(variable v1, variable v2)
{
    return compareVariableTypes(v1.type, v2.type) ? (compare(v1, v2) == 0) : 0;
}
