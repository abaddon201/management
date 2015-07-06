#ifndef SERVER_INTERNAL_STORAGE_H
#define SERVER_INTERNAL_STORAGE_H
class Storage
{
public:
	Storage();
	~Storage();
private:
	// Хранящаяся на складе не реализованная продукция
	int _production_stored;
	// Хранящиеся на складе не реализованные материалы
	int _raw_stored;
};
#endif //SERVER_INTERNAL_STORAGE_H