// exercise 2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int fn(int a, int b);

class  Fraction
{
private:
	int top;
	int bottom;
public:
	Fraction(int NU = 0, int DE = 1)  //Contructor
	{
		top = NU; bottom = DE;        //Initialize top and bottom.
		if (bottom < 0)
		{
			bottom = -bottom;
			top = -top;
		}
	}

	friend  Fraction operator + (Fraction f1, Fraction f2)//Operator + Overloaded member function
	{
		return  Fraction(f2.top*f1.bottom + f1.top*f2.bottom, f1.bottom*f2.bottom);
	}
	friend  Fraction operator - (Fraction f1, Fraction f2)//Operator - Overloaded member function
	{
		return  Fraction(f1.top*f2.bottom - f2.top*f1.bottom, f1.bottom*f2.bottom);
	}
	friend  Fraction operator / (Fraction f1, Fraction f2)//Operator / Overloaded member function
	{
		return  Fraction(f1.top*f2.bottom, f1.bottom*f2.top);
	}
	friend  Fraction operator * (Fraction f1, Fraction f2)//Operator * Overloaded member function
	{
		return  Fraction(f1.top*f2.top, f1.bottom*f2.bottom);
	}

	void input(Fraction f1, Fraction f2);
	void output(Fraction f1, Fraction f2);
};

void  Fraction::input(Fraction f1, Fraction f2)	//External implementation of input function class 
{
	cin >> top >> bottom;        // Here can realize the function of inputting
	if (bottom == 0)            //If top or bottom is equal to 0, it will report to user, end the program.
	{
		cout << "Do not devide by zero Error, " << endl;
		exit(0);
	}
}

void  Fraction::output(Fraction f1, Fraction f2)	//External implementation of output function class 
{
	int c;											//Initialize c.
	double convert;                                 //c is the greatest common divisor.
	c = fn(top, bottom);
	top /= c; bottom /= c;
	convert = (double)top / bottom;                //Here it can realize the function of comparing.
	if (bottom < 0)                                //Normalize the format of the fraction.
	{
		bottom = -bottom;
		top = -top;
	}
	if (top != 0) {
		cout << "( " << top << "/" << bottom << " )" << "The demical of this fraction is: " << convert << endl;
	}

	else cout << "( " << top << " ). " << "The demical of this fraction is: " << convert << endl;


	if ((double)f1.top / (double)f1.bottom - (double)(f2.top / (double)f2.bottom) > 0)
	{
		cout << "The previous fraciton is larger than the next fraction." << endl;
	}

	else if ((double)(f1.top / (double)f1.bottom) - (double)(f2.top / (double)f2.bottom) < 0)
	{
		cout << "The previous fraciton is smaller than the next fraction." << endl;
	}

	else if ((double)(f1.top / (double)f1.bottom) - (double)(f2.top / (double)f2.bottom) == 0)
	{
		cout << "The previous fraciton is equal to the next fraction." << endl;
	}

}

int fn(int a, int b)	// Find the greatest common divisor.
{
	int d;
	if (a > b)
	{
		for (d = a; d >= 1; d--)
			if (a%d == 0 && b%d == 0)
			{
				break;
			}
		return d;
	}

	else if (a <= b)
	{
		for (d = b; d >= 1; d--)
			if (a%d == 0 && b%d == 0)
			{
				break;
			}
		return d;
	}
}
int main()
{
	Fraction f1, f2;   //Instantiate f1 and f2.
	char operation;
	cout << "Input the initial fraction (use space to distinguish the numerator and the denominator): " << endl;
	f1.input(f1, f2);  //Call the method of input(Fraction f1, Fraction f2).

	cout << "Input the operator (Please just input +, -, * or /, then press enter to continue): " << endl;
	cin >> operation;
	cout << "Input the next fraction (use space to distinguish the numerator and the denominator): " << endl;
	f2.input(f1, f2);  //Call the method of output(Fraction f1, Fraction f2).

	switch (operation)  //Operation menu.
	{
	case '-':
		f1 = f1 - f2;
		break;
	case '+':
		f1 = f1 + f2;
		break;
	case '*':
		f1 = f1 * f2;
		break;
	case '/':
		f1 = f1 / f2;
		break;
	default:
		cout << "Please input valid operations, the program will close...";
		break;
	}
	cout << "The result of two operated fractions is: ";
	f1.output(f1, f2); //Call the method of output(Fraction f1, Fraction f2).
}
