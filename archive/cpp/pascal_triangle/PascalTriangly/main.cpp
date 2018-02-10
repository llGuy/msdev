#include <iostream>

using namespace std;

int main() {

	const int firstLineArraySize = 1;
	const int secondLineArraySize = 2;


	int nthArray;
	cout <<"Enter size ";
	cin >> nthArray;

	int prevSizeOfArray = 2;
	int nextSizeOfArray = 3;

	int *prevArray = new int[nthArray];
	int *nextArray = new int[nthArray];

	if(nthArray > 2) {
		
		prevArray[0] = 1;
		prevArray[1] = 1;
		for(int i = 3; i <= nthArray; i++) {
			nextSizeOfArray = prevSizeOfArray + 1;
			for(int y = 0; y < nextSizeOfArray; y++) {
				if(y == 0 || y == nextSizeOfArray - 1) {
					nextArray[y] = 1;
				}
				else {
					nextArray[y]=prevArray[y]+prevArray[y-1];
				}
			}
			for(int x=0; x<nextSizeOfArray; x++) {
				cout << nextArray[x] << " ";
			}
			cout << endl;
			prevSizeOfArray = nextSizeOfArray;

			int * saveNextArray = nextArray;
			nextArray = prevArray;
			prevArray = saveNextArray;
			
		}
	}

}
