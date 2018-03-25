#include "Order.h"
#include<list>
using namespace std;

class PriceLevel: public BaseData
{
	public:
//	Book *_book;	//	pointer to book to which this level belongs
//	Book::bookSide _side;
	double _levelPrice;
	unsigned long _levelSize;
	std::list<Order *> *_orderList;
	void add(Order *order);
	void remove(Order *order);
	void modifyLevel(Order *oldOrder,Order *newOrder);
	PriceLevel()
	{
		_orderList = new list<Order*>();
		_levelPrice=0.0;
		_levelSize=0;
	}
	~PriceLevel()
	{
		delete _orderList;
	}
};
