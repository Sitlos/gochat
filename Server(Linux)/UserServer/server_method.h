#include <list>
#include <map>
#include <vector>

#include "redis_handler.h"
#include "util.h"



namespace gochat{

std::list<int> client_fds;

RedisHandler handler;

int g_server_sockfd;// server socket

int g_epoll_sockfd;

std::unordered_map<int,std::string> g_sockfd_to_user_number;

std::unordered_map<int,bool> g_sockfd_login_in;

//initizatize socket
void Init();

int GetNewClientfd();

bool VerifyLogin(std::string userName,std::string password);

bool VerifyRegister(std::string userName);

void Service();

void EpollServer();

} //namespace gochat
