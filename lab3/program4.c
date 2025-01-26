#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#define KEY_LEN 32
#define ID_LEN 5
#define SPE_LEN 19
int *row,*col;
char special_symbol[]={'{','}','(',')',';',',','#','+','-','*','/','%','<','>','&','|','!','=','"'};
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
int checkLiterals(char *str){
    if(str[0]=='"')
        return 1;
    return 0;
}
int checkArithmeticExp(char *str){
    char symbol[5]={'+','-','*','/','%'};
    char c=str[0];
    for(int i=0;i<5;i++)
        if(c==symbol[i])
            return 1;
    return 0;
}
int checkExp(char *str,int len, char *symbol[len]){
    for(int i=0;i<len;i++){
        if(strcmp(str,symbol[i])==0)
            return 1;
    }
    return 0;
}
int checkLogialExp(char *str){
    char *symbol[]={"&&","||","!"};
    return checkExp(str,3,symbol);
    
    
}
int checkBitwise(char *str){
    char *symbol[]={"++","--","+=","*=","/="};
    return checkExp(str,5,symbol);
}
int checkRelational(char *str){
    char *symbol[]={">=","<=","!=","==",">","<"};
    return checkExp(str,6,symbol);
}
int checkPunc(char *str){
    char symbol[]={'{','}','(',')',';',',','#'};
    char c=str[0];
    for(int i=0;i<strlen(symbol);i++)
        if(symbol[i]==c)
            return 1;
    return 0;
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

int findNoWord(char *str){
    int len=1;
    for(int i=0;i<strlen(str);i++)
        for(int j=0;j<SPE_LEN;j++)
            if(str[i]==special_symbol[j])
                len=len+2;
    int st_length=strlen(str);
    if((st_length==0)|| ((st_length==1)&&(str[0]='\n')))
        return 0;
    return len;
}
int checkSpecialSymbol(char c){
    for(int i=0;i<SPE_LEN;i++)
        if(c==special_symbol[i])
            return 1;
    return 0;
}

int checkAndAddLiteral(char *str, int i,int l, char *words[l],int *a,int *b){
    if(str[i]!='"')
        return i;
    else{
        words[*a][*b]='\0';
        *a=*a+1;
        words[*a]=(char *)malloc(sizeof(char)*(strlen(str)+1));
        words[*a][0]=str[i++];
        *b=1;
        while(str[i]!='"'){
            words[*a][*b]=str[i];
            i++;
            (*b)++;
        }
        words[*a][(*b)++]='"';
        words[*a][*b]='\0';
        *a=*a+1;
        *b=0;
        words[*a]=(char *)malloc((strlen(str)+1)*sizeof(char));
        i=i+1;
        return i;
    }
}
int checkAndAddSpecialSymbol(char *str,int index,int l, char *words[l],int *a,int *b){
    int k=0;
    char single_symbol[]={'{','}','(',')',';',',','#','+','-','*','/','%','<','>','&','|','!','='};
    char *double_symbol[]={">=","<=","!=","==","&&","||","++","--","+=","*=","/="};
    for(int j=0;j<sizeof(single_symbol)/sizeof(single_symbol[0]);j++)
        if(single_symbol[j]==str[index])
            k=1;
    if(k==0)
        return index;
    char double_str[3];
    double_str[0]=str[index];
    double_str[1]=str[index+1];
    double_str[2]='\0';
    int i;
    for(i=0;i<sizeof(double_symbol)/sizeof(double_symbol[0]);i++){
        if(strcmp(double_str,double_symbol[i])==0){
            words[*a][*b]='\0';
            *b=0;
            (*a)++;
            words[*a]=(char *)malloc((strlen(str)+1)*sizeof(char));
            words[*a][0]=str[index];
            words[*a][1]=str[index+1];
            words[*a][2]='\0';
            *b=0;
            *a=*a+1;
            words[*a]=(char*)malloc((strlen(str)+1)*sizeof(char));
            return index+2;
        }
    }
    for(i=0;i<sizeof(single_symbol)/sizeof(single_symbol[0]);i++)
        if(str[index]==single_symbol[i]){
            words[*a][*b]='\0';
            *b=0;
            (*a)++;
            words[*a]=(char *)malloc((strlen(str)+1)*sizeof(char));
            words[*a][0]=str[index];
            words[*a][1]='\0';
            *a=*a+1;
            *b=0;
            words[*a]=(char*)malloc((strlen(str)+1)*sizeof(char));
            return index+1;
        } 
}
void splitString(char *str,int *l,char *words[*l]){
    int len=*l;
    int a=0,b=0,i,j;
    words[a]=(char *)malloc(strlen(str));
    for(i=0;i<strlen(str);i++){
        int k=0;
        i=checkAndAddLiteral(str,i,len,words,&a,&b);
        i=checkAndAddSpecialSymbol(str,i,len,words,&a,&b);
        if(i<strlen(str)&&checkSpecialSymbol(str[i])==1){
            i--;
            continue;
        }
        if(i<strlen(str)){
            words[a][b]=str[i];
            b++;
        }

    }
    if(i<strlen(str)){  
        words[a][b]='\0';
    }
    for(j=a+1;j<*l;j++){
        words[j]=(char*)malloc(sizeof(char));
        words[j][0]='\0';
    }
}
void deleteEmptyString(int *len,char *words[*len]){
    int ne=0;
    int i,j;
    for(i=0;i<*len;i++)
        if(strlen(words[i])==0)
            ne++;
    for(i=0;i<*len;i++)
        if(strlen(words[i])==0)
            for(j=i;j<*len-1;j++)
                strcpy(words[j],words[j+1]);
}
int getNextToken(FILE *fp, char c){
    char str[1000];
    int i=0;
    int k=1;
    while(1){
        if(c=='"'){
            k=!k;
            str[i]=c;
            i++;
        }
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
        if(c==' '||c=='\n')
            if(k)
                break;
    }
    str[i]='\0';
    int *len=(int*)malloc(sizeof(int));
    *len=findNoWord(str);
    if(*len==0)
        return 0;           
    char *words[*len];
    splitString(str,len,words);
    deleteEmptyString(len,words);
    printf("WORDS: ");
    for(i=0;i<*len;i++){
        printf("%s  ",words[i]);
    }
    printf("\n");
    for(i=0;i<*len;i++){
        if(checkLiterals(words[i]))
            printf("Literal: %s\n",words[i]);
        else if(checkIdentifers(words[i]))
            printf("Identifers: %s\n",words[i]);
        else if(checkKeywords(words[i]))
            printf("Keywords: %s\n",words[i]);
        else if(checkArithmeticExp(words[i]))
            printf("Arithmetic Expression: %s\n",words[i]);
        else if(checkLogialExp(words[i]))
            printf("Logical Exxpression; %s\n",words[i]);
        else if(checkArithmeticExp(words[i]))
            printf("Arithmetic Expression: %s\n",words[i]);
        else if(checkRelational(words[i]))
            printf("Relational expression: %s\n",words[i]);
        else if(checkPunc(words[i]))
            printf("Puncuation: %s\n",words[i]);
    }
    printf("\n");
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