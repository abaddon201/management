#ifndef SERVER_INTERNAL_PLAYER_H
#define SERVER_INTERNAL_PLAYER_H

#include <utility>
#include <memory>
#include <string>
#include <queue>
#include <list>

#include "storage.h"
#include "factory.h"
#include "ruleset.h"

class Player {
public:
  ///@brief Псеводним для типа очереди строящихся фабрик
  using FactoryQueue = std::queue<std::unique_ptr<Factory>>;
  ///@brief Псевдоним для списка игроков
  using List = std::list<std::shared_ptr<Player>>;
  ///@brief Псевдоним для итератора по списку игроков
  using Iterator = Player::List::iterator;
  using Id = int;

  enum class State {
    LOGGED_IN, ///<@brief Залогинился, но ещё не активен @todo (abby): может вообще не нужное состояние
    READY, ///<@brief Подготовил ход (сделал все действия)
    BANKRUPT, ///<@brief Разорился
    THINKING, ///<@brief Активен, думает над ходом
    LOST  ///<@brief Соединение потеряно
  };

  struct Bid {
    int requested_cost;
    int requested_quantity;
    int accepted_quantity;
    Player::Id player;
  };

  Player(std::shared_ptr<Ruleset> ruleset, Player::Id id) : _id{id}, _ruleset{ruleset} {}
  ~Player() {}

  ///@brief Возвращает идентификатор игрока
  Id id() {return _id;}
  ///@brief Устанавливает идентификатор игрока
  void setId(int id) { _id = id;}
  ///@brief Обновляет состояние игрока после вычислений на рынке
  void updateState(int turn, Bid raw_bid, Bid production_bid);
  ///@brief возвращает состояние игрока
  State state() {return _state;}
  ///@brief возвращает ставку игрока по материалам
  Bid rawBid() {return _current_buy_raw_bid;}
  ///@brief возвращает ставку игрока по продукции
  Bid productionBid() {return _current_sell_production_bid;}

private:
  ///@brief Идентификатор игрока
  Id _id;
  ///@brief Количество продукции, которое запланировал произвести игрок
  int _production_planned;
  ///@brief Сколько фабрик запланировал построить игрок
  int _building_planned;
  ///@brief Ставка игрока на аукцион по покупке материалов
  Bid _current_buy_raw_bid;
  ///@brief Ставка игрока на аукцион по продаже продукции
  Bid _current_sell_production_bid;
  ///@brief Склад продукции и материалов
  Storage _storage;
  ///@brief Количество функционирующих фабрик
  int _number_of_working_factories;
  ///@brief Итератор спискa указателей на фабрики, находящиеся в стадии строительства
  FactoryQueue _factories_to_build;
  ///@brief Имеющиеся в распоряжении деньги
  int _cash;
  ///@brief Ссылка на правила
  std::shared_ptr<Ruleset> _ruleset;
  ///@brief Состояние игрока
  State _state;

  ///@brief Заказ новых фабрик
  void orderFactories(int turn);
  ///@brief Производит строительство фабрик
  void buildFactories(int turn);
  ///@brief Производит материалы из сырья
  ///@param amount Количество продукции, которое хочет произвести игрок.
  void manufacture();
  ///@brief Производит расплату за склад, фабрики и прочее
  void payBills();
  ///@brief Производит обработку ставок
  void processBids();
};

#endif //SERVER_INTERNAL_PLAYER_H
