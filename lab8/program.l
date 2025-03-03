%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    typedef enum{MAIN,INT,CHAR,ID,NUM,SPE,RELOP,ADDLOP,MUL,END} TokenType;
    int row=0,col=0;
    typedef struct t{
        char lexemeName[100];
        TokenType type;
        int row,col;
        struct t *next;
    } Token;
    Token *root=NULL;
    void createToken(char *lexemeName,TokenType type,int row, int col);
    void Program();
    void declarations();
    void dataType();
    void identifierList();
    void statementList();
    void statement();
    void statementList();
    void assignStat();
    void exp();
    void simpleExp();
    void ePrime();
    void relop();
    void term();
    void sePrime();
    void factor();
    void tPrime();
    void mulop();
    void addlop();
%}
%%
"\n" {row++;col=0;}
"main" {createToken("main",MAIN,row,col);col+=4;}
int {createToken("int",INT,row,col);col+=3;}
char {createToken("char",CHAR,row,col);col+=4;}
"=="|"!="|"<="|">="|"<"|">" {createToken(yytext,RELOP,row,col);col+=strlen(yytext);}
"+"|"-" {createToken(yytext,ADDLOP,row,col);col++;}
"*"|"/"|"%" {createToken(yytext,MUL,row,col);col++;}
-?[0-9]+.?[0-9]+ {createToken(yytext,NUM,row,col);col+=strlen(yytext);}
"("|")"|"{"|"}"|";"|","|"="|"["|"]" {createToken(yytext,SPE,row,col);col+=1;}
"\t"|" " {col++;}
[a-zA-Z]+ {createToken(yytext,ID,row,col);col+=strlen(yytext);}
. {createToken(yytext,ID,row,col);col+=strlen(yytext);}
%%
void match(Token *t){
    root=root->next;
}
void invalid(Token *t,char *error_message){
    printf("Error: error in %d line\n%s\n",t->row,error_message);
    exit(0);
}
void Program(){
    if(root->type==MAIN){
        match(root);
        if(strcmp(root->lexemeName,"(")==0){
            match(root);
            if(strcmp(root->lexemeName,")")==0){
                match(root);
                if(strcmp(root->lexemeName,"{")==0){
                    match(root);
                    declarations();
                    statementList();
                    if(strcmp(root->lexemeName,"}")==0)
                        return;
                    else
                        invalid(root,"} is not declared\n");
                }
                else invalid(root,"{ is not declared\n");
            }
            else invalid(root,") is not declared\n");
        }
        else invalid(root,"( is not declared\n");
    }
    else invalid(root,"main is not declared\n");
}
void declarations(){
    if(root->type==CHAR||root->type==INT){
        dataType();
        identifierList();
        if(strcmp(root->lexemeName,";")==0){
            match(root);
            declarations();
        }
        else invalid(root,"; is missing\n");
    }
    return;
}
void dataType(){
    if(root->type==CHAR||root->type==INT)
        match(root);
}
void identifierList(){
    if(root->type==ID){
        match(root);
        if(strcmp(root->lexemeName,",")==0){
            match(root);
            identifierList();
        }
        else if(strcmp(root->lexemeName,"[")==0){
            match(root);
            if(root->type==NUM){
                match(root);
                if(strcmp(root->lexemeName,"]")==0){
                    match(root);
                    if(strcmp(root->lexemeName,",")==0){
                        match(root);
                        identifierList();
                    }
                    else return;
                }
                else invalid(root,"] is missing\n");
            }
            else invalid(root,"invalid array index\n");
        }
        else return;
    }
    else invalid(root,"error while decalring identifer \n");
}
void statementList(){
    if(root->type==ID){
        statement();
        statementList();
    }
    else return;
}
void statement(){
    assignStat();
    if(strcmp(root->lexemeName,";")==0)
        match(root);
    else invalid(root,"misssing ;");
}
void assignStat(){
    if(root->type==ID){
        match(root);
        if(strcmp(root->lexemeName,"=")==0){
            match(root);
            exp();
        }
        else invalid(root,"missing =\n");
    }
    else invalid(root,"wrong identifer\n");
}
void exp(){simpleExp();ePrime();}
void ePrime(){
    if(root->type==RELOP){
        relop();
        simpleExp();
    }
}
void simpleExp(){term();sePrime();}
void sePrime(){
    if(root->type==ADDLOP){
        addlop();
        term();
        sePrime();
    }
}
void term(){factor();tPrime();}
void tPrime(){
    if(root->type==MUL){
        mulop();
        factor();
        tPrime();
    }
}
void factor(){
    if(root->type==ID) match(root);
    else if(root->type==NUM) match(root);
    else invalid(root,"error while identifeer\n");
}
void relop(){
    if(root->type==RELOP) match(root);
    else invalid(root,"invalid in relop\n");
}
void addlop(){
    if(root->type==ADDLOP) match(root);
    else invalid(root,"invalid in addlop\n");
}
void mulop(){
    if(root->type==MUL) match(root);
    else invalid(root,"invalid in mullop\n");
}

int yywrap(){return 1;}

void createToken(char *lexemeName,TokenType type,int row, int col){
    Token *newToken=(Token*)malloc(sizeof(Token));
    strcpy(newToken->lexemeName,lexemeName);
    newToken->type=type;
    newToken->row=row;
    newToken->col=col;
    newToken->next=NULL;
    if(root==NULL)
        root=newToken;
    else{
        Token*temp=root;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=newToken;
    }
}
int main(){
    yyin=fopen("c1.c","r");
    yylex();
    //createToken("main",MAIN,row,col);
    createToken("END",END,row,col);
    Program();
    printf("No error Found\n");
}