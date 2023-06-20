#include "ast.h"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/JSON.h>

#include <cstdio>
#include <string>
#include <utility>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Value.h"

/********************************
 * Constructors of all the AST nodes in tz_ast_class
 ********************************/

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
tz_ast_class::IntegerLiteral::IntegerLiteral(
    llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree) {
  // IntegerLiteral May be int or long or longlong
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get value
  if (type->isIntegerTy(32)) {
    // int
    value = llvm::ConstantInt::get(
        llvm::Type::getInt32Ty(llvm_context),
        llvm::APInt(type->getIntegerBitWidth(),
                    json_tree->getString("value")->str(), 10));
  } else if (type->isIntegerTy(64)) {
    // long long
    value = llvm::ConstantInt::get(
        llvm::Type::getInt64Ty(llvm_context),
        llvm::APInt(type->getIntegerBitWidth(),
                    json_tree->getString("value")->str(), 10));
  } else {
    assert("IntegerLiteral Initialization False" && false);
  }
}

tz_ast_class::FloatingLiteral::FloatingLiteral(
    llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree) {
  // FloatingLiteral May be float or double
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get value
  if (type->isFloatTy()) {
    // float
    value = llvm::ConstantFP::get(
        llvm::Type::getFloatTy(llvm_context),
        llvm::APFloat(llvm::APFloatBase().IEEEsingle(),
                      json_tree->getString("value")->str()));
  } else if (type->isDoubleTy()) {
    value = llvm::ConstantFP::get(
        llvm::Type::getDoubleTy(llvm_context),
        llvm::APFloat(llvm::APFloatBase().IEEEdouble(),
                      json_tree->getString("value")->str()));
  } else {
    assert("FloatingLiteral Initialization False" && false);
  }
}

tz_ast_class::StringLiteral::StringLiteral(
    llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  std::string _value = json_tree->getString("value")->str();
  // remove the " at the head and tail
  _value = _value.substr(1, _value.size() - 2);
  // Finished! TODO(Need to process stupid chars): May be wrong!
  _value = tz_ast_utils::Unescape(_value);
  while (_value.size() < type->getArrayNumElements()) {
    _value += '\0';
  }
  assert("Unescaped value string is as long as length defined by type" &&
         _value.size() == type->getArrayNumElements());
  if (type->isArrayTy()) {
    // array
    // disable a null terminator added
    value = llvm::ConstantDataArray::getString(llvm_context, _value, false);
  } else {
    assert("FloatingLiteral Initialization False" && false);
  }
}

tz_ast_class::BinaryExpr::BinaryExpr(llvm::LLVMContext &llvm_context,
                                     const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get op
  std::string BinaryOPString = json_tree->getString("opcode")->str();
  op = tz_ast_utils::ParsingBinaryOp(BinaryOPString);

  // Get lhs and rhs
  auto lhs_json = (*json_tree->getArray("inner"))[0].getAsObject();
  auto rhs_json = (*json_tree->getArray("inner"))[1].getAsObject();

  lhs = dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, lhs_json));
  rhs = dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, rhs_json));
}

tz_ast_class::UnaryExpr::UnaryExpr(llvm::LLVMContext &llvm_context,
                                   const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get op
  std::string UnaryOPString = json_tree->getString("opcode")->str();
  op = tz_ast_utils::ParsingUnaryOp(UnaryOPString);

  // Get rhs
  auto rhs_json = (*json_tree->getArray("inner"))[0].getAsObject();
  rhs = dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, rhs_json));
}

tz_ast_class::DeclRefExpr::DeclRefExpr(llvm::LLVMContext &llvm_context,
                                       const llvm::json::Object *json_tree) {
  /******
   * All the reference will go to here,
        * including the reference to the global
        ,local,parameter and FUNCTIONS!!!
        IT IS VITAL to considerate the Feferee findings
   ******/
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::lvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get DeclRefee
  auto DeclRefee_ID =
      json_tree->getObject("referencedDecl")->getString("id")->str();
  // Finished! TODO(to be finished): Think of the global map strategy
  DeclRefee =
      dynamic_cast<Decl *>(tz_ast_class::GlobalSymbolAstMap[DeclRefee_ID]);
}

tz_ast_class::ImplicitCastExpr::ImplicitCastExpr(
    llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get CastCatgry
  std::string CastOPString = json_tree->getString("castKind")->str();
  CastCatgry = tz_ast_utils::ParsingImplicitCast(CastOPString);

  // Get castExpr
  auto castExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
  castExpr =
      dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, castExpr_json));
}

tz_ast_class::InitListExpr::InitListExpr(llvm::LLVMContext &llvm_context,
                                         const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);
  // Get initExprs
  auto initExprs_json = json_tree->getArray("inner");
  if (initExprs_json == nullptr) {
    initExprs_json = json_tree->getArray("array_filler");
  }
  // Get isInited
  isInited = false;
  for (auto &initExpr_json : *initExprs_json) {
    if (initExpr_json == initExprs_json->front() &&
        initExpr_json.getAsObject()->getString("kind")->str() ==
            "InitListExpr") {
      // Check the first element is InitListExpr
      isInited = true;
      continue;
    }
    initExprs.push_back(dynamic_cast<Expr *>(
        tz_ast_utils::BuildAST(llvm_context, initExpr_json.getAsObject())));
  }
}

tz_ast_class::ArraySubscriptExpr::ArraySubscriptExpr(
    llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::lvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get ArrayBase
  auto ArrayBase_json = (*json_tree->getArray("inner"))[0].getAsObject();
  ArrayBase = dynamic_cast<Expr *>(
      tz_ast_utils::BuildAST(llvm_context, ArrayBase_json));

  // Get ArrayIdx
  auto ArrayIdx_json = (*json_tree->getArray("inner"))[1].getAsObject();
  ArrayIdx =
      dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, ArrayIdx_json));
}

tz_ast_class::CallExpr::CallExpr(llvm::LLVMContext &llvm_context,
                                 const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get callee
  auto callee_json = (*json_tree->getArray("inner"))[0].getAsObject();
  callee =
      dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, callee_json));

  // Get CalleeArgs
  auto CalleeArgs_json = json_tree->getArray("inner");
  for (auto &CalleeArg_json : *CalleeArgs_json) {
    if (CalleeArg_json == CalleeArgs_json->front()) {
      // Jump the callee
      continue;
    }
    CalleeArgs.push_back(dynamic_cast<Expr *>(
        tz_ast_utils::BuildAST(llvm_context, CalleeArg_json.getAsObject())));
  }
}

tz_ast_class::ParenExpr::ParenExpr(llvm::LLVMContext &llvm_context,
                                   const llvm::json::Object *json_tree) {
  // Initialize the ExprCatgry
  ExprCatgry = tz_ast_type::rvalue;

  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get parenExpr
  auto parenExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
  inParenExpr = dynamic_cast<Expr *>(
      tz_ast_utils::BuildAST(llvm_context, parenExpr_json));
}

/********************************
 *  Decl
 *  TranslationUnitDecl
 *  VarDecl
 *  ParmVarDecl
 *  FunctionDecl
 ********************************/
tz_ast_class::TranslationUnitDecl::TranslationUnitDecl(
    llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree) {
  // No Name and type for TranslationUnitDecl
  type = nullptr;
  name = "";
  auto decls_json = json_tree->getArray("inner");
  for (auto &decl_json : *decls_json) {
    Decls.push_back(dynamic_cast<Decl *>(
        tz_ast_utils::BuildAST(llvm_context, decl_json.getAsObject())));
  }
}

tz_ast_class::VarDecl::VarDecl(llvm::LLVMContext &llvm_context,
                               const llvm::json::Object *json_tree) {
  // By default, the Var is not a const
  isConst = false;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    isConst = true;
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get name
  name = json_tree->getString("name")->str();

  // Get initExpr
  isInited = false;
  if (json_tree->getObject("inner") != nullptr) {
    isInited = true;
    auto initExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
    InitExpr = dynamic_cast<Expr *>(
        tz_ast_utils::BuildAST(llvm_context, initExpr_json));
  }

  // Store in the global map
  std::string VarDeclID = json_tree->getString("id")->str();
  assert("Duplicate ID, already in Map!" &&
         tz_ast_class::GlobalSymbolAstMap.find(VarDeclID) !=
             tz_ast_class::GlobalSymbolAstMap.end());
  tz_ast_class::GlobalSymbolAstMap[VarDeclID] = this;
}

tz_ast_class::ParmVarDecl::ParmVarDecl(llvm::LLVMContext &llvm_context,
                                       const llvm::json::Object *json_tree) {
  // By default, the Var is not a const
  isConst = false;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    isConst = true;
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // Get name
  name = json_tree->getString("name")->str();

  // Get initExpr
  isInited = false;
  if (json_tree->getObject("inner") != nullptr) {
    isInited = true;
    auto initExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
    InitExpr = dynamic_cast<Expr *>(
        tz_ast_utils::BuildAST(llvm_context, initExpr_json));
  }

  // Store in the global map
  std::string ParamVarDeclID = json_tree->getString("id")->str();
  assert("Duplicate ID, already in Map!" &&
         tz_ast_class::GlobalSymbolAstMap.find(ParamVarDeclID) !=
             tz_ast_class::GlobalSymbolAstMap.end());
  tz_ast_class::GlobalSymbolAstMap[ParamVarDeclID] = this;
}

tz_ast_class::FunctionDecl::FunctionDecl(llvm::LLVMContext &llvm_context,
                                         const llvm::json::Object *json_tree) {
  // By default, the Var is not a const
  isConst = false;
  // Get type
  auto _type = json_tree->getObject("type")->getString("qualType")->str();
  if (_type.find("const") != std::string::npos) {
    // remove the const description
    isConst = true;
    _type = _type.substr(6, _type.size() - 1);
  }
  type = tz_ast_utils::ParsingLLVMType(llvm_context, _type);

  // TODO(unknown):
  // // Get name
  // name = json_tree->getString("name")->str();

  // // Get ParmVarDecls
  // auto ParmVarDecls_json = json_tree->getArray("inner");
  // for (auto &ParmVarDecl_json : *ParmVarDecls_json) {
  //   ParmVarDecls.push_back(dynamic_cast<ParmVarDecl *>(
  //       tz_ast_utils::BuildAST(llvm_context,
  //       ParmVarDecl_json.getAsObject())));
  // }

  // // Get body
  // auto body_json =
  //     (*json_tree->getArray("inner"))[ParmVarDecls.size()].getAsObject();
  // body = dynamic_cast<CompoundStmt *>(
  //     tz_ast_utils::BuildAST(llvm_context, body_json));

  // Store in the global map
  std::string FuncDeclID = json_tree->getString("id")->str();
  assert("Duplicate ID, already in Map!" &&
         tz_ast_class::GlobalSymbolAstMap.find(FuncDeclID) !=
             tz_ast_class::GlobalSymbolAstMap.end());
  tz_ast_class::GlobalSymbolAstMap[FuncDeclID] = this;
}

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

tz_ast_class::CompoundStmt::CompoundStmt(llvm::LLVMContext &llvm_context,
                                         const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::Compound;
  // Get Stmts
  auto Stmts_json = json_tree->getArray("inner");
  if (Stmts_json != nullptr) {
    for (auto &Stmt_json : *Stmts_json) {
      InnerStmts.push_back(dynamic_cast<Stmt *>(
          tz_ast_utils::BuildAST(llvm_context, Stmt_json.getAsObject())));
      if (InnerStmts.size() &&
          typeid(*InnerStmts.back()) == typeid(ReturnStmt)) {
        break;
      }
    }
  }
}

tz_ast_class::ReturnStmt::ReturnStmt(llvm::LLVMContext &llvm_context,
                                     const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::Return;
  // Get returnExpr
  ReturnExpr = nullptr;
  if (json_tree->getObject("inner") == nullptr) {
    auto returnExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
    ReturnExpr = dynamic_cast<Expr *>(
        tz_ast_utils::BuildAST(llvm_context, returnExpr_json));
  }
}

tz_ast_class::IfStmt::IfStmt(llvm::LLVMContext &llvm_context,
                             const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::If;
  // Get condExpr
  auto condExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
  IfCondExpr =
      dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, condExpr_json));
  // Get thenStmt
  auto thenStmt_json = (*json_tree->getArray("inner"))[1].getAsObject();
  ThenObj = dynamic_cast<Object *>(
      tz_ast_utils::BuildAST(llvm_context, thenStmt_json));
  // Get elseStmt
  hasElse = false;
  if (json_tree->getArray("inner")->size() == 3) {
    hasElse = true;
    auto elseStmt_json = (*json_tree->getArray("inner"))[2].getAsObject();
    ElseObj = dynamic_cast<Object *>(
        tz_ast_utils::BuildAST(llvm_context, elseStmt_json));
  }
}

tz_ast_class::WhileStmt::WhileStmt(llvm::LLVMContext &llvm_context,
                                   const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::While;
  // Get condExpr
  auto condExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
  WhileCondExpr =
      dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, condExpr_json));
  // Get body
  auto body_json = (*json_tree->getArray("inner"))[1].getAsObject();
  WhileObj =
      dynamic_cast<Stmt *>(tz_ast_utils::BuildAST(llvm_context, body_json));
  assert("Error: While has no body!" && WhileObj != nullptr);
}

tz_ast_class::DoStmt::DoStmt(llvm::LLVMContext &llvm_context,
                             const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::While;
  // Get DoCondExpr
  auto condExpr_json = (*json_tree->getArray("inner"))[0].getAsObject();
  DoCondExpr =
      dynamic_cast<Expr *>(tz_ast_utils::BuildAST(llvm_context, condExpr_json));
  // Get body
  auto body_json = (*json_tree->getArray("inner"))[1].getAsObject();
  DoObj = dynamic_cast<Stmt *>(tz_ast_utils::BuildAST(llvm_context, body_json));
  assert("Error: Do has no body!" && DoObj != nullptr);
}

tz_ast_class::NullStmt::NullStmt(llvm::LLVMContext &llvm_context,
                                 const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::Null;
  // Nothing else to do
}

tz_ast_class::BreakStmt::BreakStmt(llvm::LLVMContext &llvm_context,
                                   const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::Break;
  // Nothing else to do
}

tz_ast_class::ContinueStmt::ContinueStmt(llvm::LLVMContext &llvm_context,
                                         const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::Continue;
  // Nothing else to do
}

tz_ast_class::DeclStmt::DeclStmt(llvm::LLVMContext &llvm_context,
                                 const llvm::json::Object *json_tree) {
  // Initialize the StmtCatgry
  StmtCatgry = tz_ast_type::Decl;
  // Get Decls
  auto Decls_json = json_tree->getArray("inner");
  for (auto &Decl_json : *Decls_json) {
    Decls.push_back(dynamic_cast<Decl *>(
        tz_ast_utils::BuildAST(llvm_context, Decl_json.getAsObject())));
  }
}

/********************************
 * Utils implementation
 ********************************/
tz_ast_class::Object *tz_ast_utils::BuildAST(
    llvm::LLVMContext &llvm_context, const llvm::json::Object *json_tree) {
  // Remember to assert when there is no-matched kind
  std::string NodeKind = json_tree->getString("kind")->str();
  if (NodeKind == "IntegerLiteral") {
    return new tz_ast_class::IntegerLiteral(llvm_context, json_tree);
  } else if (NodeKind == "FloatingLiteral") {
    return new tz_ast_class::FloatingLiteral(llvm_context, json_tree);
  } else if (NodeKind == "StringLiteral") {
    return new tz_ast_class::StringLiteral(llvm_context, json_tree);
  } else if (NodeKind == "BinaryExpr") {
    return new tz_ast_class::BinaryExpr(llvm_context, json_tree);
  } else if (NodeKind == "UnaryExpr") {
    return new tz_ast_class::UnaryExpr(llvm_context, json_tree);
  } else if (NodeKind == "CallExpr") {
    return new tz_ast_class::CallExpr(llvm_context, json_tree);
  } else if (NodeKind == "DeclRefExpr") {
    return new tz_ast_class::DeclRefExpr(llvm_context, json_tree);
  } else if (NodeKind == "ImplicitCastExpr") {
    return new tz_ast_class::ImplicitCastExpr(llvm_context, json_tree);
  } else if (NodeKind == "InitListExpr") {
    return new tz_ast_class::InitListExpr(llvm_context, json_tree);
  } else if (NodeKind == "ArraySubscriptExpr") {
    return new tz_ast_class::ArraySubscriptExpr(llvm_context, json_tree);
  } else if (NodeKind == "TranslationUnitDecl") {
    return new tz_ast_class::TranslationUnitDecl(llvm_context, json_tree);
  } else if (NodeKind == "VarDecl") {
    return new tz_ast_class::VarDecl(llvm_context, json_tree);
  } else if (NodeKind == "ParmVarDecl") {
    return new tz_ast_class::ParmVarDecl(llvm_context, json_tree);
  } else if (NodeKind == "FunctionDecl") {
    return new tz_ast_class::FunctionDecl(llvm_context, json_tree);
  } else if (NodeKind == "CompoundStmt") {
    return new tz_ast_class::CompoundStmt(llvm_context, json_tree);
  } else if (NodeKind == "ReturnStmt") {
    return new tz_ast_class::ReturnStmt(llvm_context, json_tree);
  } else if (NodeKind == "IfStmt") {
    return new tz_ast_class::IfStmt(llvm_context, json_tree);
  } else if (NodeKind == "WhileStmt") {
    return new tz_ast_class::WhileStmt(llvm_context, json_tree);
  } else if (NodeKind == "DoStmt") {
    return new tz_ast_class::DoStmt(llvm_context, json_tree);
  } else if (NodeKind == "NullStmt") {
    return new tz_ast_class::NullStmt(llvm_context, json_tree);
  } else if (NodeKind == "BreakStmt") {
    return new tz_ast_class::BreakStmt(llvm_context, json_tree);
  } else if (NodeKind == "ContinueStmt") {
    return new tz_ast_class::ContinueStmt(llvm_context, json_tree);
  } else if (NodeKind == "DeclStmt") {
    return new tz_ast_class::DeclStmt(llvm_context, json_tree);
  } else if (NodeKind == "TypedefDecl") {
    return nullptr;
    // TODO(nullptr judgement): May be wrong;
  } else {
    printf("Current kind is %s\n", NodeKind.c_str());
    assert("BuildAST False, Wrong Json Kind" && false);
  }
}

std::string tz_ast_utils::StripTailChars(const std::string &str, const char c) {
  int none_C_idx = str.size() - 1;
  while (str[none_C_idx] == ' ') {
    none_C_idx--;
  }
  ++none_C_idx;
  return str.substr(0, none_C_idx);
}
llvm::Type *tz_ast_utils::ParsingLLVMType(llvm::LLVMContext &llvm_context,
                                          std::string str) {
  // Notice: InitList is pretty hard
  //        Function Name and Array type is the most complicated

  str = StripTailChars(str, ' ');
  if (str == "void") {
    return llvm::Type::getVoidTy(llvm_context);
  } else if (str == "char") {
    return llvm::Type::getInt8Ty(llvm_context);
  } else if (str == "short") {
    return llvm::Type::getInt16Ty(llvm_context);
  } else if (str == "int" || str == "unsigned int") {
    return llvm::Type::getInt32Ty(llvm_context);
  } else if (str == "long" || str == "unsigned long") {
    return llvm::Type::getInt32PtrTy(llvm_context);
  } else if (str == "long long") {
    return llvm::Type::getInt64PtrTy(llvm_context);
  } else if (str == "float") {
    return llvm::Type::getFloatTy(llvm_context);
  } else if (str == "double") {
    return llvm::Type::getDoubleTy(llvm_context);
  } else if (str.find('[') != str.npos) {
    auto pos = str.find('[');
    // Get the int [3] 's 3
    auto ArraySizeStr = str.substr(pos + 1, str.find_first_of(']') - pos - 1);
    auto ArraySize = std::stoi(ArraySizeStr);
    // Remove the [3]
    str.replace(pos, str.find_first_of(']') - pos + 1, "");
    return llvm::ArrayType::get(ParsingLLVMType(llvm_context, str), ArraySize);
  } else if (str.find('*') != str.npos) {
    // Parsing type like int * & int (*)()
    auto pos = str.find("(*)");
    if (pos == str.npos) {
      // it is int *
      pos = str.find('*');
    }
    // remove the tailing * or (*)
    str = str.substr(0, pos);
    // get the type of array
    return llvm::PointerType::get(ParsingLLVMType(llvm_context, str), 0);
  } else {
    assert("ParsingLLVMType False" && false);
  }
}

tz_ast_type::BinaryOpCatgry ParsingBinaryOp(const std::string &str) {
  if (str == "+") {
    return tz_ast_type::BinaryOpCatgry::Add;
  } else if (str == "-") {
    return tz_ast_type::BinaryOpCatgry::Sub;
  } else if (str == "*") {
    return tz_ast_type::BinaryOpCatgry::Mul;
  } else if (str == "/") {
    return tz_ast_type::BinaryOpCatgry::Div;
  } else if (str == "%") {
    return tz_ast_type::BinaryOpCatgry::Mod;
  } else if (str == "<") {
    return tz_ast_type::BinaryOpCatgry::Less;
  } else if (str == "<=") {
    return tz_ast_type::BinaryOpCatgry::LessEq;
  } else if (str == ">") {
    return tz_ast_type::BinaryOpCatgry::Greater;
  } else if (str == ">=") {
    return tz_ast_type::BinaryOpCatgry::GreaterEq;
  } else if (str == "=") {
    return tz_ast_type::BinaryOpCatgry::Eq;
  } else if (str == "==") {
    return tz_ast_type::BinaryOpCatgry::EqEq;
  } else if (str == "!=") {
    return tz_ast_type::BinaryOpCatgry::ExclaimEq;
  } else if (str == "&&") {
    return tz_ast_type::BinaryOpCatgry::AmpAmp;
  } else if (str == "||") {
    return tz_ast_type::BinaryOpCatgry::PipePipe;
  } else {
    assert("ParsingBinaryOp False" && false);
  }
}
tz_ast_type::UnaryOpCatgry ParsingUnaryOp(const std::string &str) {
  if (str == "&") {
    return tz_ast_type::UnaryOpCatgry::U_FindAddr;
  } else if (str == "*") {
    return tz_ast_type::UnaryOpCatgry::U_Deref;
  } else if (str == "+") {
    return tz_ast_type::UnaryOpCatgry::U_Plus;
  } else if (str == "-") {
    return tz_ast_type::UnaryOpCatgry::U_Minus;
  } else if (str == "~") {
    return tz_ast_type::UnaryOpCatgry::U_Tilde;
  } else if (str == "!") {
    return tz_ast_type::UnaryOpCatgry::U_N;
  } else {
    assert("ParsingUnaryOp False" && false);
  }
}
tz_ast_type::CastCatgry ParsingImplicitCast(const std::string &str) {
  if (str == "IntegralCast") {
    return tz_ast_type::CastCatgry::IntegralCast;
  } else if (str == "FloatingCast") {
    return tz_ast_type::CastCatgry::FloatingCast;
  } else if (str == "LValueToRValue") {
    return tz_ast_type::CastCatgry::LValueToRValue;
  } else if (str == "IntegralToFloat") {
    return tz_ast_type::CastCatgry::IntegralToFloat;
  } else if (str == "FloatToIntegral") {
    return tz_ast_type::CastCatgry::FloatToIntegral;
  } else if (str == "FunctionToPointerDecay") {
    return tz_ast_type::CastCatgry::FunctionToPointerDecay;
  } else if (str == "ArrayToPointerDecay") {
    return tz_ast_type::CastCatgry::ArrayToPointerDecay;
  } else if (str == "BitCast") {
    return tz_ast_type::CastCatgry::BitCast;
  } else if (str == "NoOp") {
    return tz_ast_type::CastCatgry::NoOp;
  } else {
    assert("ParsingImplicitCast False" && false);
  }
}
std::string tz_ast_utils::Unescape(const std::string &str) {
  std::string result;
  for (std::size_t i = 0; i < str.length(); ++i) {
    if (str[i] == '\\') {
      ++i;
      if (i == str.length()) {
        // The string ends with a backslash
        assert("Invalid escape sequence ends with a backslash" && false);
      }
      switch (str[i]) {
        case 'n':
          result += '\n';
          break;
        case 't':
          result += '\t';
          break;
        case '\\':
          result += '\\';
          break;
        case '\"':
          result += '\"';
          break;
        case '\'':
          result += '\'';
          break;
        case 'r':
          result += '\r';
          break;
        case 'v':
          result += '\v';
          break;
        case 'f':
          result += '\f';
          break;
        case 'a':
          result += '\a';
          break;
        case 'b':
          result += '\b';
          break;
        default:
          // Unknown escape sequence
          assert("Invalid escape sequence ends with a backslash" && false);
      }
    } else {
      result += str[i];
    }
  }
  return result;
}