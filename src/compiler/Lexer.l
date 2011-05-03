%{
    #include <iostream>
    #include <string>

    #include "Syntax.h"
    #include "Parser.hpp"

    #define NEW_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)

    extern int lineNum;
    extern "C" int yywrap() {}
%}

%%
[ \t]                   ;
"--".*\n                ++lineNum;
module                  return TOKEN(MODULE);
if                      return TOKEN(IF);
else                    return TOKEN(ELSE);
while                   return TOKEN(WHILE);
return                  return TOKEN(RETURN);
end                     return TOKEN(END);
_internal               return TOKEN(INTERNAL);
[_]*[a-z][a-zA-Z]*      NEW_TOKEN; return LIDENT;
[A-Z][a-zA-Z]*          NEW_TOKEN; return UIDENT;
[0-9]+                  NEW_TOKEN; return INT;
[0-9]+"."[0-9]+         NEW_TOKEN; return REAL;
"\n"                    { ++lineNum; return TOKEN(NL); }
"<"                     return TOKEN(LT);
">"                     return TOKEN(GT);
"="                     return TOKEN(EQ);
"≠"                     return TOKEN(NE);
"≤"                     return TOKEN(LE);
"≥"                     return TOKEN(GE);
"¬"                     return TOKEN(NOT);
"∧"                     return TOKEN(AND);
"∨"                     return TOKEN(OR);
":"                     return TOKEN(COLON);
"."                     return TOKEN(DOT);
","                     return TOKEN(COMMA);
"+"                     return TOKEN(PLUS);
"-"                     return TOKEN(MINUS);
"∙"                     return TOKEN(MUL);
"/"                     return TOKEN(DIV);
"("                     return TOKEN(LPAREN);
")"                     return TOKEN(RPAREN);
"{"                     return TOKEN(LBRACKET);
"}"                     return TOKEN(RBRACKET);
"➔"                     return TOKEN(YIELDS);
.                       std::cout << "Error: Unknown token: " << yytext << std::endl;

