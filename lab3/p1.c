#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    FILE *fp=fopen("p1.c","r");
    if(fp==NULL){
        printf("The file cannot be open\n");
        return 0;
    }