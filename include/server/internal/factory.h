#ifndef  SERVER_INTERNAL_FACTORY_H
#define SERVER_INTERNAL_FACTORY_H

class Factory {
public:
	Factory();
	~Factory();
private:
	// Сколько месяцев осталось до окончания строительства
	int _months_till_construction;
};

#endif //SERVER_INTERNAL_FACTORY_H
