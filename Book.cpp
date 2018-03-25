#include<vector>
#include<map>
#include "BaseData.h"
#include "Book.h"

using namespace std;

void Book::addOrder(bookSide side, Order* order)
{
		// Find price level using binary search on vector.
		// if level not present already create it

		_orderMap.insert(std::pair<int,Order*>(order->orderID,order));
		PriceLevel* priceLevel;
		if(side == Book::BUY)
		priceLevel = myFind(_buys,side, order->price);
		else
		priceLevel = myFind(_sells,side, order->price);

		// Add the order to price level list, add quantity to _levelSize
		priceLevel->add(order);
}
	
PriceLevel* Book::myFind(std::vector<PriceLevel *> &levels,bookSide side, double price)
{
		// find the level in vector. Used binary search
		// if level is not present, then create a new pricelelvel and insert it at right position 
		// with o(1) complexity using iterator got while doing search
		
		// find comparison will work in apposite way for sell side and buy side
		// as prices are maintained in ascending and descending way in them
		// get the side from _side here.

		int low = 0;
		int high = levels.size() - 1;
		while (low <= high) 
		{
			int mid = (low + high)/2;
			if ((levels[mid]->_levelPrice) == price) 
			{
				return levels[mid];
			}
			else
			{
				if(side == Book::SELL)
				{
					if (levels[mid]->_levelPrice > price) 
						low = mid + 1;
					else 
						high = mid - 1;
				}
				else // side is BUY, price levels are in descending order, so comparision function is <
				{
					if (levels[mid]->_levelPrice < price) 
						low = mid + 1;
					else 
						high = mid - 1;
				}
			}
		}

		//price level not found. Insert the price new price level after the low index found above
		PriceLevel *level = new PriceLevel();
		levels.insert(levels.begin()+ low, level);
		return level;
}

void Book::modifyOder(Order *newOrder,bookSide side)
{
		// find order in the order map present at book level; 
		// if order not found the its a serious error. Books are not healthy
		// get the level from found order. and modify order size and cumalative size as well.
		std::map<int, Order*>::iterator itrOrder;
		itrOrder = _orderMap.find(newOrder->orderID);
		if(itrOrder == _orderMap.end())
		{
				// serious error. 
				return;
		}
		else
		{
			Order* oldOrder = itrOrder->second;
			if(oldOrder->price != newOrder->price)
			{
				//subtract the old quantity from old level
				deleteOrder(oldOrder,side);
				// add modified quantity at new level
				addOrder(side,newOrder);
			}
			else
			{
				// do the cumlative quantity modifications 
				PriceLevel*	priceLevel;
				if(side == Book::BUY)
				priceLevel = myFind(_buys,side, newOrder->price);
				else
				priceLevel = myFind(_sells,side ,newOrder->price);
			
				priceLevel->modifyLevel(oldOrder, newOrder);
				// if price is modified then remove order from priceLevel order list and add it to the
				// another price level list. Do the corrospoinding changes in price level cumulative
				//	quantity
			}
		}

}

void Book::deleteOrder(Order *order,bookSide side)
{
		// find order in local map;
		Order *orderToBeDeleted;
		std::map<int, Order*>::iterator itrOrder;
		itrOrder = _orderMap.find(order->orderID);
		if(itrOrder == _orderMap.end())
		{
				// order id to be deleted not found. 
				return;
		}
		else
		{
			orderToBeDeleted = itrOrder->second;
			_orderMap.erase(itrOrder);
		}
		PriceLevel*	priceLevel;
		if(side == Book::BUY)
		priceLevel = myFind(_buys,side, orderToBeDeleted->price);
		else
		priceLevel = myFind(_sells,side, orderToBeDeleted->price);
			
		priceLevel->remove(order);
		// Order has price level pointer, remove order from priceLevel;
		
		// delete the order.
}
PriceLevel* Book::findPriceLevel(bookSide side, int level)
{
	PriceLevel* priceLevel;
	if(side == Book::BUY)
	{
		priceLevel = _buys[level];
	}
	else
	{
		priceLevel = _sells[level];
	}
	return priceLevel;
}
Order* Book::findOrder(int orderid)
{
		// find order in local map;
		Order *orderToBeDeleted;
		std::map<int, Order*>::iterator itrOrder;
		itrOrder = _orderMap.find(orderid);
		if(itrOrder == _orderMap.end())
		{
			return NULL;
		}
		else
		{
			return itrOrder->second;
		}
}

int main()
{
	Order* order1 = new Order();
	order1->orderID = 22;
	order1->side = 'B';
	order1->price = 234;
	order1->quantity = 30;
	Book* book1 = new Book();
	book1->addOrder(Book::BUY,order1);

	Order* order2 = new Order();
	order2->orderID = 22;
	order2->side = 'B';
	order2->price = 234;
	order2->quantity = 40;

	book1->modifyOder(order2,Book::BUY);
	PriceLevel* pl = book1->findPriceLevel(Book::BUY,0);
	if(pl)
	{
		cout<<"PriceLevel Price:"<<pl->_levelPrice<<":PriceLevel Size:"<<pl->_levelSize<<endl;
	}
	//book1->deleteOrder(order1,Book::BUY);
	Order *ord=NULL;
	ord = book1->findOrder(22);
	if(ord)
	{
		cout<<ord->price<<endl;
		cout<<ord->quantity<<endl;
	}
}
