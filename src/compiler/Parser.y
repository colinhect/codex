%{
    #include <iostream>
    #include <stdexcept>
    #include <sstream>
    
    #include "Syntax.h"

    Node* root;
    int lineNum = 1;

    extern int yylex();
    void yyerror(const char* s) { 
        std::stringstream ss;

        ss << "Error: " << std::string(s) << ": line " << lineNum;
    
        throw std::runtime_error(ss.str()); 
    }
%}

%union {
    Node*           node;
    UpperIdent*     upperIdent;
    LowerIdent*     lowerIdent;
    Type*           type;
    Types*          types;
    Stmt*           stmt;
    Stmts*          stmts;
    Decl*           decl;
    Decls*          decls;
    Expr*           expr;
    Exprs*          exprs;
    Def*            def;
    Defs*           defs;
    Module*         module;
    std::string*    string;
    int             token;
}

%token <string> UIDENT LIDENT INT REAL
%token <token>  LPAREN RPAREN LBRACKET RBRACKET YIELDS
%token <token>  EQ NE PLUS MINUS MUL DIV
%token <token>  NOT AND OR
%token <token>  LT GT LE GE
%token <token>  NL COLON COMMA DOT
%token <token>  MODULE RETURN IF ELSE WHILE END INTERNAL

%type <node>            Node
%type <upperIdent>      UpperIdent
%type <lowerIdent>      LowerIdent
%type <type>            Type VariableType FunctionType
%type <types>           Types
%type <stmt>            Stmt Assignment
%type <stmts>           Stmts
%type <decl>            Decl VariableDecl FunctionDecl
%type <decls>           Decls
%type <expr>            Expr Variable FunctionInvoke ConstructorInvoke InternalInvoke Unary Binary Cast IntLit RealLit
%type <exprs>           Exprs
%type <def>             Def VariableDef FunctionDef ConstructorDef ClassDef 
%type <defs>            Defs
%type <module>          Module

%left PLUS MINUS
%left MUL DIV

%start Node

%%

Node            : Module { root = $1; }
                ;

Module          : MODULE UpperIdent NL NL Defs { $$ = new Module(lineNum, $2, $5); }
                ; 

Defs            : Def { $$ = new Defs(lineNum, $1);  }
                | Def Defs { $$ = new Defs(lineNum, $1, $2); }
                ;

Def             : ClassDef NL { $$ = $1; }
                | ConstructorDef NL { $$ = $1; }
                | FunctionDef NL { $$ = $1; }
                | VariableDef NL { $$ = $1; }
                | Def NL { $$ = $1; }
                ;

ClassDef        : UpperIdent NL NL Defs END { $$ = new ClassDef(lineNum, $1, $4); }
                ;

ConstructorDef  : UpperIdent LPAREN Decls RPAREN NL Stmts END { 
                    $$ = new ConstructorDef(lineNum, $1, $6, $3); 
                }
                | UpperIdent LPAREN RPAREN NL Stmts END { 
                    $$ = new ConstructorDef(lineNum, $1, $5); 
                }
                ;

FunctionDef     : LowerIdent LPAREN Decls RPAREN YIELDS VariableType NL Stmts END { 
                    $$ = new FunctionDef(lineNum, new FunctionDecl(lineNum, new FunctionType(lineNum, (VariableType*)$6, $3->copyTypes()), $1), $8, $3); 
                }
                | LowerIdent LPAREN RPAREN YIELDS VariableType NL Stmts END {
                    $$ = new FunctionDef(lineNum, new FunctionDecl(lineNum, new FunctionType(lineNum, (VariableType*)$5), $1), $7);
                }
                ;

VariableDef     : Decl { $$ = new VariableDef(lineNum, $1); }
                ;

Stmts           : Stmt { $$ = new Stmts(lineNum, $1); }
                | Stmt Stmts { $$ = new Stmts(lineNum, $1, $2); }
                ;

Stmt            : Decl NL { $$ = $1; }
                | Assignment NL { $$ = $1; }
                | Expr NL { $$ = $1; }
                | RETURN Expr NL { $$ = new Return(lineNum, $2); }
                | RETURN NL { $$ = new Return(lineNum); }
                | IF Expr NL Stmts END { $$ = new If(lineNum, $2, $4); }
                | IF Expr NL Stmts ELSE NL Stmts END { $$ = new If(lineNum, $2, $4, $7); }
                | WHILE Expr NL Stmts END  { $$ = new While(lineNum, $2, $4); }
                | Stmt NL { $$ = $1; }
                | NL Stmt { $$ = $2; }
                ;

Assignment      : Variable EQ Expr { $$ = new Assignment(lineNum, (Variable*)$1, $3); }
                ;

Exprs           : Expr { $$ = new Exprs(lineNum, $1); }
                | Expr COMMA Exprs { $$ = new Exprs(lineNum, $1, $3); }
                ;

Expr            : Variable
                | FunctionInvoke
                | ConstructorInvoke
                | InternalInvoke
                | Unary
                | Binary
                | Cast
                | IntLit
                | RealLit
                | LPAREN Expr RPAREN { $$ = $2; }
                ;

Variable        : LowerIdent { $$ = new Variable(lineNum, $1); }
                ;

FunctionInvoke  : LowerIdent LPAREN Exprs RPAREN { $$ = new FunctionInvoke(lineNum, $1, $3); }
                | LowerIdent LPAREN RPAREN { $$ = new FunctionInvoke(lineNum, $1); }
                ;

ConstructorInvoke : UpperIdent LPAREN Exprs RPAREN { $$ = new ConstructorInvoke(lineNum, $1, $3); }
                  | UpperIdent LPAREN RPAREN { $$ = new ConstructorInvoke(lineNum, $1); }
                  ;

InternalInvoke  : INTERNAL LPAREN INT RPAREN { $$ = new InternalInvoke(lineNum, atol($3->c_str())); delete $3; }
                ;

Unary           : NOT Expr { $$ = new Unary(lineNum, OP_NOT, $2); }
                ;

Binary          : Expr AND Expr { $$ = new Binary(lineNum, OP_AND, $1, $3); }
                | Expr OR Expr { $$ = new Binary(lineNum, OP_OR, $1, $3); }
                | Expr PLUS Expr { $$ = new Binary(lineNum, OP_PLUS, $1, $3); }
                | Expr MINUS Expr { $$ = new Binary(lineNum, OP_MINUS, $1, $3); }
                | Expr MUL Expr { $$ = new Binary(lineNum, OP_MUL, $1, $3); }
                | Expr DIV Expr { $$ = new Binary(lineNum, OP_DIV, $1, $3); }
                | Expr EQ Expr { $$ = new Binary(lineNum, OP_EQ, $1, $3); }
                | Expr NE Expr { $$ = new Binary(lineNum, OP_NE, $1, $3); }
                | Expr GT Expr { $$ = new Binary(lineNum, OP_GT, $1, $3); }
                | Expr LT Expr { $$ = new Binary(lineNum, OP_LT, $1, $3); }
                | Expr GE Expr { $$ = new Binary(lineNum, OP_GE, $1, $3); }
                | Expr LE Expr { $$ = new Binary(lineNum, OP_LE, $1, $3); }
                ;

Cast            : LPAREN Expr COLON VariableType RPAREN { $$ = new Cast(lineNum, $2, $4); }
                ;

Type            : VariableType
                | FunctionType
                ;

Types           : Type { $$ = new Types(lineNum, $1); }
                | Type COMMA Types { $$ = new Types(lineNum, $1, $3); }
                ;

VariableType    : UpperIdent { $$ = new VariableType(lineNum, $1); }
                ;

FunctionType    : LPAREN Types RPAREN YIELDS VariableType { $$ = new FunctionType(lineNum, (VariableType*)$5, $2); }
                ;

Decls           : Decl { $$ = new Decls(lineNum, $1);  }
                | Decl COMMA Decls { $$ = new Decls(lineNum, $1, $3); }
                ;

Decl            : VariableDecl
                | FunctionDecl
                ;

VariableDecl    : LowerIdent COLON VariableType { $$ = new VariableDecl(lineNum, (VariableType*)$3, $1); }
                ;

FunctionDecl    : LowerIdent COLON FunctionType { $$ = new FunctionDecl(lineNum, (FunctionType*)$3, $1); }
                ;

LowerIdent      : LIDENT { $$ = new LowerIdent(lineNum, *$1); delete $1; }
                ;

UpperIdent      : UIDENT { $$ = new UpperIdent(lineNum, *$1); delete $1; }
                ;

IntLit          : INT { $$ = new IntLit(lineNum, atol($1->c_str())); delete $1; }
                ;

RealLit         : REAL { $$ = new RealLit(lineNum, atof($1->c_str())); delete $1; }
                ;
%%
