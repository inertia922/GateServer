#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifyGrpcClient.h"

LogicSystem::LogicSystem()
{
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
		beast::ostream(connection->_response.body()) << "receive get test req";
		int i = 0;
		for (auto &elem : connection->_get_params) {
			++i;
			beast::ostream(connection->_response.body()) << "param " << i << "key is:" << elem.first;
			beast::ostream(connection->_response.body()) << "param " << i << "key is:" << elem.second;
		}
	});

	RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is : " << body_str << std::endl;

		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "err json data: " << body_str << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		if (!src_root.isMember("email")) {
			std::cout << "err json data, no mail: " << body_str << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].asString();
		auto &&rsp = VerifyGrpcClient::GetInstance()->GetVarifyCode(email);

		std::cout << "get mail: " << email << std::endl;
		root["error"] = rsp.error();
		root["email"] = email;
		beast::ostream(connection->_response.body()) << root.toStyledString();
		return true;
	});
}

LogicSystem::~LogicSystem()
{
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> con)
{
	if(!_get_handlers.count(path))return false;

	_get_handlers[path](con);
	return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> con)
{
	if (!_post_handlers.count(path))return false;

	_post_handlers[path](con);
	return true;
}

void LogicSystem::RegGet(std::string url, HttpHandler handler)
{
	_get_handlers.insert(make_pair(url, handler));
}

void LogicSystem::RegPost(std::string url, HttpHandler handler)
{
	_post_handlers.insert(make_pair(url, handler));
}
