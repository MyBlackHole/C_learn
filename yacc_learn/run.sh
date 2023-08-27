yacc -dv calc.y
lex calc.l
cc -o calc y.tab.c lex.yy.c
