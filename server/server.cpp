#include <vector>
#include <utility>
#include <algorithm>

#include "internal/server.h"

///@todo(tolstoy) добавить словать констант, для json
const int LAST_ADDED_SESSION = -1;

Server::Server(): _message_reactions_vec(NUMBER_OF_ACTIONS) {
  _message_reactions_vec[REGISTER_USER] = std::bind(&Server::registerUserHandler, this, std::placeholders::_1);
  _message_reactions_vec[DELETE_USER] = std::bind(&Server::deleteUserHandler, this, std::placeholders::_1);
  _message_reactions_vec[CREATE_SESSION] = std::bind(&Server::createNewSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[CONNECT_SESSION] = std::bind(&Server::connectSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[GIVE_TURN_IN_SESSION] = std::bind(&Server::giveTurnInSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[DISCONNECT_SESSION] = std::bind(&Server::disconnectSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[LIST_SESSIONS] = std::bind(&Server::listSessionsHandler, this, std::placeholders::_1);
}

Server::~Server() {}

Server::JsonMessageStates Server::registerUserHandler(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::deleteUserHandler(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

///@todo(tolstoy) Обработка ошибок и тут есть повтор куска кода из connectSessionHandler
Server::JsonMessageStates Server::createNewSessionHandler(const rapidjson::Document &doc) {
  auto player_login = doc["data"]["login"].GetString();
  auto player_password = doc["data"]["login"].GetString();
  auto session_password = doc["data"]["session_password"].GetString();

  auto player_id = retrievePlayerId(player_login, player_password);
  std::unique_ptr<Session> new_session_ptr = std::make_unique<Session>(Session(retrieveSessionId()));
  new_session_ptr->connectPlayer(player_id);
  _sessions.push_back(std::move(new_session_ptr));
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

///@todo(tolstoy) Обработка ошибок
Server::JsonMessageStates Server::connectSessionHandler(const rapidjson::Document &doc) {
  auto player_login = doc["data"]["login"].GetString();
  auto player_password = doc["data"]["login"].GetString();
  auto session_password = doc["data"]["session_password"].GetString();
  auto session_id = doc["data"]["session_id"].GetInt();

  auto player_id = retrievePlayerId(player_login, player_password);
  auto session_to_connect_iter =  std::find_if(_sessions.begin(),
                                               _sessions.end(),
                                               [session_id](std::unique_ptr<Session>& s)
  {return session_id == s->id() ? true : false;});
  if ((*session_to_connect_iter)->password() == std::string(session_password)){
    (*session_to_connect_iter)->connectPlayer(player_id);
    return JsonMessageStates::SUCCESSFULY_PARSED;
  } else {
    return JsonMessageStates::ACTION_DENIED;
  }
}

Server::JsonMessageStates Server::giveTurnInSessionHandler(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::disconnectSessionHandler(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

Server::JsonMessageStates Server::listSessionsHandler(const rapidjson::Document &doc) {
  ///@todo(tolstoy) Реализация
  return JsonMessageStates::SUCCESSFULY_PARSED;
}

int Server::retrievePlayerId(const char *player_login, const char *player_password)
{
  ///@todo(tolstoy) Сделать настоящее получение айдишника
  return std::rand();
}

int Server::retrieveSessionId()
{
  ///@todo(tolstoy) Сделать настоящее получение айдишника
  return std::rand();
}

///@todo(tolstoy) добавить обработку ошибок
Server::JsonMessageStates Server::processMessage(const std::string& msg) {
  rapidjson::Document message;
  message.Parse(msg.c_str());
  _message_reactions_vec[message["action"].GetInt()](message);
  return JsonMessageStates::SUCCESSFULY_PARSED;
}
