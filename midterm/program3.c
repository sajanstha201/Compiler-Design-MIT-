#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int p=0;
char buffer[100];
void U();
void V();
void W();
void match(){
    p++;
    return;
}
void invalid(){
    printf("Invalid Expression\n");
    exit(0);
}
void S(){
    U();
    V();
    W();
}
void U(){
    if(buffer[p]=='('){
        match();
        S();
        if(buffer[p]==')'){
            match();
            return;
        }
        else invalid();
    }
    else if(buffer[p]=='a'){
        match();
        S();
        if(buffer[p]=='b'){
            match();
            return;
        }
        else invalid();
    }
    else if(buffer[p]=='d'){
        match();
    }
    else invalid();
}
void V(){
    if(buffer[p]=='a'){
        match();
        V();
    }
    else return;
}
void W(){
    if(buffer[p]=='c'){
        match();
        W();
    }
    else return;
}
int main(){
    printf("Enter a string end with $: \n");
    fgets(buffer,100,stdin);
    S();
    if(buffer[p]=='$'){
        printf("Valid expression\n");
    }
    else 
        printf("Invalid Expressoin\n");
}