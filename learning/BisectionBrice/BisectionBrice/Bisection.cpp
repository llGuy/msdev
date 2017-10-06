//
//  Bisection.cpp
//  BisectionBrice
//
//  Created by Brice Rosenzweig on 15/10/2016.
//  Copyright © 2016 Brice Rosenzweig. All rights reserved.
//

#include "Bisection.hpp"
#include <iostream>
#include <math.h>

using namespace std;

Bisection::Bisection(double initial_x0, double initial_x1, MathFunction * func){
    _x0 = initial_x0;
    _x1 = initial_x1;
    _function = func;
}
Bisection::~Bisection(){
    
}

double Bisection::solve(){
    cout << "Solving started1" << endl;
    printf("f( [ %f,%f ] ) = [ %f, %f]\n", _x0,_x1,targetFunction(_x0),targetFunction(_x1));

    while( fabs( _x0-_x1)> 1.0e-6){
        double middle = (_x0+_x1)/2.0;
        
        double valueAtMiddle = targetFunction(middle);
        
        printf( "[%f,%f] f( %f ) = %f\n", _x0, _x1, middle, valueAtMiddle);
        if( valueAtMiddle > 0.0){
            _x1 = middle;
        }else{
            _x0 = middle;
        }
    }
    return 0.;
}


double Bisection::targetFunction( double x){
    return _function->valueFor(x);
}
