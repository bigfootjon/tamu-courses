/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "errors.h"
#include "codegen.h"

CodeGenerator *cg;
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}

void Decl::CheckNode() {
    id->Check();
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

void VarDecl::CheckNode() {
    id->Check();
    type->Check();
}

bool VarDecl::IsEquivalentTo(Decl* o) {
    VarDecl* other = dynamic_cast<VarDecl*>(o);
    if (other == NULL) {
        return false;
    }

    return this->type->IsEquivalentTo(other->type);
} 

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}

void ClassDecl::CheckNode() {
    if (extends) {
        Decl *superclass = LookupType(extends->GetId()->GetName());
        if (superclass == NULL || dynamic_cast<ClassDecl*>(superclass) == NULL) {
            ReportError::IdentifierNotDeclared(extends->GetId(), LookingForClass);
        }
    }
    for (int i=0;i<implements->NumElements();++i) {
        NamedType *cur = implements->Nth(i);
	Decl *interface = LookupType(cur->GetId()->GetName());
        if (interface == NULL || dynamic_cast<InterfaceDecl*>(interface) == NULL) {
            ReportError::IdentifierNotDeclared(cur->GetId(), LookingForInterface);
	}
    }
    for (int i=0; i < members->NumElements(); ++i) {
        Decl *cur = members->Nth(i);
        Decl *found = table.Lookup(cur->GetName());
	if (found != NULL) {
            ReportError::DeclConflict(cur, found);
	    continue;
	}
	if (extends != NULL) {
	    Decl *superclass = LookupType(extends->GetId()->GetName());
	    superclass->Check();
	    Decl *inherited = superclass->LookupType(cur->GetName(), false);
	    if (inherited != NULL) {
                if (dynamic_cast<VarDecl*>(cur) != NULL || dynamic_cast<VarDecl*>(inherited) != NULL) {
                    ReportError::DeclConflict(cur, inherited);
	            continue;
	        }
		if (!cur->IsEquivalentTo(inherited)) {
                    ReportError::OverrideMismatch(cur);
                    continue;
		}
	    }
	}
	for (int i=0;i<implements->NumElements();++i) {
            Decl *interface = LookupType(implements->Nth(i)->GetId()->GetName());
	    interface->Check();
	    Decl *inherited = interface->LookupType(cur->GetName(), false);
	    if (inherited != NULL && !cur->IsEquivalentTo(inherited)) {
                ReportError::OverrideMismatch(cur);
		continue;
	    }
	}
        table.Enter(cur->GetName(), cur);
    }
    for (int i=0;i<implements->NumElements();++i) {
        InterfaceDecl *interface = dynamic_cast<InterfaceDecl*>(LookupType(implements->Nth(i)->GetId()->GetName()));
        if (interface == NULL) {
            continue;
        }
        List<Decl*> *int_members = interface->GetMembers();
        for (int j=0;j<int_members->NumElements();++j) {
            FnDecl *member = (FnDecl*)int_members->Nth(j);
	    Decl *found = LookupType(member->GetId()->GetName(), false);
            if (found == NULL || !member->IsEquivalentTo(found)) {
                ReportError::InterfaceNotImplemented(this, implements->Nth(i));
            }
	}
    }
    for (int i=0; i < members->NumElements(); ++i) {
        members->Nth(i)->Check();
    }
}

bool ClassDecl::IsEquivalentTo(Decl *o) {
    if (Decl::IsEquivalentTo(o)) {
        return true;
    }
    ClassDecl *other = dynamic_cast<ClassDecl*>(o);
    if (other == NULL) {
        return false;
    }
    if (other->extends && this->IsEquivalentTo(LookupType(other->extends->GetId()->GetName()))) {
        return true;
    }
    return false;
}

Type *ClassDecl::GetType() {
    return new NamedType(GetId());
}

Decl *ClassDecl::LookupType(char *name, bool recursive) {
    Decl *superclass = Decl::LookupType(name, recursive);
    if (superclass != NULL) {
        return superclass;
    }
    if (!recursive) {
        return NULL;
    }
    if (extends && Decl::LookupType(extends->GetId()->GetName()) != NULL) {
        Decl *parent = Decl::LookupType(extends->GetId()->GetName())->LookupType(name, recursive);
	if (parent) {
            return parent;
	}
    }
    for (int i=0;i<implements->NumElements();++i) {
        InterfaceDecl *interface = dynamic_cast<InterfaceDecl*>(Decl::LookupType(implements->Nth(i)->GetId()->GetName()));
	if (interface) {
	    Decl *ininterface = interface->LookupType(name, recursive);
            if (ininterface) {
                return ininterface;
	    }
	}
    }
    return NULL;
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::CheckNode() {
    CheckTypes(members);
}

bool InterfaceDecl::IsEquivalentTo(Decl *o) {
    if (Decl::IsEquivalentTo(o)) {
        return true;
    }
    ClassDecl *other = dynamic_cast<ClassDecl*>(o);
    if (other == NULL) {
        return false;
    }
    while (other != NULL) {
        for (int i=0;i<other->implements->NumElements();++i) {
            if (strcmp(other->implements->Nth(i)->GetId()->GetName(), GetName()) == 0) {
                return true;
            }
        }
        if (other->extends == NULL) {
            break;
        }
        other = dynamic_cast<ClassDecl*>(LookupType(other->extends->GetId()->GetName()));
    }
    return false;
}
	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

void FnDecl::Emit() {
    cg->GenLabel(GetName());
    BeginFunc *func = cg->GenBeginFunc();
    body->Emit();
    func->SetFrameSize(4);
    cg->GenEndFunc();
}

void FnDecl::CheckNode() {
    returnType->Check();
    CheckTypes((List<Decl*>*)formals);
    if (body) body->Check();
}

bool FnDecl::IsEquivalentTo(Decl* o) {
    FnDecl* other = dynamic_cast<FnDecl*>(o);
    if (other == NULL) {
        return false;
    }
    if (!this->returnType->IsEquivalentTo(other->returnType)) {
        return false;
    }
    if (this->formals->NumElements() != other->formals->NumElements()) {
        return false;
    }
    for (int i=0;i<this->formals->NumElements();++i) {
        VarDecl *myFormal = this->formals->Nth(i);
	VarDecl *otherFormal = other->formals->Nth(i);
        if (!myFormal->IsEquivalentTo(otherFormal)) {
            return false;
	}
    }
    return true;
}

