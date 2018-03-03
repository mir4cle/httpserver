#include "request_parser.h"
#include "request.h"
#include "string_utils.h"

#include <string>
#include <vector>

request_parser::request_parser()
{
}

request_parser::result_type request_parser::parse(request &req_, std::istream &is)
{
    std::string line;
    request req;

    // method uri protocol/version
    std::getline(is, line);
    if(is.fail())
        return request_parser::result_type::bad;

    std::vector<std::string> tokens = string_utils::split(line, " ");
    if(tokens.size() != 3)
        return request_parser::result_type::bad;

    req.method = method_from_string(string_utils::trim(tokens[0]));
    req.uri = string_utils::trim(tokens[1]);
    req.version = string_utils::trim(tokens[2]);

    //headers
    std::getline(is, line);
    line = string_utils::trim(line);

    while(!is.fail() && !line.empty())
    {
        tokens = string_utils::split(line, ": ");
        if(tokens.size() != 2)
            return request_parser::result_type::bad;

        req.headers.push_back({tokens[0], tokens[1]});
        std::getline(is, line);
        line = string_utils::trim(line);
    }

    if(!is.fail() && !is.eof())
    {
        // body
        // not implemented yet
    }

    req_ = std::move(req);
    return request_parser::result_type::good;
}