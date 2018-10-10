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
    return Type::errorType;
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
    if (_GetType() != NULL) {
        return;
    }
    Type *ltype = left->GetType();
    Type *rtype = right->GetType();
    if (ltype == NULL || rtype == NULL) {
       return;
    }
    if (ltype == Type::errorType || rtype == Type::errorType) {
        return;
    }
    ReportError::IncompatibleOperands(op, ltype, rtype);
}

Type *CompoundExpr::_GetType() {
    Type *rType = right->GetType();
    if (left == NULL) {
        return rType;
    }
    Type *lType = left->GetType();
    if (lType->IsEquivalentTo(rType)) {
        return lType;
    }
    if (Type::errorType->IsEquivalentTo(lType) || Type::errorType->IsEquivalentTo(rType)) {
        return Type::errorType;
    }
    return NULL;
}

void ArithmeticExpr::CheckNode() {
    CompoundExpr::CheckNode();
    Type *type = GetType();
    if (type == NULL || Type::errorType->IsEquivalentTo(type)) {
        return;
    }
    if (Type::intType->IsEquivalentTo(type) || Type::doubleType->IsEquivalentTo(type)) {
        return;
    }
    ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
}

void RelationalExpr::CheckNode() {
    CompoundExpr::CheckNode();
    Type *type = CompoundExpr::GetType();
    if (type == NULL || Type::errorType->IsEquivalentTo(type)) {
        return;
    }
    if (Type::intType->IsEquivalentTo(type) || Type::doubleType->IsEquivalentTo(type)) {
        return;
    }
    ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
}

Type *RelationalExpr::GetType() {
    return Type::boolType;
}

Type *EqualityExpr::GetType() {
    return Type::boolType;
}

void LogicalExpr::CheckNode() {
    CompoundExpr::CheckNode();
    Type *type = CompoundExpr::GetType();
    if (type == NULL || Type::errorType->IsEquivalentTo(type)) {
        return;
    }
    if (Type::boolType->IsEquivalentTo(type)) {
        return;
    }
    ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
}

Type *LogicalExpr::GetType() {
    return Type::boolType;
}

Type *LValue::GetType() {
    return Type::errorType; // Pretty sure this is never called
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

Decl *This::LookupType(char *name, bool recursive) {
    if (GetClass() == NULL) {
        return NULL;
    }
    return GetClass()->LookupType(name, recursive);
}
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

void ArrayAccess::CheckNode() {
    base->Check();
    if (dynamic_cast<ArrayType*>(base->GetType()) == NULL) {
        ReportError::BracketsOnNonArray(base);
    }
    subscript->Check();
    if (!Type::intType->IsEquivalentTo(subscript->GetType())) {
        ReportError::SubscriptNotInteger(subscript);
    }
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

Node *FieldAccess::Get() {
    Node* n = NULL;
    if (base) {
        if (base->GetType() == Type::errorType) {
            return NULL;
	}
        NamedType *type = dynamic_cast<NamedType*>(base->GetType());
        if (type == NULL) {
            n = NULL;
        } else {
            n = LookupType(type->GetId()->GetName())->LookupType(field->GetName());
        }
    } else {
        n = LookupType(field->GetName());
    }
    return n;
}

void FieldAccess::CheckNode() {
    if (base) base->Check();
    Node *got = Get();
    if (got == NULL || dynamic_cast<VarDecl*>(got) == NULL) {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
    }
}

Type *FieldAccess::GetType() {
    VarDecl *vd = dynamic_cast<VarDecl*>(Get());
    if (vd != NULL) {
        return vd->GetType();
    }
    ClassDecl *cd = dynamic_cast<ClassDecl*>(Get());
    if (cd != NULL) {
        return cd->GetType();
    }
    return Type::errorType;
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
        if (base->GetType() == Type::errorType) {
            return;
	}
        NamedType *type = dynamic_cast<NamedType*>(base->GetType());
        if (type == NULL) {
            calling = NULL;
        } else {
            calling = dynamic_cast<FnDecl*>(LookupType(type->GetId()->GetName())->LookupType(field->GetName()));
        }
    } else {
        calling = dynamic_cast<FnDecl*>(LookupType(field->GetName()));
    }
    if (calling == NULL) {
        if ((base && dynamic_cast<ArrayType*>(base->GetType()) == NULL) || strcmp(field->GetName(), "length") != 0) {
            if (base != NULL) {
                ReportError::FieldNotFoundInBase(field, base->GetType());
            } else {
                ReportError::IdentifierNotDeclared(field, LookingForFunction);
            }
        }
        return;
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
        if (base->GetType() == Type::errorType) {
            return Type::errorType;
	}
        NamedType *ptype = dynamic_cast<NamedType*>(base->GetType());
        if (ptype == NULL) {
            return Type::voidType;
        }
        n = LookupType(ptype->GetId()->GetName())->LookupType(name, false);
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
    if (!Type::intType->IsEquivalentTo(size->GetType())) {
        ReportError::NewArraySizeNotInteger(size);
    }
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

