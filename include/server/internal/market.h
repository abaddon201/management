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
private:
  ///@brief Cостояние рынка. Рынок может занимать один из пяти уровней.
  int _state;

};

#endif //SERVER_INTERNAL_MARKET_H
