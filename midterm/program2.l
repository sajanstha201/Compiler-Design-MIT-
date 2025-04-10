%{
#include<stdio.h>
#include<stdlib.h>
FILE *gp;
%}
%%
"printf" {fprintf(gp,"WRITE");}
"scanf" {fprintf(gp,"READ");}
. {fputc(yytext[0],gp);}
%%
int yywrap(){return 1;}
int main(){
    FILE *fp=fopen("p1.txt","r");
    gp=fopen("p2.txt","w+");
    yyin=fp;
    yyout=gp;
    yylex();
}