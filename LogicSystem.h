#pragma once
#include "Singleton.h"
#include "CServer.h"

class HttpConnection;

typedef std::function<void(std::shared_ptr<HttpConnection>)>HttpHandler;

class LogicSystem :
    public SingleTon<LogicSystem>
{
public:
    LogicSystem();
    ~LogicSystem();
    bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
    bool HandlePost(std::string path, std::shared_ptr<HttpConnection> con);
    void RegGet(std::string, HttpHandler);

    void RegPost(std::string url, HttpHandler handler);

private:
    std::map<std::string, HttpHandler> _post_handlers;
    std::map<std::string, HttpHandler> _get_handlers;

};
