
class Order: public BaseData
{
	public:
	int orderID;
	char side; // 'B' for bid, 'O' for offer
	double price;
	int quantity;
};
