//
//  Trucks.cpp
//  Trucks
//
//  Created by Brice Rosenzweig on 11/09/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "Trucks.hpp"

ostream &operator<<(ostream & os, const Box & box){
    os << "box," << box.m_id << "," << box.m_weight << "," << box.m_volume;
    return os;
};

ostream &operator<<(ostream & os, const Truck & truck){
    os << "truck," << truck.m_id << "," << truck.weight() << "," << truck.volume();
    return os;
}

ostream &operator<<(ostream & os, const Payload & payload){
    for (vector<Box>::const_iterator it=payload.m_boxes.begin(); it!=payload.m_boxes.end(); it++) {
        os <<  *it << endl;
    }
    return os;
}
ostream &operator<<(ostream & os, const Convoy & convoy){
    for (vector<Truck>::const_iterator it=convoy.m_trucks.begin(); it!=convoy.m_trucks.end(); it++) {
        os << *it << endl;
    }
    return os;
}
