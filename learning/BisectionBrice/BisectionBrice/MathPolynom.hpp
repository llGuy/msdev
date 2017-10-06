//
//  MathPolynom.hpp
//  BisectionBrice
//
//  Created by Brice Rosenzweig on 15/10/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#ifndef MathPolynom_hpp
#define MathPolynom_hpp
#include "MathFunction.hpp"
#include <stdio.h>

class MathPolynom : public MathFunction{
private:
    double _a;
    double _b;
    double _c;
    
public:
    MathPolynom(double a, double b, double c);
    ~MathPolynom();
    
    double valueFor(double x );
    
};

#endif /* MathPolynom_hpp */
