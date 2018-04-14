//
//  Encrypt.cpp
//  password
//
//  Created by Brice Rosenzweig on 29/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "stdafx.h"
#include "Encrypt.hpp"

Encrypt::Encrypt(const string & key){
    _key = key;
}
Encrypt::~Encrypt(){
    
}

string Encrypt::encrypt(const string & encrypted_str) const{
    string processed = encrypted_str;
    size_t keySize = _key.size();
    for (size_t i=0; i<processed.size(); i++) {
        processed[i] ^= _key[i%keySize];
    }
    
    return processed;
}
string Encrypt::decrypt(const string & str) const{
    return this->encrypt(str);
}
