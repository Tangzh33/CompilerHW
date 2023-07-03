file ~/sysu/bin/sysu-generator
b main
# b tz_ast_class::InitListExpr::InitListExpr
# b tz_ast_utils::ParsingImplicitCast
# b tz_ast_class::DeclRefExpr::DeclRefExpr
# b tz_ast_utils::BuildAST
# b tz_ast_class::VarDecl::print
# b tz_ast_class::CompoundStmt::print
# b tz_ast_class::FunctionDecl::FunctionDecl
# b tz_ast_class::CompoundStmt::CompoundStmt
# b tz_ast_class::VarDecl::emit
# b tz_ast_class::DeclStmt::emit
# b tz_ast_class::WhileStmt::WhileStmt
# b tz_ast_utils::RaiseOperandType
# b tz_ast_class::BinaryExpr::emit
# b tz_ast_class::CompoundStmt::emit
# b tz_ast_class::ArraySubscriptExpr::emit
# b tz_ast_class::ReturnStmt::emit
# b tz_ast_class::IfStmt::emit
# b tz_ast_class::ReturnStmt::ReturnStmt
b tz_ast_class::FunctionDecl::emit
# b tz_ast_class::ArraySubscriptExpr::emit
# b tz_ast_class::InitListExpr::emit
# b tz_ast_class::DeclRefExpr::emit
# b  tz_ast_class::ParmVarDecl::ParmVarDecl
# b tz_ast_class::FunctionDecl::FunctionDecl
# b tz_ast_class::FunctionDecl::FunctionDecl
run < tmp/clangout.json
layout src