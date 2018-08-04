#include "connect_server.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <Winsock2.h>
#include <errno.h>

#include <iostream>

namespace gochat {

	ConnectServer::ConnectServer()
	{
	}


	ConnectServer::~ConnectServer()
	{
	}

	int ConnectServer::ConnectToServer(const char* server_ip, const short server_port) {
		WORD w_version_requested;
		WSADATA wsa_data;
		w_version_requested = MAKEWORD(2, 2);
		WSAStartup(w_version_requested, &wsa_data);
		int client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
		SOCKADDR_IN addr_srv;
		addr_srv.sin_addr.S_un.S_addr = inet_addr(server_ip);
		addr_srv.sin_family = AF_INET;
		addr_srv.sin_port = htons(server_port);
		if (connect(client_sockfd, (SOCKADDR*)&addr_srv, sizeof(SOCKADDR)) < 0) {
			perror("failed to connect");
			return -1;
		}
		return client_sockfd;
	}

	char * ConnectServer::GetUserMessage() {
		return user_message_;
	}

	//login in
	bool ConnectServer::Login(int client_sockfd) {
		memset(user_message_, 0, sizeof(user_message_));
		char user_number[kBuffSize];
		char password[kBuffSize];
		printf("ÇëÊäÈëÄãµÄÕËºÅºÍÃÜÂë\n");
		scanf("%s %s", user_number, password);
		SerializeUserMessage(user_number, password,UserMessage_OperatorType_LOGIN,user_message_);
		send(client_sockfd, user_message_, kBuffSize, 0);
		recv(client_sockfd, user_message_, sizeof(user_message_), 0);
		UserMessage user_message;
		user_message.ParseFromArray(user_message_, kBuffSize);
		if (user_message.reply_result() == UserMessage::SUCCESS) return true;
		if (user_message.reply_result() == UserMessage::FAILED) return false;
		return false;
	}

	bool ConnectServer::Register(int client_sockfd) {
		memset(user_message_, 0, sizeof(user_message_));
		char user_number[kBuffSize];
		char password[kBuffSize];
		char nickname[kBuffSize];
		char signture[kBuffSize];
		puts("ÇëÊäÈëÄãÏë×¢²áµÄÕËºÅ");
		scanf("%s", user_number);
		puts("ÇëÊäÈëÄãµÄÃÜÂë");
		scanf("%s", password);
		printf("ÇëÊäÈëÄãµÄêÇ³Æ\n");
		scanf("%s", nickname);
		puts("Ð´Ò»¾äÄãµÄ¸öÐÔÇ©Ãû°É");
		while (true) {
			gets_s(signture);
			if (strlen(signture) == 0) continue;
			if (strlen(signture) != 1 || signture[0] != '\n') break;
		}
		SerializeUserMessage(user_number, password, nickname, signture,UserMessage_OperatorType_REGISTER, user_message_);
		send(client_sockfd, user_message_, kBuffSize, 0);
		recv(client_sockfd, user_message_, kBuffSize, 0);
		UserMessage user_message;
		user_message.ParseFromArray(user_message_, kBuffSize);
		if (user_message.reply_result() == UserMessage::SUCCESS) return true;
		if (user_message.reply_result() == UserMessage::FAILED) return false;
		return false;
	}
}//  namespace gochat
