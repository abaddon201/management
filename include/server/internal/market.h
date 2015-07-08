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
private:
  ///@brief Cостояние рынка. Рынок может занимать один из пяти уровней.
  int _state;
  ///@brief Указатель на сессию. Именно raw pointer, чтобы не было циклических зависимостей объектов
  Session* _session;
};

#endif //SERVER_INTERNAL_MARKET_H
