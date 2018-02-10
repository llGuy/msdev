#include <iostream>
#include <string>
#undef cimg_display
#define cimg_display 0
#include "LSB_Encoding.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;

typedef unsigned char byte_t;

const char * byte_to_binary(byte_t x) {
	static char buf[sizeof(byte_t)*8+1] ={ 0 };
	int y;
	long long z;
	for(z=1LL<<(sizeof(byte_t)*8-1),y=0; z>0; z>>=1,y++) {
		buf[y] = (((x&z)==z) ? '1' : '0');
	}
	buf[y] = 0;
	return buf;
}
int main() {
	LSB_Encoding thing = "poop";
	unsigned _temp = 98;
	unsigned x = 5;
	
	thing.ModByte(_temp,thing.GetNthBit(x,_temp));
	cout << byte_to_binary(_temp) << endl << byte_to_binary(thing.ModByte(_temp,0)) << endl;

	/*
	//data() returns pointer of the first byte (red value of the first pixel of the picture)
	byte_t * p = image.data();		
	size_t size = image.width() * image.height() * 3; // R, G, B = 3
	cout << "Maximum " << size << " or " << size/8 << " char" << endl;
	cout << (unsigned)p[0] << endl << p[1] << endl << p[2] << endl;
	unsigned myBinary = 0b01100001;
	myBinary |= 0b00000010;
	cout << byte_to_binary(myBinary) << endl;
	for(size_t i=0; i<size; i++) {
		//p[i]/=2;
	}
	image.save("C:\\Users\\luc\\Desktop\\Programs\\C++\\Luc_Derp_output.bmp");]*/
}