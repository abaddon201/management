#include "player.h"

void Player::updateState(int turn, Bid raw_bid, Bid production_bid) {
  manufacture();
  buildFactories(turn);
  _current_buy_raw_bid = raw_bid;
  _current_sell_production_bid = production_bid;
  processBids();
  payBills();
  if (_cash < 0) {
    _state = State::BANKRUPT;
  }
  _state = State::THINKING;
}

void Player::manufacture() {
  ///@fixme (abby): Игрок может указывать кол-во, сколько произвести
  int can_produce_cash = _cash / _ruleset->manufacturing_cost.second;
  int can_produce_raw = _storage.raw_stored / _ruleset->manufacturing_cost.first;
  int count = std::min(can_produce_cash, std::min(can_produce_raw, _number_of_working_factories));
  _storage.raw_stored -= _ruleset->manufacturing_cost.first * count;
  _cash -= _ruleset->manufacturing_cost.second * count;
  _storage.production_stored += count;
}

void Player::buildFactories(const int turn) {
  if (turn == _factories_to_build.front()->month_when_done) {
    _number_of_working_factories++;
    _factories_to_build.pop();
    _cash -= _ruleset->factory_build_cost / 2;
  }
}

void Player::processBids() {
  _cash -= _current_buy_raw_bid.requested_cost * _current_buy_raw_bid.accepted_quantity;
  _cash += _current_sell_production_bid.requested_cost * _current_sell_production_bid.accepted_quantity;
}

void Player::payBills() {
  _cash -= _storage.production_stored * _ruleset->product_cost;
  _cash -= _storage.raw_stored * _ruleset->raw_cost;
  _cash -= _number_of_working_factories * _ruleset->factory_cost;
}
