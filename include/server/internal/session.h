#ifndef SERVER_INTERNAL_SESSION_H
#define SERVER_INTERNAL_SESSION_H

#include <memory>

#include "market.h"
#include "player.h"
#include "ruleset.h"

class Session {
	using Pit = std::list<std::shared_ptr<Player>>::iterator;
    enum class State {
        WAITING_FOR_PLAYERS,
        PLAYING,
        FINISHED
    };
public:
	Session();
	~Session();
private:
	// Идентификатор сессии
	int _id;
	// Пароль для доступа к сессии
    std::string _password;
	// Итератор списка умных указателей на игроков
	Pit _plistit;
	//Указатель на рынок сессии
	std::shared_ptr<Market> _market;
    ///@brief Указатель на состав правил
    std::shared_ptr<Ruleset> _ruleset;
    ///@brief Состояние сессии
    State _state;
};

#endif //SERVER_INTERNAL_SESSION_H
