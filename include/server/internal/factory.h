#ifndef  SERVER_INTERNAL_FACTORY_H
#define SERVER_INTERNAL_FACTORY_H

class Factory {
public:
  Factory() {}
  ~Factory() {}

private:
  ///@brief В каком месяце фабрика будет построена
  int _month_when_done;
};

#endif //SERVER_INTERNAL_FACTORY_H
