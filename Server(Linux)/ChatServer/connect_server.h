#pragma once

#include"messages.pb.h"
#include"util.h"

namespace gochat {

	class ConnectServer {
	public:
		ConnectServer();

		~ConnectServer();

		int ConnectToServer(const char* server_ip, const short server_port);

		bool Login(int client_sockfd);

		bool Register(int client_sockfd);

		char* GetUserMessage();
	private:
		char user_message_[kBuffSize];
	};

}//  namespace gochat
