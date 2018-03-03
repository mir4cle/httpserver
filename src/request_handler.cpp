#include "request_handler.h"
#include "request.h"
#include "reply.h"
#include "mime_types.h"

#include <fstream>

request_handler::request_handler(const std::string& root)
    : root_(root)
{
}

void request_handler::handle_request(const request &req, reply &rep)
{
    std::string req_path = req.uri;
    if(req_path.empty() || req_path[0] != '/'
        || req_path.find("..") != std::string::npos)
    {
        rep = reply::stock_reply(reply::bad_request);
        return;
    }

    if (req_path[req_path.size() - 1] == '/')
    {
        req_path += "index.html";
    }

    std::size_t last_slash_pos = req_path.find_last_of("/");
    std::size_t last_dot_pos = req_path.find_last_of(".");
    std::string extension;
    if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
    {
        extension = req_path.substr(last_dot_pos + 1);
    }

    std::string full_path = root_ + req_path;
    std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
    if (!is)
    {
        rep = reply::stock_reply(reply::not_found);
        return;
    }

    rep.status = reply::ok;
    char buf[512];
    while (is.read(buf, sizeof(buf)).gcount() > 0)
    rep.content.append(buf, is.gcount());
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = mime_types::extension_to_type(extension);
}