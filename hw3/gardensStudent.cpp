#include "gardens.h"
#include <stack>
#include <iostream>
#include <math.h>

 /* 0-credit */
Fraction ContinuedFraction::getApproximation(unsigned int k) const {
	std::stack<cf_int> numbers;
	Fraction toRet;

	unsigned int i = 1;
	resetIterator();
	while (i <= k && !hasNoMore()) { // Get those numbers ;)
		numbers.push(next());
		i++;
	}

	if (!numbers.empty()) { // If we got some numbers
		toRet.numerator = numbers.top();
		toRet.denominator = 1;
		numbers.pop();

		while (!numbers.empty()) {
			auto tmp = toRet;
			toRet.numerator = tmp.numerator * numbers.top() + tmp.denominator;
			toRet.denominator = tmp.numerator;
			numbers.pop();
		}
	} else { // Either k==0 or CF is empty
		toRet.numerator = 0;
		toRet.denominator = 1;
	}

	if (toRet.denominator == 0) {
		std::cout << "ERROR DIVISION BY 0 TSSS...!" << std::endl;
		toRet.denominator = 1;
	}
	resetIterator();
    return toRet;
}


// TODO : RationalCF::RationalCF(Fraction f) ...
RationalCF::RationalCF(Fraction f) : PeriodicCF({}, {}) {
	if (f.denominator != 0) {
		Fraction work = f;
		while (true) { // add remainders
			fixedPart.push_back(work.numerator / work.denominator); // the integer part
			if (work.numerator % work.denominator == 0) // base case
				break;
			else {
				auto tmp = work;
				work.numerator = tmp.denominator;
				work.denominator = tmp.numerator % tmp.denominator;
			}
		}
	} else {
		cout << "Denominator is 0 in RationalCF ctor" << endl;
	}
}
RationalCF::~RationalCF() {
	//delete iteratorPosition;
}

/* QUESTION 3*/

cf_int PeriodicCF::next() const {
	auto n = fixedPart.size();
	auto m = periodicPart.size();
	cf_int toRet = -1;

	if(*iteratorPosition < n) {
		toRet = fixedPart[*iteratorPosition];
		(*iteratorPosition) ++;
	} else if (m != 0) {
		toRet = periodicPart[(*iteratorPosition - n) % m];
		(*iteratorPosition) ++;
	}

	return toRet;
}

bool PeriodicCF::hasNoMore() const {
	return (*iteratorPosition >= fixedPart.size() && periodicPart.size() == 0);
}

void PeriodicCF::resetIterator() const {
	*iteratorPosition = 0;
}

PeriodicCF::~PeriodicCF() {
    delete iteratorPosition;
}



/* QUESTION 4*/

//TODO : MagicBoxCF::MagicBoxCF(ContinuedFraction const* f, unsigned long aParam, unsigned long bParam) ...
MagicBoxCF::MagicBoxCF(ContinuedFraction const* f, unsigned long aParam, unsigned long bParam)
	: boxedFraction{f}, a{aParam}, b{bParam}{
	mbnums = new cf_int[4]; // i,j,k,l = a,b,1,0
}

cf_int MagicBoxCF::next() const {
	while( ((mbnums[2] == 0 || mbnums[3] == 0) && !(mbnums[2] == 0 && mbnums[3] == 0)) ||
	            (mbnums[2] != 0 && mbnums[3] != 0 && mbnums[0] / mbnums[2] != mbnums[1] / mbnums[3]) ) {
		// while the indeces are not yet ready to spit q
		if(boxedFraction->hasNoMore()) {
			// no more integers to spit from cf
			mbnums[0] = mbnums[1];
			mbnums[2] = mbnums[3];
			continue;
		}
		//read p
		int p = boxedFraction->next();

		//change box accordingly
		int i = mbnums[1],
			j = mbnums[0] + mbnums[1] * p,
			k = mbnums[3],
			l = mbnums[2] + mbnums[3] * p;
		mbnums[0] = i;
		mbnums[1] = j;
		mbnums[2] = k;
		mbnums[3] = l;
	}
	// if we reached the end of the cf - return -1
	if(mbnums[2] == 0 && mbnums[3] == 0) return -1;

	// return q and change box accordingly
	int q = mbnums[0] / mbnums[2];
	int i = mbnums[2],
		j = mbnums[3],
		k = mbnums[0] - mbnums[2] * q,
		l = mbnums[1] - mbnums[3] * q;
	mbnums[0] = i;
	mbnums[1] = j;
	mbnums[2] = k;
	mbnums[3] = l;
	return q;
}

bool MagicBoxCF::hasNoMore() const {
	return ((mbnums[2] == 0 && mbnums[3] == 0) && boxedFraction->hasNoMore());
}

void MagicBoxCF::resetIterator() const { // i,j,k,l = a,b,1,0
	boxedFraction->resetIterator();
	mbnums[0] = a;
	mbnums[1] = b;
	mbnums[2] = 1;
	mbnums[3] = 0;
}

MagicBoxCF::~MagicBoxCF() {
    delete[] mbnums;
}



/* QUESTION 5*/

ostream &operator<<(ostream& outs, const ContinuedFraction &cf) {
	cf.resetIterator();
    int i = 0;
    const int max = 10; // display at most max numbers

    outs << "[";
    while (!cf.hasNoMore()) {

    	if (i == 1)
    		outs << "; ";
    	else if (i != 0 && i < max)
    		outs << ", ";

    	if (i < max)
    		outs << cf.next();
    	else
    		break;

    	i ++;
    }
    if (i >= max)
    	outs << " ...";
    outs << "]" << flush;

    cf.resetIterator();
	return outs;
}


/* QUESTION 6 */

float Flower::getAngle(unsigned int k) const {
	// copy cf so that the original is not modified
	//ContinuedFraction cfr = theta;
	// keep only the fractional part
	//cfr.fixedPart[0] = 0;
	// get approximation using 7 digits
	Fraction fr = theta->getApproximation(apx_length);
	// compute fractional part of the rotations
	double fractpart = ((k*fr.numerator)%fr.denominator/(double)fr.denominator);
	//return
	return (2 * pie * fractpart);
}

//TODO : Flower::Flower(const ContinuedFraction *f, unsigned int apxLengthParam) ...
Flower::Flower(const ContinuedFraction *f, unsigned int apxLengthParam)
	: theta{f}, apx_length{apxLengthParam} {

}

Seed Flower::getSeed(unsigned int k) const {
	Seed s;
	// we follow the formulas in the assignment's document
	float angle = getAngle(k);
	s.x = sqrt(k / (pie * 1.0)) * cos(angle);
	s.y = sqrt(k / (pie * 1.0)) * sin(angle);
	return s;
}

vector<Seed> Flower::getSeeds(unsigned int k) const {
	std::vector<Seed> seeds;
	for (unsigned int i=0; i<k; i++)
		seeds.push_back(getSeed(i));
	return seeds;
}

Flower::~Flower() {
    //nothing to do here
}

/* QUESTION 7*/

void Flower::writeMVGPicture (ostream &out, unsigned int N, unsigned int H, unsigned int W) const {
	auto seeds = getSeeds(N);
	for (unsigned int k=0; k<N; k++) {
		auto seed = seeds[k];
		int C_x, C_y, B_x, B_y;
		C_x = H/2 + seed.x * ((H-200) / 2) * sqrt(pie/N);
		C_y = W/2 + seed.y * ((W-200) / 2) * sqrt(pie/N);
		B_x = C_x + sqrt((double)k/N) * ((double)min(W,H))/100;
		B_y = C_y;

		out << "fill blue circle " << C_x << "," << C_y << " " << B_x << "," << B_y << endl;
	}

}
