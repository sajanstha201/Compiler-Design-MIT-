#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int k=0;
typedef enum {CONST,OPERATOR,ID,DTYPE,NUN,SPEC} Type;
typedef enum{INT,CHAR,FLOAT,NONE} Dtype;
typedef struct t {
    int id;
    char name[100];
    Type type;
    Dtype dtype;
    int size;
    struct t *nextToken;
} Token;
Token *createToken(int id,char *name,Type type,Dtype dtype,int  size){
    Token *temp=(Token*)malloc(sizeof(Token));
    temp->id=id;
    strcpy(temp->name,name);
    temp->type=type;
    temp->dtype=dtype;
    temp->size=size;
    temp->nextToken=NULL;
    return temp;
}
Token* match(char *buffer,int *i, int *j,Type t,Dtype dt){
    
    char str[*j-*i+1];
    strncpy(str,buffer+(*i),*j-*i+1);
    (*j)++;
    (*i)=(*j);
    int size;
    if(dt==INT)
        size=4;
    else if(dt==CHAR)
        size=1;
    else if(dt==FLOAT)
        size=8;
    else
        size=0;
    return createToken(0,str,t,dt,size);
}
bool checkOperator(char *buffer, int *i,int *j){
    if(buffer[*i]=='='){
        if(buffer[*i+1]=='=')
            (*j)++;
        return true;
    }
    else if(buffer[*i]=='+'){
        return true;
    }
    return false;
}
bool checkSpecialSymbol(char *buffer,int *i,int *j){
    if(buffer[*i]=='{')
        return true;
    else if(buffer[*i]=='}')
        return true;
    else if(buffer[*i]=='(')
        return true;
    else if(buffer[*i]==')')
        return true;
    else if(buffer[*i]==';')
        return true;
    else if(buffer[*i]==',')
        return true;
    else
        return false;
}
bool checkDataType(char *buffer, int *i, int *j){
    char str[100];
    strncpy(str,buffer+*i,*j-*i+1);
    if((strcmp(str,"int")==0)||(strcmp(str,"char")==0)||(strcmp(str,"FLOAT")==0)||(strcmp(str,"FLOAT")==0))
        return true;
    else 
        return false;
}
bool checkIdentifier(char *buffer, int *i, int *j){
    int k=*j+1;
    if(buffer[k]==','||buffer[k]=='='||buffer[k]==';'||buffer[k]==')'||buffer[k]=='('||buffer[k]=='+')
        return true;
    else 
        return false;
}
Token* getNextToken(char *buffer,int *i,int *j){
    Token *t=(Token*)malloc(sizeof(Token));
    t->type=NUN;
    while (*j<strlen(buffer)){
        if(buffer[*i]==' '||buffer[*i]=='\t'||buffer[*i]=='\n'){
            if(*i==*j)
                (*j)++;
            (*i)++;
        }
        if(checkOperator(buffer,i,j)){
            return match(buffer,i,j,OPERATOR,NONE);
        }
        else if(checkSpecialSymbol(buffer,i,j)){
            return match(buffer,i,j,SPEC,NONE);
        }
        else if(checkDataType(buffer,i,j)){
            char str[100];
            strncpy(str,buffer+*i,*j-*i+1);
            Dtype dtype;
            if(strcmp(str,"int")==0) dtype=INT;
            else if(strcmp(str,"char")==0) dtype=CHAR;
            else if(strcmp(str,"FLOAT")==0) dtype=FLOAT;
            return match(buffer,i,j,DTYPE,dtype);
        }
        else if(checkIdentifier(buffer,i,j)){
            return match(buffer,i,j,ID,NONE);
        }
        else{
            (*j)++;
        }
    }
    return t;
}

void addSymbol(Token *root,Token *t,Token *prev){
    Token *temp=root;
    while(temp->nextToken!=NULL){
        if(strcmp(temp->name,t->name)==0)
            return;
        temp=temp->nextToken;
    }
    if(strcmp(prev->name,"int")==0)
        t->dtype=INT;
    else if(strcmp(prev->name,"char")==0)
        t->dtype=CHAR;
    else if(strcmp(prev->name,"float")==0)
        t->dtype=FLOAT;
    temp->nextToken=t;
}
int main(){
    FILE *fp=fopen("input.txt","r");
    fseek(fp,0,SEEK_END);
    int size=ftell(fp);
    rewind(fp);
    char buffer[size];
    char c=fgetc(fp);
    int l=0;
    while(c!=EOF){
        buffer[l++]=c;
        c=fgetc(fp);
    }
    buffer[l]='\0';
    int i=0,j=0;
    Token *t1,*t2,*t3;
    Token *root[5];
    int k=-1;
    int previ,prevj;
    while (j<size){
        previ=i;
        prevj=j;
        t1=getNextToken(buffer,&i,&j);
        if(t1->type==DTYPE){
            t2=getNextToken(buffer,&i,&j);
            t3=getNextToken(buffer,&i,&j);
            if((t2->type==ID) &&t3->name[0]=='('){
                printf("found funciton\n");
                k++;
                root[k]=t2;
                continue;
            }
            else if(t2->type==ID){
                addSymbol(root[k],t2,t1);
            }
        }
        if(t1->type==ID)
            addSymbol(root[k],t1,getNextToken(buffer,&previ,&prevj));
    }
    for(int i=0;i<=k;i++){
        Token *temp=root[i];
        printf("The symbol table for %s function are: \n",temp->name);
        while (temp!=NULL){
            printf("Name: %s   Type: %d   size: %d\n",temp->name,temp->dtype,temp->size);
            temp=temp->nextToken;
        }
    }
    
}