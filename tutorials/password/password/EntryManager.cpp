//
//  EntryManager.cpp
//  password
//
//  Created by Brice Rosenzweig on 30/04/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "EntryManager.hpp"
#include "Encrypt.hpp"

#include "SeparatedString.hpp"

const string kEntrySeparator = ";";
const string kEncryptKey = "jasd@3irf24ASD32";

EntryManager::EntryManager(){
    _capacity = 10;
    _size = 0;
    _entries = new Entry[_capacity];
}
EntryManager::~EntryManager(){
    delete [] _entries;
}

void EntryManager::addEntry(const Entry & one){
    size_t found = 0;
    for (found=0; found<_size; found++) {
        if( _entries[found].isSameUsername(one)){
            break;
        }
    }
    if( found < _size){
        _entries[found].updateWith(one);
    }else{
        if( _size+1>=_capacity){
            Entry * tmp = new Entry[_capacity * 2];
            for (size_t i=0; i<_capacity; i++) {
                tmp[i] = _entries[i];
            }
            delete [] _entries;
            _entries = tmp;
            _capacity *= 2;
        }
        _entries[_size++].updateWith(one);
    }
}
Entry * EntryManager::findEntryForName(const string & name){
    for (size_t i=0; i<_size; i++) {
        if( _entries[i].isSameUsername(name)){
            return &(_entries[i]);
        }
    }
    return NULL;
}
string EntryManager::asSavedString() const{
    vector<string> v;
    for (size_t i=0; i<_size; i++) {
        v.push_back(_entries[i].toSavedString());
    }
    SeparatedString ss(v, kEntrySeparator);
    return ss.asString();
}
void EntryManager::fromSavedString(const string & s){
    SeparatedString ss(s, kEntrySeparator);
    vector<string> v = ss.asVector();
    
    _size = v.size();
    _capacity = _size * 2;

    delete [] _entries;
    
    _entries = new Entry[_capacity];
    for (size_t i=0; i<v.size(); i++) {
        _entries[i].fromSavedString(v[i]);
    }
}

void EntryManager::encryptToFile(const string & filename)const{
    ofstream of(filename, ofstream::trunc|ofstream::binary);
    Encrypt enc(kEncryptKey);
    of << enc.encrypt( asSavedString() );
}
void EntryManager::decryptFromFile(const string & filename){
    ifstream ifs(filename, ifstream::binary);
    string read;
    
    while( ifs ){
        char c;
        ifs.get(c);
        read.push_back(c);
    }
    Encrypt enc(kEncryptKey);

    fromSavedString(enc.decrypt(read));
    
}

