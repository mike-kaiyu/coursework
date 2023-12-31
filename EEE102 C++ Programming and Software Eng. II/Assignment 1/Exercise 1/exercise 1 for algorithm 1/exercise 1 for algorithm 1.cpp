// exercise 1 for algorithm 1.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

bool same_vec(vector<int> a, vector<int> b)  //Create the boolean function.
{
	if (a.size() != b.size())                //To identify whether two vectors are identical.
	{                                     
		return false;
	}
	else if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] == b[i])
			{
				continue;
			}
			else
			{
				return false;
			}

		}
		return true;
	}

}

int main()
{
	vector<int> a, b; //Initializate vector a and vector b.

	cout << "Please input the elements of vector A (Use space to separate each element. When finish inputting, input 'end' to do next operation)" << endl;
	cout << "For example: 12 32 14 56 end" << endl; //Marked words.
	string aElements;         // Use stringstream to get input.
	int ae;
	stringstream ss;
	cin >> aElements;

	while (aElements != "end") //When input != "end",  it can get number.
	{
		ss << aElements;
		while (ss >> ae)
		{
			a.push_back(ae);
		}
		ss.clear();
		cin >> aElements;
	}

	sort(a.begin(), a.end());  //Rank the elements in vector.
	a.erase(unique(a.begin(), a.end()), a.end());//Pick out the same elements and move them back then delete them.

	cout << "Please input the elements of vector B (Use space to separate each element. When finish inputting, input 'end' to do next operation)" << endl;
	cout << "For example: 12 32 14 56 end" << endl;
	string bElements;
	int be;
	cin >> bElements;

	while (bElements != "end")	//When input != "end",  it can get number.
	{
		ss << bElements;
		while (ss >> be)
		{
			b.push_back(be);
		}
		ss.clear();
		cin.clear();
		cin >> bElements;
	}

	sort(b.begin(), b.end());	//Rank the elements in vector.
	b.erase(unique(b.begin(), b.end()), b.end());  //Pick out the same elements and move them back then delete them.

	bool comparison = same_vec(a, b);

	if (comparison == true)
	{
		cout << "These two vectors are idendtical." << endl;
	}

	else if (comparison == false)
	{
		cout << "These two vectors are not idendtical." << endl;
	}
	return 0;
}

