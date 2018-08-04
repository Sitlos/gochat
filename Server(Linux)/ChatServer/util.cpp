#pragma once
#include"util.h"

namespace gochat {

	// 判断是否为有效输入
	int ValidOptype(int left_range, int right_range, char* optype_buff) {
		if (strlen(optype_buff) > 1) {
			puts("编号无效!");
			return -1;
		}
		else {
			int optype = optype_buff[0] - '0';
			if (optype < left_range || optype > right_range) {
				puts("编号无效!");
				return -1;
			}
			return optype;
		}
	}

	void PrintMessage(ChatMessage chat_message) {
		if (chat_message.message_type() == ChatMessage::GROUP_SEND) {
			puts("群聊");
		}
		else if (chat_message.message_type() == ChatMessage::PERSONAL_SEND) {
			puts("私聊");
		}
		printf("%s\n", chat_message.time().c_str());
		printf("%s : %s\n", chat_message.nickname().c_str(), chat_message.data().c_str());
	}

	// 序列化聊天消息
	void SerializeChatMessage(const ChatMessage::MessageType message_type,
							const char* from_number,
							const char* nickname,
							const char* to_number, 
							const char* time,
							const char* data,
							char* result) {
		ChatMessage chat_message_set;
		chat_message_set.set_message_type(message_type);
		chat_message_set.set_from_number(from_number);
		chat_message_set.set_nickname(nickname);
		chat_message_set.set_to_number(to_number);
		chat_message_set.set_time(time);
		chat_message_set.set_data(data);
		chat_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const char* user_number,
							const char* password,
							const char* nickname,
							const char*signture,
							const bool is_online,
							char* result) {
		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.set_password(password);
		user_message_set.set_nickname(nickname);
		user_message_set.set_signture(signture);
		user_message_set.set_is_online(is_online);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const char* user_number,
							const char* password,
							const char* nickname,
							const char*signture,
							char* result) {
		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.set_password(password);
		user_message_set.set_nickname(nickname);
		user_message_set.set_signture(signture);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const char * user_number, 
							const char * password, 
							const char * nickname, 
							const char * signture,
							const UserMessage::ReplyResult reply_result,
							char * result){

		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.set_password(password);
		user_message_set.set_nickname(nickname);
		user_message_set.set_signture(signture);
		user_message_set.set_reply_result(reply_result);
		user_message_set.SerializeToArray(result, kBuffSize);
		
	}

	void SerializeUserMessage(const char * user_number,
							const char * password, 
							const char * nickname,
							const char * signture,
							const UserMessage::OperatorType operator_type, 
							char * result){
		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.set_password(password);
		user_message_set.set_nickname(nickname);
		user_message_set.set_signture(signture);
		user_message_set.set_operator_tpye(operator_type);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const char * user_number, 
							const char * password,
							const UserMessage::OperatorType operator_type, 
							char * result){
		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.set_password(password);
		user_message_set.set_operator_tpye(operator_type);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const char * user_number, 
							UserMessage::OperatorType operator_type,
							char * result){
		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.set_operator_tpye(operator_type);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const char* user_number, const char* password, char* result) {
		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.set_password(password);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const char * user_number, char * result) {
		UserMessage user_message_set;
		user_message_set.set_user_number(user_number);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

	void SerializeUserMessage(const UserMessage::ReplyResult reply_result, char * result){
		UserMessage user_message_set;
		user_message_set.set_reply_result(reply_result);
		user_message_set.SerializeToArray(result, kBuffSize);
	}

}// gochat
