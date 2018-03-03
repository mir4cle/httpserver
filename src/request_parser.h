#pragma once

#include <istream>

class request;

class request_parser
{
public:
    enum class result_type { good, bad };

    request_parser();
    result_type parse(request &req, std::istream &is);
};