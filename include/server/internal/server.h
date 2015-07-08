#ifndef SERVER_INTERNAL_SERVER_H
#define SERVER_INTERNAL_SERVER_H

#include <list>
#include <memory>

class Server {
public:
  void createSession();

private:
  ///@brief Сокет на котором биндимся
  int _socket;
  ///@brief Список сессий
  std::list<std::unique_ptr<Session>> _sessions;
};

#endif // SERVER_H
