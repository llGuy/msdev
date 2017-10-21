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

void game_output(ifstream & ins){
    Payload payload(ins);
    Convoy convoy(100);
    convoy.fill(payload);
    vector<id_t> rv = convoy.box_allocation();
    for (size_t i=0; i<rv.size(); i++) {
        cout << rv[i] << endl;
    }
}

void test_run(ifstream & ins){
    Payload payload(ins);
    cout << payload.size() << endl;
    cout << payload.front()<< endl;
    cout << payload.back()<< endl;
    //cout << payload.weight() <<  " " << payload.size() << endl;
    Convoy convoy(100);
    convoy.fill(payload);
    cout << convoy << endl;
    //cout << convoy.max_range_diff() << endl;
    cout << convoy.box_allocation().size() << endl;
    //cout << payload.size() << endl;

}
int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream ins("/Users/brice/Development/msdev/codingame/trucks/trucks_1.csv");
    test_run(ins);
    return 0;
        
}
