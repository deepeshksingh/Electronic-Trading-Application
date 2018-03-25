#include<iostream>
using namespace std;
class BaseData
{
	public:
	// Details of where update arrived
	std::string _line; // IP:PORT
	std::string _lineIdentifier; // Logical name by exchange: A,B,C or Trade/Order/Sec
	unsigned long long _seqNo;	// 5,6,7,8,9 .....

	// Time to be populated in Business objects
	time_t _exchangeTime;
	time_t _recieveTime;
	time_t _sendTime;
};
