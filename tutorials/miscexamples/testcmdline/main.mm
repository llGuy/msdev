//
//  main.m
//  testcmdline
//
//  Created by Brice Rosenzweig on 07/06/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

// This is the include for the c function printf
#include <stdio.h>

// This is like include for all the objective c type (NSString, NSArray, etc)
#import <Foundation/Foundation.h>

// This is the include for the c++ types: cout, string, etc
#include <iostream>
#include <string>

using namespace std;

//------- USING C -------------------
// Internally BOTH objective c and c++ will create a c struct like
// this one with variables in it
struct CString {
    const char * _rep;
    size_t _size;
};

// c only has struct, and function/creation etc done in independent function
// that takes pointer as argument
CString * CStringCreateNew(){
    CString * rv = (CString*)malloc(sizeof(CString));
    return rv;
}
void CStringFree(CString * p){
    free(p);
}
// a function that initialize the struct
void CStringInit( CString * p, const char * input_string, size_t input_size){
    p->_rep = input_string;
    p->_size = input_size;
}
// a function that returns a const char * from the struct
const char * CStringCString(CString * p){
    return p->_rep;
}
//--------- USING C++ -------------------
typedef enum {
   eWordTypeUnknown = 0,
    eWordTypeNoun = 1,
    eWordTypeAdjective = 2
} eWordType;

class CPPWord {
protected:
    // the variable in the class (class is like a struct actually)
    const char * _rep;
    size_t _size;
    
    eWordType _type;
   
public:
    // the constructor
    CPPWord(const char * input_string, size_t input_size){
        _rep = input_string;
        _size = input_size;
    }
    //the function cString
    const char * cString() const{
        return _rep;
    }
    
    virtual bool isBefore(const CPPWord * other){
        return false;
    }
    
    eWordType type() const{
        return _type;
    }
};

class CPPWordNoun : public CPPWord {
public:
    CPPWordNoun(const char * input_string, size_t input_size)
    :CPPWord(input_string, input_size){
        _type = eWordTypeNoun;
    }
    virtual bool isBefore(const CPPWord * other){
        if( other->type() == eWordTypeAdjective){
            return true;
        }
        return false;
    }
};

class CPPWordAdjective : public CPPWord {
public:
    CPPWordAdjective(const char * input_string, size_t input_size)
    :CPPWord(input_string, input_size){
        _type = eWordTypeAdjective;
    }
    virtual bool isBefore(const CPPWord* other){
        if( other->type() == eWordTypeAdjective){
            return false;
        }
        return true;
    }
};

//------- USING Objective C -------------------
// Define a class in the objective c
@interface OBJCWord : NSObject

// the variable in the struct.
@property const char* rep;
@property size_t size;

// the functions that are declared
-(OBJCWord*)initWithCString:(const char*)input_string andSize:(size_t)input_size;
-(const char*)cString;

@end

@implementation OBJCWord
// Implementation of the Constructor/init function
-(OBJCWord*)initWithCString:(const char*)input_string andSize:(size_t)input_size{
    self = [super init];
    self.rep = input_string;
    self.size = input_size;
    return self;
}
// Implementation of the function cString that returns a const char *
-(const char*)cString{
    return self.rep;
}

@end



int main(int argc, const char* argv[]) {
    // DO THE Same in different c related languages:
    
    // Using c
    CString* pointer_on_c = CStringCreateNew();            // Create the c object
    CStringInit(pointer_on_c, "Hello from c\n" , 5);        // Initialize the c object with a constant
    printf("%s", CStringCString(pointer_on_c));             // call the function CString that returns const char* for printf
    CStringFree(pointer_on_c);                              // free the pointer
    
    // USing c++
    CPPWord* pointer_on_noun = new CPPWordNoun( "horse", 5);   // Create and initialize the c++ object wiht a constant
    CPPWord* pointer_on_adjective = new CPPWordAdjective( "big", 3);   // Create and initialize the c++ object wiht a constant
    cout << pointer_on_noun->isBefore(pointer_on_adjective) << endl;                          // Call the function cString() to print with cout
    cout << pointer_on_adjective->isBefore(pointer_on_adjective) << endl;                          // Call the function cString() to print with cout
    delete pointer_on_noun;                                              // delete (free) the pointer
    delete pointer_on_adjective;
    
    // using c++ native
    string cpp_str("Hello from c++ Native");
    cout << cpp_str << endl;
    // string is automatically delete
    
    // using objective c
    // Create (allocate) the object (it's a c struct internally) and initializes
    OBJCWord* pointer_on_objc = [[OBJCWord alloc] initWithCString:"Hello from Objective C" andSize:5];
    printf("%s\n", [pointer_on_objc cString]); // call the function cString on the object
    // Objective C free automatically the pointer
    
    // using objective c internal types
    NSString* objc_str = @"Hello from Objective C Native";
    printf("%s\n", [objc_str cStringUsingEncoding:NSUTF8StringEncoding]);
    
    return 0;
}
