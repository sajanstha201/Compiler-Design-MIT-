#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_KEYWORDS 32
const char *keywords[MAX_KEYWORDS] = {
"auto", "break", "case", "char", "const", "continue", "default", "do",
"double", "else", "enum", "extern", "float", "for", "goto", "if",
"int", "long", "register", "return", "short", "signed", "sizeof", "static",
"struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};
void checkKeyword(char *str,int *arr){
    int i;
    int len=1;
    for(i=0;i<strlen(str);i++)
        if(str[i]=='('||str[i]==')'||str[i]==';'||str[i]==':')
            len++;
    char words[len][100];
    int k=0,l=0;
    i=0;
    while(str[k]!='\0'){
        words[l][i]=str[k];
        i++;
        k++;
        if(str[k]=='('||str[k]==')'||str[k]==';'||str[k]==':'){
            words[l][i]='\0';
            l++;
            i=0;
        }
    }
    words[l][i]='\0';
    int j;
    for(i=0;i<len;i++)
        for(j=0;j<MAX_KEYWORDS;j++)
            if(strcmp(words[i],keywords[j])==0){
                    arr[j]=1;
                    break;
            }
}
int main(){

    FILE *fp=fopen("p3.c","r");
    if(fp==NULL){
        printf("The file cannot be open");
        return 0;
    }
    char str[100];
    int arr[MAX_KEYWORDS];
    int i;
    for(i=0;i<MAX_KEYWORDS;i++)
        arr[i]=0;
    while(fscanf(fp,"%s",str)!=EOF)
        checkKeyword(str,arr);
    printf("The keywords are:\n");
    for(i=0;i<MAX_KEYWORDS;i++)
        if(arr[i]==1)
            printf("%s\n",keywords[i]);
}