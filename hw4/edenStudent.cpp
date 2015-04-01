#include "eden.h"

#include <stack>


/* Question 2 : 0-credit */

/*  getting an approximation using the new Fraction class */
Fraction<cf_int> ContinuedFraction::getApproximation(unsigned int k) const {
    //TODO
}

/* Building a rational cf using the new Fraction class*/
RationalCF::RationalCF(Fraction<cf_int> f) {
    //TODO
}

/* Question 3 : Euler squared */

Iterator *EulerSquared::getIterator() const {
    //TODO
}


cf_int EulerSquaredIterator::next() {
    // [7 ; 2, 1, 1, 3, 18, 5, 1, 1, 6, 30, 8, 1, 1, 9, 42, 11, 1, 1 ...];
    //TODO
}

bool EulerSquaredIterator::isDone() const {
    //TODO
}


/* Question 4 : PeriodicCF iterator*/

Iterator *PeriodicCF::getIterator() const {
    //TODO
}

cf_int PeriodicCFIterator::next() {
    //TODO
}

bool PeriodicCFIterator::isDone() const {
    //TODO
}


/* Question 5 : MagicBoxCF iterator */

Iterator *MagicBoxCF::getIterator() const {
    //TODO
}

cf_int MagicBoxCFIterator::next() {
    //TODO
}

bool MagicBoxCFIterator::isDone() const {
    //TODO
}



