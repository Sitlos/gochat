#pragma once

#include "connect_server.h"
#include "messages.pb.h"

// 加入socket和protobuf的静态库
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "libprotobufd.lib")
#pragma comment(lib, "libprotocd.lib")

namespace gochat {

	char g_user_message[kBuffSize];

	int g_message_client_sockfd;

	int g_user_client_sockfd;

	// 初始化个人消息
	void Init();

	// 开启聊天
	void BeginChat();

	void RecvThread();

}// namespace0 gochat