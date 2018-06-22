#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        res = malloc(VARIABLE_SIZE + 25);
        sprintf(res, "getVariableFromId(%d)", *(int *)expression->left);
        free(expression->left);
        break;
    }

    case INTEGER:
    {
        res = malloc(NUMBER_SIZE + 25);
        sprintf(res, "createIntVariable(%d)", *((int *)expression->left));
        free(expression->left);
        break;
    }

    case FLOAT:
    {
        res = malloc(NUMBER_SIZE + 25);
        sprintf(res, "createFloatVariable(%.5f)", *((float *)expression->left));
        free(expression->left);
        break;
    }

    case STRING:
    {
        char *str = (char *)expression->left;
        res = malloc(STRING_SIZE + 25 + strlen(str));
        sprintf(res, "createStringVariable(\"%s\")", str);
        free(expression->left);
        break;
    }

    case NEGATIVE:
    {
        char *e = getExpression((expressionNode *)expression->left);
        res = malloc(strlen(e) + STRING_SIZE + 25);
        sprintf(res, "variableNegative(%s)", e);

        free(e);
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

/* Produce printing of a variable */
void producePrint(expressionNode *en)
{
    char *e = getExpression(en);
    printf("\tprintVariable(%s);\n", e);
    free(e);
}

/* Produce assignment of variable with id */
void produceAssign(assignmentNode *an)
{
    char *e = getExpression(an->expression);
    printf("\tassignVariable(%d, %s);\n", an->variableId, e);
    free(e);
}

/* Produce equals boolean node */
void produceEquals(boolNode *bn)
{
    char *e1 = getExpression((expressionNode *)bn->left);
    char *e2 = getExpression((expressionNode *)bn->right);

    printf("(equals(%s, %s))", e1, e2);

    free(e1);
    free(e2);
}

/* Produce not equals boolean node */
void produceNotEquals(boolNode *bn)
{
    printf("!");
    produceEquals(bn);
}

/* Produce compare binary boolean node */
void produceCompareBoolean(boolNode *bn, char *booleanOperator)
{
    char *e1 = getExpression((expressionNode *)bn->left);
    char *e2 = getExpression((expressionNode *)bn->right);

    printf("(compare(%s, %s) %s 0)", e1, e2, booleanOperator);

    free(e1);
    free(e2);
}

/* Produce binary boolean node */
void produceBinaryBoolean(boolNode *node, char *booleanOperator)
{
    printf("(");

    produceBoolean((boolNode *)node->left);

    printf(" %s ", booleanOperator);

    produceBoolean((boolNode *)node->right);

    printf(")");
}

/* Produce boolean node */
void produceBoolean(boolNode *bn)
{
    switch (bn->type)
    {
    case BOOLEAN_AND:
        produceBinaryBoolean(bn, "&&");
        break;

    case BOOLEAN_NOT:
        printf("!");
        produceBoolean((boolNode *)bn->left);
        break;

    case BOOLEAN_OR:
        produceBinaryBoolean(bn, "||");
        break;

    case BOOLEAN_EQ:
        produceEquals(bn);
        break;

    case BOOLEAN_NEQ:
        produceNotEquals(bn);
        break;

    case BOOLEAN_LE:
        produceCompareBoolean(bn, "<=");
        break;

    case BOOLEAN_LT:
        produceCompareBoolean(bn, "<");
        break;

    case BOOLEAN_GE:
        produceCompareBoolean(bn, ">=");
        break;

    case BOOLEAN_GT:
        produceCompareBoolean(bn, ">");
        break;

    case BOOLEAN_TRUE:
        printf("%d", TRUE);
        break;

    case BOOLEAN_FALSE:
        printf("%d", FALSE);
        break;
    }
}

/* Produce ifElseIf node */
void produceIf(ifElseIfNode *in)
{
    printf("\n\nif(");

    produceBoolean(in->condition);

    printf(") {\n");

    getCode(in->block);

    printf("}\n");

    while (in->elseif != NULL)
    {
        in = in->elseif;

        printf("else if(");

        produceBoolean(in->condition);

        printf(") {\n");

        getCode(in->block);

        printf("} ");
    }
}

/* Produce while node */
void produceWhile(whileNode *wn)
{
    printf("\n\nwhile(");

    produceBoolean(wn->condition);

    printf(") {\n");

    getCode(wn->block);

    printf("}\n\n");
}

/* Produce exit call */
void produceExit()
{
    printf("exit(0);\n");
}

/* Produce code from each statement */
void getCode(statementNode *root)
{
    while (root != NULL)
    {
        switch (root->type)
        {

        case PRINT_CALL:
            producePrint((expressionNode *)root->elem);
            break;

        case ASSIGNMENT:
            produceAssign((assignmentNode *)root->elem);
            break;

        case IF_THEN_ELSE:
            produceIf((ifElseIfNode *)root->elem);
            break;

        case WHILE_BLOCK:
            produceWhile((whileNode *)root->elem);
            break;

        case EXIT_CALL:
            produceExit();
            break;

        case START_POINT:
            printf("int main(void) { \n");
            break;

        case END_POINT:
            printf("}\n");
            break;

        default:
            break;
        }

        statementNode *prev = root;

        root = root->next;

        free(prev);
    }
}