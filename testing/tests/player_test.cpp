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
  EXPECT_EQ(p._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count);
  p._building_planned = 1;
  p.orderFactories(10);
  EXPECT_EQ(p._factories_to_build.size(), 1);
  EXPECT_EQ(p._factories_to_build.front()->month_when_done, 10 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-Ruleset::DEFAULT.factory_build_cost/2);
  EXPECT_EQ(p._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count);

  // Проверка заказа ещё 10 фабрик, при текущем ходе 15
  p._building_planned = 10;
  p.orderFactories(15);
  EXPECT_EQ(p._factories_to_build.size(), 11);
  EXPECT_EQ(p._factories_to_build.front()->month_when_done, 10 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.back()->month_when_done, 15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-11*Ruleset::DEFAULT.factory_build_cost/2);
  EXPECT_EQ(p._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count);

  // построим одну фабрику
  p.buildFactories(10 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.size(), 10);
  EXPECT_EQ(p._factories_to_build.front()->month_when_done, 15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.back()->month_when_done, 15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-12*Ruleset::DEFAULT.factory_build_cost/2);
  EXPECT_EQ(p._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count + 1);

  // построим остальные
  p.buildFactories(15 + Ruleset::DEFAULT.factory_build_time);
  EXPECT_EQ(p._factories_to_build.size(), 0);
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money-22*Ruleset::DEFAULT.factory_build_cost/2);
  EXPECT_EQ(p._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count + 11);
}

TEST(Player, State) {
  // Проверка изменений состояний без применения действий (производство, ставки, постройки)
  Player p{std::make_shared<Ruleset>(Ruleset::DEFAULT), 42};
  p.updateState(1);
  EXPECT_EQ(p.id(), 42);
  EXPECT_EQ(p.state(), Player::State::THINKING);
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
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money - (Ruleset::DEFAULT.startup_products*Ruleset::DEFAULT.product_store_cost + Ruleset::DEFAULT.startup_raw*Ruleset::DEFAULT.raw_store_cost + p._number_of_working_factories*Ruleset::DEFAULT.factory_cost));
  EXPECT_EQ(p._state, Player::State::THINKING);
  p.updateState(2);
  EXPECT_EQ(p.id(), 42);
  EXPECT_EQ(p.state(), Player::State::THINKING);
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
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money - 2*(Ruleset::DEFAULT.startup_products*Ruleset::DEFAULT.product_store_cost + Ruleset::DEFAULT.startup_raw*Ruleset::DEFAULT.raw_store_cost + p._number_of_working_factories*Ruleset::DEFAULT.factory_cost));
  EXPECT_EQ(p._state, Player::State::THINKING);
  p.updateState(3);
  EXPECT_EQ(p.id(), 42);
  EXPECT_EQ(p.state(), Player::State::BANKRUPT);
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
  EXPECT_EQ(p._cash, Ruleset::DEFAULT.startup_money - 3*(Ruleset::DEFAULT.startup_products*Ruleset::DEFAULT.product_store_cost + Ruleset::DEFAULT.startup_raw*Ruleset::DEFAULT.raw_store_cost + p._number_of_working_factories*Ruleset::DEFAULT.factory_cost));
  EXPECT_EQ(p._state, Player::State::BANKRUPT);

  // Проверка изменений состояний при работе со ставками
  Player p2{std::make_shared<Ruleset>(Ruleset::DEFAULT), 22};
  p2._storage.production_stored = 4;
  p2._current_sell_production_bid.player = p2._id;
  p2._current_sell_production_bid.accepted_quantity = 3;
  p2._current_sell_production_bid.requested_cost = 900;
  p2._current_sell_production_bid.requested_quantity = 3;
  p2._current_buy_raw_bid.player = p2._id;
  p2._current_buy_raw_bid.accepted_quantity = 3;
  p2._current_buy_raw_bid.requested_cost = 1100;
  p2._current_buy_raw_bid.requested_quantity = 3;
  p2._state = Player::State::READY;
  p2.updateState(1);
  EXPECT_EQ(p2.id(), 22);
  EXPECT_EQ(p2.state(), Player::State::THINKING);
  EXPECT_EQ(p2.rawBid().accepted_quantity, 3);
  EXPECT_EQ(p2.rawBid().player, 22);
  EXPECT_EQ(p2.rawBid().requested_cost, 1100);
  EXPECT_EQ(p2.rawBid().requested_quantity, 3);
  EXPECT_EQ(p2.productionBid().accepted_quantity, 3);
  EXPECT_EQ(p2.productionBid().player, 22);
  EXPECT_EQ(p2.productionBid().requested_cost, 900);
  EXPECT_EQ(p2.productionBid().requested_quantity, 3);
  EXPECT_EQ(p2._id, 22);
  EXPECT_EQ(p2._production_planned, 0);
  EXPECT_EQ(p2._building_planned, 0);
  EXPECT_EQ(p2._current_buy_raw_bid.accepted_quantity, 3);
  EXPECT_EQ(p2._current_buy_raw_bid.player, 22);
  EXPECT_EQ(p2._current_buy_raw_bid.requested_cost, 1100);
  EXPECT_EQ(p2._current_buy_raw_bid.requested_quantity, 3);
  EXPECT_EQ(p2._current_sell_production_bid.accepted_quantity, 3);
  EXPECT_EQ(p2._current_sell_production_bid.player, 22);
  EXPECT_EQ(p2._current_sell_production_bid.requested_cost, 900);
  EXPECT_EQ(p2._current_sell_production_bid.requested_quantity, 3);
  EXPECT_EQ(p2._storage.production_stored, 4 - 3);
  EXPECT_EQ(p2._storage.raw_stored, Ruleset::DEFAULT.startup_raw + 3);
  EXPECT_EQ(p2._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count);
  EXPECT_EQ(p2._factories_to_build.size(), 0);
  EXPECT_EQ(p2._cash, Ruleset::DEFAULT.startup_money - ((4-3)*Ruleset::DEFAULT.product_store_cost + (Ruleset::DEFAULT.startup_raw + 3)*Ruleset::DEFAULT.raw_store_cost + p2._number_of_working_factories*Ruleset::DEFAULT.factory_cost) - p2.rawBid().accepted_quantity*p2.rawBid().requested_cost + p2.productionBid().accepted_quantity*p2.productionBid().requested_cost-p2._production_planned*Ruleset::DEFAULT.manufacturing_cost.second);
  EXPECT_EQ(p2._state, Player::State::THINKING);

  Player p3{std::make_shared<Ruleset>(Ruleset::DEFAULT), 32};

  p3._storage.production_stored = 4;
  p3._current_sell_production_bid.player = p3._id;
  p3._current_sell_production_bid.accepted_quantity = 3;
  p3._current_sell_production_bid.requested_cost = 900;
  p3._current_sell_production_bid.requested_quantity = 3;
  p3._current_buy_raw_bid.player = p3._id;
  p3._current_buy_raw_bid.accepted_quantity = 3;
  p3._current_buy_raw_bid.requested_cost = 1100;
  p3._current_buy_raw_bid.requested_quantity = 3;
  p3._state = Player::State::READY;

  int can_produce_cash = p3._cash / p3._ruleset->manufacturing_cost.second;
  int can_produce_raw = p3._storage.raw_stored / p3._ruleset->manufacturing_cost.first;
  p3._production_planned = std::min(can_produce_cash, std::min(can_produce_raw, p3._number_of_working_factories));

  p3.updateState(1);
  EXPECT_EQ(p3.id(), 32);
  EXPECT_EQ(p3.state(), Player::State::THINKING);
  EXPECT_EQ(p3.rawBid().accepted_quantity, 3);
  EXPECT_EQ(p3.rawBid().player, 32);
  EXPECT_EQ(p3.rawBid().requested_cost, 1100);
  EXPECT_EQ(p3.rawBid().requested_quantity, 3);
  EXPECT_EQ(p3.productionBid().accepted_quantity, 3);
  EXPECT_EQ(p3.productionBid().player, 32);
  EXPECT_EQ(p3.productionBid().requested_cost, 900);
  EXPECT_EQ(p3.productionBid().requested_quantity, 3);
  EXPECT_EQ(p3._id, 32);
  EXPECT_EQ(p3._production_planned, 2);
  EXPECT_EQ(p3._building_planned, 0);
  EXPECT_EQ(p3._current_buy_raw_bid.accepted_quantity, 3);
  EXPECT_EQ(p3._current_buy_raw_bid.player, 32);
  EXPECT_EQ(p3._current_buy_raw_bid.requested_cost, 1100);
  EXPECT_EQ(p3._current_buy_raw_bid.requested_quantity, 3);
  EXPECT_EQ(p3._current_sell_production_bid.accepted_quantity, 3);
  EXPECT_EQ(p3._current_sell_production_bid.player, 32);
  EXPECT_EQ(p3._current_sell_production_bid.requested_cost, 900);
  EXPECT_EQ(p3._current_sell_production_bid.requested_quantity, 3);
  EXPECT_EQ(p3._storage.production_stored, 4 - 3/*bid*/ + 2/*production*/);
  EXPECT_EQ(p3._storage.raw_stored, Ruleset::DEFAULT.startup_raw + 3/*bid*/ - 2/*production*/);
  EXPECT_EQ(p3._number_of_working_factories, Ruleset::DEFAULT.startup_factory_count);
  EXPECT_EQ(p3._factories_to_build.size(), 0);
  EXPECT_EQ(p3._cash, Ruleset::DEFAULT.startup_money - ((4 - 3 + 2)*Ruleset::DEFAULT.product_store_cost + (Ruleset::DEFAULT.startup_raw + 3 - 2)*Ruleset::DEFAULT.raw_store_cost + p3._number_of_working_factories*Ruleset::DEFAULT.factory_cost) - p3.rawBid().accepted_quantity*p3.rawBid().requested_cost + p3.productionBid().accepted_quantity*p3.productionBid().requested_cost - p3._production_planned*Ruleset::DEFAULT.manufacturing_cost.second);
  EXPECT_EQ(p3._state, Player::State::THINKING);
}
