//
//  Message.cpp
//  centauri
//
//  Created by Brice Rosenzweig on 19/01/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "Message.hpp"
#include <sstream>

const char * byte_to_binary(unsigned int x){
    static char buf[sizeof(int)*8+1] = {0};
    int y;
    long long z;
    for( z=1LL<<(sizeof(int)*8-1),y=0;z>0;z>>=1,y++){
        buf[y] = (((x&z)==z) ? '1' : '0');
    }
    buf[y] = 0;
    return buf;
}

const char * byte_to_binary_index(unsigned int x){
    static char buf[sizeof(int)*8+1] = {0};
    int y;
    long long z;
    for( z=1LL<<(sizeof(int)*8-1),y=0;z>0;z>>=1,y++){
        int x = (sizeof(int)*8-1-y);
        buf[y] = '0' + x%10;
    }
    buf[y] = 0;
    return buf;
}

void Message::debug_print()const{
    cout << *this << endl;
}
Message & Message::read(istream & is){
    for (size_t i = 0; i < _size / 16; i++) {
        is >> hex >> _rep[i];
    }
    return *this;
}
Message & Message::read(const char * str){
    istringstream is(str);
    return read(is);
}
ostream & operator<<(ostream & stream,const Message & m){
    
    if( (stream.flags() & stream.hex) == stream.hex ){
        ios_base::fmtflags flags = stream.flags();
        for(int i = 0; i < m._size / 16; i++) {
            if (i > 0) {
                stream << ' ';
            }
            stream << setfill('0') << setw(8) << hex << m._rep[i];
        }
        stream.flags(flags);
        
    }else{
        for(int i = 0; i < m._size / 16; i++) {
            if (i > 0) {
                stream << ' ';
            }
            stream << byte_to_binary(m._rep[i]);
        }
        
    }
    return stream;
}


