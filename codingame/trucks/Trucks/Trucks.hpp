//
//  Trucks.hpp
//  Trucks
//
//  Created by Brice Rosenzweig on 11/09/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#ifndef Trucks_hpp
#define Trucks_hpp

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <istream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <unordered_map>


using namespace std;
typedef float weight_t;
typedef float volume_t;
typedef unsigned id_t;

const volume_t kTruckMaxVolume = 100;

class Box {
private:
    id_t m_id;
    weight_t m_weight;
    volume_t m_volume;
    
public:
    Box(istream & ss):m_id(0),m_weight(0),m_volume(0){
        if( ss ){
            ss >> m_id;
            ss.ignore();
            ss >> m_weight;
            ss.ignore();
            ss >> m_volume;
            ss.ignore();
        }
    }
    
    bool valid() const { return m_id != 0; };
    id_t id() const { return m_id; };
    weight_t weight() const { return m_weight; };
    volume_t volume() const { return m_volume; };
    bool operator==(const Box & b) const { return m_id == b.m_id; };
    friend ostream &operator<<(ostream & os, const Box & box);
};


class Payload{
private:
    vector<Box> m_boxes;
public:
    typedef vector<Box>::iterator iterator;
    typedef vector<Box>::const_iterator const_iterator;

    Payload(){};
    Payload(istream & ins){
        // skip header
        ins.ignore(numeric_limits<streamsize>::max(),'\n');
        
        while( ins ){
            Box one(ins);
            if( one.valid() ){
                m_boxes.push_back(one);
            }
        }
    }
    
    iterator begin() { return m_boxes.begin(); };
    iterator end() { return m_boxes.end(); };
    const_iterator begin() const { return m_boxes.begin(); };
    const_iterator end() const { return m_boxes.end(); };

    size_t size() const{
        return m_boxes.size();
    }
    
    weight_t weight() const{
        weight_t rv = 0;
        for (vector<Box>::const_iterator it=m_boxes.begin(); it!=m_boxes.end(); it++) {
            rv += it->weight();
        }
        return rv;
    }

    volume_t volume() const{
        volume_t rv = 0;
        for (vector<Box>::const_iterator it=m_boxes.begin(); it!=m_boxes.end(); it++) {
            rv += it->volume();
        }
        return rv;
    }
    
    void sortByDecreasingWeight(){
        sort(m_boxes.begin(), m_boxes.end(), [](const Box & l, const Box & r) { return l.weight() > r.weight(); });
    }
    
    friend ostream &operator<<(ostream & os, const Payload & payload);
    bool remove(const Box & b){
        bool rv = false;
        vector<Box>::const_iterator it;
        for (it=m_boxes.begin(); it!=m_boxes.end(); it++) {
            if( b == *it){
                break;
            }
        }
        if( it != m_boxes.end()){
            m_boxes.erase(it);
            rv = true;
        }
        return rv;
    }
    bool add(const Box & b){
        bool rv = false;
        vector<Box>::const_iterator it;
        for (it=m_boxes.begin(); it!=m_boxes.end(); it++) {
            if( b == *it){
                break;
            }
        }
        if( it == m_boxes.end()){
            m_boxes.push_back(b);
            rv = true;
        }
        return rv;
    }
};


class Truck{
private:
    id_t m_id;
    Payload m_payload;
public:
    typedef Payload::iterator iterator;
    typedef Payload::const_iterator const_iterator;
    
    Truck(id_t i=0) : m_id(i),m_payload() {};
    bool has_space_for(const Box & box){ return m_payload.volume() + box.volume() < kTruckMaxVolume; };
    bool add(const Box & box){
        bool rv = false;
        if( has_space_for(box) ){
            rv = m_payload.add(box);;
        }
        return rv;
    }
    bool remove(const Box & box){
        return m_payload.remove(box);
    }
    volume_t volume() const { return m_payload.volume(); };
    weight_t weight() const { return m_payload.weight(); };
    id_t id() const { return m_id; };
    
    iterator begin() { return m_payload.begin(); };
    iterator end() { return m_payload.end(); };
    const_iterator begin() const{ return m_payload.begin(); };
    const_iterator end() const{ return m_payload.end(); };

    friend ostream &operator<<(ostream & os, const Truck & truck);
};

class Convoy{
private:
    vector<Truck> m_trucks;
    volume_t m_max_weight;
public:
    typedef vector<Truck>::iterator iterator;
    typedef vector<Truck>::const_iterator const_iterator;
    Convoy(id_t n){
        for (id_t i=0; i<n; i++) {
            m_trucks.push_back(Truck(i));
        }
    }
    void sortByIncreasingWeight(){
        sort(m_trucks.begin(), m_trucks.end(), [](const Truck & l, const Truck & r) { return l.weight() < r.weight(); });
    }

    vector<id_t> box_allocation()const{
        id_t n = 0;
        unordered_map<id_t,id_t> alloc;
        for(const_iterator it = m_trucks.begin(); it != m_trucks.end(); it++){
            for(Truck::const_iterator b_it = it->begin(); b_it != it->end(); b_it++ ){
                alloc[b_it->id()] = it->id();
                n++;
            }
        }
        vector<id_t> rv;
        for(id_t i=0;i<n;i++){
            rv.push_back( alloc[i] );
        }
        return rv;
    }
    
    pair<weight_t,weight_t> range_weight()const{
        const_iterator it = m_trucks.begin();
        
        weight_t max_weight = it->weight();
        weight_t min_weight = it->weight();
        for (it=m_trucks.begin(); it!=m_trucks.end(); it++) {
            if( it->weight() > max_weight){
                max_weight = it->weight();
            }
            if( it->weight() < min_weight){
                min_weight = it->weight();
            }
        }

        return pair<weight_t,weight_t>(min_weight,max_weight);
    }
    
    weight_t max_range_diff()const{
        pair<weight_t,weight_t> minmax = range_weight();
        return minmax.second - minmax.first;
    }
    
    vector<Truck> too_heavy_trucks()const{
        vector<Truck> rv;
        for (const_iterator it=m_trucks.begin(); it!=m_trucks.end(); it++) {
            if( it->weight() > m_max_weight){
                rv.push_back(*it);
            }
        }
        return rv;
    }
    
    void reallocate(const Truck & t){
        
    }
    
    void fill(const Payload & pl){
        Payload payload(pl);
        m_max_weight = ceil( double( payload.weight())/m_trucks.size() );
        payload.sortByDecreasingWeight();
        for (Payload::iterator box_it=payload.begin(); box_it!=payload.end(); box_it++) {
            for(iterator it=m_trucks.begin();it!=m_trucks.end();it++){
                if( it->has_space_for(*box_it) ){
                    it->add(*box_it);
                    sortByIncreasingWeight();
                    break;
                }
            }
        }
    }
    friend ostream &operator<<(ostream & os, const Convoy & convoy);
};

#endif /* Trucks_hpp */
