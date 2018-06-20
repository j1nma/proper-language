#ifndef __AST_H
#define __AST_H

#define TRUE 1
#define FALSE 0

typedef enum
{
    PRINT_CALL,
    ASSIGNMENT,
    IF_THEN_ELSE,
    WHILE
} statementType;

typedef enum
{
    VARIABLE,
    INTEGER,
    FLOAT,
    STRING,

    BINARY_ADD,
    BINARY_SUB,
    BINARY_PROD,
    BINARY_DIV
} expressionType;

typedef enum
{
    BOOLEAN_AND,
    BOOLEAN_NOT,
    BOOLEAN_OR,

    /* Operators for expression comparisons */
    BOOLEAN_EQ,
    BOOLEAN_NEQ,
    BOOLEAN_LE,
    BOOLEAN_LT,
    BOOLEAN_GE,
    BOOLEAN_GT,

    /* Boolean literals */
    BOOLEAN_TRUE,
    BOOLEAN_FALSE
} booleanOperator;

/*
    Linked list of statements. Each statement is of type
    statementType. The adequate information of its type 
    is pointed by elem.
*/
typedef struct statementNode
{
    void *elem;
    statementType type;
    struct statementNode *next;
} statementNode;

/*
    Node with information of type expressionType. For both unary and binary
    expressions.  
*/
typedef struct expressionNode
{
    expressionType type;
    void *left;
    void *right;
} expressionNode;

/*
	Linked list of expressions.
*/
typedef struct expressionList
{
    expressionNode *expression;
    struct expressionList *next;
} expressionList;

/*
	Node with assignment statement information (expression and variable id
    involved).
*/
typedef struct assignmentNode
{
    int variableId;
    expressionNode *expression;
} assignmentNode;

/*
    Node with booleanOperator information between boolNodes or expressionNodes. 
    May be unary or binary (left points to boolNode if unary).
*/
typedef struct boolNode
{
    booleanOperator type;
    void *left;
    void *right;
} boolNode;

/*
    Node with IF statement information. Boolean condition determines which
    struct is accessed. If condition is satisfied, block, statement, else,
    another ifElseIfNode statement. This allows for linked if statements.
*/
typedef struct ifElseIfNode
{
    boolNode *condition;
    struct statementNode *block;
    struct ifElseIfNode *elseif;
} ifElseIfNode;

/*
    Node with WHILE statement information.
*/
typedef struct whileNode
{
    boolNode *condition;
    struct statementNode *block;
} whileNode;

char *getBinaryExpression(expressionNode *expression, char *binaryOperation);
char *getExpression(expressionNode *expression);
void getCode(struct statementNode *root);

#endif