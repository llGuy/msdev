//
//  main.cpp
//  stegano
//
//  Created by Brice Rosenzweig on 13/05/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include <iostream>
// Import the cimg library
#undef cimg_display
#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;
using namespace std;


typedef unsigned char byte_t;

// Helper function to print a number in binary
const char * byte_to_binary(byte_t x){
    static char buf[sizeof(byte_t)*8+1] = {0};
    int y;
    long long z;
    for( z=1LL<<(sizeof(byte_t)*8-1),y=0;z>0;z>>=1,y++){
        buf[y] = (((x&z)==z) ? '1' : '0');
    }
    buf[y] = 0;
    return buf;
}

typedef enum {
    kBigEndian,
    kLittleEndian
}Endianness;

class LSBEncoding {
private:
    size_t _size;
    byte_t * _buffer;
    Endianness _endianness;
public:
    LSBEncoding(byte_t * buf, size_t maxsize, Endianness endn = kLittleEndian) {
        _size = maxsize;
        _buffer = buf;
        _endianness = endn;
    };
    ~LSBEncoding(){};
    
    
    void encode(const string & s){
        size_t k=0;
        for (size_t i=0; i<s.length(); i++) {
            
            for (size_t bit = 0; bit<8; bit++) {
                
                size_t shift_bit = _endianness == kLittleEndian ? bit : 7-bit;
                
                // check the image is big enough to save all the bits.
                // extra 8 bit for the last 0
                if( k < _size - 8){
                    if( s[i] & (1<<shift_bit) ){
                        _buffer[k++] |= 1;
                    }else{
                        _buffer[k++] &= 0b11111110;
                    }
                }
            }
        }
        // Create a 0 bit for the end
        for (size_t bit = 0; bit<8; bit++) {
            _buffer[k++] &= 0b11111110;
        }
    }
    string decode(){
        string rv;
        char recreated = 0;
        
        for (size_t i=0; i<_size; i++) {
            byte_t val = _buffer[i] & 1;
            size_t bit = i % 8;
            if(_endianness == kBigEndian){
                bit = 7-bit;
                recreated |= val << bit;
            }

            if( bit == 0 && i > 0){ // finished one character
                if( recreated == 0){
                    break;
                }else{
                    rv.push_back(recreated);
                }
                recreated = 0;
            }
            if( _endianness == kLittleEndian){
                recreated |= val << bit;
            }
        }
        return rv;
    }
};

void demo_binary(){
    CImg<byte_t> img("/Users/brice/Downloads/IMG.bmp");
    byte_t * p = img.data();
    size_t size = img.width() * img.height()*3;
    for( size_t i=0;i <size; i++){
        // &= will do bit wise and,
        // so below will turn off the 0th bit
        byte_t new_value = p[i] & 0b11111110;
        if( i < 10){
            cout << hex << (unsigned)p[i] << " " << byte_to_binary(p[i]) << " -> " << (unsigned)new_value << " " << byte_to_binary(new_value) << endl;
        }
        //p[i] = new_value;
    }
    
    // To save the image
    //img.save("/Users/brice/Downloads/IMGc.bmp");
    
    cout << "..." << endl;
    
    string message("secret message");
    
    // Show all the letter in number/binary
    for (size_t i=0; i<message.length(); i++) {
        char c = message[i];
        cout << c << " " << hex << (int)c << " " << byte_to_binary(c) << endl;
    }
    char c = message[0]; // s
    cout << endl;
    // How to extract information from a number
    cout << "looking at '" << c << "' " << hex << (int)c << " " << byte_to_binary(c) << endl;
    
    for (size_t i=0; i<8; i++) {
        byte_t ith_bit = (1 << i);
        
        bool ith_bit_is_set = ith_bit & c;
        cout << i << " " << byte_to_binary(ith_bit) << " set = " << (int)ith_bit_is_set << endl;
    }
    
    // start with a char that is all zero
    char recreate = 0;
    cout << "start:  " << byte_to_binary(recreate) << endl;
    cout << "target: " << byte_to_binary(c) << endl;
    for (size_t i=0; i<8; i++) {
        byte_t ith_bit = (1 << i);
        
        bool ith_bit_is_set = ith_bit & c;
        
        if( ith_bit_is_set){
            
            cout << i << " is set     " << byte_to_binary(recreate) << "|" << byte_to_binary(ith_bit) << "="<<byte_to_binary(recreate|ith_bit) << endl;
            recreate |= ith_bit;
        }else{
            cout << i << " is not set " << byte_to_binary(recreate) << " unchanged" << endl;
        }
    }
    cout << "recreated  '" << recreate << "' " << hex << (int)recreate << " " << byte_to_binary(recreate) << endl;
    
}

void demo_encode(const char * fn){
    CImg<byte_t> img(fn);
    byte_t * p = img.data();
    size_t size = img.width() * img.height()*3;

    LSBEncoding enc(p,size, kBigEndian);
    enc.encode("Bravo, tu es trop un hacker hard core!!! Tu as merite que je t'emmene a ippudo... L'image d'avant ne marchais pas: google 'big endian vs little endian' pour comprendre. ");
    
    img.save("/Users/brice/Downloads/IMGd.bmp");
    
}

void demo_decode(const char * fn){
    CImg<byte_t> img2(fn);
    LSBEncoding dec(img2.data(), img2.width()*img2.height()*3, kBigEndian);
    
    string msg = dec.decode();
    cout << "Message : "<< msg << endl;
    
}

int main(int argc, const char * argv[]) {
    //demo_encode("/Users/brice/Downloads/IMG.bmp");
    demo_decode("/Users/brice/Downloads/LUCCOPY.bmp");
    
    
    return 0;
}
