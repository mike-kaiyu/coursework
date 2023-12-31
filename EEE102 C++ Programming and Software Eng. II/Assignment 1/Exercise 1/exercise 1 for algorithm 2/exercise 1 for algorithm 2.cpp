// exercise 1 for algorithm 2.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

bool same_vec(vector<int> a, vector<int> b)	//Create the boolean function.
{
	for (int i = 0; i < a.size() - 1; i++)		//To identify whether two vectors are identical.
	{
		for (int j = 0; j < a.size(); j++)
		{
			if (a[i] == a[j])
			{
				a[i] = a[i + 1];
				a.erase(a.begin() + j);			//Pick out the same elements in vector a and delete them.
			}
		}
	}

	for (int i = 0; i < b.size() - 1; i++)		//Pick out the same elements in vector b and delete them.
	{
		for (int j = 0; j < b.size(); j++)
		{
			if (b[i] == b[j])
			{
				b[i] = b[i + 1];
				b.erase(b.begin() + j);
			}
		}
	}

	int A = 0;	//Counters of elements in A are the same as B.
	int B = 0;  //Counters of elements in B are the same as A.
	if (a.size() != b.size())
	{
		return false;
	}

	else if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = 0; j < b.size(); j++)
			{
				if (a[i] != b[j])
				{
					continue;
				}
				else
					A++;
			}
		}

		for (int i = 0; i < b.size(); i++)
		{
			for (int j = 0; j < a.size(); j++)
			{
				if (b[i] != a[j])
				{
					continue;
				}
				else
					B++;
			}
		}

		if (A == a.size() && B == b.size()) //Algorithm 2.
		{
			return true;
		}
		else
			return false;
	}
}

int main()
{
	vector<int> a, b;		//Initializate vector a and vector b.

	cout << "Please input the elements of vector A (Use space to separate each element. When finish inputting, input 'end' to do next operation)" << endl;
	cout << "For example: 12 32 14 56 end" << endl; //Marked words.

	string aElements;		 // Use stringstream to get input.
	int aE;
	stringstream ss;
	cin >> aElements;

	while (aElements != "end")		//When input != "end",  it can get number.
	{
		ss << aElements;
		while (ss >> aE)
		{
			a.push_back(aE);
		}
		ss.clear();
		cin >> aElements;
	}


	cout << "Please input the elements of vector B (Use space to separate each element. When finish inputting, input 'end' to do next operation)" << endl;
	cout << "For example: 12 32 14 56 end" << endl;

	string bElements;
	int bE;
	cin >> bElements;

	while (bElements != "end")		//When input != "end",  it can get number.
	{
		ss << bElements;
		while (ss >> bE)
		{
			b.push_back(bE);
		}
		ss.clear();
		cin.clear();
		cin >> bElements;
	}


	bool comparison = same_vec(a, b);

	if (comparison == true)
	{
		cout << "These two vectors are idendical." << endl;
	}

	else if (comparison == false)
	{
		cout << "These two vectors are not idendical." << endl;
	}
	system("Pause");
	return 0;
}



