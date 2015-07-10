#include <vector>

#include "server.h"

std::vector<std::string> const actions {
  "register_user" ,
  "delete_user",
  "create_session",
  "connect_session",
  "make_turn",
  "disconnect_session"
  "list_sessions"
};

Server::Server() {}

Server::~Server() {}

void Server::createSession() {}

Server::JsonMessageStates Server::parseMessage(std::string const &msg) {
  return JsonMessageStates::SUCCESSFULY_PARSED;
}
