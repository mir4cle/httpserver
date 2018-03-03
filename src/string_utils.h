#pragma once

#include <string>
#include <vector>

namespace string_utils
{
    const std::string WHITESPACE = " \n\r\t";

    std::string trimLeft(const std::string &s)
    {
        size_t startpos = s.find_first_not_of(WHITESPACE);
        return (startpos == std::string::npos) ? "" : s.substr(startpos);
    }

    std::string trimRight(const std::string &s)
    {
        size_t endpos = s.find_last_not_of(WHITESPACE);
        return (endpos == std::string::npos) ? "" : s.substr(0, endpos+1);
    }

    std::string trim(const std::string &s)
    {
        return trimRight(trimLeft(s));
    }

    std::vector<std::string> split(const std::string &text, const std::string &sep)
    {
        std::vector<std::string> tokens;
        std::size_t start = 0, end = 0;
        while ((end = text.find(sep, start)) != std::string::npos)
        {
            tokens.push_back(text.substr(start, end - start));
            start = end + sep.length();
        }

        tokens.push_back(text.substr(start));
        return tokens;
    }
}