#include "market.h"
#include "session.h"

#include <algorithm>

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

  raw_bids.sort([](const Player::Bid& a, const Player::Bid& b) {return b.requested_cost < a.requested_cost;});
  production_bids.sort([](const Player::Bid& a, const Player::Bid& b) {return b.requested_cost > a.requested_cost;});
}
