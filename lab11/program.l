%{
#include <stdio.h>
#include "program.tab.h"
%}

%%
"if"        { yylval.str=strdup(yytext); return IF; }
"else"      { yylval.str=strdup(yytext); return ELSE; }
"{"         {yylval.str=strdup(yytext);  return '{'; }
"}"         {yylval.str=strdup(yytext);  return '}'; }
"("         {yylval.str=strdup(yytext); return '(';}
")"         {yylval.str=strdup(yytext); return ')';}
"+"         {yylval.str=strdup(yytext);  return '+'; }
"-"         {yylval.str=strdup(yytext);  return '-'; }
"*"         {yylval.str=strdup(yytext);  return '*'; }
"/"         {yylval.str=strdup(yytext);  return '/'; }
"<"         {yylval.str=strdup(yytext);  return '<'; }
">"         {yylval.str=strdup(yytext);  return '>'; }
[a-zA-Z][a-zA-Z0-9]* {yylval.str=strdup(yytext);  return ID; }
[0-9]+      {yylval.str=strdup(yytext);  return NUM; }
\n          { return NL; }
[ ;\t]+      { /* skip whitespace */ }
.           { /* ignore unrecognized characters */ }

%%
int yywrap() {
    return 1;
}
