//
//  main.cpp
//  password
//
//  Created by Brice Rosenzweig on 29/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "stdafx.h"
#include <iostream>
#include "EntryManager.hpp"
#include "Encrypt.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    EntryManager thing;
    Entry one("poop", "asd");
    Entry two("pee", "hjk");
    thing.addEntry(one);
    thing.addEntry(two);
    thing.encryptToFile("/Users/brice/t.data");
    
    EntryManager newthing;
    newthing.decryptFromFile("/Users/brice/t.data");
    cout << newthing.asSavedString() << endl;
        
    return 0;
}
