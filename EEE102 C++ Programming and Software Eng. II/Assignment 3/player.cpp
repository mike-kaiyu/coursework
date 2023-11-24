//=======================
// player.cpp
//=======================
#include <fstream>
#include<ctime>
#include<sstream>
#include"player.h"
#include "storeInfo.h"
#include<iostream>
#include<vector>
#include<string>
#include <time.h>
#include <algorithm>
using namespace std;

void player::bankruptcy()//The condition of bankruptcy.
{
	if (balance <= 0) 
	{
		cout << name << " has declared bankruptcy. " << endl;
		system("pause");
		playerbroke = 1;
	}
}

bool player::moveStep()
{
	srand((unsigned)time(0));
	int diceNum = rand() % 6 + 1;
	position += diceNum;  // Get the random number by rolling a dice.
	if (position > 79) 
	{
		position -= 80;   //Because the maximum of position is 80.
		balance += 200; //The indicated rule: If across the start, then add 200 balance.
		cout << "Passing the start! " << name << "'s balance has added 200! Good luck!" << endl;
	}
	cout << name << "'s is rolling the dice! The number of the dice is: " << diceNum << ". "; 
	cout << name << " has moved to position: " << position << endl;
	return 1;
}

bool player::broke()
{
	return playerbroke;
}

void showInformation(player &p1, player &p2)//Display the basic information of user and pc.
{
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "， " << p1.name << "'s Balcance: " << p1.balance  << endl;
	cout << "， " << p1.name << "'s Position: " << p1.position << endl;
	cout << "， " << p1.name << " has square(s): ";
	for (unsigned int i = 0; i < p1.house.size(); i++)
	{
		cout << p1.house[i] << " ";
	}
	cout << endl;
	cout << "， " << p2.name << "'s Balance: "  << p2.balance  << endl;
	cout << "， " << p2.name << "'s Position: " << p2.position << endl;
	cout << "， " << p2.name << " has square(s): ";
	for (unsigned int i = 0; i < p2.house.size(); i++)
		cout << p2.house[i] << " ";
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void AICalculation(player &p1, player &p2) {   //Calculation for pc.
	double punishment1;
	vector<int>::iterator it = find(p1.house.begin(), p1.house.end(), p2.position); //Scan user's and pc's position and houses.
	vector<int>::iterator ita = find(p2.house.begin(), p2.house.end(), p2.position);
	if (p2.position == 0)
	{
		goto sort;
	}

	else if (it != p1.house.end())//The position is in opponent's squares.
	{
		double times = 1;
		vector<int>::iterator it1 = find(p1.house.begin(), p1.house.end(), p2.position - 1);
		vector<int>::iterator it2 = find(p1.house.begin(), p1.house.end(), p2.position + 1);//Especially scan the adjacent position.
		if (it1 != p1.house.end() || it2 != p1.house.end())//The punishment rule.
													       //It will increase 10%, 15%, 20% respectively on every invesement.
		{ 
			times += 0.5;
		}
		punishment1 = (p1.price[p2.position] * times) * 0.1;
		cout << p2.name << " has passed " << p1.name << "'s bought square." << p2.name << " need to be punished by " << punishment1 << "!" << endl;
		p2.balance -= punishment1;
		p1.balance += punishment1;
		p2.bankruptcy();
		goto sort;
	}
	else if (ita != p2.house.end())   //Entre the self squares. The square could be invested.
	{
		if (p2.balance > p1.price[p2.position] / 2)
		{
			cout << p2.name << " cost " << p1.price[p2.position] / 2 << " to invest this square!" << endl;
			p1.price[p2.position] += p1.price[p2.position] / 20;
			p2.balance -= p1.price[p2.position] / 2;
			cout << p2.position << "The price of this square now is; " << p1.price[p2.position] << endl;
			goto sort;
		}
		else {
			cout << p2.name << " did not buy!" << endl;//When choosing not invest.
			goto sort;
		}
	}
	else if (p2.balance > p1.price[p2.position])
	{
		cout << p2.name << " spend " << p1.price[p2.position] << " buying " << "square: " << p2.position << endl;
		p2.balance -= p1.price[p2.position];
		p2.house.push_back(p2.position);
		p1.table[p2.position] = "++";
		goto sort;
	}
	else {
		cout << p2.name << " did not invest!" << endl;//When choosing not invest.
	}
sort:
	sort(p2.house.begin(), p2.house.end()); //Sort the houses.

}

void userCalculation(player &p1, player &p2) {
	double punishment1;
	string choose;
	vector<int>::iterator it = find(p2.house.begin(), p2.house.end(), p1.position);
	vector<int>::iterator ita = find(p1.house.begin(), p1.house.end(), p1.position);
	if (p1.position == 0)
	{
		goto arrange;
	}
	else if (it != p2.house.end()) {
		double times = 1;
		vector<int>::iterator it3 = find(p2.house.begin(), p2.house.end(), p1.position - 1);
		if (it3 != p2.house.end()) { times = times + 0.5; }
		vector<int>::iterator it4 = find(p2.house.begin(), p2.house.end(), p1.position + 1);
		if (it4 != p2.house.end()) { times = times + 0.5; }
		punishment1 = p1.price[p1.position] / 10 * times;
		cout << p1.name << " has pass " << p2.name << "'s bought square " << p1.name << " need to be punished by " << punishment1 << "!" << endl;
		p1.balance -= punishment1;
		p2.balance += punishment1;
		p1.bankruptcy();
		goto arrange;
	}
	else if (ita != p1.house.end()) {
		if (p1.balance > (p1.price[p1.position] * 0.5)) {
			cout << "The price of this square now is " << p1.price[p1.position] / 2 << ". Input Y if you want to invest / Input N if you do not want to invest." << endl;
		begin1:
			cin >> choose;
			if (choose == "Y" || choose == "y") {// The choice to see if user want to buy.
				p1.balance -= p1.price[p1.position] / 2;
				p1.price[p1.position] += p1.price[p1.position] / 20;
				cout << "You have invested, your opponent will be punished 5% more if he went to this square or near this square!";
				cout << endl;
				cout << "The price of this square now is; " << p1.position  << endl;
				goto arrange;
			}
			else if (choose == "N" || choose == "N") {
				cout << "You choose not invest this square! " << endl;
				goto arrange;
			}
			else {
				cout << "Invalid input!! Please just input Y or N!" << endl;
				goto begin1;
			}
		}
		else {
			cout << "You do not have erough money, wait for the next turn!" << endl;
			goto arrange;
		}
	}
	else {
		if (p1.balance > p1.price[p1.position]) {
			cout << "The price of this square now is "  << p1.price[p1.position] << ". Input Y if you want to invest / Input N if you do not want to invest. Input S to save the game." << endl;
			cout << "Attention!!: If you save the game, it will exit directly and your opponent will have one more chance to roll the dice and take action! So, be careful!!." << endl;
		begin2:
			cin >> choose;
			if (choose == "y" || choose == "Y") {// The choice to see if user want to buy.
				p1.balance -= p1.price[p1.position];
				cout << "You have bought the square: " << p1.position  << endl;
				p1.house.push_back(p1.position);
				p1.table[p1.position] = "**";
				goto arrange;
			}
			else if (choose == "n" || choose == "N") {
				cout << "You choose not buy this square! " << endl;
				goto arrange;
			}
			else if (choose == "S" || choose == "s") { //To save the file.
				save(p1, p2);
				cout << "Saved!!";
				exit(0);
			}
			else {
				cout << "Invalid input!! Please just input Y, N or S!!" << endl;
				goto begin2;
			}
		}
		else {
			cout << "Your dont have enough money! Wait for the next round!" << endl;
		}
	}
arrange:
	sort(p1.house.begin(), p1.house.end());//Sort the houses.
}

void showMap(player &p1, player &p2) //I took very very long time to do this!!!!
{   
	cout << "|---------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
	cout << "|      |  ";
	for (int i = 60; i > 41; i--)
	{
		cout << i << "  |  ";
	}
	cout << "41  |      |" << endl;
	cout << "|      | ";
	for (int i = 60; i > 40; i--)
	{
		cout << setw(3) << p1.price[i] << p1.table[i] << "| ";
	}
	cout << "     |" <<endl;
	
	cout << "|------|--------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
	int k = 1;
	for (int i = 61; i < 81; i++) 
	{
		cout << "|  "<< i <<"  |                                                                                                                                           |  "<< i - (20 + k) <<"  |" << endl;
		cout << "| " << setw(3) << p1.price[i] << p1.table[i] << "|                                                                                                                                           | " << setw(3) << p1.price[i - (20 + k)] << p1.table[i - (20 + k)] << "|" << endl;
		cout << "|------|                                                                                                                                           |------|" << endl;
		k = k + 2;
	}
	cout << "|------|-------------------------------------------------------------------------------------------------------------------------------------------|------|" << endl;
	cout << "| Start|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |  11  |  12  |  13  |  14  |  15  |  16  |  17  |  18  |  19  |  20  |      |" << endl;
	cout << "|      | ";
	for (int i = 1; i < 21; i++) 
	{
		cout << setw(3) << p1.price[i] << p1.table[i] << "| ";
	}
	cout << endl;
	cout << "|--------------------------------------------------------------------------------------------------------------------------------------------------|------|" << endl;
}

void save(player &p1, player &p2) {  //To save the informaiton,
	ofstream fout;
	fout.open("save.txt");

	fout << p1.house.size() << endl;
	for (auto i = p1.house.begin(); i != p1.house.end(); i++)
		fout << *i << ' ';
	fout << endl;
	fout << p1.price.size() << endl;
	for (auto i = p1.price.begin(); i != p1.price.end(); i++)
		fout << *i << ' ';
	fout << endl;
	fout << p1.position << endl;
	fout << p1.balance << endl;
	fout << p1.name << endl;

	fout << p2.house.size() << endl;
	for (auto i = p2.house.begin(); i != p2.house.end(); i++)
		fout << *i << ' ';
	fout << endl;
	fout << p2.price.size() << endl;
	for (auto i = p2.price.begin(); i != p2.price.end(); i++)
		fout << *i << ' ';
	fout << endl;
	fout << p2.position << endl;
	fout << p2.balance << endl;
	fout << p2.name << endl;

	fout.close();
	cout << "saved" << endl;
}
void start(player &p1, player &p2) { //To load the old data.
	ifstream fin;
	fin.open("save.txt");
	if (!fin)
	{
		cout << ("Save data does not exist") << endl;
		exit(0);
	}

	for (int i = 0; i < 81; i++)
		p1.table.push_back("  ");
	int size;
	fin >> size;
	for (int i = 0; i < size; i++)
	{
		int temp;
		fin >> temp;
		p1.house.push_back(temp);
		p1.table[temp] = "**";
	}
	fin >> size;
	for (int i = 0; i < size; i++)
	{
		int temp;
		fin >> temp;
		p1.price.push_back(temp);
	}
	fin >> p1.position;
	fin >> p1.balance;
	fin >> p1.name;

	for (int i = 0; i < 81; i++)
		p2.table.push_back("  ");
	fin >> size;
	for (int i = 0; i < size; i++)
	{
		int temp;
		fin >> temp;
		p2.house.push_back(temp);
		p1.table[temp] = "++";
	}
	fin >> size;
	for (int i = 0; i < size; i++)
	{
		int temp;
		fin >> temp;
		p2.price.push_back(temp);
	}
	fin >> p2.position;
	fin >> p2.balance;
	fin >> p2.name;

	p1.playerbroke = 0;
	p2.playerbroke = 0;

	fin.close();
	cout << ("Started from last time!") << endl;
	system("pause");
}



