#include <iostream>
#include <math.h>
#include <string>
#include "Simplify.h"
#include <Windows.h>

using namespace std;

int main()
{
	char beginning;
	string intro = "Welcome to a program which will either teach you how to factorise or just factorise for you! (Made by Luc Rosenzweig). Press any key to continue (then press enter)...\n";
	int k = 0;
	while (intro[k] != '\0')
	{
		cout << intro[k];
		Sleep(rand() % 1 + 35);
		k++;
	};
	std::cin >> beginning;
	bool process = true;
	while (process)
	{
		process = false;
		char decision;
		cout << "Press 'y' to learn how to factor trinomials or 'n' to solve a trinomial\n";
		cin >> decision;
		if (decision == 'y')
		{
			char decision2;
			cout << "Would you like to learn how to factor the simpler way(only works if the coefficient of x^2 is 1) or the more complex way that works for almost all cases? Press 'y' for option 1 or 'n' for option 2\n";
			cin >> decision2;
			if (decision2 == 'y')
			{
				char decision3;
				cout << "The simple way:\n";
				cout << "In order to find the value of y and z (x [+ or -] y)(x [+ or -] z), you need to find 2 numbers that multiply to get c. Those same 2 numbers must add to get b. One of those numbers will be y the other z.\n";
				cout << "For example:\n";
				cout << "1x^2 + 6x + 8. Two numbers that multiply to get 8 could be 1 and 8, 2 and 4 and that's it (there is also negative numbers such as -1 and -8, -2 and -4). The only one that adds to get 6 (b) is 4 and 2.\n";
				cout << "Therefore, if you factorise the expression properly, you will get: (x + 2)(x + 4)\n";
				cout << "That is the simpler way. Press any key to continue.\n";
				cin >> decision3;
				process = true;
			}
			if (decision2 == 'n')
			{
				cout << "The more complex way:\n";
				cout << "This method will require you to know the formula to find the value of x. The formula is:\n";
				cout << "{-b + or - sqrt(b^2 - 4ac)} / 2a\n";
				cout << "All you have to do is plug in the values of a, b and c and you will find x.\n";
				cout << "Now to actually factorise the expression, you will need to distinguish the numerator from the denominator which isn't particularly tasking.\n";
				cout << "The numerator is -b + or - sqrt(b^2 - 4ac) and the denominator is 2a. There are 2 answers for x. One when sqrt(b^2 - 4ac) is negative and when it is positive.\n";
				cout << "The first bracket will have ((the denominator which is 2a)) x - (the numerator when sqrt(b^2 - 4ac) is positive which will be -b + sqrt(b^2 - 4ac))))\n";
				cout << "The second bracket will be ((the denominator which is still 2a)) x - (the numerator when sqrt(b^2 - 4ac is negative which will be - b - sqrt(b^2 - 4ac))))\n";
				process = true;
			}
		}
		if (decision == 'n')
		{
			cout << "ax^2 + bx + c\n";
			double a;
			double b;
			double c;

			cout << "the value of a: ";
			cin >> a;
			cout << "the value of b: ";
			cin >> b;
			cout << "the value of c: ";
			cin >> c;
			cout << endl;

			double determinant = b * b - 4 * a * c;

			if (determinant < 0)
			{
				cout << "there was an error as this is not a solvable expression\n";
				process = true;
			}
			else {
				double x = (-b + sqrt(determinant)) / (2 * a);
				double negx = (-b - sqrt(determinant)) / (2 * a);

				cout << a * pow(x, 2) + b * x + c << endl;

				if (fabs(a * pow(x, 2) + b * x + c) < 1.e-12)
				{
					double topx = (-b + sqrt(determinant));
					double bottomx = (2 * a);
					double topnegx = (-b - sqrt(determinant));
					char convx = '+';
					Simplify mySimplify(round(topx), round(bottomx));
					mySimplify.simpFrac();
					cout << "(" << mySimplify.denominator << "x-" << mySimplify.numerator << ")";
					Simplify mySimplify2(round(topnegx), round(bottomx));
					mySimplify2.simpFrac();
					cout << "(" << mySimplify2.denominator << "x-" << mySimplify2.numerator << ")\n";

					cout << "x = " << x << " or " << negx << endl;
					process = true;
				}
			}
	
		}
	}
}