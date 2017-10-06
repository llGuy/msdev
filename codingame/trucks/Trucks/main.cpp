//
//  main.cpp
//  Trucks
//
//  Created by Brice Rosenzweig on 11/09/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "Trucks.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream ins("/Users/brice/Development/msdev/codingame/trucks/20Trucks.csv");
    Payload payload(ins);
    cout << payload.weight() <<  " " << payload.size() << endl;
    Convoy convoy(20);
    convoy.fill(payload);
    cout << convoy << endl;
    cout << convoy.max_range_diff() << endl;
    return 0;
}
