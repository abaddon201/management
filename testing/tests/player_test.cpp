#include "gtest/gtest.h"
#include "session.h"

// Проверка создания игроков
TEST(Player, CreatePlayers) {
  // Проверка создания игрока по правилам по умолчанию
  Player p{std::make_shared<Ruleset>(Ruleset::DEFAULT), 42};
  EXPECT_EQ(p.id(), 42);
  EXPECT_EQ(p.state(), Player::State::LOGGED_IN);
  EXPECT_EQ(p.rawBid().accepted_quantity, 0);
  EXPECT_EQ(p.rawBid().player, 0);
  EXPECT_EQ(p.rawBid().requested_cost, 0);
  EXPECT_EQ(p.rawBid().requested_quantity, 0);
  EXPECT_EQ(p.productionBid().accepted_quantity, 0);
  EXPECT_EQ(p.productionBid().player, 0);
  EXPECT_EQ(p.productionBid().requested_cost, 0);
  EXPECT_EQ(p.productionBid().requested_quantity, 0);
  EXPECT_EQ(p._id, 42);
  EXPECT_EQ(p._production_planned, 0);
  EXPECT_EQ(p._building_planned, 0);
  EXPECT_EQ(p._current_buy_raw_bid.accepted_quantity, 0);
  EXPECT_EQ(p._current_buy_raw_bid.player, 0);
  EXPECT_EQ(p._current_buy_raw_bid.requested_cost, 0);
  EXPECT_EQ(p._current_buy_raw_bid.requested_quantity, 0);
  EXPECT_EQ(p._current_sell_production_bid.accepted_quantity, 0);
  EXPECT_EQ(p._current_sell_production_bid.player, 0);
  EXPECT_EQ(p._current_sell_production_bid.requested_cost, 0);
  EXPECT_EQ(p._current_sell_production_bid.requested_quantity, 0);
  EXPECT_EQ(p._storage.production_stored, Ruleset::DEFAULT.startup_products);
  EXPECT_EQ(p._storage.raw_stored, Ruleset::DEFAULT.startup_raw);
  EXPECT_EQ(p._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count);
  EXPECT_EQ(p._factories_to_build.size(), 0);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money);
  EXPECT_EQ(p._state, Player::State::LOGGED_IN);
}

TEST(Player, Factories) {
  Player p{std::make_shared<Ruleset>(Ruleset::DEFAULT), 42};
  // Проверка заказа 1 фабрики, при текущем ходе 10
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money);
  EXPECT_EQ(p._factories_to_build.size(), 0);
  p._building_planned = 1;
  p.orderFactories(10);
  EXPECT_EQ(p._factories_to_build.size(), 1);
  EXPECT_EQ(p._factories_to_build.front()->month_when_done, 10 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-Ruleset::DEFAULT.factory_build_cost/2);

  // Проверка заказа ещё 10 фабрик, при текущем ходе 15
  p._building_planned = 10;
  p.orderFactories(15);
  EXPECT_EQ(p._factories_to_build.size(), 11);
  EXPECT_EQ(p._factories_to_build.front()->month_when_done, 10 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.back()->month_when_done, 15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-11*Ruleset::DEFAULT.factory_build_cost/2);

  // построим одну фабрику
  p.buildFactories(10 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.size(), 10);
  EXPECT_EQ(p._factories_to_build.front()->month_when_done, 15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.back()->month_when_done, 15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-12*Ruleset::DEFAULT.factory_build_cost/2);

  // построим остальные
  p.buildFactories(15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.size(), 0);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-22*Ruleset::DEFAULT.factory_build_cost/2);
}
