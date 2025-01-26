#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    FILE *fp=fopen("p1.c","r");
    if(fp==NULL){
        printf("The file cannot be open\n");
        return 0;
    }
    char c=fgetc(fp);
    while(c!=EOF){
        char k='0';
        if(c=='"')
            while(fgetc(fp)!='"');
        if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%')
            printf("Arithmetic Operator: %c\n",c);
        if(c=='>'||c=='<'||c=='!'||c=='='){
            k=c;
            c=fgetc(fp);
            if(c=='='){
                if(k=='='){
                    printf("Relational Operator: ==\n");
                    k='0';
                }
                else{
                    printf("Relational Operator: %c%c\n",k,c);
                    k='0';
                }
            }
            else if(k=='='){
                printf("Assignment Operator: %c\n",k);
            }
            else if(k=='!'){
                printf("Logical Operator: %c\n",k);
            }
        }
        if(c=='&'||c=='|'){
            k=c;
            c=fgetc(fp);
            if(c==k)
                printf("Logical Operator: %c%c\n",c,c);
        }
        c=fgetc(fp);
    }
}