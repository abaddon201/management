#include "gtest/gtest.h"
#include "market.h"

// Проверка правильности обработки рынка
TEST(Market, DefaultState) {
  std::shared_ptr<Ruleset> rules{new Ruleset(Ruleset::DEFAULT)};
  Market s={rules};

  // check state is Ruleset::DEFAULT.market_state
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  EXPECT_EQ(Ruleset::DEFAULT.market_state, s._state);

  // Проверить, что состояние меняется в соотв. с таблицей вероятностей
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  int states[5];
#define NUM_TESTS 1000000
#define STATE_TOLERANCE 0.1

  for (int st=0;st<5;st++) {
    for (int i=0;i<5;i++) {
      states[i]=0;
    }
    for (int i=0;i<NUM_TESTS;++i) {
      s._state=st;
      s.changeState();
      states[s._state]++;
    }
    for (int i=0;i<5;i++)
      EXPECT_GE(NUM_TESTS*(rules->market_state_matrix[st][i]+STATE_TOLERANCE), states[i])<<"States are="<<states[0]<<","<<states[1]<<","<<states[2]<<","<<states[3]<<","<<states[4]<<","<<states[5];
  }
}

TEST(Market, ProcessBids) {
  std::shared_ptr<Ruleset> rules{new Ruleset(Ruleset::DEFAULT)};
  Market s={rules};

  // Проверить, что одинаковые ставки обрабатываются правильно при достаточных кол-вах
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  Player::Bid bid;
  Market::BidList allequal_raw_bids;
  for(int i=0;i<4;i++) {
    bid.player=(i+1)*10;
    bid.accepted_quantity=0;
    bid.requested_cost=1000;
    bid.requested_quantity=1;
    allequal_raw_bids.push_back(bid);
  }
  Market::BidList allequal_production_bids;
  for(int i=0;i<4;i++) {
    bid.player=(i+1)*10;
    bid.accepted_quantity=0;
    bid.requested_cost=1000;
    bid.requested_quantity=1;
    allequal_production_bids.push_back(bid);
  }
  s.processBids(4, allequal_raw_bids, allequal_production_bids);

  for (int i=0;i<4;i++) {
    EXPECT_EQ(allequal_raw_bids.at(i).accepted_quantity, allequal_raw_bids.at(i).requested_quantity) << "wrong player at "<<i;
    EXPECT_EQ(allequal_production_bids.at(i).accepted_quantity, allequal_production_bids.at(i).requested_quantity) << "wrong player at "<<i;
  }




  // Проверить, что одинаковые ставки обрабатываются правильно при недостаточных кол-вах
  //
  // <TechnicalDetails>
  //
  // </TechnicalDetails>
  allequal_raw_bids.clear();
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
      << " player 3 id="<<allequal_production_bids.at(3).player;
}
