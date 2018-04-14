//
//  CppModule.cpp
//  miscexamples
//
//  Created by Brice Rosenzweig on 05/08/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//
extern "C" {
#include "CppModule.hpp"
}
class SampleCpp{
public:
    SampleCpp();
    ~SampleCpp();
    
    double compute(double x);
    unsigned size(const char * txt);
};


SampleCpp::SampleCpp(){
    
}
SampleCpp::~SampleCpp(){
    
}

double SampleCpp::compute(double x){
    return x * x;
}
unsigned SampleCpp::size(const char * txt){
    unsigned rv = 0;
    const char * k = txt;
    while( *k++ != 0){
        rv++;
    }
    return rv;
}
double c_compute(double x){
    SampleCpp c;
    return c.compute(x);
}
unsigned c_size(const char * txt){
    SampleCpp c;
    return c.size(txt);
}

