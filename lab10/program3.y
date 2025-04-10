%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(const char *msg);
    int yylex(void);
%}
%token NL NUM EXP ADD MUL SUB DIV POW
%%
stmt: input {printf("Valid Expression");exit(0);};
input: Y ;
Y: |line;
line: NL | exp NL ;
exp: NUM X;
X: exp ADD X |exp SUB X |exp MUL X | exp DIV X |exp POW X|;
%%
void yyerror(const char * msg){
    printf("Invalid ExpressioN");
    exit(0);
}
int main(){
    printf("Enter Expression:");
    yyparse();
}