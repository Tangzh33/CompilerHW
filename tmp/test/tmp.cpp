// #include <iostream>
// #include <sstream>
// #include <string>

// int main() {
//   // int base = 16;
//   // std::string numberString[] = {"1", "0xb", "1114321", "0x12a", "001",
//   "070",
//   // "0x7fFffffF", "0x80000000"}; char *end; long long int number; for (auto
//   // &&it : numberString)
//   // {
//   //     std::string s = it;
//   //     if (s.find("0x") != std::string::npos)
//   //     {
//   //         int x;
//   //         std::stringstream ss;
//   //         ss << std::hex << s;
//   //         ss >> x;
//   //         std::string value = std::to_string(x);
//   //         std::cout << value << std::endl;
//   //     }
//   //     else if(s.length() > 1 && s[0] == '0')
//   //     {
//   //         long long x;
//   //         std::stringstream ss;
//   //         ss << std::oct << s;
//   //         ss >> x;
//   //         std::string value = std::to_string(x);
//   //         std::cout << value << std::endl;
//   //     }
//   // }
//   // std::string s = "int *[2][3]", t = "[1][2][3]";
//   // std::string::size_type position = 0;
//   // // while((position=t.find_last_of('[',position)) != std::string::npos)
//   // for(auto &&it : t)
//   // {
//   //     std::cout << "Debug: " << it << std::endl;
//   //     if(it == '[')
//   //     {
//   //         if((position = s.find_last_of("[")) == std::string::npos)
//   //         {
//   //             std::cout << "Debug Depointer2: " <<position << std::endl;
//   //             position = s.find_last_of("*");
//   //             s = s.substr(0, position - 1);
//   //         }
//   //         else
//   //         {
//   //             std::cout << "Debug Depointer3: " <<position << std::endl;
//   //             s = s.substr(0, position);
//   //         }
//   //     }
//   // }
//   // {
//   //     std::cout << "Debug Depointer1: " <<position << std::endl;
//   //     t = t.substr(0, position);
//   //     std::cout << t << std::endl;
//   //     // if((position = s.find_last_of("[")) == std::string::npos)
//   //     // {
//   //     //     std::cout << "Debug Depointer2: " <<position << std::endl;
//   //     //     position = s.find_last_of("*");
//   //     //     s = s.substr(0, position);
//   //     // }
//   //     // else
//   //     // {
//   //     //     std::cout << "Debug Depointer3: " <<position << std::endl;
//   //     //     s = s.substr(0, position);
//   //     // }
//   // }
//   std::string s = "const int";
//   std::string s1 = s.substr(6, s.size() - 1);
//   std::cout << s1 << std::endl;
//   return 0;
// }

#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
  string s = "int [12][13]";
  regex re("\\d+");
  smatch match;
  if (regex_search(s, match, re)) {
    int n = stoi(match[0]);
    cout << "The number is: " << n << endl;
  } else {
    cout << "No number found in the string." << endl;
  }
  return 0;
}