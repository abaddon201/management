#ifndef SERVER_INTERNAL_STORAGE_H
#define SERVER_INTERNAL_STORAGE_H

struct Storage {
  Storage() : production_stored{0}, raw_stored{0} {}
  Storage(int prod, int raw) : production_stored{prod}, raw_stored{raw} {}
  ~Storage() {}

  ///@brief Хранящаяся на складе не реализованная продукция
  int production_stored;
  ///@brief Хранящиеся на складе не реализованные материалы
  int raw_stored;
};

#endif //SERVER_INTERNAL_STORAGE_H
