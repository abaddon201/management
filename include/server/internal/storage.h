#ifndef SERVER_INTERNAL_STORAGE_H
#define SERVER_INTERNAL_STORAGE_H

struct Storage {
  Storage() {}
  ~Storage() {}

  ///@brief Хранящаяся на складе не реализованная продукция
  int production_stored;
  ///@brief Хранящиеся на складе не реализованные материалы
  int raw_stored;
};

#endif //SERVER_INTERNAL_STORAGE_H
