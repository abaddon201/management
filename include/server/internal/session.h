#ifndef SERVER_INTERNAL_SESSION_H
#define SERVER_INTERNAL_SESSION_H

#include <memory>
#include <thread>

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
  Session(int id);
  Session(int id, std::shared_ptr<Ruleset> rules);
  Session(int id, std::string passwd);
  Session(int id, std::string passwd, int player_id);
  Session(int id, std::shared_ptr<Ruleset> rules, std::string passwd);
  Session(int id, std::shared_ptr<Ruleset> rules, std::string passwd, int player_id);
  ~Session();
  ///@brief Возвращает айди сессии
  int id() {return _id;}
  ///@brief Возвращает пароль сессии
  std::string password() {return _password;}
  ///@brief Подключает игрока к сессии
  /// @returns true - если успешно подключен, false - Если нет
  bool connectPlayer(int id);
  ///@brief Отсоединение игрока от сессии
  ///
  /// Меняет состояние сессии, в соотв. с тем остались ли игроки или нет.
  /// @returns true - если это был последний игрок, false - если игроки ещё остались
  bool disconnectPlayer(Player::Id player_id);
  ///@brief Когда все игроки сделали ставки, сессия вызывает обработку хода и переходит в следующий месяц
  void makeTurn();
  ///@brief Возвращает указатель на набор правил
  std::shared_ptr<Ruleset> ruleset() {return _ruleset;}
  ///@brief Изменяем параметры игрока на основе полученного от клиента хода
  bool setPlayerTurn(int player_id, int build_orders, int production_orders, const Player::Bid &raw, const Player::Bid &prod);

private:
  ///@brief Session mutex
//  std::unique_ptr<std::mutex> _session_mutex;
  std::mutex _session_mutex;
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

  ///@brief Возвращает количество активных игроков (не банкротов, и не отключившихся)
  int getPlayersInGame();
  ///@brief Создаёт список из текущих сырьевых ставок игроков
  Market::BidList getRawBids();
  ///@brief Создаёт список из текущих продуктовых ставок игроков
  Market::BidList getProductionBids();
};

#endif //SERVER_INTERNAL_SESSION_H
