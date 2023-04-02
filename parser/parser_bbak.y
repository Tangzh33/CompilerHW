%code requires
{
class asgNode;
}
%{
#include "parser.hh"
#include <vector>
#include <memory>
#include <llvm/Support/JSON.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/APFloat.h>
#include "asg_Node.h"
#define yyerror(x)                                                             \
  do {                                                                         \
    llvm::errs() << (x);                                                       \
  } while (0)

namespace {
auto llvmin = llvm::MemoryBuffer::getFileOrSTDIN("-");
auto input = llvmin.get() -> getBuffer();
auto end = input.end(), it = input.begin();
auto wk_getline(char endline = "\n"[0]) {
  auto beg = it;
  while (it != end && *it != endline)
    ++it;
  auto len = it - beg;
  if (it != end && *it == endline)
    ++it;
  return llvm::StringRef(beg, len);
}
asgNode* root;
} // namespace
auto yylex() {
  auto tk = wk_getline();
  auto b = tk.find("'") + 1, e = tk.rfind("'");
  auto s = tk.substr(b, e - b).str(), t = tk.substr(0, tk.find(" ")).str();
  if (t == "numeric_constant") {
    yylval = new asgNode("IntegerLiteral", "", s);
    return T_NUMERIC_CONSTANT;
  }
  if (t == "identifier") {
    yylval = new asgNode("id", s);
    return T_IDENTIFIER;
  }
  if (t == "int")
    return T_INT;
  if (t == "return")
    return T_RETURN;
  if (t == "semi")
    return T_SEMI;
  if (t == "l_paren")
    return T_L_PAREN;
  if (t == "r_paren")
    return T_R_PAREN;
  if (t == "l_brace")
    return T_L_BRACE;
  if (t == "r_brace")
    return T_R_BRACE;
// TO-DO：你需要在这里补充更多的TOKEN
  return YYEOF;
}

int main() {
  yyparse();
  root->print();
  llvm::outs() << root->toJson() << "\n";
}
%}
%define api.value.type { asgNode* }

// TO-DO：你需要在这里补充更多的TOKEN
%token T_NUMERIC_CONSTANT
%token T_IDENTIFIER
%token T_INT
%token T_RETURN
%token T_SEMI
%token T_L_PAREN
%token T_R_PAREN
%token T_L_BRACE
%token T_R_BRACE
%start Begin
%%
Begin: CompUnit {
    root = $1;
  }
  ;

CompUnit: CompUnit GlobalDecl {
    $1->addSon($2);
    $$ = $1;
  }
  | GlobalDecl {
    auto ptr = new asgNode("TranslationUnitDecl");
    ptr->addSon($1);
    $$ = ptr;
  }
	;

GlobalDecl: FuncDef {
    $$ = $1;
  }
  | VarDecl {
    $$= $1;
  }
	;

VarDecl: T_INT T_IDENTIFIER T_SEMI {
  auto ptr = new asgNode("VarDecl", $2->name);
  delete $2;
  $$ = ptr;
}

FuncDef:T_INT T_IDENTIFIER T_L_PAREN T_R_PAREN Block {
    auto ptr = new asgNode("FunctionDecl", $2->name);
    delete $2;
    ptr->addSon($5);
    $$ = ptr;
  }
  ;
Block: T_L_BRACE Stmt T_R_BRACE {
    auto ptr = new asgNode("CompoundStmt");
    ptr->addSon($2);
    $$ = ptr;
  }
  ;

Stmt: T_RETURN T_NUMERIC_CONSTANT T_SEMI {
    auto ptr = new asgNode("ReturnStmt");
    ptr->addSon($2);
    $$ = ptr;
  }
  | T_SEMI {
    $$ = new asgNode("NullStmt");
  }
  ;
// TO-DO：你需要在这里实现文法和树，通过测例
%%