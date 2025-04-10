%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(const char *msg);
    int yylex(void);
%}
%token NUM ID NL SEMICOLON DTYPE COMMA EQUAL
%%
stmt:exp1 NL {printf("Valid Expression\n");exit(0);};
exp1: exp SEMICOLON | DTYPE exp SEMICOLON
exp: X COMMA exp
| X EQUAL exp |X
X:ID |NUM
;
%%
void yyerror(const char *msg){
    printf("Invalid Expression\n");
    exit(0);
}
int main(){
    printf("Enter an Expression:");
    yyparse();
}