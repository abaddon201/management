#include "gtest/gtest.h"
#include "market.h"

// Tests the market state.
TEST(Market, DefaultState) {
  Ruleset * r = new Ruleset(Ruleset::DEFAULT);
  Market s={std::shared_ptr<Ruleset>(r)};

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
  int states[6]={};
#define NUM_TESTS 1000000
#define STATE_TOLERANCE 0.1
  for (int i=0;i<NUM_TESTS;++i) {
    s._state=0;
    s.changeState();
    states[s._state]++;
  }
  EXPECT_GE(NUM_TESTS*(r->market_state_matrix[0][0]+STATE_TOLERANCE), states[0])<<"States are="<<states[0]<<","<<states[1]<<","<<states[2]<<","<<states[3]<<","<<states[4]<<","<<states[5];
}

TEST(Market, ProcessBids) {
  Ruleset * r = new Ruleset(Ruleset::DEFAULT);
  Market s={std::shared_ptr<Ruleset>(r)};

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
