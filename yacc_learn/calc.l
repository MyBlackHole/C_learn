%{   /*%{%}包裹c代码，这部分代码会被原样输出*/
#include <stdio.h>

#include "calc.tab.h"   /*.y文件经yacc编译后会生成这个头文件*/

int
yywrap(void)
{
    return 1;
}
%}
%%
"+"     return ADD;  /*定义加减乘除，回车返回执行结果的规则*/
"-"     return SUB;
"*"     return MUL;
"/"     return DIV;
"\n"    return CR;
([1-9][0-9]*)|0 {  /*正则表达式，表示接收非0开头的数字或者0*/
    int temp;
    sscanf(yytext,"%d",&temp);
    yylval.int_value=temp;
    return INT_LITERAL;  /*返回整数运算结果*/
}
[ \t] ;
. {
    (void)input;
    (void)yyunput;
    fprintf(stderr,"lexical error.\n");
    exit(1);
}
%%
