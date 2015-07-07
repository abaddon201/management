#ifndef SERVER_INTERNAL_SESSION_H
#define SERVER_INTERNAL_SESSION_H

#include <memory>

#include "market.h"
#include "player.h"
#include "ruleset.h"

class Session {
  ///@brief Состояние в котором сейчас находится сессия
  enum class State {
    WAITING_FOR_PLAYERS,
    PLAYING,
    FINISHED
  };
public:
  Session();
  ~Session();

  ///@brief Подключает игрока к сессии
  /// @returns true - если успешно подключен, false - Если нет
  bool connectPlayer() {
    if (_state!=State::WAITING_FOR_PLAYERS)
      return false;
    if (_player_pointer_list.size() == _ruleset->_max_players) {
      return false;
    }
    _player_pointer_list.push_back(std::shared_ptr<Player>(new Player()));
    return true;
  }
  ///@brief Отсоединение игрока от сессии
  ///
  /// Меняет состояние сессии, в соотв. с тем остались ли игроки или нет.
  /// @returns true - если это был последний игрок, false - если игроки ещё остались
  bool disconnectPlayer(int player_id) {
    _player_pointer_list.remove_if([player_id](std::shared_ptr<Player> p) {return p->getId() == player_id;});
    if (0 == _player_pointer_list.size()) {
      _state = State::FINISHED;
      return true;
    }
    return false;
  }

  ///@brief когда все игроки готовы, производит рассчёт хода
  void makeTurn();
  ///@brief возвращает указатель на набор правил
  std::shared_ptr<Ruleset> ruleset() {return _ruleset;}
private:
  ///@brief Идентификатор сессии
  int _id;
  ///@brief Пароль для доступа к сессии
  std::string _password;
  ///@brief Список умных указателей на игроков
  // TODO:(tolstoy) а список ли? поменять на более разумное
  Player::List _player_pointer_list;
  ///@brief Указатель на рынок сессии
  std::shared_ptr<Market> _market;
  ///@brief Указатель на состав правил
  std::shared_ptr<Ruleset> _ruleset;
  ///@brief Состояние сессии
  State _state;

};

#endif //SERVER_INTERNAL_SESSION_H
