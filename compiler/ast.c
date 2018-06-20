#include "include/ast.h"

#define VARIABLE_SIZE 100
#define NUMBER_SIZE 15
#define STRING_SIZE 100

char *getBinaryExpression(expressionNode *expression, char *binaryOperation)
{

    char *left = getExpression((expressionNode *)expression->left);
    char *right = getExpression((expressionNode *)expression->right);

    /* +1 for '\0' */
    char *result = malloc(strlen(left) + strlen(right) + STRING_SIZE + 1);
    sprintf(result, "%s(%s, %s)", binaryOperation, left, right);

    free(left);
    free(right);

    return result;
}

char *getExpression(expressionNode *expression)
{
    char *res;

    switch (expression->type)
    {
    case VARIABLE:
    {
        res = malloc(VARIABLE_SIZE);
        sprintf(res, "getVariableFromId(%d)", *(int *)expression->left);
        free(expression->left);
        break;
    }

    case INTEGER:
    {
        res = malloc(NUMBER_SIZE);
        sprintf(res, "createIntVariable(%d)", *((int *)expression->left));
        free(expression->left);
        break;
    }

    case FLOAT:
    {
        res = malloc(NUMBER_SIZE);
        sprintf(res, "createFloatVariable(%.5f)", *((float *)expression->left));
        free(expression->left);
        break;
    }

    case STRING:
    {
        char *str = (char *)expression->left;
        res = malloc(STRING_SIZE + strlen(str));
        sprintf(res, "createStringVariable(\"%s\")", str);
        free(expression->left);
        break;
    }

    case BINARY_ADD:
    {
        res = getBinaryExpression(expression, "variablesSum");
        break;
    }

    case BINARY_SUB:
    {
        res = getBinaryExpression(expression, "variablesSub");
        break;
    }

    case BINARY_PROD:
    {
        res = getBinaryExpression(expression, "variablesProd");
        break;
    }

    case BINARY_DIV:
    {
        res = getBinaryExpression(expression, "variablesDiv");
    }
    }

    free(expression);

    return res;
}

void getCode(struct statementNode *root)
{
}