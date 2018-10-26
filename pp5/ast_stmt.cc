/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "errors.h"
#include "codegen.h"

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::CheckNode() {
    CheckTypes(decls);
}

void Program::Emit() {
    cg = new CodeGenerator();
    for (int i = 0; i < decls->NumElements(); ++i) {
        decls->Nth(i)->Emit();
    }
    cg->DoFinalCodeGen();
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

void StmtBlock::Emit() {
    for (int i=0;i<decls->NumElements();++i) {
        decls->Nth(i)->Emit();
    }
    for (int i=0;i<stmts->NumElements();++i) {
        stmts->Nth(i)->Emit();
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
    if (!test->GetType()->IsEquivalentTo(Type::boolType)) {
        ReportError::TestNotBoolean(test);
    }
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

void WhileStmt::Emit() {
    char *start_label = cg->NewLabel();
    char *end_label = cg->NewLabel();
    cg->GenLabel(start_label);
    test->Emit();
    cg->GenIfZ(test->ResultLocation(), end_label);
    body->Emit();
    cg->GenGoto(start_label);
    cg->GenLabel(end_label);
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

void IfStmt::Emit() {
    test->Emit();
    char *true_label = cg->NewLabel();
    char *false_label = cg->NewLabel();
    char *end_label = cg->NewLabel();
    cg->GenIfZ(test->ResultLocation(), false_label);
    cg->GenGoto(true_label);
    cg->GenLabel(true_label);
    body->Emit();
    cg->GenGoto(end_label);
    cg->GenLabel(false_label);
    if (elseBody) {
        elseBody->Emit();
    }
    cg->GenLabel(end_label);
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::CheckNode() {
    expr->Check();
    Type *type = expr->GetType();
    Node *super = this;
    FnDecl *as_func = NULL;
    while ((super = super->GetParent())) {
        if (super == NULL) {
            break;
        }
        as_func = dynamic_cast<FnDecl*>(super);
        if (as_func != NULL) {
            break;
        }
    }
    if (as_func) {
        if (!as_func->GetType()->IsEquivalentTo(type)) {
            ReportError::ReturnMismatch(this, type, as_func->GetType());
        }
    }
}

void ReturnStmt::Emit() {
    expr->Emit();
    cg->GenReturn(expr->ResultLocation());
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

void PrintStmt::Emit() {
    for (int i=0;i<args->NumElements();++i) {
        Expr *arg = args->Nth(i);
	arg->Emit();
	Type *arg_type = arg->GetType();
	if (Type::intType->IsEquivalentTo(arg_type)) {
	    cg->GenBuiltInCall(PrintInt, arg->ResultLocation());
	} else if (Type::stringType->IsEquivalentTo(arg_type)) {
            cg->GenBuiltInCall(PrintString, arg->ResultLocation());
	} else if (Type::boolType->IsEquivalentTo(arg_type)) {
	    cg->GenBuiltInCall(PrintBool, arg->ResultLocation());
	}
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
