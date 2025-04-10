%{
    #include"p1.tab.h"
    #include<stdio.h>
%}
%%
"int"|"char"|"float"|"long"|"double" {return DTYPE;}
[;] {return SEMICOLON;}
[,] {return COMMA;}
[=] {return EQUAL;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
[0-9]+ {return NUM;}
[ ] {}
[\n] {return NL;}
. {printf("invalid stirng %s\n",yytext);exit(0);}
%%
int yywrap(){
    return 1;
}