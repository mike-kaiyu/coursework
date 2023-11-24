#include <iostream>
#include<string>
#include <cstdlib>
#include"storeInfo.h"
using namespace std;

int main()
{
	string choose;
	string userName;
	bool success = 0;
	player *user = NULL; //Initialize a new user.
	player *pc = NULL;  //Initialize a new pc.

	cout << "Hello! Welcome to Monopoly! Input Y to start the new game / Input N to strat the saved game!" << endl; //Welcome words.
	cin >> choose; //Inpur choose.

	if (choose == "Y" || choose == "y") {// Ask user want to start new game or start an old game. 
		user = new storeInfo(0, userName);//Initialize the information of the user.
		pc = new storeInfo(0, "Computer");//Initialize the information of the pc.
		start(*user, *pc);//Load the saved game!
		system("cls");
		cout << "You have loaded your old game!";

		while (!user->broke() && !pc->broke())//When both of players are not bankruptcy.
		{
			success = 0;
			while (success != 1)
			{
				system("cls");
				showInformation(*user, *pc);//Display the basic information of the player.
				success = user->moveStep();//After rolling the dice, go to the corresponding position.
				userCalculation(*user, *pc);//Calculation for user.
				system("pause");
				break;
			}
			if (!pc->broke()) { //When pc is not bankruptcy.
				pc->AI(*user);
				AICalculation(*user, *pc);//Calculation for pc.
				system("pause");
				showInformation(*user, *pc);//Display the basic information of the player.
				showMap(*user, *pc);
				system("pause");
			}
			if (user->broke())//When user is bankruptcy.
			{
				system("cls");
				cout << endl << "************ GAME OVER ************" << endl;
				delete user;
				system("pause");
				return 0;
			}
			if (pc->broke()) {
				break;
			}
		}
		system("cls");
		cout << "************ You win this game! ************";
		delete user;
		system("pause");
	}
	else if (choose == "n" || choose == "N") {// When stat a new game
		cout << "Please input your name. Do not input the space when typing your name!! !!*Attention*!! Please use full screen to play this game!" << endl;
		cin >> userName;
		success = 1;
		system("cls");
		cout << "Your name is: " << userName << endl;
		cout << "The number under the ordered square is the corresponding price of the square." << endl;
		cout << "Your mark: **. PC's mark: ++" << endl;//Display the rule of this game.
		system("pause");
		system("cls");
		user = new storeInfo(0, userName);
		pc = new storeInfo(0, "Computer");

		while (!user->broke() && !pc->broke())
		{
			success = 0;
			while (success != 1)
			{
				system("cls");
				showInformation(*user, *pc);
				success = user->moveStep();
				userCalculation(*user, *pc);
				system("pause");
				break;
			}
			if (user->broke())
			{
				system("cls");
				cout << endl << "************ GAME OVER ************" << endl;
				delete user;
				system("pause");
				return 0;
			}
			if (!pc->broke()) {
				pc->AI(*user);
				AICalculation(*user, *pc);
				system("pause");
				showInformation(*user, *pc);
				showMap(*user, *pc);
				system("pause");
			}
			if (pc->broke()) {
				break;
			}

		}
		system("cls");
		cout << "************ You win this game! ************";
		delete user;
		system("pause");
	}
	return 0;
}