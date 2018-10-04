/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"


Type *EmptyExpr::GetType() {
    return Type::voidType;
}

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

Type *IntConstant::GetType() {
    return Type::intType;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

Type *DoubleConstant::GetType() {
    return Type::doubleType;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

Type *BoolConstant::GetType() {
    return Type::boolType;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Type *StringConstant::GetType() {
    return Type::stringType;
}

Type *NullConstant::GetType() {
    return Type::nullType;
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}

Type *Operator::GetType() {
    return Type::voidType;
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

void CompoundExpr::CheckNode() {
    if (left) left->Check();
    op->Check();
    right->Check();
    if (Type::voidType->IsEquivalentTo(GetType())) {
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
    }
}

Type *CompoundExpr::GetType() {
    Type *rType = right->GetType();
    if (left == NULL) {
        return rType;
    }
    Type *lType = left->GetType();
    if (lType->IsEquivalentTo(rType)) {
        return lType;
    }
    return Type::voidType;
}

Type *LValue::GetType() {
    return Type::voidType; // Pretty sure this is never called
}

void PostfixExpr::CheckNode() {
    left->Check();
    op->Check();
}

Type *PostfixExpr::GetType() {
    return left->GetType();
}

ClassDecl *This::GetClass() {
    Node *super = this;
    while ((super = super->GetParent()) != NULL) {
        ClassDecl *as_class = dynamic_cast<ClassDecl*>(super);
        if (as_class != NULL) {
            return as_class;
        }
    }
    return NULL;
}

void This::CheckNode() {
    if (GetClass() == NULL) {
        ReportError::ThisOutsideClassScope(this);
    }
}

Type *This::GetType() {
    return new NamedType(GetClass()->GetId());
}
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

void ArrayAccess::CheckNode() {
    base->Check();
    subscript->Check();
}

Type *ArrayAccess::GetType() {
    return ((ArrayType*)base->GetType())->GetBaseType();
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}

void FieldAccess::CheckNode() {
    if (base) base->Check();
    if (LookupType(field->GetName()) == NULL) {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
    }
}

Type *FieldAccess::GetType() {
    char *name = field->GetName();
    Node *n = NULL;
    if (base == NULL) {
        n = LookupType(name);
    } else {
        n = base->LookupType(name, false);
    }
    return dynamic_cast<VarDecl*>(n)->GetType();
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

void Call::CheckNode() {
    if (base) base->Check();
    for (int i=0;i<actuals->NumElements(); ++i) {
        actuals->Nth(i)->Check();
    }
    FnDecl* calling = NULL;
    if (base) {
        NamedType *type = dynamic_cast<NamedType*>(base->GetType());
        calling = dynamic_cast<FnDecl*>(LookupType(type->GetId()->GetName())->LookupType(field->GetName()));
    } else {
        calling = dynamic_cast<FnDecl*>(LookupType(field->GetName()));
    }
    if (calling == NULL) {
        ReportError::IdentifierNotDeclared(field, LookingForFunction);
    }
    List<VarDecl*> *formals = calling->GetFormals();
    if (formals->NumElements() != actuals->NumElements()) {
        ReportError::NumArgsMismatch(field, formals->NumElements(), actuals->NumElements());
    } else {
        for (int i=0; i<formals->NumElements();++i) {
            Type *expected = formals->Nth(i)->GetType();
            Type *actual = actuals->Nth(i)->GetType();
            if (!expected->IsEquivalentTo(actual)) {
                ReportError::ArgMismatch(actuals->Nth(i), i+1, actual, expected);
            }
        }
    }
}

Type *Call::GetType() {
    char *name = field->GetName();
    Node *n = NULL;
    if (base == NULL) {
        n = LookupType(name);
    } else {
        n = base->LookupType(name, false);
    }
    return dynamic_cast<FnDecl*>(n)->GetType();
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::CheckNode() {
    if (dynamic_cast<ClassDecl*>(LookupType(cType->GetId()->GetName())) == NULL) {
        ReportError::IdentifierNotDeclared(cType->GetId(), LookingForClass);
    }
}

Type *NewExpr::GetType() {
    return cType;
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc), location(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

void NewArrayExpr::CheckNode() {
    size->Check();
    elemType->Check();
}

Type *NewArrayExpr::GetType() {
    return new ArrayType(location, elemType);
}

Type *ReadIntegerExpr::GetType() {
    return Type::intType;
}

Type *ReadLineExpr::GetType() {
    return Type::stringType;
}

