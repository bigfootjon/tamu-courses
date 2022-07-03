/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "errors.h"


Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::CheckNode() {
    CheckTypes(decls);
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

void StmtBlock::CheckNode() {
    CheckTypes((List<Decl*>*)decls);
    for (int i=0;i<stmts->NumElements();++i) {
        stmts->Nth(i)->Check();
    }
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

void ConditionalStmt::CheckNode() {
    test->Check();
    body->Check();
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

void ForStmt::CheckNode() {
    LoopStmt::CheckNode();
    init->Check();
    step->Check();
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::CheckNode() {
    ConditionalStmt::CheckNode();
    if (elseBody) elseBody->Check();
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::CheckNode() {
    expr->Check();
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::CheckNode() {
    for (int i=0;i<args->NumElements();++i) {
        args->Nth(i)->Check();
    }
}

void Case::CheckNode() {
    for (int i=0;i<stmts->NumElements();++i) {
        stmts->Nth(i)->Check();
    }
}

void SwitchStmt::CheckNode() {
    value->Check();
    for (int i=0;i<cases->NumElements();++i) {
        cases->Nth(i)->Check();
    }
}
