#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/variables_manipulate.h"

#define NUMBER_SIZE 15

static variable intVariablesSum(variable v1, variable v2, int sign);
static variable floatVariablesSum(variable v1, variable v2, int sign);

static variable intVariablesProd(variable v1, variable v2);
static variable floatVariablesProd(variable v1, variable v2);

static variable intVariablesDiv(variable v1, variable v2);
static variable floatVariablesDiv(variable v1, variable v2);

/**
 * Allows for binary sum, sub, prod and div to be between int and floats.
 * Specify sign for sum and substraction operations.
 * */

variable variablesSum(variable v1, variable v2)
{

    int sign = 1;

    switch (v1.type)
    {
    case TYPE_INT:
        return intVariablesSum(v1, v2, sign);
    case TYPE_FLOAT:
        return floatVariablesSum(v1, v2, sign);
    default:
        fprintf(stderr, "Error: variable type not allowed for sum.\n");
        exit(0);
    }
}

variable variablesSub(variable v1, variable v2)
{
    int sign = -1;

    switch (v1.type)
    {
    case TYPE_INT:
        return intVariablesSum(v1, v2, sign);
    case TYPE_FLOAT:
        return floatVariablesSum(v1, v2, sign);
    default:
        fprintf(stderr, "Error: variable type not allowed for substraction.\n");
        exit(0);
    }
}

variable variablesProd(variable v1, variable v2)
{
    switch (v1.type)
    {
    case TYPE_INT:
        return intVariablesProd(v1, v2);
    case TYPE_FLOAT:
        return floatVariablesProd(v1, v2);
    default:
        fprintf(stderr, "Error: variable type not allowed for product.\n");
        exit(0);
    }
}

variable variablesDiv(variable v1, variable v2)
{
    switch (v1.type)
    {
    case TYPE_INT:
        return intVariablesDiv(v1, v2);
    case TYPE_FLOAT:
        return floatVariablesDiv(v1, v2);
    default:
        fprintf(stderr, "Error: variable type not allowed for division.\n");
        exit(0);
    }
}

/**
 * Negative sign for integers and floats.
 * */
variable variableNegative(variable v)
{

    switch (v.type)
    {
    case TYPE_INT:
        v.value.intValue = -v.value.intValue;
        break;
    case TYPE_FLOAT:
        v.value.floatValue = -v.value.floatValue;
        break;
    default:
        fprintf(stderr, "Error: variable type not allowed for negative sign.\n");
        exit(0);
    }

    return v;
}

static variable intVariablesSum(variable v1, variable v2, int sign)
{
    switch (v2.type)
    {
    case TYPE_INT:
    {
        return createIntVariable(v1.value.intValue + v2.value.intValue * sign);
    }
    case TYPE_FLOAT:
    {
        return createFloatVariable(v1.value.intValue + v2.value.floatValue * sign);
    }
    default:
        fprintf(stderr, "Error: variable type not allowed for sum.\n");
        exit(0);
    }
}

static variable floatVariablesSum(variable v1, variable v2, int sign)
{
    switch (v2.type)
    {
    case TYPE_INT:
    {
        return createIntVariable(v1.value.floatValue + v2.value.intValue * sign);
    }
    case TYPE_FLOAT:
    {
        return createFloatVariable(v1.value.floatValue + v2.value.floatValue * sign);
    }
    default:
        fprintf(stderr, "Error: variable type not allowed for sum.\n");
        exit(0);
    }
}

static variable intVariablesProd(variable v1, variable v2)
{
    switch (v2.type)
    {
    case TYPE_INT:
    {
        return createIntVariable(v1.value.intValue * v2.value.intValue);
    }
    case TYPE_FLOAT:
    {
        return createFloatVariable(v1.value.intValue * v2.value.floatValue);
    }
    default:
        fprintf(stderr, "Error: variable type not allowed for product.\n");
        exit(0);
    }
}

static variable floatVariablesProd(variable v1, variable v2)
{
    switch (v2.type)
    {
    case TYPE_INT:
    {
        return intVariablesProd(v2, v1);
    }
    case TYPE_FLOAT:
    {
        return createFloatVariable(v1.value.floatValue * v2.value.floatValue);
    }
    default:
        fprintf(stderr, "Error: variable type not allowed for product.\n");
        exit(0);
    }
}

static variable intVariablesDiv(variable v1, variable v2)
{
    switch (v2.type)
    {
    case TYPE_INT:
    {
        return createIntVariable(v1.value.intValue / v2.value.intValue);
    }
    case TYPE_FLOAT:
    {
        return createFloatVariable(v1.value.intValue / v2.value.floatValue);
    }
    default:
        fprintf(stderr, "Error: variable type not allowed for division.\n");
        exit(0);
    }
}

static variable floatVariablesDiv(variable v1, variable v2)
{
    switch (v2.type)
    {
    case TYPE_INT:
    {
        return createFloatVariable(v1.value.intValue / v2.value.intValue);
    }
    case TYPE_FLOAT:
    {
        return createFloatVariable(v1.value.intValue / v2.value.floatValue);
    }
    default:
        fprintf(stderr, "Error: variable type not allowed for division.\n");
        exit(0);
    }
}