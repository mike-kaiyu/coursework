#include "player.h"
#include <iostream>
#include <string>

using namespace std;
class storeInfo : public player	
{
public:
	storeInfo(int positionIn, string nameIn = "NotGiven");
	storeInfo() {};
	void AI(player &p);
	bool punish(player &p);
};