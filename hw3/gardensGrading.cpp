//============================================================================
// Name        : a3test.cpp
// Author      : Malika
// Version     :
// Copyright   :
// Description : Grading test
//============================================================================

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include "gardens.h"
#include <math.h>
#include <cmath>

map<string,const ContinuedFraction*> cfs;
map<string,string> expected_output;

ostream &operator<<(ostream &out, const Flower &flower) {
    flower.writeMVGPicture(out, 300, 1600, 1600);
    return out;
}

ostream &operator<<(ostream &out, const Fraction &f) {
    return out << f.numerator << "/" << f.denominator;
}

bool check_cf(string s_in, string s_ex) {
  if(s_in.length() > 0) {
	string f_delimiter = ";";
	string fixed_part_in = s_in.substr(1, s_in.find(f_delimiter)-1);
	string fixed_part_ex = s_ex.substr(1, s_ex.find(f_delimiter)-1);
	//cout << "Fixed Part " << fixed_part_in << "," << fixed_part_ex << endl;
	int check_fixed = 0;
	try{
		if(stoi(fixed_part_in) == stoi(fixed_part_ex))
			check_fixed = 1;
	}catch (exception& ex) {
		cout << ex.what();
		return false;
	}

	string p_delimiter = "...";
	string periodic_part_in = s_in.substr(fixed_part_in.length()+1, s_in.find(p_delimiter)-3);
	string periodic_part_ex = s_ex.substr(fixed_part_ex.length()+1, s_ex.find(p_delimiter)-3);
	//cout << "Periodic Part " << periodic_part_in << "," << periodic_part_ex << endl;

	int error = 0;
	string delimiter = ",";
	int start_index_in = 0, start_index_ex = 0;
	for (int i = 0; i < periodic_part_ex.length(); i++){
		string check_in = periodic_part_in.substr(start_index_in, periodic_part_in.find(delimiter));
		string check_ex = periodic_part_ex.substr(start_index_ex, periodic_part_ex.find(delimiter));
		start_index_in += check_in.length()+1;
		start_index_ex += check_ex.length()+1;

		if((check_ex.length()==0) || (check_ex.compare(" ")))
			break;

		if(stoi(check_in) != stoi(check_ex))
			error++;
	}

	if ((error == 0) && (check_fixed == 1)) return true;
	else return false;
  }
  return false;
}

double check_MVG(string s_in, string s_ex){
  if(s_in.length() > 0)	{
	string end_delimiter = "\n";
	int start_index_in = 17, start_index_ex = 17;
    double score = 0;
	for (int i = 0; i < 10; i++) {
		string check_in = s_in.substr(start_index_in, s_in.find(end_delimiter, start_index_in)-start_index_in);
		string check_ex = s_ex.substr(start_index_ex, s_ex.find(end_delimiter, start_index_ex)-start_index_ex);
		//cout << "delimiter pos " << s_in.find(end_delimiter, start_index_in) << endl;
		//cout << "check in " << check_in << endl;
		//cout << "check ex " << check_ex << endl;
		start_index_in += check_in.length()+17;
		start_index_ex += check_ex.length()+17;

		if(check_ex.compare(check_in) == 0)
			score += 0.5;

		if(check_ex.length()==0)
			break;
	}
	cout << "Score = " << score << endl;
	return score;
  }
  return 0;

}



double question3();
double question4();
double question5();
double question6();
double question7();

int main() {

	double grade = 0;

	grade += question3();     // 25

	cout << "------------------------------------------------------" << endl;

	grade += question4();	  // 25

	cout << "------------------------------------------------------" << endl;

	grade += question5();	  // 15

	cout << "------------------------------------------------------" << endl;

	grade += question6();	  // 15

	cout << "------------------------------------------------------" << endl;

	grade += question7();      // 20

	cout << "------------------------------------------------------" << endl;

	cout << "Grade: " << round(grade) << "/" << 100 << endl;

	if (grade >= 85) cout << "Excellent! May the wind under your wings bear you where the sun sails and the moon walks." << endl;

	else if (grade >= 75  && grade < 85 ) cout << "Good job! Where there's life there's hope." << endl;

	else if (grade >= 60  && grade < 75 ) cout  << "Good luck for next one! The road goes ever on and on." << endl;

	else if (grade >= 50  && grade < 60 ) cout  <<  "You can do better! So comes snow after fire, and even dragons have their endings" << endl;

	else if (grade < 50) cout << "It does not do to leave a live dragon out of your calculations, if you live near him." << endl;


	return 0;

}

double question3() {
	// test Periodic CF
	cout << "Question 3: PeriodicCF" << endl;
	cout << "Expected output:" << endl;
	expected_output["-Golden Ratio-"] = "[1; 1, 1, 1, 1, 1, 1, 1, 1, 1 ...]";
	cout << "The CF of -Golden Ratio- is " << expected_output["-Golden Ratio-"] << endl;
	expected_output["-Square Root 2-"] = "[1; 2, 2, 2, 2, 2, 2, 2, 2, 2 ...]";
	cout << "The CF of -Square Root 2- is " << expected_output["-Square Root 2-"] << endl;
	expected_output["-Square Root 3-"] = "[1; 1, 2, 1, 2, 1, 2, 1, 2, 1 ...]";
	cout << "The CF of -Square Root 3- is " << expected_output["-Square Root 3-"] << endl;
	expected_output["-Square Root 18-"] = "[4; 4, 8, 4, 8, 4, 8, 4, 8, 4 ...]";
	cout << "The CF of -Square Root 18- is " << expected_output["-Square Root 18-"] << endl;
	expected_output["-Square Root 7-"] = "[2; 1, 1, 1, 4, 1, 1, 1, 4, 1 ...]";
	cout << "The CF of -Square Root 7- is " << expected_output["-Square Root 7-"] << endl;

	double grade3 = 0;

	cout << "Your output:" << endl;
	cfs["-Golden Ratio-"] = new PeriodicCF({1});
	cout << "The CF of -Golden Ratio- is " << *cfs["-Golden Ratio-"] << endl;
	ostringstream gold_output;
	gold_output << *cfs["-Golden Ratio-"];
	if (check_cf(gold_output.str(), expected_output["-Golden Ratio-"]))
		grade3 +=5;

	cfs["-Square Root 2-"] = new PeriodicCF({1},{2});
	cout << "The CF of -Square Root 2- is " << *cfs["-Square Root 2-"] << endl;
	ostringstream sqrt2_output;
	sqrt2_output << *cfs["-Square Root 2-"];
	if ( check_cf(sqrt2_output.str(), expected_output["-Square Root 2-"]) )
		grade3 +=5;

	cfs["-Square Root 3-"] = new PeriodicCF({1},{1,2});
	cout << "The CF of -Square Root 3- is " << *cfs["-Square Root 3-"] << endl;
	ostringstream sqrt3_output;
	sqrt3_output << *cfs["-Square Root 3-"];
	if (check_cf(sqrt3_output.str(), expected_output["-Square Root 3-"]))
		grade3 +=5;

	cfs["-Square Root 18-"] = new PeriodicCF({4},{4,8});
	cout << "The CF of -Square Root 18- is " << *cfs["-Square Root 18-"] << endl;
	ostringstream sqrt18_output;
	sqrt18_output << *cfs["-Square Root 18-"];
	if (check_cf(sqrt18_output.str(), expected_output["-Square Root 18-"]))
		grade3 +=5;

	cfs["-Square Root 7-"] = new PeriodicCF({2},{1,1,1,4});
	cout << "The CF of -Square Root 7- is " << *cfs["-Square Root 7-"] << endl;
	ostringstream sqrt7_output;
	sqrt7_output << *cfs["-Square Root 7-"];
	if (check_cf(sqrt7_output.str(), expected_output["-Square Root 7-"]))
		grade3 +=5;

	cout << "Grade: " << grade3 << "/25" << endl;
	return grade3;
}

double question4() {
    // test MagicBoxCF
	double grade4 = 0;

	cout << "Question 4: MagicBoxCF" << endl;
	cout << "Expected output:" << endl;
	cout << "MagicBox of -Square Root 18- is " << expected_output["-Square Root 18-"] << endl;
	expected_output["-Square Root 72-"] = "[8; 2, 16, 2, 16, 2, 16, 2, 16, 2 ...]";
	cout << "MagicBox of -Square Root 72- is " << expected_output["-Square Root 72-"] << endl;
	expected_output["-Fraction 125/13-"] = "[9; 1, 1, 1, 1, 2]";
	cout << "MagicBox of -Fraction 125/13- is " << expected_output["-Fraction 125/13-"] << endl;
	expected_output["-Fraction 41/13-"] = "[3; 6, 2]";
	cout << "MagicBox of -Fraction 41/13- is " << expected_output["-Fraction 41/13-"] << endl;
	expected_output["-Fraction 5/12-"] = "[0; 2, 2, 2]";
	cout << "MagicBox of -Fraction  5/12- is " << expected_output["-Fraction 5/12-"] << endl;

	cout << "Your output:" << endl;
	cfs["-Square Root 18-"] = new MagicBoxCF(cfs["-Square Root 2-"], 0, 3);
	ostringstream sqrt18_output;
	sqrt18_output << *cfs["-Square Root 18-"];
	cout << "MagicBox of -Square Root 18- is " << sqrt18_output.str() << endl;
	if (check_cf(sqrt18_output.str(), expected_output["-Square Root 18-"]))
		grade4 += 5;

	cout << grade4 << endl;

	cfs["-Square Root 72-"] = new MagicBoxCF(cfs["-Square Root 18-"], 0, 2);
	ostringstream sqrt72_output;
	sqrt72_output << *cfs["-Square Root 72-"];
	cout << "MagicBox of -Square Root 72- is " << sqrt72_output.str() << endl;
	if (check_cf(sqrt72_output.str(), expected_output["-Square Root 72-"]))
		grade4 += 5;

	cout << grade4 << endl;

	const Fraction thirtyOverThirteen = {30,13};
	const RationalCF *rcf1 = new RationalCF(thirtyOverThirteen);
	cfs["-Fraction 125/13-"] = new MagicBoxCF(rcf1, 5, 2);
	ostringstream fraction1_output;
	fraction1_output << *cfs["-Fraction 125/13-"];
	cout << "MagicBox of  is -Fraction 125/13- " << fraction1_output.str() << endl;
	if (check_cf(fraction1_output.str(), expected_output["-Fraction 125/13-"]))
		grade4 += 5;

	cout << grade4 << endl;

	const Fraction twoOverThirteen = {2,13};
	const RationalCF *rcf2 = new RationalCF(twoOverThirteen);
	cfs["-Fraction 41/13-"] = new MagicBoxCF(rcf2, 3, 1);
	ostringstream fraction2_output;
	fraction2_output << *cfs["-Fraction 41/13-"];
	cout << "MagicBox of  is -Fraction 41/13- " << fraction2_output.str() << endl;
	if (check_cf(fraction2_output.str(), expected_output["-Fraction 41/13-"]))
		grade4 += 5;

	cout << grade4 << endl;

	const Fraction sevenOverTwelve = {7,12};
	const RationalCF *rcf3 = new RationalCF(sevenOverTwelve);
	cfs["-Fraction 5/12-"] = new MagicBoxCF(rcf3, 1, -1);
	ostringstream fraction3_output;
	fraction3_output << *cfs["-Fraction 5/12-"];
	cout << "MagicBox of  is -Fraction 5/12- " << fraction3_output.str() << endl;
	if (check_cf(fraction3_output.str(), expected_output["-Fraction 5/12-"]))
		grade4 += 5;

	cout << grade4 << endl;

	cout << "Grade: " << grade4 << "/25" << endl;

    return(grade4);

}

double question5() {
	//test operator <<
	double grade5 = 1;	// Bonus 1 for no run time errors

    cout << "Question 5: operator << " << endl;
	cout << "Expected output:" << endl;
    cout << "The CF of -Fraction 125/13- is " << expected_output["-Fraction 125/13-"] << endl;
    cout << "The CF of -Fraction 41/13- is " << expected_output["-Fraction 41/13-"] << endl;
    cout << "The CF of -Fraction 5/12- is " << expected_output["-Fraction 5/12-"] << endl;
    cout << "The CF of -Golden Ratio- is " << expected_output["-Golden Ratio-"] << endl;
    cout << "The CF of -Square Root 18- is " << expected_output["-Square Root 18-"] << endl;
    cout << "The CF of -Square Root 2- is " << expected_output["-Square Root 2-"] << endl;
    cout << "The CF of -Square Root 3- is " << expected_output["-Square Root 3-"] << endl;
    cout << "The CF of -Square Root 7- is " << expected_output["-Square Root 7-"] << endl;
    cout << "The CF of -Square Root 72- is " << expected_output["-Square Root 72-"] << endl;

    cout << "Your output: " << endl;
    for (auto& x : cfs) {
        ostringstream output;
        output << *(x.second);
        //cout << output.str().length() << endl;
        if((x.first == "-Golden Ratio-")||(x.first == "-Square Root 2-")||(x.first == "-Square Root 3-")||(x.first == "-Square Root 18-")||(x.first == "-Square Root 7-")) {
        	if (check_cf(output.str(), expected_output[x.first]))
        		grade5 += 2;  // 2 point for golden ratio and square root
        }
        else {
        	if (check_cf(output.str(), expected_output[x.first]))
        		grade5 += 1;  // 1 point fractions
        }
        cout << "The CF of " << x.first << " is " << output.str() << endl;

    }

	cout << "Grade: " << grade5 << "/15" << endl;

	return grade5;
}

double question6() {
	//test seeds
	double grade6 = 0;
	cout << "Question 6: Seeds" << endl;
	cout << endl << "Expected output:" << endl;

	cout << "sqrt{2}-flower of size 10:" << endl;
	Seed expected_seeds2[] = {Seed{0, 0},Seed{-0.484, 0.29},Seed{0.377, -0.703},Seed{0.0454, 0.976},Seed{-0.624, -0.94},Seed{1.14, 0.544},Seed{-1.38, 0.128},Seed{1.2, -0.882},Seed{-0.621, 1.47},Seed{-0.235, -1.68}};
	string expected_output2 = "(0, 0)(-0.484, 0.29)(0.377, -0.703)(0.0454, 0.976)(-0.624, -0.94)(1.14, 0.544)(-1.38, 0.128)(1.2, -0.882)(-0.621, 1.47)(-0.235, -1.68)";
	cout << expected_output2 << endl;

	cout << endl << "sqrt{3}-flower of size 10:"<< endl;
	Seed expected_seeds3[] = {Seed{0, 0},Seed{-0.0647, -0.56},Seed{-0.777, 0.182},Seed{0.33, 0.92},Seed{1.01, -0.501},Seed{-0.686, -1.06},Seed{-1.07, 0.879},Seed{1.08, 1.04},Seed{0.967, -1.27},Seed{-1.45, -0.865}};
	string expected_output3 = "(0, 0)(-0.0647, -0.56)(-0.777, 0.182)(0.33, 0.92)(1.01, -0.501)(-0.686, -1.06)(-1.07, 0.879)(1.08, 1.04)(0.967, -1.27)(-1.45, -0.865)";
	cout << expected_output3 << endl;

	cout << endl << "sqrt{7}-flower of size 10:"<< endl;
	Seed expected_seeds7[] = {Seed{0, 0},Seed{-0.345, -0.446},Seed{-0.2, 0.772},Seed{0.898, -0.385},Seed{-0.987, -0.548},Seed{0.191, 1.25},Seed{0.952, -1},Seed{-1.49, -0.151},Seed{0.844, 1.35},Seed{0.588, -1.59}};
	string expected_output7 = "(0, 0)(-0.345, -0.446)(-0.2, 0.772)(0.898, -0.385)(-0.987, -0.548)(0.191, 1.25)(0.952, -1)(-1.49, -0.151)(0.844, 1.35)(0.588, -1.59)";
	cout << expected_output7 << endl;

	cout << endl << "sqrt{18}-flower of size 10:"<< endl;
	Seed expected_seeds18[] = {Seed{0, 0},Seed{0.0261, 0.564},Seed{-0.794, 0.0737},Seed{-0.135, -0.968},Seed{1.11, -0.208},Seed{0.289, 1.23},Seed{-1.33, 0.379},Seed{-0.475, -1.42},Seed{1.49, -0.577},Seed{0.684, 1.55}};
	string expected_output18 = "(0, 0)(0.0261, 0.564)(-0.794, 0.0737)(-0.135, -0.968)(1.11, -0.208)(0.289, 1.23)(-1.33, 0.379)(-0.475, -1.42)(1.49, -0.577)(0.684, 1.55)";
	cout << expected_output18 << endl;

	cout << endl << "sqrt{72}-flower of size 10:"<< endl;
	Seed expected_seeds72[] = {Seed{0, 0},Seed{-0.562, 0.0521},Seed{0.784, -0.147},Seed{-0.94, 0.268},Seed{1.05, -0.408},Seed{-1.13, 0.563},Seed{1.17, -0.728},Seed{-1.19, 0.9},Seed{1.18, -1.08},Seed{-1.14, 1.25}};
	string expected_output72 = "(0, 0)(-0.562, 0.0521)(0.784, -0.147)(-0.94, 0.268)(1.05, -0.408)(-1.13, 0.563)(1.17, -0.728)(-1.19, 0.9)(1.18, -1.08)(-1.14, 1.25)";
	cout << expected_output72 << endl;

	cout << endl << "Your output: " << endl;
	cout << "sqrt{2}-flower of size 10:" << endl;
	Flower f2(cfs["-Square Root 2-"], 7);
	int ada2 = 0, err2 = 0;
	auto z2 = f2.getSeeds(10);
    for (auto& s : z2) {
    	cout << setprecision(3) <<"(" << s.x << ", " << s.y << ")";
        if((abs(expected_seeds2[ada2].x - s.x) > 0.01) || (abs(expected_seeds2[ada2].y - s.y) > 0.01))
        	err2 += 1;
        ada2++;
    }cout << endl;
    if (err2 == 0) grade6 += 3;
    else grade6 += (3 - 0.3*err2);

    cout << endl << "sqrt{3}-flower of size 10:" << endl;
	Flower f3(cfs["-Square Root 3-"], 7);
	int ada3 = 0, err3 = 0;
    auto z3 = f3.getSeeds(10);
    for (auto& s : z3) {
        cout << setprecision(3) <<"(" << s.x << ", " << s.y << ")";
        if((abs(expected_seeds3[ada3].x - s.x) > 0.01) || (abs(expected_seeds3[ada3].y - s.y) > 0.01))
        	err3 += 1;
        ada3++;
    }cout << endl;
    if (err3 == 0) grade6 += 3;
    else grade6 += (3 - 0.3*err3);

    cout << endl << "sqrt{7}-flower of size 10:" << endl;
	Flower f7(cfs["-Square Root 7-"], 7);
	int ada7 = 0, err7 = 0;
    auto z7 = f7.getSeeds(10);
    for (auto& s : z7) {
        cout << setprecision(3) <<"(" << s.x << ", " << s.y << ")";
        if((abs(expected_seeds7[ada7].x - s.x) > 0.01) || (abs(expected_seeds7[ada7].y - s.y) > 0.01))
        	err7 += 1;
        ada7++;
    }cout << endl;
    if (err7 == 0) grade6 += 3;
    else grade6 += (3 - 0.3*err7);

    cout << endl << "sqrt{18}-flower of size 10:" << endl;
	Flower f18(cfs["-Square Root 18-"], 7);
	int ada18 = 0, err18 = 0;
    auto z18 = f18.getSeeds(10);
    for (auto& s : z18) {
        cout << setprecision(3) <<"(" << s.x << ", " << s.y << ")";
        if((abs(expected_seeds18[ada18].x - s.x) > 0.01) || (abs(expected_seeds18[ada18].y - s.y) > 0.01))
        	err18 += 1;
        ada18++;
    }cout << endl;
    if (err18 == 0) grade6 += 3;
    else grade6 += (3 - 0.3*err18);

    cout << endl << "sqrt{72}-flower of size 10:" << endl;
	Flower f72(cfs["-Square Root 72-"], 7);
	int ada72 = 0, err72 = 0;
    auto z72 = f72.getSeeds(10);
    for (auto& s : z72) {
        cout << setprecision(3) <<"(" << s.x << ", " << s.y << ")";
        if((abs(expected_seeds72[ada72].x - s.x) > 0.01) || (abs(expected_seeds72[ada72].y - s.y) > 0.01))
        	err72 += 1;
        ada72++;
    }cout << endl;
    if (err72 == 0) grade6 += 3;
    else grade6 += (3 - 0.3*err72);

    cout << endl << "Grade: " << grade6 << "/15" <<  endl;

    return grade6;

}

double question7() {
    // test MVG
	double grade7 = 0;

	cout << "Question 7: MVG " << endl;
	cout << "Expected output: " << endl;

	cout << "MVG for Square Root 2" << endl;
	Flower f2(cfs["-Square Root 2-"], 7);
	ostringstream ss2;
	f2.writeMVGPicture(ss2, 10, 1600, 1600);

	string expected_output2 = "fill blue circle 800,800 801,800\n"
				"fill blue circle 610,913 615,913\n"
				"fill blue circle 948,524 955,524\n"
				"fill blue circle 817,1182 825,1182\n"
				"fill blue circle 555,431 565,431\n"
				"fill blue circle 1246,1013 1257,1013\n"
				"fill blue circle 260,850 272,850\n"
				"fill blue circle 1272,453 1285,453\n"
				"fill blue circle 556,1376 570,1376\n"
				"fill blue circle 707,142 722,142\n";
	cout << expected_output2 << endl;
	cout << "Your output: " << endl;
	cout << ss2.str() << endl;

	grade7 += check_MVG(ss2.str(), expected_output2);

	// "--------------------------"

	cout << "MVG for Square Root 3" << endl;
	cout << "Expected ouput:" << endl;
	Flower f3(cfs["-Square Root 3-"], 7);
	ostringstream ss3;
	f3.writeMVGPicture(ss3, 10, 1600, 1600);

	string expected_output3 = "fill blue circle 800,800 801,800\n"
			"fill blue circle 774,580 779,580\n"
			"fill blue circle 495,871 502,871\n"
			"fill blue circle 929,1160 937,1160\n"
			"fill blue circle 1196,603 1206,603\n"
			"fill blue circle 530,384 541,384\n"
			"fill blue circle 381,1144 393,1144\n"
			"fill blue circle 1221,1206 1234,1206\n"
			"fill blue circle 1179,302 1193,302\n"
			"fill blue circle 229,460 244,460\n";

	cout << expected_output3 << endl;
	cout << "Your output: " << endl;
	cout << ss3.str() << endl;

	grade7 += check_MVG(ss3.str(), expected_output3);

	// "--------------------------"
	cout << "MVG for Square Root 7" << endl;
	cout << "Expected output: " << endl;
	Flower f7(cfs["-Square Root 7-"], 7);
	ostringstream ss7;
	f7.writeMVGPicture(ss7, 10, 1600, 1600);

	string expected_output7 = "fill blue circle 800,800 801,800\n"
			"fill blue circle 664,624 669,624\n"
			"fill blue circle 721,1103 728,1103\n"
			"fill blue circle 1152,648 1160,648\n"
			"fill blue circle 412,585 422,585\n"
			"fill blue circle 874,1289 885,1289\n"
			"fill blue circle 1173,407 1185,407\n"
			"fill blue circle 217,740 230,740\n"
			"fill blue circle 1131,1331 1145,1331\n"
			"fill blue circle 1030,177 1045,177\n";

	cout << expected_output7 << endl;
	cout << "Your output: " << endl;
	cout << ss7.str() << endl;

	grade7 += check_MVG(ss7.str(), expected_output7);

	// "--------------------------"
	cout << "MVG for Square Root 18" << endl;
	cout << "Expected output: " << endl;
	Flower f18(cfs["-Square Root 18-"], 7);
	ostringstream ss18;
	f18.writeMVGPicture(ss18, 10, 1600, 1600);

	string expected_output18 = "fill blue circle 800,800 801,800\n"
			"fill blue circle 810,1021 815,1021\n"
			"fill blue circle 488,828 495,828\n"
			"fill blue circle 746,420 754,420\n"
			"fill blue circle 1235,718 1245,718\n"
			"fill blue circle 913,1281 924,1281\n"
			"fill blue circle 278,948 290,948\n"
			"fill blue circle 613,244 626,244\n"
			"fill blue circle 1383,573 1397,573\n"
			"fill blue circle 1068,1407 1083,1407\n";

	cout << expected_output18 << endl;
	cout << "Your output: " << endl;
	cout << ss18.str() << endl;

	grade7 += check_MVG(ss18.str(), expected_output18);

	// "--------------------------"*/

    cout << "Grade: " << grade7 << "/20" <<  endl;

    return grade7;

}

