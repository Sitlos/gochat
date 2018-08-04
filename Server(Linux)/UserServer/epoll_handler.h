#pragma once

#include <sys/epoll.h>
#include <fcntl.h>
namespace gochat{

class EpollHandler{
    public:
        EpollHandler();

        virtual ~EpollHandler();

        static int SetNonBlocking(int sock_fd);

        static void AddClientSockfd(int epoll_fd, int client_sockfd, bool enable_et);

        static void DelClientSockfd(int epoll_fd, int client_sockfd, bool enable_et);

    private:
};
}// namespace gochat

