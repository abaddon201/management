#ifndef SERVER_INTERNAL_MARKET_H
#define SERVER_INTERNAL_MARKET_H

#include "player.h"

class Ruleset;

class Market {
public:
  Market(std::shared_ptr<Ruleset> r) : _ruleset(r) {}
  ~Market();
  ///@brief сменить состояние рынка
  void changeState();
  ///@brief геттер состояния рынка
  int state();
private:
  ///@brief Cостояние рынка. Рынок может занимать один из пяти уровней.
  int _state;
  ///@brief Набор правил, заимствованых у сессии
  std::shared_ptr<Ruleset> _ruleset;
};

#endif //SERVER_INTERNAL_MARKET_H
