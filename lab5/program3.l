%{#include<stdio.h>
    int pos=0,neg=0,fpos=0,fneg=0;
%}
%%
-?[0-9]+\.[0-9]+ {
    if(yytext[0]=='-')fneg++;
    else fpos++;}
-?[0-9]+ {
    if(yytext[0]=='-') neg++;
    else pos++;}
%%
int yywrap(){
    return 1;
}
int main(){
    yyin=fopen("text.c","r");
    yylex();
    printf("\nPositive: %d\nNegative: %d\nFloating Positive: %d\nFloating Negative: %d\n",pos,neg,fpos,fneg);

}