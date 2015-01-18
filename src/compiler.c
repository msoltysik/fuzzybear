#include <iostream>
#include <sstream>
#include <regex>
#include "helpers.c"
using namespace std;
extern int yylineno;

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


class MachineCode {
private:
	std::vector<string> machineCode;
public:
	// pobraną liczbę zapisuje w rejestrze A
	// k := k + 1
	// time = 100
	void push_READ() {
		machineCode.push_back("READ");
	}

	// Wyświetla zawartość rejestru a
	// k := k + 1
	// time = 100
	void push_WRITE() {
		machineCode.push_back("WRITE");
	}

//  -------------------------------------------------------------

	// a := p[i]
	// k := k + 1
	// time = 10
	void push_LOAD(string i) {
		string cmd = "LOAD " + i;
		machineCode.push_back(cmd);
	}

	// p[i] := a
	// k := k + 1
	// time = 10
	void push_STORE(string i) {
		string cmd = "STORE " + i;
		machineCode.push_back(cmd);
	}

//  -------------------------------------------------------------

	// a := a + p[i]
	// k := k + 1
	// time = 30
	void push_ADD(string i) {
		string cmd = "ADD " + i;
		machineCode.push_back(cmd);
	}

	// a := max(a - p[i], 0)
	// k := k + 1
	// time = 30
	void push_SUB(string i) {
		string cmd = "SUB " + i;
		machineCode.push_back(cmd);
	}

	// a := floor(a/2**p[i])
	// k := k + 1
	// time = 12
	void push_SHR(string i) {
		string cmd = "SHR " + i;
		machineCode.push_back(cmd);
	}

	// a := a * 2**p[i]
	// k := k + 1
	// time = 12
	void push_SHL(string i) {
		string cmd = "SHL " + i;
		machineCode.push_back(cmd);
	}

//  -------------------------------------------------------------

	// a := a + 1
	// k := k + 1
	// time = 1
	void push_INC(string i) {
		string cmd = "SHL " + i;
		machineCode.push_back(cmd);
	}

	// a := 0
	// k := k + 1
	// time = 1
	void push_RESET(string i) {
		string cmd = "SHL " + i;
		machineCode.push_back(cmd);
	}

//  -------------------------------------------------------------

	// k := i
	// time = 1
	void push_JUMP(string i) {
		string cmd = "JUMP " + i;
		machineCode.push_back(cmd);
	}

	// Jeśli a = 0, to k :=i
	// W przeciwnym p. k := k + 1
	// time = 1
	void push_JZERO(string i) {
		string cmd = "SHL " + i;
		machineCode.push_back(cmd);
	}

	// Jeśli a nieparzyste, to k := i
	// W przeciwnym przypadku: k := k + 1
	// time = 1
	void push_JODD(string i) {
		string cmd = "SHL " + i;
		machineCode.push_back(cmd);
	}

//  -------------------------------------------------------------

	// Zatrzymaj program
	// time = 0
	void push_HALT() {
		string cmd = "HALT";
		machineCode.push_back(cmd);
	}

//  -------------------------------------------------------------

	void getMachineCode(bool with_linenumber) {
		if (with_linenumber) {
			for (int i = 0; i < machineCode.size(); i++) {
				cout << i << " " << machineCode[i] << endl;
			}
		} else {
			for (int i = 0; i < machineCode.size(); i++) {
				cout << machineCode[i] << endl;
			}
		}
	}


	void getMachineCode() {
		getMachineCode(false);
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
MachineCode machineCode;



int end_of_file() {

	machineCode.push_HALT();
	machineCode.getMachineCode(true);

	variableManager.getVectorVariables();
 //    printf( "Koniec Programu\nLiczba zmiennych: %d\n", variableManager.size());
}

void define_variable(string variableName) {
	variableManager.addVariable(new Variable(variableName));
}

void get_variable(string variableName) {
	variableManager.getVariable(variableName)->declarated = true;
	machineCode.push_READ();
	machineCode.push_STORE("0");

}

void assign_variable(string v1, string v2) {
	printf("%s\n", v2.c_str());
	variableManager.getVariable(v1)->setValue(v2);
}

void put_variable(string v1) {
	variableManager.getInitializedVariable(v1);
	// machineCode.push_back("WRITE");
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

	} else if (is_identifier(v1) && is_number(v2)) {

	} else if (is_identifier(v1) && is_identifier(v2)) {

	} else if (is_number(v1) && is_number(v2)) {

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
