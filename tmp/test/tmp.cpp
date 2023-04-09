#include <iostream>
#include <string>
#include <sstream>

int main()
{
    int base = 16;
    std::string numberString[] = {"1", "0xb", "1114321", "0x12a", "001", "070"};
    char *end;
    long long int number;
    for (auto &&it : numberString)
    {
        std::string s = it;
        if (s.find("0x") != std::string::npos)
        {
            int x;
            std::stringstream ss;
            ss << std::hex << s;
            ss >> x;
            std::string value = std::to_string(x);
        }
        else if(s.length() > 1 && s[0] == '0')
        {
            int x;
            std::stringstream ss;
            ss << std::oct << s;
            ss >> x;
            std::string value = std::to_string(x);
            std::cout << value << std::endl;
        }
    }
    
    return 0;
}
