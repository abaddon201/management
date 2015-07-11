#include <vector>
#include "internal/server.h"

///@fixme(tolstoy) just for test
#include <iostream>

Server::Server(): _message_reactions_vec(NUMBER_OF_ACTIONS) {
  _message_reactions_vec[REGISTER_USER] = std::bind(&Server::registerUser, this, std::placeholders::_1);
  _message_reactions_vec[DELETE_USER] = std::bind(&Server::deleteUser, this, std::placeholders::_1);
  _message_reactions_vec[CREATE_SESSION] = std::bind(&Server::createNewSession, this, std::placeholders::_1);
  _message_reactions_vec[CONNECT_SESSION] = std::bind(&Server::connectSession, this, std::placeholders::_1);
  _message_reactions_vec[GIVE_TURN_IN_SESSION] = std::bind(&Server::giveTurnInSession, this, std::placeholders::_1);
  _message_reactions_vec[DISCONNECT_SESSION] = std::bind(&Server::disconnectSession, this, std::placeholders::_1);
  _message_reactions_vec[LIST_SESSIONS] = std::bind(&Server::listSessions, this, std::placeholders::_1);
}

Server::~Server() {}

Server::JsonMessageStates Server::registerUser(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::deleteUser(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::createNewSession(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::connectSession(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::giveTurnInSession(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::disconnectSession(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::listSessions(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

///@todo(tolstoy) добавить обработку ошибок
Server::JsonMessageStates Server::processMessage(const std::string& msg) {
  rapidjson::Document message;

  message.Parse(msg.c_str());
  _message_reactions_vec[message["action"].GetInt()](message);

  return JsonMessageStates::SUCCESSFULY_PARSED;
}
