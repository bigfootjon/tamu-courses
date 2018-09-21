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
    List<VarDecl*> *varlist;
    Identifier *ident;
    NamedType *namedtype;
    List<NamedType*> *implements;
    Stmt *stmt;
    List<Stmt*> *stmtlist;
    Expr *expr;
    List<Expr*> *exprlist;
    CaseStmt *kase;
    List<CaseStmt*> *caselist;
    DefaultStmt *defaultstmt;
    BreakStmt *breakstmt;
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
%type <declList> DeclList FieldList PrototypeList
%type <decl> Decl FunctionDecl ClassDecl InterfaceDecl Field Prototype
%type <type> Type 
%type <vardecl> Variable VariableDecl
%type <varlist> VariableList VariableDeclList
%type <ident> Ident
%type <namedtype> MaybeExtends
%type <implements> ImplementsList ImplementsListActual
%type <stmt> StmtBlock Stmt MaybeElse
%type <stmtlist> StmtList MaybeStmtList
%type <expr> Expr MaybeExpr Call Constant LValue
%type <exprlist> ExprList Actuals
%type <kase> Case
%type <caselist> CaseList
%type <defaultstmt> MaybeDefault
%type <breakstmt> MaybeBreak

%nonassoc '='
%left T_Or
%left T_And
%left T_Equal T_NotEqual
%nonassoc '<'
%nonassoc '>'
%nonassoc T_LessEqual
%nonassoc T_GreaterEqual
%left '+' '-'
%left '*' '/' '%'

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

Decl : Field { $$ = $1; }
     | ClassDecl
     | InterfaceDecl
     ;

VariableDecl : Variable ';'
             ;

VariableList : /* empty */ { $$ = new List<VarDecl*>; }
             | VariableList ',' Variable { ($$=$1)->Append($3); }
             | Variable { ($$=new List<VarDecl*>)->Append($1); }
             ;

Ident : T_Identifier { $$ = new Identifier(@1, $1); }
      ;

Variable : Type Ident { $$ = new VarDecl($2, $1); }
         ;

Type : T_Int { $$ = Type::intType; }
     | T_Double { $$ = Type::doubleType; }
     | T_Bool { $$ = Type::boolType; }
     | T_String { $$ = Type::stringType; }
     | Ident { $$ = new NamedType($1); }
     | Type T_Dims { $$ = new ArrayType(@1, $1); }
     ;
          
FunctionDecl : Type Ident '(' VariableList ')' StmtBlock { FnDecl *fn = new FnDecl($2, $1, $4); fn->SetFunctionBody($6); $$ = fn; }
             | T_Void Ident '(' VariableList ')' StmtBlock { FnDecl *fn = new FnDecl($2, Type::voidType, $4); fn->SetFunctionBody($6); $$ = fn; }
             ;

ClassDecl : T_Class Ident MaybeExtends ImplementsList '{' FieldList '}' { $$ = new ClassDecl($2, $3, $4, $6); }
          ;

MaybeExtends : /* empty */ { $$ = 0; }
             | T_Extends Ident { $$ = new NamedType($2); }
             ;

ImplementsList : /* empty */ { $$ = new List<NamedType*>; }
               | T_Implements ImplementsListActual { $$ = $2; }
               ;

ImplementsListActual : ImplementsListActual ',' Ident { ($$=$1)->Append(new NamedType($3)); }
                     | Ident { ($$=new List<NamedType*>)->Append(new NamedType($1)); }
		     ;

FieldList : /* empty */ { $$ = new List<Decl*>; }
          | FieldList Field { ($$=$1)->Append($2); }
          | Field { ($$=new List<Decl*>)->Append($1); }
          ;

Field : VariableDecl { $$ = $1; }
      | FunctionDecl
      ;

InterfaceDecl : T_Interface Ident '{' PrototypeList '}' { $$ = new InterfaceDecl($2, $4); }

PrototypeList : /* empty */ { $$ = new List<Decl*>; }
              | PrototypeList Prototype { ($$=$1)->Append($2); }
              | Prototype { ($$=new List<Decl*>)->Append($1); }
              ;

Prototype : Type Ident '(' VariableList ')' ';' { $$ = new FnDecl($2, $1, $4); }
          | T_Void Ident '(' VariableList ')' ';' { $$ = new FnDecl($2, Type::voidType, $4); }
          ;

StmtBlock : '{' VariableDeclList StmtList '}' { $$ = new StmtBlock($2, $3); }
          | '{' StmtList '}' { $$ = new StmtBlock(new List<VarDecl*>, $2); }
          | '{' VariableDeclList '}' { $$ = new StmtBlock($2, new List<Stmt*>); }
          | '{' '}' { $$ = new StmtBlock(new List<VarDecl*>, new List<Stmt*>); }
          ;

VariableDeclList : VariableDeclList VariableDecl { ($$=$1)->Append($2); }
                 | VariableDecl { ($$=new List<VarDecl*>)->Append($1); }
                 ;

StmtList : StmtList Stmt { ($$=$1)->Append($2); }
         | Stmt { ($$=new List<Stmt*>)->Append($1); }
         ;

Stmt : ';' { $$ = new EmptyExpr; }
     | Expr ';' { $$ = $1; }
     | T_If '(' Expr ')' Stmt MaybeElse { $$ = new IfStmt($3, $5, $6); }
     | T_While '(' Expr ')' Stmt { $$ = new WhileStmt($3, $5); }
     | T_For '(' MaybeExpr ';' Expr ';' MaybeExpr ')' Stmt { $$ = new ForStmt($3, $5, $7, $9); }
     | T_Break ';' { $$ = new BreakStmt(@1); }
     | T_Return ';' { $$ = new ReturnStmt(@1, new EmptyExpr); }
     | T_Return Expr ';' { $$ = new ReturnStmt(@1, $2); }
     | T_Print '(' ExprList ')' ';' { $$ = new PrintStmt($3); }
     | T_Switch '(' Expr ')' '{' CaseList MaybeDefault '}' { $$ = new SwitchStmt($3, $6, $7); }
     | StmtBlock
     ;

MaybeElse : /* empty */ { $$ = 0; }
          | T_Else Stmt { $$ = $2; }
          ;

ExprList : ExprList ',' Expr { ($$=$1)->Append($3); }
         | Expr { ($$=new List<Expr*>)->Append($1); }
         ;

CaseList : CaseList Case { ($$=$1)->Append($2); }
         | Case { ($$=new List<CaseStmt*>)->Append($1); }
	 ;

Case : T_Case T_IntConstant ':' MaybeStmtList MaybeBreak { $$ = new CaseStmt(new IntConstant(@2, $2), $4, $5); }
     ;

MaybeDefault : /* empty */ { $$ = 0; }
             | T_Default ':' MaybeStmtList MaybeBreak { $$ = new DefaultStmt($3, $4); }
             ;

MaybeStmtList : /* empty */ { $$ = new List<Stmt*>; }
              | StmtList
	      ;

MaybeBreak : /* empty */ { $$ = 0; }
           | T_Break ';' { $$ = new BreakStmt(@1); }
	   ;

Call : Ident '(' Actuals ')' { $$ = new Call(@3, 0, $1, $3); }
     | Expr '.' Ident '(' Actuals ')' { $$ = new Call(@3, $1, $3, $5); }
     ;

Actuals : /* empty */ { $$ = new List<Expr*>; }
        | ExprList
        ; 

Constant : T_IntConstant { $$ = new IntConstant(@1, $1); }
         | T_DoubleConstant { $$ = new DoubleConstant(@1, $1); }
         | T_BoolConstant { $$ = new BoolConstant(@1, $1); }
         | T_StringConstant { $$ = new StringConstant(@1, $1); }
         | T_Null { $$ = new NullConstant(@1); }
         ;

MaybeExpr : /* empty */ { $$ = new EmptyExpr; }
          | Expr
          ;

Expr : Constant
     | LValue
     | T_This { $$ = new This(@1); }
     | Call
     | '(' Expr ')' { $$ = $2; }
     | T_ReadInteger '(' ')' { $$ = new ReadIntegerExpr(@1); }
     | T_ReadLine '(' ')' { $$ = new ReadLineExpr(@1); }
     | T_New '(' Ident ')' { $$ = new NewExpr(@1, new NamedType($3)); }
     | T_NewArray '(' Expr ',' Type ')' { $$ = new NewArrayExpr(@1, $3, $5); }
     | Expr '.' Ident { $$ = new FieldAccess($1, $3); }
     | Expr '[' Expr ']' { $$ = new ArrayAccess(@1, $1, $3); }
     | '!' Expr { $$ = new LogicalExpr(new Operator(@1, "!"), $2); }
     | '-' Expr { $$ = new ArithmeticExpr(new Operator(@1, "-"), $2); }
     | Expr T_PostIncr { $$ = new PostfixExpr($1, new Operator(@2, "++")); }
     | Expr T_PostDecr { $$ = new PostfixExpr($1, new Operator(@2, "--")); }
     | Expr '*' Expr { $$ = new ArithmeticExpr($1, new Operator(@2, "*"), $3); }
     | Expr '/' Expr { $$ = new ArithmeticExpr($1, new Operator(@2, "/"), $3); }
     | Expr '%' Expr { $$ = new ArithmeticExpr($1, new Operator(@2, "%"), $3); }
     | Expr '+' Expr { $$ = new ArithmeticExpr($1, new Operator(@2, "+"), $3); }
     | Expr '-' Expr { $$ = new ArithmeticExpr($1, new Operator(@2, "-"), $3); }
     | Expr '<' Expr { $$ = new RelationalExpr($1, new Operator(@2, "<"), $3); }
     | Expr T_LessEqual Expr { $$ = new RelationalExpr($1, new Operator(@2, "<="), $3); }
     | Expr '>' Expr { $$ = new RelationalExpr($1, new Operator(@2, ">"), $3); }
     | Expr T_GreaterEqual Expr { $$ = new RelationalExpr($1, new Operator(@2, ">="), $3); }
     | Expr T_Equal Expr { $$ = new EqualityExpr($1, new Operator(@2, "=="), $3); }
     | Expr T_NotEqual Expr { $$ = new EqualityExpr($1, new Operator(@2, "!="), $3); }
     | Expr T_And Expr { $$ = new LogicalExpr($1, new Operator(@2, "&&"), $3); }
     | Expr T_Or Expr { $$ = new LogicalExpr($1, new Operator(@2, "||"), $3); }
     | LValue '=' Expr { $$ = new AssignExpr($1, new Operator(@2, "="), $3); }
     ;

LValue : Ident { $$ = new FieldAccess(0, $1); }
       | Expr '.' Ident { $$ = new FieldAccess($1, $3); }
       | Expr '[' Expr ']' { $$ = new ArrayAccess(@1, $1, $3); }
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
