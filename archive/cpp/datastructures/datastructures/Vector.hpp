//
//  Vector.hpp
//  datastructures
//
//  Created by Brice Rosenzweig on 26/12/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>
#include <iostream>

class Vector{
public:
    typedef double Element;
    
private:
    Element * _first;
    size_t _count;
    size_t _size;
    
    friend std::ostream & operator <<(std::ostream & os, const Vector & vec);
public:
    Vector();
    ~Vector();
    
    void addElement(const Element & newOne);
};


#endif /* Vector_hpp */
