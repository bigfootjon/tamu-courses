/* File: ast.cc
 * ------------
 */

#include "ast.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> // strdup
#include <stdio.h>  // printf
#include "errors.h"

Node::Node(yyltype loc) {
    location = new yyltype(loc);
    parent = NULL;
    visited = false;
}

Node::Node() {
    location = NULL;
    parent = NULL;
    visited = false;
}

Decl *Node::LookupType(char *name, bool recursive) {
    Decl *local = table.Lookup(name);
    if (local != NULL) {
        return local;
    }
    if (!recursive) {
        return NULL;
    }
    if (GetParent() == NULL) {
        return NULL;
    }
    return GetParent()->LookupType(name);
}

void Node::CheckTypes(List<Decl*> *decls) {
    for (int i=0; i < decls->NumElements(); ++i) {
        Decl *cur = decls->Nth(i);
        Decl *found = table.Lookup(cur->GetName());
	if (found != NULL) {
            ReportError::DeclConflict(cur, found);
	} else {
            table.Enter(cur->GetName(), cur);
	}
    }
    for (int i=0; i < decls->NumElements(); ++i) {
        decls->Nth(i)->Check();
    }
}
	 
Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
    name = strdup(n);
} 

