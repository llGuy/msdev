//
//  Charles.cpp
//  centauri
//
//  Created by Brice Rosenzweig on 28/01/2017.
//  Copyright © 2017 Brice Rosenzweig. All rights reserved.
//

#include "Charles.hpp"


# include <algorithm>
# include <cassert>
# include <iomanip>
# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <set>
# include <random>
# include <time.h>


// ----------------------------------------------------------------------

// The factorisation algorithm in this file is the one described in:

// Knuth, The Art of Computer Programming, Vol2, section 4.6.2

// This program requires a C++11 or more recent compiler, but only
// because we use the random number generator, which is only required
// for testing. Comment away the tests, and it should compile fine on
// an earlier vintage.

// ----------------------------------------------------------------------

typedef unsigned int word_type;
static const unsigned int log_word_length = 5;
static const unsigned int word_length = 1 << log_word_length;

// ----------------------------------------------------------------------

class bitvector
{
public:
    
    // a bit vector that with some optimal features (for our
    // purposes).
    
    // initialise a vector to 0's with the given number of bits
    inline
    bitvector(const unsigned int nbits)
    : words_((nbits+(word_length-1)) >> log_word_length,0),
    size_(nbits)
    {
    }
    
    // Retrieve the bit at offset i in the vector
    inline
    bool
    get(const unsigned int i) const
    {
        assert(i < size_);
        return words_[i>>log_word_length] & (1 << (i&(word_length-1))) ? true : false;
    }
    
    // compare for equality
    inline
    bool
    operator==(const bitvector& other) const
    {
        return size_ == other.size_ && words_ == other.words_;
    }
    
    // compare for non-equality
    inline
    bool
    operator!=(const bitvector& other) const
    {
        return !(*this == other);
    }
    
    // less-than operator; we use something that works well for the polys
    inline
    bool
    operator<(const bitvector& other) const
    {
        if(size_ < other.size_) return true;
        if(size_ > other.size_) return false;
        
        for(unsigned int s=size_; s>0; --s)
        {
            if(get(s-1) < other.get(s-1)) return true;
            if(get(s-1) > other.get(s-1)) return false;
        }
        
        return false;
    }
    
    // set the bit at offset i in the vector
    inline
    void set(const unsigned int i)
    {
        assert(i < size_);
        words_[i>>log_word_length] |= (1 << (i&(word_length-1)));
    }
    
    // XOR this vector with another, must be the same size
    inline
    bitvector& operator^=(const bitvector& other)
    {
        shift_xor(other,0);
        return *this;
    }
    
    // Add i bits to the left of the other vector, which should make
    // it the no bigger than this vector, and then xor the bits
    inline
    void shift_xor(const bitvector& other,const unsigned int i)
    {
        assert(i+other.size_ <= size_);
        const unsigned int other_nw = other.num_words();
        const unsigned int shift1 = i & (word_length-1);
        const unsigned int shift2 = i >> log_word_length;
        if(shift1)
        {
            for(unsigned int j=0; j<other_nw; ++j)
            {
                words_[j+shift2] ^= other.words_[j] << shift1;
            }
            const unsigned int shift1b = word_length - shift1;
            const unsigned int shift2b = shift2+1;
            for(unsigned int j=0; j<other_nw; ++j)
            {
                words_[j+shift2b] ^= other.words_[j] >> shift1b;
            }
        }
        else
        {
            for(unsigned int j=0; j<other_nw; ++j)
            {
                words_[j+shift2] ^= other.words_[j];
            }
        }
    }
    
    // get the size of the vector, in bits
    inline
    unsigned int size() const
    {
        return size_;
    }
    
    // make a smaller or larger vector. in case of a larger vector,
    // bits containing 0 are added, in the case of smaller, bits are
    // forgotten.
    inline
    void resize(unsigned int nbits)
    {
        if(nbits < size_)
        {
            unsigned int word_index = nbits >> log_word_length;
            const unsigned int bit_index  = nbits & (word_length-1);
            if(bit_index)
            {
                words_[word_index] &= (1<<bit_index) -1;
                ++word_index;
            }
            const unsigned int nw = num_words();
            while(word_index < nw)
            {
                words_[word_index] = 0;
                ++word_index;
            }
            
            size_ = nbits;
            words_.resize(num_words());
        }
        else if(nbits > size_)
        {
            const unsigned int new_num_words = (nbits+(word_length-1)) >> log_word_length;
            if(new_num_words > words_.size())
            {
                words_.resize(new_num_words,0);
            }
            
            size_ = nbits;
        }
    }
    
    inline
    void
    swap(bitvector& other)
    {
        words_.swap(other.words_);
        std::swap(size_,other.size_);
    }
    
    std::string
    dump() const
    {
        std::ostringstream os;
        os << "BV[";
        for(unsigned int i=0; i<words_.size(); ++i)
        {
            os << std::hex << words_[i] << ";";
        }
        os << "#" << size_ << "]";
        return os.str();
    }
    
    // add n bits to the start of the vector and write the results to ret
    void shift(bitvector& ret,unsigned int n) const
    {
        if(n>0)
        {
            bitvector ans(size()+n);
            ans.shift_xor(*this,n);
            ret.swap(ans);
        }
        else
        {
            ret = *this;
        }
    }
    
    void dump_bin()const{
        for(unsigned int i=0;i<size();i++){
            std::cout << (get(i)?1:0);
        }
        std::cout << std::endl;
    }
    
    std::string to_string() const
    {
        std::ostringstream os;
        os << hex_string() << " #" << size_;
        return os.str();
    }
    
    // get a string format (32-bit big endian chunks, themselves in
    // little-endian format)
    std::string hex_string() const
    {
        std::ostringstream os;
        assert(word_length == 32);
        for(unsigned int i=0; i<num_words(); ++i)
        {
            if(i>0)
            {
                os << " ";
            }
            os << std::setfill('0') << std::setw(8) << std::hex << words_[i];
        }
        
        return os.str();
    }
    
    // parse a bit-stream from an input, assuming it will be the given
    // number of bits (0 padded, little ending in chunks of 32 bit
    // words)
    
    void parse(std::istream& is,unsigned int nbits)
    {
        assert(word_length == 32);
        
        resize(0);
        resize(nbits);
        resize(num_words() * word_length);
        
        for(unsigned int i=0; i<num_words(); ++i)
        {
            is >> std::hex >> words_[i];
        }
        
        resize(nbits);
    }
    
private:
    
    inline
    unsigned int
    num_words() const
    {
        return (size_+(word_length-1)) >> log_word_length;
    }
    
    std::vector<word_type> words_;
    unsigned int size_;
};

// ----------------------------------------------------------------------

class poly
{
public:
    
    // these are polys over the binary field, with some useful
    // operations to go with them.
    
    inline
    poly()
    : vector_(0)
    {
    }
    
    // compare for equality
    bool operator==(const poly& other) const
    {
        return vector_ == other.vector_;
    }
    
    // compare for non-equality
    bool operator!=(const poly& other) const
    {
        return vector_ != other.vector_;
    }
    
    // compare for less-than
    bool operator<(const poly& other) const
    {
        return vector_ < other.vector_;
    }
    
    // get the unit poly
    inline static
    poly
    unit()
    {
        bitvector b(1);
        b.set(0);
        poly p;
        p.swapbits(b);
        return p;
    }
    
    // get the poly "X^1"
    inline static
    poly
    X()
    {
        bitvector b(2);
        b.set(1);
        poly p;
        p.swapbits(b);
        return p;
    }
    
    // get the degree of the poly
    inline
    int
    degree() const
    {
        return vector_.size()-1;
    }
    
    // determine if the poly is zero ...
    inline
    bool
    is_zero() const
    {
        return vector_.size() == 0;
    }
    
    // determine if the poly is the unit poly ...
    inline
    bool
    is_unit() const
    {
        return vector_.size() == 1;
    }
    
    inline
    void
    set_zero()
    {
        bitvector b(0);
        swapbits(b);
    }
    
    // determine if the coefficient of X^i is 1 or not ...
    inline
    bool
    coeff(const unsigned int i) const
    {
        if(i < vector_.size())
        {
            return vector_.get(i);
        }
        else
        {
            return false;
        }
    }
    
    // add the given poly to this one
    inline
    poly&
    operator+=(const poly& other)
    {
        if(vector_.size() < other.vector_.size())
        {
            vector_.resize(other.vector_.size());
        }
        
        vector_ ^= other.vector_;
        fixup();
        return *this;
    }
    
    // subtract the given poly to this one (since its the binary
    // field, this is the same as adding) ...
    inline
    poly&
    operator-=(const poly& other)
    {
        *this += other;
        return *this;
    }
    
    // compute the sum of two polys
    inline
    poly
    operator+(const poly& other) const
    {
        poly tmp(*this);
        tmp += other;
        return tmp;
    }
    
    // compute the difference of two polys
    inline
    poly
    operator-(const poly& other) const
    {
        return *this + other;
    }
    
    // multiply two polyomials
    inline
    void
    multiply(const poly &other,poly& ret) const
    {
        if(is_zero() || other.is_zero())
        {
            ret.set_zero();
        }
        else
        {
            bitvector v(1+(degree() + other.degree()));
            const unsigned int n = vector_.size();
            for(unsigned int i=0; i<n; ++i)
            {
                if(coeff(i))
                {
                    v.shift_xor(other.vector_,i);
                }
            }
            
            ret.swapbits(v);
        }
    }
    
    // multiply two polys together ...
    inline
    poly
    operator*(const poly& other) const
    {
        poly ret;
        multiply(other,ret);
        return ret;
    }
    
    // compute the n'th power of the poly
    inline
    poly
    pow(const unsigned int n) const
    {
        unsigned int cn = n;
        poly ret(unit());
        poly acc(*this);
        
        for(unsigned int b=1; cn; b<<=1)
        {
            if(cn&b)
            {
                cn &= ~b;
                ret.multiply(acc,ret);
            }
            
            if(cn)
            {
                acc.square(acc);
            }
        }
        
        return ret;
    }
    
    // compute the square of the polynomal (efficiently)
    void
    square(poly& ret) const
    {
        if(is_zero())
        {
            ret.set_zero();
        }
        else
        {
            bitvector b(degree()*2 + 1);
            for(unsigned int i=0; i<vector_.size(); ++i)
            {
                if(vector_.get(i))
                {
                    b.set(2*i);
                }
            }
            ret.swapbits(b);
        }
    }
    
    inline
    poly
    squared() const
    {
        poly ret;
        square(ret);
        return ret;
    }
    
    // compute the square root, assuming there is one (asserts otherwise)
    void
    sqrt(poly& ret) const
    {
        bitvector b(1+vector_.size()/2);
        
        for(int i=1; i<vector_.size(); i+=2)
        {
            assert(!vector_.get(i));
        }
        
        for(int i=0; 2*i<vector_.size(); ++i)
        {
            if(vector_.get(2*i))
            {
                b.set(i);
            }
        }
        
        ret.swapbits(b);
    }
    
    // compute the formal derivative of the polynomial
    void deriv(poly& ret) const
    {
        bitvector b(vector_.size());
        
        for(int i=1; i<vector_.size(); i+= 2)
        {
            if(vector_.get(i))
            {
                b.set(i-1);
            }
        }
        
        ret.swapbits(b);
    }
    
    // divide this polyomial by the other, leaving the remainder in
    // this poly and returning the quotient
    poly div(const poly &other)
    {
        if(is_zero())
        {
            return poly();
        }
        
        assert(!other.is_zero());
        const unsigned int qsize = other.vector_.size();
        bitvector b(vector_.size());
        for(unsigned int n = vector_.size(); n>=qsize; --n)
        {
            if(vector_.get(n-1))
            {
                b.set(n-qsize);
                vector_.shift_xor(other.vector_,n-qsize);
            }
        }
        fixup();
        poly ret;
        ret.swapbits(b);
        return ret;
    }
    
    // multiply self by X^n ...
    inline
    void
    scale(unsigned int n)
    {
        bitvector res(0);
        vector_.shift(res,n);
        swapbits(res);
    }
    
    inline
    void swapbits(bitvector& other)
    {
        vector_.swap(other);
        fixup();
    }
    
    std::string hex_string() const{
        return vector_.hex_string();
    }
    std::string to_string() const
    {
        std::ostringstream os;
        if(is_zero())
        {
            os << "0";
        }
        else if(is_unit())
        {
            os << "1";
        }
        else
        {
            for(int i=degree(); i>=0; --i)
            {
                os << (coeff(i) ? 1 : 0);
            }
            /*
            os << "(";
            for(int i=degree(); i>=0; --i)
            {
                if(coeff(i))
                {
                    if(i < degree())
                    {
                        os << " + ";
                    }
                    
                    os << "X^" << i;
                }
            }
            os << ")";
             */
        }
        return os.str();
    }
    
    std::string
    dump() const
    {
        return vector_.dump();
    }
    
    void swap(poly& other)
    {
        vector_.swap(other.vector_);
    }
    
    inline
    poly
    operator%(const poly& other) const
    {
        poly r(*this);
        r.div(other);
        return r;
    }
    
    inline
    poly
    operator/(const poly& other) const
    {
        poly r(*this);
        return r.div(other);
    }
    
    // tell if one polynomial divides into another
    inline
    bool
    divides(const poly& other) const
    {
        return (other % *this).is_zero();
    }
    
    // look at the underlying bit vector
    const bitvector& bits() const
    {
        return vector_;
    }
    
private:
    
    inline
    void fixup()
    {
        for(unsigned int i=vector_.size(); i>0; --i)
        {
            if(vector_.get(i-1))
            {
                vector_.resize(i);
                return;
            }
        }
        vector_.resize(0);
    }
    
    bitvector vector_;
};

std::ostream& operator<<(std::ostream& os,const poly& p)
{
    os << p.to_string();
    return os;
}

// ----------------------------------------------------------------------

// Treat <mat> as a row-major matrix, like fixpoint_finder does, and
// calculate the effect of multiplying the polynomial by the matrix.
poly
matmul(const poly& v,const std::vector<poly>& mat)
{
    bitvector b((unsigned int)mat.size());
    
    for(unsigned int i=0; i<mat.size(); ++i)
    {
        int bit = 0;
        
        for(unsigned int j=0; j<mat.size(); ++j)
        {
            if(v.coeff(j) && mat[j].coeff(i))
            {
                bit ^= 1;
            }
        }
        
        if(bit)
        {
            b.set(i);
        }
    }
    
    poly ret;
    ret.swapbits(b);
    return ret;
}

// ----------------------------------------------------------------------

// compute the greatest common divisor polyomial
poly
gcd(const poly& a,const poly& b)
{
    poly a1(a);
    poly b1(b);
    
    while(!b1.is_zero())
    {
        a1.div(b1); // puts the remainder into a1
        a1.swap(b1);
    }
    
    return a1;
}

// ----------------------------------------------------------------------

// given a polynomial f, returns a vector of pairs like this:
//
//     [ (p1,a1), (p2,a2), ..., (pN,aN) ]
//
// such that all polynomials p1, p2, ..., pN have no repeated irreducible
// factors, and such that:
//
//     f = p1.pow(a1) * p2.pow(a2) * ... * pN.pow(aN)
//
void
square_free_factors(const poly& f,std::vector< std::pair<poly,unsigned int> >& ret)
{
    assert(!f.is_zero());
    
    if(!f.is_unit())
    {
        poly g;
        f.deriv(g);
        
        if(g.is_zero())
        {
            // f is perfect square
            poly r;
            f.sqrt(r);
            unsigned int i=(unsigned int)ret.size();
            square_free_factors(r,ret);
            for(; i<ret.size(); ++i)
            {
                ret[i].second *= 2;
            }
        }
        else
        {
            const poly c = gcd(f,g);
            if(c.is_unit())
            {
                // f has no square factors
                ret.push_back(std::make_pair(f,1));
            }
            else
            {
                // c is a factor repreated more than once in f
                poly f2 = f;
                square_free_factors(f2.div(c),ret);
                square_free_factors(c,ret);
            }
        }
    }
}

void dump_poly_vec(const std::vector<poly> & v){
    for (size_t i=0; i<v.size(); i++) {
        std::cout << v[i].to_string() << std::endl;
    }
}

void dump_cols(const std::vector<bitvector> & v){
    for (size_t i=0; i<v.size(); i++) {
        v[i].dump_bin();
    }
}

// ----------------------------------------------------------------------

class fixpoint_finder
{
public:
    
    // Use this to look (incrementally) for a linearly indepenent
    // basis of the fixpoint of an NxN matrix over the binary field.
    //
    // If the matrix is M, then for the purposes of this utility, the
    // fixpoint vectors are the *row* vectors v for which v*M = v in
    // terms of normal matrix arithmetic. This is a linear subspace.
    void init(std::vector< poly >& M)
    {
        degree_ = (unsigned int)M.size();
        row_ = 0;
        colmajor_.resize(degree_,bitvector(degree_));
        
        for(unsigned int row=0; row<degree_; ++row)
        {
            for(unsigned int col=0; col<degree_; ++col)
            {
                bool bit = M[row].coeff(col);
                
                if(row==col ? !bit : bit)
                {
                    colmajor_[col].set(row);
                }
            }
        }
        /*std::cout << "C COLS" << std::endl;
        dump_cols(colmajor_);*/
    }
    
    // get the next fixpoint basis element and return true, if another
    // one can be found; else return false.
    bool next(poly& ret)
    {
        while(row_ < degree_)
        {
            if(!colmajor_[row_].get(row_))
            {
                for(unsigned int j=0; j<row_; ++j)
                {
                    if(!colmajor_[j].get(j) && colmajor_[j].get(row_))
                    {
                        //std::cout << "swap< " << j << " " << row_ << std::endl;
                        assert(!colmajor_[row_].get(j));
                        colmajor_[row_].swap(colmajor_[j]);
                        assert(colmajor_[row_].get(row_));
                        assert(! colmajor_[j].get(j));
                        break;
                    }
                }
            }
            
            if(!colmajor_[row_].get(row_))
            {
                for(unsigned int j=row_+1; j<degree_; ++j)
                {
                    if(colmajor_[j].get(row_))
                    {
                        //std::cout << "swap< " << j << " " << row_ << std::endl;
                        colmajor_[row_].swap(colmajor_[j]);
                        break;
                    }
                }
            }
            
            if(colmajor_[row_].get(row_))
            {
                for(unsigned int j=0; j<row_; ++j)
                {
                    assert(!colmajor_[row_].get(j));
                }

                for(unsigned int j=0; j<degree_; ++j)
                {
                    if(j!= row_ and colmajor_[j].get(row_))
                    {
                        colmajor_[j] ^= colmajor_[row_];

                    }
                }
                
                row_ += 1;
            }
            else
            {
                //std::cout << "found " << row_ << std::endl;
                bitvector b(row_+1);
                
                for(unsigned int j=0; j<row_; ++j)
                {
                    if(colmajor_[j].get(row_))
                    {
                        b.set(j);
                    }
                }

                b.set(row_);
                ret.swapbits(b);
                //std::cout << ret.to_string() << std::endl;
                //std::cout << ret.hex_string() << std::endl;
                row_ += 1;
                return true;
            }
        }
        
        return false;
    }
    
private:
    
    unsigned int degree_;
    unsigned int row_;
    std::vector<bitvector> colmajor_;
};

// ----------------------------------------------------------------------

class berlekamp_finder
{
    // in order to support the Berlekamp algorithm, this class takes a
    // non-trivial polynomial u that is free of squared factors, and
    // then generates a linearly indepenent basis of polynomials v
    // that solve:
    //
    //    v*v - v = 0 (mod u)
    
public:
    
    berlekamp_finder(const poly& u)
    {
        std::vector<poly> mat;
        poly acc = poly::unit();
        //std::cout << acc.to_string() << std::endl;
        for(unsigned int i=0; i<u.degree(); ++i)
        {
            acc.div(u); // get the remainder
            mat.push_back(acc);
            acc.scale(2); // multiply by X^2
            
        }
        
        ff_.init(mat);
    }
    
    bool next(poly& ret)
    {
        return ff_.next(ret);
    }
    
private:
    
    fixpoint_finder ff_;
};

// ----------------------------------------------------------------------

// u is a polynomial that is on-trivial and has no sqaured factors;
// facorise it and return a vector of irreducibles whose product
// matches the original. <ret> must start off empty.
void
berlekamp(std::vector<poly>& ret,const poly&u)
{
    berlekamp_finder bf(u);
    poly v;
    
    while(bf.next(v))
    {
        const poly c = gcd(u,v);
        if(0 < c.degree() && c.degree() < u.degree())
        {
            // We've found a factor, not necessarily irreducible but
            // worth recursing now to reduce complexity ...
            berlekamp(ret,c);
            berlekamp(ret,u / c);
            
            return;
        }
    }
    
    // if we drop out here, it's irreducible.
    ret.push_back(u);
}

// ----------------------------------------------------------------------

// f is an arbitrary non-trivial polynomial; facorise it and return a
// vector of its factors.
std::vector<poly>
factorise(const poly& f)
{
    std::vector<poly> ret;
    
    std::vector< std::pair<poly,unsigned int> > sff;
    square_free_factors(f,sff);
    
    for(unsigned int s=0; s<sff.size(); ++s)
    {
        const poly& u = sff[s].first;
        const unsigned int pwr = sff[s].second;
        
        std::vector<poly> bfp;
        berlekamp(bfp,u);
        
        for(unsigned int i=0; i<pwr; ++i)
        {
            ret.insert(ret.end(),bfp.begin(),bfp.end());
        }
    }
    
    return ret;
}

// ----------------------------------------------------------------------

void test_gen_all_bitvectors(std::vector<bitvector>& ret,const unsigned int n)
{
    // generate all bitvectors of size == n
    
    assert(n < 20); // ridiculous otherwise
    ret.resize(1 << n,bitvector(n));
    
    unsigned int cnt = 1;
    
    for(unsigned int i=0; i<n; ++i)
    {
        for(unsigned int j=0; j<cnt; ++j)
        {
            ret[cnt+j] = ret[j];
            ret[cnt+j].set(i);
        }
        cnt *= 2;
    }
}

// ----------------------------------------------------------------------

void test_gen_all_polys(std::vector<poly>& ret,const unsigned int n)
{
    // generate all polys of degree == n-1 or lower
    
    std::vector<bitvector> bs;
    test_gen_all_bitvectors(bs,n);
    ret.resize(bs.size());
    
    for(unsigned int i=0; i<bs.size(); ++i)
    {
        ret[i].swapbits(bs[i]);
    }
}

// ----------------------------------------------------------------------

// Convert a bitvector of n*n bits to a n*n row-major matrix with rows
// represented in poly format.
void test_bitvector_to_matrix(std::vector<poly>& ret,const bitvector& b,const unsigned int n)
{
    assert(b.size() == n*n);
    ret.resize(n);
    
    for(unsigned int row=0; row<n; ++row)
    {
        bitvector rb(n);
        for(unsigned int col=0; col<n; ++col)
        {
            if(b.get(n*row+col))
            {
                rb.set(col);
            }
        }
        ret[row].swapbits(rb);
    }
}

// ----------------------------------------------------------------------

// For test purposes, generate all n*n matrices
void test_gen_matrices(std::vector< std::vector<poly> >& ret,const unsigned int n)
{
    assert(n<5); // silly otherwise
    
    std::vector<bitvector> bvs;
    test_gen_all_bitvectors(bvs,n*n);
    
    ret.resize(bvs.size());
    
    for(unsigned int i=0; i<bvs.size(); ++i)
    {
        test_bitvector_to_matrix(ret[i],bvs[i],n);
    }
}

// ----------------------------------------------------------------------

void
basic_tests()
{
    // tests of all the basic support funtions and classes.
    
    std::vector<poly> data;
    test_gen_all_polys(data,5);
    
    for(unsigned int i=0; i<data.size(); ++i)
    {
        std::cout << data[i].to_string() << "\n";
    }
    
    // Check comparissons and basic arithmetic ...
    
    for(unsigned int i=0; i<data.size(); ++i)
    {
        for(unsigned int j=0; j<data.size(); ++j)
        {
            assert((data[i] == data[j]) == (i==j));
            assert((data[i] != data[j]) == (i!=j));
            assert((data[i] <  data[j]) == (i< j));
            assert(data[i]+data[j] == data[i^j]);
            assert(data[i]-data[j] == data[i^j]);
        }
    }
    
    // Check pow(), and multiplication with large bit fields ...
    
    for(int i=0; i<100; ++i)
    {
        bitvector b(i+1);
        b.set(i);
        poly p;
        p.swapbits(b);
        poly q = poly::X().pow(i);
        assert(p==q);
        
        if(i == 0)
        {
            assert(poly().pow(i) == poly::unit());
        }
        else
        {
            assert(poly().pow(i) == poly());
        }
        
        assert(poly() * q == poly());
        assert(q * poly() == poly());
    }
    
    // Some division tests in large bit fields ...
    
    for(int i=0; i<100; ++i)
    {
        for(int j=0; j<i; ++j)
        {
            poly a = poly::X().pow(i);
            poly b = poly::X().pow(j);
            poly q = b.div(b);
            assert(b.is_zero());
            assert(q == poly::X().pow(i-j));
        }
    }
    
    // Division and remainder tests on small bit fields but comprehensive ...
    
    for(unsigned int i=0; i<data.size(); ++i)
    {
        for(unsigned int j=0; j<data.size(); ++j)
        {
            poly a = data[i];
            poly b = data[j];
            if(!b.is_zero())
            {
                std::cout << a << " / " << b << " = ";
                poly r = a;
                poly q = r.div(b);
                std::cout << q << " remainder " << r << "\n";
                assert(r.degree() < b.degree());
                assert(q*b + r == a);
            }
        }
    }
    
    // Some tests for "gcd" ...
    
    for(unsigned int i=0; i<data.size(); ++i)
    {
        for(unsigned int j=0; j<data.size(); ++j)
        {
            const poly a = data[i];
            const poly b = data[j];
            const poly g = gcd(a,b);
            std::cout << "gcd(" << a << "," << b << ") = " << g << "\n";
            assert(g.divides(a));
            assert(g.divides(b));
            
        }
    }
    
    // More tests for "gcd" in large bit fields ...
    
    for(unsigned int i=0; i<500; i+=11)
    {
        for(unsigned int j=0; j<i; j+=13)
        {
            poly p(poly::X().pow(i));
            poly q(poly::X().pow(j));
            assert(gcd(p,q) == q);
            assert(gcd(q,p) == q);
        }
    }
    
    // test square-free factorisation (and collect a set of known
    // smallish polynomials with square-free factors) ...
    
    std::set<poly> sffs;
    
    for(unsigned int i=0; i<data.size(); ++i)
    {
        for(unsigned int j=0; j<data.size(); ++j)
        {
            poly f = data[i]*data[j];
            if(f.is_zero())
            {
                continue;
            }
            std::cout << "factors of " << f << " ...\n";
            std::vector< std::pair<poly,unsigned int> > factors;
            square_free_factors(f,factors);
            poly product = poly::unit();
            for(unsigned int i=0; i<factors.size(); ++i)
            {
                sffs.insert(factors[i].first);
                std::cout << "  factor " << factors[i].first << " ** " << factors[i].second << "\n";
                for(int k=0; k<data.size(); ++k)
                {
                    if(data[k].degree() > 0)
                    {
                        assert(!data[k].squared().divides(factors[i].first));
                    }
                }
                
                product = product * factors[i].first.pow(factors[i].second);
            }
            assert(product == f);
        }
    }
    
    // Testing the fixpoint finder ...
    
    std::vector< std::vector<poly> > mats;
    test_gen_matrices(mats,4);
    bool found4 = false;
    
    for(unsigned int i=0; i<mats.size(); ++i)
    {
        
        fixpoint_finder ff;
        ff.init(mats[i]);
        poly fp;
        unsigned int num = 0;
        
        while(ff.next(fp))
        {
            //std::cout << "fixpoint: " << fp << " " << matmul(fp,mats[i]) << "\n";
            assert(matmul(fp,mats[i]) == fp);
            num += 1;
        }
        
        if(num == 4)
        {
            found4 = true;
        }
    }
    
    assert(found4);
    
    // Now test the Berlekamp finder ...
    
    std::vector<poly> sffv(sffs.begin(),sffs.end());
    
    for(unsigned int i=0; i<sffv.size(); ++i)
    {
        const poly u(sffv[i]);
        // std::cout << "berlekamp find on " << u << "\n";
        berlekamp_finder bf(u);
        poly v;
        
        while(bf.next(v))
        {
            // std::cout << " a fixpoint is " << v << " ... " << (v.squared() % u) << "\n";
            assert(v == v.squared() % u);
        }
    }
    
    // Finally, test the Berlekamp factorisation ...
    
    for(unsigned int i=0; i<sffv.size(); ++i)
    {
        const poly u(sffv[i]);
        std::vector<poly> factors;
        std::cout << "berlekamp factor on " << u << "\n";
        berlekamp(factors,u);
        poly product = poly::unit();
        
        for(unsigned int i=0; i<factors.size(); ++i)
        {
            std::cout << "  factor " << factors[i] << "\n";
            product = product * factors[i];
        }
        
        assert(product == u);
    }
    
}

// ----------------------------------------------------------------------

poly prod(const std::vector<poly>& ps)
{
    poly ret(poly::unit());
    
    for(unsigned int i=0; i<ps.size(); ++i)
    {
        ret = ret * ps[i];
    }
    
    return ret;
}

// ----------------------------------------------------------------------

void major_tests()
{
    // test of factorisation of very large things
    
    std::default_random_engine prng;
    std::uniform_int_distribution<int> dist(0,1);
    std::set<poly> large_irreducibles;
    
    // test some very large polynomials can be factored ...
    
    for(unsigned int i=0; i<100; ++i)
    {
        poly u;
        
        while(u.is_zero())
        {
            bitvector bs(300);
            
            for(unsigned int j=0; j<bs.size(); ++j)
            {
                if(dist(prng))
                {
                    bs.set(j);
                }
            }
            
            u.swapbits(bs);
        }
        
        // std::cout << "factorising " << u << "\n";
        clock_t t0 = clock();
        std::vector<poly> factors = factorise(u);
        poly p = poly::unit();
        
        for(unsigned int j=0; j<factors.size(); ++j)
        {
            // std::cout << "  factor " << factors[j] << std::endl;
            if(factors[j] != poly::X())
            {
                assert(! ( poly::X().divides(factors[j]) )); // it certainly wouldn't be irreducible in this case
            }
            p = p * factors[j];
            if(factors[j].degree() > 250)
            {
                large_irreducibles.insert(factors[j]);
                // std::cerr << "added irreducible " << factors[j] << "\n";
            }
        }
        
        assert(p == u);
        
        std::cout << "facorised degree " << u.degree()
        << " polynomial in " << float(clock()-t0)/CLOCKS_PER_SEC << "\n";
    }
    
    std::cout << "collected " << large_irreducibles.size() << " large irreducibles for further testing\n";
    
    std::vector<poly> lir(large_irreducibles.rbegin(),large_irreducibles.rend());
    assert(lir.size() >= 10);
    lir.resize(10);
    for(unsigned int i=0; i<lir.size(); ++i)
    {
        //std::cout << "lir contains " << lir[i] << "\n";
        assert( !poly::X().divides(lir[i]) ); // it certainly wouldn't be irreducible in this case
    }
    
    for(unsigned int i=0; i<lir.size(); ++i)
    {
        for(unsigned int j=i; j<lir.size(); ++j)
        {
            const poly p1(lir[i]);
            const poly p2(lir[j]);
            const poly u = p1*p2;
            
            //std::cout << "p1 = " << p1 << "\n";
            //std::cout << "p2 = " << p2 << "\n";
            
            const clock_t t0 = clock();
            const std::vector<poly> fs = factorise(u);
                        
            assert(prod(fs) == u);
            assert(fs.size() == 2);
            assert(fs[0] == p1 || fs[0] == p2);
            assert(fs[1] == p1 || fs[1] == p2);
            assert(p1 == fs[0] || p1 == fs[1]);
            assert(p2 == fs[0] || p2 == fs[1]);
            std::cout << "facorised " << p1.degree() << "+" << p2.degree() << " = " << u.degree() << " polynomial in "
            << float(clock()-t0)/CLOCKS_PER_SEC << "\n";
        }
    }
}

// ----------------------------------------------------------------------

void get_fits(std::set< std::pair<poly,poly> >& fits,
              const std::vector<poly>& factors,
              const unsigned int index,
              const poly& lhs,
              const poly& rhs,
              const unsigned int maxdegree)
{
    if(lhs.degree() > maxdegree)
    {
        return;
    }
    
    if(rhs.degree() <= maxdegree)
    {
        fits.insert(std::make_pair(lhs,rhs));
    }
    
    if(index < factors.size())
    {
        assert((rhs % factors[index]).is_zero());
        get_fits(fits,factors,index+1,lhs,rhs,maxdegree);
        get_fits(fits,factors,index+1,lhs * factors[index],rhs/factors[index],maxdegree);
    }
}

// ----------------------------------------------------------------------

std::vector<std::string> decrypt(int size, const char * str)
{
    // actually, we dont know how many bits are in our input until
    // we've read it all.
        
    unsigned int nbits = size*2; // number of bits in the thing we're going to read in.
    nbits *= 2; // for some reason
    bitvector bits(0);
    std::istringstream is(str);

    bits.parse(is,nbits);
    poly f;
    f.swapbits(bits);
    
    const std::vector<poly> ps = factorise(f);
    
    // Now produce all of the factorisations that "fit" ...
    std::set< std::pair<poly,poly> > fits0;
    get_fits(fits0,ps,0,poly::unit(),f,nbits/2);
    std::vector< std::pair<poly,poly> > fits(fits0.begin(),fits0.end());
    
    std::vector<std::string> outbuf;
    for(unsigned int i=0; i<fits.size(); ++i)
    {
        std::ostringstream os;
        bitvector b1 = fits[i].first.bits();
        bitvector b2 = fits[i].second.bits();
        b1.resize(nbits/2);
        b2.resize(nbits/2);
        os << b1.hex_string() << " " << b2.hex_string();
        outbuf.push_back(os.str());
    }
    
    std::sort(outbuf.begin(),outbuf.end());
    
    //std::cerr << "time: " << float(clock()-t0)/CLOCKS_PER_SEC << " second(s)\n";
    
    return outbuf;
}

