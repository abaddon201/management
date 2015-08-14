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
  ///@brief Псевдоним для типа идентификатора
  using Id = int;

  enum class State {
    LOGGED_IN, ///<@brief Залогинился, но ещё не активен @todo (abby): может вообще не нужное состояние
    READY, ///<@brief Подготовил ход (сделал все действия)
    BANKRUPT, ///<@brief Разорился
    THINKING, ///<@brief Активен, думает над ходом
    LOST  ///<@brief Соединение потеряно
  };

  ///@brief Структура ставки
  struct Bid {
    Bid() : requested_cost{0}
    , requested_quantity{0}
    , accepted_quantity{0}
    , player{0} {}
    int requested_cost; ///<@brief Запрошенная цена
    int requested_quantity; ///<@brief Запрошенное кол-во
    int accepted_quantity; ///<@brief Принятое рынком количество
    Player::Id player; ///<@brief Идентификатор игрока, сделавшего ставку
  };

  ///@brief Конструктор игрока
  /// @param ruleset набор правил, которым подчиняется игрок
  /// @param id Идентификатор игрока (генерируется сервером)
  Player(std::shared_ptr<Ruleset> ruleset, Player::Id id)
    : _id{id}
    , _production_planned{0}
    , _building_planned{0}
    , _storage{ruleset->startup_products, ruleset->startup_raw}
    , _number_of_working_factories{ruleset->startup_factory_count}
    , _cash{ruleset->startup_money}
    , _ruleset{ruleset}
    , _state{State::LOGGED_IN}
  {}
  ~Player() {}

  ///@brief Возвращает идентификатор игрока
  Id id() {return _id;}
  ///@brief Устанавливает идентификатор игрока
  void setId(int id) { _id = id;}
  ///@brief Обновляет состояние игрока после вычислений на рынке
  void updateState(int turn);
  ///@brief возвращает состояние игрока
  State state() {return _state;}
  ///@brief возвращает ставку игрока по материалам
  Bid& rawBid() {return _current_buy_raw_bid;}
  ///@brief возвращает ставку игрока по продукции
  Bid& productionBid() {return _current_sell_production_bid;}

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

#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
  FRIEND_TEST(Session, ProcessBids);
#endif
};

#endif //SERVER_INTERNAL_PLAYER_H
