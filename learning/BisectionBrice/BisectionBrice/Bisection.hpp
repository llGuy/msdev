//
//  Bisection.hpp
//  BisectionBrice
//
//  Created by Brice Rosenzweig on 15/10/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#ifndef Bisection_hpp
#define Bisection_hpp

#include <stdio.h>
#include "MathFunction.hpp"


class Bisection{
private:
    double _x0;
    double _x1;
    MathFunction * _function;
public:
    Bisection(double initial_x0, double initial_x1, MathFunction * target);
    ~Bisection();
    
    double solve();
    double targetFunction( double x);
};

#endif /* Bisection_hpp */
