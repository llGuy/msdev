//
//  MathFunction.hpp
//  BisectionBrice
//
//  Created by Brice Rosenzweig on 15/10/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#ifndef MathFunction_hpp
#define MathFunction_hpp

#include <stdio.h>

class MathFunction{
    
public:
    virtual double valueFor(double x) = 0;
    
};
#endif /* MathFunction_hpp */
