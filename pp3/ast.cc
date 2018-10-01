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
}

Node::Node() {
    location = NULL;
    parent = NULL;
}

Decl *Node::LookupType(char *name) {
    Decl *local = table.Lookup(name);
    if (local != NULL) {
        return local;
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
	    std::cout << cur->GetName() << std::endl;
            table.Enter(cur->GetName(), cur);
	}
    }
}
	 
Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
    name = strdup(n);
} 

