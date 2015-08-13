#include "gtest/gtest.h"
#include "session.h"

// Проверка подключения игроков
TEST(Session, ConnectPlayers) {
  Ruleset * r = new Ruleset(Ruleset::DEFAULT);
  Session s={42, std::shared_ptr<Ruleset>(r)};

  bool res=s.connectPlayer(111);
  EXPECT_TRUE(res);
  res=s.connectPlayer(121);
  EXPECT_TRUE(res);
  res=s.connectPlayer(131);
  EXPECT_TRUE(res);
  res=s.connectPlayer(141);
  EXPECT_TRUE(res);
  res=s.connectPlayer(151);
  EXPECT_TRUE(res);
}

// Проверка обработки рынка
TEST(Session, ProcessBids) {
  Ruleset * r = new Ruleset(Ruleset::DEFAULT);
  Session s={42, std::shared_ptr<Ruleset>(r)};

  // Проверить, что сессия отбрасывает ставки, которые не соотв. правилам
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  /*allequal_raw_bids.clear();
  for(int i=0;i<4;i++) {
    bid.player=(i+1)*10;
    bid.accepted_quantity=0;
    bid.requested_cost=1000;
    bid.requested_quantity=3;
    allequal_raw_bids.push_back(bid);
  }
  allequal_production_bids.clear();
  for(int i=0;i<4;i++) {
    bid.player=(i+1)*10;
    bid.accepted_quantity=0;
    bid.requested_cost=1000;
    bid.requested_quantity=3;
    allequal_production_bids.push_back(bid);
  }
  s.processBids(4, allequal_raw_bids, allequal_production_bids);
  EXPECT_EQ(allequal_raw_bids.at(0).accepted_quantity, 3);
  EXPECT_EQ(allequal_raw_bids.at(1).accepted_quantity, 3);
  EXPECT_EQ(allequal_raw_bids.at(2).accepted_quantity, 2);
  EXPECT_EQ(allequal_raw_bids.at(3).accepted_quantity, 0);

  bool raw_randomized = (allequal_raw_bids.at(0).player!=10) || (allequal_raw_bids.at(1).player!=20) || (allequal_raw_bids.at(2).player!=30) || (allequal_raw_bids.at(3).player!=40);
  EXPECT_TRUE(raw_randomized)
      << " player 0 id="<<allequal_raw_bids.at(0).player
      << " player 1 id="<<allequal_raw_bids.at(1).player
      << " player 2 id="<<allequal_raw_bids.at(2).player
      << " player 3 id="<<allequal_raw_bids.at(3).player;

  EXPECT_EQ(allequal_production_bids.at(0).accepted_quantity, 3);
  EXPECT_EQ(allequal_production_bids.at(1).accepted_quantity, 3);
  EXPECT_EQ(allequal_production_bids.at(2).accepted_quantity, 2);
  EXPECT_EQ(allequal_production_bids.at(3).accepted_quantity, 0);

  bool prod_randomized = (allequal_production_bids.at(0).player!=10) || (allequal_production_bids.at(1).player!=20) || (allequal_production_bids.at(2).player!=30) || (allequal_production_bids.at(3).player!=40);
  EXPECT_TRUE(prod_randomized)
      << " player 0 id="<<allequal_production_bids.at(0).player
      << " player 1 id="<<allequal_production_bids.at(1).player
      << " player 2 id="<<allequal_production_bids.at(2).player
      << " player 3 id="<<allequal_production_bids.at(3).player;*/
}
