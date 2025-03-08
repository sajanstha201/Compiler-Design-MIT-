%{#include<stdio.h>
int num_words=0,num_char=0,num_blanks=0,num_lines=1;
int in_words=0;
%}
%%
\n {num_lines++;in_words=0;}
" "|\t {num_blanks++;in_words=0;}
[a-zA-Z] {
    num_char++;
    if(!in_words){
        num_words++;
        in_words=1;
    }
    }
%%
int yywrap(){
    return 1;
}
int main(){
    yyin=fopen("text.c","r");
    yylex();
    printf("\nNumber of words: %d\n Number of Char: %d\n Number of Blanks: %d\n Number of Lines: %d\n",num_words,num_char,num_blanks,num_lines);
}