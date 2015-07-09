#include "session.h"

#include <algorithm>

bool Session::connectPlayer(std::string name, std::string pass) {
  if (_state!=State::WAITING_FOR_PLAYERS)
    return false;
  if (_player_pointer_list.size() == _ruleset->_max_players) {
    return false;
  }
  _player_pointer_list.push_back(std::shared_ptr<Player>(new Player(_ruleset, name, pass)));
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
  Market::BidQueue raw_bids = getRawBids();
  Market::BidQueue production_bids = getProductionBids();

  _market->makeTurn(getPlayersInGame(), raw_bids, production_bids);
  for(auto p: _player_pointer_list) {
    Player::Id id = p->id();
    Market::BidQueue::const_iterator raw = std::find_if(raw_bids.cbegin(), raw_bids.cend(), [id] (const Player::Bid& bid) {return bid.player == id;});
    Market::BidQueue::const_iterator prod = std::find_if(production_bids.cbegin(), production_bids.cend(), [id] (const Player::Bid& bid) {return bid.player == id;});

    p->updateState(*raw, *prod);
  }
}

int Session::getPlayersInGame() {
  return std::count_if(_player_pointer_list.begin(), _player_pointer_list.end(), [](std::shared_ptr<Player> p) { return (p->state()!=Player::State::BANKRUPT) && (p->state()!=Player::State::LOST);});
}

Market::BidQueue Session::getRawBids() {
  Market::BidQueue raws;
  for(auto p: _player_pointer_list) {
    if (p->state() == Player::State::READY) {
      raws.push_back(p->rawBid());
    }
  }
  return raws;
}

Market::BidQueue Session::getProductionBids() {
  Market::BidQueue prods;
  for(auto p: _player_pointer_list) {
    if (p->state() == Player::State::READY) {
      prods.push_back(p->productionBid());
    }
  }
  return prods;
}
