//
//  SeparatedString.hpp
//  password
//
//  Created by Brice Rosenzweig on 30/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#ifndef SeparatedString_hpp
#define SeparatedString_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class SeparatedString{
public:
    SeparatedString(const string & s, const string & separator = ",");
    SeparatedString(const vector<string> & v, const string & separator = ",");
    
    vector<string> asVector() const;
    string asString() const;
    
private:
    string _separatedString;
    string _separator;
};
#endif /* SeparatedString_hpp */
