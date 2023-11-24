//=========================
// player.h
//=========================
#include<string>
#include<iostream>
#include<vector>
#include<time.h>
#include<iomanip>
using namespace std;

#ifndef _PLAYER
#define _PLAYER

class player
{
	friend void userCalculation(player &p1, player &p2); //Calculation for user.
	friend void showInformation(player &p1, player &p2); // Display the information.
	friend void showMap(player &p1, player &p2); //Display the map.
	friend class storeInfo; // Store the information.
	friend void AICalculation(player &p1, player &p2);//Calculation for pc.
	friend void save(player &p1, player &p2);//To save the current information.
	friend void start(player &p1, player &p2);// To load the information saved.

private:
	bool playerbroke;

public:
	virtual void AI(player &p) = 0;
	virtual bool punish(player &p) = 0;
	void bankruptcy();
	bool moveStep();
	bool broke();
	virtual ~player() {};

protected:
	int  balance, position;
	vector<string>table;
	vector<int>price;
	vector<int> house;
	string name;

};
#endif