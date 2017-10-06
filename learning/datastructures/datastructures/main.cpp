//
//  main.cpp
//  datastructures
//
//  Created by Brice Rosenzweig on 26/12/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "Vector.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    Vector muyVector;
    muyVector.addElement(42);
    cout << muyVector << endl;
    muyVector.addElement(42*2);
    cout << muyVector << endl;
}
