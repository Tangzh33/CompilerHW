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