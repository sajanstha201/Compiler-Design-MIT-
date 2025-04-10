%{
    #include"program3.tab.h"
%}
%%
[\n] {return NL;}
"exp" {return EXP;}
"+" {return ADD;}
"-" {return SUB;}
"/" {return DIV;}
"*" {return MUL;}
"^" {return POW;}
[0-9]+ {return NUM;}
[ ] {}
. {exit(0);}
%%
int yywrap(){return 1;}