//
//  main.cpp
//  ostreamlearning
//
//  Created by Brice Rosenzweig on 07/05/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include <iostream>
#include "Person.hpp"

int main(int argc, const char * argv[]) {
    Person bmr("brice", "rosenzweig", genderMale);
    Person lgr("luc", "rosenzweig", genderMale);
    Person yz("yi", "zhou", genderFemale);
    
    cout << bmr.isSameFamily(lgr) << endl;
    
    cout << bmr << endl;
    cout << lgr.asString() << endl;
    
    cout << yz << endl;
    
    return 0;
}
