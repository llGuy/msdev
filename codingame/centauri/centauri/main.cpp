//
//  main.cpp
//  centauri
//
//  Created by Brice Rosenzweig on 07/01/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "Message.hpp"
#include "Charles.hpp"

using namespace std;


int main(){
    Message ce(128);
    
    ce.read("541a4231 5d324646 27219a26 12497b0e 724eddcb 0e131617 9521bedf 55544dc7");
    vector<Message> solution = ce.decode();
    for(size_t i=0;i<solution.size();i++){
        cout << hex << solution[i] << endl;
    }
    
    Message ab(256);
    ab.read("4af6fc33 39029380 465c5267 c72f6a8b 0906e6d0 ca60550f 14a5e47c 42ad10fb 4a3bb446 bb74360a 5ea02b9c 23c68553 3fade253 e270ba24 39e141ad 6c38c43d");
    int n = 1;
    
    clock_t t0 = clock();
    for( int i =0 ;i<n; i++){
        ab.decode();
    }
    std::cerr << "m time: " << float(clock()-t0)/CLOCKS_PER_SEC/n << " second(s)\n";
    
    t0 = clock();
    for( int i =0 ;i<n; i++){
        decrypt(256, "4af6fc33 39029380 465c5267 c72f6a8b 0906e6d0 ca60550f 14a5e47c 42ad10fb 4a3bb446 bb74360a 5ea02b9c 23c68553 3fade253 e270ba24 39e141ad 6c38c43d");
    }
    std::cerr << "c time: " << float(clock()-t0)/CLOCKS_PER_SEC/n << " second(s)\n";

}
