#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace management {
namespace server {

class Player {
  int _factories;
  bool _ready;
  int _cash;
  int _raw;
  int _products;
  int _bid_sell;
  int _bid_buy;
  int _manufacturings;
  std::string _name;
  std::string _pass;
public:
  Player();
};

}
}

#endif // PLAYER_H
