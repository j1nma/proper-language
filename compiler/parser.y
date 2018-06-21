%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/ast.h"

#define MAX_IDENTIFIERS 1000


int yylex();
void yyerror (char const *s);


char * identifiers[MAX_IDENTIFIERS] = {0};

int getOrAddId(char * strId) {
	int i;

	for(i = 0 ; i < MAX_IDENTIFIERS && identifiers[i] != NULL ; i++){
		if(!strcmp(identifiers[i], strId)){
			return i;
		}
	}

	if(i == MAX_IDENTIFIERS){
		return -1;
	}

	identifiers[i] = malloc(strlen(strId) + 1);
	strcpy(identifiers[i], strId);
	printf("addVariableNameToId(%d, \"%s\");\n", i, strId);

	return i;

}

%}


%union {
	int intval;
	float floatval;
	char * stringval;

	booleanOperator booleanoperator;

  	assignmentNode * assignmentnode;
	ifElseIfNode * ifnode;
	whileNode * whilenode;

  	expressionNode * expressionnode;

	boolNode * boolnode;

  	statementNode * statementnode;

	blockNode * block;
}

%error-verbose

%token <intval> INT;
%token <floatval> FLT;
%token <stringval> STR;
%token <stringval> IDENTIFIER;

%token PRINT;
%token READ;
%token NUMBER;
%token TEXT;

%token SAY;
%token IS;

%token DELIM;

%token IF;
%token ELSEIF;
%token ELSE;

%token WHILE;
%token UNTIL;
%token DO;
%token WHILE_END;
%token END;

%token AND;
%token NOT;
%token OR;

%token EQ;
%token NEQ;
%token LE;
%token LT;
%token GE;
%token GT;

%token EXIT;

/* specify the associativity of an operator */
%left AND
%left OR
%left NOT
%left LE GE EQ
%left '+' '-';
%left '*' '/';

%type <booleanoperator> bool_operator;

%type <assignmentnode> assign;
%type <ifnode> if;
%type <ifnode> elseif;
%type <whilenode> while;

%type <expressionnode> print;
%type <expressionnode> expression;
%type <boolnode> condition;

%type <statementnode> program;
%type <block> block;

%start entry

%%

entry: program {
			getCode($1);
	  	}

program: block {
		   	$$ = malloc(sizeof(*$$));
			$$->type = $1->type;
			$$->elem = $1->node;
			$$->next = NULL;
			free($1);
		}
		| block program {
			$$ = malloc(sizeof(*$$));
			$$->type = $1->type;
			$$->elem = $1->node;
			$$->next = $2;
			free($1);
		}
		;

block: print {
			$$ = malloc(sizeof(*$$));
			$$->type = PRINT_CALL;
			$$->node = $1;
		}
		| assign {
			$$ = malloc(sizeof(*$$));
			$$->type = ASSIGNMENT;
			$$->node = $1;
		}
		| if {
			$$ = malloc(sizeof(*$$));
			$$->type = IF_THEN_ELSE;
			$$->node = $1;
		}
		| while {
			$$ = malloc(sizeof(*$$));
			$$->type = WHILE_BLOCK;
			$$->node = $1;
		}
		| exit {
			$$ = malloc(sizeof(*$$));
			$$->type = EXIT_CALL;
		}
		;

exit: EXIT;
assign: SAY IDENTIFIER IS expression {
	 		$$ = malloc(sizeof(*$$));
	 		$$->variableId = getOrAddId($2);
	 		$$->expression = $4;
	 	}
	 ;

expression: IDENTIFIER {
			$$ = malloc(sizeof(*$$));
			$$->type = VARIABLE;
			$$->left = malloc(sizeof(int));
			int id = getOrAddId($1);
			memcpy($$->left, &id, sizeof(int));
	 	}
		| INT {
	 		$$ = malloc(sizeof(*$$));
			$$->type = INTEGER;
			$$->left = malloc(sizeof(int));
			memcpy($$->left, &$1, sizeof(int));
		}
		| FLT {
	 		$$ = malloc(sizeof(*$$));
			$$->type = FLOAT;
			$$->left = malloc(sizeof(float));
			memcpy($$->left, &$1, sizeof(float));
	 	}
		| STR {
			$$ = malloc(sizeof(*$$));
			$$->type = STRING;
			$$->left = malloc(strlen($1) + 1);
			strcpy($$->left, $1);
		}
		| '-' expression {
	 		$$ = malloc(sizeof(*$$));
			$$->type = NEGATIVE;
			$$->left = $2;
	 	}
		| expression '+' expression {
			$$ = malloc(sizeof(*$$));
			$$->type = BINARY_ADD;
			$$->left = $1;
			$$->right = $3;
		}
		| expression '-' expression {
	 		$$ = malloc(sizeof(*$$));
			$$->type = BINARY_SUB;
			$$->left = $1;
			$$->right = $3;
		}
		|  expression '*' expression {
	 		$$ = malloc(sizeof(*$$));
			$$->type = BINARY_PROD;
			$$->left = $1;
			$$->right = $3;
	 	}
		| expression '/' expression {
			$$ = malloc(sizeof(*$$));
			$$->type = BINARY_DIV;
			$$->left = $1;
			$$->right = $3;
		}
		| '(' expression ')' {
			$$ = $2;
		}
		;

print: PRINT expression {
			$$ = $2;
		}
		;

while: WHILE DELIM condition DELIM DO program WHILE_END {
			$$ = malloc(sizeof(*$$));
			$$->condition = $3;
			$$->block = $6;
			}
		| UNTIL DELIM condition DELIM DO program WHILE_END {
				$$ = malloc(sizeof(*$$));
				$$->condition = malloc(sizeof(*$$->condition));
				$$->condition->type = BOOLEAN_NOT;
				$$->condition->left = $3;
				$$->block = $6;
			}
		;

if: IF DELIM condition DELIM DO program END {
			$$ = malloc(sizeof(*$$));
			$$->condition = $3;
			$$->block = $6;
			$$->elseif = NULL;
		}
		| IF DELIM condition DELIM DO program elseif END {
			$$ = malloc(sizeof(*$$));
			$$->condition = $3;
			$$->block = $6;
			$$->elseif = $7;
		}

elseif: ELSEIF DELIM condition DELIM program {
			$$ = malloc(sizeof(*$$));
			$$->condition = $3;
			$$->block = $5;
			$$->elseif = NULL;
		}
		| ELSEIF DELIM condition DELIM program elseif {
			$$ = malloc(sizeof(*$$));
			$$->condition = $3;
			$$->block = $5;
			$$->elseif = $6;
		}
		| ELSE program {
			$$ = malloc(sizeof(*$$));
			$$->block = $2;
			$$->elseif = NULL;
			$$->condition = malloc(sizeof(*$$->condition));
			$$->condition->type = BOOLEAN_TRUE;
		}
		;

condition: expression bool_operator expression {
			$$ = malloc(sizeof(*$$));
			$$->type = $2;
			$$->left = $1;
			$$->right = $3;
		}
		| condition AND condition {
			$$ = malloc(sizeof(*$$));
			$$->type = BOOLEAN_AND;
			$$->left = $1;
			$$->right = $3;
		}
		| condition OR condition {
			$$ = malloc(sizeof(*$$));
			$$->type = BOOLEAN_OR;
			$$->left = $1;
			$$->right = $3;
		}
		| NOT condition {
			$$ = malloc(sizeof(*$$));
			$$->type = BOOLEAN_NOT;
			$$->left = $2;
			$$->right = NULL;
		}
		;

bool_operator: EQ { $$ = BOOLEAN_EQ;  }
			| NEQ { $$ = BOOLEAN_NEQ; }
			| LE { $$ = BOOLEAN_LE;  }
			| LT { $$ = BOOLEAN_LT;  }
			| GE { $$ = BOOLEAN_GE;  }
			| GT { $$ = BOOLEAN_GT;  }
			;


%%


int main()
{
	printf("#include <stdlib.h>\n");

	printf("#include \"run/var/include/variables.h\"\n");

	printf("#include \"run/var/include/variables_compare.h\"\n");

	printf("#include \"run/var/include/variables_manipulate.h\"\n\n");

    printf("int main(void) { \n");

    yyparse();

    printf("}\n");

    return 0;
}


int yywrap()
{
        return 1;
}
