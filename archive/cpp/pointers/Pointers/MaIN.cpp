#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
	int n[5];
	int *bp0=&n[0];
	int *bp1=&n[1];
	int *bp2=&n[2];
	cout<<"bp0 is at "<<bp0<<endl;
	cout<<"bp1 is at "<<bp1<<endl;
	cout<<"bp2 is at "<<bp2<<endl;
	bp0++;
	cout<<"bp0 is now  at "<<bp0<<endl;
}
