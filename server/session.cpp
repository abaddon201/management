#include <algorithm>
#include <iostream>

#include "internal/session.h"

Session::Session(int id): Session(id, std::make_shared<Ruleset>(Ruleset::DEFAULT), std::string("")) {}

Session::Session(int id, std::shared_ptr<Ruleset> rules): Session(id, rules, std::string(""))  {}

Session::Session(int id, std::string passwd): Session(id, std::make_shared<Ruleset>(Ruleset::DEFAULT), passwd) {}

Session::Session(int id, std::shared_ptr<Ruleset> rules, std::string passwd): _id{id}, _password{passwd}, _ruleset{rules} {_state=State::WAITING_FOR_PLAYERS;}

Session::~Session() {
}

bool Session::connectPlayer(int id) {
  if (_state!=State::WAITING_FOR_PLAYERS)
    return false;
  if (_player_pointer_list.size() == _ruleset->max_players) {
    return false;
  }
  _player_pointer_list.push_back(std::shared_ptr<Player>(new Player(_ruleset, static_cast<Player::Id>(id))));
  return true;
}

bool Session::disconnectPlayer(Player::Id player_id) {
  _player_pointer_list.remove_if([player_id](std::shared_ptr<Player> p) {return p->id() == player_id;});
  if (0 == _player_pointer_list.size()) {
    _state = State::FINISHED;
    return true;
  }
  return false;
}

void Session::makeTurn() {
  Market::BidList raw_bids = getRawBids();
  Market::BidList production_bids = getProductionBids();
  _market->makeTurn(getPlayersInGame(), raw_bids, production_bids);
  for(auto p: _player_pointer_list) {
    Player::Id id = p->id();
    Market::BidList::const_iterator raw = std::find_if(raw_bids.cbegin(), raw_bids.cend(), [id] (const Player::Bid& bid) {return bid.player == id;});
    Market::BidList::const_iterator prod = std::find_if(production_bids.cbegin(), production_bids.cend(), [id] (const Player::Bid& bid) {return bid.player == id;});

    if (raw!=raw_bids.end())
      p->rawBid().accepted_quantity = raw->accepted_quantity;
    else
      p->rawBid().accepted_quantity = 0;
    if (prod!=production_bids.end())
      p->productionBid().accepted_quantity = prod->accepted_quantity;
    else
      p->productionBid().accepted_quantity = 0;
    p->updateState(_turn_number);
  }
}

int Session::getPlayersInGame() {
  return std::count_if(_player_pointer_list.begin(), _player_pointer_list.end(), [](std::shared_ptr<Player> p) { return (p->state()!=Player::State::BANKRUPT) && (p->state()!=Player::State::LOST);});
}

Market::BidList Session::getRawBids() {
  Market::BidList raws;
  int min_raw_cost = _ruleset->market_raw.at(_market->state()).second;
  for(auto p: _player_pointer_list) {
    if (p->state() == Player::State::READY) {
      if (min_raw_cost<=p->rawBid().requested_cost)
        raws.push_back(p->rawBid());
    }
  }
  return raws;
}

Market::BidList Session::getProductionBids() {
  Market::BidList prods;
  int max_prod_cost = _ruleset->market_production.at(_market->state()).second;
  for(auto p: _player_pointer_list) {
    if (p->state() == Player::State::READY) {
      if (max_prod_cost>=p->productionBid().requested_cost)
        prods.push_back(p->productionBid());
    }
  }
  return prods;
}

bool Session::beginGame() {
  ///@fixme (abby): must check all preconditions, like players count, ruleset initialized, and so on
  _market=std::make_shared<Market>(_ruleset);
  return true;
}
