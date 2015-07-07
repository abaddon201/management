#ifndef SERVER_INTERNAL_SESSION_H
#define SERVER_INTERNAL_SESSION_H

#include <memory>

#include "market.h"
#include "player.h"
#include "ruleset.h"

class Session {
  ///@brief Псевдоним для итератора по списку игроков 
  using Pit = std::list<std::shared_ptr<Player>>::iterator;
  ///@brief Состояние в котором сейчас находится сессия
  enum class State {
    WAITING_FOR_PLAYERS,
    PLAYING,
    FINISHED
  };
public:
  Session();
  ~Session();
private:
  ///@brief Идентификатор сессии
  int _id;
  ///@brief Пароль для доступа к сессии
  std::string _password;
  ///@brief Список умных указателей на игроков
  // TODO:(tolstoy) а список ли? поменять на более разумное
  std::list<std::shared_ptr<Player>> _player_pointer_list
  ///@brief Указатель на рынок сессии
  std::shared_ptr<Market> _market;
  ///@brief Указатель на состав правил
  std::shared_ptr<Ruleset> _ruleset;
  ///@brief Состояние сессии
  State _state;
};

#endif //SERVER_INTERNAL_SESSION_H
