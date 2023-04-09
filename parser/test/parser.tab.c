/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser.y"

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
    std::cout << "Testing  " << t << " " << s << std::endl;
    if (t == "numeric_constant") {
        auto value = s;
        auto kind = "IntegerLiteral";
        auto type = "int";
        if (s.find('.') != std::string::npos || s.find('p') != std::string::npos || s.find('e') != std::string::npos) 
        {
            auto kind = "FloatingLiteral";
            llvm::StringRef str(value);
            llvm::APFloat apf(0.0);
            llvm::Expected<llvm::APFloatBase::opStatus> returnFlag = apf.convertFromString(str, llvm::APFloat::rmNearestTiesToEven);
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
    llvm::outs() << root->toJson() << "\n";
    root->clear();
    // if(argc > 1)
    // root->print();
    delete root;
    return 0;
}

#line 294 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 2 "parser.y"

    class asgNode;

#line 330 "parser.tab.c"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_COMMA = 258,                 /* T_COMMA  */
    T_SEMI = 259,                  /* T_SEMI  */
    T_L_SQUARE = 260,              /* T_L_SQUARE  */
    T_R_SQUARE = 261,              /* T_R_SQUARE  */
    T_L_BRACE = 262,               /* T_L_BRACE  */
    T_R_BRACE = 263,               /* T_R_BRACE  */
    T_L_PAREN = 264,               /* T_L_PAREN  */
    T_R_PAREN = 265,               /* T_R_PAREN  */
    T_EQUAL = 266,                 /* T_EQUAL  */
    T_PLUS = 267,                  /* T_PLUS  */
    T_MINUS = 268,                 /* T_MINUS  */
    T_EXCLAIM = 269,               /* T_EXCLAIM  */
    T_STAR = 270,                  /* T_STAR  */
    T_SLASH = 271,                 /* T_SLASH  */
    T_PERCENT = 272,               /* T_PERCENT  */
    T_LESS = 273,                  /* T_LESS  */
    T_GREATER = 274,               /* T_GREATER  */
    T_LESSEQUAL = 275,             /* T_LESSEQUAL  */
    T_GREATEREQUAL = 276,          /* T_GREATEREQUAL  */
    T_EQUALEQUAL = 277,            /* T_EQUALEQUAL  */
    T_EXCLAIMEQUAL = 278,          /* T_EXCLAIMEQUAL  */
    T_AMPAMP = 279,                /* T_AMPAMP  */
    T_PIPEPIPE = 280,              /* T_PIPEPIPE  */
    T_INT = 281,                   /* T_INT  */
    T_FLOAT = 282,                 /* T_FLOAT  */
    T_CHAR = 283,                  /* T_CHAR  */
    T_VOID = 284,                  /* T_VOID  */
    T_CONST = 285,                 /* T_CONST  */
    T_IF = 286,                    /* T_IF  */
    T_ELSE = 287,                  /* T_ELSE  */
    T_DO = 288,                    /* T_DO  */
    T_WHILE = 289,                 /* T_WHILE  */
    T_BREAK = 290,                 /* T_BREAK  */
    T_CONTINUE = 291,              /* T_CONTINUE  */
    T_RETURN = 292,                /* T_RETURN  */
    T_NUMERIC_CONSTANT = 293,      /* T_NUMERIC_CONSTANT  */
    T_STRING_LITERAL = 294,        /* T_STRING_LITERAL  */
    T_IDENTIFIER = 295,            /* T_IDENTIFIER  */
    T_LONG = 296,                  /* T_LONG  */
    U_N = 297,                     /* U_N  */
    U_MINUS = 298,                 /* U_MINUS  */
    U_PLUS = 299                   /* U_PLUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef  asgNode*  YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_COMMA = 3,                    /* T_COMMA  */
  YYSYMBOL_T_SEMI = 4,                     /* T_SEMI  */
  YYSYMBOL_T_L_SQUARE = 5,                 /* T_L_SQUARE  */
  YYSYMBOL_T_R_SQUARE = 6,                 /* T_R_SQUARE  */
  YYSYMBOL_T_L_BRACE = 7,                  /* T_L_BRACE  */
  YYSYMBOL_T_R_BRACE = 8,                  /* T_R_BRACE  */
  YYSYMBOL_T_L_PAREN = 9,                  /* T_L_PAREN  */
  YYSYMBOL_T_R_PAREN = 10,                 /* T_R_PAREN  */
  YYSYMBOL_T_EQUAL = 11,                   /* T_EQUAL  */
  YYSYMBOL_T_PLUS = 12,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 13,                   /* T_MINUS  */
  YYSYMBOL_T_EXCLAIM = 14,                 /* T_EXCLAIM  */
  YYSYMBOL_T_STAR = 15,                    /* T_STAR  */
  YYSYMBOL_T_SLASH = 16,                   /* T_SLASH  */
  YYSYMBOL_T_PERCENT = 17,                 /* T_PERCENT  */
  YYSYMBOL_T_LESS = 18,                    /* T_LESS  */
  YYSYMBOL_T_GREATER = 19,                 /* T_GREATER  */
  YYSYMBOL_T_LESSEQUAL = 20,               /* T_LESSEQUAL  */
  YYSYMBOL_T_GREATEREQUAL = 21,            /* T_GREATEREQUAL  */
  YYSYMBOL_T_EQUALEQUAL = 22,              /* T_EQUALEQUAL  */
  YYSYMBOL_T_EXCLAIMEQUAL = 23,            /* T_EXCLAIMEQUAL  */
  YYSYMBOL_T_AMPAMP = 24,                  /* T_AMPAMP  */
  YYSYMBOL_T_PIPEPIPE = 25,                /* T_PIPEPIPE  */
  YYSYMBOL_T_INT = 26,                     /* T_INT  */
  YYSYMBOL_T_FLOAT = 27,                   /* T_FLOAT  */
  YYSYMBOL_T_CHAR = 28,                    /* T_CHAR  */
  YYSYMBOL_T_VOID = 29,                    /* T_VOID  */
  YYSYMBOL_T_CONST = 30,                   /* T_CONST  */
  YYSYMBOL_T_IF = 31,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 32,                    /* T_ELSE  */
  YYSYMBOL_T_DO = 33,                      /* T_DO  */
  YYSYMBOL_T_WHILE = 34,                   /* T_WHILE  */
  YYSYMBOL_T_BREAK = 35,                   /* T_BREAK  */
  YYSYMBOL_T_CONTINUE = 36,                /* T_CONTINUE  */
  YYSYMBOL_T_RETURN = 37,                  /* T_RETURN  */
  YYSYMBOL_T_NUMERIC_CONSTANT = 38,        /* T_NUMERIC_CONSTANT  */
  YYSYMBOL_T_STRING_LITERAL = 39,          /* T_STRING_LITERAL  */
  YYSYMBOL_T_IDENTIFIER = 40,              /* T_IDENTIFIER  */
  YYSYMBOL_T_LONG = 41,                    /* T_LONG  */
  YYSYMBOL_U_N = 42,                       /* U_N  */
  YYSYMBOL_U_MINUS = 43,                   /* U_MINUS  */
  YYSYMBOL_U_PLUS = 44,                    /* U_PLUS  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_Begin = 46,                     /* Begin  */
  YYSYMBOL_CompUnit = 47,                  /* CompUnit  */
  YYSYMBOL_GlobalDecl = 48,                /* GlobalDecl  */
  YYSYMBOL_ConstDecl = 49,                 /* ConstDecl  */
  YYSYMBOL_VarDecl = 50,                   /* VarDecl  */
  YYSYMBOL_BType = 51,                     /* BType  */
  YYSYMBOL_ArrayList = 52,                 /* ArrayList  */
  YYSYMBOL_VarDefList = 53,                /* VarDefList  */
  YYSYMBOL_VarDef = 54,                    /* VarDef  */
  YYSYMBOL_InitVal = 55,                   /* InitVal  */
  YYSYMBOL_InitValList = 56,               /* InitValList  */
  YYSYMBOL_FuncDef = 57,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 58,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 59,                /* FuncFParam  */
  YYSYMBOL_ParamArrayList = 60,            /* ParamArrayList  */
  YYSYMBOL_BlockPrefix = 61,               /* BlockPrefix  */
  YYSYMBOL_Block = 62,                     /* Block  */
  YYSYMBOL_BlockItem = 63,                 /* BlockItem  */
  YYSYMBOL_Stmt = 64,                      /* Stmt  */
  YYSYMBOL_MatchedStmt = 65,               /* MatchedStmt  */
  YYSYMBOL_UnmatchedStmt = 66,             /* UnmatchedStmt  */
  YYSYMBOL_Exp = 67,                       /* Exp  */
  YYSYMBOL_LVal = 68,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 69,                /* PrimaryExp  */
  YYSYMBOL_Number = 70,                    /* Number  */
  YYSYMBOL_UnaryExp = 71,                  /* UnaryExp  */
  YYSYMBOL_FuncRParams = 72,               /* FuncRParams  */
  YYSYMBOL_MulExp = 73,                    /* MulExp  */
  YYSYMBOL_AddExp = 74,                    /* AddExp  */
  YYSYMBOL_RelExp = 75,                    /* RelExp  */
  YYSYMBOL_EqExp = 76,                     /* EqExp  */
  YYSYMBOL_LAndExp = 77,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 78                     /* LOrExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   351,   351,   356,   365,   377,   380,   383,   389,   400,
     410,   414,   418,   422,   426,   430,   438,   441,   451,   455,
     463,   471,   487,   490,   495,   499,   503,   509,   527,   530,
     534,   540,   547,   557,   564,   568,   573,   577,   583,   588,
     593,   598,   601,   616,   622,   625,   628,   631,   637,   642,
     645,   648,   653,   656,   664,   669,   677,   682,   732,   735,
     740,   745,   762,   765,   781,   786,   791,   798,   805,   812,
     817,   820,   826,   832,   840,   843,   849,   857,   860,   866,
     872,   878,   886,   889,   895,   903,   906,   914,   917
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_COMMA", "T_SEMI",
  "T_L_SQUARE", "T_R_SQUARE", "T_L_BRACE", "T_R_BRACE", "T_L_PAREN",
  "T_R_PAREN", "T_EQUAL", "T_PLUS", "T_MINUS", "T_EXCLAIM", "T_STAR",
  "T_SLASH", "T_PERCENT", "T_LESS", "T_GREATER", "T_LESSEQUAL",
  "T_GREATEREQUAL", "T_EQUALEQUAL", "T_EXCLAIMEQUAL", "T_AMPAMP",
  "T_PIPEPIPE", "T_INT", "T_FLOAT", "T_CHAR", "T_VOID", "T_CONST", "T_IF",
  "T_ELSE", "T_DO", "T_WHILE", "T_BREAK", "T_CONTINUE", "T_RETURN",
  "T_NUMERIC_CONSTANT", "T_STRING_LITERAL", "T_IDENTIFIER", "T_LONG",
  "U_N", "U_MINUS", "U_PLUS", "$accept", "Begin", "CompUnit", "GlobalDecl",
  "ConstDecl", "VarDecl", "BType", "ArrayList", "VarDefList", "VarDef",
  "InitVal", "InitValList", "FuncDef", "FuncFParams", "FuncFParam",
  "ParamArrayList", "BlockPrefix", "Block", "BlockItem", "Stmt",
  "MatchedStmt", "UnmatchedStmt", "Exp", "LVal", "PrimaryExp", "Number",
  "UnaryExp", "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp",
  "LAndExp", "LOrExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
#endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     164,   -58,   -58,   -58,   -58,   174,   -32,    47,   164,   -58,
     -58,   -58,   -19,   -58,     5,   -58,   -58,   -58,    59,     8,
     -58,   -58,    28,   174,    11,     5,   -58,   -58,    37,     4,
     -58,   170,   159,   -58,    79,   174,    88,   170,   170,   170,
     170,   -58,    90,    99,   -58,   -58,   -58,   -58,    12,    38,
     193,    33,    82,    83,   159,   -58,   -58,   107,   -58,   -58,
      45,   103,   -58,   109,   -58,   -58,   -58,   170,   104,   -58,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   -58,    22,   -58,   -58,   -58,   111,   115,
     126,   120,   138,   149,   -58,   -58,     5,   -58,   -58,   -58,
     -58,   -58,   151,   145,   -58,   -58,   -58,   -58,    14,   -58,
     -58,   -58,    12,    12,    38,    38,    38,    38,   193,   193,
      33,    82,   159,   -58,   104,   170,     6,   170,   -58,   -58,
     -58,   153,   -58,   170,   170,   -58,   -58,   150,   156,   161,
     160,   -58,   155,   -58,   114,   170,   142,     6,   -58,   -58,
     146,   167,   171,   -58,   114,     6,   170,   -58,   -58,   154,
     175,     6,   184,   -58
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    10,    15,    11,    13,     0,    12,     0,     2,     4,
       5,     6,     0,     7,     0,    14,     1,     3,    16,     0,
      18,    16,     0,    28,    20,     0,     9,     8,     0,     0,
      29,     0,     0,    19,    31,     0,     0,     0,     0,     0,
       0,    61,    16,     0,    59,    62,    60,    70,    74,    77,
      82,    85,    87,    56,    26,    21,    22,     0,    32,    30,
       0,     0,    27,     0,    64,    65,    66,    69,    57,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,     0,    16,    45,    37,     0,     0,
       0,     0,     0,     0,    38,    39,     0,    46,    34,    40,
      41,    42,     0,    59,    36,    35,    58,    67,     0,    71,
      72,    73,    75,    76,    78,    79,    80,    81,    83,    84,
      86,    88,     0,    23,    33,     0,     0,     0,    49,    50,
      52,     0,    44,     0,     0,    63,    25,     0,     0,     0,
       0,    51,     0,    68,     0,     0,     0,     0,    43,    54,
      41,     0,     0,    48,     0,     0,     0,    47,    55,     0,
       0,     0,     0,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,   -58,   187,     0,    32,     3,   -37,   182,   173,
     -52,   -58,   -58,   -58,   169,   -58,   -58,   185,   148,    62,
      20,    53,   -31,   -57,   -58,   -58,    -5,   -58,    15,   141,
      21,   139,   140,   -58
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    11,    12,    24,    19,    20,
      55,    84,    13,    29,    30,    58,    61,    97,    98,    99,
     100,   101,   102,    44,    45,    46,    47,   108,    48,    49,
      50,    51,    52,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      43,    56,    83,   103,   103,    68,    63,    35,    14,    15,
      86,    25,    26,    60,    36,    37,    31,   134,    38,    39,
      40,    18,    32,    56,   135,   122,    28,    70,    71,    72,
     123,    25,    27,    64,    65,    66,   107,   138,    28,    89,
      90,    91,    92,    93,    41,    21,    42,    16,   124,    86,
      73,    74,    60,    87,    37,    79,    80,    38,    39,    40,
      94,    94,   131,    96,    96,   109,   110,   111,    23,   103,
     136,     1,     2,     3,     4,     5,    88,    34,    89,    90,
      91,    92,    93,    41,    57,    42,     6,   103,   112,   113,
     103,    56,    95,    95,   137,    60,   140,   103,   103,    67,
     118,   119,   142,   143,   103,    69,    81,    86,    82,    31,
      60,   104,    37,    85,   151,    38,    39,    40,    86,   106,
     125,    60,   126,    37,   128,   160,    38,    39,    40,     1,
       2,     3,     4,     5,    88,   127,    89,    90,    91,    92,
      93,    41,   129,    42,     6,    88,   139,    89,    90,    91,
      92,    93,    41,   130,    42,   132,   133,   141,    37,   148,
     144,    38,    39,    40,   150,   145,    54,   153,    37,   146,
     147,    38,    39,    40,   157,   159,   152,   155,   154,    37,
     156,   157,    38,    39,    40,   162,   161,    41,   163,    42,
       1,     2,     3,     4,     5,    17,    22,    41,    33,    42,
       1,     2,     3,     4,    59,     6,   149,   158,    41,   105,
      42,    75,    76,    77,    78,     6,   114,   115,   116,   117,
     120,    62,   121
};

static const yytype_uint8 yycheck[] =
{
      31,    32,    54,    60,    61,    42,    37,     3,     5,    41,
       4,     3,     4,     7,    10,     9,     5,     3,    12,    13,
      14,    40,    11,    54,    10,     3,    23,    15,    16,    17,
       8,     3,     4,    38,    39,    40,    67,    31,    35,    33,
      34,    35,    36,    37,    38,    40,    40,     0,    85,     4,
      12,    13,     7,     8,     9,    22,    23,    12,    13,    14,
      60,    61,    93,    60,    61,    70,    71,    72,     9,   126,
     122,    26,    27,    28,    29,    30,    31,    40,    33,    34,
      35,    36,    37,    38,     5,    40,    41,   144,    73,    74,
     147,   122,    60,    61,   125,     7,   127,   154,   155,     9,
      79,    80,   133,   134,   161,     6,    24,     4,    25,     5,
       7,     8,     9,     6,   145,    12,    13,    14,     4,    10,
       9,     7,     7,     9,     4,   156,    12,    13,    14,    26,
      27,    28,    29,    30,    31,     9,    33,    34,    35,    36,
      37,    38,     4,    40,    41,    31,   126,    33,    34,    35,
      36,    37,    38,     4,    40,     4,    11,     4,     9,     4,
      10,    12,    13,    14,   144,     9,     7,   147,     9,     8,
      10,    12,    13,    14,   154,   155,    34,    10,    32,     9,
       9,   161,    12,    13,    14,    10,    32,    38,     4,    40,
      26,    27,    28,    29,    30,     8,    14,    38,    25,    40,
      26,    27,    28,    29,    35,    41,   144,   154,    38,    61,
      40,    18,    19,    20,    21,    41,    75,    76,    77,    78,
      81,    36,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    28,    29,    30,    41,    46,    47,    48,
      49,    50,    51,    57,    51,    41,     0,    48,    40,    53,
      54,    40,    53,     9,    52,     3,     4,     4,    51,    58,
      59,     5,    11,    54,    40,     3,    10,     9,    12,    13,
      14,    38,    40,    67,    68,    69,    70,    71,    73,    74,
      75,    76,    77,    78,     7,    55,    67,     5,    60,    59,
       7,    61,    62,    67,    71,    71,    71,     9,    52,     6,
      15,    16,    17,    12,    13,    18,    19,    20,    21,    22,
      23,    24,    25,    55,    56,     6,     4,     8,    31,    33,
      34,    35,    36,    37,    49,    50,    51,    62,    63,    64,
      65,    66,    67,    68,     8,    63,    10,    67,    72,    71,
      71,    71,    73,    73,    74,    74,    74,    74,    75,    75,
      76,    77,     3,     8,    52,     9,     7,     9,     4,     4,
       4,    67,     4,    11,     3,    10,    55,    67,    31,    65,
      67,     4,    67,    67,    10,     9,     8,    10,     4,    64,
      65,    67,    34,    65,    32,    10,     9,    65,    66,    65,
      67,    32,    10,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    50,
      51,    51,    51,    51,    51,    51,    52,    52,    53,    53,
      54,    54,    55,    55,    56,    56,    56,    57,    58,    58,
      58,    59,    59,    60,    61,    61,    62,    62,    63,    63,
      63,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    67,    68,    69,    69,
      69,    70,    71,    71,    71,    71,    71,    72,    72,    72,
      73,    73,    73,    73,    74,    74,    74,    75,    75,    75,
      75,    75,    76,    76,    76,    77,    77,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     4,     3,
       1,     1,     1,     1,     2,     1,     0,     4,     1,     3,
       2,     4,     1,     3,     1,     3,     0,     6,     0,     1,
       3,     2,     3,     3,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     4,     2,     1,     1,     7,     5,     2,
       2,     3,     2,     9,     5,     7,     1,     2,     3,     1,
       1,     1,     1,     4,     2,     2,     2,     1,     3,     0,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Begin: CompUnit  */
#line 351 "parser.y"
                {
        root = yyvsp[0];
    }
#line 1579 "parser.tab.c"
    break;

  case 3: /* CompUnit: CompUnit GlobalDecl  */
#line 356 "parser.y"
                              {
    yyval = yyvsp[-1];
    if (yyvsp[0]->kind == "VarDeclPreNode") {
        yyval->moveSons(yyvsp[0]);
    }
    else {
        yyval->addSon(yyvsp[0]);
    }
    }
#line 1593 "parser.tab.c"
    break;

  case 4: /* CompUnit: GlobalDecl  */
#line 365 "parser.y"
                 {
        yyval = new asgNode("TranslationUnitDecl");
        if (yyvsp[0]->kind == "VarDeclPreNode") {
            yyval->moveSons(yyvsp[0]);
        }
        else {
            yyval->addSon(yyvsp[0]);
        }
    }
#line 1607 "parser.tab.c"
    break;

  case 5: /* GlobalDecl: ConstDecl  */
#line 377 "parser.y"
                     {
        yyval = yyvsp[0];
    }
#line 1615 "parser.tab.c"
    break;

  case 6: /* GlobalDecl: VarDecl  */
#line 380 "parser.y"
              {
        yyval = yyvsp[0];
    }
#line 1623 "parser.tab.c"
    break;

  case 7: /* GlobalDecl: FuncDef  */
#line 383 "parser.y"
              {
        yyval= yyvsp[0];
    }
#line 1631 "parser.tab.c"
    break;

  case 8: /* ConstDecl: T_CONST BType VarDefList T_SEMI  */
#line 390 "parser.y"
    {
        yyval = yyvsp[-1];
        for(auto&& it: yyval->sons)
        {
            it->type = "const " + yyvsp[-2]->type + " " + it->type;
        }
        delete yyvsp[-2];
    }
#line 1644 "parser.tab.c"
    break;

  case 9: /* VarDecl: BType VarDefList T_SEMI  */
#line 400 "parser.y"
                                 {
        yyval = yyvsp[-1];
        for(auto&& it: yyval->sons)
        {
            it->type = yyvsp[-2]->type + " " + it->type;
        }
        delete yyvsp[-2];
    }
#line 1657 "parser.tab.c"
    break;

  case 10: /* BType: T_INT  */
#line 410 "parser.y"
            {
        yyval = new asgNode();
        yyval->type = "int";
    }
#line 1666 "parser.tab.c"
    break;

  case 11: /* BType: T_CHAR  */
#line 414 "parser.y"
             {
        yyval = new asgNode();
        yyval->type = "char";
    }
#line 1675 "parser.tab.c"
    break;

  case 12: /* BType: T_LONG  */
#line 418 "parser.y"
             {
        yyval = new asgNode();
        yyval->type = "long";
    }
#line 1684 "parser.tab.c"
    break;

  case 13: /* BType: T_VOID  */
#line 422 "parser.y"
             {
        yyval = new asgNode();
        yyval->type = "void";
    }
#line 1693 "parser.tab.c"
    break;

  case 14: /* BType: T_LONG T_LONG  */
#line 426 "parser.y"
                    {
        yyval = new asgNode();
        yyval->type = "long long";
    }
#line 1702 "parser.tab.c"
    break;

  case 15: /* BType: T_FLOAT  */
#line 430 "parser.y"
              {
        yyval = new asgNode();
        yyval->type = "float";
    }
#line 1711 "parser.tab.c"
    break;

  case 16: /* ArrayList: %empty  */
#line 438 "parser.y"
                  {
        yyval = new asgNode("ArrayDecl");
    }
#line 1719 "parser.tab.c"
    break;

  case 17: /* ArrayList: ArrayList T_L_SQUARE Exp T_R_SQUARE  */
#line 441 "parser.y"
                                          {
        yyval = yyvsp[-3];
        yyval->addSon(yyvsp[-1]);
        yyval->type += "[" + yyvsp[-1]->value + "]";
        //cal the $ 3 type
    }
#line 1730 "parser.tab.c"
    break;

  case 18: /* VarDefList: VarDef  */
#line 451 "parser.y"
                   {
        yyval = new asgNode("VarDeclPreNode");
        yyval->addSon(yyvsp[0]);
    }
#line 1739 "parser.tab.c"
    break;

  case 19: /* VarDefList: VarDefList T_COMMA VarDef  */
#line 455 "parser.y"
                                {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1748 "parser.tab.c"
    break;

  case 20: /* VarDef: T_IDENTIFIER ArrayList  */
#line 463 "parser.y"
                               {
        yyval = yyvsp[-1];
        yyval->type = yyvsp[0]->type;
        yyval->kind = "VarDecl";
        // Add in symbol table
        idenTable[yyval->name] = yyval;
        delete yyvsp[0];
    }
#line 1761 "parser.tab.c"
    break;

  case 21: /* VarDef: T_IDENTIFIER ArrayList T_EQUAL InitVal  */
#line 471 "parser.y"
                                             {
        yyval = yyvsp[-3];
        yyval->type = yyvsp[-2]->type;
        yyval->kind = "VarDecl";
        // Add in symbol table
        idenTable[yyval->name] = yyval;
        delete yyvsp[-2];
        // Todo: For Implicit Type Conversion
        yyval->opcode = "=";
        yyval->addSon(yyvsp[0]);

    }
#line 1778 "parser.tab.c"
    break;

  case 22: /* InitVal: Exp  */
#line 487 "parser.y"
             {
        yyval = yyvsp[0];
    }
#line 1786 "parser.tab.c"
    break;

  case 23: /* InitVal: T_L_BRACE InitValList T_R_BRACE  */
#line 490 "parser.y"
                                      {
        yyval = yyvsp[-1];
    }
#line 1794 "parser.tab.c"
    break;

  case 24: /* InitValList: InitVal  */
#line 495 "parser.y"
                     {
        yyval = new asgNode("InitListExpr");
        yyval->addSon(yyvsp[0]);
    }
#line 1803 "parser.tab.c"
    break;

  case 25: /* InitValList: InitValList T_COMMA InitVal  */
#line 499 "parser.y"
                                  {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1812 "parser.tab.c"
    break;

  case 26: /* InitValList: %empty  */
#line 503 "parser.y"
             {
        yyval = new asgNode("InitListExpr");
    }
#line 1820 "parser.tab.c"
    break;

  case 27: /* FuncDef: BType T_IDENTIFIER T_L_PAREN FuncFParams T_R_PAREN Block  */
#line 509 "parser.y"
                                                                  {
        yyval = yyvsp[-4];
        yyval->type = yyvsp[-5]->type + "(" + yyvsp[-2]->type + ")";
        yyval->kind = "FunctionDecl";
        delete yyvsp[-5];
        if (yyvsp[-2] -> kind != "emptyParams") {
            yyval->moveSons(yyvsp[-2]);
        }
        else {
            delete yyvsp[-2];
        }
        yyval->addSon(yyvsp[0]);
        // Add in symbol table
        idenTable[yyval->name] = yyval;
    }
#line 1840 "parser.tab.c"
    break;

  case 28: /* FuncFParams: %empty  */
#line 527 "parser.y"
                    {
        yyval = new asgNode("emptyParams");
    }
#line 1848 "parser.tab.c"
    break;

  case 29: /* FuncFParams: FuncFParam  */
#line 530 "parser.y"
                 {
        yyval = new asgNode("ParamVarPreNode");
        yyval->addSon(yyvsp[0]);
    }
#line 1857 "parser.tab.c"
    break;

  case 30: /* FuncFParams: FuncFParams T_COMMA FuncFParam  */
#line 534 "parser.y"
                                     {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1866 "parser.tab.c"
    break;

  case 31: /* FuncFParam: BType T_IDENTIFIER  */
#line 540 "parser.y"
                              {
        yyval = yyvsp[0];
        yyval->type = yyvsp[-1]->type;
        idenTable[yyval->name] = yyval;
        delete yyvsp[-1];
        yyval->kind = "ParmVarDecl";
    }
#line 1878 "parser.tab.c"
    break;

  case 32: /* FuncFParam: BType T_IDENTIFIER ParamArrayList  */
#line 547 "parser.y"
                                        {
        yyval = yyvsp[-1];
        yyval->type = yyvsp[-2]->type + yyvsp[0]->type;
        idenTable[yyval->name] = yyval;
        delete yyvsp[-2];
        delete yyvsp[0];
        yyval->kind = "ParmVarDecl";
    }
#line 1891 "parser.tab.c"
    break;

  case 33: /* ParamArrayList: T_L_SQUARE T_R_SQUARE ArrayList  */
#line 557 "parser.y"
                                                {
        yyval = yyvsp[0];
        yyval->type = "[]" + yyval->type;
    }
#line 1900 "parser.tab.c"
    break;

  case 34: /* BlockPrefix: T_L_BRACE BlockItem  */
#line 564 "parser.y"
                                {
        yyval = new asgNode("CompoundStmt");
        yyval->addSon(yyvsp[0]);
    }
#line 1909 "parser.tab.c"
    break;

  case 35: /* BlockPrefix: BlockPrefix BlockItem  */
#line 568 "parser.y"
                            {
        yyval = yyvsp[-1];
        yyval->addSon(yyvsp[0]);
    }
#line 1918 "parser.tab.c"
    break;

  case 36: /* Block: BlockPrefix T_R_BRACE  */
#line 573 "parser.y"
                             {
        yyval = yyvsp[-1];
        yyval->kind = "CompoundStmt";
    }
#line 1927 "parser.tab.c"
    break;

  case 37: /* Block: T_L_BRACE T_R_BRACE  */
#line 577 "parser.y"
                          {
        auto ptr = new asgNode("CompoundStmt");
        yyval = ptr;
    }
#line 1936 "parser.tab.c"
    break;

  case 38: /* BlockItem: ConstDecl  */
#line 583 "parser.y"
                     {
        yyval = new asgNode("DeclStmt");
        // Move sons because we use a declprenode
        yyval->moveSons(yyvsp[0]);
    }
#line 1946 "parser.tab.c"
    break;

  case 39: /* BlockItem: VarDecl  */
#line 588 "parser.y"
              {
        yyval = new asgNode("DeclStmt");
        // Move sons because we use a declprenode
        yyval->moveSons(yyvsp[0]);
    }
#line 1956 "parser.tab.c"
    break;

  case 40: /* BlockItem: Stmt  */
#line 593 "parser.y"
           {
        yyval = yyvsp[0];
    }
#line 1964 "parser.tab.c"
    break;

  case 41: /* Stmt: MatchedStmt  */
#line 598 "parser.y"
                  {
        yyval = yyvsp[0];
    }
#line 1972 "parser.tab.c"
    break;

  case 42: /* Stmt: UnmatchedStmt  */
#line 601 "parser.y"
                    {
        yyval = yyvsp[0];
    }
#line 1980 "parser.tab.c"
    break;

  case 43: /* MatchedStmt: LVal T_EQUAL Exp T_SEMI  */
#line 616 "parser.y"
                                     {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "=";
        yyval->addSon(yyvsp[-3]);
        yyval->addSon(yyvsp[-1]);
    }
#line 1991 "parser.tab.c"
    break;

  case 44: /* MatchedStmt: Exp T_SEMI  */
#line 622 "parser.y"
                 {
        yyval = yyvsp[-1];
    }
#line 1999 "parser.tab.c"
    break;

  case 45: /* MatchedStmt: T_SEMI  */
#line 625 "parser.y"
             {
        yyval = new asgNode("NullStmt");
    }
#line 2007 "parser.tab.c"
    break;

  case 46: /* MatchedStmt: Block  */
#line 628 "parser.y"
            {
        yyval = yyvsp[0];
    }
#line 2015 "parser.tab.c"
    break;

  case 47: /* MatchedStmt: T_IF T_L_PAREN Exp T_R_PAREN MatchedStmt T_ELSE MatchedStmt  */
#line 631 "parser.y"
                                                                  {
        yyval = new asgNode("IfStmt");
        yyval->addSon(yyvsp[-4]);
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2026 "parser.tab.c"
    break;

  case 48: /* MatchedStmt: T_WHILE T_L_PAREN Exp T_R_PAREN MatchedStmt  */
#line 637 "parser.y"
                                                  {
        yyval = new asgNode("WhileStmt");
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2036 "parser.tab.c"
    break;

  case 49: /* MatchedStmt: T_BREAK T_SEMI  */
#line 642 "parser.y"
                     {
        yyval = new asgNode("BreakStmt");
    }
#line 2044 "parser.tab.c"
    break;

  case 50: /* MatchedStmt: T_CONTINUE T_SEMI  */
#line 645 "parser.y"
                        {
        yyval = new asgNode("ContinueStmt");
    }
#line 2052 "parser.tab.c"
    break;

  case 51: /* MatchedStmt: T_RETURN Exp T_SEMI  */
#line 648 "parser.y"
                          {
        yyval = new asgNode("ReturnStmt");
        yyval->addSon(yyvsp[-1]);
        // Todo: Implicit conversion
    }
#line 2062 "parser.tab.c"
    break;

  case 52: /* MatchedStmt: T_RETURN T_SEMI  */
#line 653 "parser.y"
                      {
        yyval = new asgNode("ReturnStmt");
    }
#line 2070 "parser.tab.c"
    break;

  case 53: /* MatchedStmt: T_DO T_L_BRACE MatchedStmt T_R_BRACE T_WHILE T_L_PAREN Exp T_R_PAREN T_SEMI  */
#line 656 "parser.y"
                                                                                  {
        yyval = new asgNode("DoStmt");
        yyval->addSon(yyvsp[-6]);
        yyval->addSon(yyvsp[-2]);
    }
#line 2080 "parser.tab.c"
    break;

  case 54: /* UnmatchedStmt: T_IF T_L_PAREN Exp T_R_PAREN Stmt  */
#line 664 "parser.y"
                                                 {
        yyval = new asgNode("IfStmt");
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2090 "parser.tab.c"
    break;

  case 55: /* UnmatchedStmt: T_IF T_L_PAREN Exp T_R_PAREN MatchedStmt T_ELSE UnmatchedStmt  */
#line 669 "parser.y"
                                                                    {
        yyval = new asgNode("IfStmt");
        yyval->addSon(yyvsp[-4]);
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2101 "parser.tab.c"
    break;

  case 56: /* Exp: LOrExp  */
#line 677 "parser.y"
            {
        yyval = yyvsp[0];
    }
#line 2109 "parser.tab.c"
    break;

  case 57: /* LVal: T_IDENTIFIER ArrayList  */
#line 682 "parser.y"
                             {
        yyvsp[-1]->type = idenTable[yyval->name]->type;
        if(yyvsp[0]->type != "")
        {
            // $$ = new asgNode("ArraySubscriptExpr");
            // $$->type = idenTable[$1->name]->type;

            // auto ptr = new asgNode("ImplicitCastExpr");
            // ptr->type = "ArrayToPointerDecay";
            // $1->kind = "DeclRefExpr";
            // $$->addSon(ptr);
            // ptr->addSon($1);
            // $1->moveSons($2);
            asgNode* preNode = nullptr;
            // GO through all the sons reversely
            // for(auto&& it: $2->sons | std::views::reverse)
            for(auto&& it = yyvsp[0]->sons.rbegin(); it != yyvsp[0]->sons.rend(); ++it)
            {
                auto ptr_1 = new asgNode("ArraySubscriptExpr");
                auto ptr_2 = new asgNode("ImplicitCastExpr");

                ptr_1->type = idenTable[yyvsp[-1]->name]->type;
                ptr_2->type = "ArrayToPointerDecay";

                ptr_1->addSon(ptr_2);
                // //Move it to ptr_1's Sons
                ptr_1->sons.emplace_back(std::move(*it));;

                if(preNode == nullptr)
                {
                    // The first Node
                    yyval = ptr_1;
                }
                else
                {
                    preNode->addSon(ptr_1);
                }
                preNode = ptr_2;
            }
            yyvsp[-1]->kind = "DeclRefExpr";
            preNode->addSon(yyvsp[-1]);
        }
        else
        {
            yyval->kind = "DeclRefExpr";
        }
        // delete $2;
    }
#line 2162 "parser.tab.c"
    break;

  case 58: /* PrimaryExp: T_L_PAREN Exp T_R_PAREN  */
#line 732 "parser.y"
                                    {
        yyval = yyvsp[-1];
    }
#line 2170 "parser.tab.c"
    break;

  case 59: /* PrimaryExp: LVal  */
#line 735 "parser.y"
           {
        yyval = new asgNode("ImplicitCastExpr");
        yyval->addSon(yyvsp[0]);
        yyval->type = "LValueToRValue";
    }
#line 2180 "parser.tab.c"
    break;

  case 60: /* PrimaryExp: Number  */
#line 740 "parser.y"
             {
        yyval = yyvsp[0];
    }
#line 2188 "parser.tab.c"
    break;

  case 61: /* Number: T_NUMERIC_CONSTANT  */
#line 745 "parser.y"
                           {
        yyval = yyvsp[0];
        if(yyval->type == "int")
        {
            yyval->kind = "IntegerLiteral";
        }
        else
        {
            yyval->kind = "FloatingLiteral";
        }
    }
#line 2204 "parser.tab.c"
    break;

  case 62: /* UnaryExp: PrimaryExp  */
#line 762 "parser.y"
                     {
        yyval = yyvsp[0];
    }
#line 2212 "parser.tab.c"
    break;

  case 63: /* UnaryExp: T_IDENTIFIER T_L_PAREN FuncRParams T_R_PAREN  */
#line 765 "parser.y"
                                                   {
        yyval = new asgNode("CallExpr");

        // Implicit conversion Node
        auto ptr_i = new asgNode("ImplicitCastExpr");
        ptr_i->type = "FunctionToPointerDecay";
        yyval->addSon(ptr_i);
        yyval->moveSons(yyvsp[-1]);

        // DeclRefExpr Node
        yyvsp[-3]->kind = "DeclRefExpr";
        yyvsp[-3]->type = idenTable[yyvsp[-3]->name]->type + yyvsp[-1]->type;
        ptr_i->addSon(yyvsp[-3]);

        // Todo: Fix type of ImplicitCastExpr
    }
#line 2233 "parser.tab.c"
    break;

  case 64: /* UnaryExp: T_PLUS UnaryExp  */
#line 781 "parser.y"
                                   {
        yyval = new asgNode("UnaryOperator");
        yyval->opcode = "+";
        yyval->addSon(yyvsp[0]);
    }
#line 2243 "parser.tab.c"
    break;

  case 65: /* UnaryExp: T_MINUS UnaryExp  */
#line 786 "parser.y"
                                     {
        yyval = new asgNode("UnaryOperator");
        yyval->opcode = "-";
        yyval->addSon(yyvsp[0]);
    }
#line 2253 "parser.tab.c"
    break;

  case 66: /* UnaryExp: T_EXCLAIM UnaryExp  */
#line 791 "parser.y"
                                   {
        yyval = new asgNode("UnaryOperator");
        yyval->opcode = "!";
        yyval->addSon(yyvsp[0]);
    }
#line 2263 "parser.tab.c"
    break;

  case 67: /* FuncRParams: Exp  */
#line 798 "parser.y"
                 {
        yyval = new asgNode("FuncRParamsPreNode");
        // auto ptr = new asgNode("ImplicitCastExp");
        // ptr->type = "LValueToRValue";
        yyval->addSon(yyvsp[0]);
        // ptr->addSon($1);
    }
#line 2275 "parser.tab.c"
    break;

  case 68: /* FuncRParams: FuncRParams T_COMMA Exp  */
#line 805 "parser.y"
                              {
        yyval = yyvsp[-2];
        // auto ptr = new asgNode("ImplicitCastExp");
        // ptr->type = "LValueToRValue";
        yyval->addSon(yyvsp[0]);
        // ptr->addSon($3);
    }
#line 2287 "parser.tab.c"
    break;

  case 69: /* FuncRParams: %empty  */
#line 812 "parser.y"
             {
        yyval = new asgNode("FuncRParamsPreNode");
    }
#line 2295 "parser.tab.c"
    break;

  case 70: /* MulExp: UnaryExp  */
#line 817 "parser.y"
                 {
        yyval = yyvsp[0];
    }
#line 2303 "parser.tab.c"
    break;

  case 71: /* MulExp: MulExp T_STAR UnaryExp  */
#line 820 "parser.y"
                             {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "*";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2314 "parser.tab.c"
    break;

  case 72: /* MulExp: MulExp T_SLASH UnaryExp  */
#line 826 "parser.y"
                              {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "/";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2325 "parser.tab.c"
    break;

  case 73: /* MulExp: MulExp T_PERCENT UnaryExp  */
#line 832 "parser.y"
                                {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "%";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2336 "parser.tab.c"
    break;

  case 74: /* AddExp: MulExp  */
#line 840 "parser.y"
               {
        yyval = yyvsp[0];
    }
#line 2344 "parser.tab.c"
    break;

  case 75: /* AddExp: AddExp T_PLUS MulExp  */
#line 843 "parser.y"
                           {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "+";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2355 "parser.tab.c"
    break;

  case 76: /* AddExp: AddExp T_MINUS MulExp  */
#line 849 "parser.y"
                            {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "-";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2366 "parser.tab.c"
    break;

  case 77: /* RelExp: AddExp  */
#line 857 "parser.y"
               {
        yyval = yyvsp[0];
    }
#line 2374 "parser.tab.c"
    break;

  case 78: /* RelExp: RelExp T_LESS AddExp  */
#line 860 "parser.y"
                           {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "<";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2385 "parser.tab.c"
    break;

  case 79: /* RelExp: RelExp T_GREATER AddExp  */
#line 866 "parser.y"
                              {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = ">";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2396 "parser.tab.c"
    break;

  case 80: /* RelExp: RelExp T_LESSEQUAL AddExp  */
#line 872 "parser.y"
                                {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "<=";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2407 "parser.tab.c"
    break;

  case 81: /* RelExp: RelExp T_GREATEREQUAL AddExp  */
#line 878 "parser.y"
                                   {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = ">=";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2418 "parser.tab.c"
    break;

  case 82: /* EqExp: RelExp  */
#line 886 "parser.y"
              {
        yyval = yyvsp[0];
    }
#line 2426 "parser.tab.c"
    break;

  case 83: /* EqExp: EqExp T_EQUALEQUAL RelExp  */
#line 889 "parser.y"
                                {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "==";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2437 "parser.tab.c"
    break;

  case 84: /* EqExp: EqExp T_EXCLAIMEQUAL RelExp  */
#line 895 "parser.y"
                                  {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "!=";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2448 "parser.tab.c"
    break;

  case 85: /* LAndExp: EqExp  */
#line 903 "parser.y"
               {
        yyval = yyvsp[0];
    }
#line 2456 "parser.tab.c"
    break;

  case 86: /* LAndExp: LAndExp T_AMPAMP EqExp  */
#line 906 "parser.y"
                             {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "&&";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2467 "parser.tab.c"
    break;

  case 87: /* LOrExp: LAndExp  */
#line 914 "parser.y"
                {
        yyval = yyvsp[0];
    }
#line 2475 "parser.tab.c"
    break;

  case 88: /* LOrExp: LOrExp T_PIPEPIPE LAndExp  */
#line 917 "parser.y"
                                {
        yyval = new asgNode("BinaryOperator");
        yyval->opcode = "||";
        yyval->addSon(yyvsp[-2]);
        yyval->addSon(yyvsp[0]);
    }
#line 2486 "parser.tab.c"
    break;


#line 2490 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 924 "parser.y"
