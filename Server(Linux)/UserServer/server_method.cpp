#include"server_method.h"

#include <cstring>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "redis_handler.h"
#include "messages.pb.h"
#include "util.h"
#include "epoll_handler.h"
#include "thread_pool.h"



namespace gochat{

using std::map;
using std::string;
using std::list;

//initizatize socket
void Init(){
	if(!handler.Connect(kUserDbIp,kUserDbPort)){
		perror("failed to connect database");
		exit(1);
	}
    g_server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (g_server_sockfd == -1){
        perror("failed to build socket");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(kUserServerPort);
    addr.sin_addr.s_addr = inet_addr(kUserServerIp);
    if (bind(g_server_sockfd,(sockaddr*)&addr,sizeof(addr)) == -1){
        perror("failed to bind");
        exit(1);
    }
    if (listen(g_server_sockfd,kMaxiumPeopleNum) == -1){
        perror("failed to listen");
        exit(1);
    }
}

bool VerifyLogin(string user_name,string password){
    if(!handler.Exist(user_name)){
        return false;
    }
    string personal_message=handler.Get(user_name);
    UserMessage user_message;
    user_message.ParseFromString(personal_message);
    if(user_message.password()==password){
        return true;
    }else{
        return false;
    }
}

bool VerifyRegister(string user_name){
    if(!handler.Exist(user_name)){
        return true;
    }else{
        return false;
    }
}

void Service(int sockfd){
        int client_fd = sockfd;
        UserMessage user_message,user_message_get_from_datebase;
        char user_message_buf[kBuffSize]={},reply_buff[kBuffSize]={},restore_buff[kBuffSize]={};
        //when a client leave,set it offline
        if (recv(client_fd,user_message_buf,kBuffSize,0)<=0){
	    printf("lost\n");
            client_fds.remove(client_fd);
            EpollHandler::DelClientSockfd(g_epoll_sockfd,client_fd,true);
            close(client_fd);
            if(!g_sockfd_login_in[client_fd]){
                return ;
            }
            g_sockfd_login_in.erase(client_fd);
            user_message.ParseFromArray(handler.Get(g_sockfd_to_user_number[client_fd]).c_str(),kBuffSize);
            //serialize restore buf to database
            SerializeUserMessage(user_message.user_number().c_str(),
                                user_message.password().c_str(),
                                user_message.nickname().c_str(),
                                user_message.signture().c_str(),
                                false,
                                restore_buff);
            handler.Set(g_sockfd_to_user_number[client_fd],restore_buff);

        }
        user_message.ParseFromArray(user_message_buf,kBuffSize);
        string user_number=user_message.user_number();
        //when someone loading sucess,give him the user_message of his
        if(user_message.operator_tpye() == UserMessage::LOGIN){
            string password=user_message.password();
            if(VerifyLogin(user_number,password)){
                g_sockfd_login_in[client_fd]=true;
                g_sockfd_to_user_number[client_fd]=user_number;
                user_message_get_from_datebase.ParseFromArray(handler.Get(user_number).c_str(),kBuffSize);
                //serialize restore buf to database
                SerializeUserMessage(user_message_get_from_datebase.user_number().c_str(),
                                    user_message_get_from_datebase.password().c_str(),
                                    user_message_get_from_datebase.nickname().c_str(),
                                    user_message_get_from_datebase.signture().c_str(),
                                    true,
                                    restore_buff);
                //serialize reply buff to client
                SerializeUserMessage(user_message_get_from_datebase.user_number().c_str(),
                                    user_message_get_from_datebase.password().c_str(),
                                    user_message_get_from_datebase.nickname().c_str(),
                                    user_message_get_from_datebase.signture().c_str(),
                                    UserMessage::SUCCESS,
                                    reply_buff);
                send(client_fd,reply_buff,strlen(reply_buff),0);
                handler.Set(user_message.user_number(),restore_buff);
            }else{
                SerializeUserMessage(UserMessage::FAILED,reply_buff);
                send(client_fd,reply_buff,kBuffSize,0);
            }
        }else if(user_message.operator_tpye() == UserMessage::REGISTER){
            if(VerifyRegister(user_number)){
                g_sockfd_login_in[client_fd]=true;
                g_sockfd_to_user_number[client_fd]=user_number;
                //serialize restore buf to database
                SerializeUserMessage(user_message.user_number().c_str(),
                                    user_message.password().c_str(),
                                    user_message.nickname().c_str(),
                                    user_message.signture().c_str(),
                                    true,
                                    restore_buff);
                //serialize reply buff to client
                SerializeUserMessage(user_message.user_number().c_str(),
                                    user_message.password().c_str(),
                                    user_message.nickname().c_str(),
                                    user_message.signture().c_str(),
                                    UserMessage::SUCCESS,
                                    reply_buff);
                send(client_fd,reply_buff,strlen(reply_buff),0);
                handler.Set(user_message.user_number(),restore_buff);
            }else{
                SerializeUserMessage(UserMessage::FAILED,reply_buff);
                send(client_fd,reply_buff,kBuffSize,0);
            }
            //judge if someone is exist
        }else if(user_message.operator_tpye() == UserMessage::CHECK){
            if(handler.Exist(user_number)){
                SerializeUserMessage(UserMessage::SUCCESS,reply_buff);
                send(client_fd,reply_buff,kBuffSize,0);
            }else{
                SerializeUserMessage(UserMessage::FAILED,reply_buff);
                send(client_fd,reply_buff,kBuffSize,0);
            }
        }
    //------
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
    printf("user server begin\n");
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
                client_fds.push_back(client_fd);
            }else{

                   pool.AddTask([&sockfd]{
                        Service(sockfd);
                   });

            }
        }
    }
    close(g_server_sockfd);
    close(g_epoll_sockfd);
}

}  //namespace gochat

int main(){
    gochat::Init();
    gochat::EpollServer();
    return 0;
}
