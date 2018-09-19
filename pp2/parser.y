/* File: parser.y
 * --------------
 * Yacc input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;
    Type *type;
    VarDecl *vardecl;
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Yacc will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class 
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine
%token   T_PostIncr T_PostDecr T_Switch T_Case T_Default

%token   <identifier> T_Identifier
%token   <stringConstant> T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant> T_DoubleConstant
%token   <boolConstant> T_BoolConstant


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <declList>  DeclList 
%type <decl>      Decl
%type <type>      Type
%type <identifier> T_Int
%type <identifier> T_Double
%type <identifier> T_Bool
%type <identifier> T_String
%type <vardecl> Variable

%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program   :    DeclList            { 
                                      Program *program = new Program($1);
                                      if (ReportError::NumErrors() == 0) 
                                          program->Print(0);
                                    }
          ;

DeclList  :    DeclList Decl        { ($$=$1)->Append($2); }
          |    Decl                 { ($$ = new List<Decl*>)->Append($1); }
          ;

Decl : VariableDecl {} 
     | FunctionDecl {}
     | ClassDecl {}
     | InterfaceDecl {}
     ;

VariableDecl : Variable ';' {}
             ;

VariableList : /* empty */ {}
             | VariableList ',' Variable {}
             | Variable {}
             ;

Variable : Type T_Identifier { $$ = new VarDecl(new Identifier(@1, $2), $1); }
         ;

Type : T_Int { $$ = new Type($1); }
     | T_Double { $$ = new Type($1); }
     | T_Bool { $$ = new Type($1); }
     | T_String { $$ = new Type($1); }
     | T_Identifier { $$ = new Type($1); }
     | Type T_Dims {}
     ;
          
FunctionDecl : Type T_Identifier '(' Formals ')' StmtBlock {}
             | T_Void T_Identifier '(' Formals ')' StmtBlock {}
             ;

Formals : VariableList
        ;

ClassDecl : T_Class T_Identifier MaybeExtends ImplementsList '{' FieldList '}' {}
          ;

MaybeExtends : /* empty */ {}
             | T_Extends T_Identifier {}
             ;

ImplementsList : /* empty */ {}
               | T_Implements T_Identifier {}
               ;

FieldList : /* empty */ {}
          | FieldList Field {}
          | Field {}
          ;

Field : VariableDecl {}
      | FunctionDecl {}
      ;

InterfaceDecl : T_Interface T_Identifier '{' PrototypeList '}' {}

PrototypeList : /* empty */ {}
              | PrototypeList Prototype {}
              | Prototype {}
              ;

Prototype : Type T_Identifier '(' Formals ')' ';' {}
          | T_Void T_Identifier '(' Formals ')' ';' {}
          ;

StmtBlock : '{' VariableDeclList StmtList '}' {}
          ;

VariableDeclList : /* empty */ {}
                 | VariableDeclList VariableDecl {}
                 | VariableDecl {}
                 ;

StmtList : /* empty */ {}
         | StmtList Stmt {}
         | Stmt {}
         ;

Stmt : ';' {}
     | Expr ';' {}
     | IfStmt {}
     | WhileStmt {}
     | ForStmt {}
     | BreakStmt {}
     | ReturnStmt {}
     | PrintStmt {}
     | SwitchStmt {}
     | StmtBlock {}
     ;

IfStmt : T_If '(' Expr ')' Stmt MaybeElse {}
       ;

MaybeElse : /* empty */ {}
          | T_Else Stmt {}
          ;

WhileStmt : T_While '(' Expr ')' Stmt {}
          ;

ForStmt : T_For '(' MaybeExpr ';' Expr ';' MaybeExpr ')' {}
        ;

ReturnStmt : T_Return ';' {}
           | T_Return Expr ';' {}
           ;

BreakStmt : T_Break ';' {}
          ;

PrintStmt : T_Print '(' ExprList ')' ';' {}
          ;

ExprList : ExprList ',' Expr {}
         | Expr {}
         ;

SwitchStmt : T_Switch '(' Expr ')' '{' CaseList '}' {}
           ;

CaseList : /* empty */ {}
         | CaseList Case {}
         | Case {}

Case : T_Case T_IntConstant ':' Stmt {}
     | T_Default {}
     ;

Call : T_Identifier '(' Actuals ')' {}
     | Expr '.' T_Identifier '(' Actuals ')' {}
     ;

Actuals : /* empty */ {}
        | ExprList {}
        ; 

Constant : T_IntConstant {}
         | T_DoubleConstant {}
         | T_BoolConstant {}
         | T_StringConstant {}
         | T_Null {}
         ;

MaybeExpr : /* empty */ {}
          | Expr {}
          ;

Expr : LValue '=' Expr {}
     | Constant {}
     | LValue {}
     | T_This {}
     | Call {}
     | '(' Expr ')' {}
     | '!' Expr {}
     | T_ReadInteger '(' ')' {}
     | T_ReadLine '(' ')' {}
     | T_New '(' T_Identifier ')' {}
     | T_NewArray '(' Expr ',' Type ')' {}
     | Expr '+' '+' {}
     | Expr '-' '-' {}
     ;

FunctionDecl : Type T_Identifier '(' Formals ')' StmtBlock {}
             | T_Void T_Identifier '(' Formals ')' StmtBlock {}
             ;

Formals : VariableList
        ;

ClassDecl : T_Class T_Identifier MaybeExtends ImplementsList '{' FieldList '}' {}
          ;

MaybeExtends : /* empty */ {}
             | T_Extends T_Identifier {}
             ;

ImplementsList : /* empty */ {}
               | T_Implements T_Identifier {}
               ;

FieldList : /* empty */ {}
          | FieldList Field {}
          | Field {}
          ;

Field : VariableDecl {}
      | FunctionDecl {}
      ;

InterfaceDecl : T_Interface T_Identifier '{' PrototypeList '}' {}

PrototypeList : /* empty */ {}
              | PrototypeList Prototype {}
              | Prototype {}
              ;

Prototype : Type T_Identifier '(' Formals ')' ';' {}
          | T_Void T_Identifier '(' Formals ')' ';' {}
          ;

StmtBlock : '{' VariableDeclList StmtList '}' {}
          ;

VariableDeclList : /* empty */ {}
                 | VariableDeclList VariableDecl {}
                 | VariableDecl {}
                 ;

StmtList : /* empty */ {}
         | StmtList Stmt {}
         | Stmt {}
         ;

Stmt : ';' {}
     | Expr ';' {}
     | IfStmt {}
     | WhileStmt {}
     | ForStmt {}
     | BreakStmt {}
     | ReturnStmt {}
     | PrintStmt {}
     | SwitchStmt {}
     | StmtBlock {}
     ;

IfStmt : T_If '(' Expr ')' Stmt MaybeElse {}
       ;

MaybeElse : /* empty */ {}
          | T_Else Stmt {}
          ;

WhileStmt : T_While '(' Expr ')' Stmt {}
          ;

ForStmt : T_For '(' MaybeExpr ';' Expr ';' MaybeExpr ')' {}
        ;

ReturnStmt : T_Return ';' {}
           | T_Return Expr ';' {}
           ;

BreakStmt : T_Break ';' {}
          ;

PrintStmt : T_Print '(' ExprList ')' ';' {}
          ;

ExprList : ExprList ',' Expr {}
         | Expr {}
         ;

SwitchStmt : T_Switch '(' Expr ')' '{' CaseList '}' {}
           ;

CaseList : /* empty */ {}
         | CaseList Case {}
         | Case {}

Case : T_Case T_IntConstant ':' Stmt {}
     | T_Default {}
     ;

Call : T_Identifier '(' Actuals ')' {}
     | Expr '.' T_Identifier '(' Actuals ')' {}
     ;

Actuals : /* empty */ {}
        | ExprList {}
        ; 

Constant : T_IntConstant {}
         | T_DoubleConstant {}
         | T_BoolConstant {}
         | T_StringConstant {}
         | T_Null {}
         ;

MaybeExpr : /* empty */ {}
          | Expr {}
          ;

Expr : Constant {}
     | LValue {}
     | T_This {}
     | Call {}
     | '(' Expr ')' {}
     | T_ReadInteger '(' ')' {}
     | T_ReadLine '(' ')' {}
     | T_New '(' T_Identifier ')' {}
     | T_NewArray '(' Expr ',' Type ')' {}
     | Prec1 {}
     ;

Prec1 : Prec1 '.' T_Identifier {}
      | Prec1 '[' Expr ']' {}
      | Prec2 {}
      ;

Prec2 : '!' Prec2 {}
      | '-' Prec2 {}
      | Prec3 {}
      ;

Prec3 : Prec3 '*' Prec4 {}
      | Prec3 '/' Prec4 {}
      | Prec3 '%' Prec4 {}
      | Prec4 {}
      ;

Prec4 : Prec4 '+' Prec5 {}
      | Prec4 '-' Prec5 {}
      | Prec5 {}
      ;

Prec5 : Prec5 '<' Prec6 {}
      | Prec5 T_LessEqual Prec6 {}
      | Prec5 '>' Prec6 {}
      | Prec5 T_GreaterEqual Prec6 {}
      | Prec6 {}
      ;

Prec6 : Prec6 T_Equal Prec7 {}
      | Prec6 T_NotEqual Prec7 {}
      | Prec7 {}
      ;

Prec7 : Prec7 T_And Prec8 {}
      | Prec8 {}
      ;

Prec8 : Prec8 T_Or Prec9 {}
      | Prec9 {}

Prec9 : Prec9 '=' Expr {}
      | LValue {}

>>>>>>> Stashed changes
LValue : T_Identifier {}
       | Expr '.' T_Identifier {}
       | Expr '[' Expr ']' {}
       ;

%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
