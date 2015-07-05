#ifndef SESSION_H
#define SESSION_H

#include "market.h"
#include "player.h"
#include <vector>

namespace management {
namespace server {

class Session {
  Market _market;
  std::vector<Player> _players;
  std::string _id;
  std::string _pass;
  int _nturn;
public:
  Session();
};

}
}

#endif // SESSION_H
