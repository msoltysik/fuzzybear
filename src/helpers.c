#include <iostream>
#include <sstream>

using namespace std;

bool is_identifier(string p) {
    for (int i = 0; i < p.length(); i++) {
    	if (p[i] < 48 || p[i] > 57)
    		return true;
    }
	return false;
}


bool is_number(string p) {
    return !is_identifier(p);
}




string DecToBin(int number) {
	if (number == 0) return "0";
	if (number == 1) return "1";

	if (number % 2 == 0) {
		return DecToBin(number / 2) + "0";
	} else {
		return DecToBin(number / 2) + "1";
	}
}

string BinToDec(string number) {
	int result = 0;
	int pow = 1;

	for (int i = number.length() - 1; i >= 0; --i, pow <<= 1) {
		result += (number[i] - '0') * pow;
	}
	ostringstream ss;
	ss << result;

	return ss.str();
}


string DecToBin(string number) {
	int num = stoi(number);
	return DecToBin(num);	
}
