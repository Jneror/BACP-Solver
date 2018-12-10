#include <regex>
#include <iostream>

int main()
{
    const std::string s = "/home/toto/FILE_mysymbol_EVENT.DAT";
    std::regex rgx(".*FILE_(\\w+)_EVENT\\.DAT.*");
    std::smatch match;

    if (std::regex_search(s.begin(), s.end(), match, rgx))
        std::cout << "match: " << match[1] << '\n';
    
    ////////////////////////////////////////////////////////
    
    const std::string s2 = "< dew101 , dew100 >,";
    std::regex rgx2(".*< (\\w+) , (\\w+) >,.*");

    std::smatch match2;
    if (std::regex_search(s2.begin(), s2.end(), match2, rgx2))
        std::cout << "match: " << match2[1] << '\n';
    
    ////////////////////////////////////////////////////////

    const std::string s3 = "a=10; /* minimum academic load allowed per period */";
    std::regex rgx3("a=(\\d+);");
    std::smatch match3;

    if (std::regex_search(s3.begin(), s3.end(), match3, rgx3))
        std::cout << "match: " << match3[0] << " " << match3[1] << " " << match3[2] << '\n';
}