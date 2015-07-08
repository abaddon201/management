#ifndef SERVER_INTERNAL_PLAYER_H
#define SERVER_INTERNAL_PLAYER_H

#include <utility>
#include <memory>
#include <string>
#include <queue>
#include <list>

#include "storage.h"
#include "factory.h"

class Player {
  // Bid. Это пара целых чисел, первое из которых это количество единиц, а второе - цена.
  // TODO: (tolstoy) Вообще стоит создание псевдонима вынести отсюда, поскольку оно будет нужно не только тут
    // THINK: (abby) Зато тип будет красивый Player::Bid ... В общем, я бы не торопился
  using Bid = std::pair<int,int>;
public:
  ///@brief Псеводним для типа очереди строящихся фабрик
  using FactoryQueue = std::queue<std::unique_ptr<Factory>>;
  ///@brief Псевдоним для списка игроков
  using List = std::list<std::shared_ptr<Player>>;
  ///@brief Псевдоним для итератора по списку игроков
  using Iterator = Player::List::iterator;

  Player() {_id = generateSomeUniqueId();}
  ~Player() {}
  int getId() {return _id;}
  int generateSomeUniqueId() {return std::rand();} ///@fixme: (abby): написать генератор уникального
private:
  ///@brief Идентификатор игрока
  int _id;
  ///@brief Пароль игрока
  std::string _password;
  ///@brief Псевдоним игрока
  std::string _nickname;
  ///@brief Завершил ли пользователь свой ход
  bool _if_made_turn;
  ///@brief Ставка игрока на аукцион по покупке материалов
  Bid _current_buy_raw_bid;
  ///@brief Ставка игрока на аукцион по продаже продукции
  Bid _current_sell_production_bid;
  ///@brief Склад продукции и материалов
  Storage _storage_room;
  ///@brief Количество функционирующих фабрик
  int _number_of_working_factories;
  ///@brief Количество строящихся фабрик
  int _number_of_factories_under_construction;
  ///@brief Итератор спискa указателей на фабрики, находящиеся в стадии строительства
  FactoryQueue _factory_ptr_queue;
  ///@brief Имеющиеся в распоряжении деньги
  int _cash;
};

#endif //SERVER_INTERNAL_PLAYER_H
