/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp5: You will need to extend the Decl classes to implement
 * code generation for declarations.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "list.h"

class Type;
class NamedType;
class Identifier;
class Stmt;

class Decl : public Node 
{
  protected:
    Identifier *id;
  
  public:
    Decl(Identifier *name);
    friend std::ostream& operator<<(std::ostream& out, Decl *d) { return out << d->id; }
    Identifier *GetId() { return id; }
    char *GetName() { return id->GetName(); }
    void CheckNode();
    virtual bool IsEquivalentTo(Decl* other) {
        return strcmp(other->id->GetName(), this->id->GetName()) == 0;
    }
};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);
    void CheckNode();
    Type *GetType() { return type; }
    bool IsEquivalentTo(Decl* other);
};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;

  public:
    NamedType *extends;
    List<NamedType*> *implements;

    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
    void CheckNode();
    bool IsEquivalentTo(Decl *o);
    Type *GetType();
    Decl *LookupType(char *name, bool recursive=true);
};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    List<Decl*> *GetMembers() { return members; }
    void CheckNode();
    bool IsEquivalentTo(Decl *o);
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    void CheckNode();
    bool IsEquivalentTo(Decl* other);
    List<VarDecl*> *GetFormals() { return formals; }
    Type *GetType() { return returnType; }
    void Emit();
};

#endif
