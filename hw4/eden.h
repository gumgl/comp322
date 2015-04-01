#ifndef hw4_eden_h
#define hw4_eden_h

#include <vector>
#include "fraction.h"

using namespace std;

//--- shorthand notation for unsigned long
typedef unsigned long cf_int;


//--- Defines an interface/virtual class for an iterator that would allow one to work with continued fractions
class Iterator {
public:
    //returns the next element in the iterator. Should throw an integer equal to 1 if no more elements can be listed using this iterator
    virtual cf_int next() = 0;
    //returns true if no more elements are to be listed using this iterator
    virtual bool isDone() const = 0;
    
    virtual ~Iterator() {}
};




//--- Defines an interface/virtual class for a simple continued fraction
class ContinuedFraction {
    friend class MagicBoxCF;
protected:
    //-- TODO getIterator - returns an iterator over the current continued fraction
    virtual Iterator *getIterator() const = 0;
public:
    /*--TODO getApproximation: return the approximation - much like the previous homework assignments
     * -> 'k'  is the maximum number of integers to use for the approximation
     * -> It should throw an exception (int equal to 1) if k is 0
     **/
    Fraction<cf_int> getApproximation(unsigned int k) const;
    
    virtual ~ContinuedFraction() {}
    
    // prints up to 10 elements in the continued fraction
    friend ostream &operator<<(ostream &outs, const ContinuedFraction &cf) {
        const int init_k = 10;
        int k = init_k;
        Iterator *ada = cf.getIterator();
        outs << "[";
        while (!ada->isDone() && k-- > 0) {
            outs << ada->next();
            if (!ada->isDone() && k != 0) {
                outs << ((k == init_k - 1) ? "; " : ", ");
            }
        }
        if(!ada->isDone()) { outs << " ..."; }
        outs << "]";
        delete ada;
        return outs;
    }
};



//--- Defines a class for periodic continued fractions
class PeriodicCF : public ContinuedFraction {
    friend class PeriodicCFIterator;
protected:
    // data
    vector<cf_int> fixedPart;
    vector<cf_int> periodicPart;
    
    //--TODO: returns a PeriodicCFIterator, properly initialized
    Iterator *getIterator() const;
    
    //--Might have to use it in classes inheriting from this
    PeriodicCF() {}
public:
    PeriodicCF(const vector<cf_int> &fixedParam, const vector<cf_int> &periodicParam) : fixedPart{fixedParam}, periodicPart{periodicParam} {
        if (fixedParam.empty() && periodicParam.empty()) throw 1;
    }
    PeriodicCF(const vector<cf_int> &periodicParam) : PeriodicCF({}, periodicParam) {}
    ~PeriodicCF() {}
};

//--- TODO Defines a class for periodic continued fraction iterators
class PeriodicCFIterator : public Iterator {
private:
    //-- the PeriodicCF that it iterates over
    const PeriodicCF &cf;
    //-- position of the iterator
    unsigned int it;
public:
    // takes in as parameter the PeriodicCF which one would iterate over
    PeriodicCFIterator(const PeriodicCF &cf) : cf{cf}, it{0} {}
    
    //--TODO
    cf_int next();
    //--TODO
    bool isDone() const;
};


class RationalCF : public PeriodicCF {
public:
    RationalCF (const vector<cf_int> &fixedParam) : PeriodicCF(fixedParam,{}) {}

    // TODO : constructor takes a fraction as parameter and using code from previous assignments, computes the fixed part vector of integers for this cf (HINT: might want to use the protected constructor in PeriodicCF
    RationalCF (Fraction<cf_int> frac);
    
    ~RationalCF() {}
    
    //----additional methods
    unsigned int length() const {return (unsigned int) PeriodicCF::fixedPart.size(); }
    Fraction<cf_int> getValue() const { return PeriodicCF::getApproximation(length()); }
};


class MagicBoxCF : public ContinuedFraction {
   friend class MagicBoxCFIterator;
protected:
    //-- the fraction boxed - same as in HW3
    const ContinuedFraction &boxedFraction;
    //-- this MagicBoxCF will represent a+b*x, where x is the boxedFraction
    const cf_int a,b;
    
    //--TODO returns a MagicBoxCFIterator, properly initialized
    Iterator *getIterator() const ;
public:
    MagicBoxCF(const ContinuedFraction &f, cf_int a, cf_int b) : boxedFraction{f}, a{a}, b{b} {}
    ~MagicBoxCF() {}
};



//--- TODO Defines a class for periodic continued fraction iterators
class MagicBoxCFIterator : public Iterator {
private:
    //-- the 4 integers used to keep track of the magic box
    cf_int i,j,k,l;
    //-- iterator over the boxed fraction
    Iterator *boxedIterator;
    
    //-- this method updates the indeces untill either k=l=0, or a new integer can be extracted for this magic box(i.e. we can return a value q)
    void updateIndeces() {
        while( ((k == 0 || l == 0) && !(k == 0 && l == 0)) ||
              (k != 0 && l != 0 && i / k != j / l) ) {
            // no more integers to spit from cf
            if(boxedIterator->isDone()) {
                i = j;
                k = l;
                continue;
            }
            //read p
            
            cf_int p = boxedIterator->next();
            
            //change box
            cf_int ii = j,
            jj = i + j * p,
            kk = l,
            ll = k + l * p;
            i = ii;
            j = jj;
            k = kk;
            l = ll;
        }
    }
public:
    MagicBoxCFIterator(Iterator *cf, cf_int a, cf_int b) : boxedIterator{cf}, i{a}, j{b}, k{1}, l{0} {
        updateIndeces();
    }
    
    ~MagicBoxCFIterator() { delete boxedIterator; }
    
    //--TODO : use updateIndeces!
    cf_int next();
    
    //--TODO
    bool isDone() const;
};


//-- Represents the continued fraction of e^2, as we computed in hw2
class EulerSquared : public ContinuedFraction {
    friend class EulerSquaredIterator;
protected:
    //--TODO returns a EulerSquaredIterator, properly initialized
    Iterator *getIterator() const;
};

//--TODO: iterator for iterating over the cf of e^2
class EulerSquaredIterator : public Iterator {
private:
    //-- index keeping track of the number of elements already returned by this iterator (starts at 0)
    unsigned int index;
public:
    EulerSquaredIterator(): index{0} {}
    
    //--TODO
    cf_int next();
    //--TODO
    bool isDone() const;
};

#endif
