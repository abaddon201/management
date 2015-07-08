#ifndef SERVER_INTERNAL_SESSION_H
#define SERVER_INTERNAL_SESSION_H

#include <memory>

#include "market.h"
#include "player.h"
#include "ruleset.h"

class Session {
public:
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
  bool connectPlayer();
  ///@brief Отсоединение игрока от сессии
  ///
  /// Меняет состояние сессии, в соотв. с тем остались ли игроки или нет.
  /// @returns true - если это был последний игрок, false - если игроки ещё остались
  bool disconnectPlayer(int player_id);
  ///@brief Когда все игроки сделали ставки, сессия вызывает обработку хода и переходит в следующий месяц
  void makeTurn();
  ///@brief возвращает указатель на набор правил
  std::shared_ptr<Ruleset> ruleset() {return _ruleset;}

private:
  ///@brief Идентификатор сессии
  int _id;
  ///@brief Пароль для доступа к сессии
  std::string _password;
  ///@brief Указатель на состав правил
  std::shared_ptr<Ruleset> _ruleset;
  ///@brief Список умных указателей на игроков
  Player::List _player_pointer_list;
  ///@brief Указатель на рынок сессии
  std::shared_ptr<Market> _market;
  ///@brief Состояние сессии
  State _state;
  ///@brief Номер хода
  int _turn_number;

  ///@brief Обработать ход игроков
  void doPlayers();
};

#endif //SERVER_INTERNAL_SESSION_H
