#include <string>
#include <vector>
#include <memory>
#include <llvm/Support/JSON.h>
#include "asg_Node.h"
#include <iostream>
#define yyerror(x)                                                             \
  do {                                                                         \
    llvm::errs() << (x);                                                       \
  } while (0)

void asgNode::addSon(asgNode* son)
{
  sons.emplace_back(std::unique_ptr<asgNode>(son)); 
}
void asgNode::addSon(std::unique_ptr<asgNode>&& son)
{ 
  sons.emplace_back(std::move(son));
}
llvm::json::Value asgNode::toJson()
{
  // llvm::json::Object tmp{
  //   {"kind", kind},
  //   {"name", name},
  //   {"value", value},
  //   {"type", type},
  //   {"inner", llvm::json::Array{}}
  // };
  llvm::json::Object tmp;
  if(kind!="") tmp.try_emplace("kind", kind);
  if(name!="") tmp.try_emplace("name", name);
  if(value!="") tmp.try_emplace("value", value);
  if(type!="") tmp.insert({"type", llvm::json::Object{{"qualType", type}}});
  if(opcode!="") tmp.try_emplace("opcode", opcode);
  if(castKind!="") tmp.try_emplace("castKind", castKind);
  if(funcReturnType!="") tmp.try_emplace("funcReturnType", funcReturnType);
  if(sons.size()) tmp.try_emplace("inner", llvm::json::Array{});
  for(auto&& it: sons) tmp.get("inner")->getAsArray()->push_back(it->toJson());
  return tmp;
}
void asgNode::print(int depth) const
{
  yyerror("|");
  for(int i=0;i<depth;++i) yyerror(" ");
  yyerror("-"+kind+" "+name+" "+value);
  for(auto&& it: sons)
  {
    yyerror("\n");
    it->print(depth+1);
  }
  if(!depth) yyerror("\n\n");
}
void asgNode::clear() {
  // clear sons memory
  for (auto &&it : sons) {
    it->clear();
    it.reset();
  }
}
void asgNode::moveSons(asgNode* node)
{
  for(auto&& it: node->sons)
  {
    sons.emplace_back(std::move(it));
  }
  node->sons.clear();
  delete node;
}

int countChar(const std::string &s)
{
    char curr,next;
    int count = 0;
    for(int i=0; i<s.size(); i++){
      curr = s[i];
      next = s[i+1];
      if(curr == '\\'){
        count++;
        if(next == '\\'){
            i++;
        }
        else if(next == '\"'){
            i++;
        }else if(next == 'n'){
            i++;
        }else if(next == 't'){
            i++;
        }else if(next == 'r'){
            i++;
        }else if(next == 'b'){
            i++;
        }else if(next == 'f'){
            i++;
        }else if(next == 'a'){
            i++;
        }else if(next == 'v'){
            i++;
        }else if(next == '\''){
            i++;
        }else{
            count--;
            i++;
        }
      }
      else{
          count++;
      }
    }
    return count;
}

void binaryImplicitCast(asgNode * lhs, asgNode * rhs, asgNode* head)
{
  /* 
  Rule: Low Cast to Higher;
  int -> float;
  int -> double;
  float -> double;
  int -> long;
  int -> long long;
  */
  if(lhs->type == rhs -> type)
  {
    head->addSon(lhs);
    head->addSon(rhs);
    head->type = lhs->type;
  }
  else
  {
    bool l_flag_float, l_flag_double, l_flag_long, l_flag_int, l_flag_longlong;
    bool r_flag_float, r_flag_double, r_flag_long, r_flag_int, r_flag_longlong;
    l_flag_float = (lhs->type == "float" || lhs->type == "const float");
    l_flag_double = (lhs->type == "double" || lhs->type == "const double");
    l_flag_long = (lhs->type == "long" || lhs->type == "const long");
    l_flag_int = (lhs->type == "int" || lhs->type == "const int");
    l_flag_longlong = (lhs->type == "long long" || lhs->type == "const long long");
    r_flag_float = (rhs->type == "float" || rhs->type == "const float");
    r_flag_double = (rhs->type == "double" || rhs->type == "const double");
    r_flag_long = (rhs->type == "long" || rhs->type == "const long");
    r_flag_int = (rhs->type == "int" || rhs->type == "const int");
    r_flag_longlong = (rhs->type == "long long" || rhs->type == "const long long");
    // int -> float;
    if(l_flag_int && r_flag_float)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralToFloating";
      tmp->type = "float";
      head->type = "float";
      tmp->addSon(lhs);
      head->addSon(tmp);
      head->addSon(rhs);
    }
    else if(l_flag_float && r_flag_int)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralToFloating";
      tmp->type = "float";
      head->type = "float";
      tmp->addSon(rhs);
      head->addSon(lhs);
      head->addSon(tmp);
    }
  // int -> double;
    else if(l_flag_int && r_flag_double)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralToFloating";
      tmp->type = "double";
      head->type = "double";
      tmp->addSon(lhs);
      head->addSon(tmp);
      head->addSon(rhs);
    }
    else if(l_flag_double && r_flag_int)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralToFloating";
      tmp->type = "double";
      head->type = "double";
      tmp->addSon(rhs);
      head->addSon(lhs);
      head->addSon(tmp);
    }
  // float -> double;
    else if(l_flag_float && r_flag_double)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "FloatingToDouble";
      tmp->type = "double";
      head->type = "double";
      tmp->addSon(lhs);
      head->addSon(tmp);
      head->addSon(rhs);
    }
    else if(l_flag_double && r_flag_float)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "FloatingToDouble";
      tmp->type = "double";
      head->type = "double";
      tmp->addSon(rhs);
      head->addSon(lhs);
      head->addSon(tmp);
    }
  // int -> long;
    else if(l_flag_int && r_flag_long)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralCast";
      tmp->type = "long";
      head->type = "long";
      tmp->addSon(lhs);
      head->addSon(tmp);
      head->addSon(rhs);
    }
    else if(l_flag_long && r_flag_int)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralCast";
      tmp->type = "long";
      head->type = "long";
      tmp->addSon(rhs);
      head->addSon(lhs);
      head->addSon(tmp);
    }
  // int -> long long;
    else if(l_flag_int && r_flag_longlong)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralCast";
      tmp->type = "long long";
      head->type = "long long";
      tmp->addSon(lhs);
      head->addSon(tmp);
      head->addSon(rhs);
    }
    else if(l_flag_longlong && r_flag_int)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->castKind = "IntegralCast";
      tmp->type = "long long";
      head->type = "long long";
      tmp->addSon(rhs);
      head->addSon(lhs);
      head->addSon(tmp);
    }
    else
    {
      // yyerror("Implicit Cast Error");
      // exit(1);
      head->addSon(lhs);
      head->addSon(rhs);
      head->type = lhs->type;
    }
  }
}
void forceImplicitCast(asgNode * oprand, std::string type, asgNode* head)
{
  /* 
  Rule: all cast to type;
  type: int, float, double, long, long long;
  oprand Type: int, float, double, long long;
  */
  // std::cout << "Debug: " << oprand->type << " " << type << std::endl;
  if(oprand->type == type)
  {
    head->addSon(oprand);
    head->type = oprand->type;
  }
  else
  {
    bool l_flag_int, l_flag_float, l_flag_double, l_flag_long, l_flag_longlong;
    bool r_flag_int, r_flag_float, r_flag_double, r_flag_long, r_flag_longlong;
    r_flag_int = (oprand->type == "int" || oprand->type == "const int");
    r_flag_float = (oprand->type == "float" || oprand->type == "const float");
    r_flag_double = (oprand->type == "double" || oprand->type == "const double");
    r_flag_long = (oprand->type == "long" || oprand->type == "const long");
    r_flag_longlong = (oprand->type == "long long" || oprand->type == "const long long");
    l_flag_int = (type == "int" || type == "const int");
    l_flag_float = (type == "float" || type == "const float");
    l_flag_double = (type == "double" || type == "const double");
    l_flag_long = (type == "long" || type == "const long");
    l_flag_longlong = (type == "long long" || type == "const long long");
    // Type: int
    if(l_flag_int)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->type = "int";
      head->type = "int";
      if(r_flag_float)
      {
        tmp->castKind = "FloatingToIntegral";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_double)
      {
        tmp->castKind = "FloatingToIntegral";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_long)
      {
        tmp->castKind = "IntegralCast";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_longlong)
      {
        tmp->castKind = "IntegralCast";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else
      {
        // yyerror("Implicit Cast Error");
        // exit(1);
        head->addSon(oprand);
        head->type = oprand->type;
      }
    }
    else if(l_flag_float)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->type = "float";
      head->type = "float";
      if(r_flag_int)
      {
        tmp->castKind = "IntegralToFloating";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_double)
      {
        tmp->castKind = "FloatingToFloat";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_long)
      {
        tmp->castKind = "IntegralToFloating";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_longlong)
      {
        tmp->castKind = "IntegralToFloating";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else
      {
        // yyerror("Implicit Cast Error");
        // exit(1);
        head->addSon(oprand);
        head->type = oprand->type;
      }
    }
    else if(l_flag_double)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->type = "double";
      head->type = "double";
      if(r_flag_int)
      {
        tmp->castKind = "IntegralToFloating";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_float)
      {
        tmp->castKind = "FloatingToDouble";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_long)
      {
        tmp->castKind = "IntegralToFloating";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_longlong)
      {
        tmp->castKind = "IntegralToFloating";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else
      {
        // yyerror("Implicit Cast Error");
        // exit(1);
        head->addSon(oprand);
        head->type = oprand->type;
      }
    }
    else if(l_flag_long)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->type = "long";
      head->type = "long";
      if(r_flag_int)
      {
        tmp->castKind = "IntegralCast";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_float)
      {
        tmp->castKind = "FloatingToIntegral";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_double)
      {
        tmp->castKind = "FloatingToIntegral";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_longlong)
      {
        tmp->castKind = "IntegralCast";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else
      {
        // yyerror("Implicit Cast Error");
        // exit(1);
        head->addSon(oprand);
        head->type = oprand->type;
      }
    }
    else if(l_flag_longlong)
    {
      auto tmp = new asgNode("ImplicitCastExpr");
      tmp->type = "long long";
      head->type = "long long";
      if(r_flag_int)
      {
        tmp->castKind = "IntegralCast";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_float)
      {
        tmp->castKind = "FloatingToIntegral";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_double)
      {
        tmp->castKind = "FloatingToIntegral";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else if(r_flag_long)
      {
        tmp->castKind = "IntegralCast";
        tmp->addSon(oprand);
        head->addSon(tmp);
      }
      else
      {
        // yyerror("Implicit Cast Error");
        // exit(1);
        head->addSon(oprand);
        head->type = oprand->type;
      }
    }
  }
}

// void forceImplicitCast(std::unique_ptr<asgNode> &&oprand, std::string type, asgNode* head)
// {
//   /* 
//   Rule: all cast to type;
//   type: int, float, double, long, long long;
//   oprand Type: int, float, double, long long;
//   */
//   // std::cout << "Debug: " << oprand->type << " " << type << std::endl;
//   if(oprand->type == type)
//   {
//     head->sons.emplace_back(std::move(oprand));
//     head->type = oprand->type;
//   }
//   else
//   {
//     bool l_flag_int, l_flag_float, l_flag_double, l_flag_long, l_flag_longlong;
//     bool r_flag_int, r_flag_float, r_flag_double, r_flag_long, r_flag_longlong;
//     l_flag_int = (oprand->type == "int" || oprand->type == "const int");
//     l_flag_float = (oprand->type == "float" || oprand->type == "const float");
//     l_flag_double = (oprand->type == "double" || oprand->type == "const double");
//     l_flag_long = (oprand->type == "long" || oprand->type == "const long");
//     l_flag_longlong = (oprand->type == "long long" || oprand->type == "const long long");
//     r_flag_int = (type == "int" || type == "const int");
//     r_flag_float = (type == "float" || type == "const float");
//     r_flag_double = (type == "double" || type == "const double");
//     r_flag_long = (type == "long" || type == "const long");
//     r_flag_longlong = (type == "long long" || type == "const long long");
//     // Type: int
//     if(l_flag_int)
//     {
//       auto tmp = new asgNode("ImplicitCastExpr");
//       tmp->type = "int";
//       head->type = "int";
//       if(r_flag_float)
//       {
//         tmp->castKind = "FloatingToIntegral";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_double)
//       {
//         tmp->castKind = "FloatingToIntegral";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_long)
//       {
//         tmp->castKind = "IntegralCast";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_longlong)
//       {
//         tmp->castKind = "IntegralCast";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else
//       {
//         // yyerror("Implicit Cast Error");
//         // exit(1);
//         head->sons.emplace_back(std::move(oprand));
//         head->type = oprand->type;
//       }
//     }
//     else if(l_flag_float)
//     {
//       auto tmp = new asgNode("ImplicitCastExpr");
//       tmp->type = "float";
//       head->type = "float";
//       if(r_flag_int)
//       {
//         tmp->castKind = "IntegralToFloating";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_double)
//       {
//         tmp->castKind = "FloatingToFloat";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_long)
//       {
//         tmp->castKind = "IntegralToFloating";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_longlong)
//       {
//         tmp->castKind = "IntegralToFloating";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else
//       {
//         // yyerror("Implicit Cast Error");
//         // exit(1);
//         head->sons.emplace_back(std::move(oprand));
//         head->type = oprand->type;
//       }
//     }
//     else if(l_flag_double)
//     {
//       auto tmp = new asgNode("ImplicitCastExpr");
//       tmp->type = "double";
//       head->type = "double";
//       if(r_flag_int)
//       {
//         tmp->castKind = "IntegralToFloating";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_float)
//       {
//         tmp->castKind = "FloatingToDouble";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_long)
//       {
//         tmp->castKind = "IntegralToFloating";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_longlong)
//       {
//         tmp->castKind = "IntegralToFloating";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else
//       {
//         // yyerror("Implicit Cast Error");
//         // exit(1);
//         head->sons.emplace_back(std::move(oprand));
//         head->type = oprand->type;
//       }
//     }
//     else if(l_flag_long)
//     {
//       auto tmp = new asgNode("ImplicitCastExpr");
//       tmp->type = "long";
//       head->type = "long";
//       if(r_flag_int)
//       {
//         tmp->castKind = "IntegralCast";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_float)
//       {
//         tmp->castKind = "FloatingToIntegral";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_double)
//       {
//         tmp->castKind = "FloatingToIntegral";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_longlong)
//       {
//         tmp->castKind = "IntegralCast";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else
//       {
//         // yyerror("Implicit Cast Error");
//         // exit(1);
//         head->sons.emplace_back(std::move(oprand));
//         head->type = oprand->type;
//       }
//     }
//     else if(l_flag_longlong)
//     {
//       auto tmp = new asgNode("ImplicitCastExpr");
//       tmp->type = "long long";
//       head->type = "long long";
//       if(r_flag_int)
//       {
//         tmp->castKind = "IntegralCast";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_float)
//       {
//         tmp->castKind = "FloatingToIntegral";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_double)
//       {
//         tmp->castKind = "FloatingToIntegral";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else if(r_flag_long)
//       {
//         tmp->castKind = "IntegralCast";
//         tmp->sons.emplace_back(std::move(oprand));
//         head->addSon(tmp);
//       }
//       else
//       {
//         // yyerror("Implicit Cast Error");
//         // exit(1);
//         head->sons.emplace_back(std::move(oprand));
//         head->type = oprand->type;
//       }
//     }
//   }
// }