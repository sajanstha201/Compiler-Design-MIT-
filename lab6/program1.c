#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int curr=0;
char *buffer;
void invalid(){
    printf("ERROR\n");
    exit(0);
}
void S();
void T();
void S(){
    if(buffer[curr]=='a'){
        curr++;
        return;
    }
    else if(buffer[curr]=='>'){
        curr++;
        return;
    }
    else if(buffer[curr]=='('){
        curr++;
        T();
        if(buffer[curr]==')'){
            curr++;
            return;
        }
        else
            invalid();
    }
    else
        invalid();
}
void T(){
    if(buffer[curr]=='a'||buffer[curr]=='>'||buffer[curr]=='(')
        S();
    else{
        T();
        if(buffer[curr]==','){
            curr++;
            S();
        }
    }
}
int main(){
    printf("Enter a string with $ end character:\n");
    buffer=(char*)malloc(sizeof(char)*100);
    fgets(buffer,100,stdin);
    printf("The strng is %s\n",buffer);
    S();
    if(buffer[curr]=='$')
        printf("valid string");
    else
        invalid();
}