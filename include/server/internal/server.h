#ifndef SERVER_INTERNAL_SERVER_H
#define SERVER_INTERNAL_SERVER_H

#include <list>
#include <memory>

class Server {
public:
  enum class JsonMessageStates {
    SUCCESSFULY_PARSED,
    UNNOWN_ACTION,
    BAD_ARGS
  };

public:
  ///@brief Конструктор
  Server();
  ///@brief Деструктор
  ~Server();
  ///@brief Создать новую сессию
  void createSession();

private:
  ///@brief Сокет на котором биндимся
  int _socket;
  ///@brief Список сессий
  std::list<std::unique_ptr<Session>> _sessions;

  ///@brief Распаршиваем полученное сообщение
  JsonMessageStates parseMessage(std::string const &msg);
};

#endif // SERVER_H
