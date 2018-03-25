#include<list>
#include "BaseData.h"
#include"PriceLevel.h"

using namespace std;

void PriceLevel::add(Order *order)
{
		_orderList->push_back(order);
		_levelSize=_levelSize+order->quantity;
		_levelPrice=order->price;
}	
void PriceLevel::remove(Order *order)
{
		_orderList->remove(order);
}	
void PriceLevel::modifyLevel(Order *oldOrder,Order *newOrder)
{
		_orderList->remove(newOrder);
		_levelSize = _levelSize - oldOrder->quantity;
		_levelSize = _levelSize + newOrder->quantity;
		_orderList->push_back(newOrder);
}
