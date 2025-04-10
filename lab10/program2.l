%{
    #include"program2.tab.h"
%}
%%
"if" {return IF;}
"else" {return ELSE;}
"(" {return LP;}
")" {return RP;}
"{" {return LC;}
"}" {return RC;}
[ ] {}
[\n] {return NL;}
"exp" {return EXP;}
. {exit(0);}
%%
int yywrap(){
    return 1;
}