#ifndef MARKET_H
#define MARKET_H

#include <vector>

namespace management {
namespace server {

class Market {
  int _state;
  /*const */std::vector<std::vector<float> > _stateMatrix/* = {{1,2,3,4,5}, {6,7,8,9,10}}*/;
public:
  Market();
  void nextState();
};

}
}

#endif // MARKET_H
