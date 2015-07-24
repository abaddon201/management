#ifndef SERVER_INTERNAL_SERVER_H
#define SERVER_INTERNAL_SERVER_H

#include <sys/select.h>

#include <memory>
#include <list>
#include <functional>
#include <thread>
#include <future>

#include "rapidjson/document.h"

#include "session.h"

class Server {
public:
  ///@brief Результаты парсинга
  enum class JsonMessageStates {
    SUCCESSFULY_PARSED,
    UNNOWN_ACTION,
    BAD_ARGS,
    ACTION_DENIED
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
  Server(int port_num);
  ///@brief Деструктор
  ~Server();
  ///@brief Создать новую сессию
  void createSession();
  ///@brief Стартовать сервер
  int start();

private:
  ///@brief Вектор обработчиков действий требуемых клиентом
  std::vector<std::function<JsonMessageStates(const rapidjson::Document& doc)>> _message_reactions_vec;
  ///@brief Сокет на котором биндимся
  int _socket;
  ///@brief Номер порта на котором висим
  int _port_num;
  ///@brief Сет сокетов для просмотра селектом
  fd_set _socket_set;
  ///@brief Вектор текущих дескрипторов соединений
  std::vector<int> _connections_vec;
  ///@brief Global Mutex
  std::mutex _list_mutex;
  ///@brief Вектор фьючерсов в которых мы обрабатываем сообщения пришедшие от клиентов
  std::vector<std::future<JsonMessageStates>> _futures_vec;
  ///@brief Список сессий
  std::list<std::unique_ptr<Session>> _sessions;

  ///@brief Первично проверим формат и отдаем полученное сообщение обработчику
  JsonMessageStates processMessage(const std::string &&msg);
  ///@brief Регистрируем пользователя
  JsonMessageStates registerUserHandler(const rapidjson::Document &doc);
  ///@brief Удаляем пользователя
  JsonMessageStates deleteUserHandler(const rapidjson::Document &doc);
  ///@brief Создаем сессию
  JsonMessageStates createNewSessionHandler(const rapidjson::Document &doc);
  ///@brief Присоединяем пользователя к сессии
  JsonMessageStates connectSessionHandler(const rapidjson::Document &doc);
  ///@brief Передаем ход в сессию
  JsonMessageStates giveTurnInSessionHandler(const rapidjson::Document &doc);
  ///@brief Отсоединяем пользователя от сессии
  JsonMessageStates disconnectSessionHandler(const rapidjson::Document &doc);
  ///@brief Собираем список сессий
  JsonMessageStates listSessionsHandler(const rapidjson::Document &doc);
  ///@brief Начинаем слушать на сокете и обрабатывать соединения входящие
  int work();
  ///@brief Готовимся к вызову select
  void buildSocketSet();
  ///@brief Подключаем новое соединение
  int acceptNewConnection();
  ///@brief Обрабатываем пришедшие соединения
  int processConnections();
  ///@brief Выдает айди игрока
  ///@returns Айди игрока в виде целого числа, чтобы знаний о внутренней логике не давать серверу
  ///
  ///@param player_login Логин игрока
  ///@param player_password Пароль игрока
  int retrievePlayerId(const char *player_login, const char *player_password);
  ///@brief Выдает айди сессии
  ///@returns Айди сессии в виде целого числа, чтобы знаний о внутренней логике не давать серверу
  int retrieveSessionId();

};

#endif // SERVER_INTERNAL_SERVER_H
