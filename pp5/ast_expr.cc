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

void CompoundExpr::Emit() {
    right->Emit();
    Location *right_loc = right->ResultLocation();
    Location *left_loc;
    char *op_string = op->GetOpString();
    
    if (left) {
        left->Emit();
        left_loc = left->ResultLocation();
    } else {
        left_loc = cg->GenLoadConstant(0);
        if (strcmp(op_string, "!") == 0) {
            op_string = (char*)"==";
        }
    }
    if (strcmp(op_string, "<=") == 0) {
        Location *const_1 = cg->GenLoadConstant(1);
        right_loc = cg->GenBinaryOp((char*)"+", right_loc, const_1);
	op_string = (char*)"<";
    } else if (strcmp(op_string, ">") == 0) {
        Location *temp = left_loc;
	left_loc = right_loc;
	right_loc = temp;
	op_string = (char*)"<";
    } else if (strcmp(op_string, ">=") == 0) {
        Location *temp = left_loc;
	left_loc = right_loc;
	right_loc = temp;
        Location *const_1 = cg->GenLoadConstant(1);
        right_loc = cg->GenBinaryOp((char*)"+", right_loc, const_1);
	op_string = (char*)"<";
    } else if (strcmp(op_string, "!=") == 0) {
        right_loc = cg->GenBinaryOp((char*)"==", left_loc, right_loc);
	left_loc = cg->GenLoadConstant(0);
        op_string = (char*)"==";
    }
    SetResult(cg->GenBinaryOp(op_string, left_loc, right_loc));
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
    if (left) {
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
    } else {
        ReportError::IncompatibleOperand(op, right->GetType());
    }
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
    if (left) {
        ReportError::IncompatibleOperands(op, left->GetType(), right->GetType());
    } else {
        ReportError::IncompatibleOperand(op, right->GetType());
    }
}

Type *LogicalExpr::GetType() {
    return Type::boolType;
}

void AssignExpr::Emit() {
    left->Emit();
    right->Emit();
    if (left->NeedsStore() != NULL) {
        cg->GenStore(left->NeedsStore(), right->ResultLocation());
    } else {
        cg->GenAssign(left->ResultLocation(), right->ResultLocation());
    }
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

void PostfixExpr::Emit() {
    char *op_string = (char*)"+";
    if (strcmp(op->GetOpString(), "--") == 0) {
        op_string = (char*)"-";
    }
    left->Emit();
    Location *result = cg->GenTempVar();
    cg->GenAssign(result, left->ResultLocation());
    SetResult(result);
    cg->GenAssign(left->ResultLocation(), cg->GenBinaryOp(op_string, left->ResultLocation(), cg->GenLoadConstant(1)));
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

void This::Emit() {
    SetResult(cg->ThisPtr);
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

void ArrayAccess::Emit() {
    char *good_label = cg->NewLabel();
    base->Emit();
    subscript->Emit();
    Location *const_0 = cg->GenLoadConstant(0);
    Location *gt0 = cg->GenBinaryOp((char*)"<", subscript->ResultLocation(), const_0);
    Location *size = cg->GenLoad(base->ResultLocation(), 0);
    Location *lts = cg->GenBinaryOp((char*)"<", cg->GenBinaryOp((char*)"-", size, cg->GenLoadConstant(1)), subscript->ResultLocation());
    Location *either = cg->GenBinaryOp((char*)"||", gt0, lts);
    cg->GenIfZ(either, good_label);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant("Decaf runtime error: Array subscript out of bounds"));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(good_label);
    Location *padded_subscript = cg->GenBinaryOp("+", subscript->ResultLocation(), cg->GenLoadConstant(1));
    Location *offset = cg->GenBinaryOp("*", padded_subscript, cg->GenLoadConstant(cg->VarSize));
    Location *address = cg->GenBinaryOp("+", base->ResultLocation(), offset);
    Location *location = cg->GenLoad(address, 0);
    SetResult(location, address);
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
	Type *base_type = base->GetType();
        if (Type::errorType->IsEquivalentTo(base_type)) {
            return NULL;
	}
        NamedType *named_base_type = dynamic_cast<NamedType*>(base_type);
        if (named_base_type == NULL) {
            n = NULL;
        } else {
	    Node *klass = LookupType(named_base_type->GetId()->GetName());
	    klass->Check();
            n = klass->LookupType(field->GetName());
        }
    } else {
        n = LookupType(field->GetName());
    }
    return n;
}

bool FieldAccess::HasAccess() {
    if (!base) {
        return true;
    }
    if (base->GetType() == Type::errorType) {
        return true;
    }
    NamedType *type = dynamic_cast<NamedType*>(base->GetType());
    if (type == NULL) {
        return true;
    }
    ClassDecl *as_class = dynamic_cast<ClassDecl*>(LookupType(type->GetId()->GetName()));
    if (as_class) {
        Node *super = this;
	do {
           ClassDecl *parent_class = dynamic_cast<ClassDecl*>(super);
	   if (parent_class) {
	       if (parent_class->IsEquivalentTo(as_class)) {
	           return true;
	       }
	   }
	} while ((super = super->GetParent()));
	return false;
    }
    return true;
}

void FieldAccess::CheckNode() {
    if (base) base->Check();
    Node *got = Get();
    if (got == NULL || dynamic_cast<VarDecl*>(got) == NULL) {
        if (base) {
            ReportError::FieldNotFoundInBase(field, base->GetType());
	} else {
            ReportError::IdentifierNotDeclared(field, LookingForVariable);
	}
	return;
    }
    if (!HasAccess()) {
        ReportError::InaccessibleField(field, base->GetType());
    }
}

Type *FieldAccess::GetType() {
    if (!HasAccess()) {
        return Type::errorType;
    }
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

void FieldAccess::Emit() {
    VarDecl *var_decl = dynamic_cast<VarDecl*>(Get());
    if (base) {
        base->Emit();
        ClassDecl *class_decl = dynamic_cast<ClassDecl*>(var_decl->GetParent());
	int offset = class_decl->VarOffset(var_decl->GetName());
	Location *address = cg->GenBinaryOp("+", base->ResultLocation(), cg->GenLoadConstant(offset+cg->VarSize));
	Location *location = cg->GenLoad(address, 0);
        SetResult(location, address);
    } else {
        if (var_decl->GetLocation() == NULL) {
            ClassDecl *class_decl = dynamic_cast<ClassDecl*>(var_decl->GetParent());
	    int offset = class_decl->VarOffset(var_decl->GetName());
	    Location *address = cg->GenBinaryOp("+", cg->ThisPtr, cg->GenLoadConstant(offset+cg->VarSize));
	    Location *location = cg->GenLoad(address, 0);
            SetResult(location, address);
	} else {
            SetResult(var_decl->GetLocation());
	}
    }
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
    calling = NULL;
    if (base) {
        if (base->GetType() == Type::errorType) {
            return;
	}
        NamedType *type = dynamic_cast<NamedType*>(base->GetType());
        if (type == NULL) {
            calling = NULL;
        } else {
            Decl *superclass = LookupType(type->GetId()->GetName());
            superclass->Check();
            calling = dynamic_cast<FnDecl*>(superclass->LookupType(field->GetName()));
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
    Check();
    if (calling) {
        return calling->GetType();
    }
    if (dynamic_cast<ArrayType*>(base->GetType()) != NULL && strcmp(field->GetName(), "length") == 0) {
        return Type::intType;
    }
    return Type::errorType;
}

void Call::Emit() {
    for (int i = 0; i < actuals->NumElements(); ++i) {
        actuals->Nth(i)->Emit();
    }
    for (int i = actuals->NumElements() - 1; i >= 0; --i) {
        cg->GenPushParam(actuals->Nth(i)->ResultLocation());
    }
    bool hasReturn = Type::voidType->IsEquivalentTo(calling->GetType());
    int thisarg = 0;
    if (base) {
        thisarg = 1;
        base->Emit();
        cg->GenPushParam(base->ResultLocation());
        Location *obj = cg->GenLoad(base->ResultLocation());
	ClassDecl *class_obj = dynamic_cast<ClassDecl*>(calling->GetParent());
	class_obj->Check();
        Location *func = cg->GenLoad(obj, class_obj->FuncOffset(field->GetName()));
        SetResult(cg->GenACall(func, !hasReturn));
    } else {
        SetResult(cg->GenLCall(calling->GetName(), !hasReturn));
    }
    cg->GenPopParams(cg->VarSize * (actuals->NumElements() + thisarg));
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

ClassDecl *NewExpr::Get() {
    return dynamic_cast<ClassDecl*>(LookupType(cType->GetId()->GetName()));
}

void NewExpr::CheckNode() {
    if (Get() == NULL) {
        ReportError::IdentifierNotDeclared(cType->GetId(), LookingForClass);
    }
}

Type *NewExpr::GetType() {
    return cType;
}

void NewExpr::Emit() {
    Location *alloced = cg->GenBuiltInCall(Alloc, cg->GenLoadConstant((Get()->VarCount() + 1) * cg->VarSize));
    cg->GenStore(alloced, cg->GenLoadLabel(Get()->GetName()));
    SetResult(alloced);
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

void NewArrayExpr::Emit() {
    char *good_label = cg->NewLabel();
    size->Emit();
    Location *const_0 = cg->GenLoadConstant(0);
    Location *gt0 = cg->GenBinaryOp((char*)"<", size->ResultLocation(), const_0);
    cg->GenIfZ(gt0, good_label);
    cg->GenBuiltInCall(PrintString, cg->GenLoadConstant("Decaf runtime error: Array size is <= 0"));
    cg->GenBuiltInCall(Halt);
    cg->GenLabel(good_label);
    Location *const_1 = cg->GenLoadConstant(1);
    Location *total_count = cg->GenBinaryOp((char*)"+", const_1, size->ResultLocation());
    Location *var_size = cg->GenLoadConstant(cg->VarSize);
    Location *total_size = cg->GenBinaryOp((char*)"*", total_count, var_size);
    Location *alloced = cg->GenBuiltInCall(Alloc, total_size);
    cg->GenStore(alloced, size->ResultLocation(), 0);
    SetResult(alloced);
}

Type *ReadIntegerExpr::GetType() {
    return Type::intType;
}

void ReadIntegerExpr::Emit() {
    SetResult(cg->GenBuiltInCall(ReadInteger));
}

Type *ReadLineExpr::GetType() {
    return Type::stringType;
}

void ReadLineExpr::Emit() {
    SetResult(cg->GenBuiltInCall(ReadInteger));
}

