//============================================================================
// Name        : continuedGrading.cpp
// Author      : Stephanie Laflamme
// Version     :
// Copyright   : 
// Description : Tests for grading assignment 1
//============================================================================
#include "continued.h"
#include <string>
#include <sstream>

using namespace std;

string printCF(ContinuedFraction, int);

bool test1();
bool test2();
bool test3();
bool test4();


using namespace std;

int main() {
	
	int grade = 0;

	// tests getCFLargerThanOne
	cout << "Question 1" << endl;
	if (test1()) grade+=35;

	// tests getCF(b,a)
	cout << "\nQuestion 2" << endl;
	if (test2()) grade+=10;

	// tests getCF(head, fixed, period)
	cout << "\nQuestion 3" << endl;
	if (test3()) grade+=30;

	// tests getApproximation
	cout << "\nQuestion 4" << endl;
	if (test4()) grade+=25;

	cout << "\nFinal grade:" << endl;
	cout << grade << "/" << 100 << endl;

	return 0;
}

bool test1() {

	bool toRet = true;

	// test for the 'one' case, much shorter
	// should both be [1], but will break code with a variety of different problems
	// (e.g. not returning at the base case or inadvertent division by 0)
	ContinuedFraction* one = getCFlargerThanOne(1,1);
	ContinuedFraction* oneprime = getCFlargerThanOne(5,5);
	string s1 = printCF(*one, 5);
	cout << s1 << " should be" << " [1]" << endl;
	string s2 = printCF(*oneprime,5);
	cout << s2 <<  " should be" << " [1]" << endl;
	if (s1.compare("[1]") != 0) toRet = false;
	if (s2.compare("[1]") != 0) toRet = false;

	// test for some others... 
	ContinuedFraction* trad1 = getCFlargerThanOne(355, 113);
	ContinuedFraction* trad2 = getCFlargerThanOne(688, 219);
	ContinuedFraction* trad3 = getCFlargerThanOne(75, 33);
	ContinuedFraction* trad4 = getCFlargerThanOne(780, 209);

	string s3 = printCF(*trad1, 5);
	string s4 = printCF(*trad2, 5);
	string s5 = printCF(*trad3, 5);
	string s6 = printCF(*trad4, 15);
	cout << s3 <<  " should be [3; 7, 16]" << endl;
	cout << s4 <<  " should be [3; 7, 15, 2]" << endl;
	cout << s5 <<  " should be [2; 3, 1, 2]" << endl;
	cout << s6 <<  " should be [3; 1, 2, 1, 2, 1, 2, 1, 3]" << endl;
	if (s3.compare("[3; 7, 16]") != 0) toRet = false;
	if (s4.compare("[3; 7, 15, 2]") != 0) toRet = false;
	if (s5.compare("[2; 3, 1, 2]") != 0) toRet = false;
	if (s6.compare("[3; 1, 2, 1, 2, 1, 2, 1, 3]") != 0) toRet = false;

	return toRet;

}

bool test2() {

	bool toRet = true;

	// try both ways, a < b and a > b
	// this case will also break code that does division by 0 under b%a = 0
	ContinuedFraction* greater = getCF(20,4);
	ContinuedFraction* lessthan = getCF(4,20);
	string s1 = printCF(*greater, 5);
	string s2 = printCF(*lessthan, 5);
	cout << s1 <<  " should be [5]" << endl;
	cout << s2 <<  " should be [0; 5]" << endl;
	if (s1.compare("[5]") != 0) toRet = false;
	if (s2.compare("[0; 5]") != 0) toRet = false;

	// also try the assignment example...
	ContinuedFraction* trad = getCF(33, 75);
	string s3 = printCF(*trad, 6);
	cout << s3 <<  " should be [0; 2, 3, 1, 2]" << endl;
	if (s3.compare("[0; 2, 3, 1, 2]") != 0) toRet = false;

	return toRet;
}

bool test3() {

	bool toRet = true;

	// try the golden ratio (WITHOUT its null value)
	ContinuedFraction goldenRatio;
	goldenRatio.head = 1;
	goldenRatio.tail = &goldenRatio;
	ContinuedFraction* h = new ContinuedFraction;
	h->head = 1;
	h->tail = nullptr;
	// the method call has been changed to remove the null argument
	// note that the SAME pointer is passed for both fixed and period!
	// this is very likely to break code which does what we said not to do :)
	ContinuedFraction* golden = getCF(1, h, h); 
	string s1 = printCF(*golden, 5);
	cout << s1 <<  " should be [1; 1, 1, 1, 1,...]" << endl;
	if (s1.compare("[1; 1, 1, 1, 1,...]") != 0) toRet = false;

	// the example on the assignment...
	ContinuedFraction* tfixed = new ContinuedFraction;
	tfixed->head = 4;
	tfixed->tail = new ContinuedFraction;
	tfixed->tail->head = 1;
	tfixed->tail->tail = new ContinuedFraction;
	tfixed->tail->tail->head = 3;
	tfixed->tail->tail->tail = nullptr;

	ContinuedFraction* trepeat = new ContinuedFraction;
	trepeat->head = 1;
	trepeat->tail = new ContinuedFraction;
	trepeat->tail->head = 2;
	trepeat->tail->tail = nullptr;

	ContinuedFraction* assxample = getCF(3, tfixed, trepeat);

	// test printing for different lengths to ensure the repeat works!!
	string s2 = printCF(*assxample, 10);
	string s3 = printCF(*assxample, 3);
	cout << s2 <<  " should be [3; 4, 1, 3, 1, 2, 1, 2, 1, 2,...]" << endl;
	cout << s3 <<  " should be [3; 4, 1,...]" << endl;
	if (s3.compare("[3; 4, 1,...]") != 0) toRet = false;
	if (s2.compare("[3; 4, 1, 3, 1, 2, 1, 2, 1, 2,...]") != 0) toRet = false;

	return toRet;

}

bool test4() {

	bool toRet = true;

	// try the one on assignment
	ContinuedFraction* trepeat = new ContinuedFraction;
	trepeat->head = 1;
	trepeat->tail = new ContinuedFraction;
	trepeat->tail->head = 2;
	trepeat->tail->tail = trepeat;

	ContinuedFraction* tfixed = new ContinuedFraction;
	tfixed->head = 4;
	tfixed->tail = new ContinuedFraction;
	tfixed->tail->head = 1;
	tfixed->tail->tail = new ContinuedFraction;
	tfixed->tail->tail->head = 3;
	tfixed->tail->tail->tail = trepeat;

	ContinuedFraction* test = new ContinuedFraction;
	test->head = 3;
	test->tail = tfixed;

	// test with different lengths
	Fraction test1 = getApproximation(test, 3);
	Fraction test2 = getApproximation(test, 10);

	cout << test1.numerator << "/" << test1.denominator <<  " should be 16/5" << endl;
	cout << test2.numerator << "/" << test2.denominator <<  " should be 2981/929" << endl;

	if (test1.numerator != 16 || test1.denominator != 5) toRet = false;
	if (test2.numerator != 2981 || test2.denominator != 929) toRet = false;

	return toRet;
}


/**
 * method prints a given continued fraction to a string and returns it.
 * If the fraction has length larger than max_length,
 * the method only print max_lenth number of digits and ...
 * to signal that there are more to come
 */
string printCF(ContinuedFraction fr, int max_length) {
	ostringstream output;

	//always print the integer part of the number
	output << "[" << fr.head;
	// print the rest
	if(fr.tail != nullptr && max_length-- > 1) {
		//print second integer
		output << "; ";
		fr = *(fr.tail);
		output << fr.head;
		// print the rest separated by comma
		while(fr.tail != nullptr && (--max_length > 0)) {
			output << ", ";
			fr = *(fr.tail);
			output << fr.head;
		}
		// check to see whether anything was left out
		if(fr.tail != nullptr) output << ",...";
	}
	output << "]";

	return output.str();
}

