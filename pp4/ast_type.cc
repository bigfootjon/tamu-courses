/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"

 
/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error"); 

Type::Type(const char *n) {
    Assert(n);
    typeName = strdup(n);
}

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
} 

void NamedType::CheckNode() {
    if (LookupType(id->GetName()) == NULL) {
        ReportError::IdentifierNotDeclared(id, LookingForType);
    }
}

bool NamedType::IsEquivalentTo(Type* o) {
    if (Type::IsEquivalentTo(o)) {
        return true;
    }
    if (o == Type::nullType) {
        return true;
    }
    NamedType *other = dynamic_cast<NamedType*>(o);
    if (other == NULL) {
        return false;
    }
    if (strcmp(this->id->GetName(), other->id->GetName()) == 0) {
        return true;
    }
    Decl *me_decl = LookupType(this->id->GetName());
    Decl *ot_decl = LookupType(other->id->GetName());
    if (me_decl == NULL || ot_decl == NULL) {
        return false;
    }
    return me_decl->IsEquivalentTo(ot_decl);
}

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}

void ArrayType::CheckNode() {
    elemType->Check();
}


bool ArrayType::IsEquivalentTo(Type* o) {
    if (Type::IsEquivalentTo(o)) {
        return true;
    }
    ArrayType *other = dynamic_cast<ArrayType*>(o);
    if (other == NULL) {
        return false;
    }
    return this->elemType->IsEquivalentTo(other->elemType);
}
