//
//  main.cpp
//  spoon
//
//  Created by Brice Rosenzweig on 08/01/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Coord{
public:
    size_t _x;
    size_t _y;
    bool invalid;
    Coord(){
        _x = 0;
        _y = 0;
        invalid = false;
    }
    Coord(const Coord & other){
        _x = other._x;
        _y = other._y;
        invalid = other.invalid;
    }
    Coord & operator=(const Coord & other ){
        _x = other._x;
        _y = other._y;
        invalid = other.invalid;
        return *this;
    }
    
    string representation() const{
        if (invalid) {
            return "-1 -1";
        }else{
            char buf[64];
            snprintf(buf, 64, "%lu %lu", _x, _y);
            return string(buf);
        }
    }
};

class Board {
private:
    vector<string> _map;
    size_t _width;
    size_t _height;
public:
    Board(int w, int h, vector<string> m){
        _map = m;
        _width = w;
        _height = h;
    }
    
    bool node(const Coord & c){
        if (c.invalid) {
            return false;
        }
        string s = _map[c._y];
        char n = s[c._x];
        return n == '0';
    }
    
    Coord nextNode(const Coord & node){
        Coord next(node);
        next._x++;
        if( next._x >= _width){
            next._x = 0;
            next._y++;
        }
        if( next._y >= _height || next._x >= _width){
            next.invalid = true;
        }
        return next;
    }
    
    Coord rightNodeOf(const Coord & node){
        Coord next(node);
        next._x++;
        if( next._x >= _width){
            next.invalid = true;
        }
        return next;
    }
    
    Coord belowNodeOf(const Coord & node){
        Coord next(node);
        next._y++;
        if( next._y >= _height){
            next.invalid = true;
        }
        return next;
    }
    void solve(){
        vector<string> rv;
        Coord current;
        while( !current.invalid){
            if( node(current)){
                Coord right(rightNodeOf(current));
                Coord below(belowNodeOf(current));
                
                while( !right.invalid && !node(right)){
                    right = rightNodeOf(right);
                }
                while( !below.invalid && !node(below)){
                    below = belowNodeOf(below);
                }
                char buf[128];
                snprintf(buf, 128, "%s %s %s", current.representation().c_str(), right.representation().c_str(), below.representation().c_str());
                rv.push_back(string(buf));
            }
            current = nextNode(current);
        }
        for (size_t i=0; i<rv.size(); i++) {
            cout << rv[i] <<endl;
        }
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    vector<string> map;
    map.push_back("0.0.0");
    
    Board board( 5, 1, map);
    board.solve();
    return 0;
}
