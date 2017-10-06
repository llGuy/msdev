//
//  main.cpp
//  Compiler
//
//  Created by Brice Rosenzweig on 05/08/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "LinkedList.h"
#include "Variable.h"
#include "VarLists.h"
#include "CodeLine.h"
#include "CompilerTests.h"
#include "Vector.h"
#include "Miscellaneous.h"
#include "CalcParsing.h"
#include <iostream>

using namespace std;

int main() {
    std::cout << "Started" << std::endl;
    CompilerTests::Run();
    //CalcParser thing("12 * (3 + 4)");
    //std::cout << thing.Reduce("1 + (1 + (1 + 1))","","");
}
