#include<stdio.h>
#include<stdlib.h>
char *buffer;
int curr=0;
void S();
void U();
void W();
void V();
void invalid(){
    printf("Not Matched\n");
    exit(0);
}
void S(){
    U();
    V();
    W();
}
void U(){
    if(buffer[curr]=='('){
        curr++;
        S();
        if(buffer[curr]==')')
            curr++;
        else
            invalid();
    }
    else if(buffer[curr]=='a'){
        curr++;
        S();
        if(buffer[curr]=='b')
            curr++;
        else
        invalid();
    }
    else if(buffer[curr]=='d')
        curr++;
    else
        invalid();
}
void V(){
    if(buffer[curr]=='a'){
        curr++;
        V();
    }
    else
        return;
}
void W(){
    if(buffer[curr]=='c'){
        curr++;
        W();
    }
    else
        return;
}
int main(){
    printf("Enter a string with $ end\n");
    buffer=(char*)malloc(sizeof(char)*100);
    fgets(buffer,100,stdin);
    S();
    if(buffer[curr]=='$')
        printf("Valid String\n");
    else
        invalid();
}