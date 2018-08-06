#pragma once

#include <map>
#include <list>

#include "redis_handler.h"

namespace gochat{

//initizatize socket
void Init();
//send message to all client
void SendMsgToAll(char* msg);

void Service(int sockfd);

int GetNewClientfd();

void EpollServer();

void GetUserMessage(int sockfd);

RedisHandler g_message_redis_handler;

std::map<std::string,int> g_user_number_to_sockfd;

std::map<int,std::string> g_sockfd_to_user_number;

std::map<int,bool> g_is_not_first_message;

int g_server_sockfd;// server socket

int g_epoll_sockfd;

std::list<int> g_client_fds;

}// namespace go chat
