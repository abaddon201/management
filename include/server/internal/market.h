#ifndef SERVER_INTERNAL_MARKET_H
#define SERVER_INTERNAL_MARKET_H

#include <memory>
#include <utility>
#include <queue>

#include "player.h"

#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
#include "gtest/gtest_prod.h"
#endif

struct Ruleset;

class Market {
public:
  using Limit = std::pair<int, int>;
  ///@brief очередь из пар<айдишник игрока, пара<ставка на продажу, ставка на покупку>
  using BidList = std::vector<Player::Bid>;

public:
  Market(std::shared_ptr<Ruleset> r) : _ruleset{r} {_state = r->market_state;}
  ~Market() {};

  ///@brief производит ход рынка
  /// @param players_in_game Количество игроков, которые ещё не разорились
  /// @param raw_bids Ставки игроков на закупку материалов
  /// @param production_bids Ставки игроков на продажу товаров
  void makeTurn(int players_in_game, BidList& raw_bids, BidList& production_bids);
  int state() {return _state;}
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
  void processBids(int players_in_game, BidList& raw_bids, BidList& production_bids);
  ///@brief Перетасовывает случайным образом блоки ставок с одинаковой ценой
  /// @param @bids список ставок (должен быть отсортирован по цене ставки
  void randomizeBids(BidList& bids);
#ifdef GTEST_INCLUDE_GTEST_GTEST_H_
  FRIEND_TEST(Market, DefaultState);
  FRIEND_TEST(Market, ProcessBids);
#endif
};

#endif //SERVER_INTERNAL_MARKET_H
