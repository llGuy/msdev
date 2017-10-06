//
//  EntryManager.hpp
//  password
//
//  Created by Brice Rosenzweig on 30/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#ifndef EntryManager_hpp
#define EntryManager_hpp

#include <stdio.h>
#include "Entry.hpp"

using namespace std;

class EntryManager{
public:
    EntryManager();
    ~EntryManager();
    
    void addEntry(const Entry & one);
    // Returns null if not found
    Entry * findEntryForName(const string & name);
    
    string asSavedString() const;
    void fromSavedString(const string & s);
    
    void encryptToFile(const string & filename)const;
    void decryptFromFile(const string & filename);
    
private:
    size_t _capacity;
    size_t _size;
    Entry * _entries;
};
#endif /* EntryManager_hpp */
