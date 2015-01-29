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
/*
string DecToBin(int number) {
	if (number == 0) return "0";
	if (number == 1) return "1";

	if (number % 2 == 0) {
		return DecToBin(number / 2) + "0";
	} else {
		return DecToBin(number / 2) + "1";
	}
}

string DecToBin(string number) {
	int num = stoi(number);
	return DecToBin(num);
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
}*/

bool isOdd(char c) {
	int number = (int)c - (int)48;
	return (number % 2);
}

bool isOdd(string s) {
	char tmp = s.back();
	int number = (int)tmp - (int)48;
	return (number % 2);
}

string divByTwo(string s) {
	string new_s = "";
	int next_add = 0;

	for (char& ch : s) {
		int add = next_add;
		if (isOdd(ch)) {
			next_add = 5;
		} else {
			next_add = 0;
		}

		char new_ch = (char)((ch - '0') / 2 + add + '0');
		new_s.push_back(new_ch);
	}

	if(new_s != "0") {
 		if(new_s[0] == '0') {
				string tmp = new_s.substr(1, new_s.size()-1);
				new_s = tmp;
 		} 
 	}

	return new_s;
}

string DecToBin(string num) {
	string stack = "";

	while (num != "0") {
		if (isOdd(num[num.size() - 1]))
		{
			stack = "1" + stack;
		} else {
			stack = "0" + stack;
		}
		num = divByTwo(num);
	}
	if (stack == "") {
		return "0";
	}
	return stack;
}