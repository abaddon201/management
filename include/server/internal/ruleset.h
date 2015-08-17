#ifndef SERVER_INTERNAL_RULESET_H
#define SERVER_INTERNAL_RULESET_H

#include <utility>
#include <vector>

struct Ruleset {
  using ManufacturingCost = std::pair<int,int>;
  ///@brief Параметр рынка для описания сырья/продукции.
  /// формат: кол-во (коэффициент, на который домножается кол-во необанкротившихся игроков), цена
  using MarketParam = std::pair<double,int>;

  Ruleset();
  Ruleset(int tt, unsigned mpl, int fc, int rc, int pc, ManufacturingCost mc, int m, int fbt, int fbc, int sr, int sp, int sfc, int ms,
          std::vector<std::vector<double>> msm, std::vector<MarketParam> mr, std::vector<MarketParam> mp) :
      turn_timeout{tt}, max_players{mpl},
      factory_cost{fc}, raw_store_cost{rc}, product_store_cost{pc},
      manufacturing_cost{mc},
      startup_money{m}, factory_build_time{fbt}, factory_build_cost{fbc},
      startup_raw{sr}, startup_products{sp}, startup_factory_count{sfc}, market_state{ms},
      market_state_matrix{msm}, market_raw{mr}, market_production{mp} {};
  ~Ruleset() {};

  ///@brief Ограничение времени на ход в секундах. Если отрицательное - время не ограничено
  int turn_timeout;
  ///@brief Максимальное кол-во игроков
  unsigned max_players;
  ///@brief Стоимость содержания фабрики
  int factory_cost;
  ///@brief Стоимость сырья оставшегося на складе
  int raw_store_cost;
  ///@brief Стоимость продукции оставшейся на складе
  int product_store_cost;
  ///@brief Стоимость производства изделия (кол-во сырья, деньги)
  ManufacturingCost manufacturing_cost;
  ///@brief Первоначальный капитал
  int startup_money;
  ///@brief Время постройки фабрики
  int factory_build_time;
  ///@brief Стоимость постройки фабрики (чётное)
  int factory_build_cost;
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

  ///@brief Набор правил поумолчанию
  static const Ruleset DEFAULT;
};

#endif //SERVER_INTERNAL_RULESET_H
