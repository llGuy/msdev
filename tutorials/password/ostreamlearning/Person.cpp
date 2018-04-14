//
//  Person.cpp
//  password
//
//  Created by Brice Rosenzweig on 07/05/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "Person.hpp"
#include <iostream>

using namespace std;

Person::Person(const string &_input, const string & _input_lastname, gender_t gender){
    cout << "++Calling Person::Person(const string &_input, const string & _input_lastname)" << endl;
    _name = _input;
    _lastname = _input_lastname;
    _gender = gender;
    
}

Person::Person(const Person & other){
    cout << "++Calling Person::Person(const Person & other)" << endl;
    _name = other._name;
    _lastname = other._lastname;
    _gender = other._gender;
}
Person::~Person(){
    
}

bool Person::operator == (const Person & other) const{
    cout << "++Calling Person::operator == (const Person & other)" << endl;
    return _name == other._name && _lastname == other._lastname && _gender == other._gender;
    
}
Person & Person::operator = (const Person & other){
    cout << "++Calling Person::operator = (const Person & other)" << endl;
    _name = other._name;
    _lastname = other._lastname;
    _gender = other._gender;
    return *this;
}

bool Person::isSameFamily(Person other)const{
    cout << "++Calling Person::isSameFamily(Person other)const" << endl;
    return _lastname == other._lastname;

}

string Person::asString()const{
    cout << "++Calling Person::asString()const" << endl;
    return _name + " " + _lastname;
}

ostream & operator << (ostream & os, const Person & person){
    cout << "++Calling operator << (ostream & os, const Person & person)" << endl;
    string toOutput = person.asString();
    os << toOutput << " (" << person._gender << ")";
    return os;
}
