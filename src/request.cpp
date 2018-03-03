#include "request.h"

request_method method_from_string(const std::string &str)
{
    request_method method = request_method::unknown;
    if(str == "GET")
    {
        method = request_method::get;
    }
    else if(str == "HEAD")
    {
        method = request_method::head;
    }
    else if(str == "POST")
    {
        method = request_method::post;
    }
    else if(str == "PUT")
    {
        method = request_method::put;
    }
    else if(str == "DELETE")
    {
        method = request_method::del;
    }
    else if(str == "TRACE")
    {
        method = request_method::trace;
    }
    else if(str == "OPTIONS")
    {
        method = request_method::options;
    }
    else if(str == "CONNECT")
    {
        method = request_method::connect;
    }
    else if(str == "PATCH")
    {
        method = request_method::patch;
    }

    return method;
}