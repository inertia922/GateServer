#pragma once
#include <grpcpp/grpcpp.h>
#include "const.h"
#include "message.grpc.pb.h"
#include "Singleton.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using namespace message;

class VerifyGrpcClient:public SingleTon<VerifyGrpcClient>
{
public:
	GetVerifyRsp GetVarifyCode(std::string email) {
		using namespace std;
		ClientContext context;
		GetVerifyRsp reply;
		GetVerifyReq request;
		request.set_email(email);
		Status status = stub_->GetVerifyCode(&context, request, &reply);
		if (!status.ok()) {
			reply.set_error(ErrorCodes::RPCFailed);
			cout << "errcode: " << status.error_code() << endl;
		}
		
		cout << "rpc request success£¬reply: " << reply.DebugString() << endl;
		return std::move(reply);
	}
	VerifyGrpcClient() {
		std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials());
		stub_ = VerifyService::NewStub(channel);
	}

private:
	std::unique_ptr<VerifyService::Stub> stub_;
};

