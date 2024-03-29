#pragma once
#include <llvm-11/llvm/IR/DerivedTypes.h>
#include <llvm-11/llvm/IR/Instructions.h>
#include <llvm-11/llvm/IR/Value.h>

#include <cstdio>

#ifndef __TANGZ_AST_NODE_H_
#define __TANGZ_AST_NODE_H_
// Use std::move to avoid uncessary copy.

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/JSON.h>

#include <utility>

#include "llvm/IR/BasicBlock.h"

namespace tz_ast_type {
enum ExprCatgry { lvalue, rvalue };
enum StmtCatgry {
  While,
  Do,
  Continue,
  Compound,
  Break,
  If,
  Exp,
  Assign,
  Return,
  Null,
  Decl,
};
enum CastCatgry {
  IntegralCast,
  FloatingCast,
  LValueToRValue,
  IntegralToFloat,
  FloatToIntegral,
  FunctionToPointerDecay,
  ArrayToPointerDecay,
  BitCast,
  NoOp,
};
enum BinaryOpCatgry {
  Add,
  Sub,
  Mul,
  Div,
  Mod,
  Less,
  LessEq,
  Greater,
  GreaterEq,
  Eq,
  EqEq,
  ExclaimEq,
  AmpAmp,
  PipePipe,
};
enum UnaryOpCatgry { U_FindAddr, U_Deref, U_Plus, U_Minus, U_N, U_Tilde };

}  // namespace tz_ast_type

namespace tz_ast_class {
// Use obj to point to all of the AST nodes.
class Object {
 public:
  Object() = default;
  //  declare the AST node by default
  virtual ~Object() = default;
  // emit the IR code for specific type.
  virtual llvm::BasicBlock *emit(llvm::Module &TheModule,
                                 llvm::LLVMContext &llvm_context,
                                 llvm::BasicBlock *PrevBB,
                                 llvm::Value **ReturnValue) {
    assert("Emit Failure, In Object!" && false);
  };
  // print the AST node
  virtual void print() { printf("Object\n"); };
};

class Decl : public Object {
 public:
  std::string name;
  llvm::Type *type;
  Decl() = default;
  Decl(std::string name, llvm::Type *type)
      : name(std::move(name)), type(type) {}
  virtual llvm::BasicBlock *emit(llvm::Module &TheModule,
                                 llvm::LLVMContext &llvm_context,
                                 llvm::BasicBlock *PrevBB,
                                 llvm::Value **ReturnValue) {
    assert("Emit Failure, In Decl!" && false);
  }
  virtual void print() { printf("Decl\n name: %s\n", name.c_str()); };
};

class Stmt : public Object {
 public:
  Stmt() = default;
  tz_ast_type::StmtCatgry StmtCatgry;
  explicit Stmt(tz_ast_type::StmtCatgry StmtCatgry) : StmtCatgry(StmtCatgry) {}
  virtual llvm::BasicBlock *emit(llvm::Module &TheModule,
                                 llvm::LLVMContext &llvm_context,
                                 llvm::BasicBlock *PrevBB,
                                 llvm::Value **ReturnValue) {
    assert("Emit Failure, In Stmt!" && false);
  };
  virtual void print() { printf("Stmt\n StmtCatgry: %d\n", StmtCatgry); };
};

class Expr : public Object {
 public:
  llvm::Type *type;
  llvm::Value *value;
  tz_ast_type::ExprCatgry ExprCatgry;
  Expr() = default;
  Expr(llvm::Type *type, llvm::Value *value, tz_ast_type::ExprCatgry ExprCatgry)
      : type(type), value(value), ExprCatgry(ExprCatgry) {}
};

/********************************
 *  Expr
 *  Literal: IntegerLiteral, FloatingLiteral, StringLiteral
 *  BinaryExpr
 *  UnaryExpr
 *  CallExpr
 *  DeclRefExpr
 *  ImplicitCastExpr
 *  InitListExpr
 *  ArraySubscriptExpr
 ********************************/

class IntegerLiteral : public Expr {
 public:
  IntegerLiteral() = default;
  IntegerLiteral(llvm::Type *type, llvm::Constant *value)
      : Expr(type, value, tz_ast_type::ExprCatgry::rvalue) {}
  IntegerLiteral(llvm::LLVMContext &llvm_context,
                 const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override { printf("IntegerLiteral\n"); };
};

class FloatingLiteral : public Expr {
 public:
  FloatingLiteral() = default;
  FloatingLiteral(llvm::Type *type, llvm::Constant *value)
      : Expr(type, value, tz_ast_type::ExprCatgry::rvalue) {}
  FloatingLiteral(llvm::LLVMContext &llvm_context,
                  const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override { printf("FloatingLiteral\n"); };
};

class StringLiteral : public Expr {
 public:
  StringLiteral() = default;
  StringLiteral(llvm::Type *type, llvm::Constant *value)
      : Expr(type, value, tz_ast_type::ExprCatgry::rvalue) {}
  StringLiteral(llvm::LLVMContext &llvm_context,
                const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override { printf("StringLiteral\n"); };
};

class BinaryExpr : public Expr {
 public:
  tz_ast_type::BinaryOpCatgry op;
  Expr *lhs;
  Expr *rhs;
  BinaryExpr() = default;
  BinaryExpr(llvm::Type *type, tz_ast_type::ExprCatgry ExprCatgry,
             tz_ast_type::BinaryOpCatgry op, Expr *lhs, Expr *rhs)
      : Expr(type, nullptr, ExprCatgry), op(op), lhs(lhs), rhs(rhs) {}
  BinaryExpr(llvm::LLVMContext &llvm_context,
             const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("BinaryExpr, op: %d, lhs: ", op);
    lhs->print();
    printf("rhs: ");
    rhs->print();
    printf("Finish BinaryExpr\n");
  };
};

class UnaryExpr : public Expr {
 public:
  tz_ast_type::UnaryOpCatgry op;
  Expr *rhs;
  UnaryExpr() = default;
  UnaryExpr(llvm::Type *type, tz_ast_type::ExprCatgry ExprCatgry,
            tz_ast_type::UnaryOpCatgry op, Expr *rhs)
      : Expr(type, nullptr, ExprCatgry), op(op), rhs(rhs) {}
  UnaryExpr(llvm::LLVMContext &llvm_context,
            const llvm::json::Object *json_tree);

  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("UnaryExpr, op: %d, rhs: ", op);
    rhs->print();
    printf("Finish UnaryExpr\n");
  };
};

class DeclRefExpr : public Expr {
 public:
  Decl *DeclRefee;
  DeclRefExpr() = default;
  DeclRefExpr(llvm::Type *type, Decl *DeclRefee)
      : Expr(type, nullptr, tz_ast_type::ExprCatgry::lvalue),
        DeclRefee(DeclRefee) {}
  DeclRefExpr(llvm::LLVMContext &llvm_context,
              const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("DeclRefExpr, DeclRefee:");
    DeclRefee->print();
  };
};

class ImplicitCastExpr : public Expr {
 public:
  Expr *castExpr;
  tz_ast_type::CastCatgry CastCatgry;
  ImplicitCastExpr() = default;
  ImplicitCastExpr(llvm::Type *type, tz_ast_type::ExprCatgry ExprCatgry,
                   tz_ast_type::CastCatgry CastCatgry, Expr *castExpr)
      : Expr(type, nullptr, ExprCatgry),
        CastCatgry(CastCatgry),
        castExpr(castExpr) {}
  ImplicitCastExpr(llvm::LLVMContext &llvm_context,
                   const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("ImplicitCastExpr, CastCatgry: %d,", CastCatgry);
    castExpr->print();
  };
};

class InitListExpr : public Expr {
 public:
  bool isInited;
  // Dynamic adjust the Initlist of the function.
  std::vector<Expr *> initExprs;
  InitListExpr() = default;
  InitListExpr(llvm::Type *type, bool isInited, std::vector<Expr *> initExprs)
      : Expr(type, nullptr, tz_ast_type::ExprCatgry::rvalue),
        isInited(isInited),
        initExprs(std::move(initExprs)) {}
  InitListExpr(llvm::LLVMContext &llvm_context,
               const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("InitListExpr, isInited: %d, initExprs: ", isInited);
    for (auto &initExpr : initExprs) {
      initExpr->print();
    }
    printf("Finish InitListExpr\n");
  };
};

class ArraySubscriptExpr : public Expr {
 public:
  Expr *ArrayBase;
  Expr *ArrayIdx;
  ArraySubscriptExpr() = default;
  ArraySubscriptExpr(llvm::Type *type, Expr *ArrayBase, Expr *ArrayIdx)
      : Expr(type, nullptr, tz_ast_type::ExprCatgry::lvalue),
        ArrayBase(ArrayBase),
        ArrayIdx(ArrayIdx) {}
  ArraySubscriptExpr(llvm::LLVMContext &llvm_context,
                     const llvm::json::Object *json_tree);

  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("ArraySubscriptExpr, ArrayBase: ");
    ArrayBase->print();
    printf("ArrayIdx: ");
    ArrayIdx->print();
    printf("Finish ArraySubscriptExpr\n");
  };
};

class CallExpr : public Expr {
 public:
  Expr *callee;
  std::vector<Expr *> CalleeArgs;
  CallExpr() = default;
  CallExpr(llvm::Type *type, Expr *callee, std::vector<Expr *> CalleeArgs)
      : Expr(type, nullptr, tz_ast_type::ExprCatgry::rvalue),
        callee(callee),
        CalleeArgs(std::move(CalleeArgs)) {}
  CallExpr(llvm::LLVMContext &llvm_context,
           const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("CallExpr, callee: ");
    callee->print();
    printf("CalleeArgs: ");
    for (auto &CalleeArg : CalleeArgs) {
      CalleeArg->print();
    }
    printf("Finish CallExpr\n");
  };
};

class ParenExpr : public Expr {
 public:
  Expr *inParenExpr;
  ParenExpr() = default;
  explicit ParenExpr(Expr *inParenExpr)
      : Expr(inParenExpr->type, nullptr, inParenExpr->ExprCatgry),
        inParenExpr(inParenExpr) {}
  ParenExpr(llvm::LLVMContext &llvm_context,
            const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("ParenExpr, inParenExpr: ");
    inParenExpr->print();
    printf("Finish ParenExpr\n");
  };
};

/********************************
 *  Decl
 *  TranslationUnitDecl
 *  VarDecl
 *  ParmVarDecl
 *  FunctionDecl
 ********************************/
class TranslationUnitDecl : public Decl {
 public:
  std::vector<Decl *> Decls;
  TranslationUnitDecl() = default;
  explicit TranslationUnitDecl(std::vector<Decl *> Decls)
      : Decl("TranslationUnit", nullptr), Decls(std::move(Decls)) {}
  TranslationUnitDecl(llvm::LLVMContext &llvm_context,
                      const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("TranslationUnitDecl, Decls: ");
    for (auto &Decl : Decls) {
      Decl->print();
    }
    printf("Finish TranslationUnitDecl\n");
  };
};

class VarDecl : public Decl {
 public:
  bool isInited;
  bool isConst;
  // By default, the var is not global.
  bool isGlobal;
  Expr *InitExpr;
  VarDecl() = default;
  VarDecl(std::string name, llvm::Type *type, bool isConst, bool isInited,
          bool isGlobal, Expr *InitExpr)
      : Decl(std::move(name), type),
        isConst(isConst),
        isInited(isInited),
        isGlobal(isGlobal),
        InitExpr(InitExpr) {}
  VarDecl(llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree,
          const bool _isGlobal = false);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf(
        "VarDecl, Name: %s, isConst: %d, isInited: %d, isGlobal: %d, "
        "InitExpr: ",
        name.c_str(), isConst, isInited, isGlobal);
    if (isInited) {
      InitExpr->print();
    }
    printf("Finish VarDecl\n");
  };
};

class ParmVarDecl : public VarDecl {
 public:
  ParmVarDecl() = default;
  ParmVarDecl(std::string name, llvm::Type *type, bool isConst, bool isInited,
              bool isGlobal, Expr *InitExpr)
      : VarDecl(std::move(name), type, isConst, isInited, isGlobal, InitExpr) {}
  ParmVarDecl(llvm::LLVMContext &llvm_context,
              const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf(
        "ParmVarDecl, Name: %s, isConst: %d, isInited: %d, isGlobal:%d, "
        "InitExpr: ",
        name.c_str(), isConst, isInited, isGlobal);
    if (isInited) {
      InitExpr->print();
    }
    printf("Finish ParmVarDecl\n");
  };
};

class FunctionDecl : public Decl {
 public:
  bool isVariadic;
  bool isExternal;
  bool isConst;
  Stmt *FuncStmt;
  llvm::Type *ReturnType;
  std::vector<Decl *> params;
  FunctionDecl() = default;
  FunctionDecl(std::string name, llvm::Type *type, llvm::Type *ReturnType,
               std::vector<Decl *> params, bool isVariadic, bool isExternal,
               bool isConst)
      : Decl(std::move(name), type),
        ReturnType(ReturnType),
        params(std::move(params)),
        isVariadic(isVariadic),
        isExternal(isExternal),
        isConst(isConst) {}
  FunctionDecl(llvm::LLVMContext &llvm_context,
               const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("FunctionDecl, params[%zu]: ", params.size());
    for (auto &param : params) {
      param->print();
    }
    printf("isVariadic: %d, isExternal: %d, FuncStmt: ", isVariadic,
           isExternal);
    FuncStmt->print();
    printf("Finish FunctionDecl\n");
  };
};

/********************************
 *  Stmt
 *  CompoundStmt
 *  ReturnStmt
 *  IfStmt
 *  WhileStmt
 *  DoStmt
 *  NullStmt
 *  BreakStmt
 *  ContinueStmt
 *  DeclStmt
 ********************************/

class CompoundStmt : public Stmt {
 public:
  std::vector<Object *> InnerStmts;
  CompoundStmt() = default;
  explicit CompoundStmt(std::vector<Object *> InnerStmts)
      : Stmt(tz_ast_type::Compound), InnerStmts(std::move(InnerStmts)) {}
  CompoundStmt(llvm::LLVMContext &llvm_context,
               const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("CompoundStmt, InnerStmts: ");
    for (auto &InnerStmt : InnerStmts) {
      InnerStmt->print();
    }
    printf("Finish CompoundStmt\n");
  };
};

class ReturnStmt : public Stmt {
 public:
  Expr *ReturnExpr;
  ReturnStmt() = default;
  explicit ReturnStmt(Expr *ReturnExpr)
      : Stmt(tz_ast_type::Return), ReturnExpr(ReturnExpr) {}
  ReturnStmt(llvm::LLVMContext &llvm_context,
             const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("ReturnStmt, ReturnExpr: ");
    ReturnExpr->print();
    printf("Finish ReturnStmt\n");
  };
};

class IfStmt : public Stmt {
 public:
  Expr *IfCondExpr;
  Object *ThenObj;
  bool hasElse;
  Object *ElseObj;
  IfStmt() = default;
  IfStmt(Expr *IfCondExpr, Object *ThenObj, Object *ElseObj)
      : Stmt(tz_ast_type::If),
        hasElse(ElseObj != nullptr),
        IfCondExpr(IfCondExpr),
        ThenObj(ThenObj),
        ElseObj(ElseObj) {}
  IfStmt(llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("IfStmt, IfCondExpr: ");
    IfCondExpr->print();
    printf("ThenObj: ");
    ThenObj->print();
    if (hasElse) {
      printf("ElseObj: ");
      ElseObj->print();
    }
    printf("Finish IfStmt\n");
  };
};

class WhileStmt : public Stmt {
 public:
  Expr *WhileCondExpr;
  Object *WhileObj;
  WhileStmt() = default;
  WhileStmt(Expr *WhileCondExpr, Object *WhileObj)
      : Stmt(tz_ast_type::While),
        WhileCondExpr(WhileCondExpr),
        WhileObj(WhileObj) {}
  WhileStmt(llvm::LLVMContext &llvm_context,
            const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("WhileStmt, WhileCondExpr: ");
    WhileCondExpr->print();
    printf("WhileObj: ");
    WhileObj->print();
    printf("Finish WhileStmt\n");
  };
};

class DoStmt : public Stmt {
 public:
  Expr *DoCondExpr;
  Stmt *DoObj;
  DoStmt() = default;
  DoStmt(Expr *DoCondExpr, Stmt *DoObj)
      : Stmt(tz_ast_type::Do), DoCondExpr(DoCondExpr), DoObj(DoObj) {}
  DoStmt(llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("DoStmt, DoCondExpr: ");
    DoCondExpr->print();
    printf("DoObj: ");
    DoObj->print();
    printf("Finish DoStmt\n");
  };
};

class NullStmt : public Stmt {
 public:
  NullStmt() : Stmt(tz_ast_type::Null) {}
  NullStmt(llvm::LLVMContext &llvm_context,
           const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override { printf("NullStmt\n"); };
};

class BreakStmt : public Stmt {
 public:
  BreakStmt() : Stmt(tz_ast_type::Break) {}
  BreakStmt(llvm::LLVMContext &llvm_context,
            const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override { printf("BreakStmt\n"); };
};

class ContinueStmt : public Stmt {
 public:
  ContinueStmt() : Stmt(tz_ast_type::Continue) {}
  ContinueStmt(llvm::LLVMContext &llvm_context,
               const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override { printf("ContinueStmt\n"); };
};

class DeclStmt : public Stmt {
  // In funciton Declaration, the DeclStmt is used to declare the local
 public:
  std::vector<Decl *> Decls;
  DeclStmt() = default;
  explicit DeclStmt(std::vector<Decl *> Decls)
      : Stmt(tz_ast_type::Exp), Decls(std::move(Decls)) {}
  DeclStmt(llvm::LLVMContext &llvm_context,
           const llvm::json::Object *json_tree);
  llvm::BasicBlock *emit(llvm::Module &TheModule,
                         llvm::LLVMContext &llvm_context,
                         llvm::BasicBlock *PrevBB,
                         llvm::Value **ReturnValue) override;
  void print() override {
    printf("DeclStmt, Decls: ");
    for (auto &Decl : Decls) {
      Decl->print();
    }
    printf("Finish DeclStmt\n");
  };
};

}  // namespace tz_ast_class

namespace tz_ast_utils {
tz_ast_class::Object *BuildAST(llvm::LLVMContext &llvm_context,
                               const llvm::json::Object *json_tree,
                               const bool varDeclIsGlobal = false);

llvm::Type *ParsingLLVMType(llvm::LLVMContext &llvm_context, std::string str);

std::string StripTailChars(const std::string str, const char c = ' ');

tz_ast_type::BinaryOpCatgry ParsingBinaryOp(std::string str);
tz_ast_type::UnaryOpCatgry ParsingUnaryOp(std::string str);
tz_ast_type::CastCatgry ParsingImplicitCast(std::string str);

std::string Unescape(const std::string &str);

int ConvertMatToVec(llvm::Type *&ArrayType);

void RaiseOperandType(llvm::Module &TheModule, llvm::LLVMContext &llvm_context,
                      llvm::BasicBlock *BB, llvm::Value **lhs,
                      llvm::Value **rhs, bool isInt);
llvm::Constant *CalConstValueForGlobalVar(tz_ast_class::Expr *E);
llvm::Constant *CalConstArrayForGlobalVar(tz_ast_class::InitListExpr *E);
llvm::BasicBlock *buildInitListHelper(llvm::Module &TheModule,
                                      llvm::LLVMContext &llvm_context,
                                      llvm::BasicBlock *BB,
                                      tz_ast_class::InitListExpr *E,
                                      llvm::AllocaInst *arrayPtr, int &idx,
                                      int elementNum);
void buildConstInitListHelper(tz_ast_class::InitListExpr *E,
                              std::vector<llvm::Constant *> &elements, int &idx,
                              int elementNum, llvm::Type *BasicType);

int ConvertMatToVec2(llvm::Type *&ArrayGeneralType,
                     llvm::ArrayType *&ArrayTopType);
class WhileRangeControl {
  // findout the control range of while
 public:
  llvm::BasicBlock *whileBegin;
  llvm::BasicBlock *whileEnd;
  WhileRangeControl(llvm::BasicBlock *begin, llvm::BasicBlock *end)
      : whileBegin(begin), whileEnd(end) {}
};
}  // namespace tz_ast_utils
#endif