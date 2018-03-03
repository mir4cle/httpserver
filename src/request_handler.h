#pragma once

#include <string>

class request;
struct reply;

class request_handler
{
public:
    request_handler(const request_handler&) = delete;
    request_handler& operator=(const request_handler&) = delete;

    explicit request_handler(const std::string& root);

    /// Handle a request and produce a reply.
    void handle_request(const request &req, reply &rep);

private:
    std::string root_;
};