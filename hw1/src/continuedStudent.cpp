#include "continued.h"


unsigned int gcd(unsigned int a, unsigned int b) {
	if (a == 0) // Base case
		return b;
	else
		return gcd(b % a, a);
}
unsigned int gcdFaster(unsigned int x, unsigned int y) {
	/*if (!(x < y)) // require x < y
		return gcdFaster(y, x);*/
	if (x == y || x == 0) // Base case
		return y;

	bool xOdd = x%2;
	bool yOdd = y%2;
	if (!xOdd && !yOdd)
		return 2 * gcdFaster(x/2, y/2); // gcd(2x, 2y) = 2 × gcd(x, y)
	else if (xOdd && yOdd)
		if (x > y)
			return gcdFaster(x/2 - y/2, y); // gcd(2x + 1, 2y + 1) = gcd(x − y, 2y + 1)
		else
			gcdFaster(y/2 - x/2, x);

	else if (!xOdd && yOdd)
		return gcdFaster(x/2, y); // gcd(2x, 2y + 1) = gcd(x, 2y + 1)
	else if (!xOdd && yOdd)
		return gcdFaster(x, y/2); // gcd(2x + 1, 2y) = gcd(2x + 1, y)

}

ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
	auto toRet = new ContinuedFraction;
	int r = b % a;
	toRet->head = b / a;
	if (r == 0) // a divides evenly into b, fraction does not continue
		toRet->tail = nullptr;
	else // continue the fraction
		toRet->tail = getCFlargerThanOne(a, r);
	return toRet;
}

ContinuedFraction *getCF(unsigned int b, unsigned int a) {
	if (b > a)
		return getCFlargerThanOne(b, a);
	else {
		auto toRet = new ContinuedFraction;
		toRet->head = 0;
		toRet->tail = getCFlargerThanOne(b, a);
		return toRet;
	}
}

// works even when fixed or period == nullptr!
ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
	auto toRet = new ContinuedFraction;
	toRet->head = head;

	auto previous = toRet; // to link the new CF to the chain

	// Copy the fixed part
	while (fixed != nullptr) {
		auto copy = new ContinuedFraction;
		copy->head = fixed->head; // copy value
		previous->tail = copy; // link
		previous = previous->tail; // move forward
		fixed = fixed->tail; // move forward
	}
	auto periodStart = previous;
	// Copy the period part
	while (period != nullptr) {
		auto copy = new ContinuedFraction;
		copy->head = period->head; // copy value
		previous->tail = copy; // link
		previous = previous->tail; // move forward
		period = period->tail; // move forward
	}
	// attach the end of period to the beginning of period
	previous->tail = periodStart->tail;
	return toRet;
}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
	Fraction toRet;
	if (n <= 1 || fr->tail == nullptr) { // base case
		toRet.numerator = fr->head;
		toRet.denominator = 1;
	} else {
		auto sub = getApproximation(fr->tail, n-1);
		toRet.numerator = sub.numerator * fr->head + sub.denominator;
		toRet.denominator = sub.numerator;
	}
	return toRet;
}
