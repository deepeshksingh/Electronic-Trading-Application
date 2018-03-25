#include "PriceLevel.h"
#include<vector>
#include<map>
using namespace std;

class Book: public BaseData
{
	public:
	//	Main book content pointer to priceLevels
	//  Vector choosen
	//		1> It will have contiguos underlying memory, level look up  in 0(1), as vector as sequnetial containers with random iterator
	//		2> In case of feed has 100000+ symbols, book will have only limited levels save loads of book memory for illiquide, non-active symbols, 
	//			though which could be dynamically increased. In case book exceeds the current size(max levels),
	//			then vector underlying memory relocation will occur and it will move only pointers and not 
	//			actual price level.
	//		3>  
	std::vector<PriceLevel *> _buys;
	std::vector<PriceLevel *> _sells;


	//Subscription of symbol to which book belongs; Not required
//	subscrition	*_sub;

	// Order map in which all orders for this symbols reside
	std::map<int, Order*> _orderMap;

	enum bookSide
	{
		BUY=0,
		SELL=1
	};
	void addOrder(bookSide side, Order* order);
	PriceLevel* myFind(std::vector<PriceLevel *> &levels,bookSide side, double price);
	void modifyOder(Order *newOrder,bookSide side);
	void deleteOrder(Order *order,bookSide side);
	PriceLevel* findPriceLevel(bookSide side, int level);
	Order* findOrder(int orderID);
	~Book()
	{
	}
}; 
