#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define KEY_LEN 34
#define SPE_LEN 8
#define PRE_IDEN_LEN 18
#define CONST_LEN 11
typedef enum {IDENTIFIER,STRING,OPERATOR,SPECIAL_SYMBOL,KEYWORDS,END,CONSTANT} TokenType;
char *token_name[]={"identifier","string","Operator","special symbol","keywords","end","constant"};
typedef enum{ARITH,REL,LOG,ASI,BIT,NONE} OperatorType;
typedef enum {GLOBAL,LOCAL} Scope;
typedef enum {INT,CHAR,FLOAT,DOUBLE,BOOL,LONG} IdentifierType;
typedef struct t{
    int size,id;
    char lexemeName[100];
    TokenType type;
    char identifier_type[100];
    Scope scope;
    OperatorType operator_type;
    struct t *next;
} Token;
char *keywords[] = {
"auto", "break", "case", "char", "const", "continue", "default", "do",
"double", "else", "enum", "extern", "float", "for", "goto", "if",
"int", "long", "register", "return", "short", "signed", "sizeof", "static",
"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while","FILE","NULL"
};
Token createToken(char *name,int size,TokenType type,OperatorType op_type){
    Token t;
    t.size=size;
    strcpy(t.lexemeName,name);
    t.type=type;
    t.operator_type=op_type;
    return t;
}
char special_symbol[]={'{','}','(',')',';',',','#','"'};
char pre_ident_symbol[]={'{','}','(',')',';',',','#','"','=','+','-','/','*','&','|','!','>','<'};
char constant_arr[]={'0','1','2','3','4','5','6','7','8','9','.'};
void createBuffer(int size,char buffer[size],FILE* fp){
    char c=fgetc(fp);
    int k=0;
    while(c!=EOF){
        buffer[k]=c;
        c=fgetc(fp);
        k++;
    }
}

bool isKeyword(char *str){
    for(int i=0;i<KEY_LEN;i++)
        if(strcmp(str,keywords[i])==0)
            return true;
    return false;
}
bool isSpecialSymbol(char *str){
    char c=str[0];
    for(int i=0;i<SPE_LEN;i++)
        if(c==special_symbol[i])
            return true;
    return false;
}
bool isString(char *buffer,int *start,int *end){
    if(buffer[*start]=='"'){
        (*end)++;
        while(buffer[*end]!='"'){
            (*end)++;
            continue;
        }
        return true;
    }
    if(buffer[*start]=='\''){
        (*end)++;
        while(buffer[*end]!='\''){
            (*end)++;
            continue;
        }
        return true;
    }
    return false;
}
Token isOperator(char *str,int *start,int *end){
    int k=0;
    if(*start==*end){
        (*end)++;
        k=1;
    } 
    else if(*start+1!=*end)
        return createToken("",0,OPERATOR,NONE);
        
    if(str[*start]=='='){
        if(str[*end]=='=')
            return createToken("==",0,OPERATOR,REL);
        else{
            (*end)--;
            return createToken("=",0,OPERATOR,ASI);
        }
    }
    else if(str[*start]=='<')
        if(str[*end]=='=')
            return createToken("<=",0,OPERATOR,REL);
        else{
            (*end)--;
            return createToken("<",0,OPERATOR,REL);
        }
    else if(str[*start]=='>')
        if(str[*end]=='=')
            return createToken(">=",0,OPERATOR,REL);
        else{
            (*end)--;
            return createToken(">",0,OPERATOR,REL);
        }
    else if(str[*start]=='&')
        if(str[*end]=='&')
            return createToken("&&",0,OPERATOR,LOG);
        else{
            (*end)--;
            return createToken("&",0,OPERATOR,BIT);
        }
    else if(str[*start]=='|')
        if(str[*end]=='|')
            return createToken("||",0,OPERATOR,LOG);
        else{
            (*end)--;
            return createToken("|",0,OPERATOR,BIT);
        }
    else if(str[*start]=='!')
        if(str[*end]=='=')
            return  createToken("!=",0,OPERATOR,LOG);
        else{
            (*end)--;
            return createToken("!",0,OPERATOR,BIT);
        }
    else if(str[*start]=='+')
        if(str[*end]=='=')
            return createToken("+=",0,OPERATOR,ASI);
        else if(str[*end]=='+')
            return createToken("++",0,OPERATOR,ARITH);
        else{
            (*end)--;
            return createToken("+",0,OPERATOR,ARITH);
        }
    else if(str[*start]=='-')
        if(str[*end]=='=')
            return createToken("-=",0,OPERATOR,ASI);
        else if(str[*end]=='-')
            return createToken("--",0,OPERATOR,ARITH);
        else{
            (*end)--;
            return createToken("-",0,OPERATOR,ARITH);
        }
    else if(str[*start]=='/')
        if(str[*end]=='=')
            return createToken("/=",0,OPERATOR,ASI);
        else{
            (*end)--;
            return createToken("/",0,OPERATOR,ARITH);
        }
    else if(str[*start]=='*')
        if(str[*end]=='=')
            return createToken("*=",0,OPERATOR,ASI);
        else{
            (*end)--;
            return createToken("*",0,OPERATOR,ARITH);
        }
    else{
        if(k==1){
            (*end)--;
        }
        return createToken("",0,OPERATOR,NONE);
    }
        
}
bool isPreIdentiferSymbol(char *str){
    for(int i=0;i<PRE_IDEN_LEN;i++)
        if(str[0]==pre_ident_symbol[i])
            return true;
    return false;
}

bool isIdentifier(char *str,int *start,int *end){
    if(*start==*end)
        return false;
    char *k=(char*)malloc(sizeof(char));
    strncpy(k,str+(*end),1);
    if(isPreIdentiferSymbol(k)){
        (*end)--;
        return true;
    }
        
    return false;
}
bool isConstant(char *str,int *start,int *end){
    int c=0;
    while(1){
        int k=0;
        for(int i=0;i<CONST_LEN;i++)
            if(str[*end]==constant_arr[i])
                c=k=1;
        if(k==1){
            (*end)++;
            continue;
        }
        else
            break;
    }
    if(c==1){
        (*end)--;
        return true;
    }
    return false;
}
Token getNextToken(char *buffer, int* start, int* end){
    Token t;
    t.operator_type=NONE;
    while(1){
        if(buffer[*end]==' '||buffer[*end]=='\n'){
            if(*start==*end){
                (*end)++;
                *start=*end;
                continue;
            }
            char *name=(char*)malloc(sizeof(char)*(*end-*start));
            strncpy(name,buffer+(*start),(*end-*start));
            (*end)++;
            *start=*end;
            return createToken(name,strlen(name),IDENTIFIER,NONE);
        }
        char *str=(char*)malloc(sizeof(char)*(*end-*start+1));
        strncpy(str,buffer+(*start)*sizeof(char),(*end-*start+1));
        if(isString(buffer,start,end)){
            char *string=(char*)malloc(sizeof(char)*(*end-*start+1));
            strncpy(string,buffer+(*start)*sizeof(char),(*end-*start+1));
            (*end)++;
            *start=*end;
            t=createToken(string,strlen(string),STRING,NONE);
            return t;
        }
        else if(isKeyword(str)){
            (*end)++;
            *start=*end;
            return createToken(str,0,KEYWORDS,NONE);
        }
        else if(isSpecialSymbol(str)){
            (*end)++;
            *start=*end;
            return createToken(str,0,SPECIAL_SYMBOL,NONE);
        }
        else if(isConstant(buffer,start,end)){
            char var[*end-*start+1];
            strncpy(var,buffer+(*start),(*end-*start+1));
            (*end)++;
            *start=*end;
            return createToken(var,0,CONSTANT,NONE);
        }
        else if(isIdentifier(buffer,start,end)){
            char ident[(*end-*start+1)];
            strncpy(ident,buffer+(*start),(*end-*start+1));
            (*end)++;
            *start=*end;
            return createToken(ident,0,IDENTIFIER,NONE);
        }
        else{
            t=isOperator(buffer,start,end);
            if(t.operator_type!=NONE){
                (*end)++;
                *start=*end;
                return t;
            }
        }
        (*end)++;
    }
}
// int main(){
//     FILE *fp=fopen("p1.c","r");
//     if(fp==NULL){
//         printf("Error\n");
//         return 0;
//     }
//     fseek(fp,0,SEEK_END);
//     int size=ftell(fp)*sizeof(char);
//     rewind(fp);
//     char buffer[size];
//     createBuffer(size,buffer,fp);
//     int start=0,end=0;
//     while(buffer[start]!='\0'){
//         Token t=getNextToken(buffer,&start,&end);
//             printf("%s : %s\n",token_name[t.type],t.lexemeName);
//         if(t.type==END)
//             break;
//     }
// }