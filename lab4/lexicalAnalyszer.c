#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "getNextToken.c"
#define RET_LEN 7
#define TOKEN_BUFFER_SIZE 5
char *return_type[]={"char","int","void","float","double","void","long"};
Token* createNewToken(char *lexemeName, int size, TokenType token_type, Scope scope,OperatorType op_type){
    Token *node=(Token*)malloc(sizeof(Token));
    strcpy(node->lexemeName,lexemeName);
    node->type=token_type;
    node->size=size;
    node->scope=scope;
    node->operator_type=op_type;
    node->next=NULL;
    return node;
}
int parseInt(char *str){
    int k=0;
    for(int i=0;i<strlen(str);i++)
        k=(str[i]-'0')+k*10;
    return k;
}
int findSize(Token t[TOKEN_BUFFER_SIZE]){
    int rep=1;
    if(t[3].type==CONSTANT&&(strcmp(t[2].lexemeName,"[")==0))
        rep=parseInt(t[4].lexemeName);
    if(strcmp(t[0].lexemeName,"char")==0)
        return rep;
    else if((strcmp(t[0].lexemeName,"int")==0)||(strcmp(t[0].lexemeName,"long")==0))
        return rep*4;
    else if((strcmp(t[0].lexemeName,"double")==0)||(strcmp(t[0].lexemeName,"float")==0))
        return rep*8;
    else
        return rep;
}
Token* createNewNode(Token t[5]){
    Token *node=(Token*)malloc(sizeof(Token));
    strcpy(node->lexemeName,t[1].lexemeName);
    node->size=findSize(t);
    node->type=t[1].type;
    node->scope=t[1].scope;
    node->operator_type=t[1].operator_type;
    strcpy(node->identifier_type,t[0].lexemeName);
    node->next=NULL;
    return node;
}
int findLength(Token* root){
    int count=0;
    while(root!=NULL){
        count++;    
        root=root->next;
    }    
    return count;
}
bool findNode(Token* root,Token *t ){
    while(root!=NULL){
        if(strcmp(t->lexemeName,root->lexemeName)==0)
            return false;
        root=root->next;
    }
    return true;
}
bool addNode(Token* root, Token*node){
    if(!findNode(root,node))
        return false;
    node->id=findLength(root);
    printf("ldskfjasd\n");
    Token* temp=root;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=node;
    return true;
}
bool isReturnType(Token t){
    for(int i=0;i<RET_LEN;i++){
        if(strcmp(return_type[i],t.lexemeName)==0){
            
            return true;
        }
            
    }
    if(t.type==IDENTIFIER)
        return true;
    return false;
}
void printBuf(Token buf[TOKEN_BUFFER_SIZE]){
    for(int i=0;i<TOKEN_BUFFER_SIZE;i++){
        printf("%s\t",buf[i].lexemeName);
    }
    printf("\n");
}
bool isFunction(Token buf[TOKEN_BUFFER_SIZE]){
    if(isReturnType(buf[0])&&((buf[1].type==IDENTIFIER)||(strcmp(buf[1].lexemeName,"main")==0))&&(strcmp(buf[2].lexemeName,"(")==0))
        return true;
    return false;
}

void updateBuf(Token *buf,char *buffer,int *start,int *end){
    int i;
    for(i=0;i<TOKEN_BUFFER_SIZE-1;i++)
        buf[i]=buf[i+1];
    buf[i]=getNextToken(buffer,start,end);
}
bool isCallFunction(Token *buf){
    if(strcmp(buf[2].lexemeName,"(")==0)
        return true;
    return false;
}
int main(){
    FILE *fp=fopen("p1.c","r");
    if(fp==NULL){
        printf("Error while opeaning the file\n");
        return 0;
    }
    fseek(fp,0,SEEK_END);
    int size=ftell(fp);
    rewind(fp);
    char buffer[size];
    createBuffer(size,buffer,fp);
    int start=0,end=0;
    Token *tables[5];
    int k=-1;
    Token buf[TOKEN_BUFFER_SIZE];
    for(int i=0;i<TOKEN_BUFFER_SIZE;i++)
        buf[i]=getNextToken(buffer,&start,&end);
    while (buffer[start]!='\0'){
        if(isFunction(buf)){
            k++;
            tables[k]=createNewNode(buf);
        }
        updateBuf(buf,buffer,&start,&end);
        printBuf(buf);
        if(k!=-1){
            if(buf[1].type==IDENTIFIER&&!isCallFunction(buf)){
                addNode(tables[k],createNewNode(buf));
            }
        }
    }
    printf("\nThe global symbol tables are\n");
    for(int i=0;i<k+1;i++){
        Token *temp=tables[i];
        printf("%s \t function \n",temp->lexemeName);
    }
    printf("\nThe local symbol tables are\n");
    for(int i=0;i<k+1;i++){
        Token *temp=tables[i];
        printf("The Symbol table for %s function are: \n",temp->lexemeName);
        while(1){
            temp=temp->next;
            if(temp==NULL)
                break;
            printf("%s  %s  %d\n",temp->lexemeName,temp->identifier_type,temp->size);
        }
    }
}