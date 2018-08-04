#include "redis_handler.h"

#include <algorithm>

#include <iostream>

namespace gochat{

using std::vector;
using std::string;

RedisHandler::RedisHandler(){
    //ctor
}

RedisHandler::~RedisHandler(){
    //dtor
}

bool RedisHandler::Connect(const char* ip,short port){
    this->connect_ = redisConnect(ip,port);
    if (this->connect_ != NULL && this->connect_->err){
        return false;
    }
    return true;
}

bool RedisHandler::Exist(string key){
    this->reply_ = (redisReply*)redisCommand(this->connect_, "EXISTS %s", key.c_str());
    bool flag= this->reply_->integer;
    freeReplyObject(this->reply_);
    return flag;
}


string RedisHandler::Get(string key){
    this->reply_ = (redisReply*)redisCommand(this->connect_, "GET %s", key.c_str());
    string str = this->reply_->str;
    freeReplyObject(this->reply_);
    return str;
}

void RedisHandler::Del(std::string key){
     redisCommand(this->connect_, "DEL %s", key.c_str());
}

void RedisHandler::Set(string key,string value){
     redisCommand(this->connect_, "SET %s %s", key.c_str(), value.c_str());
}

void RedisHandler::SetMessageList(std::string people, std::string message) {
    redisCommand(this->connect_, "RPUSH %s %s",people.c_str(), message.c_str());
}

vector<string> RedisHandler::GetMessageList(string key){
    vector<string> result;
    this->reply_ = (redisReply*)redisCommand(this->connect_, "LRANGE %s %s %s",key.c_str(),"0","-1");
    for (int i = 0; i < reply_->elements; ++i){
        result.push_back(reply_->element[i]->str);
    }
    freeReplyObject(this->reply_);
    return result;
}

void RedisHandler::Close(){
    redisFree(connect_);
}
}  //namespace gochat
