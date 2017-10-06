//
//  Message.hpp
//  centauri
//
//  Created by Brice Rosenzweig on 19/01/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <time.h>

using namespace std;

#include <stdio.h>

class Message {
public:
    typedef unsigned int one_t;
    typedef pair<Message,size_t> message_power_t;
    typedef pair<Message,Message> divisor_remainder_t;
    typedef vector<message_power_t> message_power_factors_t;
    
private:
    size_t _size;
    one_t * _rep;
    
public:
    Message(size_t s=32,one_t * values = NULL){
        _size = s;
        _rep = new one_t[_size/16];
        for( size_t k = 0; k < _size/16; k++){
            _rep[k] = values ? values[k] : 0;
        }
    }
    ~Message(){
        delete[] _rep;
    }
    Message(const Message & other){
        _size = other._size;
        _rep = new one_t[_size/16];
        
        for( size_t i = 0; i < _size/16; i++){
            _rep[i] = other._rep[i];
        }
    }
    Message & operator=(const Message &other){
        /*
        if( _size < other._size || _rep == NULL){
            _size = other._size;
            delete []_rep;
            _rep = new unsigned int[_size/16];
        }
        */
        for( size_t i = 0; i < _size/16; i++){
            _rep[i] = i < (other._size/16) ? other._rep[i] : 0;
        }
        return *this;
    }
    Message & operator=(one_t val){
        for(size_t i=0;i<_size/16;i++){
            _rep[i] = (i == 0) ? (val) : 0;
        }
        return *this;
    }
    bool operator==(one_t val)const{
        bool rv = true;
        if( val != _rep[0]){
            rv = false;
        }else{
            for (size_t i=1; i<_size/16; i++) {
                if( _rep[i]!=0){
                    rv = false;
                }
            }
        }
        return rv;
    }
    bool operator!=(one_t val)const{
        return !operator==(val);
    }
    bool operator==(const Message & other) const{
        bool rv = true;
        for (size_t i = 0; i<_size/16; i++) {
            one_t oval = i < other._size ? other._rep[i] : 0;
            rv = rv && oval == _rep[i];
        }
        if( rv && (other._size > _size)){
            for (size_t i = _size/16; i<other._size/16; i++){
                rv = rv && other._rep[i] == 0;
            }
        }
        return rv;
    }
    bool operator!=(const Message & other)const{
        return ! operator==(other);
    }
    bool operator<(const Message & other) const{
        bool rv = false;
        for (int i = 0; i<_size/16; i++) {
            if(_rep[i]>other._rep[i]){
                return false;
            }else if(_rep[i]<other._rep[i]){
                return true;
            }
        }
        return rv;
    }
    
    void set( one_t * v){
        for (int i = 0; i<_size/16; i++) {
            _rep[i] = v[i];
        }
    }
    
    friend ostream & operator<<(ostream & stream,const Message & m);
    Message & read(istream & is);
    Message & read(const char * str);
    void debug_print() const;
    
    Message x_n(size_t n) const{
        Message rv(_size);
        rv._rep[ n/32 ] |= (one_t)1 << (n % 32);
        return rv;
    }
    
    bool operator[](size_t i)const{
        return ((_rep[i/32] >> (i%32)) & 1)==1;
    }
    
    bool get_bit(size_t i)const{
        return ((_rep[i/32] >> (i%32)) & 1) == 1;
    }
    void set_bit(size_t i, bool val){
        if( val ){
            _rep[i/32] |= ( 1<< i);
        }else{
            _rep[i/32] &= ~( 1<<i);
        }
    }
    
    size_t order()const{
        for (size_t k=0; k<_size/16; k++) {
            size_t kk = (_size/16-1)-k;
            if (_rep[kk] != 0) {
                for (int i=0; i<_size; i++) {
                    if( ((_rep[kk] >> (31-i)) & 1) == 1){
                        return (  32 * kk + (31-i) );
                    }
                }
            }
        }
        return 0;
    }

#pragma mark - arithmetics
    Message & operator>>=(size_t i){
        while( i > 0){
            one_t carry = 0;
            for(size_t k=0;k<_size/16;k++){
                size_t kk = (_size/16-1-k);
                one_t shifted = (_rep[kk] >> 1) | carry;
                carry = ( _rep[kk] & 1 ) << 31;
                _rep[kk] = shifted;
            }
            i--;
        }
        return *this;
    }

    Message operator >>(size_t i) const{
        Message rv(*this);
        rv >>= i;
        return rv;
    }
    
    Message & operator<<=(size_t i){
        while( i > 0){
            one_t carry = 0;
            for(size_t k=0;k<_size/16;k++){
                one_t shifted = (_rep[k] << 1) | carry;
                carry = ( _rep[k] >> 31 ) & 1;
                _rep[k] = shifted;
            }
            i--;
        }
        return *this;
    }
    
    Message operator <<( size_t i ) const{
        Message rv(*this);
        rv <<= i;
        return ( rv );
    }
    
    Message & operator-=(const Message & o){
        for (int k=0; k<_size/16; k++) {
            if (k < o._size/16) {
                _rep[k] ^= o._rep[k];
            }
        }
        return *this;
    }
    Message operator -(const Message & o )const{
        Message rv(*this);
        rv -= o;
        return rv;
    }
    Message & operator+=(const Message & o){
        for (int k=0; k<_size/16; k++) {
            if( k < o._size/16){
                _rep[k] ^= o._rep[k];
            }
        }
        return *this;
    }
    Message operator+(const Message & o)const{
        Message rv(*this);
        rv+= o;
        return rv;
    }

    Message & operator^=(const Message & o){
        for (size_t k=0; k<_size/16; k++) {
            _rep[k] ^= o._rep[k];
        }
        return *this;
    }
    
    Message operator*(const Message & o){
        if( o._size != _size){
            cout <<"BOO"<<endl;
        }
        Message rv(_size);
        
        
        for (int i = 0; i < _size; i++)
            for (int j = 0; j < _size; j++) {
                rv._rep[(i + j) / 32] ^= ( (_rep[i / 32] >> (i % 32)) &
                                          (o._rep[j / 32] >> (j % 32)) & 1 ) << ((i + j) % 32);
            }
        
        /*
        for(int i = 0; i < _size;i++){
            if( (_rep[i/32] >> (i%32)  & 1 ) == 1){
                Message shift( o<<i );
                for (size_t k=0; k<_size/16; k++) {
                    rv._rep[k] ^= shift._rep[k];
                }
            }
        }
         */
        return rv;

    }
    
    Message operator^(size_t n){
        if( n==1){
            return *this;
        }
        if( n==0){
            return 1;
        }
        Message rv(( *this) * (*this));
        size_t p = 2;
        while( p*2 < n){
            rv = rv*rv;
            p  *= 2;
        }
        while( p < n){
            rv = rv * (*this);
            p++;
        }
        return rv;
    }

    Message compose_power(size_t n) const{
        Message rv(_size);
        if( n == 1){
            rv = *this;
        }else{
            for (size_t i=0; i<=(_size/n);i++) {
                if( ( (_rep[i/32] >> (i%32) ) & 1 ) == 1){
                    size_t j = i * n;
                    if( j < _size){
                        rv._rep[j/32] |= ( 1 << (j %32) );
                    }
                }
            }
        }
        return rv;
    }
    
    Message compose_inverse_power(size_t n) const{
        Message rv(_size);
        size_t p = order();
        for (size_t k=0; k<p; k++) {
            if( k % n == 0){
                size_t from = k;
                size_t to = k/n;
                
                rv._rep[to/32] |= ((_rep[from/32] >> (from%32)) & 1 ) << (to%32);
            }
        }
        
        return rv;
    }
    
    divisor_remainder_t divide_by(const Message & o) const{
        Message div(_size);
        Message rem(*this);
        
        size_t oOrder = o.order();
        size_t rOrder = rem.order();
        
        while( rOrder >= oOrder && rem != 0){
            size_t n = rem.order() - oOrder;
            rem -= (o << n);
            div += x_n(n);
            rOrder = rem.order();
        }
        return divisor_remainder_t(div,rem);
    }
    
    Message operator / (const Message & o)const{
        return divide_by(o).first;
    }
    
    Message & operator /= (const Message & o){
        this->operator=( *this/o );
        return *this;
    }
    Message operator % (const Message & o) const{
        return divide_by(o).second;
    }
    
    Message derivative() const{
        Message rv(*this);
        
        rv >>= 1;
        
        for(size_t k=0;k<_size/16;k++){
            // x^4+x^3+x^2+x+1 -> 4x^3+3x^2+2x+1 -> 0101
            rv._rep[k] &= 0b01010101010101010101010101010101;
        }
        return rv;
    }
    
    //https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
    Message gcd(const Message & o) const{
        bool thisLarger = order()>o.order();
        
        Message a( thisLarger ? *this : o);
        Message b( thisLarger ? o : *this);
        
        while( b != 0){
            Message t(b);
            b = a % b;
            a = t;
        }

        return a;

    }
    
#pragma mark - factorization
    //https://en.wikipedia.org/wiki/Factorization_of_polynomials_over_finite_fields#Square-free_factorization
    message_power_factors_t square_free_factors() const{
        message_power_factors_t rv;
        Message f(*this);
        size_t i = 1;
        Message R(f.x_n(0));
        Message g(derivative());
        if( g != 0){
            Message c(f.gcd(g));
            Message w(f/c);
            while( w != 1){
                Message y(w.gcd(c));
                Message z(w/y);
                // FACTOR: z power i
                w = y;
                c = c/y;
                cout << dec << z << "^" << i << endl;
                rv.push_back(message_power_t(z,i));
                i++;
            }
            if( c != 1){
                c = c.compose_inverse_power(2);
                vector<message_power_t> c_factors = c.square_free_factors();
                for (message_power_factors_t::iterator it = c_factors.begin(); it != c_factors.end(); it++) {
                    message_power_t mp = *it;
                    rv.push_back(message_power_t(mp.first, mp.second * 2));
                }
            }
        }else{
            f = f.compose_inverse_power(2);
            message_power_factors_t f_factors = f.square_free_factors();
            for (message_power_factors_t::iterator it = f_factors.begin(); it != f_factors.end(); it++) {
                message_power_t mp = *it;
                rv.push_back(message_power_t(mp.first, mp.second * 2));
            }
        }
        return rv;
    }
    
    Message square_free_part() const{
        Message rv(*this);
        Message g(derivative());
        if( g == 0 && order() >0){
            rv = compose_inverse_power(2).square_free_part();
        }else{
            rv = rv / gcd(g);
        }
        return rv;
    }
    
    //https://en.wikipedia.org/wiki/Factorization_of_polynomials_over_finite_fields#Distinct-degree_factorization
    vector<Message> distinct_degree_factors() const{
        vector<Message> rv;
        Message rem(*this);
        for (size_t i=0; i<_size; i++) {
            Message poly(x_n(2^(i+1)) - x_n(1));
            Message one_g( rem.gcd(poly) );
            if( one_g != 1){
                rv.push_back(one_g);
                rem /= one_g;
            }
            if (rem.order() < 2*i) {
                break;
            }
        }
        return rv;
    }
    Message random(size_t order, size_t method = 0) const{
        Message rv(_size);
        if( method == 0){
            for (size_t k =0 ; k<_size/16; k++) {
                if( k < order/32){
                    rv._rep[k] = rand();
                }else if( k == order/32){
                    one_t mask = (1 << order %32) -1;
                    one_t val = rand();
                    rv._rep[k] = val & mask;
                }else{
                    rv._rep[k] = 0;
                }
            }
        }else{
            for (size_t i = 0; i<order; i++) {
                rv._rep[i/32] |= ( rand() & 1 ) << i % 32;
            }
        }
        return rv;
    }
    
    //https://en.wikipedia.org/wiki/Factorization_of_polynomials_over_finite_fields#Cantor.E2.80.93Zassenhaus_algorithm
    std::set<Message> equal_degree_factors_cz(size_t d) const{
        std::set<Message> rv;
        rv.insert(*this);
        size_t n = order();
        Message unit = 1;
        
        size_t idx = 0;
        unsigned long begTime = clock();
        unsigned long startTime = clock();
        
        while(rv.size() < n/d){
            Message h(random(n-1,0));
            size_t power = (2^d - 1)/2;
            
            Message g( ((h^power) + unit) % (*this) );
            //Message g( ((h.compose_power(power) + unit) /*% (*this)*/ ) );
            std::set<Message> next;
            
            idx++;
            unsigned long elapsed = (clock()-begTime)/CLOCKS_PER_SEC;
            if( elapsed > 10){
                begTime = clock();
                unsigned long total = (clock()-startTime)/CLOCKS_PER_SEC;
                cout << idx << " tries after " << total/60 << ":" << total %60 << endl;
            }
            
            for (std::set<Message>::iterator it = rv.begin(); it!=rv.end(); it++) {
                Message u(*it);
                Message div = g.gcd(u);
                if( div != 1 && div != u ){
                    next.insert(div);
                    next.insert(u/div);
                }else{
                    next.insert(u);
                }
            }
            rv = next;
        }
        return rv;
    }
    //https://pdfs.semanticscholar.org/91b8/d2172d6ceeb99fd548532483aa8f3a99c8e5.pdf
    Message equal_degree_factors_mce() const{
        Message rv(_size);

        size_t size = _size*2; // extra space for the search
        
        Message f(size);
        Message x(size);
        Message r(size);
        
        f = *this;
        x = x_n(1);
        r = x_n(2);
        size_t n = 2;
        
        while (true) {
            r = (r*r) % f;
            if( r == x){
                break;
            }
            if( r==0){
                return f;
            }
            n++;
        }
        
        size_t ord = order();
        for (size_t i=0; i<ord; i++) {
            Message dT = f.x_n(i) % f;
            Message Ti(size);
            for (size_t j=0; j<n; j++){
                Ti += dT;
                dT = (dT*dT) % f;
            }
            if( Ti != 0){
                Message Ci = f.gcd(Ti);
                Message Qi = f / Ci;
                if (Ci != 1 && ( Ci * Qi) == f) {
                    rv = Ci;
                    break;
                }
            }
        }
        
        return rv;
    }
    
    void swap_cols(vector<Message> & M, size_t i, size_t j)const{
        size_t idx_i = i/32;
        size_t idx_j = j/32;
        one_t bit_i = (one_t)1 << i%32;
        one_t bit_j = (one_t)1 << j%32;
        
        for (vector<Message>::iterator it = M.begin(); it != M.end(); it++) {
            one_t val_i = ((it->_rep[idx_j]  & bit_j) == bit_j) ? 1<<(i%32) : 0;
            one_t val_j = ((it->_rep[idx_i]  & bit_i) == bit_i) ? 1<<(j%32) : 0;
            
            it->_rep[idx_i] = (it->_rep[idx_i] & (~bit_i)) | val_i;
            it->_rep[idx_j] = (it->_rep[idx_j] & (~bit_j)) | val_j;
        }
    }
    
    void factor_out_col(vector<Message> & M, size_t c)const{
        size_t idx_c = c/32;
        size_t bit_c = (size_t)1 << c%32;
        
        const Message & row = M[c];
        
        size_t n = row._size * 2;
        
        for( size_t j=0;j<n;j++){
            size_t idx_j = j/32;
            size_t bit_j = (size_t)1<<(j%32);
            if( j != c && (row._rep[idx_j] & bit_j) == bit_j){
                
                for (size_t r = 0; r<M.size();r++) {
                    Message & one = M[r];
                    
                    if((one._rep[idx_c] & bit_c)==bit_c){
                        one._rep[idx_j] ^=  bit_j;
                    }
                }
            }
        }
    }
    
    ostream & dump_col(ostream & os, vector<Message> & M, size_t c)const{
        size_t i=0;
        for (vector<Message>::iterator it = M.begin(); it != M.end(); it++) {
            os << (it->get_bit(c) ? 1 : 0);
            if( i%32 == 0 && i != 0){
                os << " ";
            }
            i++;
        }
        return os;
    }
    
    //https://en.wikipedia.org/wiki/Berlekamp%27s_algorithm
    vector<Message> equal_degree_factors_ber() const{
        Message rv(_size);
        
        size_t ord = order();
        
        Message x(_size*2);
        Message f(_size*2);
        f = *this;
        x = 1;
        vector<Message> Qs;
        
        for (size_t i=0; i<ord; i++) {
            x = x % f;
            Qs.push_back(x);
            x <<= 2;
        }
        
        Message c(_size*2);
        c = 1;
        
        vector<Message> A(Qs);
        size_t n = ord;
        // A = Q-I
        for (size_t k=0; k<n; k++) {
            A[k] ^= c;
            c <<= 1;
            
        }
        vector<Message> solutions;
        // Triangularisation
        
        for( size_t k = 0; k < n; k++ ){
            if(! A[k].get_bit(k)){
                for( size_t j = 0; j< k;j++){
                    if( ! A[j].get_bit(j) && A[k].get_bit(j)){
                        swap_cols(A, j, k);
                        break;
                    }
                }
            }
            if(! A[k].get_bit(k)){
                for (size_t j=k+1; j<n; j++) {
                    if(A[k].get_bit(j)){
                        swap_cols(A, j, k);
                        break;
                    }
                }
            }
            
            if( A[k].get_bit(k)){
                factor_out_col(A, k);
            }else{
                Message found(A[k]);
                found.set_bit(k, true);
                found = f.gcd(found);
                solutions.push_back(found);
            }
        }
        
        return solutions;
    }
    
#pragma mark - encode/decode
    Message encode() const{
        Message rv(_size);
        for (int i = 0; i < _size; i++)
            for (int j = 0; j < _size; j++) {
                rv._rep[(i + j) / 32] ^= ( (_rep[i / 32] >> (i % 32)) &
                                          (_rep[j / 32 + _size / 32] >> (j % 32)) & 1 ) << ((i + j) % 32);   // Magic centaurian operation
            }
        
        return rv;
    }
    
    Message(const Message & left, const Message & right)
    :Message(left._size)
    {
        for(int k = 0;k<_size/16;k++){
            _rep[k] = k < _size/32 ? left._rep[k] : right._rep[k-_size/32];
        }
    }
    
    vector<Message> decode() const{
        vector<Message> factors = equal_degree_factors_ber();
        
        vector<Message> rv;
        
        for (size_t i=0; i<factors.size(); i++) {
            Message factor(_size);
            factor = factors[i];
            Message complement(_size);
            complement = this->operator/(factor);
            if( factor.order() < _size && complement.order() < _size){
                rv.push_back(Message(factor,complement));
                rv.push_back(Message(complement,factor));
            }
        }
        sort(rv.begin(), rv.end());
        return rv;
    }
};


#endif /* Message_hpp */
