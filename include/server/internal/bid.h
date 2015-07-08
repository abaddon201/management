#ifndef BID
#define BID

class Bid {
public:
private:
  int _requested_cost;
  int _requested_quantity;
  int _accepted_quantity;
  Player::Id _player;
};

#endif // BID

