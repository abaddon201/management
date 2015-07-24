#include <algorithm>

#include "internal/session.h"

Session::Session(int id): Session(id, std::make_shared<Ruleset>(Ruleset::DEFAULT), std::string(""), -1) {}

Session::Session(int id, std::shared_ptr<Ruleset> rules): Session(id, rules, std::string(""), -1)  {}

Session::Session(int id, std::string passwd):
  Session(id, std::make_shared<Ruleset>(Ruleset::DEFAULT), passwd, -1) {}

Session::Session(int id, std::string passwd, int player_id):
  Session(id, std::make_shared<Ruleset>(Ruleset::DEFAULT), passwd, player_id) {}

Session::Session(int id, std::shared_ptr<Ruleset> rules, std::string passwd):
  Session(id, rules, passwd, -1) {}

Session::Session(int id, std::shared_ptr<Ruleset> rules, std::string passwd, int player_id):
  _id{id}, _password{passwd}, _ruleset{rules} {
  if (player_id >= 0) {
    connectPlayer(player_id);
  }
}

Session::~Session() {
}

bool Session::connectPlayer(int id) {
  LockObj lk {&_session_mutex};
  if (_state!= State::WAITING_FOR_PLAYERS)
    return false;
  _player_pointer_list.push_back(std::shared_ptr<Player>(new Player(_ruleset, static_cast<Player::Id>(id))));
  if (_player_pointer_list.size() == _ruleset->max_players) {
    _state = State::PLAYING;
  }
  return true;
}

bool Session::disconnectPlayer(Player::Id player_id) {
  LockObj lk {&_session_mutex};
  _player_pointer_list.remove_if([player_id](std::shared_ptr<Player> p) {return p->id() == player_id;});
  if (_player_pointer_list.empty()) {
    _state = State::FINISHED;
    return true;
  }
  return false;
}

void Session::makeTurn() {
  LockObj lk {&_session_mutex};
  Market::BidList raw_bids = getRawBids();
  Market::BidList production_bids = getProductionBids();

  _market->makeTurn(getPlayersInGame(), raw_bids, production_bids);
  for(auto p: _player_pointer_list) {
    Player::Id id = p->id();
    Market::BidList::const_iterator raw = std::find_if(raw_bids.cbegin(), raw_bids.cend(),
                                                       [id] (const Player::Bid& bid) {return bid.player == id;});
    Market::BidList::const_iterator prod = std::find_if(production_bids.cbegin(), production_bids.cend(),
                                                        [id] (const Player::Bid& bid) {return bid.player == id;});

    p->updateState(_turn_number, *raw, *prod);
  }
}

int Session::getPlayersInGame() {
  return std::count_if(_player_pointer_list.begin(), _player_pointer_list.end(),
                       [](std::shared_ptr<Player> p) { return (p->state()!=Player::State::BANKRUPT) && (p->state()!=Player::State::LOST);});
}

void Session::checkIfNeedMakeTurn() {
  if (std::all_of(_player_pointer_list.begin(), _player_pointer_list.end(),
                  [](std::shared_ptr<Player> sp){ return sp->state() == Player::State::READY; })) {
    makeTurn();
  }
}

Market::BidList Session::getRawBids() {
  Market::BidList raws;
  for(auto p: _player_pointer_list) {
    if (p->state() == Player::State::READY) {
      raws.push_back(p->rawBid());
    }
  }
  return raws;
}

Market::BidList Session::getProductionBids() {
  Market::BidList prods;
  for(auto p: _player_pointer_list) {
    if (p->state() == Player::State::READY) {
      prods.push_back(p->productionBid());
    }
  }
  return prods;
}

bool Session::setPlayerTurn(int player_id, int build_orders, int production_orders, const Player::Bid &raw, const Player::Bid &prod) {
  LockObj lk {&_session_mutex};
  auto player_it = std::find_if(_player_pointer_list.begin(), _player_pointer_list.end(),
                                [player_id](std::shared_ptr<Player> pl_ptr) {return player_id == pl_ptr->id();});
  if (player_it != _player_pointer_list.end()) {
    (*player_it)->setRawBid(raw);
    (*player_it)->setProductionBid(prod);
    (*player_it)->setProductionPlanned(production_orders);
    (*player_it)->setBuildingPlanned(build_orders);
    (*player_it)->setState(Player::State::READY);
    checkIfNeedMakeTurn();
    return true;
  } else {
    return false;
  }
}
