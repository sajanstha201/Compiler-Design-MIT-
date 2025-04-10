%{
    #include<stdio.h>
    #include<stdlib.h>
    void statement();
    void loopingStat();
%}
int yywrap(return 1;)
void statement(){
    assignStat();
    if(strcmp(root->lexemeName,";")==0){
        match(root);
        return;
    }
    decisionStat();
    loopingStat();
}
void loopingStat(){
    if(root->type==WHILE){
        match(root);
        if(strcmp(root->lexemeName,"(")==0){
            match(root);
            expn();
            if(strcmp(root->lexemeName,")")==0){
                match(root);
                if(strcmp(root->lexemeName,"{")){
                    match(root);
                    statementList();
                    if(strcmp(root->lexemeName,"}")==0){
                        match(root);
                    }
                    else invalid(root,"missing }");
                }
                else invalid(root,"missing {");
            }
            else invlaid(root,"missing )");
        }
        else invalid(root,"missing (");
    }
    else if(root->type==FOR){
        match(root);
        if(strcmp(root->lexemeName,"(")==0){
            match(root);
            assingStat();
            if(strcmp(root->lexemeName,";")==0){
                match(root);
                expn();
                if(strcmp(root->lexemeName,";")==0){
                    match(root);
                    assingStat();
                    if(strcmp(root->lexemeName,"{")==0){
                        match(root);
                        statementList();
                        if(strcmp(root->lexemeName,"}")==0){
                            match(root);
                        }
                        else invalid(root,"misssing }");
                    }
                    else invalid(root,"missing {");
                }
                else invalid(root,"missing ;");
            }
            else invalid(root,"missing ;");
        }
        else invalid(root,"missing (");
    }
}