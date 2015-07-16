#include <cstdlib>
#include <algorithm>
#include "internal/session.h"
#include "internal/market.h"


void Market::makeTurn(int players_in_game, BidQueue& raw_bids, BidQueue& production_bids) {
  processBids(players_in_game, raw_bids, production_bids);
  changeState();
}

void Market::changeState() {
  int pos = 0;
  for(double v:_ruleset->market_state_matrix.at(_state)) {
    double rnd = (double)std::rand()/(double)RAND_MAX;
    if (rnd<v) {
      _state = pos;
      return;
    }
  }
}

void Market::processBids(int players_in_game, BidQueue &raw_bids, BidQueue &production_bids) {
  ///@todo (abby): не реализовно нихрена
  int max_buy_quantity = _ruleset->market_production.at(_state).first * players_in_game;
  int max_buy_cost = _ruleset->market_production.at(_state).second;
  int max_sell_quantity = _ruleset->market_raw.at(_state).first * players_in_game;
  int min_sell_cost = _ruleset->market_raw.at(_state).second;

  int total_raw_bids = 0;
  std::for_each(raw_bids.begin(), raw_bids.end(), [&total_raw_bids](Player::Bid& a) {total_raw_bids+=a.requested_quantity;});
  int total_prod_bids = 0;
  std::for_each(production_bids.begin(), production_bids.end(), [&total_prod_bids](Player::Bid& a) {total_prod_bids+=a.requested_quantity;});
  if (total_raw_bids<max_sell_quantity) {
    // Можем удовлетворить все запросы
    std::for_each(raw_bids.begin(), raw_bids.end(), [](Player::Bid& a) {a.accepted_quantity = a.requested_quantity;});
  } else {
    raw_bids.sort([](const Player::Bid& a, const Player::Bid& b) {return b.requested_cost < a.requested_cost;});
  }
  if (total_prod_bids<max_buy_quantity) {
    // Можем удовлетворить все запросы
    std::for_each(production_bids.begin(), production_bids.end(), [](Player::Bid& a) {a.accepted_quantity = a.requested_quantity;});
  } else {
    production_bids.sort([](const Player::Bid& a, const Player::Bid& b) {return b.requested_cost > a.requested_cost;});
  }
}
