#include "gtest/gtest.h"
#include "session.h"

// Проверка подключения игроков
TEST(Session, ConnectPlayers) {
  std::shared_ptr<Ruleset> rules{new Ruleset(Ruleset::DEFAULT)};
  Session s={42, rules};

  // Проверить, что сессия отбрасывает добавление игроков, при правилах по умолчанию
  //
  // <TechnicalDetails>
  //
  // Максимальное количество игроков в правилах по умолчанию - 4. Соотв. при добавлении 5 - го
  // должны получить ошибку
  //
  // </TechnicalDetails>
  bool res=s.connectPlayer(111);
  EXPECT_TRUE(res);
  res=s.connectPlayer(121);
  EXPECT_TRUE(res);
  res=s.connectPlayer(131);
  EXPECT_TRUE(res);
  res=s.connectPlayer(141);
  EXPECT_TRUE(res);
  res=s.connectPlayer(151);
  EXPECT_FALSE(res);

  // Проверить, что сессия отбрасывает отключение игроков, при правилах по умолчанию
  //
  // <TechnicalDetails>
  //
  // При удалении последнего игрока ф-ция возвращает true, во всех остальных случаях - false
  // должны получить ошибку
  //
  // </TechnicalDetails>
  res=s.disconnectPlayer(111);
  EXPECT_FALSE(res);
  res=s.disconnectPlayer(121);
  EXPECT_FALSE(res);
  res=s.disconnectPlayer(131);
  EXPECT_FALSE(res);
  res=s.disconnectPlayer(141);
  EXPECT_TRUE(res);
  res=s.disconnectPlayer(151);
  EXPECT_TRUE(res);


  Session s2={42, rules};
  // Проверить, что сессия отбрасывает отключение игроков не в порядке их подключения
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  res=s2.connectPlayer(111);
  EXPECT_TRUE(res);
  res=s2.connectPlayer(121);
  EXPECT_TRUE(res);
  res=s2.connectPlayer(131);
  EXPECT_TRUE(res);
  res=s2.connectPlayer(141);
  EXPECT_TRUE(res);
  res=s2.connectPlayer(151);
  EXPECT_FALSE(res);
  res=s2.disconnectPlayer(131);
  EXPECT_FALSE(res);
  res=s2.disconnectPlayer(141);
  EXPECT_FALSE(res);
  res=s2.disconnectPlayer(151);
  EXPECT_FALSE(res);
  res=s2.disconnectPlayer(121);
  EXPECT_FALSE(res);
  res=s2.disconnectPlayer(111);
  EXPECT_TRUE(res);



  std::shared_ptr<Ruleset> rules2{new Ruleset(Ruleset::DEFAULT)};
  Session s3={42, rules2};
  rules2->max_players=5;
  // Проверить, что сессия отбрасывает отключение игроков не в порядке их подключения
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  res=s3.connectPlayer(111);
  EXPECT_TRUE(res);
  res=s3.connectPlayer(121);
  EXPECT_TRUE(res);
  res=s3.connectPlayer(131);
  EXPECT_TRUE(res);
  res=s3.connectPlayer(141);
  EXPECT_TRUE(res);
  res=s3.connectPlayer(151);
  EXPECT_TRUE(res);
  res=s3.connectPlayer(161);
  EXPECT_FALSE(res);
  res=s3.disconnectPlayer(131);
  EXPECT_FALSE(res);
  res=s3.disconnectPlayer(141);
  EXPECT_FALSE(res);
  res=s3.disconnectPlayer(151);
  EXPECT_FALSE(res);
  res=s3.disconnectPlayer(121);
  EXPECT_FALSE(res);
  res=s3.disconnectPlayer(111);
  EXPECT_TRUE(res);
}

// Проверка обработки рынка
TEST(Session, ProcessBids) {
  std::shared_ptr<Ruleset> rules{new Ruleset(Ruleset::DEFAULT)};
  Session s={422, rules};

  // Проверить, что сессия отбрасывает ставки, которые не соотв. правилам
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  bool res=s.connectPlayer(111);
  EXPECT_TRUE(res);
  res=s.connectPlayer(121);
  EXPECT_TRUE(res);
  res=s.connectPlayer(131);
  EXPECT_TRUE(res);
  res=s.connectPlayer(141);
  EXPECT_TRUE(res);
  Player::List::iterator it = s._player_pointer_list.begin();
  // 111
  (*it)->_current_sell_production_bid.player = (*it)->_id;
  (*it)->_current_sell_production_bid.accepted_quantity = 0;
  (*it)->_current_sell_production_bid.requested_cost = 1000;
  (*it)->_current_sell_production_bid.requested_quantity = 3;
  (*it)->_state = Player::State::READY;
  ++it;
  // 121
  (*it)->_current_sell_production_bid.player = (*it)->_id;
  (*it)->_current_sell_production_bid.accepted_quantity = 0;
  (*it)->_current_sell_production_bid.requested_cost = 10000;
  (*it)->_current_sell_production_bid.requested_quantity = 3;
  (*it)->_state = Player::State::READY;
  ++it;
  // 131
  (*it)->_current_sell_production_bid.player = (*it)->_id;
  (*it)->_current_sell_production_bid.accepted_quantity = 0;
  (*it)->_current_sell_production_bid.requested_cost = 1000;
  (*it)->_current_sell_production_bid.requested_quantity = 3;
  (*it)->_state = Player::State::READY;
  ++it;
  // 141
  (*it)->_current_sell_production_bid.player = (*it)->_id;
  (*it)->_current_sell_production_bid.accepted_quantity = 0;
  (*it)->_current_sell_production_bid.requested_cost = 10000;
  (*it)->_current_sell_production_bid.requested_quantity = 3;
  (*it)->_state = Player::State::READY;

  res = s.beginGame();
  EXPECT_TRUE(res);
  s.makeTurn();
  it = s._player_pointer_list.begin();
  // 111
  EXPECT_EQ((*it)->_current_sell_production_bid.accepted_quantity, 3);
  ++it;
  // 121
  EXPECT_EQ((*it)->_current_sell_production_bid.accepted_quantity, 0);
  ++it;
  // 131
  EXPECT_EQ((*it)->_current_sell_production_bid.accepted_quantity, 3);
  ++it;
  // 141
  EXPECT_EQ((*it)->_current_sell_production_bid.accepted_quantity, 0);

}
