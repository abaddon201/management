#ifndef  SERVER_INTERNAL_FACTORY_H
#define SERVER_INTERNAL_FACTORY_H

struct Factory {
  Factory(int turn): month_when_done{turn} {}
  ~Factory() {}

  ///@brief В каком месяце фабрика будет построена
  int month_when_done;
};

#endif //SERVER_INTERNAL_FACTORY_H
