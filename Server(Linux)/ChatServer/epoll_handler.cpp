#include "epoll_handler.h"

#include<cstdio>

namespace gochat{

EpollHandler::EpollHandler()
{
    //ctor
}

EpollHandler::~EpollHandler()
{
    //dtor
}

int EpollHandler::SetNonBlocking(int sockfd){
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)| O_NONBLOCK);
    return 0;
}

void EpollHandler::AddClientSockfd(int epoll_sockfd, int sockfd, bool enable_et){
    struct epoll_event this_epoll_event;
    this_epoll_event.data.fd = sockfd;
    this_epoll_event.events = EPOLLIN ;
    if(enable_et){
        this_epoll_event.events = EPOLLIN | EPOLLET ;
    }
    if(epoll_ctl(epoll_sockfd, EPOLL_CTL_ADD, sockfd, &this_epoll_event)< 0){
        perror("failed to add socket to epoll\n");
    }
    SetNonBlocking(sockfd);
    printf("fd added to epoll!\n");
}

void EpollHandler::DelClientSockfd(int epoll_sockfd, int sockfd, bool enable_et){
    struct epoll_event this_epoll_event;
    this_epoll_event.data.fd = sockfd;
    this_epoll_event.events = EPOLLIN ;
    if(enable_et){
        this_epoll_event.events = EPOLLIN | EPOLLET ;
    }
    if(epoll_ctl(epoll_sockfd, EPOLL_CTL_DEL, sockfd, &this_epoll_event)< 0){
        perror("failed to del socket from epoll\n");
    }

}
} // namespace gochat
