%{#include<stdio.h>
    int num_p=0,num_s=0;
%}
%%
"printf" {
    fprintf(yyout,"%s","WRITE");
    num_p++;
}
"scanf" {
    fprintf(yyout,"%s","READ");
    num_s++;
}
. {fputc(yytext[0],yyout);}
%%
int yywrap(){return 1;}
int main(){
    yyin=fopen("text.c","r");
    yyout=fopen("p4_out.c","w+");
    yylex();
    printf("Number of printf: %d\n Number of scanf: %d\n",num_p,num_s);
    return 0;
}