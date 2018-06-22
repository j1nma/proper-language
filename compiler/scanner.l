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

[\t \n]	;
"Dear Sir or Madam," {return MAIN_START;}
"Sincerely,\nMr. Proper"		{return MAIN_END;}
"Please show"    	{return PRINT;}

[\(\)]				{return *yytext;}

{digit}+   			{
						yylval.intval = atoi(yytext);
						return INT;
					}

{digit}+\.{digit}+  { 	yylval.floatval = atof(yytext);
						return FLT;
						}

"."					{return END_LINE;}

{alpha}({alpha}|{digit})*  {
								yylval.stringval = malloc(strlen(yytext)+1);
								strcpy(yylval.stringval, yytext);
								return IDENTIFIER;
							}
							
\"[^\"]*\"			{
					int len = strlen(yytext);
					char * str = malloc(len-1);
					strncpy(str, yytext + 1, len - 2);
					str[len-2] = '\0';
					yylval.stringval = str;
					return STR;
					}

	.               {return yytext[0];}

%%
