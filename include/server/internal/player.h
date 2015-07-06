#ifndef SERVER_INTERNAL_PLAYER_H
#define SERVER_INTERNAL_PLAYER_H

#include <utility>
#include <memory>
#include <string>
#include <list>

#include "server/internal/storage.h"
#include "server/internal/factory.h"

class Player
{
	// Bid. Это пара целых чисел, первое из которых это количество единиц, а второе - цена.
	// TODO: (tolstoy) Вообще стоит создание псевдонима вынести отсюда, поскольку оно будет нужно не только тут
	using Bid = pair<int,int>;
	using f_iterator = std::list<std::shared_ptr<Factory>>::iterator;
public:
	Player();
	~Player();
private:
	// Идентификатор игрока
	int _id;
	// Пароль игрока
	string _password;
	// Псевдоним игрока
	string nickname;
	// Завершил ли пользователь свой ход
	bool _if_made_turn;
	// Ставка игрока на аукцион по покупке материалов
	Bid _current_buy_raw_bid;
	// Ставка игрока на аукцион по продаже продукции
	Bid _current_sell_production_bid;
	// Склад продукции и материалов
	Storage _storage_room;
	// Количество функционирующих фабрик
	int _number_of_working_factories
	// Количество строящихся фабрик
	int _number_of_factories_under_construction
	// Итератор спискa указателей на фабрики, находящиеся в стадии строительства
	f_iterator fi_undercostruct;
	// Имеющиеся в распоряжении средства
	int _cash;

};
#endif //SERVER_INTERNAL_PLAYER_H