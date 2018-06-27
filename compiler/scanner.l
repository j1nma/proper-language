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

[\t \nsecond]	;
Dear\ Sir\ or\ Madam,			return MAIN_START;
Sincerely,\nMr.\ Proper 		return MAIN_END;
Please\ show   					return PRINT;
please\ show   					return PRINT;

Say|say    						return SAY;
is    							return IS;

If								return IF;
Suppose\ that					return IF;

Otherwise\ if  					return ELSEIF;

Otherwise						return ELSE;
Or\ else						return ELSE;

While							return WHILE;
while							return WHILE;
Until							return UNTIL;
until							return UNTIL;
then  							return DO;
and\ that\ is\ it.				return END;
and\ repeat.					return WHILE_END;
and\ repeat\ the\ previous.		return WHILE_END;
And\ repeat\ the\ previous.		return WHILE_END;

\'								return DELIM;

and								return AND;
not								return NOT;
or\ rather						return OR;

equals							return EQ;
is\ equal\ to					return EQ;
does\ not\ equals				return NEQ;
is\ less\ than\ or\ equals\ to	return LE;
is\ less\ than					return LT;
is\ greater\ than\ or\ equals\ to 	return GE;
is\ greater\ than				return GT;

Please\ read					return READ;
a\ number						return NUMBER;
text							return TEXT;
into							return INTO;

Wait							return SLEEP;
wait							return SLEEP;
Sleep							return SLEEP;
sleep							return SLEEP;
seconds.						return SLEEP_END;
Show\ the\ Shining\ please.		return THE_SHINING;

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
