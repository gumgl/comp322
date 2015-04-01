#include "continued.h"

unsigned int gcd(unsigned int b, unsigned int a) {
	// we want b to be the smaller one, and then return the larger one
	while (b != 0) { //while the smaller number is not 0
		// assign b to a and a % b to b
		auto oldb = b; //we need a temp value for that
		b = a % b;
		a = oldb;
	}
	return a;
}


unsigned int gcdFaster(unsigned int b, unsigned int a) {
	if(b == 0) return a; //base case
	if(a == 0) return b; // base case
	if (b & 1) { //b is odd
		if(a & 1) { // both a,b odd
			// if x > y gcd(2x+1,2y+1) = gcd(x-y,2y+1);
			if (b > a) return gcd((b - a) >> 1, a);
			return gcd((a - b) >> 1, b);
		}else { // b odd, a even
			// gcd(2x,2y+1) = gcd(x,2y+1)
			return gcd(b,a >> 1);
		}
	}else { // b is even
		if (a & 1) { // b even, a odd
			// gcd(2x,2y+1) = gcd(x,2y+1)
			return gcd(b >> 1,a);
		}
		else { // both a,b even
			//gcd(2x,2y) = 2*gcd(x,y)
			return gcd(b >> 1, a >> 1) << 1;
		}
	}
	return -1; //code is never reached
}

ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
	ContinuedFraction* result = new ContinuedFraction;
	result->head = b / a; // the quotient - integer part
	result->tail = (b % a == 0) ?
			nullptr : //base case
			getCFlargerThanOne(a, b % a); // recursive call
	return result;
}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {
	// the implementation for getCFlargerThanOne will handle this case
	// if b < a,b / a = 0  and b % a = b so the recursive call will do what we want!
	return getCFlargerThanOne(b, a);
}


ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
	ContinuedFraction *toRet = new ContinuedFraction; //will be returned
	toRet->head = head;

	//we will have two iterators, one over the parameter, one over a copy of the parameter
	ContinuedFraction *iterateFixed = fixed;
	ContinuedFraction *iteratetoRet = toRet;
	while(iterateFixed != nullptr) {
		iteratetoRet->tail = new ContinuedFraction; //create a new struct to store the saved data
		iteratetoRet = iteratetoRet->tail;
		iteratetoRet->head = iterateFixed->head;
		// continue over the parameter cf
		iterateFixed = iterateFixed->tail;
	}

	// we do the same for the period
	ContinuedFraction *iterateperiod = period;
	ContinuedFraction *periodTmp = period;
	bool first = true; // we will connect the end of the fixed copy to the first el. of the period
	while(iterateperiod != nullptr) {
		iteratetoRet->tail = new ContinuedFraction; //create a new struct to store the saved data
		if(first) { // connect fixed to period
			periodTmp = iteratetoRet->tail;
			first = false;
		}
		iteratetoRet = iteratetoRet->tail;
		iteratetoRet->head = iterateperiod->head;
		// continue over the parameter cf
		iterateperiod = iterateperiod->tail;
	}

	// connect the end of the fixed copy to the start of the fixed period
	iteratetoRet->tail = periodTmp;
	return toRet;
}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
	Fraction toRet; // will be returned
	if (fr == nullptr) return toRet; //return shit if fr is nullptr
	if(n <= 1 || fr->tail == nullptr) { //base case
		//either we reached the end of the cf, or we want to print one int only
		toRet.numerator = fr->head;
		toRet.denominator = 1;
	} else {
		// make a recursive call
		Fraction f = getApproximation(fr->tail, n-1);
		// we need (head + 1/f) = head + f.den / f.num = (head * f.num + f.den) / f.num
		toRet.numerator = fr->head * f.numerator + f.denominator;
		toRet.denominator = f.numerator;
	}
	return toRet;
}
