#include <cstdlib>
#include <algorithm>
#include <iostream>

#include "internal/session.h"
#include "internal/market.h"


void Market::makeTurn(int players_in_game, BidList& raw_bids, BidList& production_bids) {
  processBids(players_in_game, raw_bids, production_bids);
  changeState();
}

void Market::changeState() {
  int pos = 0;
  double sum = 0;

  for(double v:_ruleset->market_state_matrix.at(_state)) {
    sum += v;
  }

  double rnd = sum*(double)std::rand()/(double)RAND_MAX;
  sum = 0;
  for(double v:_ruleset->market_state_matrix.at(_state)) {
    sum+=v;
    if (rnd<=sum) {
      _state = pos;
      return;
    }
    pos++;
  }
}

void Market::randomizeBids(BidList& bids) {
  BidList::iterator it = bids.begin();
  BidList::iterator first_it = bids.begin();
  BidList::iterator last = bids.begin();
  // рандомизировать группы с одинаковыми ценами
  while(it!=bids.end()) {
    first_it = it;
    last = it;
    std::cout<<"b"<<std::endl;
    while ((it != bids.end()) && (it->requested_cost == first_it->requested_cost)) {
      ++last;
      ++it;
      std::cout<<"c"<<std::endl;
    }
    if (last!=bids.end())
      ++last;
    std::random_shuffle(first_it, last);
  }
}

void Market::processBids(int players_in_game, BidList &raw_bids, BidList &production_bids) {
  ///@todo (abby): не реализовно нихрена
  int max_prod_quantity = _ruleset->market_production.at(_state).first * players_in_game;
  ///@fixme (abby): по ходу, цены рынка интересны только в гуйне... Хотя, можно добавить проверку и сюда, но не логично...
  int max_prod_cost = _ruleset->market_production.at(_state).second;
  int max_raw_quantity = _ruleset->market_raw.at(_state).first * players_in_game;
  int min_raw_cost = _ruleset->market_raw.at(_state).second;

  int total_raw_bids = 0;
  std::for_each(raw_bids.begin(), raw_bids.end(), [&total_raw_bids](Player::Bid& a) {total_raw_bids+=a.requested_quantity;});
  int total_prod_bids = 0;
  std::for_each(production_bids.begin(), production_bids.end(), [&total_prod_bids](Player::Bid& a) {total_prod_bids+=a.requested_quantity;});
  if (total_raw_bids < max_raw_quantity) {
    // Можем удовлетворить все запросы
    std::for_each(raw_bids.begin(), raw_bids.end(), [](Player::Bid& a) {a.accepted_quantity = a.requested_quantity;});
  } else {
    std::cout<<"not enougth"<<std::endl;
    std::sort(raw_bids.begin(), raw_bids.end(), [](const Player::Bid& a, const Player::Bid& b) {return b.requested_cost < a.requested_cost;});
    randomizeBids(raw_bids);
    std::cout<<"randomed"<<std::endl;
    for(auto it=raw_bids.begin(); it!=raw_bids.end(); ++it) {
      std::cout<<"req="<<it->requested_quantity<<", max="<<max_raw_quantity<<std::endl;
      if (it->requested_quantity > max_raw_quantity) {
        it->accepted_quantity = max_raw_quantity;
        break;
      }
      it->accepted_quantity = it->requested_quantity;
      max_raw_quantity-=it->requested_quantity;
    }
  }
  if (total_prod_bids<max_prod_quantity) {
    // Можем удовлетворить все запросы
    std::for_each(production_bids.begin(), production_bids.end(), [](Player::Bid& a) {a.accepted_quantity = a.requested_quantity;});
  } else {
    std::sort(production_bids.begin(), production_bids.end(), [](const Player::Bid& a, const Player::Bid& b) {return b.requested_cost > a.requested_cost;});
    randomizeBids(production_bids);
    for(auto it=production_bids.begin(); it!=production_bids.end(); ++it) {
      if (it->requested_quantity > max_prod_quantity) {
        it->accepted_quantity = max_prod_quantity;
        break;
      }
      it->accepted_quantity = it->requested_quantity;
      max_prod_quantity-=it->requested_quantity;
    }
  }
}
