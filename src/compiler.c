#include <iostream>
#include <sstream>
#include <regex>

using namespace std;
extern int yylineno;

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

std::vector<string> machineCode;


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


class ErrorFactory {
public:
	static void SECOND_DECLARATION(string variable) {
		printf("Błąd w linii %d: druga deklaracja %s\n", yylineno, variable.c_str());
		exit(-4);
	}
	static void UNDECLARATED_VARIABLE(string variable) {
 		printf("Błąd w linii %d: niezadeklarowana zmienna %s\n", yylineno, variable.c_str());
 		exit(-5);
	}
	static void USING_OF_UNDECLARATED_VARIABLE(string variable) {
		printf("Błąd w linii %d: użycie niezainicjowanej zmiennej %s\n", yylineno, variable.c_str());
		exit(-6);
	}
};


class Variable {
public:
	string name;					// nazwa
	string value;					// wartość
	bool declarated;				// zainicjowana?
	bool in_memory;					// w pamięci?
	unsigned int memory_adress; 	// numer komórki pamięci

	Variable(string name) {
		this->name = name;
		this->declarated = false;
	}
	
	Variable(string name, string value) {
		this->name = name;
		this->value = value;
		this->declarated = true;
	}

	void setValue(std::string value) {
		this->value = value;
		this->declarated = true;
	}
};

class VariableManager {
private:
	vector<Variable*> variableVector;

	bool inVector(Variable* variable) {
		for(int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == variable->name) {
				return true;
			}
		}
		return false;
	}

	bool notInVector(string name) {
		for(int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == name) {
				return false;
			}
		}
		return true;
	}

	bool notInitialized(string name) {
		for(int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == name) {
				if (variableVector.at(it)->declarated) {
					return false;
				} else {
					return true;
				}
			}
		}
	}


	int index(Variable* variable) {
		for(int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == variable->name) {
				return it;
			}
		}
		return -1;
	}

	int index(string name) {
		for(int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == name) {
				return it;
			}
		}
		return -1;
	}

public:
	void addVariable(Variable* var) {
		if (inVector(var))
		{
			ErrorFactory::SECOND_DECLARATION(var->name);
		} else {
			variableVector.push_back(var);
		}
	}
	void addVariable(string name, string value) {
		Variable* var = new Variable(name, value);
		addVariable(var);
	}


	Variable* getVariable(string name) {
		if (notInVector(name)) {
			ErrorFactory::UNDECLARATED_VARIABLE(name);
		}

		return variableVector.at(index(name));
	}

	Variable* getInitializedVariable(string name) {
		if (notInVector(name)) {
			ErrorFactory::UNDECLARATED_VARIABLE(name);
		}

		if (notInitialized(name)) {
			ErrorFactory::USING_OF_UNDECLARATED_VARIABLE(name);
		}

		return variableVector.at(index(name));
	}


	int size() {
		return variableVector.size();
	}

	void getVectorVariables() {
		for(int it = 0; it < variableVector.size(); it++) {
			printf("Name: %s, Value: %s\n",
				variableVector.at(it)->name.c_str(),
				variableVector.at(it)->value.c_str());
		}
	}
};


VariableManager variableManager;



int end_of_file() {
	machineCode.push_back("HALT");

	for (int i = 0; i < machineCode.size(); i++) {
   		cout << machineCode[i] << endl;
	}

	// variableManager.getVectorVariables();
 //    printf( "Koniec Programu\nLiczba zmiennych: %d\n", variableManager.size());
}

void define_variable(string variableName) {
	variableManager.addVariable(new Variable(variableName));
}

void get_variable(string variableName) {
	variableManager.getVariable(variableName)->declarated = true;
	machineCode.push_back("READ");
	machineCode.push_back("STORE 0");

}

void assign_variable(string v1, string v2) {
	printf("%s\n", v2.c_str());
	variableManager.getVariable(v1)->setValue(v2);
}

void put_variable(string v1) {
	variableManager.getInitializedVariable(v1);
	machineCode.push_back("WRITE");
}


void _expression(string v1) {
	if (is_identifier(v1)){

	} else if (is_number(v1)){

	} else {
		cout << "BARDZO POWAŻNY BŁĄD[1] - expressions" << endl;
	}
}

void plus_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[2] - expressions" << endl;
	}	
}
void minus_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[3] - expressions" << endl;
	}	
}
void times_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[4] - expressions" << endl;
	}	
}
void div_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[5] - expressions" << endl;
	}	
}
void mod_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[1] - expressions" << endl;
	}	
}


// Conditions
void eq_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[1] - conditions" << endl;
	}
}

void diff_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[2] - conditions" << endl;
	}
}

void le_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[3] - conditions" << endl;
	}
}

void ge_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[4] - conditions" << endl;
	}
}

void leq_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[5] - conditions" << endl;
	}
}

void geq_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_identifier(v1) && is_number(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[6] - conditions" << endl;
	}
}
