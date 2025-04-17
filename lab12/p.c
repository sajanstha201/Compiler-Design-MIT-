#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
char* stack[100];
int top=-1;
int tempCount=0;
void push(char*c){
    strcpy(stack+(++top),c);
}
char* pop(){
    return stack+(top--);
}
bool isArithmetic(char *str){
    char c=str[0];
    if(c=='+' || c=='-' || c=='*' || c=='/')
        return true;
    return false;
}
void printA(char *result,char *p1,char *operator,char *p2){
    char c=operator[0];
    if(c=='+')
        printf("ADD ");
    else if(c=='-')
        printf("SUB ");
    else if(c=='/')
        printf("MUL ");
    else if(c=='*')
        printf("DIV ");
    printf("%s %s %s\n",result,p1,p2);
}
int main(){
    char *str="abc+*";
    for(int i=0;i<strlen(str);i++){
        char c[100];
        strncpy(c,str+i,1);
        if(!isArithmetic(c))
            push(c);
        else{
            char *temp;
            sprintf(temp,"r%d",tempCount++);
            char *p1=pop();
            char *p2=pop();
            printA(temp,p1,c,p2);
            push(temp);
        }
    }
}