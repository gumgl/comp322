#include "gardens.h"
#include <stack>
#include <iostream>
#include <math.h>

 /* 0-credit */
Fraction ContinuedFraction::getApproximation(unsigned int k) const {
    // start with 1/0
    Fraction toRet;
    toRet.numerator = 1;
    toRet.denominator = 0;
    
    
    // we go backwards from the end to the beginning to compute the approximation
    // to do this, we need to collect on a stack all the numbers we'll use for the apx
    stack<cf_int> ints;
    // make sure iterator starts at beginning
    resetIterator();
    while (!hasNoMore() && k-- > 0) {
        ints.push(next());
    }
    
    // do the math for adding an integer to a partial solution:
    // x + 1 / (n / d) = x + d / n = (x*n + d) / n
    while (!ints.empty()) {
        cf_int x = ints.top();
        cf_int n = toRet.numerator;
        cf_int d = toRet.denominator;
        toRet.numerator = x * n + d;
        toRet.denominator = n;
        ints.pop();
    }
    // must reset iterator for the next operation using it
    resetIterator();
    return toRet;
}


RationalCF::RationalCF(Fraction f) : PeriodicCF({}) {
    if (f.numerator == 0) { // if the fraction is 0
        fixedPart.push_back(0);
        return;
    }
    // same as getCFlargerThanOne from hw1
    while (f.denominator != 0) {
        if (f.numerator != 0) {
            fixedPart.push_back(f.numerator / f.denominator);
        }
        auto tmp = f.numerator % f.denominator;
        f.numerator = f.denominator;
        f.denominator = tmp;
    }
}

RationalCF::~RationalCF() {}

/* QUESTION 3*/

cf_int PeriodicCF::next() const {
    auto iteratorPosition = *(this->iteratorPosition); //save previous position
    (*(this->iteratorPosition))++; // increment previous position
    if (iteratorPosition < fixedPart.size()) { // if still in the fixed part
        return fixedPart[iteratorPosition];
    }else { // if in the periodic part
        auto positionInPeriodic = (iteratorPosition - fixedPart.size()) % periodicPart.size();
        return periodicPart[positionInPeriodic];
    }
    
    
}

bool PeriodicCF::hasNoMore() const {
    return periodicPart.empty() // if not periodic
            && *iteratorPosition >= fixedPart.size(); // and done with the fixed part
}

void PeriodicCF::resetIterator() const {
    *iteratorPosition = 0;
}

PeriodicCF::~PeriodicCF() {
    delete iteratorPosition;
}



/* QUESTION 4*/

MagicBoxCF::MagicBoxCF(ContinuedFraction const* f, unsigned long aParam, unsigned long bParam) : boxedFraction{f}, a{aParam}, b{bParam} {
    mbnums = new cf_int[4];
    mbnums[0] = a;
    mbnums[1] = b;
    mbnums[2] = 1;
    mbnums[3] = 0;
}

cf_int MagicBoxCF::next() const {
    if(hasNoMore()) return 0;
    cf_int &i = mbnums[0];
    cf_int &j = mbnums[1];
    cf_int &k = mbnums[2];
    cf_int &l = mbnums[3];
    
    // return q and change box accordingly
    cf_int q = i / k;
    cf_int  ii = k,
            jj = l,
            kk = i - k * q,
            ll = j - l * q;
    i = ii;
    j = jj;
    k = kk;
    l = ll;
    
    return q;
}

bool MagicBoxCF::hasNoMore() const {
    cf_int &i = mbnums[0];
    cf_int &j = mbnums[1];
    cf_int &k = mbnums[2];
    cf_int &l = mbnums[3];
    
    while( ((k == 0 || l == 0) && !(k == 0 && l == 0)) ||
          (k != 0 && l != 0 && i / k != j / l) ) {
        if(boxedFraction->hasNoMore()) { // no more integers to spit from cf
            i = j;
            k = l;
            continue;
        }
        //read p and change box accordingly
        cf_int p = boxedFraction->next();
        cf_int  ii = j,
                jj = i + j * p,
                kk = l,
                ll = k + l * p;
        i = ii;
        j = jj;
        k = kk;
        l = ll;
    }
    return k == 0 && l == 0;
}

void MagicBoxCF::resetIterator() const {
    boxedFraction->resetIterator();
    mbnums[0] = a;
    mbnums[1] = b;
    mbnums[2] = 1;
    mbnums[3] = 0;
}

MagicBoxCF::~MagicBoxCF() {
    delete [] mbnums;
}



/* QUESTION 5*/

ostream &operator<<(ostream& outs, const ContinuedFraction &cf) {
    // print at most 10 integers
    const int init_k = 10;
    
    int k = init_k;
    // make sure the iterator starts at the beginning
    cf.resetIterator();
    outs << "[";
    while (!cf.hasNoMore() && k-- > 0) {
        outs << cf.next();
        if (!cf.hasNoMore() && k != 0) {
            outs << ((k == init_k - 1) ? "; " : ", ");
        }
    }
    if(!cf.hasNoMore()) { outs << " ..."; }
    outs << "]";
    cf.resetIterator();
    return outs;
}


/* QUESTION 6 */

float Flower::getAngle(unsigned int k) const {
    //get approximation
    Fraction fr = theta->getApproximation(apx_length);
    // keep only fractional part of k*fr
    double fractpart = ( (k * fr.numerator) % fr.denominator // numerator
                        / (double)fr.denominator); // denominator
    return (2 * pie * fractpart);
}

Flower::Flower(const ContinuedFraction *f, unsigned int apxLengthParam) : theta{f}, apx_length(apxLengthParam) { }

Seed Flower::getSeed(unsigned int k) const {
    Seed s; // seed to return
    float angle = getAngle(k); // get angle first
    s.x = sqrt(k / (pie * 1.0)) * cos(angle);
    s.y = sqrt(k / (pie * 1.0)) * sin(angle);
    return s;
}

vector<Seed> Flower::getSeeds(unsigned int k) const {
    vector<Seed> toRet;
    for (int ada = 0; ada < k; ada++) {
        toRet.push_back(getSeed(ada));
    }
    return toRet;
}


Flower::~Flower() {}

/* QUESTION 7*/

void Flower::writeMVGPicture(ostream &out, unsigned int N, unsigned int H, unsigned int W) const {
    // start at the center of the picture
    auto center_x = H / 2;
    auto center_y = W / 2;
    
    // find the size of the circle min(W,H) / 100
    auto size_circle = min(H, W) / 100;
    
    int k = 0;
    for(auto& oneSeed : getSeeds(N)) {
        // C_x and C_y
        int x = center_x + oneSeed.x * (center_x - 100) / sqrt(N / pie);
        int y = center_y + oneSeed.y * (center_y - 100) / sqrt(N / pie);
        // radius
        int radius = sqrt(k++) / sqrt(N) * size_circle ;
        if (radius < 1) radius = 1;
        // print the command based on the center and the radius
        out << "fill blue circle " << x << "," << y << " " << (x+radius) << "," << y << endl;
    }
    
}





