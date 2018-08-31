#pragma once

#include<cstdio>
#include<ctime>
#include<string>

#include<iostream>

#include"messages.pb.h"

namespace gochat {

	const char kUserServerIp[] = "127.0.0.1";
	const char kMessageServerIp[] = "0.0.0.0";
	const char kUserDbIp[] = "127.0.0.1";
	const char kMessageDbIp[] = "127.0.0.1";
	const short kUserServerPort = 9838;//用户服务端口
	const short kMessageServerPort = 9837;//消息服务端口
	const short kUserDbPort = 6379;
	const short kMessageDbPort = 6380;
	const int kBuffSize = 256;
	const int kMaxiumPeopleNum = 100000;
	const int kMaxTaskCount = 10000;

	//获取当前系统时间
	inline std::string GetTime() {
		time_t timep;
		time(&timep);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
		return tmp;
	}

	//把char数组转换为int
	inline int CharbufToInt(char* number) {
		int result = 0;
		int len = strlen(number);
		for (int i = 0; i < len; ++i) {
			result = result * 10 + number[i] - '0';
		}
		return result;
	}

	//把int变为string
	inline std::string IntToString(int value) {
		std::string result;
		while (value != 0) {
			result += value % 10 + '0';
			value /= 10;
		}
		reverse(result.begin(), result.end());
		result += '\0';
		return result;
	}

	inline void CopyBuff(char* target, const char* source) {
		int len = strlen(source);
		for (int i = 0; i < len; i++) {
			target[i] = source[i];
		}
		target[len] = '\0';
	}

	// 判断是否为有效输入
	int ValidOptype(int left_range, int right_range, char* optype_buff);

	void PrintMessage(ChatMessage chat_message);

	// 序列化聊天消息
	void SerializeChatMessage(ChatMessage::MessageType message_type,
							const char* from_number,
							const char* nickname,
							const char* to_number,
							const char* time,
							const char* data,
							char* result);

	void SerializeUserMessage(const char* user_number,
							const char* password,
							const char* nickname,
							const char*signture,
							bool is_online,
							char* result);

	void SerializeUserMessage(const char* user_number,
							const char* password,
							const char* nickname,
							const char*signture,
							char* result);

	void SerializeUserMessage(const char* user_number,
							const char* password,
							const char* nickname,
							const char*signture,
							const UserMessage::ReplyResult reply_result,
							char* result);

	void SerializeUserMessage(const char* user_number,
		const char* password,
		const char* nickname,
		const char*signture,
		const UserMessage::OperatorType operator_type,
		char* result);

	void SerializeUserMessage(const char* user_number, 
							const char* password,
							const UserMessage::OperatorType operator_type ,
							char* result);

	void SerializeUserMessage(const char* user_number,
							UserMessage::OperatorType operator_type,
							char* result);

	void SerializeUserMessage(const char* user_number, const char* password, char* result);

	void SerializeUserMessage(const char* user_number, char* result);

	void SerializeUserMessage(const UserMessage::ReplyResult reply_result, char* result);

}//  namespace gochat
