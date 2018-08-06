#include "server_method.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#include <iostream>
#include <vector>

#include "messages.pb.h"
#include "util.h"
#include "thread_pool.h"
#include "epoll_handler.h"

namespace gochat{

using std::map;
using std::list;
using std::string;
using std::vector;

//initizatize socket
void Init(){
	if(!g_message_redis_handler.Connect(kMessageDbIp,kMessageDbPort)){
		perror("failed to connect message database");
		exit(1);
	}
    g_server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (g_server_sockfd == -1){
        perror("failed to build socket");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(kMessageServerPort);
    addr.sin_addr.s_addr = inet_addr(kMessageServerIp);
    if (bind(g_server_sockfd,(sockaddr*)&addr,sizeof(addr)) == -1){
        perror("failed to bind");
        exit(1);
    }
    if (listen(g_server_sockfd,kMaxiumPeopleNum) == -1){
        perror("failed to listen");
        exit(1);
    }
}

//send message to all client
void SendMsgToAll(char* broadcast_message){
    list<int>::iterator ite;
    for(ite=g_client_fds.begin();ite!=g_client_fds.end();++ite){
        send(*ite,broadcast_message,kBuffSize,0);
    }
}

int GetNewClientfd(){
    struct sockaddr_in from_addr;
    socklen_t len = sizeof(from_addr);
    int client_fd = accept(g_server_sockfd,(sockaddr*)&from_addr,&len);
    if (client_fd == -1){
        printf("client connect error...\n");
        return -1;
    }
    return client_fd;
}

//fast epoll server
void EpollServer(){
    ThreadPool pool;
    printf("message server begin\n");
    g_epoll_sockfd = epoll_create(kMaxiumPeopleNum);
    if(g_epoll_sockfd<0){
        perror("failed to create epoll");
        exit(1);
    }
    struct epoll_event epoll_events[kMaxiumPeopleNum];
    EpollHandler::AddClientSockfd(g_epoll_sockfd,g_server_sockfd,true);
    while(true){
        int epoll_events_count = epoll_wait(g_epoll_sockfd,epoll_events,kMaxiumPeopleNum,-1);
        if(epoll_events_count< 0){
            perror("epoll failure");
            break;
        }
        for(int i=0 ;i<epoll_events_count;++i){
            int sockfd = epoll_events[i].data.fd;
            //new client enter in
            if(sockfd == g_server_sockfd){
                int client_fd=GetNewClientfd();
                if(client_fd==-1){
                    continue;
                }
                EpollHandler::AddClientSockfd(g_epoll_sockfd,client_fd,true);
                g_client_fds.push_back(client_fd);
            }else{
                if(g_is_not_first_message[sockfd]){
                    pool.AddTask([&sockfd]{
                    Service(sockfd);
                    });
                }else{
                    pool.AddTask([&sockfd]{
                    GetUserMessage(sockfd);
                    });
                }
            }
        }
    }
    close(g_server_sockfd);
    close(g_epoll_sockfd);
}

void GetUserMessage(int sockfd){
    char user_message_buff[kBuffSize]={};
    int client_fd=sockfd;
    if(recv(client_fd,user_message_buff,kBuffSize,0)<=0){
        g_client_fds.remove(client_fd);
        EpollHandler::DelClientSockfd(g_epoll_sockfd,client_fd,true);
        g_is_not_first_message.erase(client_fd);
        close(client_fd);
        return;
    }
    UserMessage user_message;
    user_message.ParseFromArray(user_message_buff, kBuffSize);
    g_user_number_to_sockfd[user_message.user_number()]=client_fd;
    g_sockfd_to_user_number[client_fd] = user_message.user_number() ;
    if(!g_message_redis_handler.Exist(user_message.user_number())){
        send(client_fd,"0\0",2,0);
    }else{
        vector<string> message_vector=g_message_redis_handler.GetMessageList(user_message.user_number());
        string number=IntToString(message_vector.size());
        send(client_fd,number.c_str(),number.size(),0);
        for(int i=0;i<message_vector.size();++i){
            send(client_fd,message_vector[i].c_str(),kBuffSize,0);
        }
        g_message_redis_handler.Del(user_message.user_number());
    }
    g_is_not_first_message[client_fd]=true;
}


void Service(int sockfd){
    int client_fd=sockfd;
    string user_number=g_sockfd_to_user_number[client_fd];
    char send_message[kBuffSize];
    if (recv(client_fd,send_message,kBuffSize,0) <= 0){
        g_client_fds.remove(client_fd);
        g_user_number_to_sockfd.erase(user_number);
        g_sockfd_to_user_number.erase(client_fd);
        g_is_not_first_message.erase(client_fd);
        EpollHandler::DelClientSockfd(g_epoll_sockfd,client_fd,true);
        close(client_fd);
    }
    ChatMessage chat_message;
    chat_message.ParseFromArray(send_message,kBuffSize);
    if(chat_message.message_type()==ChatMessage::GROUP_SEND){
        SendMsgToAll(send_message);
    }else if(chat_message.message_type()==ChatMessage::PERSONAL_SEND){
        if(g_user_number_to_sockfd[chat_message.to_number()] != 0) {
            send(g_user_number_to_sockfd[chat_message.to_number()],send_message,kBuffSize,0);
        }else{
            g_message_redis_handler.SetMessageList(chat_message.to_number(),send_message);
        }
    }
}
}//  namespace gochat

int main(){
    gochat::Init();
    gochat::EpollServer();
    return 0;
}

