all:
	lex scanner.l
	yacc -d parser.y
	gcc -Wall -o proper_compiler y.tab.c ast.c lex.yy.c -ly

debug:
	lex scanner.l
	yacc -d --debug --verbose parser.y
	gcc -Wall -o proper_compiler y.tab.c ast.c lex.yy.c -ly

clean:
	rm y.tab.c
	rm y.tab.h
	rm lex.yy.c
	rm proper_compiler