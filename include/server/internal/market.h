#ifndef SERVER_INTERNAL_MARKET_H
#define SERVER_INTERNAL_MARKET_H

#include <memory>
#include <utility>
#include <queue>

#include "player.h"

class Ruleset;

class Market {
public:
  using Limit = std::pair<int, int>;
  ///@brief очередь из пар<айдишник игрока, пара<ставка на продажу, ставка на покупку>
  using BidQueue = std::queue<std::pair<int, std::pair<Player::Bid, Player::Bid>>;
  ///@brief контейнер результатов торгов пара<айди, пара<продано материала, куплено продукции>>
  ///@think(tolstoy) подумать нет ли контейнера сильно лучше
  using ResultContainer = std:queue<std::pair<int, std::pair<int, int>>;

public:
  Market(std::shared_ptr<Ruleset> r) : _ruleset(r) {}
  ~Market();
  ///@brief задать лимиты
  void setLimits(Limit raw, Limit production);
  ///@brief обработать заявки на покупку ресурсов и продажу продукции
  ///@think(think) а может принимать rvalue reference и отдавать так же.
  shared_ptr<ResultContainer> processBids(shared_ptr<BidQueue>);
  
private:
<<<<<<< HEAD
  ///@brief лимит продажи материалов
  Limit _raw;
  ///@brief лимит покупки материалов
  Limit _production;

=======
  ///@brief Cостояние рынка. Рынок может занимать один из пяти уровней.
  int _state;
  ///@brief Набор правил, заимствованых у сессии
  std::shared_ptr<Ruleset> _ruleset;
>>>>>>> origin/abby_serv
};

#endif //SERVER_INTERNAL_MARKET_H
