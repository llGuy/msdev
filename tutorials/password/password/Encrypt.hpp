//
//  Encrypt.hpp
//  password
//
//  Created by Brice Rosenzweig on 29/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#ifndef Encrypt_hpp
#define Encrypt_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Encrypt{
public:
    Encrypt(const string & key);
    ~Encrypt();
    
    string encrypt(const string & encrypted_str) const;
    string decrypt(const string & str) const;
    
private:
    string _key;
    
};

#endif /* Encrypt_hpp */
