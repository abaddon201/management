#ifndef SERVER_INTERNAL_SESSION_H
#define SERVER_INTERNAL_SESSION_H

#include <memory>

#include "sever/internal/market.h"
#include "sever/internal/player.h"
class Session
{
	using Pit = std::list<std::shared_ptr<Player>>::iterator;
public:
	Session();
	~Session();
private:
	// Идентификатор сессии
	int _id;
	// Пароль для доступа к сессии
	string _password;
	// Итератор списка умных указателей на игроков
	Pit _plistit;
	//Указатель на рынок сессии
	std::shared_ptr<Market> _market;
};
#endif //SERVER_INTERNAL_SESSION_H