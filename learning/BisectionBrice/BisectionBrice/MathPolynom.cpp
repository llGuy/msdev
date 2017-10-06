//
//  MathPolynom.cpp
//  BisectionBrice
//
//  Created by Brice Rosenzweig on 15/10/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#include "MathPolynom.hpp"

MathPolynom::MathPolynom(double a, double b, double c){
    _a = a;
    _b = b;
    _c = c;
}
MathPolynom::~MathPolynom(){
    
}

double MathPolynom::valueFor(double x ){
    return _a * x * x + _b * x + _c;
}
