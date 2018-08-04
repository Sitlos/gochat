#pragma once

#include<cstring>

#include<string>
#include<vector>

#include"hiredis/hiredis.h"

namespace gochat{
class RedisHandler
{
    public:
        RedisHandler();
        ~RedisHandler();
        //connect to database server
        bool Connect(const char* ip,short port);
        //judge if the key if exist
        bool Exist(std::string key);
        //del the key
        void Del(std::string key);
        // get the value by the key
        std::string Get(std::string key);
        // set the value of the key
        void Set(std::string key, std::string value);
        //set Message List of key
        void SetMessageList(std::string key, std::string message);
        //get Message List of key
        std::vector<std::string> GetMessageList(std::string key);
        //close connect server
        void Close();
    private:
        // redis context
        redisContext* connect_;
        // resulut of command
        redisReply* reply_;

};
}  //namespace gochat
