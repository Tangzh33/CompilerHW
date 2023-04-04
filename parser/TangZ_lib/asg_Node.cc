#include <string>
#include <vector>
#include <memory>
#include <llvm/Support/JSON.h>
#include "asg_Node.h"
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
  llvm::json::Object tmp{
    {"kind", kind},
    {"name", name},
    {"value", value},
    {"inner", llvm::json::Array{}}
  };
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
