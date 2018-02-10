#include <iostream>
#include <string>
#include "SCR_Encoder.h"

using namespace std;

const char * char_to_binary(char x){
    static char buf[sizeof(char)*8+1] = {0};
    int y;
    long long z;
    for( z=1LL<<(sizeof(char)*8-1),y=0;z>0;z>>=1,y++){
        buf[y] = (((x&z)==z) ? '1' : '0');
    }
    buf[y] = 0;
    return buf;
}



unsigned char br_encode_decode(unsigned char input,bool decode){
    size_t order_[8] = {2,0,7,5,6,1,4,3};
    size_t order[8] ;
    for (size_t i=0; i<8; i++) {
        if( decode){
            order[ 7-order_[i]] = 7-i;
        }else{
            order[ i]= order_[i];
        }
    }
    char output = 0x00;
    
    for (size_t i=0; i<8; i++) {
        size_t from = 7-i;
        size_t to = order[i];
        unsigned char from_bit = input & (1<<from);
        unsigned char to_bit = (from_bit>>from) ;
        to_bit = to_bit << to;
        output |= to_bit;
    }
    return output;
}

unsigned char br_encode(unsigned char input){
    return br_encode_decode(input, false);
}
unsigned char br_decode(unsigned char input){
    return br_encode_decode(input, true);
}


int main()
{
    string input = string("cryptography");
	SCR_Encoder Encoder = input;
	Encoder.DefineArrOrder("20756143");
	string thing = Encoder.EncodeInput();
	cout << "cryptography = " << thing << endl;
	cout << thing.length() << endl;
    
    for (int i = 0; i < input.length(); i++){
        char c = input[i];
        cout <<c << ": "<< char_to_binary(c) << " "<< char_to_binary(br_encode(c))  << " "
        << char_to_binary(br_decode(br_encode(c))) << " " << br_decode(br_encode(c)) << endl;
    }
    cout<<endl;
	for (int i = 0; i < thing.length(); i++){
        if( i < input.length()){
            cout << i << ": " << input[i] << " " << br_decode(thing[i]) << " " << Encoder.BinaryConverter(thing[i]) << endl;
        }else{
            cout << i << ": " << Encoder.BinaryConverter(thing[i]) << endl;
        }
	}
}
	
