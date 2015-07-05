#ifndef SERVER_INTERNAL_MARKET_H
#define SERVER_INTERNAL_MARKET_H
class Market {
public:
	Market();
	~Market();
	void changeState(int num_of_players);
private:
	// Cостояние рынка. Рынок может занимать один из пяти уровней.
	int _state;
	int _current_number_of_players;
};
#endif //SERVER_INTERNAL_MARKET_H