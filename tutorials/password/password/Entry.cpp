//
//  Entry.cpp
//  password
//
//  Created by Brice Rosenzweig on 29/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "stdafx.h"
#include "Entry.hpp"
#include "SeparatedString.hpp"

const string kNameSeparator = ",";

Entry::Entry(const string & u, const string & p){
    _username = u;
    _password = p;
}

Entry & Entry::operator =(const Entry & o){
    _username = o._username;
    _password = o._password;
    return *this;
}
Entry::Entry(const Entry & o){
    _username = o._username;
    _password = o._password;
}
Entry::~Entry(){
    
}

string Entry::toSavedString() const{
    return _username + kNameSeparator + _password;
}

void Entry::fromSavedString(const string & s){
    SeparatedString ss(s, kNameSeparator);
    vector<string> v= ss.asVector();
    if( v.size() == 2){
        _username = v[0];
        _password = v[1];
    }
}
