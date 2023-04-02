// Forward declaration of some structs
struct Type;
struct Decl;
struct Expr;
struct Stmt;

// Structs
struct CompUnit {
    std::vector<Decl*> decls; // Declarations in the compilation unit
};

struct BType {
    enum { kInt, kFloat, kDouble, kChar, kVoid } kind; // Basic type kind
};

struct ConstInitVal {
    Expr* expr; // Constant initialization expression
};

struct ConstDecl {
    std::string name; // Constant name
    Type* type; // Constant type
    ConstInitVal* init; // Constant initialization value (optional)
};

struct ConstDef {
    ConstDecl* decl; // Constant declaration
};

struct VarDecl {
    std::string name; // Variable name
    Type* type; // Variable type
};

struct VarDef {
    VarDecl* decl; // Variable declaration
    Expr* init; // Variable initialization value (optional)
};

struct FuncFParam {
    std::string name; // Parameter name
    Type* type; // Parameter type
};

struct FuncFParams {
    std::vector<FuncFParam*> params; // Function parameters
};

struct FuncType {
    Type* returnType; // Function return type
    FuncFParams* params; // Function parameters
};

struct FuncDef {
    std::string name; // Function name
    FuncType* type; // Function type
    Stmt* body; // Function body
};

struct BlockItem {
    enum { kDecl, kStmt } kind; // Block item kind
    union {
        Decl* decl; // Declaration (if kind == kDecl)
        Stmt* stmt; // Statement (if kind == kStmt)
    };
};

struct Block {
    std::vector<BlockItem*> items; // Block items (declarations and statements)
};

struct LVal {
    enum { kVar, kArrElem, kDeref, kMember } kind; // Left value kind
    union {
        Decl* var; // Variable (if kind == kVar)
        struct {
            LVal* array; // Array expression
            Expr* index; // Index expression
        } arrElem; // Array element (if kind == kArrElem)
        Expr* deref; // Dereference expression (if kind == kDeref)
        struct {
            LVal* obj; // Object expression
            std::string member; // Member name
        } member; // Member expression (if kind == kMember)
    };
};

struct PrimaryExp {
    enum { kId, kNumber, kStr } kind; // Primary expression kind
    union {
        std::string id; // Identifier (if kind == kId)
        std::int64_t number; // Number (if kind == kNumber)
        std::string str; // String (if kind == kStr)
    };
};

struct UnaryOp {
    enum { kAddr, kDeref, kPlus, kMinus, kNot } kind; // Unary operator kind
};

struct UnaryExp {
    UnaryOp* op; // Unary operator
    Expr* subExp; // Subexpression
};

struct MulExp {
    enum { kMul, kDiv, kMod } op; // Multiplicative operator
    Expr* left; // Left operand
    Expr* right; // Right operand
};

struct AddExp {
    enum { kAdd, kSub } op; // Additive operator
    Expr* left; // Left operand
    Expr* right; // Right operand
};

struct RelExp {
    enum { kLt, kGt, kLe, k


struct AddExp : public Expr {
    enum { kAdd, kSub } op; // 加减运算符
    Expr *left, *right; // 左右操作数
};

struct RelExp : public Expr {
    enum { kLess, kLessEqual, kGreater, kGreaterEqual } op; // 关系运算符
    Expr *left, *right; // 左右操作数
};

struct EqExp : public Expr {
    enum { kEqual, kNotEqual } op; // 相等性运算符
    Expr *left, *right; // 左右操作数
};

struct LAndExp : public Expr {
    Expr *left, *right; // 左右操作数
};

struct LOrExp : public Expr {
    Expr *left, *right; // 左右操作数
};

struct ConstExp : public Expr {
    Expr *expr; // 常量表达式
};

struct CompUnit {
    std::vector<Decl*> declarations; // 编译单元中的声明列表
};

struct Decl {
    std::string name; // 声明的名称
    Type type; // 声明的类型
};

struct ConstDecl : public Decl {
    // 该常量声明不需要特殊的成员
};

struct BType : public Type {
    enum { kInt, kChar } kind; // 基本类型的种类
};

struct ConstDef : public Decl {
    ConstInitVal* initVal; // 常量的初始值
};

struct ConstInitVal {
    Expr* expr; // 常量的表达式形式的初始值
};

struct VarDecl : public Decl {
    // 该变量声明不需要特殊的成员
};

struct VarDef : public Decl {
    InitVal* initVal; // 变量的初始值
};

struct InitVal {
    Expr* expr; // 变量的表达式形式的初始值
};

struct FuncDef : public Decl {
    FuncType* funcType; // 函数的类型
    FuncFParams* params; // 函数的形参表
    Block* body; // 函数的语句块
};

struct FuncType : public Type {
    Type* returnType; // 函数的返回类型
};

struct FuncFParams {
    std::vector<VarDecl*> params; // 函数形参表中的参数列表
};

struct FuncFParam : public VarDecl {
    // 该函数形参不需要特殊的成员
};

struct Block {
    std::vector<BlockItem*> items; // 语句块中的语句列表
};

struct BlockItem {
    Stmt* stmt; // 语句块项中的语句
};

struct Stmt {
    enum { kExpr, kBlock, kIf, kWhile, kReturn } kind; // 语句的种类
    union {
        Expr* exprStmt; // 表达式语句
        Block* blockStmt; // 语句块
        IfStmt* ifStmt; // If语句
        WhileStmt* whileStmt; // While语句
        Expr* returnStmt; // Return语句
    } u;
};

struct IfStmt {
    Expr* condition; // If语句的条件
    Stmt* thenStmt; // If语句的then语句
    Stmt* elseStmt; // If语句的else语句
};

struct WhileStmt {
    Expr* condition; // While语句的条件
    Stmt* body; // While语句的循环体
};

struct LVal {
    enum { kVar, kArray } kind; // 左值的种类
    union {
        std::string varName; // 变量名
        struct {
            LVal* base; // 数组的基地址
            Expr* index; // 数组的下标
        } array;
    } u;
};

struct PrimaryExp {
    enum { kId, kLiteral, kParen } kind; // 基本表达式的种类
    union {
        std::string idName; // 标识符的名称
        Number* literal; // 数字字面量
        Expr* parenExpr; // 括号内的


struct CompUnit;

struct Decl {
  virtual ~Decl() = default;
};

struct ConstDecl : public Decl {
  BType type;
  std::vector<std::pair<std::string, std::vector<int>>> vars; // pair of variable name and its dimensions
  std::vector<ConstInitVal*> vals;
};

struct VarDecl : public Decl {
  BType type;
  std::vector<std::pair<std::string, std::vector<int>>> vars; // pair of variable name and its dimensions
  std::vector<InitVal*> vals;
};

struct FuncDef : public Decl {
  FuncType returnType;
  std::string name;
  std::vector<FuncFParam*> params;
  Block* body;
};

struct FuncFParam {
  BType type;
  std::string name;
  std::vector<int> dimensions;
};

struct BlockItem {
  virtual ~BlockItem() = default;
};

struct DeclBlockItem : public BlockItem {
  Decl* decl;
};

struct StmtBlockItem : public BlockItem {
  Stmt* stmt;
};

struct Block {
  std::vector<BlockItem*> items;
};

struct Stmt {
  virtual ~Stmt() = default;
};

struct AssignStmt : public Stmt {
  LVal* lval;
  Exp* exp;
};

struct ExpStmt : public Stmt {
  Exp* exp;
};

struct BlockStmt : public Stmt {
  Block* block;
};

struct IfStmt : public Stmt {
  Exp* cond;
  Stmt* thenStmt;
  Stmt* elseStmt;
};

struct WhileStmt : public Stmt {
  Exp* cond;
  Stmt* body;
};

struct BreakStmt : public Stmt {};

struct ContinueStmt : public Stmt {};

struct ReturnStmt : public Stmt {
  Exp* exp;
};

struct DoWhileStmt : public Stmt {
  Stmt* body;
  Exp* cond;
};

struct LVal {
  virtual ~LVal() = default;
};

struct VarLVal : public LVal {
  std::string name;
  std::vector<Exp*> indexes;
};

struct Number : public PrimaryExp {
  std::int64_t val;
};

struct FuncCall : public PrimaryExp {
  std::string name;
  std::vector<Exp*> args;
};

struct UnaryExp {
  virtual ~UnaryExp() = default;
};

struct UnaryOp : public UnaryExp {
  std::string op;
  UnaryExp* exp;
};

struct PrimaryExp {
  virtual ~PrimaryExp() = default;
};

struct BinaryExp : public Exp {
  std::string op;
  Exp* left;
  Exp* right;
};

struct MulExp : public Exp {
  UnaryExp* expr;
  std::vector<std::string> ops;
  std::vector<UnaryExp*> exprs;
};

struct AddExp : public Exp {
  MulExp* mulExp;
  std::vector<std::string> ops;
  std::vector<MulExp*> mulExps;
};

struct RelExp : public Exp {
  AddExp* addExp;
  std::vector<std::string> ops;
  std::vector<AddExp*> addExps;
};

struct EqExp : public Exp {
  RelExp* relExp;
  std::vector<std::string> ops;
  std::vector<RelExp*> relExps;
};

struct LAndExp : public Exp {
  EqExp* eqExp;
  std::vector<EqExp*> eqExps;
};

struct LOrExp : public Exp {
  LAndExp* landExp;
  std::vector<LAndExp*> landExps;
};

struct ConstExp : public Exp {
  Exp* exp
