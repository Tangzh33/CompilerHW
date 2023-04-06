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
  // Build symbol table for identifiers
  std::map<std::string, asgNode*> idenTable;
} // namespace
auto yylex() {
  asgNode* test = new asgNode();
  delete test;
  auto tk = wk_getline();
  auto b = tk.find("'") + 1, e = tk.rfind("'");
  auto s = tk.substr(b, e - b).str(), t = tk.substr(0, tk.find(" ")).str();
  // std::cout << "Testing  " << t << " " << s << std::endl;
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
    if(idenTable.find(s) != idenTable.end())
      yylval -> type = idenTable[s] -> type;
    return T_IDENTIFIER;
  }
  if (t == "string_literal") {
    yylval = new asgNode("StringLiteral", "", s);
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
  // root->print();
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
    $$ = $1;
    if ($2->kind == "VarDeclPreNode") {
        // for(auto son : $2->sons) {
        //     $$->addSon(son);
        // }
        for (auto&& it: $2 -> sons) {
            $$ -> addSon(std::move(it));
        }
        delete $2;
    }
    else {
      $$->addSon($2);
    }
  }
  | GlobalDecl {
    $$ = new asgNode("TranslationUnitDecl");
    if ($1->kind == "VarDeclPreNode") {
    //   for(auto son : $2->sons) {
    //     $$->addSon(son);
    //   }
        for (auto&& it: $1 -> sons) {
            $$ -> addSon(std::move(it));
        }
      delete $1;
    }
    else {
      $$->addSon($1);
    }
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
    $$ = new asgNode();
    $$->kind = "VarDeclPreNode";
    $$->type = $2->type;
    delete $2;
    $3->type = $$->type + $3->type;
    $3->kind = "VarDecl";
    idenTable[$3->name] = $3;
    $$->addSon($2);
  }
  | ConstDeclPrefix T_COMMA ConstDef {
    $$ = $1;
    $3->type = $$->type + $3->type;
    $3->kind = "VarDecl";
    idenTable[$3->name] = $3;
    $$->addSon($3);
  }
  ;
ConstDecl: ConstDeclPrefix T_SEMI {
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
    $$ = $1;
    $$->type = "const " + $$->type; 
  }
  | ConstDef T_L_SQUARE ConstExp T_R_SQUARE {
    $$ = $1;
    $$->type = $$->type + " [" + $3->value + "]";
    // Todo: Cal Value of ConstExp 
  }
  | ConstDef T_EQUAL ConstInitVal {
    $$ = $1;
    $$->addSon($3);
  }
  ;

/* ConstInitVal  ::= ConstExp | "{" [ConstInitVal {"," ConstInitVal}] "}"; */
/* Todo Check */
ConstInitValPrefix: T_L_BRACE ConstInitVal {
    $$ = $2;
  }
  | ConstInitValPrefix T_COMMA ConstInitVal {
    $$ = $1;
    $$->addSon($3);
  }

ConstInitVal: ConstExp {
    $$ = new asgNode("InitListExpr");
    $$->addSon($1);
  }
  | T_L_BRACE T_R_BRACE {
    $$ = new asgNode("InitListExpr");
  }
  | ConstInitValPrefix T_R_BRACE {
    $$ = new asgNode("InitListExpr");
    $$->addSon($1);
  }
/* ConstInitVal: ConstExp {
    $$ = $1;
    $1->kind = "InitListExpr";
    // Todo: Cal Value of ConstExp 
  }
  | T_L_BRACE ConstInitValList T_R_BRACE {
    $$ = $2;
    $1->addSon($2);
  }
  ;
ConstInitValList: ConstInitVal {
    $$ = $1;
  }
  | ConstInitValList T_COMMA ConstInitVal {
    $$ = $1;
    $$->addSon($3);
  }
  ; */


/* VarDecl       ::= BType VarDef {"," VarDef} ";"; */
VarDeclPrefix: BType VarDef {
    $$ = new asgNode();
    $$->kind = "VarDeclPreNode";
    $$->type = $1->type;
    delete $1;
    $2->type = $$->type + $2->type;
    $2->kind = "VarDecl";
    idenTable[$2->name] = $2;
    $$->addSon($2);
  }
  | VarDeclPrefix T_COMMA VarDef {
    $$ = $1;
    $3->type = $$->type + $3->type;
    $3->kind = "VarDecl";
    idenTable[$3->name] = $3;
    $$->addSon($3);
  }
  ;
VarDecl: VarDeclPrefix T_SEMI {
    $$ = $1;
  }
/* 
VarDecl: BType T_IDENTIFIER T_SEMI {
  $2->kind = "VarDecl";
  $2->type = $1->type;
  delete $1;
  $$ = $2;
} */

/* VarDef        ::= IDENT {"[" ConstExp "]"}
                | IDENT {"[" ConstExp "]"} "=" InitVal; */
VarDef: T_IDENTIFIER {
    $$ = $1;
  }
  | VarDef T_L_SQUARE ConstExp T_R_SQUARE {
    $$ = $1;
    $$->type = $$->type + " [" + $3->value + "]";
  }
  | VarDef T_EQUAL InitVal {
    $$ = $1;
    $$->addSon($3);
  }

/* InitVal       ::= Exp | "{" [InitVal {"," InitVal}] "}"; */
// Todo: Merge with ConstInitVal
InitValPrefix: T_L_BRACE InitVal {
    $$ = $2;
  }
  | InitValPrefix T_COMMA InitVal {
    $$ = $1;
    $$->addSon($3);
  }

InitVal: Exp {
    $$ = new asgNode("InitListExpr");
    $$->addSon($1);
  }
  | T_L_BRACE T_R_BRACE {
    $$ = new asgNode("InitListExpr");
  }
  | InitValPrefix T_R_BRACE {
    $$ = new asgNode("InitListExpr");
    $$->addSon($1);
  }
/* InitVal: Exp {
    $$ = $1;
    $1->kind = "InitListExpr";
  }
  | T_L_BRACE InitValList T_R_BRACE {
    $$ = $2;
    $1->addSon($2);
  }
  ;
InitValList: InitVal {
    $$ = $1;
  }
  | InitValList T_COMMA InitVal {
    $$ = $1;
    $$->addSon($3);
  } */

/* FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block; */
/* Warning: Using Btype instead of FuncType */
FuncDef: BType T_IDENTIFIER T_L_PAREN FuncFParams T_R_PAREN Block {
    $2->kind = "FunctionDecl";
    $2->type = $1->type + "(" + $4->type + ")";
    delete $1;
    $2->addSon($4);
    $2->addSon($6);
    // Push the FuncDef to the symbol table
    idenTable[$2->name] = $2;
    $$ = $2;
  }
  | BType T_IDENTIFIER T_L_PAREN T_R_PAREN Block {
    $2->kind = "FunctionDecl";
    $2->type = $1->type + "()";
    delete $1;
    $2->addSon($5);
    // Push the FuncDef to the symbol table
    idenTable[$2->name] = $2;
    $$ = $2;
  }
  ;

/* FuncDef:BType T_IDENTIFIER T_L_PAREN T_R_PAREN Block {
    $2->kind = "FunctionDecl";
    $2->type = $1->type;
    delete $1;
    $2->addSon($5);
    $$ = $2;
  }
  ; */

/* FuncType      ::= "void" | "int"; */
/* FuncType: T_VOID {
    $$ = new asgNode();
    $$->type = "void";
  }
  | T_INT {
    $$ = new asgNode();
    $$->type = "int";
  } */

/* FuncFParams   ::= FuncFParam {"," FuncFParam}; */
FuncFParams: FuncFParam {
    $$ = $1;
  }
  | FuncFParams T_COMMA FuncFParam {
    $$ = $1;
    $$->addSon($3);
    $$->type = $$->type + ", " + $3->type;
  }
  ;

/* FuncFParam    ::= BType IDENT ["[" "]" {"[" ConstExp "]"}]; */
FuncFParam: BType T_IDENTIFIER {
    $$ = $2;
    $$->type = $1->type;
    delete $1;
  }
  | BType T_IDENTIFIER FuncFParamSuffix {
    $$ = $2;
    $$->type = $1->type + $3->type;
    delete $1;
    $$->addSon($3);
  }
  
FuncFParamSuffix: T_L_SQUARE T_R_SQUARE {
    $$ = $1;
    $$->type = $$->type + " (*)";
  }
  | FuncFParamSuffix T_L_SQUARE ConstExp T_R_SQUARE {
    $$ = $1;
    $$->type = $$->type + "[" + $3->value + "]";
  }

/* Block         ::= "{" {BlockItem} "}"; */
BlockPrefix: T_L_BRACE BlockItem{
    $$ = new asgNode("CompoundStmt");
    $$->addSon($2);
  }
  | BlockPrefix BlockItem {
    $$ = $1;
    $$->addSon($2);
  }
  ;
Block: BlockPrefix T_R_BRACE {
    $$ = $1;
    $$->kind = "CompoundStmt";
  }
  | T_L_BRACE T_R_BRACE {
    auto ptr = new asgNode("CompoundStmt");
    $$ = ptr;
  }
  ;
/* Block: T_L_BRACE BlockItemList T_R_BRACE {
    auto ptr = new asgNode("CompoundStmt");
    ptr->addSon($2);
    $$ = ptr;
  }
  | T_L_BRACE T_R_BRACE {
    auto ptr = new asgNode("CompoundStmt");
    $$ = ptr;
  }
  ;

BlockItemList: BlockItem {
    $$ = $1;
  }
  | BlockItemList BlockItem {
    $$ = $1;
    $$->addSon($2);
  } */

/* Block: T_L_BRACE Stmt T_R_BRACE {
    auto ptr = new asgNode("CompoundStmt");
    ptr->addSon($2);
    $$ = ptr;
  }
  ; */
/* BlockItem     ::= Decl | Stmt; */
BlockItem: ConstDecl {
    $$ = new asgNode("DeclStmt");
    $$->addSon($1);
  }
  | VarDecl {
    $$ = new asgNode("DeclStmt");
    $$->addSon($1);
  }
  | Stmt {
    $$ = $1;
  }
  ;

  
/* Stmt          ::= LVal "=" Exp ";"
                | [Exp] ";"
                | Block
                | "if" "(" Exp ")" Stmt ["else" Stmt]
                | "while" "(" Exp ")" Stmt
                | "break" ";"
                | "continue" ";"
                | "return" [Exp] ";";
                | "do" "{" Stmt "}" "while" "(" Stmt ")" ";" */
/* Todo: Need to Re-check carefully */
/* Todo:  solve dangling else
  http://www.cs.man.ac.uk/~pjj/cs212/ho/node7.html#SECTION00074000000000000000*/
Stmt: LVal T_EQUAL Exp T_SEMI {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "=";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | Exp T_SEMI {
    $$ = $1;
  }
  | T_SEMI {
    $$ = new asgNode("NullStmt");
  }
  | Block {
    $$ = $1;
  }
  | T_IF T_L_PAREN Exp T_R_PAREN Stmt {
    auto ptr = new asgNode("IfStmt");
    ptr->addSon($3);
    ptr->addSon($5);
    $$ = ptr;
  }
  | T_IF T_L_PAREN Exp T_R_PAREN Stmt T_ELSE Stmt {
    auto ptr = new asgNode("IfStmt");
    ptr->addSon($3);
    ptr->addSon($5);
    ptr->addSon($7);
    $$ = ptr;
  }
  | T_WHILE T_L_PAREN Exp T_R_PAREN Stmt {
    auto ptr = new asgNode("WhileStmt");
    ptr->addSon($3);
    ptr->addSon($5);
    $$ = ptr;
  }
  | T_BREAK T_SEMI {
    $$ = new asgNode("BreakStmt");
  }
  | T_CONTINUE T_SEMI {
    $$ = new asgNode("ContinueStmt");
  }
  | T_RETURN T_SEMI {
    $$ = new asgNode("ReturnStmt");
  }
  | T_RETURN Exp T_SEMI {
    auto ptr = new asgNode("ReturnStmt");
    ptr->addSon($2);
    $$ = ptr;
  }
  | T_DO T_L_BRACE Stmt T_R_BRACE T_WHILE T_L_PAREN Exp T_R_PAREN T_SEMI {
    auto ptr = new asgNode("DoStmt");
    ptr->addSon($3);
    ptr->addSon($7);
    $$ = ptr;
  }

/* Stmt: T_RETURN T_NUMERIC_CONSTANT T_SEMI {
    auto ptr = new asgNode("ReturnStmt");
    ptr->addSon($2);
    $$ = ptr;
  }
  | T_SEMI {
    $$ = new asgNode("NullStmt");
  }
  ; */

/* Exp           ::= LOrExp; */
Exp: LOrExp {
    $$ = $1;
  }
  ;
/* LVal          ::= IDENT {"[" Exp "]"}; */
LVal: T_IDENTIFIER {
    $$ = new asgNode("DeclRefExpr");
    $$ -> addSon($1);
  }
  | LVal T_L_SQUARE Exp T_R_SQUARE {
    auto ptr = new asgNode("ArraySubscriptExpr");
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  ;
/* Todo: Implicit Cast */

/* PrimaryExp    ::= "(" Exp ")" | LVal | Number; */
PrimaryExp: T_L_PAREN Exp T_R_PAREN {
    $$ = $2;
  }
  | LVal {
    $$ = $1;
  }
  | Number {
    $$ = $1;
  }
  ;

/* Number        ::= INT_CONST; */
/* Todo: Need to be int constant? */
Number: T_NUMERIC_CONSTANT {
    $$ = $1;
    $$->kind = "IntegerLiteral";
  }
  ;


/* UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp; */

UnaryExp: PrimaryExp {
    $$ = $1;
  }
  | T_IDENTIFIER T_L_PAREN FuncRParams T_R_PAREN {
    auto ptr = new asgNode("CallExpr");
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | T_IDENTIFIER T_L_PAREN T_R_PAREN {
    auto ptr = new asgNode("CallExpr");
    ptr->addSon($1);
    $$ = ptr;
  }
  | UnaryOp UnaryExp {
    $$ = $1;
    $1->addSon($2);
  }
  ;

/* UnaryOp       ::= "+" | "-" | "!"; */
UnaryOp: T_PLUS {
    $$ = new asgNode("UnaryOperator");
    $$->opcode = "+";
  }
  | T_MINUS {
    $$ = new asgNode("UnaryOperator");
    $$->opcode = "-";
  }
  | T_EXCLAIM {
    $$ = new asgNode("UnaryOperator");
    $$->opcode = "!";
  }
  ;
  
/* FuncRParams   ::= Exp {"," Exp}; */
FuncRParams: Exp {
    $$ = $1;
  }
  | FuncRParams T_COMMA Exp {
    $$ = $1;
    $$->addSon($3);
  }
  ;
/* MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp; */
MulExp: UnaryExp {
    $$ = $1;
  }
  | MulExp T_STAR UnaryExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "*";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | MulExp T_SLASH UnaryExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "/";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | MulExp T_PERCENT UnaryExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "%";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  ;

/* AddExp        ::= MulExp | AddExp ("+" | "-") MulExp; */
AddExp: MulExp {
    $$ = $1;
  }
  | AddExp T_PLUS MulExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "+";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | AddExp T_MINUS MulExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "-";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  ;
/* RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp; */
RelExp: AddExp {
    $$ = $1;
  }
  | RelExp T_LESS AddExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "<";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | RelExp T_GREATER AddExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = ">";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | RelExp T_LESSEQUAL AddExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "<=";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | RelExp T_GREATEREQUAL AddExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = ">=";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  ;

/* EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp; */
EqExp: RelExp {
    $$ = $1;
  }
  | EqExp T_EQUAL RelExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "==";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  | EqExp T_EXCLAIMEQUAL RelExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "!=";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  ;

/* LAndExp       ::= EqExp | LAndExp "&&" EqExp; */
LAndExp: EqExp {
    $$ = $1;
  }
  | LAndExp T_AMPAMP EqExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "&&";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  ;

/* LOrExp        ::= LAndExp | LOrExp "||" LAndExp; */
LOrExp: LAndExp {
    $$ = $1;
  }
  | LOrExp T_PIPEPIPE LAndExp {
    auto ptr = new asgNode("BinaryOperator");
    ptr->opcode = "||";
    ptr->addSon($1);
    ptr->addSon($3);
    $$ = ptr;
  }
  ;

/* ConstExp      ::= Exp; */
ConstExp: Exp {
    $$ = $1;
  }
  ;
%%