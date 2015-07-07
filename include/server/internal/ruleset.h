#ifndef SERVER_INTERNAL_RULESET_H
#define SERVER_INTERNAL_RULESET_H

#include <utility>
#include <vector>

class Ruleset {
  using ManufacturingCost = std::pair<int,int>;
  ///@brief Параметр рынка для описания сырья/продукции.
  /// формат: кол-во (коэффициент, на который домножается кол-во необанкротившихся игроков), цена
  using MarketParam = std::pair<double,int>;
public:
  Ruleset();
  Ruleset(int tt, int fc, int rc, int pc, ManufacturingCost mc, int m, int fbt, int sr, int sp, int sfc, int ms,
          std::vector<std::vector<double>> msm, std::vector<MarketParam> mr, std::vector<MarketParam> mp) :
      turn_timeout{tt},
      factory_cost{fc}, raw_cost{rc}, product_cost{pc},
      manufacturing_cost{mc},
      money{m}, factory_build_time{fbt}, startup_raw{sr}, startup_products{sp}, startup_factory_count{sfc}, market_state{ms},
      market_state_matrix{msm}, market_raw{mr}, market_production{mp} {};
  ~Ruleset() {};
  ///@brief Ограничение времени на ход в секундах. Если отрицательное - время не ограничено
  int turn_timeout;
  ///@brief Стоимость содержания фабрики
  int factory_cost;
  ///@brief Стоимость сырья оставшегося на складе
  int raw_cost;
  ///@brief Стоимость продукции оставшейся на складе
  int product_cost;
  ///@brief Стоимость производства изделия (кол-во сырья, деньги)
  ManufacturingCost _manufacturing_cost;
  ///@brief Первоначальный капитал
  int money;
  ///@brief Время постройки фабрики
  int factory_build_time;
  ///@brief Кол-во материала на старте
  int startup_raw;
  ///@brief Кол-во продукции на старте
  int startup_products;
  ///@brief Кол-во фабрик на старте
  int startup_factory_count;
  ///@brief Состояние рынка на старте
  int market_state;
  ///@brief Таблица вероятностей перехода состояний рынка
  std::vector<std::vector<double>> market_state_matrix;
  ///@brief Таблица лимитов (стоимости) сырья, в зависимости от состояния рынка
  std::vector<MarketParam> market_raw;
  ///@brief Таблица лимитов (стоимости) продукции, в зависимости от состояния рынка
  std::vector<MarketParam> market_production;
};

static const Ruleset DEFAULT_RULESET {
  -1,
  1000, 300, 500,
  {1, 2000},
  10000, 5,
  4, 2, 2,
  3,
  {{1./3., 1./3., 1./6., 1./12., 1./12.},
   {1./4., 1./3., 1./4., 1./12., 1./12.},
   {1./12., 1./4., 1./3., 1./4., 1./12.},
   {1./12., 1./12., 1./4., 1./3., 1./4.},
   {1./12., 1./12., 1./6., 1./3., 1./3.}},
  {{1., 800},
   {1.5, 650},
   {2., 500},
   {2.5, 400},
   {3., 300}},
  {{3., 6500},
   {2.5, 6000},
   {2., 5500},
   {1.5, 5000},
   {1, 4500}}
};

#endif //SERVER_INTERNAL_RULESET_H
