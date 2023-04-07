// A Bison parser, made by GNU Bison 3.7.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "referenct.tab.h"


// Unqualified %code blocks.
#line 35 "referenct.y"

#include "SysYFDriver.h"
#define yylex driver.lexer.yylex

#line 51 "referenct.tab.c"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 143 "referenct.tab.c"

  /// Build a parser object.
  SysYFParser::SysYFParser (SysYFDriver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  SysYFParser::~SysYFParser ()
  {}

  SysYFParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  SysYFParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  SysYFParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  SysYFParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  SysYFParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  SysYFParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  SysYFParser::symbol_kind_type
  SysYFParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  SysYFParser::stack_symbol_type::stack_symbol_type ()
  {}

  SysYFParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.YY_MOVE_OR_COPY< SyntaxTree::Assembly* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Number: // Number
        value.YY_MOVE_OR_COPY< SyntaxTree::Literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Block: // Block
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::BlockStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Exp: // Exp
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::FuncDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParams: // FuncFParams
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::FuncParam> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitVal: // InitVal
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::InitVal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LVal: // LVal
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::LVal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_MatchedStmt: // MatchedStmt
      case symbol_kind::S_UnmatchedStmt: // UnmatchedStmt
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VarDef: // VarDef
        value.YY_MOVE_OR_COPY< SyntaxTree::Ptr<SyntaxTree::VarDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ArrayParamList: // ArrayParamList
      case symbol_kind::S_FuncRParams: // FuncRParams
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParamList: // FuncFParamList
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitValList: // InitValList
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::InitVal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::VarDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BType: // BType
        value.YY_MOVE_OR_COPY< SyntaxTree::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  SysYFParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.move< SyntaxTree::Assembly* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Number: // Number
        value.move< SyntaxTree::Literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Block: // Block
        value.move< SyntaxTree::Ptr<SyntaxTree::BlockStmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Exp: // Exp
        value.move< SyntaxTree::Ptr<SyntaxTree::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.move< SyntaxTree::Ptr<SyntaxTree::FuncDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParams: // FuncFParams
        value.move< SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.move< SyntaxTree::Ptr<SyntaxTree::FuncParam> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitVal: // InitVal
        value.move< SyntaxTree::Ptr<SyntaxTree::InitVal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LVal: // LVal
        value.move< SyntaxTree::Ptr<SyntaxTree::LVal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_MatchedStmt: // MatchedStmt
      case symbol_kind::S_UnmatchedStmt: // UnmatchedStmt
        value.move< SyntaxTree::Ptr<SyntaxTree::Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VarDef: // VarDef
        value.move< SyntaxTree::Ptr<SyntaxTree::VarDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ArrayParamList: // ArrayParamList
      case symbol_kind::S_FuncRParams: // FuncRParams
        value.move< SyntaxTree::PtrList<SyntaxTree::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParamList: // FuncFParamList
        value.move< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.move< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitValList: // InitValList
        value.move< SyntaxTree::PtrList<SyntaxTree::InitVal> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.move< SyntaxTree::PtrList<SyntaxTree::Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.move< SyntaxTree::PtrList<SyntaxTree::VarDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BType: // BType
        value.move< SyntaxTree::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  SysYFParser::stack_symbol_type&
  SysYFParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.copy< SyntaxTree::Assembly* > (that.value);
        break;

      case symbol_kind::S_Number: // Number
        value.copy< SyntaxTree::Literal* > (that.value);
        break;

      case symbol_kind::S_Block: // Block
        value.copy< SyntaxTree::Ptr<SyntaxTree::BlockStmt> > (that.value);
        break;

      case symbol_kind::S_Exp: // Exp
        value.copy< SyntaxTree::Ptr<SyntaxTree::Expr> > (that.value);
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.copy< SyntaxTree::Ptr<SyntaxTree::FuncDef> > (that.value);
        break;

      case symbol_kind::S_FuncFParams: // FuncFParams
        value.copy< SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > (that.value);
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.copy< SyntaxTree::Ptr<SyntaxTree::FuncParam> > (that.value);
        break;

      case symbol_kind::S_InitVal: // InitVal
        value.copy< SyntaxTree::Ptr<SyntaxTree::InitVal> > (that.value);
        break;

      case symbol_kind::S_LVal: // LVal
        value.copy< SyntaxTree::Ptr<SyntaxTree::LVal> > (that.value);
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_MatchedStmt: // MatchedStmt
      case symbol_kind::S_UnmatchedStmt: // UnmatchedStmt
        value.copy< SyntaxTree::Ptr<SyntaxTree::Stmt> > (that.value);
        break;

      case symbol_kind::S_VarDef: // VarDef
        value.copy< SyntaxTree::Ptr<SyntaxTree::VarDef> > (that.value);
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ArrayParamList: // ArrayParamList
      case symbol_kind::S_FuncRParams: // FuncRParams
        value.copy< SyntaxTree::PtrList<SyntaxTree::Expr> > (that.value);
        break;

      case symbol_kind::S_FuncFParamList: // FuncFParamList
        value.copy< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (that.value);
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.copy< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (that.value);
        break;

      case symbol_kind::S_InitValList: // InitValList
        value.copy< SyntaxTree::PtrList<SyntaxTree::InitVal> > (that.value);
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.copy< SyntaxTree::PtrList<SyntaxTree::Stmt> > (that.value);
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.copy< SyntaxTree::PtrList<SyntaxTree::VarDef> > (that.value);
        break;

      case symbol_kind::S_BType: // BType
        value.copy< SyntaxTree::Type > (that.value);
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  SysYFParser::stack_symbol_type&
  SysYFParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.move< SyntaxTree::Assembly* > (that.value);
        break;

      case symbol_kind::S_Number: // Number
        value.move< SyntaxTree::Literal* > (that.value);
        break;

      case symbol_kind::S_Block: // Block
        value.move< SyntaxTree::Ptr<SyntaxTree::BlockStmt> > (that.value);
        break;

      case symbol_kind::S_Exp: // Exp
        value.move< SyntaxTree::Ptr<SyntaxTree::Expr> > (that.value);
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.move< SyntaxTree::Ptr<SyntaxTree::FuncDef> > (that.value);
        break;

      case symbol_kind::S_FuncFParams: // FuncFParams
        value.move< SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > (that.value);
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.move< SyntaxTree::Ptr<SyntaxTree::FuncParam> > (that.value);
        break;

      case symbol_kind::S_InitVal: // InitVal
        value.move< SyntaxTree::Ptr<SyntaxTree::InitVal> > (that.value);
        break;

      case symbol_kind::S_LVal: // LVal
        value.move< SyntaxTree::Ptr<SyntaxTree::LVal> > (that.value);
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_MatchedStmt: // MatchedStmt
      case symbol_kind::S_UnmatchedStmt: // UnmatchedStmt
        value.move< SyntaxTree::Ptr<SyntaxTree::Stmt> > (that.value);
        break;

      case symbol_kind::S_VarDef: // VarDef
        value.move< SyntaxTree::Ptr<SyntaxTree::VarDef> > (that.value);
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ArrayParamList: // ArrayParamList
      case symbol_kind::S_FuncRParams: // FuncRParams
        value.move< SyntaxTree::PtrList<SyntaxTree::Expr> > (that.value);
        break;

      case symbol_kind::S_FuncFParamList: // FuncFParamList
        value.move< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (that.value);
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.move< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (that.value);
        break;

      case symbol_kind::S_InitValList: // InitValList
        value.move< SyntaxTree::PtrList<SyntaxTree::InitVal> > (that.value);
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.move< SyntaxTree::PtrList<SyntaxTree::Stmt> > (that.value);
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.move< SyntaxTree::PtrList<SyntaxTree::VarDef> > (that.value);
        break;

      case symbol_kind::S_BType: // BType
        value.move< SyntaxTree::Type > (that.value);
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.move< double > (that.value);
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.move< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  SysYFParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  SysYFParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  SysYFParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  SysYFParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  SysYFParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SysYFParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SysYFParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SysYFParser::debug_level_type
  SysYFParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SysYFParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  SysYFParser::state_type
  SysYFParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  SysYFParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  SysYFParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SysYFParser::operator() ()
  {
    return parse ();
  }

  int
  SysYFParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 24 "referenct.y"
{
// Initialize the initial location.
yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 773 "referenct.tab.c"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_CompUnit: // CompUnit
        yylhs.value.emplace< SyntaxTree::Assembly* > ();
        break;

      case symbol_kind::S_Number: // Number
        yylhs.value.emplace< SyntaxTree::Literal* > ();
        break;

      case symbol_kind::S_Block: // Block
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::BlockStmt> > ();
        break;

      case symbol_kind::S_Exp: // Exp
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::Expr> > ();
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::FuncDef> > ();
        break;

      case symbol_kind::S_FuncFParams: // FuncFParams
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > ();
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::FuncParam> > ();
        break;

      case symbol_kind::S_InitVal: // InitVal
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::InitVal> > ();
        break;

      case symbol_kind::S_LVal: // LVal
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::LVal> > ();
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_MatchedStmt: // MatchedStmt
      case symbol_kind::S_UnmatchedStmt: // UnmatchedStmt
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
        break;

      case symbol_kind::S_VarDef: // VarDef
        yylhs.value.emplace< SyntaxTree::Ptr<SyntaxTree::VarDef> > ();
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ArrayParamList: // ArrayParamList
      case symbol_kind::S_FuncRParams: // FuncRParams
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::Expr> > ();
        break;

      case symbol_kind::S_FuncFParamList: // FuncFParamList
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ();
        break;

      case symbol_kind::S_InitValList: // InitValList
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::InitVal> > ();
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::Stmt> > ();
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
        break;

      case symbol_kind::S_BType: // BType
        yylhs.value.emplace< SyntaxTree::Type > ();
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // Begin: CompUnit END
#line 100 "referenct.y"
                    {
    yystack_[1].value.as < SyntaxTree::Assembly* > ()->loc = yylhs.location;
    driver.root = yystack_[1].value.as < SyntaxTree::Assembly* > ();
    return 0;
  }
#line 1006 "referenct.tab.c"
    break;

  case 3: // CompUnit: CompUnit GlobalDecl
#line 108 "referenct.y"
                            {
		yystack_[1].value.as < SyntaxTree::Assembly* > ()->global_defs.insert(yystack_[1].value.as < SyntaxTree::Assembly* > ()->global_defs.end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end());
		yylhs.value.as < SyntaxTree::Assembly* > ()=yystack_[1].value.as < SyntaxTree::Assembly* > ();
	}
#line 1015 "referenct.tab.c"
    break;

  case 4: // CompUnit: GlobalDecl
#line 112 "referenct.y"
                    {
		yylhs.value.as < SyntaxTree::Assembly* > ()=new SyntaxTree::Assembly();
		yylhs.value.as < SyntaxTree::Assembly* > ()->global_defs.insert(yylhs.value.as < SyntaxTree::Assembly* > ()->global_defs.end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end());
  }
#line 1024 "referenct.tab.c"
    break;

  case 5: // GlobalDecl: ConstDecl
#line 119 "referenct.y"
                    {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ()=SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1033 "referenct.tab.c"
    break;

  case 6: // GlobalDecl: VarDecl
#line 123 "referenct.y"
                 {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ()=SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1042 "referenct.tab.c"
    break;

  case 7: // GlobalDecl: FuncDef
#line 127 "referenct.y"
           {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ()=SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::GlobalDef>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::FuncDef> > ()));
  }
#line 1051 "referenct.tab.c"
    break;

  case 8: // BType: INT
#line 134 "referenct.y"
         {
    yylhs.value.as < SyntaxTree::Type > ()=SyntaxTree::Type::INT;
  }
#line 1059 "referenct.tab.c"
    break;

  case 9: // BType: FLOAT
#line 137 "referenct.y"
         {
    yylhs.value.as < SyntaxTree::Type > ()=SyntaxTree::Type::FLOAT;
  }
#line 1067 "referenct.tab.c"
    break;

  case 10: // BType: VOID
#line 140 "referenct.y"
        {
    yylhs.value.as < SyntaxTree::Type > ()=SyntaxTree::Type::VOID;
  }
#line 1075 "referenct.tab.c"
    break;

  case 11: // ConstDecl: CONST BType VarDefList SEMICOLON
#line 146 "referenct.y"
                                          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
    for (auto &node : yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()) {
      node->btype = yystack_[2].value.as < SyntaxTree::Type > ();
      node->is_constant = true;
    }
  }
#line 1087 "referenct.tab.c"
    break;

  case 12: // VarDecl: BType VarDefList SEMICOLON
#line 156 "referenct.y"
                                  {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
    for (auto &node : yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()) {
      node->btype = yystack_[2].value.as < SyntaxTree::Type > ();
      node->is_constant = false;
    }
  }
#line 1099 "referenct.tab.c"
    break;

  case 13: // VarDefList: VarDefList COMMA VarDef
#line 164 "referenct.y"
                                  {
    yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
  }
#line 1108 "referenct.tab.c"
    break;

  case 14: // VarDefList: VarDef
#line 168 "referenct.y"
                {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=SyntaxTree::PtrList<SyntaxTree::VarDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()));
  }
#line 1117 "referenct.tab.c"
    break;

  case 15: // VarDef: IDENTIFIER ArrayExpList ASSIGN InitVal
#line 173 "referenct.y"
                                             {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > () = std::shared_ptr<SyntaxTree::VarDef>(new SyntaxTree::VarDef());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->name = yystack_[3].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->array_length = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->initializers = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->is_inited = true;
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->loc = yylhs.location;
  }
#line 1130 "referenct.tab.c"
    break;

  case 16: // VarDef: IDENTIFIER ArrayExpList
#line 181 "referenct.y"
                           {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()=std::shared_ptr<SyntaxTree::VarDef>(new SyntaxTree::VarDef());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->name=yystack_[1].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->array_length = yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->is_inited = false;
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::VarDef> > ()->loc = yylhs.location;
  }
#line 1142 "referenct.tab.c"
    break;

  case 17: // ArrayExpList: ArrayExpList LBRACKET Exp RBRACKET
#line 190 "referenct.y"
                                               {
    yystack_[3].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ()=yystack_[3].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  }
#line 1151 "referenct.tab.c"
    break;

  case 18: // ArrayExpList: %empty
#line 194 "referenct.y"
                {
    //not an array or get start
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ()=SyntaxTree::PtrList<SyntaxTree::Expr>();
  }
#line 1160 "referenct.tab.c"
    break;

  case 19: // InitVal: Exp
#line 201 "referenct.y"
            {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > () = std::shared_ptr<SyntaxTree::InitVal>(new SyntaxTree::InitVal());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()->isExp = true;
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()->expr = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()->loc = yylhs.location;
  }
#line 1171 "referenct.tab.c"
    break;

  case 20: // InitVal: LBRACE InitValList RBRACE
#line 207 "referenct.y"
                             {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > () = std::shared_ptr<SyntaxTree::InitVal>(new SyntaxTree::InitVal());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()->isExp = false;
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()->elementList = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::InitVal> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()->loc = yylhs.location;
  }
#line 1182 "referenct.tab.c"
    break;

  case 21: // InitValList: InitValList COMMA InitVal
#line 214 "referenct.y"
                                     {
    yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::InitVal> > ().push_back(SyntaxTree::Ptr<SyntaxTree::InitVal>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::InitVal> > () = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::InitVal> > ();
  }
#line 1191 "referenct.tab.c"
    break;

  case 22: // InitValList: InitVal
#line 218 "referenct.y"
           {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::InitVal> > () = SyntaxTree::PtrList<SyntaxTree::InitVal>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::InitVal> > ().push_back(SyntaxTree::Ptr<SyntaxTree::InitVal>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::InitVal> > ()));
  }
#line 1200 "referenct.tab.c"
    break;

  case 23: // InitValList: %empty
#line 222 "referenct.y"
          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::InitVal> > () = SyntaxTree::PtrList<SyntaxTree::InitVal>();
  }
#line 1208 "referenct.tab.c"
    break;

  case 24: // FuncDef: BType IDENTIFIER LPARENTHESE FuncFParams RPARENTHESE Block
#line 228 "referenct.y"
                                                                  {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncDef> > () = std::shared_ptr<SyntaxTree::FuncDef>(new SyntaxTree::FuncDef());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncDef> > ()->ret_type = yystack_[5].value.as < SyntaxTree::Type > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncDef> > ()->name = yystack_[4].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncDef> > ()->param_list = std::shared_ptr<SyntaxTree::FuncFParamList>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncDef> > ()->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::BlockStmt> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncDef> > ()->loc = yylhs.location;
  }
#line 1221 "referenct.tab.c"
    break;

  case 25: // FuncFParams: FuncFParamList
#line 237 "referenct.y"
                          {
  yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > () = std::shared_ptr<SyntaxTree::FuncFParamList>(new SyntaxTree::FuncFParamList());
  yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncFParamList> > ()->params = yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
  }
#line 1230 "referenct.tab.c"
    break;

  case 26: // FuncFParamList: FuncFParamList COMMA FuncFParam
#line 242 "referenct.y"
                                              {
    yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ().push_back(SyntaxTree::Ptr<SyntaxTree::FuncParam>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > () = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
  }
#line 1239 "referenct.tab.c"
    break;

  case 27: // FuncFParamList: FuncFParam
#line 246 "referenct.y"
              {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > () = SyntaxTree::PtrList<SyntaxTree::FuncParam>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ().push_back(SyntaxTree::Ptr<SyntaxTree::FuncParam>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > ()));
  }
#line 1248 "referenct.tab.c"
    break;

  case 28: // FuncFParamList: %empty
#line 250 "referenct.y"
          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > () = SyntaxTree::PtrList<SyntaxTree::FuncParam>();
  }
#line 1256 "referenct.tab.c"
    break;

  case 29: // FuncFParam: BType IDENTIFIER
#line 254 "referenct.y"
                           {
    //非数组
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > () = std::shared_ptr<SyntaxTree::FuncParam>(new SyntaxTree::FuncParam());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > ()->name = yystack_[0].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > ()->param_type=yystack_[1].value.as < SyntaxTree::Type > ();
  }
#line 1267 "referenct.tab.c"
    break;

  case 30: // FuncFParam: BType IDENTIFIER ArrayParamList
#line 260 "referenct.y"
                                   {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > () =std::shared_ptr<SyntaxTree::FuncParam>(new SyntaxTree::FuncParam());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > ()->name = yystack_[1].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > ()->param_type=yystack_[2].value.as < SyntaxTree::Type > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::FuncParam> > ()->array_index=yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  }
#line 1278 "referenct.tab.c"
    break;

  case 31: // ArrayParamList: ArrayParamList LBRACKET Exp RBRACKET
#line 267 "referenct.y"
                                                   {
    yystack_[3].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = yystack_[3].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  }
#line 1287 "referenct.tab.c"
    break;

  case 32: // ArrayParamList: LBRACKET Exp RBRACKET
#line 271 "referenct.y"
                         {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = SyntaxTree::PtrList<SyntaxTree::Expr>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()));
  }
#line 1296 "referenct.tab.c"
    break;

  case 33: // ArrayParamList: LBRACKET RBRACKET
#line 275 "referenct.y"
                     {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = SyntaxTree::PtrList<SyntaxTree::Expr>();
    //塞入空指针，表示数组的一维省略
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>());
  }
#line 1306 "referenct.tab.c"
    break;

  case 34: // Block: LBRACE BlockItemList RBRACE
#line 283 "referenct.y"
                                 {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::BlockStmt> > () = std::shared_ptr<SyntaxTree::BlockStmt>(new SyntaxTree::BlockStmt());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::BlockStmt> > ()->body = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::BlockStmt> > ()->loc = yylhs.location;
  }
#line 1316 "referenct.tab.c"
    break;

  case 35: // BlockItemList: BlockItemList BlockItem
#line 289 "referenct.y"
                                     {
    yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().insert(yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end());
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ();
  }
#line 1325 "referenct.tab.c"
    break;

  case 36: // BlockItemList: %empty
#line 293 "referenct.y"
          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
  }
#line 1333 "referenct.tab.c"
    break;

  case 37: // BlockItem: VarDecl
#line 297 "referenct.y"
                 {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1342 "referenct.tab.c"
    break;

  case 38: // BlockItem: ConstDecl
#line 301 "referenct.y"
             {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1351 "referenct.tab.c"
    break;

  case 39: // BlockItem: Stmt
#line 305 "referenct.y"
        {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Stmt>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()));
  }
#line 1360 "referenct.tab.c"
    break;

  case 40: // Stmt: MatchedStmt
#line 312 "referenct.y"
                 {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
  }
#line 1368 "referenct.tab.c"
    break;

  case 41: // Stmt: UnmatchedStmt
#line 315 "referenct.y"
                 {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
  }
#line 1376 "referenct.tab.c"
    break;

  case 42: // MatchedStmt: IF LPARENTHESE Exp RPARENTHESE MatchedStmt ELSE MatchedStmt
#line 320 "referenct.y"
                                                                       {
    auto temp = std::shared_ptr<SyntaxTree::IfStmt>(new SyntaxTree::IfStmt());
    temp->cond_exp = yystack_[4].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ();
    temp->if_statement = yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
    temp->else_statement = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1389 "referenct.tab.c"
    break;

  case 43: // MatchedStmt: LVal ASSIGN Exp SEMICOLON
#line 329 "referenct.y"
                           {
    auto temp = std::shared_ptr<SyntaxTree::AssignStmt>(new SyntaxTree::AssignStmt());
    temp->target = SyntaxTree::Ptr<SyntaxTree::LVal>(yystack_[3].value.as < SyntaxTree::Ptr<SyntaxTree::LVal> > ());
    temp->value = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1401 "referenct.tab.c"
    break;

  case 44: // MatchedStmt: Exp SEMICOLON
#line 336 "referenct.y"
                  {
    auto temp = std::shared_ptr<SyntaxTree::ExprStmt>(new SyntaxTree::ExprStmt());
    temp->exp = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1412 "referenct.tab.c"
    break;

  case 45: // MatchedStmt: RETURN Exp SEMICOLON
#line 342 "referenct.y"
                        {
    auto temp = std::shared_ptr<SyntaxTree::ReturnStmt>(new SyntaxTree::ReturnStmt());
    temp->ret = yystack_[1].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1423 "referenct.tab.c"
    break;

  case 46: // MatchedStmt: RETURN SEMICOLON
#line 348 "referenct.y"
                    {
    auto temp = std::shared_ptr<SyntaxTree::ReturnStmt>(new SyntaxTree::ReturnStmt());
    temp->ret = nullptr;
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1434 "referenct.tab.c"
    break;

  case 47: // MatchedStmt: BREAK SEMICOLON
#line 354 "referenct.y"
                   {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::shared_ptr<SyntaxTree::Stmt>(new SyntaxTree::BreakStmt());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1443 "referenct.tab.c"
    break;

  case 48: // MatchedStmt: CONTINUE SEMICOLON
#line 358 "referenct.y"
                      {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::shared_ptr<SyntaxTree::Stmt>(new SyntaxTree::ContinueStmt());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1452 "referenct.tab.c"
    break;

  case 49: // MatchedStmt: WHILE LPARENTHESE Exp RPARENTHESE MatchedStmt
#line 362 "referenct.y"
                                                 {
    auto temp = std::shared_ptr<SyntaxTree::WhileStmt>(new SyntaxTree::WhileStmt());
    temp->cond_exp = yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ();
    temp->statement = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1464 "referenct.tab.c"
    break;

  case 50: // MatchedStmt: Block
#line 369 "referenct.y"
         {
    auto temp=std::shared_ptr<SyntaxTree::BlockStmt>(new SyntaxTree::BlockStmt());
    temp = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::BlockStmt> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
  }
#line 1474 "referenct.tab.c"
    break;

  case 51: // MatchedStmt: SEMICOLON
#line 374 "referenct.y"
             {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::shared_ptr<SyntaxTree::Stmt>(new SyntaxTree::EmptyStmt());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1483 "referenct.tab.c"
    break;

  case 52: // UnmatchedStmt: IF LPARENTHESE Exp RPARENTHESE Stmt
#line 380 "referenct.y"
                                                 {
    auto temp = std::shared_ptr<SyntaxTree::IfStmt>(new SyntaxTree::IfStmt());
    temp->cond_exp = yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ();
    temp->if_statement = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
    //temp->else_statement = nullptr;
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1496 "referenct.tab.c"
    break;

  case 53: // UnmatchedStmt: IF LPARENTHESE Exp RPARENTHESE MatchedStmt ELSE UnmatchedStmt
#line 388 "referenct.y"
                                                                 {
    auto temp = std::shared_ptr<SyntaxTree::IfStmt>(new SyntaxTree::IfStmt());
    temp->cond_exp = yystack_[4].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ();
    temp->if_statement = yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
    temp->else_statement = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > () = std::dynamic_pointer_cast<SyntaxTree::Stmt>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Stmt> > ()->loc = yylhs.location;
  }
#line 1509 "referenct.tab.c"
    break;

  case 54: // FuncRParams: FuncRParams COMMA Exp
#line 399 "referenct.y"
                                 {
    yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  }
#line 1518 "referenct.tab.c"
    break;

  case 55: // FuncRParams: Exp
#line 403 "referenct.y"
       {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = SyntaxTree::PtrList<SyntaxTree::Expr>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()));
  }
#line 1527 "referenct.tab.c"
    break;

  case 56: // FuncRParams: %empty
#line 407 "referenct.y"
          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = SyntaxTree::PtrList<SyntaxTree::Expr>();
  }
#line 1535 "referenct.tab.c"
    break;

  case 57: // LVal: IDENTIFIER ArrayExpList
#line 413 "referenct.y"
                            {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::LVal> > () = std::shared_ptr<SyntaxTree::LVal>(new SyntaxTree::LVal());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::LVal> > ()->name = yystack_[1].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::LVal> > ()->array_index = yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::LVal> > ()->loc = yylhs.location;
  }
#line 1546 "referenct.tab.c"
    break;

  case 58: // Exp: LPARENTHESE Exp RPARENTHESE
#line 431 "referenct.y"
                                {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = yystack_[1].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ();
  }
#line 1554 "referenct.tab.c"
    break;

  case 59: // Exp: LVal
#line 434 "referenct.y"
        {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::LVal> > ();
  }
#line 1562 "referenct.tab.c"
    break;

  case 60: // Exp: Number
#line 437 "referenct.y"
          {
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::shared_ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Literal* > ());
  }
#line 1570 "referenct.tab.c"
    break;

  case 61: // Exp: NOT Exp
#line 440 "referenct.y"
           {
    auto temp = std::shared_ptr<SyntaxTree::UnaryCondExpr>(new SyntaxTree::UnaryCondExpr());
    temp->op = SyntaxTree::UnaryCondOp::NOT;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1582 "referenct.tab.c"
    break;

  case 62: // Exp: PLUS Exp
#line 447 "referenct.y"
                        {
    auto temp = std::shared_ptr<SyntaxTree::UnaryExpr>(new SyntaxTree::UnaryExpr());
    temp->op = SyntaxTree::UnaryOp::PLUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1594 "referenct.tab.c"
    break;

  case 63: // Exp: MINUS Exp
#line 454 "referenct.y"
                          {
    auto temp = std::shared_ptr<SyntaxTree::UnaryExpr>(new SyntaxTree::UnaryExpr());
    temp->op = SyntaxTree::UnaryOp::MINUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1606 "referenct.tab.c"
    break;

  case 64: // Exp: IDENTIFIER LPARENTHESE FuncRParams RPARENTHESE
#line 461 "referenct.y"
                                                  {
    auto temp = std::shared_ptr<SyntaxTree::FuncCallStmt>(new SyntaxTree::FuncCallStmt());
    temp->name = yystack_[3].value.as < std::string > ();
    temp->params = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1618 "referenct.tab.c"
    break;

  case 65: // Exp: Exp PLUS Exp
#line 468 "referenct.y"
                {
    auto temp = std::shared_ptr<SyntaxTree::BinaryExpr>(new SyntaxTree::BinaryExpr());
    temp->op = SyntaxTree::BinOp::PLUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1631 "referenct.tab.c"
    break;

  case 66: // Exp: Exp MINUS Exp
#line 476 "referenct.y"
                 {
    auto temp = std::shared_ptr<SyntaxTree::BinaryExpr>(new SyntaxTree::BinaryExpr());
    temp->op = SyntaxTree::BinOp::MINUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1644 "referenct.tab.c"
    break;

  case 67: // Exp: Exp MODULO Exp
#line 484 "referenct.y"
                  {
    auto temp = std::shared_ptr<SyntaxTree::BinaryExpr>(new SyntaxTree::BinaryExpr());
    temp->op = SyntaxTree::BinOp::MODULO;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1657 "referenct.tab.c"
    break;

  case 68: // Exp: Exp MULTIPLY Exp
#line 492 "referenct.y"
                    {
    auto temp = std::shared_ptr<SyntaxTree::BinaryExpr>(new SyntaxTree::BinaryExpr());
    temp->op = SyntaxTree::BinOp::MULTIPLY;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1670 "referenct.tab.c"
    break;

  case 69: // Exp: Exp DIVIDE Exp
#line 500 "referenct.y"
                  {
    auto temp = std::shared_ptr<SyntaxTree::BinaryExpr>(new SyntaxTree::BinaryExpr());
    temp->op = SyntaxTree::BinOp::DIVIDE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1683 "referenct.tab.c"
    break;

  case 70: // Exp: Exp LOR Exp
#line 508 "referenct.y"
                {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::LOR;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1696 "referenct.tab.c"
    break;

  case 71: // Exp: Exp LAND Exp
#line 516 "referenct.y"
                {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::LAND;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1709 "referenct.tab.c"
    break;

  case 72: // Exp: Exp NEQ Exp
#line 524 "referenct.y"
               {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::NEQ;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1722 "referenct.tab.c"
    break;

  case 73: // Exp: Exp EQ Exp
#line 532 "referenct.y"
              {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::EQ;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1735 "referenct.tab.c"
    break;

  case 74: // Exp: Exp LTE Exp
#line 540 "referenct.y"
               {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::LTE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1748 "referenct.tab.c"
    break;

  case 75: // Exp: Exp GTE Exp
#line 548 "referenct.y"
               {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::GTE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1761 "referenct.tab.c"
    break;

  case 76: // Exp: Exp LT Exp
#line 556 "referenct.y"
              {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::LT;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1774 "referenct.tab.c"
    break;

  case 77: // Exp: Exp GT Exp
#line 564 "referenct.y"
              {
    auto temp = std::shared_ptr<SyntaxTree::BinaryCondExpr>(new SyntaxTree::BinaryCondExpr());
    temp->op = SyntaxTree::BinaryCondOp::GT;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ());
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > () = std::dynamic_pointer_cast<SyntaxTree::Expr>(temp);
    yylhs.value.as < SyntaxTree::Ptr<SyntaxTree::Expr> > ()->loc = yylhs.location;
  }
#line 1787 "referenct.tab.c"
    break;

  case 78: // Number: FLOATCONST
#line 575 "referenct.y"
                   {
    yylhs.value.as < SyntaxTree::Literal* > () = new SyntaxTree::Literal();
    yylhs.value.as < SyntaxTree::Literal* > ()->is_const = true;
    yylhs.value.as < SyntaxTree::Literal* > ()->literal_type = SyntaxTree::Type::FLOAT;
    yylhs.value.as < SyntaxTree::Literal* > ()->float_const = yystack_[0].value.as < double > ();
    yylhs.value.as < SyntaxTree::Literal* > ()->loc = yylhs.location;
  }
#line 1799 "referenct.tab.c"
    break;

  case 79: // Number: INTCONST
#line 582 "referenct.y"
             {
    yylhs.value.as < SyntaxTree::Literal* > () = new SyntaxTree::Literal();
    yylhs.value.as < SyntaxTree::Literal* > ()->is_const = true;
    yylhs.value.as < SyntaxTree::Literal* > ()->literal_type = SyntaxTree::Type::INT;
    yylhs.value.as < SyntaxTree::Literal* > ()->int_const = yystack_[0].value.as < int > ();
    yylhs.value.as < SyntaxTree::Literal* > ()->loc = yylhs.location;
  }
#line 1811 "referenct.tab.c"
    break;


#line 1815 "referenct.tab.c"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
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


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  SysYFParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  SysYFParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  SysYFParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // SysYFParser::context.
  SysYFParser::context::context (const SysYFParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  SysYFParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  SysYFParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  SysYFParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char SysYFParser::yypact_ninf_ = -78;

  const signed char SysYFParser::yytable_ninf_ = -1;

  const short
  SysYFParser::yypact_[] =
  {
      32,   -78,   -78,   -78,    52,     3,    25,   -78,    12,   -78,
     -78,   -78,    13,   -78,   -78,   -78,     8,    -2,   -78,   -78,
       7,    52,    -5,   -78,    13,   -78,    19,    41,    27,   -78,
     111,   171,   -78,    39,    45,    52,   171,   171,   171,   171,
     111,    49,   -78,   -78,   -78,   -78,   382,   -78,   207,   156,
      48,   -78,   -78,   -78,   -78,   -78,   -78,   258,   -78,    -8,
     171,    57,   171,   171,   171,   171,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   -78,   -78,   224,   171,    71,
     -78,   111,   -78,    -7,   382,    78,    78,   -78,   -78,   -78,
      17,    17,    17,    17,   424,   424,   411,   397,   -78,   241,
     -78,   -78,   168,    53,    58,    68,    70,    13,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,    98,   334,   -78,   171,   -78,
     -78,   -78,   350,   171,   -78,   -78,   171,   171,   -78,   382,
     -78,   277,   296,   366,   108,   132,   -78,    93,   -78,   -78,
      81,   171,   132,   315,   -78,   -78,   108,    82,   108
  };

  const signed char
  SysYFParser::yydefact_[] =
  {
       0,     8,     9,    10,     0,     0,     0,     4,     0,     5,
       6,     7,     0,     1,     2,     3,    18,     0,    14,    18,
       0,    28,    16,    12,     0,    11,     0,     0,    25,    27,
       0,     0,    13,    29,     0,     0,     0,     0,     0,     0,
      23,    18,    79,    78,    15,    59,    19,    60,     0,     0,
      30,    36,    24,    26,    62,    63,    61,     0,    22,     0,
      56,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    33,     0,     0,     0,
      58,     0,    20,     0,    55,    65,    66,    68,    69,    67,
      77,    76,    74,    75,    73,    72,    71,    70,    32,     0,
      51,    34,     0,     0,     0,     0,     0,     0,    38,    37,
      50,    35,    39,    40,    41,    59,     0,    21,     0,    64,
      31,    46,     0,     0,    47,    48,     0,     0,    44,    54,
      45,     0,     0,     0,     0,     0,    43,     0,    49,    52,
      40,     0,     0,     0,    42,    53,     0,     0,     0
  };

  const signed char
  SysYFParser::yypgoto_[] =
  {
     -78,   -78,   -78,   113,    10,    42,    43,   112,   101,    85,
     -35,   -78,   -78,   -78,   -78,    95,   -78,    94,   -78,   -78,
       0,   -68,    -9,   -78,   -77,   -30,   -78
  };

  const unsigned char
  SysYFParser::yydefgoto_[] =
  {
       0,     5,     6,     7,     8,     9,    10,    17,    18,    22,
      44,    59,    11,    27,    28,    29,    50,   110,    79,   111,
     112,   144,   114,    83,    45,   116,    47
  };

  const unsigned char
  SysYFParser::yytable_[] =
  {
      46,    48,   115,    13,    30,    58,    54,    55,    56,    57,
      46,   113,    81,   118,    12,   119,    82,    23,    24,    77,
      31,    62,    63,    64,    65,    66,    25,    24,    14,    21,
      84,    26,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    26,   117,    35,    99,    16,
      19,    46,     1,     2,     3,     4,    33,   115,   115,     1,
       2,     3,     4,    34,    49,   115,   138,   140,    51,   115,
      60,   115,   122,    78,   123,    36,    37,   124,   147,     1,
       2,     3,    31,    38,    64,    65,    66,   125,   129,   107,
     100,   126,    39,   131,    51,   101,   132,   133,     1,     2,
       3,     4,   102,   103,   104,   105,   106,   127,    41,    42,
      43,   143,    36,    37,   141,    36,    37,   142,   148,    15,
      38,   108,   109,    38,    20,    32,    61,   100,    52,    39,
      53,    51,    39,   145,    40,   139,    36,    37,     0,   102,
     103,   104,   105,   137,    38,    41,    42,    43,    41,    42,
      43,   100,     0,    39,     0,    51,     0,     0,     0,     0,
      36,    37,     0,   102,   103,   104,   105,   106,    38,    41,
      42,    43,    36,    37,     0,    36,    37,    39,     0,     0,
      38,     0,    76,    38,     0,     0,     0,   121,     0,    39,
       0,     0,    39,    41,    42,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    41,    42,    43,    41,    42,
      43,    62,    63,    64,    65,    66,     0,    67,    68,     0,
      69,    70,    71,    72,    73,    74,     0,     0,    62,    63,
      64,    65,    66,    75,    67,    68,     0,    69,    70,    71,
      72,    73,    74,     0,     0,    62,    63,    64,    65,    66,
      98,    67,    68,     0,    69,    70,    71,    72,    73,    74,
       0,     0,    62,    63,    64,    65,    66,   120,    67,    68,
       0,    69,    70,    71,    72,    73,    74,     0,     0,     0,
      80,    62,    63,    64,    65,    66,     0,    67,    68,     0,
      69,    70,    71,    72,    73,    74,     0,     0,     0,   134,
      62,    63,    64,    65,    66,     0,    67,    68,     0,    69,
      70,    71,    72,    73,    74,     0,     0,     0,   135,    62,
      63,    64,    65,    66,     0,    67,    68,     0,    69,    70,
      71,    72,    73,    74,     0,     0,     0,   146,    62,    63,
      64,    65,    66,     0,    67,    68,     0,    69,    70,    71,
      72,    73,    74,   128,    62,    63,    64,    65,    66,     0,
      67,    68,     0,    69,    70,    71,    72,    73,    74,   130,
      62,    63,    64,    65,    66,     0,    67,    68,     0,    69,
      70,    71,    72,    73,    74,   136,    62,    63,    64,    65,
      66,     0,    67,    68,     0,    69,    70,    71,    72,    73,
      74,    62,    63,    64,    65,    66,     0,    67,    68,     0,
      69,    70,    71,    72,    73,    62,    63,    64,    65,    66,
       0,    67,    68,     0,    69,    70,    71,    72,    62,    63,
      64,    65,    66,     0,    67,    68,     0,    69,    70
  };

  const short
  SysYFParser::yycheck_[] =
  {
      30,    31,    79,     0,     9,    40,    36,    37,    38,    39,
      40,    79,    20,    20,     4,    22,    24,    19,    20,    49,
      25,     4,     5,     6,     7,     8,    19,    20,     3,    21,
      60,    21,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    35,    81,    20,    78,    37,
      37,    81,    27,    28,    29,    30,    37,   134,   135,    27,
      28,    29,    30,    22,    25,   142,   134,   135,    23,   146,
      21,   148,   102,    25,    21,     4,     5,    19,   146,    27,
      28,    29,    25,    12,     6,     7,     8,    19,   118,    79,
      19,    21,    21,   123,    23,    24,   126,   127,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     9,    37,    38,
      39,   141,     4,     5,    21,     4,     5,    36,    36,     6,
      12,    79,    79,    12,    12,    24,    41,    19,    34,    21,
      35,    23,    21,   142,    23,   135,     4,     5,    -1,    31,
      32,    33,    34,    35,    12,    37,    38,    39,    37,    38,
      39,    19,    -1,    21,    -1,    23,    -1,    -1,    -1,    -1,
       4,     5,    -1,    31,    32,    33,    34,    35,    12,    37,
      38,    39,     4,     5,    -1,     4,     5,    21,    -1,    -1,
      12,    -1,    26,    12,    -1,    -1,    -1,    19,    -1,    21,
      -1,    -1,    21,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    38,    39,    37,    38,
      39,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      13,    14,    15,    16,    17,    18,    -1,    -1,     4,     5,
       6,     7,     8,    26,    10,    11,    -1,    13,    14,    15,
      16,    17,    18,    -1,    -1,     4,     5,     6,     7,     8,
      26,    10,    11,    -1,    13,    14,    15,    16,    17,    18,
      -1,    -1,     4,     5,     6,     7,     8,    26,    10,    11,
      -1,    13,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      22,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      13,    14,    15,    16,    17,    18,    -1,    -1,    -1,    22,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,    13,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    22,     4,
       5,     6,     7,     8,    -1,    10,    11,    -1,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    22,     4,     5,
       6,     7,     8,    -1,    10,    11,    -1,    13,    14,    15,
      16,    17,    18,    19,     4,     5,     6,     7,     8,    -1,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    19,
       4,     5,     6,     7,     8,    -1,    10,    11,    -1,    13,
      14,    15,    16,    17,    18,    19,     4,     5,     6,     7,
       8,    -1,    10,    11,    -1,    13,    14,    15,    16,    17,
      18,     4,     5,     6,     7,     8,    -1,    10,    11,    -1,
      13,    14,    15,    16,    17,     4,     5,     6,     7,     8,
      -1,    10,    11,    -1,    13,    14,    15,    16,     4,     5,
       6,     7,     8,    -1,    10,    11,    -1,    13,    14
  };

  const signed char
  SysYFParser::yystos_[] =
  {
       0,    27,    28,    29,    30,    46,    47,    48,    49,    50,
      51,    57,    49,     0,     3,    48,    37,    52,    53,    37,
      52,    21,    54,    19,    20,    19,    49,    58,    59,    60,
       9,    25,    53,    37,    22,    20,     4,     5,    12,    21,
      23,    37,    38,    39,    55,    69,    70,    71,    70,    25,
      61,    23,    62,    60,    70,    70,    70,    70,    55,    56,
      21,    54,     4,     5,     6,     7,     8,    10,    11,    13,
      14,    15,    16,    17,    18,    26,    26,    70,    25,    63,
      22,    20,    24,    68,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    26,    70,
      19,    24,    31,    32,    33,    34,    35,    49,    50,    51,
      62,    64,    65,    66,    67,    69,    70,    55,    20,    22,
      26,    19,    70,    21,    19,    19,    21,     9,    19,    70,
      19,    70,    70,    70,    22,    22,    19,    35,    66,    65,
      66,    21,    36,    70,    66,    67,    22,    66,    36
  };

  const signed char
  SysYFParser::yyr1_[] =
  {
       0,    45,    46,    47,    47,    48,    48,    48,    49,    49,
      49,    50,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    56,    57,    58,    59,    59,    59,    60,
      60,    61,    61,    61,    62,    63,    63,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    69,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    71
  };

  const signed char
  SysYFParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     3,     3,     1,     4,     2,     4,     0,     1,
       3,     3,     1,     0,     6,     1,     3,     1,     0,     2,
       3,     4,     3,     2,     3,     2,     0,     1,     1,     1,
       1,     1,     7,     4,     2,     3,     2,     2,     2,     5,
       1,     1,     5,     7,     3,     1,     0,     2,     3,     1,
       1,     2,     2,     2,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const SysYFParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "END", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MODULO", "ASSIGN", "GT", "LT", "NOT", "LTE",
  "GTE", "EQ", "NEQ", "LAND", "LOR", "SEMICOLON", "COMMA", "LPARENTHESE",
  "RPARENTHESE", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "INT",
  "FLOAT", "VOID", "CONST", "RETURN", "WHILE", "BREAK", "CONTINUE", "IF",
  "ELSE", "IDENTIFIER", "INTCONST", "FLOATCONST", "EOL", "COMMENT",
  "BLANK", "UPLUS", "UMINUS", "$accept", "Begin", "CompUnit", "GlobalDecl",
  "BType", "ConstDecl", "VarDecl", "VarDefList", "VarDef", "ArrayExpList",
  "InitVal", "InitValList", "FuncDef", "FuncFParams", "FuncFParamList",
  "FuncFParam", "ArrayParamList", "Block", "BlockItemList", "BlockItem",
  "Stmt", "MatchedStmt", "UnmatchedStmt", "FuncRParams", "LVal", "Exp",
  "Number", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  SysYFParser::yyrline_[] =
  {
       0,   100,   100,   108,   112,   119,   123,   127,   134,   137,
     140,   146,   156,   164,   168,   173,   181,   190,   194,   201,
     207,   214,   218,   222,   228,   237,   242,   246,   250,   254,
     260,   267,   271,   275,   283,   289,   293,   297,   301,   305,
     312,   315,   320,   329,   336,   342,   348,   354,   358,   362,
     369,   374,   380,   388,   399,   403,   407,   413,   431,   434,
     437,   440,   447,   454,   461,   468,   476,   484,   492,   500,
     508,   516,   524,   532,   540,   548,   556,   564,   575,   582
  };

  void
  SysYFParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  SysYFParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2434 "referenct.tab.c"

#line 591 "referenct.y"


// Register errors to the driver:
void yy::SysYFParser::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
