//
//  Entry.hpp
//  password
//
//  Created by Brice Rosenzweig on 29/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#ifndef Entry_hpp
#define Entry_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Entry{
public:
    Entry(const string & u = "", const string & p = "");
    Entry(const Entry & o);
    ~Entry();
    
    Entry & operator =(const Entry & o);
    
    bool isSameUsername( const Entry & o)const{
        return _username == o._username;
    }
    void updateWith( const Entry & o ){
        _username = o._username;
        _password = o._password;
    }
    
    string toSavedString() const;
    void fromSavedString(const string & s);
private:
    string _username;
    string _password;
    
};

#endif /* Entry_hpp */
