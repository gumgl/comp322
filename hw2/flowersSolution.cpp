#include "flowers.h"
#include <math.h>


unsigned int spitEulerSquare(unsigned int index) {
    // [7 ; 2, 1, 1, 3, 18, 5, 1, 1, 6, 30, 8, 1, 1, 9, 42, 11, 1, 1 ...];
    if(index == 0) return 7; // first item
	if(index == 1) return 2; // second item
	if(index % 5 == 2 || index%5 == 3) return 1; // all the 1s
	if(index % 5 == 4) return index/5 * 3 + 3; //3,6,9,12...etc
	if(index % 5 == 0) return index/5 * 12 + 6; // 18, 30, 42, etc...
	return index/5 * 3 + 2; // 5,8,11,14 etc....
}

int spitNextMagicBox(MagicBox &box) {
	while( ((box.k == 0 || box.l == 0) && !(box.k == 0 && box.l == 0)) ||
            (box.k != 0 && box.l != 0 && box.i / box.k != box.j / box.l) ) {
		// while the indeces are not yet ready to spit q
		if(box.boxedFraction.periodicPart.size() == 0 && box.indexInBoxedFraction >= box.boxedFraction.fixedPart.size()) {
            // no more integers to spit from cf
			box.i = box.j;
			box.k = box.l;
            continue;
		}
		//read p
		int idx = box.indexInBoxedFraction;
        int p = (idx >= box.boxedFraction.fixedPart.size()) ?
            // p is inside the periodic part
            box.boxedFraction.periodicPart[(idx - box.boxedFraction.fixedPart.size()) % box.boxedFraction.periodicPart.size()] :
            // else p is inside the fixed part
            box.boxedFraction.fixedPart[idx];
			
        // increment the index
		box.indexInBoxedFraction++;
        
		//change box accordingly
		int i = box.j,
            j = box.i + box.j * p,
			k = box.l,
			l = box.k + box.l * p;
		box.i = i;
		box.j = j;
		box.k = k;
		box.l = l;
    }
    // if we reached the end of the cf - return -1
	if(box.k == 0 && box.l == 0) return -1;
    
    // return q and change box accordingly
	int q = box.i / box.k;
	int i = box.k,
        j = box.l,
		k = box.i - box.k * q,
		l = box.j - box.l * q;
	box.i = i;
	box.j = j;
	box.k = k;
	box.l = l;
	return q;
}


ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
	// initialize magic box
    MagicBox mb;
	mb.boxedFraction = f;
	mb.i = a;
	mb.j = b;
    mb.k = 1;
    mb.l = 0;
    mb.indexInBoxedFraction = 0;
    
    auto toRet = new ContinuedFraction; // will be returned
	for (int ada = 0; ada < length; ++ada) {
		int tmp = spitNextMagicBox(mb);
		if(tmp < 0) break; // if we reached the end of the cf, just break
		toRet->fixedPart.push_back(tmp);
	}
	return *toRet;
}

ContinuedFraction scaleCF(ContinuedFraction &theta, int k) {
    int length = 5;
    if (k == 1) {
        return theta; // don't use a MB if the scale is 1
    }
    return getCFUsingMB(theta, 0, k, length);
}


Fraction getApproximation(ContinuedFraction &fr, unsigned int n){
    Fraction toRet; // will be returned
    
    // we go backwards from the end to the beginning to compute the approximation
    // z is the index that keeps track of the position reached - starts at n-1
    int z = n-1;
    
    // start with 1/0
    toRet.numerator = 1;
    toRet.denominator = 0;
    
    auto m = fr.periodicPart.size(); // m is the length of the periodic part
    auto l = fr.fixedPart.size(); // l is the length of the fixed part
    
    for (; m > 0 && z >= l; z--) { // first do the periodic part - if m > 0
        auto idx = (z-l) % m; // get idex in the periodic part

        // change the numerator and denominator
        auto tmp = toRet.numerator;
        toRet.numerator = fr.periodicPart[idx] * toRet.numerator + toRet.denominator;
        toRet.denominator = tmp;
    }
    
    for (; z >= 0; z--) { // do the fixed part now
        // change the numerator and denominator
        auto tmp = toRet.numerator;
        toRet.numerator = fr.fixedPart[z] * toRet.numerator + toRet.denominator;
        toRet.denominator = tmp;
    }
    return toRet;
}


double getAngle(ContinuedFraction &theta, int k) {
    // copy cf so that the original is not modified
    ContinuedFraction cfr = theta;
    // keep only the fractional part
    cfr.fixedPart[0] = 0;
    // get approximation using 7 digits
    Fraction fr = getApproximation(cfr, 7);
    // compute fractional part of the rotations
    double fractpart = ((k*fr.numerator)%fr.denominator/(double)fr.denominator);
    //return
    return (2 * M_PI * fractpart);
}

Seed getSeed(ContinuedFraction &theta, int k) {
	Seed s;
    // we follow the formulas in the assignment's document
    float angle = getAngle(theta, k);
    s.x = sqrt(k / (M_PI * 1.0)) * cos(angle);
    s.y = sqrt(k / (M_PI * 1.0)) * sin(angle);
    return s;
}

void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
    flower.push_back(getSeed(theta, (int) flower.size()));
}
