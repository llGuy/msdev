//
//  main.cpp
//  BisectionBrice
//
//  Created by Brice Rosenzweig on 15/10/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#include <iostream>
#include "Bisection.hpp"
#include "MathPolynom.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello Bisection!\n";
    
    MathPolynom * sqrt2 = new MathPolynom(1.0, 0.0, -2.0);
    
    Bisection * myBisection = new Bisection(1.0, 2.0, sqrt2);
    myBisection->solve();
    return 0;
}
