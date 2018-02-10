//
//  Vector.cpp
//  datastructures
//
//  Created by Brice Rosenzweig on 26/12/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#include "Vector.hpp"

Vector::Vector(){
    _count = 0;
    _size = 16;
    _first=new Element[_size];
    
}
Vector::~Vector(){
    delete _first;
}
void Vector::addElement(const Element & newOne){
    if(_count>=_size){
        _size=_size*2;
        Element * _temp=new Element[_size];
        for (int num=0; num<_count; num++) {
            _temp[num]=_first[num];
        }
        delete _first;
        _first=_temp;
        
    }
    _first[_count]=newOne;
    _count+=1;
}

std::ostream & operator <<(std::ostream & os, const Vector & vec){
    os << "Vector[";
    for (size_t i=0; i<vec._count; i++) {
        os << vec._first[i];
        if( i != vec._count-1){
            os << ", ";
        }
    }
    os << "]";
    return os;
}
