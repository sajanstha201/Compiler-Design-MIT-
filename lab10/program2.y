%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(const char *msg);
    int yylex(void);
%}
%token IF ELSE EXP LP RP NL LC RC
%%
stmt: exp NL {printf("Valid Expression");exit(0);};
exp: IF LP EXP RP LC exp RC ELSE LC exp RC | IF LP EXP RP LC exp RC |EXP;
%%
void yyerror(const char *mgs){
    printf("Invalid Expression\n");
    exit(0);
}
int main(){
    printf("Enter Expression: ");
    yyparse();
}