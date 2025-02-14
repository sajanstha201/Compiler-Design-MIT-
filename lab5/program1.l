%{
    #include<stdio.h>
    #include<string.h>
    #include<stdlib.h>
    int num_vow=0;
    int num_const=0;
%}
%%
[aeiouAEIOU] {num_vow++;}
[a-zA-Z] {num_const++;}
%%
int yywrap(){
    return 1;
}
int main(){
    yyin=fopen("text.c","r");
    yyout=stdout;
    yylex();
    printf("Vowel Number: %d\nConsonant Number: %d\n",num_vow,num_const);
    return 0;
}