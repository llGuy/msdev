#include <string>
#include <iostream>

using namespace std;

//Various definitions and prototype.

void binaryConv(int letter);		
int temp;
int binary[7];
int number;

int main()
{
	bool process = true;		
	while (process)					//While loop that makes the program run repeatedly.
	{
		int a = 97;					//Ascii equivalent of letters (Dec).
		int b = 98;
		int c = 99;
		int d = 100;
		int e = 101;
		int f = 102;
		int g = 103;
		int h = 104;
		int ii = 105;
		int j = 106;
		int k = 107;
		int l = 108;
		int m = 109;
		int n = 110;
		int o = 111;
		int p = 112;
		int q = 113;
		int r = 114;
		int s = 115;
		int t = 116;
		int u = 117;
		int v = 118;
		int w = 119;
		int x = 120;
		int y = 121;
		int z = 122;

		
		string word;

		cin >> word;

		int arraySize = word.length();			
		int *asciArray = new int[word.length()];		//Creates an array with no constant.	

			for (int i = 0; i < word.length(); i++)		//For loop : Goes through each letter.
			{
				switch (word.at(i))
				{
				case 'a':
					binaryConv(a);
					break;
				case 'b':
					binaryConv(b);
					break;
				case 'c':
					binaryConv(c);
					break;
				case 'd':
					binaryConv(d);
					break;
				case 'e':
					binaryConv(e);
					break;
				case 'f':
					binaryConv(f);
					break;
				case 'g':
					binaryConv(g);
					break;
				case 'h':
					binaryConv(h);
					break;
				case 'i':
					binaryConv(ii);
					break;
				case 'j':
					binaryConv(j);
					break;
				case 'k':
					binaryConv(k);
					break;
				case 'l':
					binaryConv(l);
					break;
				case 'm':
					binaryConv(m);
					break;
				case 'n':
					binaryConv(n);
					break;
				case 'o':
					binaryConv(o);
					break;
				case 'p':
					binaryConv(p);
					break;
				case 'q':
					binaryConv(q);
					break;
				case 'r':
					binaryConv(r);
					break;
				case 's':
					binaryConv(s);
					break;
				case 't':
					binaryConv(t);
					break;
				case 'u':
					binaryConv(u);
					break;
				case 'v':
					binaryConv(v);
					break;
				case 'w':
					binaryConv(w);
					break;
				case 'x':
					binaryConv(x);
					break;
				case 'y':
					binaryConv(y);
					break;
				case 'z':
					binaryConv(z);
					break;
				case '-':
					process = false;
					break;
		
				};
				
			}
	}
}

//Func : Conversion from letters to binary code.

void binaryConv(int letter)
{
	temp = letter;
	for (int y = 0; y < 7; y++)
	{

		binary[y] = temp % 2;
		temp = temp / 2;

	}
	for (int y = 6; y > -1; y--)
	{
		cout << binary[y];
	}cout << endl;
}

