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
		ClientContext context;
		GetVerifyRsp reply;
		GetVerifyReq request;
		request.set_email(email);
		Status status = stub_->GetVerifyCode(&context, request, &reply);
		if (!status.ok()) {
			reply.set_error(ErrorCodes::RPCFailed);
		}
		return std::move(reply);
	}
	VerifyGrpcClient() {
		std::shared_ptr<Channel> channel = grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials());
		stub_ = VerifyService::NewStub(channel);
	}

private:
	std::unique_ptr<VerifyService::Stub> stub_;
};

