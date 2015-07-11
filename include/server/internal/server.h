#ifndef SERVER_INTERNAL_SERVER_H
#define SERVER_INTERNAL_SERVER_H

#include <memory>
#include <list>
#include <functional>

#include "rapidjson/document.h"

#include "session.h"

class Server {
public:
  ///@brief Результаты парсинга
  enum class JsonMessageStates {
    SUCCESSFULY_PARSED,
    UNNOWN_ACTION,
    BAD_ARGS
  };
  ///@brief Варинты действий требуемых клиентами
  enum Actions {
    REGISTER_USER,
    DELETE_USER,
    CREATE_SESSION,
    CONNECT_SESSION,
    GIVE_TURN_IN_SESSION,
    DISCONNECT_SESSION,
    LIST_SESSIONS,
    NUMBER_OF_ACTIONS
  };

public:
  ///@brief Конструктор
  Server();
  ///@brief Деструктор
  ~Server();
  ///@brief Создать новую сессию
  void createSession();

private:
  ///@brief Вектор обработчиков действий требуемых клиентом
  std::vector<std::function<JsonMessageStates(const rapidjson::Document& doc)>> _message_reactions_vec;
  ///@brief Сокет на котором биндимся
  int _socket;
  ///@brief Список сессий
  std::list<std::unique_ptr<Session>> _sessions;

public:
  ///@brief Распаршиваем полученное сообщение
  JsonMessageStates processMessage(const std::string& msg);
private:
  ///@brief Регистрируем пользователя
  JsonMessageStates registerUser(const rapidjson::Document& doc);
  ///@brief Удаляем пользователя
  JsonMessageStates deleteUser(const rapidjson::Document& doc);
  ///@brief Создаем сессию
  JsonMessageStates createNewSession(const rapidjson::Document& doc);
  ///@brief Присоединяем пользователя к сессии
  JsonMessageStates connectSession(const rapidjson::Document& doc);
  ///@brief Передаем ход в сессию
  JsonMessageStates giveTurnInSession(const rapidjson::Document& doc);
  ///@brief Отсоединяем пользователя от сессии
  JsonMessageStates disconnectSession(const rapidjson::Document& doc);
  ///@brief Собираем список сессий
  JsonMessageStates listSessions(const rapidjson::Document& doc);
};

#endif // SERVER_H
