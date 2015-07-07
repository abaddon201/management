#ifndef SERVER_INTERNAL_MARKET_H
#define SERVER_INTERNAL_MARKET_H

class Market {
public:
  Market();
  ~Market();
  ///@brief сменить состояние рынка
  void changeState();
private:
  ///@brief Cостояние рынка. Рынок может занимать один из пяти уровней.
  int _state;
  ///@brief Текущее количество игроков
  int _current_number_of_players;
};

#endif //SERVER_INTERNAL_MARKET_H
