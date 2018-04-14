//
//  main.cpp
//  testcmdlinecpp
//
//  Created by Brice Rosenzweig on 07/06/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include <iostream>
using namespace std;

//------- USING C
struct CString {
    const char * _rep;
    size_t _size;
};

//
CString * CStringCreateNew(){
    CString * rv = (CString*)malloc(sizeof(CString));
    return rv;
}

void CStringInit( CString * p, const char * input_string, size_t input_size){
    p->_rep = input_string;
    p->_size = input_size;
}

const char * CStringCString(CString * p){
    return p->_rep;
}
//--------- USING C++
class CPPString {
private:
    const char * _rep;
    size_t _size;
public:
    CPPString(const char * input_string, size_t input_size){
        _rep = input_string;
        _size = input_size;
    }
    const char * cString() const{
        return _rep;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    // Using c
    CString * pointer_on_c = CStringCreateNew();
    CStringInit(pointer_on_c, "Hello World from c\n" , 5);
    printf("%s", CStringCString(pointer_on_c));
    
    // USing c++
    CPPString * pointer_on_str = new CPPString( "Hello from c++\n", 5);
    cout << "string " << pointer_on_str->cString() << endl;
    
    delete pointer_on_str;
    return 0;
}
