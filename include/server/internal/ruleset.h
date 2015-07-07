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
      _turn_timeout{tt},
      _factory_cost{fc}, _raw_cost{rc}, _product_cost{pc},
      _manufacturing_cost{mc},
      _money{m}, _factory_build_time{fbt}, _startup_raw{sr}, _startup_products{sp}, _startup_factory_count{sfc}, _market_state{ms},
      _market_state_matrix{msm}, _market_raw{mr}, _market_production{mp} {};
  ~Ruleset() {};
  ///@brief Ограничение времени на ход в секундах. Если отрицательное - время не ограничено
  int _turn_timeout;
  ///@brief Стоимость содержания фабрики
  int _factory_cost;
  ///@brief Стоимость сырья оставшегося на складе
  int _raw_cost;
  ///@brief Стоимость продукции оставшейся на складе
  int _product_cost;
  ///@brief Стоимость производства изделия (кол-во сырья, деньги)
  ManufacturingCost _manufacturing_cost;
  ///@brief Первоначальный капитал
  int _money;
  ///@brief Время постройки фабрики
  int _factory_build_time;
  ///@brief Кол-во материала на старте
  int _startup_raw;
  ///@brief Кол-во продукции на старте
  int _startup_products;
  ///@brief Кол-во фабрик на старте
  int _startup_factory_count;
  ///@brief Состояние рынка на старте
  int _market_state;
  ///@brief Таблица вероятностей перехода состояний рынка
  std::vector<std::vector<double>> _market_state_matrix;
  ///@brief Таблица лимитов (стоимости) сырья, в зависимости от состояния рынка
  std::vector<MarketParam> _market_raw;
  ///@brief Таблица лимитов (стоимости) продукции, в зависимости от состояния рынка
  std::vector<MarketParam> _market_production;
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
