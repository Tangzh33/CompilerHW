%{
#include <cctype>
#include <cstdio>
#include <string>
#define YYEOF 0
int yylex();
int main() {
  do {
  } while (yylex() != YYEOF);
}
std::string yyloc = "<stdin>";
enum TokenFlags {
  StartOfLine = 0x01 , LeadingSpace = 0x02 , DisableExpand = 0x04 , NeedsCleaning = 0x08 ,
  LeadingEmptyMacro = 0x10 , HasUDSuffix = 0x20 , HasUCN = 0x40 , IgnoredComma = 0x80 ,
  StringifiedInMacro = 0x100 , CommaAfterElided = 0x200 , IsEditorPlaceholder = 0x400 , IsReinjected = 0x800
};
std::string yytokenFlag[] = {
  "StartOfLine", "LeadingSpace", "DisableExpand", "NeedsCleaning",
  "LeadingEmptyMacro", "HasUDSuffix", "HasUCN", "IgnoredComma",
  "StringifiedInMacro", "CommaAfterElided", "IsEditorPlaceholder", " IsReinjected"
};
void yyGenerateTokenFlags(std::string & yy_token_flag, int yycolumn, int yyleng, int yy_space, int& yy_first) {
  int yy_tag = 0, yy_curr_loc = yycolumn - yyleng;
  if(yy_space > 0 && yy_curr_loc - yy_space == 1)
    yy_tag |= LeadingSpace;
  if(yy_first == 0)
  {
    yy_tag |= StartOfLine;
    yy_first = 1;
  }
  for (int i = 0; i < 12; ++i)
    if (yy_tag & (1 << i))
      yy_token_flag += " [" + yytokenFlag[i] + "]";
}
int yyrow = 1, yycolumn = 1, yycolpre = 1;
int yy_space = -1, yy_first = 0;
#define YY_USER_ACTION                                                         \
  do {                                                                         \
    yycolumn += yyleng;                                                        \
  } while (0);
%}
%option noyywrap
%%
#.* {
  std::string s(yytext);
  auto l = s.find("\""), r = s.rfind("\"");
  yyloc = s.substr(l + 1, r - l - 1);
  for (int i = 0; i < s.size(); ++i)
    if (std::isdigit(s[i])) {
      for (yyrow = 0; i < s.size() && std::isdigit(s[i]); ++i)
        yyrow = yyrow * 10 + s[i] - '0';
      --yyrow;
      break;
    }
}
\n {
  ++yyrow;
  yycolpre = yycolumn;
  yycolumn = 1;
  yy_first = 0;
  yy_space = -1;
}
[\f\r\t\v] {}
int {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "int '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
float {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "float '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
char {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "char '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
long {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "long '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
const {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "const '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
= {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "equal '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
void {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "void '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
if {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "if '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
else {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "else '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
while {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "while '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
do {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "do '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
break {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "break '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
continue {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "continue '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
return {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "return '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\( {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "l_paren '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\) {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "r_paren '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\{ {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "l_brace '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\} {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "r_brace '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\[ {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "l_square '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\] {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "r_square '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
; {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "semi '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
, {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "comma '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext, yy_token_flag.c_str(), yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
([0-9]+\.?[0-9]*|[0-9]*\.?[0-9]+)([eE][+-]?[0-9]+)? {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "numeric_constant '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
0x([0-9a-fA-F]+\.?[0-9a-fA-F]*|[0-9a-fA-F]*\.?[0-9a-fA-F]+)([pP][+-]?[0-9]+)? {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "numeric_constant '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
[a-zA-Z_][a-zA-Z_0-9]* {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "identifier '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\+ {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "plus '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
- {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "minus '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
! {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "exclaim '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\* {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "star '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\/ {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "slash '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
% {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "percent '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\< {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "less '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
> {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "greater '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\<= {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "lessequal '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
>= {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "greaterequal '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
== {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "equalequal '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
!= {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "exclaimequal '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
&& {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "ampamp '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\|\| {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "pipepipe '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\.\.\. {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "ellipsis '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
\"[^,\n]*\" {
  std::string yy_token_flag = "";
  yyGenerateTokenFlags(yy_token_flag, yycolumn, yyleng, yy_space, yy_first);
  std::fprintf(yyout, "string_literal '%s'\t%s\tLoc=<%s:%d:%d>\n", yytext,
               yy_token_flag.c_str(), yyloc.c_str(), yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
<<EOF>> {
  std::fprintf(yyout, "eof ''\t\tLoc=<%s:%d:%d>\n", yyloc.c_str(), yyrow - 1,
               yycolpre - yyleng);
  return YYEOF;
}
[ ] {
  yy_space = yycolumn - yyleng;
}
. {
  std::fprintf(yyout, "unknown '%s'\t\tLoc=<%s:%d:%d>\n", yytext, yyloc.c_str(),
               yyrow, yycolumn - yyleng);
  return ~YYEOF;
}
%%