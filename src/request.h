#pragma once

#include "header.h"

#include <string>
#include <vector>
#include <map>

enum class request_method
{
    unknown = -1,
    get,
    head, 
    post,
    put,
    del,
    trace,
    options,
    connect,
    patch
};

struct request
{
    request_method method;
    std::string uri;
    std::string version;
    std::vector<header> headers;
};

request_method method_from_string(const std::string &str);