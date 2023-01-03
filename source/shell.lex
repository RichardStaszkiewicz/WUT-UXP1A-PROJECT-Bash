%{
    enum TokenType {
        PIPE=1, FROM, TO, EQUAL, EXPORT, LOCAL, IDENTIFIER, WORD, PATH, VARIABLE, QUOTE, INVQUOTE, UNKNOWN
    };
%}

WS         [ \t]+
DIGIT      [0-9]
LETTER     [a-zA-Z_]
LETTERDOT  [a-zA-Z_.-]
IDENTIFIER {LETTER}({LETTER}|{DIGIT})*
WORD       ({LETTERDOT}|{DIGIT})*
PATH       ("~/"|"/"|"./")?({WORD}"/")*{WORD}
VARIABLE   "$"{LETTER}({LETTER}|{DIGIT})*
QUOTE      "'"[^"'"]*"'"
INVQUOTE   \`[^\`]*\`

%%

{WS}      
"|"          { /*printf("pipe\n");*/ return PIPE; }
"<"          { /*printf("redirect to\n");*/ return TO;  }
">"          { /*printf("redirect from\n");*/ return FROM; }
"="          { /*printf("equal\n");*/ return EQUAL; }
export       { /*printf("export\n");*/ return EXPORT; }
local        { /*printf("local\n");*/ return LOCAL; }
{IDENTIFIER} { /*printf("IDENTIFIER: %s\n", yytext);*/ return IDENTIFIER; }
{WORD}       { /*printf("word: %s\n", yytext);*/ return WORD; }
{PATH}       { /*printf("PATH: %s\n", yytext);*/ return PATH; }
{QUOTE}      { /*printf("quote: %s\n", yytext);*/ return QUOTE; }
{INVQUOTE}   { /*printf("INVQUOTE: %s\n", yytext);*/ return INVQUOTE; }
{VARIABLE}   { /*printf("VARIABLE: %s\n", yytext);*/ return VARIABLE; }
\n           { /*return 0; }
.            { /*printf("UNKNOWN\n");*/ return UNKNOWN; }

%%

int yywrap(){}

/*
int main(){ 
    yy_scan_string("export variable = `exec ./test.sh`");

    int atom;
    while((atom = yylex())>0)
    {
        // if(atom == EXPORT) 
        //    printf("happy");
        //    printf("atom: %d, lexem: %s", atom, yytext);
    }
    return 0;
}
*/