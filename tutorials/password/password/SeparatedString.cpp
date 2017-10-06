//
//  SeparatedString.cpp
//  password
//
//  Created by Brice Rosenzweig on 30/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "stdafx.h"
#include "SeparatedString.hpp"

SeparatedString::SeparatedString(const string & s, const string & separator){
    _separatedString = s;
    _separator = separator;
}
SeparatedString::SeparatedString(const vector<string> & v,const string & separator ){
    _separatedString = "";
    _separator = separator;
    for (size_t i=0; i<v.size(); i++) {
        _separatedString += v[i];
        if(i+1<v.size()){
            _separatedString += separator;
        }
    }
}

vector<string> SeparatedString::asVector() const{
    vector<string> rv;
    size_t last = 0;
    size_t size = _separatedString.size();
    for (size_t current = 0;current <= size; current++) {
        if( current == size || _separatedString[current] == _separator[0] ){
            if( last < size){
                string one = _separatedString.substr(last, current - last);
                rv.push_back(one);
                last = current+1;
            }
        }
    }
    return rv;
}
string SeparatedString::asString() const{
    return _separatedString;
}
