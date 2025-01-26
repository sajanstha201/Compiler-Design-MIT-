#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fp=fopen("p2.c","r");
    FILE *rp=fopen("p2_result.c","w");
    if(fp==NULL || rp==NULL){
        printf("The file cannot open\n");
        return 0;
    }
    char c=fgetc(fp);
    while(c!=EOF){
        if(c=='#'){
            while(c!='\n'){
                c=fgetc(fp);
            }
            c=fgetc(fp);
        }
        else{
            fputc(c,rp);
            c=fgetc(fp);
        }
    }
}