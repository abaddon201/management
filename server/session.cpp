#include "session.h"

bool Session::connectPlayer() {
  if (_state!=State::WAITING_FOR_PLAYERS)
    return false;
  if (_player_pointer_list.size() == _ruleset->_max_players) {
    return false;
  }
  _player_pointer_list.push_back(std::shared_ptr<Player>(new Player()));
  return true;
}

bool Session::disconnectPlayer(int player_id) {
  _player_pointer_list.remove_if([player_id](std::shared_ptr<Player> p) {return p->id() == player_id;});
  if (0 == _player_pointer_list.size()) {
    _state = State::FINISHED;
    return true;
  }
  return false;
}

void Session::makeTurn() {
  doPlayers();
  ///@todo(abby): найти банкротов...
  _market->changeState();
}

void Session::doPlayers() {
  ///@todo: (abby) : реализовать алгоритм
}
