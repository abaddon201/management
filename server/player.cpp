#include "player.h"

void Player::updateState(Bid raw_bid, Bid production_bid) {
  manufacture();
  buildFactories();
  _current_buy_raw_bid = raw_bid;
  _current_sell_production_bid = production_bid;
  processBids();
  payBills();
}

void Player::manufacture() {
  ///@todo (abby): to be defined
}

void Player::buildFactories() {
  ///@todo (abby): to be defined
}

void Player::processBids() {
  ///@todo (abby): to be defined
}

void Player::payBills() {
  ///@todo (abby): to be defined
}
