//
//  Person.hpp
//  password
//
//  Created by Brice Rosenzweig on 07/05/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <string>
using namespace std;

typedef enum {
    genderMale = 1,
    genderFemale = 2 } gender_t;

class Person{
public:
    Person(const string &_input_name, const string &_input_lastname, gender_t g);
    Person(const Person & other);
    ~Person();
    
    bool operator == (const Person & other) const;
    Person & operator = (const Person & other);
    
    // This function doesn't have const Person &
    bool isSameFamily(Person other)const;
    
    string asString()const;
    
    friend ostream & operator << (ostream & os, const Person & person);
private:
    string _name;
    string _lastname;
    gender_t _gender;
};

#endif /* Person_hpp */

