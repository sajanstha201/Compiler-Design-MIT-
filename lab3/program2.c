#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#define KEY_LEN 32
#define ID_LEN 5
#define SPE_LEN 16
int *row,*col;
char special_symbol[]={'{','}','(',')',';',',','#','*','&','=','!','|','+','>','<'};
char *keywords[] = {
"auto", "break", "case", "char", "const", "continue", "default", "do",
"double", "else", "enum", "extern", "float", "for", "goto", "if",
"int", "long", "register", "return", "short", "signed", "sizeof", "static",
"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
char *p_identifiers[]={"int","char","float","long","struct"};
int checkKeywords(char *str){
    for(int i=0;i<KEY_LEN;i++)
        if(strcmp(str,keywords[i])==0)
            return 1;
    return 0;
}
int  checkIdentifers(char *str){
    for(int i=0;i<ID_LEN;i++)
        if(strcmp(str,p_identifiers[i])==0)
            return 1;
    return 0;
}
void escapeLiterals(FILE *fp, char c){
    if(c=='"')
        while(fgetc(fp)!='"');
}
void escapeComment(FILE *fp, char c){
    if(c=='/'&&fgetc(fp)=='/'){
        while(c!='\n'){
            c=fgetc(fp);
        }
    }
    (*row)++;
    *col=0;
}
void escapeDirectives(FILE* fp, char c){
    if(c=='#')
        while(fgetc(fp)!='\n');
    *row++;
    *col=0;
}
void splitString(char *str,int *l,char *words[*l]){
    int len=*l;
    int a=0,b=0;
    words[a]=(char *)malloc(100);
    for(int i=0;i<strlen(str);i++){
        int k=0;
        for(int j=0;j<SPE_LEN;j++){
            if(str[i]==special_symbol[j]){
                words[a][b]='\0';
                a++;
                b=0;
                k=1;
                words[a]=(char *)malloc(100);
                break;
            }
        }
        if(k==0){
            words[a][b]=str[i];
            b++;
        }
    }
    words[a][b]='\0';
    for(int i=0;i<len;i++){
        if(strlen(words[i])==0){
            int j;
            for(j=i;j<len-1;j++){
                strcpy(words[j],words[j+1]);
            }
            len--;
            i--;
        }
    }
    *l=len;
}
int getNextToken(FILE *fp, char c){
    char str[100];
    int i=0;;
    while(c!=' '&&c!='\n'){
        if(c=='"')
            escapeLiterals(fp,c);
        else if(c=='/')
            escapeComment(fp,c);
        else if(c=='#')
            escapeDirectives(fp,c);
        else if(c=='\n'){
            (*row)++;
            *col=0;
        }
        else if(c==EOF){
            return -1;
        }
        else{
            str[i]=c;
            i++;
        }
        c=fgetc(fp);
    }
    str[i]='\0';
    int *len=(int *)malloc(sizeof(int));
    *len=1;
    for(int i=0;i<strlen(str);i++)
        for(int j=0;j<SPE_LEN;j++)
            if(str[i]==special_symbol[j])
                (*len)++;
                
    char *words[*len];
    splitString(str,len,words);
    if(*len==0){
        return 0;
    }
    for(i=0;i<*len;i++){
        if(checkIdentifers(words[i]))
            printf("Identifers; %s\n",words[i]);
        else if(checkKeywords(words[i]))
            printf("Keywords: %s\n",words[i]);

    }
}
int main(){
    row=(int *)malloc(sizeof(int));
    col=(int *)malloc(sizeof(int));
    FILE *fp=fopen("p1.c","r");
    if(fp==NULL){
        printf("Error while opeaning file\n");
        return 0;
    }
    *row=0;
    *col=0;
    char c=fgetc(fp);
    while(c!=EOF){
        if(getNextToken(fp,c)==-1)
            break;
        c=fgetc(fp);
    }
}