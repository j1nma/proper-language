%{
    #include <stdlib.h>
    #include <string.h>
	#include "include/ast.h"
    #include "y.tab.h"
%}

alpha [A-Za-z_$]
digit [0-9]

%option nounput
%option noinput

%%

[\t \n]
show           		return PRINT;

[\(\)]				{return *yytext;}

{digit}+   			{
						yylval.intval = atoi(yytext);
						return INTEGER;
					}

{digit}+\.{digit}+  { 	yylval.floatval = atof(yytext);
						return FLOAT;
						}

\"[^\"]*\"			{
					int len = strlen(yytext);
					char * str = malloc(len-1);
					strncpy(str, yytext + 1, len - 2);
					str[len-2] = '\0';
					yylval.stringval = str;
					return STR;
					}

{alpha}({alpha}|{digit})*  {
								yylval.stringval = malloc(strlen(yytext)+1);
								strcpy(yylval.stringval, yytext);
								return IDENTIFIER;
							}

.               {return yytext[0];}

%%
