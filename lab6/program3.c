#include<stdio.h>
#include<stdlib.h>
char *buffer;
int curr;
void S();
void A();
void B();
void invalid(){
    printf("not Matvhed\n");
    exit(0);
}
void S(){
    if(buffer[curr]=='a'){
        curr++;
        A();
        if(buffer[curr]=='c'){
            curr++;
            B();
            if(buffer[curr]=='e'){
                curr++;
            }
            else
                invalid();
        }
        else
            invalid();

    }
}
void A(){
    if(buffer[curr]=='b')
        curr++;
    else{
        A();
        if(buffer[curr]=='a')
            curr++;
        else
            invalid();
    }
}
void B(){
    if(buffer[curr]=='d')
        curr++;
    else
        invalid();
}
int main(){
    buffer=(char*)malloc(sizeof(char)*100);
    printf("Enter a sring with $ end\n");
    fgets(buffer,100,stdin);
    S();
    if(buffer[curr]=='$')
        printf("Valid String\n");
    else
        invalid();
}