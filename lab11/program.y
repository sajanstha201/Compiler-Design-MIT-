%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    int yylex(void);
    void yyerror(char *str);
    int tempCount=0;
    char *newTemp(){
    char buffer[10];
    sprintf(buffer,"t%d",tempCount++);
    return strdup(buffer);
}
%}
%union{
    char *str;
}
%token <str> IF ELSE NUM NL ID
%type <str> exp pexp
%left '+' '-'
%left '*' '/'
%left '<' '>'
%%
stat: exp NL| {printf("Valid Expressoin\n");exit(0);};
exp: IF'(' exp ')' '{' exp '}' ELSE '{'exp'}' {
        printf("IF %s GO TO %s\n",$3,$6);
        printf("ELSE GO TO %s\n",$10);
    }
    | IF '{' exp '}' {if($3){printf("GO TO %s\n",$3);}}
    | pexp
    | ID '=' pexp {char *temp=newTemp(); printf("%s =%s\n",temp,$3);$1=temp;};
pexp: pexp '+' pexp {char *temp=newTemp();printf("%s= %s + %s\n",temp,$1,$3);$$=temp;}
    | pexp '-' pexp {char *temp=newTemp();printf("%s= %s - %s\n",temp,$1,$3);$$=temp;}
    | pexp '*' pexp {char *temp=newTemp();printf("%s= %s * %s\n",temp,$1,$3);$$=temp;}
    | pexp '/' pexp {char *temp=newTemp();printf("%s= %s / %s\n",temp,$1,$3);$$=temp;}
    | pexp '>' pexp {char *temp=newTemp();printf("%s= %s > %s\n",temp,$1,$3);$$=temp;}
    | pexp '<' pexp {char *temp=newTemp();printf("%s= %s < %s\n",temp,$1,$3);$$=temp;}
    | NUM
    | ID;
%%
void yyerror(char *str){
    printf("Error %s\n",str);
    exit(0);
}
int main(){
    printf("Enter a epression:\n");
    yyparse();
}