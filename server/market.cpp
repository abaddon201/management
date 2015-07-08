#include "market.h"
#include "session.h"

void Market::changeState() {
  int pos = 0;
  for(double v:_session->ruleset()->_market_state_matrix.at(_state)) {
    double rnd = (double)std::rand()/(double)RAND_MAX;
    if (rnd<v) {
      _state = pos;
      return;
    }
  }
}
