#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *fp=fopen("p1.txt","r");
    FILE *gp=fopen("p1.txt","r");
    FILE *rp=fopen("p2.txt","w");
    if(fp==NULL || gp==NULL || rp==NULL){
        printf("The file cannot open\n");
        return 0;
    }
    char fc=fgetc(fp);
    fseek(gp,1,SEEK_SET);
    char gc=fgetc(gp);
    while(gc!=EOF){
        printf("%c",gc);
        if(gc!=' '||fc!=' ')
            fputc(gc,rp);
        fc=fgetc(fp);
        gc=fgetc(gp);
    }
    printf("Completed\n");
    fclose(fp);
    fclose(gp);
    fclose(rp);
}