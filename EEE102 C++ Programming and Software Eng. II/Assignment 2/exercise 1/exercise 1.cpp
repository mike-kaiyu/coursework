// exercise 1.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int fn(int a, int b);

class  Fraction
{
protected:
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
	Fraction operator + (Fraction R);//Operator + Overloaded member function
	Fraction operator - (Fraction R);//Operator - Overloaded member function
	Fraction operator / (Fraction R);//Operator / Overloaded member function
	Fraction operator * (Fraction R);//Operator * Overloaded member function

	void input(Fraction f1, Fraction f2);
	void output(Fraction f1, Fraction f2);

	friend void convertF(const Fraction &, Fraction &);  //convertF is the friend function of class Fraction.
};

class iFraction :public Fraction
{
public:
	iFraction(int NU = 0, int DE = 1) :Fraction(NU, DE) {}
	void output();
};

void  Fraction::input(Fraction f1, Fraction f2)	//External implementation of input function class 
{
	cin >> top >> bottom;        // Here can realize the function of inputting
	if (bottom == 0)            //If top or bottom is equal to 0, it will report to user, end the program.
	{
		cout << "Do not divide by zero Error, " << endl;
		exit(0);
	}
}

void  Fraction::output(Fraction f1, Fraction f2)	//External implementation of output function class 
{
	float compare = (float)((float)f1.top / (float)f1.bottom) - (float)((float)f2.top / (float)f2.bottom);
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
		cout << "( " << top << "/" << bottom << " )" << "The decimal of this fraction is: " << convert << endl;
	}

	else cout << "( " << top << " ). " << "The decimal of this fraction is: " << convert << endl;


	if (compare > 0)
	{
		cout << "The previous fraction is larger than the next fraction." << endl;
	}

	else if (compare < 0)
	{
		cout << "The previous fraction is smaller than the next fraction." << endl;
	}

	else if (compare == 0)
	{
		cout << "The previous fraction is equal to the next fraction." << endl;
	}

}

Fraction Fraction::operator + (Fraction R)
{
	int nu = top;
	int de = bottom;
	int t = R.top;
	int b = R.bottom;

	int x = nu * b + de * t;
	int y = de * b;

	return Fraction(x, y);
}

Fraction Fraction::operator - (Fraction R)
{
	int nu = top;
	int de = bottom;
	int t = R.top;
	int b = R.bottom;

	int x = nu * b - de * t;
	int y = de * b;

	return Fraction(x, y);
}

Fraction Fraction::operator * (Fraction R)
{
	int nu = top;
	int de = bottom;
	int t = R.top;
	int b = R.bottom;

	int x = nu * t;
	int y = de * b;

	return Fraction(x, y);
}

Fraction Fraction::operator / (Fraction R)
{
	int nu = top;
	int de = bottom;
	int t = R.top;
	int b = R.bottom;

	int x = nu * b;
	int y = de * t;

	return Fraction(x, y);
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

void iFraction::output()
{
	int c = (abs(top) - abs(top) % abs(bottom)) / abs(bottom);
	if (top < 0) 
	{
		if (c < 1) 
		{
			cout << "The mixed fraction for this improper fraction is: -" << (abs(top) - abs(bottom) * c) << "/" << abs(bottom) << endl;
		}
		else if (c > 1) 
		{
			cout << "The mixed fraction for this improper fraction is: " << -c << " " << (abs(top) - abs(bottom) * c) << "/" << abs(bottom) << endl;
		}
		else if (c == 1) 
		{
			cout << "The mixed fraction for this improper fraction is itself."  << endl;
		}
	}
	else if (top > 0)
	{
		if (c < 1)
		{
			cout << "The mixed fraction for this improper fraction is: " << (abs(top) - abs(bottom) * c) << "/" << abs(bottom) << endl;
		}
		else if (c > 1)
		{
			cout << "The mixed fraction for this improper fraction is: " << c << " " << (abs(top) - abs(bottom) * c) << "/" << abs(bottom) << endl;
		}
		else if (c == 1)
		{
			cout << "The mixed fraction for this improper fraction is itself. " << endl;
		}

	}
	else if (top == 0) 
	{
		cout << "The mixed fraction for this improper fraction is 0. " << endl;
	}
}

void convertF(const Fraction & src, Fraction & target) //convertF is the friend function of two classes(Fraction and iFraction).
{                                                      //Here is to get the top and bottom in Fraction and send them to iFraction to convert.
	target.top = src.top;
	target.bottom = src.bottom;
}


int main()
{
	Fraction f1, f2, f3;   //Instantiate f1 and f2.
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
		f3 = f1 - f2;
		break;
	case '+':
		f3 = f1 + f2;
		break;
	case '*':
		f3 = f1 * f2;
		break;
	case '/':
		f3 = f1 / f2;
		break;
	default:
		cout << "Please input valid operations, the program will close...";
		break;
	}
	cout << "The result of two operated fractions is: ";
	f3.output(f1, f2); //Call the method of output(Fraction f1, Fraction f2).
	iFraction if1;
	convertF(f3, if1);
	if1.output();
}

