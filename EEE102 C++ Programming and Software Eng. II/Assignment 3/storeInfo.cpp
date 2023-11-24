#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include"storeInfo.h"

using namespace std;
storeInfo::storeInfo(int positionIn, string nameIn)
{
	srand((unsigned)time(0));
	position = positionIn;//To obtain the position.
	balance = 1000;
	name = nameIn;//To obtain the name.
	house = {};//Initialize the elements of the house.

	price= { 0, 10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500,10 + rand() % 500 };
	playerbroke = 0;
	table = {"  ","  ","  ","  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  " ,"  "};
}

void storeInfo::AI(player &p)
{
	moveStep();
}

bool storeInfo::punish(player &p)
{
	return 1;
};
