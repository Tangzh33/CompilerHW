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
#include <sstream>
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
    std::string currentFuncType;
    // const long INT_MAX = 2147483647;
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
            kind = "FloatingLiteral";
            llvm::StringRef str(value);
            llvm::APFloat apf(0.0);
            llvm::Expected<llvm::APFloatBase::opStatus> returnFlag = apf.convertFromString(str, llvm::APFloat::rmNearestTiesToEven);
            llvm::SmallString<16> Buffer;
            apf.toString(Buffer);
            value = Buffer.c_str();
            // std::cout << "Number Testing  " << t << " " << value << std::endl;
            type = "double";
        }
        else if (s.find("0x") != std::string::npos)
        {
            // convert the hexadecimal int to decimal form
            long long x;
            std::stringstream ss;
            ss << std::hex << s;
            ss >> x;
            value = std::to_string(x);
            if(x > __INT_MAX__)
            {
                type = "long";
            }
            kind = "IntegerLiteral";
        }
        else if(s.length() > 1 && s[0] == '0')
        {
            // convert the oct-int to decimal form
            long long x;
            std::stringstream ss;
            ss << std::oct << s;
            ss >> x;
            value = std::to_string(x);
            if(x > __INT_MAX__)
            {
                type = "long";
            }
            kind = "IntegerLiteral";
        }
        else
        {
            long long x = strtol(s.c_str(), nullptr, 0);
            if(x > __INT_MAX__)
            {
                type = "long";
            }
            kind = "IntegerLiteral";
        }
        yylval = new asgNode(kind, "", value);
        yylval -> type = type;
        return T_NUMERIC_CONSTANT;
    }
    if (t == "identifier") {
        yylval = new asgNode("id", s);
        if(idenTable.find(s) != idenTable.end())
            yylval -> type = idenTable[s] -> type;
        else
        {
            // Todo: Temporary solution
            yylval -> type = "";
            idenTable[s] = yylval;
        }
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
    // %token T_ELLIPSIS
    if (t == "ellipsis") {
        return T_ELLIPSIS;
    }
    if (t == "long") {
        return T_LONG;
    }
    return YYEOF;
}
int main() {
    yyparse();
    llvm::outs() << root->toJson() << "\n";
    root->clear();
    // if(argc > 1)
    // root->print();
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
%token T_ELLIPSIS
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

FuncDef       ::= BType IDENT "(" FuncFParams ")" Block
                | "BType" IDENT "(" FuncFParams ")" ";";
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
            if(it->type != "")
                it->type = "const " + $2->type + " " + it->type;
            else
                it->type = "const " + $2->type;
            if(it->sons.size() > 0)
            {
                auto&& son = it->sons[0];
                if(son->type == "float" && $2->type == "int")
                {
                    son->castKind = "FloatingToIntegral";
                }
                else if(son->type == "int" && $2->type == "float")
                {
                    // move it's sons to new node named "ptr"
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->type = "float";
                    ptr->castKind = "IntegralToFloating";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
                else if(son->type == "long" && $2->type == "int")
                {
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->castKind = "IntegralCast";
                    ptr->type = "int";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
                else if(son->type == "int" && $2->type == "long")
                {
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->castKind = "IntegralCast";
                    ptr->type = "long";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
                else if(son->type == "int" && $2->type == "long long")
                {
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->castKind = "IntegralCast";
                    ptr->type = "long long";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
            }
        }
        delete $2;
    }
    ;
/* VarDecl       ::= BType VarDefList ";"; */
VarDecl: BType VarDefList T_SEMI {
        $$ = $2;
        for(auto&& it: $$->sons)
        {
            if(it->type != "")
                it->type = $1->type + " " + it->type;
            else
                it->type = $1->type;
            if(it->sons.size() > 0)
            {
                auto&& son = it->sons[0];
                if(son->type == "float" && $1->type == "int")
                {
                    son->castKind = "FloatingToIntegral";
                }
                else if(son->type == "int" && $1->type == "float")
                {
                    // move it's sons to new node named "ptr"
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->type = "float";
                    ptr->castKind = "IntegralToFloating";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
                else if(son->type == "long" && $1->type == "int")
                {
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->castKind = "IntegralCast";
                    ptr->type = "int";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
                else if(son->type == "int" && $1->type == "long")
                {
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->castKind = "IntegralCast";
                    ptr->type = "long";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
                else if(son->type == "int" && $1->type == "long long")
                {
                    auto ptr = new asgNode("ImplicitCastExpr");
                    ptr->castKind = "IntegralCast";
                    ptr->type = "long long";
                    for(auto&& iit: it->sons)
                    {
                        ptr->sons.emplace_back(std::move(iit));
                    }
                    it->sons.clear();
                    it->addSon(ptr);
                }
            }
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
        $$->type += "[" + $3->value + "]";
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
        $$->kind = "VarDecl";
        $$->type = "";
        // Add in symbol table
        idenTable[$$->name] = $$;
        delete $2;
    }
    | T_IDENTIFIER ArrayList T_EQUAL InitVal {
        $$ = $1;
        $$->kind = "VarDecl";
        $$->type = "";
        // Add in symbol table
        idenTable[$$->name] = $$;
        delete $2;
        // Todo: For Implicit Type Conversion
        $$->opcode = "=";
        if($4->type == "double")
        {
            auto ptr = new asgNode("ImplicitCastExpr");
            ptr->castKind = "FloatingCast";
            ptr->type = "float";
            ptr->addSon($4);
            $$->addSon(ptr);
        }
        else
        {
            $$->addSon($4);
        }

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
    | STRING_LITERAL {
        $$ = $1;
    }
    ;
/* InitValList   ::= InitVal {"," InitVal}; */
InitValList: InitVal {
        $$ = new asgNode("InitListExpr");
        // $$->type = $1->type;
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

/* FuncDef       ::= BType IDENT "(" FuncFParams ")" Block; 
                | "BType" IDENT "(" FuncFParams ")" ";";
*/
FuncDefPrefix: BType T_IDENTIFIER T_L_PAREN FuncFParams T_R_PAREN{
        $$ = $2;
        $$->type = $1->type + "(" + $4->type + ")";
        $$->funcReturnType = $1->type;
        $$->kind = "FunctionDecl";
        delete $1;
        if ($4 -> kind != "emptyParams") {
            $$->moveSons($4);
        }
        else {
            delete $4;
        }
        // Add in symbol table
        idenTable[$$->name] = $$;
        currentFuncType = $1->type;
    }
    ;
FuncDef: FuncDefPrefix Block {
        $$ = $1;
        $$->addSon($2);
    }
    | FuncDefPrefix T_SEMI {
        $$ = $1;
    }
    ;
/* FuncFParams   ::= [FuncFParam {"," FuncFParam}]; */
/* Todo: Maybe the type is wrong */
FuncFParams: %empty {
        $$ = new asgNode("emptyParams");
    }
    | FuncFParam {
        $$ = new asgNode("ParamVarPreNode");
        $$->addSon($1);
    }
    | FuncFParams T_COMMA FuncFParam {
        $$ = $1;
        $$->addSon($3);
    }
    | FuncFParams T_COMMA T_ELLIPSIS {
        $$ = $1;
        $$->type += ", ...";
    }
    ;
/* FuncFParam    ::= BType IDENT [ParamArrayList]; */
FuncFParam: BType T_IDENTIFIER{
        $$ = $2;
        $$->type = $1->type;
        idenTable[$$->name] = $$;
        delete $1;
        $$->kind = "ParmVarDecl";
    }
    | BType T_IDENTIFIER ParamArrayList {
        $$ = $2;
        $$->type = $1->type + $3->type;
        idenTable[$$->name] = $$;
        delete $1;
        delete $3;
        $$->kind = "ParmVarDecl";
    }
    | T_CONST BType T_IDENTIFIER {
        $$ = $3;
        $$->type = "const " + $2->type;
        idenTable[$$->name] = $$;
        delete $2;
        $$->kind = "ParmVarDecl";
    }
    | T_CONST BType T_IDENTIFIER ParamArrayList {
        $$ = $3;
        $$->type = "const " + $2->type + $4->type;
        idenTable[$$->name] = $$;
        delete $2;
        delete $4;
        $$->kind = "ParmVarDecl";
    }
    ;
/* ParamArrayList::= "[" "]" ArrayList; */
ParamArrayList: T_L_SQUARE T_R_SQUARE ArrayList {
        $$ = $3;
        $$->type = " *" + $$->type;
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
        if (($1->type == "int" &&  $3->type == "float") || ($1->type == "float" &&  $3->type == "int")) {
        // if (false) {
            // auto ptr = new asgNode("ImplicitCastExpr");
            // ptr->castKind = "IntegralToFloating";
            // ptr->addSon($3);
            // $$->addSon(ptr);
            $$->type = $1->type;
            
            bool l_flag, r_flag, global_flag;
            l_flag = ($1->type == "float");
            r_flag = ($3->type == "float");
            auto tmp = new asgNode("ImplicitCastExpr");
            if (l_flag) {
                // The left is float, the right is int
                tmp->castKind = "IntegralToFloating";
            }
            else {
                // The left is int, the right is float
                tmp->castKind = "FloatingToIntegral";
            }
            tmp->addSon($3);
            $$->addSon(tmp);
        }
        else if (($1->type == "int" &&  $3->type == "double") || ($1->type == "double" &&  $3->type == "int")) {
        // if (false) {
            // auto ptr = new asgNode("ImplicitCastExpr");
            // ptr->castKind = "IntegralToFloating";
            // ptr->addSon($3);
            // $$->addSon(ptr);
            $$->type = $1->type;
            
            bool l_flag, r_flag, global_flag;
            l_flag = ($1->type == "double");
            r_flag = ($3->type == "double");
            auto tmp = new asgNode("ImplicitCastExpr");
            if (l_flag) {
                // The left is float, the right is int
                tmp->castKind = "IntegralToFloating";
            }
            else {
                // The left is int, the right is float
                tmp->castKind = "FloatingToIntegral";
            }
            tmp->addSon($3);
            $$->addSon(tmp);
        }
        else {
            $$->addSon($3);
        }
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
        forceImplicitCast($2, currentFuncType, $$);
        // $$->addSon($2);
        // Todo: Implicit conversion
    }
    | T_RETURN T_SEMI {
        $$ = new asgNode("ReturnStmt");
    }
    | T_DO MatchedStmt T_WHILE T_L_PAREN Exp T_R_PAREN T_SEMI {
        $$ = new asgNode("DoStmt");
        $$->addSon($2);
        $$->addSon($5);
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
        $1->type = idenTable[$$->name]->type;
        auto type = $1->type;
        int position = 0;
        // Correct the type of the LVal when it is an array
        for(auto &&it : $2->type)
        {
            // std::cout << "Debug: " << it << std::endl;
            if(it == '[')
            {
                if((position = type.find_last_of("[")) == std::string::npos)
                {
                    // std::cout << "Debug Depointer2: " <<position << std::endl; 
                    position = type.find_last_of("*");
                    type = type.substr(0, position - 1);
                }
                else
                {
                    // std::cout << "Debug Depointer3: " <<position << std::endl; 
                    type = type.substr(0, position);
                }
            }
        }
        // while((position=$2->type.find("[",position)) != std::string::npos)
        // {
        //     std::cout << "Debug Depointer1: " <<position << std::endl; 
        //     if((position = $1->type.find_last_of("[")) == std::string::npos)
        //     {
        //         std::cout << "Debug Depointer2: " <<position << std::endl; 
        //         position = $1->type.find_last_of("*");
        //         $1->type = $1->type.substr(0, position);
        //     }
        //     else
        //     {
        //         std::cout << "Debug Depointer3: " <<position << std::endl; 
        //         $1->type = $1->type.substr(0, position);
        //     }
        // }
        if($2->type != "")
        {
            asgNode* preNode = nullptr;
            for(auto&& it = $2->sons.rbegin(); it != $2->sons.rend(); ++it)
            {
                auto ptr_1 = new asgNode("ArraySubscriptExpr");
                auto ptr_2 = new asgNode("ImplicitCastExpr");

                ptr_1->type = idenTable[$1->name]->type;
                ptr_2->castKind = "ArrayToPointerDecay";

                ptr_1->addSon(ptr_2);
                // //Move it to ptr_1's Sons
                ptr_1->sons.emplace_back(std::move(*it));;

                if(preNode == nullptr)
                {
                    // The first Node
                    $$ = ptr_1;
                    $$->type = type;
                }
                else
                {
                    preNode->addSon(ptr_1);
                }
                preNode = ptr_2;
            }
            $1->kind = "DeclRefExpr";
            preNode->addSon($1);
        }
        else
        {
            $$->kind = "DeclRefExpr";
        }
    }
    ;
/* PrimaryExp    ::= "(" Exp ")" | LVal | Number; */
PrimaryExp: T_L_PAREN Exp T_R_PAREN {
        // $$ = $2;
        $$ = new asgNode("ParenExpr");
        $$->addSon($2);
        if($2->kind == "ImplicitCastExpr")
        {
            $$->kind = "ImplicitCastExpr";
            $2->kind = "ParenExpr";
        }
        $$->type = $2->type;
    }
    | LVal {
        $$ = new asgNode("ImplicitCastExpr");
        $$->addSon($1);
        $$->castKind = "LValueToRValue";
        $$->type = $1->type;
    }
    | Number {
        $$ = $1;
    }
    ;
/* Number        ::= INT_CONST; */
Number: T_NUMERIC_CONSTANT {
        $$ = $1;
        // if($$->type == "int")
        // {
        //     $$->kind = "IntegerLiteral";
        // }
        // else
        // {
        //     $$->kind = "FloatingLiteral";
        // }
    }
    ;

  /* %prec UMINUS => 将该产生式的优先级调整为 UMINUS
  如：T_MINUS Expr %prec UMINUS */

/* UnaryExp      ::= PrimaryExp | IDENT "(" FuncRParams ")" | ("+" | "-" | "!") UnaryExp; */
UnaryExp: PrimaryExp {
        $$ = $1;
    }
    | T_IDENTIFIER T_L_PAREN FuncRParams T_R_PAREN {
        $$ = new asgNode("CallExpr");

        // Implicit conversion Node
        auto ptr_i = new asgNode("ImplicitCastExpr");
        ptr_i->castKind = "FunctionToPointerDecay";
        $$->addSon(ptr_i);
        int idx = 0;
        if($3->castKind == "NoOp")
        {
            $$->moveSons($3);
        }
        else
        {
            for(auto& it : $3->sons)
            {
                // Cast it into asgNode * type:
                // asgNode* tmp = dynamic_cast<asgNode*>(it);
                if(it-> castKind == "LValueToRValue" && it->type == "float" && it->sons.size() > 0 && it->sons[0]->name == "area_trunc")
                {
                    forceImplicitCast(&(*it), idenTable[$1->name]->sons[idx++]->type, $$);
                }
                else if(it-> castKind == "LValueToRValue" && it->type == "const char" && idenTable[$1->name]->sons[idx++]->type == "int")
                {
                    auto tmp = new asgNode("ImplicitCastExpr");
                    tmp->type = "int";
                    // $$->type = "int";
                    tmp->castKind = "IntegralCast";
                    tmp->addSon(&(*it));
                    $$->addSon(tmp);
                }
                else if(it-> castKind == "LValueToRValue" && it->type == "const float" && idenTable[$1->name]->sons[idx++]->type == "int")
                {
                    auto tmp = new asgNode("ImplicitCastExpr");
                    tmp->type = "int";
                    // $$->type = "int";
                    tmp->castKind = "FloatingToIntegral";
                    tmp->addSon(&(*it));
                    $$->addSon(tmp);
                }
                else if(it-> castKind == "LValueToRValue" && it->type == "float" && idx < idenTable[$1->name]->sons.size() &&idenTable[$1->name]->sons[idx++]->type == "int")
                {
                    auto tmp = new asgNode("ImplicitCastExpr");
                    tmp->type = "int";
                    // $$->type = "int";
                    tmp->castKind = "FloatingToIntegral";
                    tmp->addSon(&(*it));
                    $$->addSon(tmp);
                    // std::cout << "JSDKf" << std::endl;
                }
                else
                {
                    idx++;
                    $$->addSon(&(*it));
                }
            }
        }

        // DeclRefExpr Node
        $1->kind = "DeclRefExpr";
        $1->type = idenTable[$1->name]->type;
        ptr_i->addSon($1);

        if($1->type != "")
        {
            if($1->type[0] == 'f')
                $$->type = "float";
            else if($1->type[0] == 'i')
                $$->type = "int";
        }
        ptr_i->type =  idenTable[$1->name]->funcReturnType;
        $$->type = ptr_i->type;

        // Todo: Fix type of ImplicitCastExpr
    }
    | T_PLUS UnaryExp %prec U_PLUS {
        $$ = new asgNode("UnaryOperator");
        $$->opcode = "+";
        $$->type = $2->type;
        $$->addSon($2);
    }
    | T_MINUS UnaryExp %prec U_MINUS {
        $$ = new asgNode("UnaryOperator");
        $$->opcode = "-";
        $$->type = $2->type;
        $$->addSon($2);
    }
    | T_EXCLAIM UnaryExp %prec U_N {
        $$ = new asgNode("UnaryOperator");
        $$->opcode = "!";
        $$->type = $2->type;
        $$->addSon($2);
    }
    ;
/* FuncRParams   ::= [Exp {"," Exp}]; */
FuncRParams: Exp {
        $$ = new asgNode("FuncRParamsPreNode");
        $$->addSon($1);
    }
    | FuncRParams T_COMMA Exp {
        $$ = $1;
        $$->addSon($3);
    }
    | %empty {
        $$ = new asgNode("FuncRParamsPreNode");
    }
    | STRING_LITERAL {
        $$ = new asgNode("ImplicitCastExpr");
        $$->castKind = "NoOp";
        auto ptr_bdg = new asgNode("ImplicitCastExpr");
        $$->castKind = "NoOp";
        auto ptr = new asgNode("ImplicitCastExpr");
        ptr->castKind = "ArrayToPointerDecay";
        $$->addSon(ptr_bdg);
        ptr_bdg->addSon(ptr);
        ptr->addSon($1);
        // $$->addSon($1);
    }
    ;
/* MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp; */
MulExp: UnaryExp {
        $$ = $1;
    }
    | MulExp T_STAR UnaryExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "*";
        binaryImplicitCast($1, $3, $$);
    }
    | MulExp T_SLASH UnaryExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "/";
        binaryImplicitCast($1, $3, $$);
    }
    | MulExp T_PERCENT UnaryExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "%";
        binaryImplicitCast($1, $3, $$);
    }
    ;
/* AddExp        ::= MulExp | AddExp ("+" | "-") MulExp; */
AddExp: MulExp {
        $$ = $1;
    }
    | AddExp T_PLUS MulExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "+";
        binaryImplicitCast($1, $3, $$);
    }
    | AddExp T_MINUS MulExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "-";
        binaryImplicitCast($1, $3, $$);
    }
    ;
/* RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp; */
RelExp: AddExp {
        $$ = $1;
    }
    | RelExp T_LESS AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "<";
        binaryImplicitCast($1, $3, $$);
    }
    | RelExp T_GREATER AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = ">";
        binaryImplicitCast($1, $3, $$);
    }
    | RelExp T_LESSEQUAL AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "<=";
        binaryImplicitCast($1, $3, $$);
    }
    | RelExp T_GREATEREQUAL AddExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = ">=";
        binaryImplicitCast($1, $3, $$);
    }
    ;
/* EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp; */
EqExp: RelExp {
        $$ = $1;
    }
    | EqExp T_EQUALEQUAL RelExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "==";
        $$->type = "int";
        $$->addSon($1);
        $$->addSon($3);
    }
    | EqExp T_EXCLAIMEQUAL RelExp {
        $$ = new asgNode("BinaryOperator");
        $$->opcode = "!=";
        $$->type = "int";
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
        $$->type = "int";
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
        $$->type = "int";
        $$->addSon($1);
        $$->addSon($3);
        // binaryImplicitCast($1, $3, $$);
    }
    ;

STRING_LITERAL: T_STRING_LITERAL {
        $$ = $1;
        int size = countChar($$->value.substr(1, $$->value.size() - 2)) + 1;
        $$->type = "char [" + std::to_string(size) +  "]";
    }
    | STRING_LITERAL T_STRING_LITERAL {
        // connect the string
        $$ = $1;
        int size_old = countChar($$->value.substr(1, $$->value.size() - 2)) + 1;
        int size_new = countChar($2->value.substr(1, $2->value.size() - 2)) + 1;
        int index_old = $$->value.size();
        int index_new = $2->value.size();
        $$->value = $$->value.substr(0, index_old - 1) + $2->value.substr(1, index_new - 1);
        $$->type = "char [" + std::to_string(size_old + size_new) +  "]";
    }
    ;

%%