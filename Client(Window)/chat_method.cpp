#include"chat_method.h"

#include <cstdio>
#include <thread>
#include <winsock.h>

#include<iostream>

#include "util.h"
#include "thread_pool.h"

namespace gochat {

	void Init() {
		ConnectServer my_server;

		if ((g_user_client_sockfd = my_server.ConnectToServer(kUserServerIp, kUserServerPort)) < 0) {
			perror("连接用户服务失败\n");
			exit(1);
		}
		char optype_buff[kBuffSize] = {};//操作类型
		int optype;
		while (true) {
			puts("请输入操作编号: 1.登录 2.注册 3.关闭客户端");
			scanf("%s", optype_buff);
			if ((optype = ValidOptype(1, 3, optype_buff)) == -1) {
				continue;
			}
			if (optype == 1) {
				bool state = my_server.Login(g_user_client_sockfd);
				if (!state) {
					puts("账号或者密码错误");
				}
				else {
					puts("登录成功");
					break;
				}
			}
			else if (optype == 2) {
				bool state = my_server.Register(g_user_client_sockfd);
				if (!state) {
					puts("服务器无响应或者此账号已被注册");
				}
				else {
					puts("注册成功,已登录");
					break;
				}
			}
			else if (optype == 3) {
				closesocket(g_user_client_sockfd);
				exit(0);
			}
		}
		CopyBuff(g_user_message, my_server.GetUserMessage());
		UserMessage user_message;
		user_message.ParseFromArray(g_user_message, kBuffSize);
		puts("--------------------------------------------------------------------------------------------------------------------");
		printf("%s ,欢迎你回来!现在是:%s\n", user_message.nickname().c_str(), GetTime().c_str());
		puts("以下是你的个人信息:");
		printf("你的账号:%s\n", user_message.user_number().c_str());
		printf("你的昵称:%s\n你的个人签名 : %s\n", user_message.nickname().c_str(), user_message.signture().c_str());
		puts("--------------------------------------------------------------------------------------------------------------------");

	}

	void BeginChat() {
		ConnectServer my_server;

		if ((g_message_client_sockfd = my_server.ConnectToServer(kMessageServerIp, kMessageServerPort)) < 0) {
			perror("连接消息服务失败\n");
			closesocket(g_user_client_sockfd);
			exit(1);
		}
		send(g_message_client_sockfd, g_user_message, kBuffSize, 0);
		puts("正在尝试拉取离线消息.........");
		char offline_message_count_buf[kBuffSize] = {};
		recv(g_message_client_sockfd, offline_message_count_buf, sizeof(offline_message_count_buf), 0);
		int offline_message_count = CharbufToInt(offline_message_count_buf);
		printf("共拉取到 %d 条消息\n", offline_message_count);
		while (offline_message_count--) {
			char offline_message[kBuffSize] = {};
			recv(g_message_client_sockfd, offline_message, kBuffSize, 0);
			ChatMessage cm;
			cm.ParseFromArray(offline_message, kBuffSize);
			PrintMessage(cm);
		}
		puts("拉取完毕!");
		//开启用于接受消息的线程
		std::thread recv_thead(RecvThread);

		UserMessage user_message;
		user_message.ParseFromArray(g_user_message, kBuffSize);

		while (true) {
			char send_message[kBuffSize] = {} , serialize_send_message[kBuffSize] = {} , send_user_number[kBuffSize] = {};
			puts("请输入操作编号: 1.私聊 2.群聊 3.下线");
			char optype_buff[kBuffSize] = {};//操作类型
			int optype;
			scanf("%s", optype_buff);
			optype = ValidOptype(1, 3, optype_buff);
			if (optype == -1) continue;
			if (optype == 1) {
				puts("请输入你要联系的人的账号");
				scanf("%s", send_user_number);
				char server_reply_buff[kBuffSize] = {}, user_number[kBuffSize] = {};
				SerializeUserMessage(send_user_number,UserMessage::CHECK, user_number);
				send(g_user_client_sockfd, user_number, kBuffSize, 0);
				recv(g_user_client_sockfd, server_reply_buff, kBuffSize, 0);
				UserMessage server_reply;
				server_reply.ParseFromArray(server_reply_buff,kBuffSize);
				if (server_reply.reply_result() == UserMessage::FAILED) {
					puts("查无此人!");
					continue;
				}
				puts("请输入要发送的消息");
				while (true) {
					gets_s(send_message);
					if (strlen(send_message) == 0) continue;
					if (strlen(send_message) != 1 || send_message[0] != '\n') break;
				}
				SerializeChatMessage(ChatMessage::PERSONAL_SEND,
					user_message.user_number().c_str(),
					user_message.nickname().c_str(), send_user_number,
					GetTime().c_str(),
					send_message,
					serialize_send_message);
				puts("私聊:");
				printf("%s\n我 : %s\n", GetTime().c_str(), send_message);
				send(g_message_client_sockfd, serialize_send_message, kBuffSize, 0);
			}
			else if (optype == 2) {
				puts("请输入要发送的消息");
				while (true) {
					gets_s(send_message);
					if (strlen(send_message) == 0) continue;
					if (strlen(send_message) != 1 || send_message[0] != '\n') break;
				}
				SerializeChatMessage(ChatMessage::GROUP_SEND,
					user_message.user_number().c_str(),
					user_message.nickname().c_str(),
					"", GetTime().c_str(),
					send_message,
					serialize_send_message);
				send(g_message_client_sockfd, serialize_send_message, kBuffSize, 0);
			}
			else if (optype == 3) {
				closesocket(g_user_client_sockfd);
				closesocket(g_message_client_sockfd);
				exit(0);
			}
			Sleep(15);
		}
	}

	//接收线程
	void RecvThread() {
		while (true) {
			char recv_buff[kBuffSize] = {};
			if (recv(g_message_client_sockfd, recv_buff, sizeof(recv_buff), 0) <= 0) {
				break;
			}
			ChatMessage cm;
			cm.ParseFromArray(recv_buff, kBuffSize);
			PrintMessage(cm);
		}
	}

}//  namespace gochat

int main() {
	gochat::Init();
	gochat::BeginChat();
	closesocket(gochat::g_user_client_sockfd);
	closesocket(gochat::g_message_client_sockfd);
	return 0;
}