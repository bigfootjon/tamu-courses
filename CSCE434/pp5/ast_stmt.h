/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp5: You will need to extend the stmt classes to implement
 * code generation for statments.
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"

class Decl;
class VarDecl;
class Expr;
class IntConstant;
  
class Program : public Node
{
  protected:
     List<Decl*> *decls;
     
  public:
     Program(List<Decl*> *declList);
     void CheckNode();
     void Emit();
};

class Stmt : public Node
{
  public:
     Stmt() : Node() {}
     Stmt(yyltype loc) : Node(loc) {}
};

class StmtBlock : public Stmt 
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
    
  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    void CheckNode();
    void Emit();
};

  
class ConditionalStmt : public Stmt
{
  public:
    Expr *test;
    Stmt *body;
    ConditionalStmt(Expr *testExpr, Stmt *body);
    void CheckNode();
};

class LoopStmt : public ConditionalStmt 
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
    char *end_label;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    void CheckNode();
    void Emit();
    char *EndLabel() { return end_label; }
};

class WhileStmt : public LoopStmt 
{
  private:
    char *end_label;

  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    void Emit();
    char *EndLabel() { return end_label; }
};

class IfStmt : public ConditionalStmt 
{
  protected:
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    void CheckNode();
    void Emit();
};

class BreakStmt : public Stmt 
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
    void Emit();
};

class ReturnStmt : public Stmt  
{
  protected:
    Expr *expr;
  
  public:
    ReturnStmt(yyltype loc, Expr *expr);
    void CheckNode();
    void Emit();
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;
    
  public:
    PrintStmt(List<Expr*> *arguments);
    void CheckNode();
    void Emit();
};

class Case : public Stmt
{
  protected:
    IntConstant *label;
    List<Stmt*> *stmts;

  public:
    Case(IntConstant *i, List<Stmt*> *s) : label(i), stmts(s) {}
    void CheckNode();
};

class SwitchStmt : public Stmt
{
  protected:
    Expr *value;
    List<Case*> *cases;

  public:
    SwitchStmt(Expr *val, List<Case*> *list) : value(val), cases(list) {}
    void CheckNode();
};

#endif
