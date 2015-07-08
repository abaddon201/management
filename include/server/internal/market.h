#ifndef SERVER_INTERNAL_MARKET_H
#define SERVER_INTERNAL_MARKET_H

#include "player.h"

class Session;

class Market {
public:
  Market(Session* s) : _session(s) {}
  ~Market();
  ///@brief сменить состояние рынка
  void changeState();
  ///@brief геттер состояния рынка
  int state();
  ///@brief возвращает указатель на набор правил
  std::shared_ptr<Ruleset> ruleset() {return _ruleset;}
private:
  ///@brief Cостояние рынка. Рынок может занимать один из пяти уровней.
  int _state;
  ///@brief Указатель на состав правил
  std::shared_ptr<Ruleset> _ruleset;
};

#endif //SERVER_INTERNAL_MARKET_H
