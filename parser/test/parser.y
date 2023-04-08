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
        if (s.find('.') != std::string::npos || s.find('p') != std::string::npos || s.find('e') != std::string::npos) 
        {
            auto kind = "FloatingLiteral";
            llvm::StringRef str(value);
            llvm::APFloat apf(0.0);
            apf.convertFromString(str, llvm::APFloat::rmNearestTiesToEven);
            llvm::SmallString<16> Buffer;
            apf.toString(Buffer);
            value = Buffer.c_str();
            // std::cout << "Number Testing  " << t << " " << value << std::endl;
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
%right U_N
%right U_MINUS U_PLUS 
%%
/* New Rules
CompUnit      ::= [CompUnit] GlobalDecl;

GlobalDecl    ::= ConstDecl | VarDecl | FuncDef;
ConstDecl     ::= "const" BType VarDefList ";";
VarDecl       ::= BType VarDefList ";";
BType         ::= "int" | "char" | "long long";
ArrayList     ::= {"[" Exp "]"};
VarDefList    ::= VarDef {"," VarDef};

VarDef        ::= IDENT ArrayList
                | IDENT ArrayList "=" InitVal;
InitVal       ::= Exp | "{" InitValList "}";
InitValList   ::= InitVal {"," InitVal};

FuncDef       ::= BType IDENT "(" FuncFParams ")" Block;
FuncFParams   ::= [FuncFParam {"," FuncFParam}];
FuncFParam    ::= BType IDENT ["[" "]" ArrayList];
ParamArrayList::= {"[" "]" ArrayList};

Block         ::= "{" {BlockItem} "}";
BlockItem     ::= ConstDecl | VarDecl | Stmt;
Stmt          ::= MatchedStmt | UnmatchedStmt;
MatchedStmt   ::= LVal "=" Exp ";"
                | Exp ";"
                | ";"
                | Block
                | "if" "(" Exp ")" MatchedStmt "else" MatchedStmt
                | "while" "(" Exp ")" MatchedStmt
                | "break" ";"
                | "continue" ";"
                | "return" Exp ";";
                | "return" ";"
                | "do" "{" MatchedStmt "}" "while" "(" MatchedStmt ")" ";"
UnmatchedStmt ::= "if" "(" Exp ")" Stmt
                | "if" "(" Exp ")" Stmt "else" UnmatchedStmt

Exp           ::= LOrExp;
LVal          ::= IDENT ArrayList;
PrimaryExp    ::= "(" Exp ")" | LVal | Number;
Number        ::= INT_CONST;

  %prec UMINUS => 将该产生式的优先级调整为 UMINUS
  如：T_MINUS Expr %prec UMINUS

UnaryExp      ::= PrimaryExp | IDENT "(" FuncRParams ")" | UnaryOp UnaryExp;
UnaryOp       ::= "+" | "-" | "!";
FuncRParams   ::= [Exp {"," Exp}];
MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;
AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;
RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;
EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;
LAndExp       ::= EqExp | LAndExp "&&" EqExp;
LOrExp        ::= LAndExp | LOrExp "||" LAndExp;



// Todo: Checkpoint: Maybe useless
ConstDef      ::= IDENT ArrayList "=" InitVal; //Temporarily merge with VarDef

//Useless
ConstExp      ::= Exp;
FuncType      ::= "void" | "int";
ConstInitVal  ::= Exp | "{" [ConstInitVal {"," ConstInitVal}] "}"; //Merge with InitVal
 */


/* CompUnit      ::= [CompUnit] GlobalDecl; */
Begin: CompUnit {
        root = $1;
    }
    ;

CompUnit: CompUnit GlobalDecl {
    $$ = $1;
    if ($2->kind == "VarDeclPreNode") {
        $$->moveSons($2);
    }
    else {
        $$->addSon($2);
    }
    }
    | GlobalDecl {
        $$ = new asgNode("TranslationUnitDecl");
        if ($1->kind == "VarDeclPreNode") {
            $$->moveSons($1);
        }
        else {
            $$->addSon($1);
        }
    }
    ;

/* GlobalDecl    ::= ConstDecl | VarDecl | FuncDef; */
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

/* ConstDecl     ::= "const" BType VarDefList ";"; */
ConstDecl: T_CONST BType VarDefList T_SEMI 
    {
        $$ = $3;
        for(auto&& it: $$->sons)
        {
            it->type = "const " + $2->type + son->type;
        }
        delete $2;
    }
    ;
/* VarDecl       ::= BType VarDefList ";"; */
VarDecl: BType VarDefList T_SEMI {
        $$ = $2;
        for(auto&& it: $$->sons)
        {
            it->type = $1->type + son->type;
        }
        delete $1;
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

/* ArrayList     ::= {"[" Exp "]"}; */
/* Please Delete the ArrayList after using, It's only useful when first used */
ArrayList: %empty {
        $$ = new asgNode("ArrayDecl");
    }
    | ArrayList T_L_SQUARE Exp T_R_SQUARE {
        $$ = $1;
        $$->addSon($3);
        $$->type += " [" + $3->value + "]";
        //cal the $ 3 type
    }
    ;


/* VarDefList    ::= VarDef {"," VarDef}; */
VarDefList: VarDef {
        $$ = new asgNode("VarDeclPreNode");
        $$->addSon($1);
    }
    | VarDefList T_COMMA VarDef {
        $$ = $1;
        $$->addSon($3);
    }
    ;

/* VarDef        ::= IDENT ArrayList
                | IDENT ArrayList "=" InitVal; */
VarDef: T_IDENTIFIER ArrayList {
        $$ = $1;
        $$->type = $2->type;
        $$->kind = "VarDecl";
        // Add in symbol table
        idenTable[$$->name] = $$;
        delete $2;
    }
    | T_IDENTIFIER ArrayList T_EQUAL InitVal {
        $$ = $1;
        $$->type = $2->type;
        $$->kind = "VarDecl";
        // Add in symbol table
        idenTable[$$->name] = $$;
        delete $2;
        // Todo: For Implicit Type Conversion
        $$->opcode = "=";
        $$->addSon($4);

    }
    ;
/* InitVal       ::= Exp | "{" InitValList "}"; */
/* Notice: Need to add a prenode named InitListExpr when using InitVal */
/* Todo: Maybe need to fix */
InitVal: Exp {
        $$ = $1;
    }
    | T_L_BRACE InitValList T_R_BRACE {
        $$ = $2;
    }
    ;
/* InitValList   ::= InitVal {"," InitVal}; */
InitValList: InitVal {
        $$ = new asgNode("InitListExpr");
        $$->addSon($1);
    }
    | InitValList T_COMMA InitVal {
        $$ = $1;
        $$->addSon($3);
    }
    | %empty {
        $$ = new asgNode("InitListExpr");
    }
    ;

/* FuncDef       ::= BType IDENT "(" FuncFParams ")" Block; */
FuncDef: BType T_IDENTIFIER T_L_PAREN FuncFParams T_R_PAREN Block {
        $$ = $2;
        $$->type = $1->type + "(" + $4->type + ")";
        $$->kind = "FunctionDecl";
        delete $1;
        $$->addSon($4);
        $$->addSon($6);
        // Add in symbol table
        idenTable[$$->name] = $$;
    }
    ;
/* FuncFParams   ::= [FuncFParam {"," FuncFParam}]; */
/* Todo: Maybe the type is wrong */
FuncFParams: %empty {
        $$ = new asgNode("ParamVarDecl");
    }
    | FuncFParam {
        $$ = new asgNode("ParamVarDecl");
        $$->addSon($1);
    }
    | FuncFParams T_COMMA FuncFParam {
        $$ = $1;
        $$->addSon($3);
    }
    ;
/* FuncFParam    ::= BType IDENT [ParamArrayList]; */
FuncFParam: BType T_IDENTIFIER{
        $$ = $2;
        $$->type = $1->type;
        delete $1;
    }
    | BType T_IDENTIFIER ParamArrayList {
        $$ = $2;
        $$->type = $1->type + $3->type;
        delete $1;
        delete $3;
    }
    ;
/* ParamArrayList::= "[" "]" ArrayList; */
ParamArrayList: T_L_SQUARE T_R_SQUARE ArrayList {
        $$ = $3;
        $$->type = "[]" + $$->type;
    }
    ;

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
/* BlockItem     ::= ConstDecl | VarDecl | Stmt; */
BlockItem: ConstDecl {
        $$ = new asgNode("DeclStmt");
        // Move sons because we use a declprenode
        $$->moveSons($1);
    }
    | VarDecl {
        $$ = new asgNode("DeclStmt");
        // Move sons because we use a declprenode
        $$->moveSons($1);
    }
    | Stmt {
        $$ = $1;
    }
    ;
/* Stmt          ::= MatchedStmt | UnmatchedStmt; */
Stmt: MatchedStmt {
        $$ = $1;
    }
    | UnmatchedStmt {
        $$ = $1;
    }
    ;
/* MatchedStmt   ::= LVal "=" Exp ";"
                | Exp ";"
                | ";"
                | Block
                | "if" "(" Exp ")" MatchedStmt "else" MatchedStmt
                | "while" "(" Exp ")" MatchedStmt
                | "break" ";"
                | "continue" ";"
                | "return" Exp ";";
                | "return" ";"
                | "do" "{" MatchedStmt "}" "while" "(" MatchedStmt ")" ";" */
MatchedStmt: LVal T_EQUAL Exp T_SEMI {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "=";
        $$->addSon($1);
        $$->addSon($3);
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
    | T_IF T_L_PAREN Exp T_R_PAREN MatchedStmt T_ELSE MatchedStmt {
        $$ = new asgNode("IfStmt");
        $$->addSon($3);
        $$->addSon($5);
        $$->addSon($7);
    }
    | T_WHILE T_L_PAREN Exp T_R_PAREN MatchedStmt {
        $$ = new asgNode("WhileStmt");
        $$->addSon($3);
        $$->addSon($5);
    }
    | T_BREAK T_SEMI {
        $$ = new asgNode("BreakStmt");
    }
    | T_CONTINUE T_SEMI {
        $$ = new asgNode("ContinueStmt");
    }
    | T_RETURN Exp T_SEMI {
        $$ = new asgNode("ReturnStmt");
        $$->addSon($2);
        // Todo: Implicit conversion
    }
    | T_RETURN T_SEMI {
        $$ = new asgNode("ReturnStmt");
    }
    | T_DO T_L_BRACE MatchedStmt T_R_BRACE T_WHILE T_L_PAREN Exp T_R_PAREN T_SEMI {
        $$ = new asgNode("DoStmt");
        $$->addSon($3);
        $$->addSon($7);
    }
    ;
/* UnmatchedStmt ::= "if" "(" Exp ")" Stmt
                | "if" "(" Exp ")" Stmt "else" UnmatchedStmt */
UnmatchedStmt: T_IF T_L_PAREN Exp T_R_PAREN Stmt {
        $$ = new asgNode("IfStmt");
        $$->addSon($3);
        $$->addSon($5);
    }
    | T_IF T_L_PAREN Exp T_R_PAREN MatchedStmt T_ELSE UnmatchedStmt {
        $$ = new asgNode("IfStmt");
        $$->addSon($3);
        $$->addSon($5);
        $$->addSon($7);
    }
    ;
/* Exp           ::= LOrExp; */
Exp: LOrExp {
        $$ = $1;
    }
    ;
/* LVal          ::= IDENT ArrayList; */
LVal: T_IDENTIFIER ArrayList {
        $$ = $1;
        $$->type = idenTable[$$->name]->type + $2->type;
        delete $2;
    }
    ;
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
Number: T_NUMERIC_CONSTANT {
        $$ = $1;
        if($$->type == "int")
        {
            $$->kind = "IntegerLiteral";
        }
        else
        {
            $$->kind = "FloatingLiteral";
        }
    }
    ;

  /* %prec UMINUS => 将该产生式的优先级调整为 UMINUS
  如：T_MINUS Expr %prec UMINUS */

/* UnaryExp      ::= PrimaryExp | IDENT "(" FuncRParams ")" | ("+" | "-" | "!") UnaryExp; */
UnaryExp: PrimaryExp {
        $$ = $1;
    }
    | T_IDENTIFIER T_L_PAREN FuncRParams T_R_PAREN {
        $$ = $1;
        $$->kind = "CallExpr";
        $$->type = idenTable[$$->name]->type + $3->type;
        $$->moveSons($3);
    }
    | T_PLUS UnaryExp %prec U_PLUS {
        $$ = new asgNode("UnaryOperator");
        $$->opcode = "+";
        $$->addSon($2);
    }
    | T_MINUS UnaryExp %prec U_MINUS {
        $$ = new asgNode("UnaryOperator");
        $$->opcode = "-";
        $$->addSon($2);
    }
    | T_EXCLAIM UnaryExp %prec U_N {
        $$ = new asgNode("UnaryOperator");
        $$->opcode = "!";
        $$->addSon($2);
    }
    ;
/* FuncRParams   ::= [Exp {"," Exp}]; */
FuncRParams: Exp {
        $$ = $1;
    }
    | FuncRParams T_COMMA Exp {
        $$ = $1;
        $$->addSon($3);
    }
    | %empty {
        $$ = new asgNode("FuncRParamsPreNode");
    }
    ;
/* MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp; */
MulExp: UnaryExp {
        $$ = $1;
    }
    | MulExp T_STAR UnaryExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "*";
        $$->addSon($1);
        $$->addSon($3);
    }
    | MulExp T_SLASH UnaryExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "/";
        $$->addSon($1);
        $$->addSon($3);
    }
    | MulExp T_PERCENT UnaryExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "%";
        $$->addSon($1);
        $$->addSon($3);
    }
    ;
/* AddExp        ::= MulExp | AddExp ("+" | "-") MulExp; */
AddExp: MulExp {
        $$ = $1;
    }
    | AddExp T_PLUS MulExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "+";
        $$->addSon($1);
        $$->addSon($3);
    }
    | AddExp T_MINUS MulExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "-";
        $$->addSon($1);
        $$->addSon($3);
    }
    ;
/* RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp; */
RelExp: AddExp {
        $$ = $1;
    }
    | RelExp T_LESS AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "<";
        $$->addSon($1);
        $$->addSon($3);
    }
    | RelExp T_GREATER AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = ">";
        $$->addSon($1);
        $$->addSon($3);
    }
    | RelExp T_LESSEQUAL AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "<=";
        $$->addSon($1);
        $$->addSon($3);
    }
    | RelExp T_GREATEREQUAL AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = ">=";
        $$->addSon($1);
        $$->addSon($3);
    }
    ;
/* EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp; */
EqExp: RelExp {
        $$ = $1;
    }
    | EqExp T_EQUALEQUAL RelExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "==";
        $$->addSon($1);
        $$->addSon($3);
    }
    | EqExp T_EXCLAIMEQUAL RelExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "!=";
        $$->addSon($1);
        $$->addSon($3);
    }
    ;
/* LAndExp       ::= EqExp | LAndExp "&&" EqExp; */
LAndExp: EqExp {
        $$ = $1;
    }
    | LAndExp T_AMPAMP EqExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "&&";
        $$->addSon($1);
        $$->addSon($3);
    }
    ;
/* LOrExp        ::= LAndExp | LOrExp "||" LAndExp; */
LOrExp: LAndExp {
        $$ = $1;
    }
    | LOrExp T_PIPEPIPE LAndExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "||";
        $$->addSon($1);
        $$->addSon($3);
    }
    ;
%%