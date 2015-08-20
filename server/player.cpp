#include "internal/player.h"

void Player::updateState(int turn) {
  orderFactories(turn); ///<@brief деньги за заказ фабрики списываются сразу
  manufacture();
  buildFactories(turn);
  processBids();
  payBills();
  if (_cash < 0) {
    _state = State::BANKRUPT;
  } else {
    _state = State::THINKING;
  }
}

void Player::orderFactories(int turn) {
  _cash -= _building_planned * (_ruleset->factory_build_cost / 2);
  for (int i = 0; i < _building_planned; ++i) {
      _factories_to_build.push(std::make_unique<Factory>(turn + _ruleset->factory_build_time));
  }
}

void Player::manufacture() {
  _storage.raw_stored -= _ruleset->manufacturing_cost.first * _production_planned;
  _cash -= _ruleset->manufacturing_cost.second * _production_planned;
  _storage.production_stored += _production_planned;
}

void Player::buildFactories(const int turn) {
  while ((_factories_to_build.size() != 0) && turn == _factories_to_build.front()->month_when_done) {
    _number_of_working_factories++;
    _factories_to_build.pop();
    _cash -= _ruleset->factory_build_cost / 2;
  }
}

void Player::processBids() {
  _cash -= _current_buy_raw_bid.requested_cost * _current_buy_raw_bid.accepted_quantity;
  _storage.raw_stored += _current_buy_raw_bid.accepted_quantity;
  _cash += _current_sell_production_bid.requested_cost * _current_sell_production_bid.accepted_quantity;
  _storage.production_stored -= _current_sell_production_bid.accepted_quantity;
}

void Player::payBills() {
  _cash -= _storage.production_stored * _ruleset->product_store_cost;
  _cash -= _storage.raw_stored * _ruleset->raw_store_cost;
  _cash -= _number_of_working_factories * _ruleset->factory_cost;
}
