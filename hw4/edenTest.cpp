
#include <iostream>
#include <vector>
#include <stack>

#include "eden.h"
#include "fraction.h"

using namespace std;



/** Continued Fractions **/


void tryOutFraction() {
    Fraction<int> twoOverThree(20,30);
    
    cout << twoOverThree << " simplified is ";
    twoOverThree.simplify();
    cout << twoOverThree << endl;
    
    cout << "Fractions of fractions: " << endl;
    Fraction<int> fiveOverSix(5,6);
    Fraction<Fraction<int>> f3(twoOverThree,fiveOverSix);
    Fraction<Fraction<int>> f5(fiveOverSix,twoOverThree);
    cout << f3 << " times " << f5 << " is " << f3 * f5 << endl;
    Fraction<Fraction<int>> f35 = f3 * f5;
    cout << "...maybe we should simplify that " << f35.quotient();
    Fraction<int> f35q = f35.quotient();
    f35q.simplify();
    cout << "...even better " << f35q << " or " << f35q.quotient() << endl;

    cout << "Fractions of doubles: ";
    Fraction<double> fff(3.0,4.0);
    cout << fff << " is " << fff.quotient() << endl;
    
    cout << "--------------------\nFractions and exceptions: " << endl;
    Fraction<int> infty(5,0);
    cout << "5/0 is saved as " << infty << endl;
    Fraction<int> zero(0,5);
    cout << "0/5 is saved as " << zero << endl;
    
    try {
        Fraction<int> bad(0,0);
        cout << "NO! You shouldn't have a 0/0 fraction!" << endl;
    }catch(int) {
        cout << "0/0 throws an exception!" << endl;
    }

    try {
        Fraction<int> bad1(1,0);
        Fraction<int> bad2(0,1);
        bad1 * bad2;
        cout << "NO! Infinity * 0 should not work!" << endl;
    }catch(int) {
        cout << "Infinity times zero makes no sense" << endl;
    }
    
    try {
        Fraction<int> bad1(1,0);
        Fraction<int> bad2(9,0);
        bad1 / bad2;
        cout << "NO! Infinity / Infinity should not work!" << endl;
    }catch(int) {
        cout << "Infinity / infinity makes no sense" << endl;
    }
    
    try {
        Fraction<int> bad1(1,0);
        Fraction<int> bad2(3,0);
        bad1 - bad2;
        cout << "NO! Infinity - infinity should not work!" << endl;
    }catch(int) {
        cout << "Infinity - infinity makes no sense" << endl;
    }
}

int main(int argc, const char * argv[]) {
    // Fraction part - 0 credit
    tryOutFraction();
    cout << "-------------------" << endl;
    // check fraction simplification
    Fraction<cf_int> seventyFiveOverThirtyThree = {75,33};
    cout << seventyFiveOverThirtyThree << " simplified directly: ";
    seventyFiveOverThirtyThree.simplify();
    cout << seventyFiveOverThirtyThree << endl;
    
    Fraction<cf_int> seventyFiveOverThirtyThree2 = {75,33};
    ContinuedFraction *b = new RationalCF(seventyFiveOverThirtyThree2);
    ContinuedFraction &z = *b;
    
    cout << seventyFiveOverThirtyThree2 << " simplified using cfs: ";
    cout << z.getApproximation(100) << endl;
    cout << "-------------------" << endl;
    EulerSquared eulerSquared;
    cout << "e squared: " << eulerSquared << endl;
    cout << "e squared approximation: " << eulerSquared.getApproximation(10) << endl;
    cout << "Esquared Sequence: ";
    for(auto gh = 0; gh < 10; gh++) {
        cout << eulerSquared.getApproximation(gh).getNumerator() << " ";
    }cout << endl;
    cout << "-------------------" << endl;
    PeriodicCF goldenRatio({1});
    cout << "Golden ratio: " << goldenRatio << endl;
    cout << "Golden ratio approximation: " << goldenRatio.getApproximation(10) << endl;
    cout << "Fibonnaci Sequence: ";
    for(auto gh = 0; gh < 20; gh++) {
        cout << goldenRatio.getApproximation(gh).getNumerator() << " ";
    }cout << endl;
    cout << "-------------------" << endl;
    
    PeriodicCF sqrt5({2},{4});
    cout << "Square root 5: " << sqrt5 << endl;
    cout << "Square root 5 approximation: " << sqrt5.getApproximation(10) << endl;
    cout << "Sqrt5 Sequence: ";
    for(auto gh = 0; gh < 20; gh++) {
        cout << sqrt5.getApproximation(gh).getNumerator() << " ";
    }cout << endl;
    cout << "-------------------" << endl;
    
    MagicBoxCF sqrt20(sqrt5,0,2);
    cout << "Square root 20: " << sqrt20 << endl;
    cout << "Square root 20 approximation: " << sqrt20.getApproximation(10) << endl;
    cout << "Sqrt20 Sequence: ";
    for(auto gh = 0; gh < 20; gh++) {
        cout << sqrt20.getApproximation(gh).getNumerator() << " ";
    }cout << endl;

}









