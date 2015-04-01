#include "flowers.h"
#include <math.h>

ContinuedFraction fractionalPart(ContinuedFraction &f) {
	if (f.fixedPart.empty()) {
		if (!f.periodicPart.empty()) {
			// rotate
			f.fixedPart.push_back(0);
			auto temp = f.periodicPart[0];
			f.periodicPart.erase(f.periodicPart.begin());
			f.periodicPart.push_back(temp);
		}
	} else
		f.fixedPart[0] = 0;
	return f;
}
Fraction fractionalPart(Fraction &f) {
	if ((double) f.numerator / (double) f.denominator >= 1.0)
		f.numerator = f.numerator % f.denominator;
	return f;
}

unsigned int spitSqrt8(unsigned int index) {
	if (index == 0)
		return 2;
	else
		return index % 2 == 1 ? 1 : 4;
}

unsigned int spitEulerSquare(unsigned int index) {
	if (index == 0)
		return 7;

	switch (index % 5) {
	case 0:
		return 6 + (index / 5) * 12;
	case 1:
		return 2 + (index / 5) * 3;
	case 2:
	case 3:
		return 1;
	case 4:
		return (index / 5 + 1) * 3;
	}
}

Fraction getApproximation(ContinuedFraction &fr, unsigned int n) {
	Fraction toRet;

	auto tail = fr; // Maybe this copies... C++ mis(t)ery
	int head;

	// Check 4 goddamn cases....
	if (tail.periodicPart.empty()) { // Then we can't go too far
		if (tail.fixedPart.empty()) { // Then we can't go anywhere...
			toRet.numerator = 0;
			toRet.denominator = 1;
			return toRet;
		} else {
			if (n > tail.fixedPart.size()) // Limit how far we go
				n = tail.fixedPart.size();
		}
	} else {
		if (tail.fixedPart.empty()) {
			// the periodic part is where we'll go
		} else {
			// we have numbers everywhere, no problemo
		}
	}

	if (!tail.fixedPart.empty()) { // Grab the first element of fixedPart
		head = tail.fixedPart[0];
		tail.fixedPart.erase(tail.fixedPart.begin());
	} else if (!tail.periodicPart.empty()) { // Grab the first element of periodicPart and rotate
		head = tail.periodicPart[0];
		tail.periodicPart.erase(tail.periodicPart.begin());
		tail.periodicPart.push_back(head);
	}

	if (n <= 1) { // Base case
		toRet.numerator = head;
		toRet.denominator = 1;
	} else {
		auto sub = getApproximation(tail, n - 1);
		toRet.numerator = sub.numerator * head + sub.denominator;
		toRet.denominator = sub.numerator;
	}

	if (toRet.denominator == 0) {
		std::cout << "ERROR DIVISION BY 0 TSSS...!" << std::endl;
		toRet.denominator = 1;
	}

	return toRet;
}

double getAngle(ContinuedFraction &theta, int k) {
	ContinuedFraction thetafp = fractionalPart(theta);
	auto val = getApproximation(thetafp, 7);
	val.numerator *= k;
	val = fractionalPart(val);
	return (double) 2 * (double) M_PI * (double) val.numerator / (double) val.denominator;
}

Seed getSeed(ContinuedFraction &theta, int k) {
	double angle = getAngle(theta, k);
	double factor = sqrt((double) k / (double) M_PI);
	Seed toRet;
	toRet.x = factor * cos(angle);
	toRet.y = factor * sin(angle);
	return toRet;
}

void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
	int k = flower.size();
	flower.push_back(getSeed(theta, k));
}

void printMB(MagicBox box) {
	std::cout << "{" << box.i << "," << box.j << "," << box.k << "," << box.l << "," << box.indexInBoxedFraction << "}\n";
}

int spitNextMagicBox(MagicBox &box) {

	while (true) {
		MagicBox box2 = box; // To copy
		//printMB(box);
		if (box.k == 0 && box.l == 0) {
			// CASE 1
			// no integer to spit
			//std::cout << "NO INTEGER TO SPIT k==l==0\n";
			return -29341;
		} else if (box.k == 0
			|| box.l == 0
			|| box.i / box.k != box.j / box.l) {
			// CASE 3
			if ( (! box.boxedFraction.periodicPart.empty())
				|| box.indexInBoxedFraction < box.boxedFraction.fixedPart.size()) {
				// If end of x is not reached
				int p = spit(box.boxedFraction, box.indexInBoxedFraction);
				box.indexInBoxedFraction ++;
				//std::cout << "GETTING NEXT INTEGER p=" << p << "\n";
				box.i = box2.j;
				box.j = box2.i + box2.j * p;
				box.k = box2.l;
				box.l = box2.k + box2.l * p;
			}
		} else { // i/k and j/l have the same integer part
			// CASE 2
			int q1 = box.i / box.k;
			int q2 = box.j / box.l;
			if (q1 != q2)
				std::cout << "WTFFFFF IS THIS\n";

			int q = q1;
			box.i = box2.k;
			box.j = box2.l;
			box.k = box2.i - box2.k * q;
			box.l = box2.j - box2.l * q;
			//std::cout << "RETURNING q=" << q << "\n";

			return q;
		}
		if (box.boxedFraction.periodicPart.empty()
			&& box.indexInBoxedFraction >= box.boxedFraction.fixedPart.size()) {
			// We have reached the end of x
			box.i = box2.j;
			box.k = box2.l;
			box2 = box;
			//std::cout << "END OF x\n";
		}
	}
}

ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
	ContinuedFraction f2;
	MagicBox box;
	box.boxedFraction = f; // copying? I think so...
	box.indexInBoxedFraction = 0;
	box.i = a;
	box.j = b;
	box.k = 1;
	box.l = 0;

	for (int i=0; i<length; i++) {
		int num = spitNextMagicBox(box);
		if (num == -29341)
			break;
		else
			f2.fixedPart.push_back(num);
	}
	//std::cout << "FINISH\n";
	return f2;
}
