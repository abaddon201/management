#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "internal/server.h"

///@todo(tolstoy) добавить обработку ошибок в start, work, buildSocketSet, acceptNewConnection, processConnections

///@todo(tolstoy) добавить словать констант, для json
const int LAST_ADDED_SESSION = -1;

Server::Server(int port_num): _message_reactions_vec(NUMBER_OF_ACTIONS),  _port_num{port_num} {
  _message_reactions_vec[REGISTER_USER] = std::bind(&Server::registerUserHandler, this, std::placeholders::_1);
  _message_reactions_vec[DELETE_USER] = std::bind(&Server::deleteUserHandler, this, std::placeholders::_1);
  _message_reactions_vec[CREATE_SESSION] = std::bind(&Server::createNewSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[CONNECT_SESSION] = std::bind(&Server::connectSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[GIVE_TURN_IN_SESSION] = std::bind(&Server::giveTurnInSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[DISCONNECT_SESSION] = std::bind(&Server::disconnectSessionHandler, this, std::placeholders::_1);
  _message_reactions_vec[LIST_SESSIONS] = std::bind(&Server::listSessionsHandler, this, std::placeholders::_1);
}

Server::~Server() {}

int Server::start()
{
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket < 0) {
    perror("Failed to create socket\n");
    return 1;
  }

  int reuseAddrOpt;
  setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &reuseAddrOpt, sizeof(reuseAddrOpt));
  int opts = fcntl(_socket, F_GETFL);
  if (opts < 0) {
    perror("Failed to fcntl(F_GETFL)\n");
    return 1;
  }
  opts = (opts | O_NONBLOCK);
  if (fcntl(_socket,F_SETFL,opts) < 0) {
    perror("Failed to fcntl(F_SETFL)\n");
    return 1;
  }

  struct sockaddr_in serv_addr;
  memset(reinterpret_cast<char*>(&serv_addr), 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(_port_num);
  if (0 > bind(_socket, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr))) {
    perror("Failed to bind\n");
    return 1;
  }

  work();

  return 0;
}

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

int Server::work()
{
  int highest_sock = _socket;
  listen(_socket,5);
  while(1) {
    auto max_connection_it = std::max_element(_connections_vec.begin(),_connections_vec.end());
    if (max_connection_it != _connections_vec.end()) {
      highest_sock = std::max(highest_sock, *max_connection_it);
    }
    int was_read = select(highest_sock + 1,
                          &_socket_set, static_cast<fd_set*>(0), static_cast<fd_set*>(0), NULL);
    if (was_read < 0) {
      perror("Failed with select\n");
      return 1;
    }
    if (FD_ISSET(_socket, &_socket_set)) {
      int was_accepted = acceptNewConnection();
      if (was_accepted) {
        perror("Failed with accept\n");
        return 1;
      }
    }
    processConnections();
  }
  return 0;
}

void Server::buildSocketSet()
{
  FD_ZERO(&_socket_set);
  FD_SET(_socket, &_socket_set);
  for(auto connection : _connections_vec) {
    if (connection) {
      FD_SET(connection, &_socket_set);
    }
  }
}

int Server::acceptNewConnection()
{
  int new_connection = accept(_socket, NULL, NULL);
  int opts;
  opts = fcntl(new_connection,F_GETFL);
  if (opts < 0) {
    printf("fcntl(F_GETFL)\n");
    return 1;
  }
  opts = (opts | O_NONBLOCK);
  if (fcntl(new_connection,F_SETFL,opts) < 0) {
    printf("fcntl(F_SETFL)\n");
    return 1;
  }
  auto connection_it = std::find(_connections_vec.begin(), _connections_vec.end(), 0);
  if (_connections_vec.end() == connection_it) {
    _connections_vec.push_back(new_connection);
  } else {
    *connection_it = new_connection;
  }
  return 0;
}

int Server::processConnections()
{
  for (auto connection : _connections_vec) {
    if (FD_ISSET(connection, &_socket_set)) {
      ///@todo(tolstoy) Заменить на запуск тредов по обработке
      char buffer[256];
      char *cur_char;
      memset(buffer, 0, sizeof(buffer));
      if (read(connection,buffer,255) < 0) {
        printf("\nConnection lost: FD=%d;  Slot=%d\n",
               connection,
               std::distance(_connections_vec.begin(), std::find(_connections_vec.begin(), _connections_vec.end(), connection)));
        close(connection);
        printf("105\n");
        connection = 0;
      } else {
        printf("\nReceived: %s; ",buffer);
        cur_char = buffer;
        while (cur_char[0] != 0) {
          cur_char[0] = toupper(cur_char[0]);
          cur_char++;
        }
        write(connection,buffer, sizeof(buffer));
        write(connection,"\n", 1);
        printf("responded: %s\n",buffer);
      }
    }
  }
  return 0;
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
