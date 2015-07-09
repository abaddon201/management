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
  using BidQueue = std::list<Player::Bid>;

public:
  Market(std::shared_ptr<Ruleset> r) : _ruleset{r} {}
  ~Market();

  ///@brief производит ход рынка
  /// @param players_in_game Количество игроков, которые ещё не разорились
  /// @param raw_bids Ставки игроков на закупку материалов
  /// @param production_bids Ставки игроков на продажу товаров
  void makeTurn(int players_in_game, BidQueue& raw_bids, BidQueue& production_bids);

private:
  ///@brief текущее состояние рынка
  int _state;
  ///@brief указатель на набор правил
  std::shared_ptr<Ruleset> _ruleset;

  ///@brief меняет состояние рынка, в соотв. с правилами
  void changeState();
  ///@brief обсчитывает ставки
  /// @param players_in_game Количество игроков, которые ещё не разорились
  /// @param raw_bids Ставки игроков на закупку материалов
  /// @param production_bids Ставки игроков на продажу товаров
  void processBids(int players_in_game, BidQueue& raw_bids, BidQueue& production_bids);
};

#endif //SERVER_INTERNAL_MARKET_H
