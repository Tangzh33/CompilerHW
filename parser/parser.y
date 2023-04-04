%code requires
{
class asgNode;
}
%{
#include "parser.hh"
#include <llvm/Support/JSON.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <iostream>
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
  // llvm::json::Array stak;
  asgNode* root;
} // namespace
auto yylex() {
  asgNode* test = new asgNode();
  delete test;
  auto tk = wk_getline();
  auto b = tk.find("'") + 1, e = tk.rfind("'");
  auto s = tk.substr(b, e - b).str(), t = tk.substr(0, tk.find(" ")).str();
  std::cout << "Testing  " << t << " " << s << std::endl;
  if (t == "numeric_constant") {
    auto value = s;
    auto kind = "IntegerLiteral";
    auto type = "int";
    if (s.find('.') != std::string::npos || s.find('p') != std::string::npos ||
    s.find('e') != std::string::npos) 
    {
      auto kind = "FloatingLiteral";
      llvm::StringRef str(value);
      llvm::APFloat apf(0.0);
      apf.convertFromString(str, llvm::APFloat::rmNearestTiesToEven);
      llvm::SmallString<16> Buffer;
      apf.toString(Buffer);
      value = Buffer.c_str();
      std::cout << "Number Testing  " << t << " " << value << std::endl;
      type = "float";
    }
    yylval = new asgNode(kind, "", value);
    yylval -> type = type;
    return T_NUMERIC_CONSTANT;
  }
  if (t == "identifier") {
    yylval = new asgNode("id", s);
    return T_IDENTIFIER;
  }
  if (t == "string_literal") {
    yylval = new asgNode("StringLiteral", s);
    return T_STRING_LITERAL;
  }
// %token T_NUMERIC_CONSTANT
// %token T_STRING_LITERAL
// %token T_IDENTIFIER
//   %token T_COMMA
  if (t == "comma") {
    return T_COMMA;
  }
// %token T_SEMI
  if (t == "semi") {
    return T_SEMI;
  }
// %token T_L_SQUARE
  if (t == "l_square") {
    return T_L_SQUARE;
  }
// %token T_R_SQUARE
  if (t == "r_square") {
    return T_R_SQUARE;
  }
// %token T_L_BRACE
  if (t == "l_brace") {
    return T_L_BRACE;
  }
// %token T_R_BRACE
  if (t == "r_brace") {
    return T_R_BRACE;
  }
// %token T_L_PAREN
  if (t == "l_paren") {
    return T_L_PAREN;
  }
// %token T_R_PAREN
  if (t == "r_paren") {
    return T_R_PAREN;
  }
// %token T_EQUAL
  if (t == "equal") {
    return T_EQUAL;
  }
// %token T_PLUS
  if (t == "plus") {
    return T_PLUS;
  }
// %token T_MINUS
  if (t == "minus") {
    return T_MINUS;
  }
// %token T_EXCLAIM // !
  if (t == "exclaim") {
    return T_EXCLAIM;
  }
// %token T_STAR
  if (t == "star") {
    return T_STAR;
  }
// %token T_SLASH
  if (t == "slash") {
    return T_SLASH;
  }
// %token T_PERCENT
  if (t == "percent") {
    return T_PERCENT;
  }
// %token T_LESS
  if (t == "less") {
    return T_LESS;
  }
// %token T_GREATER
  if (t == "greater") {
    return T_GREATER;
  }
// %token T_LESSEQUAL
  if (t == "lessequal") {
    return T_LESSEQUAL;
  }
// %token T_GREATEREQUAL
  if (t == "greaterequal") {
    return T_GREATEREQUAL;
  }
// %token T_EQUALEQUAL
  if (t == "equalequal") {
    return T_EQUALEQUAL;
  }
// %token T_EXCLAIMEQUAL // !=
  if (t == "exclaimequal") {
    return T_EXCLAIMEQUAL;
  }
// %token T_AMPAMP
  if (t == "ampamp") {
    return T_AMPAMP;
  }
// %token T_PIPEPIPE
  if (t == "pipepipe") {
    return T_PIPEPIPE;
  }
// %token T_INT
  if (t == "int") {
    return T_INT;
  }
// %token T_FLOAT
  if (t == "float") {
    return T_FLOAT;
  }
// %token T_CHAR
  if (t == "char") {
    return T_CHAR;
  }
// %token T_VOID
  if (t == "void") {
    return T_VOID;
  }
// %token T_CONST
  if (t == "const") {
    return T_CONST;
  }
// %token T_IF
  if (t == "if") {
    return T_IF;
  }
// %token T_ELSE
  if (t == "else") {
    return T_ELSE;
  }
// %token T_DO
  if (t == "do") {
    return T_DO;
  }
// %token T_WHILE
  if (t == "while") {
    return T_WHILE;
  }
// %token T_BREAK
  if (t == "break") {
    return T_BREAK;
  }
// %token T_CONTINUE
  if (t == "continue") {
    return T_CONTINUE;
  }
// %token T_RETURN
  if (t == "return") {
    return T_RETURN;
  }
  return YYEOF;
}
int main() {
  yyparse();
  root->print();
  llvm::outs() << root->toJson() << "\n";
  root->clear();
  delete root;
  return 0;
}
%}
/* Change the stack datatype */
%define api.value.type { asgNode* }

%token T_COMMA
%token T_SEMI
%token T_L_SQUARE
%token T_R_SQUARE
%token T_L_BRACE
%token T_R_BRACE
%token T_L_PAREN
%token T_R_PAREN
%token T_EQUAL
%token T_PLUS
%token T_MINUS
%token T_EXCLAIM // !
%token T_STAR
%token T_SLASH
%token T_PERCENT
%token T_LESS
%token T_GREATER
%token T_LESSEQUAL
%token T_GREATEREQUAL
%token T_EQUALEQUAL
%token T_EXCLAIMEQUAL // !=
%token T_AMPAMP
%token T_PIPEPIPE
%token T_INT
%token T_FLOAT
%token T_CHAR
%token T_VOID
%token T_CONST
%token T_IF
%token T_ELSE
%token T_DO
%token T_WHILE
%token T_BREAK
%token T_CONTINUE
%token T_RETURN
%token T_NUMERIC_CONSTANT
%token T_STRING_LITERAL
%token T_IDENTIFIER
%token T_LONG
%start Begin
%left T_COMMA
%left T_PIPEPIPE 
%left T_AMPAMP 
%left T_EQUALEQUAL T_EXCLAIMEQUAL
%left T_LESS T_GREATER T_LESSEQUAL T_GREATEREQUAL 
%left T_PLUS T_MINUS
%left T_STAR T_PERCENT T_SLASH
/* Unary-operators -, +, ! */
%right U_MINUS U_PLUS U_N
%%
/* Rules
CompUnit      ::= [CompUnit] (Decl | FuncDef);

Decl          ::= ConstDecl | VarDecl;
ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";";
BType         ::= "int" | "char" | "long long";
ConstDef      ::= IDENT {"[" ConstExp "]"} "=" ConstInitVal;
ConstInitVal  ::= ConstExp | "{" [ConstInitVal {"," ConstInitVal}] "}";
VarDecl       ::= BType VarDef {"," VarDef} ";";
VarDef        ::= IDENT {"[" ConstExp "]"}
                | IDENT {"[" ConstExp "]"} "=" InitVal;
InitVal       ::= Exp | "{" [InitVal {"," InitVal}] "}";

FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block;
FuncType      ::= "void" | "int";
FuncFParams   ::= FuncFParam {"," FuncFParam};
FuncFParam    ::= BType IDENT ["[" "]" {"[" ConstExp "]"}];

Block         ::= "{" {BlockItem} "}";
BlockItem     ::= Decl | Stmt;
Stmt          ::= LVal "=" Exp ";"
                | [Exp] ";"
                | Block
                | "if" "(" Exp ")" Stmt ["else" Stmt]
                | "while" "(" Exp ")" Stmt
                | "break" ";"
                | "continue" ";"
                | "return" [Exp] ";";
                | "do" "{" Stmt "}" "while" "(" Stmt ")" ";"

Exp           ::= LOrExp;
LVal          ::= IDENT {"[" Exp "]"};
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
Number        ::= INT_CONST;
UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp;
UnaryOp       ::= "+" | "-" | "!";
FuncRParams   ::= Exp {"," Exp};
MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;
RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp       ::= EqExp | LAndExp "&&" EqExp;
LOrExp        ::= LAndExp | LOrExp "||" LAndExp;
ConstExp      ::= Exp;
 */
/* CompUnit      ::= [CompUnit] (Decl | FuncDef); */
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

/* Decl          ::= ConstDecl | VarDecl; */
GlobalDecl: ConstDecl{
    $$ = $1;
  }
  | VarDecl {
    $$ = $1;
  }
  | FuncDef {
    $$= $1;
  }
	;

/* ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";"; */
/* Notice! augment!!! 
Test: const int d = 0, c = 0, b = 0;
*/
ConstDeclPrefix: T_CONST BType ConstDef {
    $3->type = $2->type;
    delete $2;
    $$ = $3;
  }
  | ConstDeclPrefix T_COMMA ConstDef {
    $$ = $1;
    $$->addSon($3);
  }
  ;
ConstDecl: ConstDeclPrefix T_SEMI {
    $1->kind = "VarDecl";
    $$ = $1;
  }
  ;

/* BType         ::= "int" | "char" | "long long"; */
BType: T_INT{
    $$ = new asgNode();
    $$->type = "int";
  }
  | T_CHAR {
    $$ = new asgNode();
    $$->type = "char";
  }
  | T_LONG {
    $$ = new asgNode();
    $$->type = "long";
  }
  | T_VOID {
    $$ = new asgNode();
    $$->type = "void";
  }
  | T_LONG T_LONG {
    $$ = new asgNode();
    $$->type = "long long";
  }
  | T_FLOAT {
    $$ = new asgNode();
    $$->type = "float";
  }
  ;

/* ConstDef      ::= IDENT {"[" ConstExp "]"} "=" ConstInitVal; */
ConstDef: T_IDENTIFIER {
    $$ = new asgNode();
    $$->name = $1->name;
  }
  | ConstDef T_L_BRACKET ConstExp T_R_BRACKET {
    $$ = $1;
  }
  | ConstDef T_EQUAL ConstInitVal {
    $$ = $1;
    $$->addSon($3);
  }
  ;

VarDecl: BType T_IDENTIFIER T_SEMI {
  $2->kind = "VarDecl";
  $2->type = $1->type;
  delete $1;
  $$ = $2;
}

FuncDef:BType T_IDENTIFIER T_L_PAREN T_R_PAREN Block {
    $2->kind = "FunctionDecl";
    $2->type = $1->type;
    delete $1;
    $2->addSon($5);
    $$ = $2;
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
%%