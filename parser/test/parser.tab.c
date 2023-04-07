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

#line 293 "parser.tab.c"

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

#line 329 "parser.tab.c"

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
    U_MINUS = 297,                 /* U_MINUS  */
    U_PLUS = 298,                  /* U_PLUS  */
    U_N = 299                      /* U_N  */
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
  YYSYMBOL_U_MINUS = 42,                   /* U_MINUS  */
  YYSYMBOL_U_PLUS = 43,                    /* U_PLUS  */
  YYSYMBOL_U_N = 44,                       /* U_N  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_Begin = 46,                     /* Begin  */
  YYSYMBOL_CompUnit = 47,                  /* CompUnit  */
  YYSYMBOL_GlobalDecl = 48,                /* GlobalDecl  */
  YYSYMBOL_ConstDeclPrefix = 49,           /* ConstDeclPrefix  */
  YYSYMBOL_ConstDecl = 50,                 /* ConstDecl  */
  YYSYMBOL_BType = 51,                     /* BType  */
  YYSYMBOL_ConstDef = 52,                  /* ConstDef  */
  YYSYMBOL_ConstInitValPrefix = 53,        /* ConstInitValPrefix  */
  YYSYMBOL_ConstInitVal = 54,              /* ConstInitVal  */
  YYSYMBOL_VarDeclPrefix = 55,             /* VarDeclPrefix  */
  YYSYMBOL_VarDecl = 56,                   /* VarDecl  */
  YYSYMBOL_VarDef = 57,                    /* VarDef  */
  YYSYMBOL_InitValPrefix = 58,             /* InitValPrefix  */
  YYSYMBOL_InitVal = 59,                   /* InitVal  */
  YYSYMBOL_FuncDef = 60,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 61,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 62,                /* FuncFParam  */
  YYSYMBOL_FuncFParamSuffix = 63,          /* FuncFParamSuffix  */
  YYSYMBOL_BlockPrefix = 64,               /* BlockPrefix  */
  YYSYMBOL_Block = 65,                     /* Block  */
  YYSYMBOL_BlockItem = 66,                 /* BlockItem  */
  YYSYMBOL_Stmt = 67,                      /* Stmt  */
  YYSYMBOL_Exp = 68,                       /* Exp  */
  YYSYMBOL_LVal = 69,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 70,                /* PrimaryExp  */
  YYSYMBOL_Number = 71,                    /* Number  */
  YYSYMBOL_UnaryExp = 72,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 73,                   /* UnaryOp  */
  YYSYMBOL_FuncRParams = 74,               /* FuncRParams  */
  YYSYMBOL_MulExp = 75,                    /* MulExp  */
  YYSYMBOL_AddExp = 76,                    /* AddExp  */
  YYSYMBOL_RelExp = 77,                    /* RelExp  */
  YYSYMBOL_EqExp = 78,                     /* EqExp  */
  YYSYMBOL_LAndExp = 79,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 80,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 81                   /* ConstExp  */
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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

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
       0,   325,   325,   330,   339,   351,   354,   357,   366,   376,
     384,   390,   394,   398,   402,   406,   410,   417,   421,   426,
     434,   437,   442,   446,   449,   474,   484,   492,   506,   509,
     513,   521,   524,   530,   534,   537,   561,   571,   602,   605,
     613,   618,   626,   630,   637,   641,   646,   650,   681,   685,
     689,   707,   714,   717,   720,   723,   729,   736,   742,   745,
     748,   751,   756,   775,   780,   803,   806,   809,   816,   825,
     828,   834,   839,   846,   850,   854,   861,   864,   870,   873,
     880,   887,   897,   900,   907,   916,   919,   926,   933,   940,
     950,   953,   960,   970,   973,   983,   986,   996
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
  "U_MINUS", "U_PLUS", "U_N", "$accept", "Begin", "CompUnit", "GlobalDecl",
  "ConstDeclPrefix", "ConstDecl", "BType", "ConstDef",
  "ConstInitValPrefix", "ConstInitVal", "VarDeclPrefix", "VarDecl",
  "VarDef", "InitValPrefix", "InitVal", "FuncDef", "FuncFParams",
  "FuncFParam", "FuncFParamSuffix", "BlockPrefix", "Block", "BlockItem",
  "Stmt", "Exp", "LVal", "PrimaryExp", "Number", "UnaryExp", "UnaryOp",
  "FuncRParams", "MulExp", "AddExp", "RelExp", "EqExp", "LAndExp",
  "LOrExp", "ConstExp", YY_NULLPTR
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

#define YYPACT_NINF (-66)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     201,   -66,   -66,   -66,   -66,    52,    -6,    48,   201,   -66,
      11,   -66,    17,    60,   -66,   -66,    27,   -66,   -66,   -66,
      27,   -66,    41,    12,    34,   -66,   -66,    29,    29,   197,
      59,   176,   -66,    12,    59,   206,     3,    63,    26,   -66,
      59,   -66,   -66,   -66,   -66,    83,   -66,   -66,   -66,   -66,
     -66,    59,   119,    73,   214,     1,    90,    94,   137,    75,
      10,   -66,   -66,   138,    93,    67,   -66,   -66,   133,   168,
     -66,   115,    52,     3,   139,   114,   -66,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
     -66,   -66,   -66,   176,   -66,   -66,   -66,   -66,   206,   -66,
     -66,   -66,   116,   144,   146,   149,   153,     7,   -66,    34,
     -66,   -66,   -66,   -66,   154,   167,   -66,   -66,   159,   174,
     -66,   -66,   -66,   -66,   -66,    36,   -66,   -66,   -66,   119,
     119,    73,    73,    73,    73,   214,   214,     1,    90,   -66,
     -66,    59,    18,    59,   -66,   -66,   -66,   180,   -66,    59,
     -66,    59,    59,   -66,   177,   178,   181,   -66,   188,   187,
     -66,    18,   166,    18,   -66,   -66,   179,   203,   -66,    18,
      59,   -66,   200,   213,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    16,    12,    14,     0,    13,     0,     2,     4,
       0,     5,     0,     0,     6,     7,     0,    15,     1,     3,
       0,    10,    28,    25,     0,    27,    17,     8,     9,     0,
       0,     0,    28,    26,     0,     0,     0,     0,     0,    38,
       0,    73,    74,    75,    68,    64,    97,    66,    69,    67,
      78,     0,    82,    85,    90,    93,    95,    63,     0,     0,
       0,    30,    33,     0,     0,     0,    19,    22,     0,     0,
      37,    40,     0,     0,     0,     0,    72,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      29,    34,    31,     0,    35,    18,    23,    20,     0,    24,
      53,    47,     0,     0,     0,     0,     0,     0,    48,     0,
      49,    54,    44,    50,     0,    66,    46,    45,     0,    41,
      39,    36,    65,    71,    76,     0,    79,    80,    81,    83,
      84,    86,    87,    88,    89,    91,    92,    94,    96,    32,
      21,     0,     0,     0,    58,    59,    60,     0,    52,     0,
      42,     0,     0,    70,     0,     0,     0,    61,     0,     0,
      77,     0,     0,     0,    51,    43,    55,     0,    57,     0,
       0,    56,     0,     0,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -66,   -66,   -66,   228,   -66,    22,    -3,   202,   -66,   -57,
     -66,    40,   215,   -66,   -51,   -66,   -66,   169,   -66,   -66,
     -30,   152,   -13,   -31,   -65,   -66,   -66,   -18,   -66,   -66,
      14,   165,    30,   155,   148,   -66,   -29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    11,    12,    27,    65,    66,
      13,    14,    23,    60,    61,    15,    38,    39,   119,    69,
     111,   112,   113,    46,    47,    48,    49,    50,    51,   125,
      52,    53,    54,    55,    56,    57,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      62,    58,    16,   115,   115,    63,    70,    97,    92,    74,
      68,   146,    86,    93,    20,    21,    40,    30,    94,    41,
      42,    43,   100,    31,    87,    68,    37,    40,    62,    72,
      41,    42,    43,    76,    34,    17,    73,   114,   114,   152,
      35,   140,   139,   121,   124,    44,   153,    45,    18,   102,
      29,   103,   104,   105,   106,   107,    44,    22,    45,   126,
     127,   128,    62,    24,    25,   109,   109,    26,    40,    37,
      98,    41,    42,    43,    32,    99,   147,   115,     1,     2,
       3,     4,    59,    91,    40,    80,    81,    41,    42,    43,
     108,   108,    75,     6,   129,   130,   115,    44,   115,    45,
      64,    96,    40,    71,   115,    41,    42,    43,   110,   110,
     154,   114,   156,    44,    88,    45,   135,   136,   158,    89,
     118,   160,   159,    40,   123,   141,    41,    42,    43,   155,
     114,    44,   114,    45,    77,    78,    79,   100,   114,   172,
      68,   101,    40,    90,    95,    41,    42,    43,   166,   122,
     168,   142,    44,   144,    45,   143,   171,   145,   148,     1,
       2,     3,     4,     5,   102,   150,   103,   104,   105,   106,
     107,    44,   100,    45,     6,    68,   116,    40,   149,   151,
      41,    42,    43,    59,   157,    40,   162,   161,    41,    42,
      43,   163,   164,   165,     1,     2,     3,     4,     5,   102,
     167,   103,   104,   105,   106,   107,    44,    36,    45,     6,
     173,   169,   170,    64,    44,    40,    45,   174,    41,    42,
      43,   117,    28,     1,     2,     3,     4,     1,     2,     3,
       4,     5,    82,    83,    84,    85,    19,   138,     6,    33,
       0,   120,     6,   137,    44,     0,    45,   131,   132,   133,
     134
};

static const yytype_int16 yycheck[] =
{
      31,    30,     5,    68,    69,    34,    36,    64,    59,    40,
       7,     4,    11,     3,     3,     4,     9,     5,     8,    12,
      13,    14,     4,    11,    23,     7,    29,     9,    59,     3,
      12,    13,    14,    51,     5,    41,    10,    68,    69,     3,
      11,    98,    93,    73,    75,    38,    10,    40,     0,    31,
       9,    33,    34,    35,    36,    37,    38,    40,    40,    77,
      78,    79,    93,     3,     4,    68,    69,    40,     9,    72,
       3,    12,    13,    14,    40,     8,   107,   142,    26,    27,
      28,    29,     7,     8,     9,    12,    13,    12,    13,    14,
      68,    69,     9,    41,    80,    81,   161,    38,   163,    40,
       7,     8,     9,    40,   169,    12,    13,    14,    68,    69,
     141,   142,   143,    38,    24,    40,    86,    87,   149,    25,
       5,   152,   151,     9,    10,     9,    12,    13,    14,   142,
     161,    38,   163,    40,    15,    16,    17,     4,   169,   170,
       7,     8,     9,     6,     6,    12,    13,    14,   161,    10,
     163,     7,    38,     4,    40,     9,   169,     4,     4,    26,
      27,    28,    29,    30,    31,     6,    33,    34,    35,    36,
      37,    38,     4,    40,    41,     7,     8,     9,    11,     5,
      12,    13,    14,     7,     4,     9,     8,    10,    12,    13,
      14,    10,     4,     6,    26,    27,    28,    29,    30,    31,
      34,    33,    34,    35,    36,    37,    38,    10,    40,    41,
      10,    32,     9,     7,    38,     9,    40,     4,    12,    13,
      14,    69,    20,    26,    27,    28,    29,    26,    27,    28,
      29,    30,    18,    19,    20,    21,     8,    89,    41,    24,
      -1,    72,    41,    88,    38,    -1,    40,    82,    83,    84,
      85
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    28,    29,    30,    41,    46,    47,    48,
      49,    50,    51,    55,    56,    60,    51,    41,     0,    48,
       3,     4,    40,    57,     3,     4,    40,    52,    52,     9,
       5,    11,    40,    57,     5,    11,    10,    51,    61,    62,
       9,    12,    13,    14,    38,    40,    68,    69,    70,    71,
      72,    73,    75,    76,    77,    78,    79,    80,    81,     7,
      58,    59,    68,    81,     7,    53,    54,    81,     7,    64,
      65,    40,     3,    10,    68,     9,    72,    15,    16,    17,
      12,    13,    18,    19,    20,    21,    11,    23,    24,    25,
       6,     8,    59,     3,     8,     6,     8,    54,     3,     8,
       4,     8,    31,    33,    34,    35,    36,    37,    50,    51,
      56,    65,    66,    67,    68,    69,     8,    66,     5,    63,
      62,    65,    10,    10,    68,    74,    72,    72,    72,    75,
      75,    76,    76,    76,    76,    77,    77,    78,    79,    59,
      54,     9,     7,     9,     4,     4,     4,    68,     4,    11,
       6,     5,     3,    10,    68,    67,    68,     4,    68,    81,
      68,    10,     8,    10,     4,     6,    67,    34,    67,    32,
       9,    67,    68,    10,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      50,    51,    51,    51,    51,    51,    51,    52,    52,    52,
      53,    53,    54,    54,    54,    55,    55,    56,    57,    57,
      57,    58,    58,    59,    59,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      66,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    69,    70,    70,    70,    71,    72,
      72,    72,    72,    73,    73,    73,    74,    74,    75,    75,
      75,    75,    76,    76,    76,    77,    77,    77,    77,    77,
      78,    78,    78,    79,    79,    80,    80,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       2,     1,     1,     1,     1,     2,     1,     1,     4,     3,
       2,     3,     1,     2,     2,     2,     3,     2,     1,     4,
       3,     2,     3,     1,     2,     2,     6,     5,     1,     3,
       2,     3,     2,     4,     2,     2,     2,     2,     1,     1,
       1,     4,     2,     1,     1,     5,     7,     5,     2,     2,
       2,     3,     9,     1,     1,     3,     1,     1,     1,     1,
       4,     3,     2,     1,     1,     1,     1,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1
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
#line 325 "parser.y"
                {
        root = yyvsp[0];
    }
#line 1594 "parser.tab.c"
    break;

  case 3: /* CompUnit: CompUnit GlobalDecl  */
#line 330 "parser.y"
                              {
    yyval = yyvsp[-1];
    if (yyvsp[0]->kind == "VarDeclPreNode") {
        yyval->moveSons(yyvsp[0]);
    }
    else {
        yyval->addSon(yyvsp[0]);
    }
    }
#line 1608 "parser.tab.c"
    break;

  case 4: /* CompUnit: GlobalDecl  */
#line 339 "parser.y"
                 {
        yyval = new asgNode("TranslationUnitDecl");
        if (yyvsp[0]->kind == "VarDeclPreNode") {
            yyval->moveSons(yyvsp[0]);
        }
        else {
            yyval->addSon(yyvsp[0]);
        }
    }
#line 1622 "parser.tab.c"
    break;

  case 5: /* GlobalDecl: ConstDecl  */
#line 351 "parser.y"
                     {
        yyval = yyvsp[0];
    }
#line 1630 "parser.tab.c"
    break;

  case 6: /* GlobalDecl: VarDecl  */
#line 354 "parser.y"
              {
        yyval = yyvsp[0];
    }
#line 1638 "parser.tab.c"
    break;

  case 7: /* GlobalDecl: FuncDef  */
#line 357 "parser.y"
              {
        yyval= yyvsp[0];
    }
#line 1646 "parser.tab.c"
    break;

  case 8: /* ConstDeclPrefix: T_CONST BType ConstDef  */
#line 366 "parser.y"
                                        {
        yyval = new asgNode();
        yyval->kind = "VarDeclPreNode";
        yyval->type = yyvsp[-1]->type;
        delete yyvsp[-1];
        yyvsp[0]->type = yyval->type + yyvsp[0]->type;
        yyvsp[0]->kind = "VarDecl";
        idenTable[yyvsp[0]->name] = yyvsp[0];
        yyval->addSon(yyvsp[-1]);
    }
#line 1661 "parser.tab.c"
    break;

  case 9: /* ConstDeclPrefix: ConstDeclPrefix T_COMMA ConstDef  */
#line 376 "parser.y"
                                       {
        yyval = yyvsp[-2];
        yyvsp[0]->type = yyval->type + yyvsp[0]->type;
        yyvsp[0]->kind = "VarDecl";
        idenTable[yyvsp[0]->name] = yyvsp[0];
        yyval->addSon(yyvsp[0]);
    }
#line 1673 "parser.tab.c"
    break;

  case 10: /* ConstDecl: ConstDeclPrefix T_SEMI  */
#line 384 "parser.y"
                                      {
        yyval = yyvsp[-1];
    }
#line 1681 "parser.tab.c"
    break;

  case 11: /* BType: T_INT  */
#line 390 "parser.y"
            {
        yyval = new asgNode();
        yyval->type = "int";
    }
#line 1690 "parser.tab.c"
    break;

  case 12: /* BType: T_CHAR  */
#line 394 "parser.y"
             {
        yyval = new asgNode();
        yyval->type = "char";
    }
#line 1699 "parser.tab.c"
    break;

  case 13: /* BType: T_LONG  */
#line 398 "parser.y"
             {
        yyval = new asgNode();
        yyval->type = "long";
    }
#line 1708 "parser.tab.c"
    break;

  case 14: /* BType: T_VOID  */
#line 402 "parser.y"
             {
        yyval = new asgNode();
        yyval->type = "void";
    }
#line 1717 "parser.tab.c"
    break;

  case 15: /* BType: T_LONG T_LONG  */
#line 406 "parser.y"
                    {
        yyval = new asgNode();
        yyval->type = "long long";
    }
#line 1726 "parser.tab.c"
    break;

  case 16: /* BType: T_FLOAT  */
#line 410 "parser.y"
              {
        yyval = new asgNode();
        yyval->type = "float";
    }
#line 1735 "parser.tab.c"
    break;

  case 17: /* ConstDef: T_IDENTIFIER  */
#line 417 "parser.y"
                       {
        yyval = yyvsp[0];
        yyval->type = "const " + yyval->type; 
    }
#line 1744 "parser.tab.c"
    break;

  case 18: /* ConstDef: ConstDef T_L_SQUARE ConstExp T_R_SQUARE  */
#line 421 "parser.y"
                                              {
        yyval = yyvsp[-3];
        yyval->type = yyval->type + " [" + yyvsp[-1]->value + "]";
        // Todo: Cal Value of ConstExp 
    }
#line 1754 "parser.tab.c"
    break;

  case 19: /* ConstDef: ConstDef T_EQUAL ConstInitVal  */
#line 426 "parser.y"
                                    {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1763 "parser.tab.c"
    break;

  case 20: /* ConstInitValPrefix: T_L_BRACE ConstInitVal  */
#line 434 "parser.y"
                                           {
        yyval = yyvsp[0];
    }
#line 1771 "parser.tab.c"
    break;

  case 21: /* ConstInitValPrefix: ConstInitValPrefix T_COMMA ConstInitVal  */
#line 437 "parser.y"
                                              {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1780 "parser.tab.c"
    break;

  case 22: /* ConstInitVal: ConstExp  */
#line 442 "parser.y"
                       {
        yyval = new asgNode("InitListExpr");
        yyval->addSon(yyvsp[0]);
    }
#line 1789 "parser.tab.c"
    break;

  case 23: /* ConstInitVal: T_L_BRACE T_R_BRACE  */
#line 446 "parser.y"
                          {
        yyval = new asgNode("InitListExpr");
    }
#line 1797 "parser.tab.c"
    break;

  case 24: /* ConstInitVal: ConstInitValPrefix T_R_BRACE  */
#line 449 "parser.y"
                                   {
        yyval = new asgNode("InitListExpr");
        yyval->addSon(yyvsp[-1]);
    }
#line 1806 "parser.tab.c"
    break;

  case 25: /* VarDeclPrefix: BType VarDef  */
#line 474 "parser.y"
                            {
        yyval = new asgNode();
        yyval->kind = "VarDeclPreNode";
        yyval->type = yyvsp[-1]->type;
        delete yyvsp[-1];
        yyvsp[0]->type = yyval->type + yyvsp[0]->type;
        yyvsp[0]->kind = "VarDecl";
        idenTable[yyvsp[0]->name] = yyvsp[0];
        yyval->addSon(yyvsp[0]);
    }
#line 1821 "parser.tab.c"
    break;

  case 26: /* VarDeclPrefix: VarDeclPrefix T_COMMA VarDef  */
#line 484 "parser.y"
                                   {
        yyval = yyvsp[-2];
        yyvsp[0]->type = yyval->type + yyvsp[0]->type;
        yyvsp[0]->kind = "VarDecl";
        idenTable[yyvsp[0]->name] = yyvsp[0];
        yyval->addSon(yyvsp[0]);
    }
#line 1833 "parser.tab.c"
    break;

  case 27: /* VarDecl: VarDeclPrefix T_SEMI  */
#line 492 "parser.y"
                                  {
        yyval = yyvsp[-1];
    }
#line 1841 "parser.tab.c"
    break;

  case 28: /* VarDef: T_IDENTIFIER  */
#line 506 "parser.y"
                     {
        yyval = yyvsp[0];
    }
#line 1849 "parser.tab.c"
    break;

  case 29: /* VarDef: VarDef T_L_SQUARE ConstExp T_R_SQUARE  */
#line 509 "parser.y"
                                            {
        yyval = yyvsp[-3];
        yyval->type = yyval->type + " [" + yyvsp[-1]->value + "]";
    }
#line 1858 "parser.tab.c"
    break;

  case 30: /* VarDef: VarDef T_EQUAL InitVal  */
#line 513 "parser.y"
                             {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1867 "parser.tab.c"
    break;

  case 31: /* InitValPrefix: T_L_BRACE InitVal  */
#line 521 "parser.y"
                                 {
        yyval = yyvsp[0];
    }
#line 1875 "parser.tab.c"
    break;

  case 32: /* InitValPrefix: InitValPrefix T_COMMA InitVal  */
#line 524 "parser.y"
                                    {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1884 "parser.tab.c"
    break;

  case 33: /* InitVal: Exp  */
#line 530 "parser.y"
             {
        yyval = new asgNode("InitListExpr");
        yyval->addSon(yyvsp[0]);
    }
#line 1893 "parser.tab.c"
    break;

  case 34: /* InitVal: T_L_BRACE T_R_BRACE  */
#line 534 "parser.y"
                          {
        yyval = new asgNode("InitListExpr");
    }
#line 1901 "parser.tab.c"
    break;

  case 35: /* InitVal: InitValPrefix T_R_BRACE  */
#line 537 "parser.y"
                              {
        yyval = new asgNode("InitListExpr");
        yyval->addSon(yyvsp[-1]);
    }
#line 1910 "parser.tab.c"
    break;

  case 36: /* FuncDef: BType T_IDENTIFIER T_L_PAREN FuncFParams T_R_PAREN Block  */
#line 561 "parser.y"
                                                                  {
        yyvsp[-4]->kind = "FunctionDecl";
        yyvsp[-4]->type = yyvsp[-5]->type + "(" + yyvsp[-2]->type + ")";
        delete yyvsp[-5];
        yyvsp[-4]->addSon(yyvsp[-2]);
        yyvsp[-4]->addSon(yyvsp[0]);
        // Push the FuncDef to the symbol table
        idenTable[yyvsp[-4]->name] = yyvsp[-4];
        yyval = yyvsp[-4];
    }
#line 1925 "parser.tab.c"
    break;

  case 37: /* FuncDef: BType T_IDENTIFIER T_L_PAREN T_R_PAREN Block  */
#line 571 "parser.y"
                                                   {
        yyvsp[-3]->kind = "FunctionDecl";
        yyvsp[-3]->type = yyvsp[-4]->type + "()";
        delete yyvsp[-4];
        yyvsp[-3]->addSon(yyvsp[0]);
        // Push the FuncDef to the symbol table
        idenTable[yyvsp[-3]->name] = yyvsp[-3];
        yyval = yyvsp[-3];
    }
#line 1939 "parser.tab.c"
    break;

  case 38: /* FuncFParams: FuncFParam  */
#line 602 "parser.y"
                        {
        yyval = yyvsp[0];
    }
#line 1947 "parser.tab.c"
    break;

  case 39: /* FuncFParams: FuncFParams T_COMMA FuncFParam  */
#line 605 "parser.y"
                                     {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
        yyval->type = yyval->type + ", " + yyvsp[0]->type;
    }
#line 1957 "parser.tab.c"
    break;

  case 40: /* FuncFParam: BType T_IDENTIFIER  */
#line 613 "parser.y"
                               {
        yyval = yyvsp[0];
        yyval->type = yyvsp[-1]->type;
        delete yyvsp[-1];
    }
#line 1967 "parser.tab.c"
    break;

  case 41: /* FuncFParam: BType T_IDENTIFIER FuncFParamSuffix  */
#line 618 "parser.y"
                                          {
        yyval = yyvsp[-1];
        yyval->type = yyvsp[-2]->type + yyvsp[0]->type;
        delete yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 1978 "parser.tab.c"
    break;

  case 42: /* FuncFParamSuffix: T_L_SQUARE T_R_SQUARE  */
#line 626 "parser.y"
                                        {
        yyval = yyvsp[-1];
        yyval->type = yyval->type + " []";
    }
#line 1987 "parser.tab.c"
    break;

  case 43: /* FuncFParamSuffix: FuncFParamSuffix T_L_SQUARE ConstExp T_R_SQUARE  */
#line 630 "parser.y"
                                                      {
        yyval = yyvsp[-3];
        yyval->type = yyval->type + "[" + yyvsp[-1]->value + "]";
    }
#line 1996 "parser.tab.c"
    break;

  case 44: /* BlockPrefix: T_L_BRACE BlockItem  */
#line 637 "parser.y"
                                {
        yyval = new asgNode("CompoundStmt");
        yyval->addSon(yyvsp[0]);
    }
#line 2005 "parser.tab.c"
    break;

  case 45: /* BlockPrefix: BlockPrefix BlockItem  */
#line 641 "parser.y"
                            {
        yyval = yyvsp[-1];
        yyval->addSon(yyvsp[0]);
    }
#line 2014 "parser.tab.c"
    break;

  case 46: /* Block: BlockPrefix T_R_BRACE  */
#line 646 "parser.y"
                             {
        yyval = yyvsp[-1];
        yyval->kind = "CompoundStmt";
    }
#line 2023 "parser.tab.c"
    break;

  case 47: /* Block: T_L_BRACE T_R_BRACE  */
#line 650 "parser.y"
                          {
        auto ptr = new asgNode("CompoundStmt");
        yyval = ptr;
    }
#line 2032 "parser.tab.c"
    break;

  case 48: /* BlockItem: ConstDecl  */
#line 681 "parser.y"
                     {
        yyval = new asgNode("DeclStmt");
        yyval->moveSons(yyvsp[0]);
    }
#line 2041 "parser.tab.c"
    break;

  case 49: /* BlockItem: VarDecl  */
#line 685 "parser.y"
              {
        yyval = new asgNode("DeclStmt");
        yyval->moveSons(yyvsp[0]);
    }
#line 2050 "parser.tab.c"
    break;

  case 50: /* BlockItem: Stmt  */
#line 689 "parser.y"
           {
        yyval = yyvsp[0];
    }
#line 2058 "parser.tab.c"
    break;

  case 51: /* Stmt: LVal T_EQUAL Exp T_SEMI  */
#line 707 "parser.y"
                              {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "=";
        ptr->addSon(yyvsp[-3]);
        ptr->addSon(yyvsp[-1]);
        yyval = ptr;
    }
#line 2070 "parser.tab.c"
    break;

  case 52: /* Stmt: Exp T_SEMI  */
#line 714 "parser.y"
                 {
        yyval = yyvsp[-1];
    }
#line 2078 "parser.tab.c"
    break;

  case 53: /* Stmt: T_SEMI  */
#line 717 "parser.y"
             {
        yyval = new asgNode("NullStmt");
    }
#line 2086 "parser.tab.c"
    break;

  case 54: /* Stmt: Block  */
#line 720 "parser.y"
            {
        yyval = yyvsp[0];
    }
#line 2094 "parser.tab.c"
    break;

  case 55: /* Stmt: T_IF T_L_PAREN Exp T_R_PAREN Stmt  */
#line 723 "parser.y"
                                        {
        auto ptr = new asgNode("IfStmt");
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2105 "parser.tab.c"
    break;

  case 56: /* Stmt: T_IF T_L_PAREN Exp T_R_PAREN Stmt T_ELSE Stmt  */
#line 729 "parser.y"
                                                    {
        auto ptr = new asgNode("IfStmt");
        ptr->addSon(yyvsp[-4]);
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2117 "parser.tab.c"
    break;

  case 57: /* Stmt: T_WHILE T_L_PAREN Exp T_R_PAREN Stmt  */
#line 736 "parser.y"
                                           {
        auto ptr = new asgNode("WhileStmt");
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2128 "parser.tab.c"
    break;

  case 58: /* Stmt: T_BREAK T_SEMI  */
#line 742 "parser.y"
                     {
        yyval = new asgNode("BreakStmt");
    }
#line 2136 "parser.tab.c"
    break;

  case 59: /* Stmt: T_CONTINUE T_SEMI  */
#line 745 "parser.y"
                        {
        yyval = new asgNode("ContinueStmt");
    }
#line 2144 "parser.tab.c"
    break;

  case 60: /* Stmt: T_RETURN T_SEMI  */
#line 748 "parser.y"
                      {
        yyval = new asgNode("ReturnStmt");
    }
#line 2152 "parser.tab.c"
    break;

  case 61: /* Stmt: T_RETURN Exp T_SEMI  */
#line 751 "parser.y"
                          {
        auto ptr = new asgNode("ReturnStmt");
        ptr->addSon(yyvsp[-1]);
        yyval = ptr;
    }
#line 2162 "parser.tab.c"
    break;

  case 62: /* Stmt: T_DO T_L_BRACE Stmt T_R_BRACE T_WHILE T_L_PAREN Exp T_R_PAREN T_SEMI  */
#line 756 "parser.y"
                                                                           {
        auto ptr = new asgNode("DoStmt");
        ptr->addSon(yyvsp[-6]);
        ptr->addSon(yyvsp[-2]);
        yyval = ptr;
    }
#line 2173 "parser.tab.c"
    break;

  case 63: /* Exp: LOrExp  */
#line 775 "parser.y"
            {
        yyval = yyvsp[0];
    }
#line 2181 "parser.tab.c"
    break;

  case 64: /* LVal: T_IDENTIFIER  */
#line 780 "parser.y"
                   {
        yyval = yyvsp[0];
        yyval->kind = "DeclRefExpr";
    }
#line 2190 "parser.tab.c"
    break;

  case 65: /* PrimaryExp: T_L_PAREN Exp T_R_PAREN  */
#line 803 "parser.y"
                                    {
        yyval = yyvsp[-1];
    }
#line 2198 "parser.tab.c"
    break;

  case 66: /* PrimaryExp: LVal  */
#line 806 "parser.y"
           {
        yyval = yyvsp[0];
    }
#line 2206 "parser.tab.c"
    break;

  case 67: /* PrimaryExp: Number  */
#line 809 "parser.y"
             {
        yyval = yyvsp[0];
    }
#line 2214 "parser.tab.c"
    break;

  case 68: /* Number: T_NUMERIC_CONSTANT  */
#line 816 "parser.y"
                           {
        yyval = yyvsp[0];
        yyval->kind = "IntegerLiteral";
    }
#line 2223 "parser.tab.c"
    break;

  case 69: /* UnaryExp: PrimaryExp  */
#line 825 "parser.y"
                     {
        yyval = yyvsp[0];
    }
#line 2231 "parser.tab.c"
    break;

  case 70: /* UnaryExp: T_IDENTIFIER T_L_PAREN FuncRParams T_R_PAREN  */
#line 828 "parser.y"
                                                   {
        auto ptr = new asgNode("CallExpr");
        ptr->addSon(yyvsp[-3]);
        ptr->addSon(yyvsp[-1]);
        yyval = ptr;
    }
#line 2242 "parser.tab.c"
    break;

  case 71: /* UnaryExp: T_IDENTIFIER T_L_PAREN T_R_PAREN  */
#line 834 "parser.y"
                                       {
        auto ptr = new asgNode("CallExpr");
        ptr->addSon(yyvsp[-2]);
        yyval = ptr;
    }
#line 2252 "parser.tab.c"
    break;

  case 72: /* UnaryExp: UnaryOp UnaryExp  */
#line 839 "parser.y"
                       {
        yyval = yyvsp[-1];
        yyvsp[-1]->addSon(yyvsp[0]);
    }
#line 2261 "parser.tab.c"
    break;

  case 73: /* UnaryOp: T_PLUS  */
#line 846 "parser.y"
                {
        yyval = new asgNode("UnaryOperator");
        yyval->opcode = "+";
    }
#line 2270 "parser.tab.c"
    break;

  case 74: /* UnaryOp: T_MINUS  */
#line 850 "parser.y"
              {
        yyval = new asgNode("UnaryOperator");
        yyval->opcode = "-";
    }
#line 2279 "parser.tab.c"
    break;

  case 75: /* UnaryOp: T_EXCLAIM  */
#line 854 "parser.y"
                {
        yyval = new asgNode("UnaryOperator");
        yyval->opcode = "!";
    }
#line 2288 "parser.tab.c"
    break;

  case 76: /* FuncRParams: Exp  */
#line 861 "parser.y"
                 {
        yyval = yyvsp[0];
    }
#line 2296 "parser.tab.c"
    break;

  case 77: /* FuncRParams: FuncRParams T_COMMA Exp  */
#line 864 "parser.y"
                              {
        yyval = yyvsp[-2];
        yyval->addSon(yyvsp[0]);
    }
#line 2305 "parser.tab.c"
    break;

  case 78: /* MulExp: UnaryExp  */
#line 870 "parser.y"
                 {
        yyval = yyvsp[0];
    }
#line 2313 "parser.tab.c"
    break;

  case 79: /* MulExp: MulExp T_STAR UnaryExp  */
#line 873 "parser.y"
                             {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "*";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2325 "parser.tab.c"
    break;

  case 80: /* MulExp: MulExp T_SLASH UnaryExp  */
#line 880 "parser.y"
                              {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "/";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2337 "parser.tab.c"
    break;

  case 81: /* MulExp: MulExp T_PERCENT UnaryExp  */
#line 887 "parser.y"
                                {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "%";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2349 "parser.tab.c"
    break;

  case 82: /* AddExp: MulExp  */
#line 897 "parser.y"
               {
        yyval = yyvsp[0];
    }
#line 2357 "parser.tab.c"
    break;

  case 83: /* AddExp: AddExp T_PLUS MulExp  */
#line 900 "parser.y"
                           {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "+";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2369 "parser.tab.c"
    break;

  case 84: /* AddExp: AddExp T_MINUS MulExp  */
#line 907 "parser.y"
                            {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "-";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2381 "parser.tab.c"
    break;

  case 85: /* RelExp: AddExp  */
#line 916 "parser.y"
               {
        yyval = yyvsp[0];
    }
#line 2389 "parser.tab.c"
    break;

  case 86: /* RelExp: RelExp T_LESS AddExp  */
#line 919 "parser.y"
                           {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "<";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2401 "parser.tab.c"
    break;

  case 87: /* RelExp: RelExp T_GREATER AddExp  */
#line 926 "parser.y"
                              {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = ">";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2413 "parser.tab.c"
    break;

  case 88: /* RelExp: RelExp T_LESSEQUAL AddExp  */
#line 933 "parser.y"
                                {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "<=";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2425 "parser.tab.c"
    break;

  case 89: /* RelExp: RelExp T_GREATEREQUAL AddExp  */
#line 940 "parser.y"
                                   {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = ">=";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2437 "parser.tab.c"
    break;

  case 90: /* EqExp: RelExp  */
#line 950 "parser.y"
              {
        yyval = yyvsp[0];
    }
#line 2445 "parser.tab.c"
    break;

  case 91: /* EqExp: EqExp T_EQUAL RelExp  */
#line 953 "parser.y"
                           {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "==";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2457 "parser.tab.c"
    break;

  case 92: /* EqExp: EqExp T_EXCLAIMEQUAL RelExp  */
#line 960 "parser.y"
                                  {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "!=";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2469 "parser.tab.c"
    break;

  case 93: /* LAndExp: EqExp  */
#line 970 "parser.y"
               {
        yyval = yyvsp[0];
    }
#line 2477 "parser.tab.c"
    break;

  case 94: /* LAndExp: LAndExp T_AMPAMP EqExp  */
#line 973 "parser.y"
                             {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "&&";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2489 "parser.tab.c"
    break;

  case 95: /* LOrExp: LAndExp  */
#line 983 "parser.y"
                {
        yyval = yyvsp[0];
    }
#line 2497 "parser.tab.c"
    break;

  case 96: /* LOrExp: LOrExp T_PIPEPIPE LAndExp  */
#line 986 "parser.y"
                                {
        auto ptr = new asgNode("BinaryOperator");
        ptr->opcode = "||";
        ptr->addSon(yyvsp[-2]);
        ptr->addSon(yyvsp[0]);
        yyval = ptr;
    }
#line 2509 "parser.tab.c"
    break;

  case 97: /* ConstExp: Exp  */
#line 996 "parser.y"
              {
        yyval = yyvsp[0];
    }
#line 2517 "parser.tab.c"
    break;


#line 2521 "parser.tab.c"

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

#line 1000 "parser.y"
