/*
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

#pragma once
#ifndef __TANGZ_ASG_H_
#define __TANGZ_ASG_H_

#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

struct Obj {
  virtual ~Obj() = default;
};
struct Decl : public Obj { // 表达一个符号声明（变量、参数等）
  std::string name; // 符号名
  std::string type; // 符号类型
};
struct Expr : public Obj {
  std::string type; // C语言的每个表达式都有类型
};
struct Rvalue : public Expr {
  std::string val; // 右值
}; 
struct DeclRefExpr : public Expr {
  Decl* decl; // 指向引用的声明
};
struct BinaryExpr : public Expr {
  enum { kAdd, kSub, kMul, kDiv, kMod, kLEq, kLAnd, kLOr} op; // 操作符
  int opNum; // 操作数个数
  Expr *lft, *rht; // 指向左右操作数
};
struct UnaryExpr : public Expr {
  enum { kPos, kNeg, kLNot } op; // 操作符
  Expr *sub; // 指向子表达式
};

#ifdef __cplusplus
}
#endif

#endif
