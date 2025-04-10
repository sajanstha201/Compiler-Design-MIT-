%{
#include<stdio.h>
#include<stdlib.h>
void statement();
void decisionStat();
void dprime();
%}
void statement(){
    assignStat();
    if(strcmp(root->lexemeName,";")==0){
        match(root);
        return;
    }
    decisionStat();
}
void decisionStat(){
    if(root->type==IF){
        match(root);
        if(strcmp(root->lexemeName,"(")==0){
            match(root);
            exp();
            if(strcmp(root->lexemeName,")")==0){
                match(root);
                if(strcmp(root->lexemeName,"}")==0){
                    match(root);
                    statemnentList();
                    if(strcmp(root->lexemeName,"}")==0){
                        match(root);
                        dprime();
                    }
                    else invlaid(root,"missing }");
                }
                else invalid(root,"missing {");
                
            }
            else invalid(root,"missing )")
        }
        else invalid(root,"missing (");
    }
    else invalid(root,"invlaid if statement\n");
}
void dprime(){
    if(root->type==ELSE){
        if(strcmp(root->lexemeName,"{")==0){
            match(root);
            statementList();
            if(strcmp(root->lexemeName,"}")==0){
                match(root);
            }
            else invalid(root,"} missing\n");
        }
        else invalid(root,"{ missing\n");
    }
}
int yywrap(return 1;)
int main(){
    yylex();

}