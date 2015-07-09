#include "market.h"
#include "session.h"
#include <cstdlib>

void Market::makeTurn(int players_in_game, BidQueue& raw_bids, BidQueue& production_bids) {
  processBids(players_in_game, raw_bids, production_bids);
  changeState();
}

void Market::changeState() {
  int pos = 0;
  for(double v:_ruleset->_market_state_matrix.at(_state)) {
    double rnd = (double)std::rand()/(double)RAND_MAX;
    if (rnd<v) {
      _state = pos;
      return;
    }
  }
}

void Market::processBids(int players_in_game, BidQueue &raw_bids, BidQueue &production_bids) {
  ///@todo (abby): не реализовно нихрена
}
