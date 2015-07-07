#include "session.h"

void Session::makeTurn() {
  _market->doPlayers(_player_pointer_list);
  ///@todo(abby): найти банкротов...
  _market->changeState();
}
