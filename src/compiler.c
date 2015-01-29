#include <iostream>
#include <sstream>
#include <regex>
#include "helpers.c"

using namespace std;
extern int yylineno;

// Stąd zaczynamy zapisywać zmienne
// Pierwsza zmienna jest w p[10]
int memory_pointer = 9; 
bool dbg = false;

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

	// a := a + 1
	// k := k + 1
	// time = 1
	void push_INC() {
		string cmd = "INC";
		machineCode.push_back(cmd);
	}

	// a := 0
	// k := k + 1
	// time = 1
	void push_RESET() {
		string cmd = "RESET";
		machineCode.push_back(cmd);
	}

	// k := i
	// time = 1
	void push_JUMP(string i) {
		string cmd = "JUMP " + i;
		machineCode.push_back(cmd);
	}

	void push_JUMP(int i) {
		string cmd = "JUMP " + to_string(i);
		machineCode.push_back(cmd);
	}

	// Jeśli a = 0, to k :=i
	// W przeciwnym p. k := k + 1
	// time = 1
	void push_JZERO(string i) {
		string cmd = "JZERO " + i;
		machineCode.push_back(cmd);
	}

	void push_JZERO(int i) {
		string cmd = "JZERO " + to_string(i);
		machineCode.push_back(cmd);
	}

	// Jeśli a nieparzyste, to k := i
	// W przeciwnym przypadku: k := k + 1
	// time = 1
	void push_JODD(string i) {
		string cmd = "JODD " + i;
		machineCode.push_back(cmd);
	}

	void push_JODD(int i) {
		string cmd = "JODD " + to_string(i);
		machineCode.push_back(cmd);
	}

	// Zatrzymaj program
	// time = 0
	void push_HALT() {
		string cmd = "HALT";
		machineCode.push_back(cmd);
	}


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

	int lineNumber() {
		return machineCode.size();
	}

	void getMachineCode() {
		getMachineCode(false);
	}
};

class Variable {
public:
	string name;					// nazwa
	string value;					// wartość
	bool initialized;				// zainicjowana?
	unsigned int memory_adress; 	// numer komórki pamięci

	Variable(string name) {
		this->name = name;
		this->initialized = false;
	}
	
	Variable(string name, string value) {
		this->name = name;
		this->value = value;
		this->initialized = true;
	}

	void setValue(string value) {
		this->value = value;
		this->initialized = true;
	}

	void setMemoryAdress(unsigned int memory_adress) {
		this->memory_adress = memory_adress;
	}

	string getMemoryAdress() {
		return to_string(this->memory_adress);
	}

};

class VariableManager {
private:
	vector<Variable*> variableVector;

	bool inVectorByName() {
		return false;
	}

	bool inVector(Variable* variable) {
		for (int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == variable->name) {
				return true;
			}
		}
		return false;
	}

	bool notInVector(string name) {
		for (int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == name) {
				return false;
			}
		}
		return true;
	}

	bool notInitialized(string name) {
		for(int it = 0; it < variableVector.size(); it++) {
			if (variableVector.at(it)->name == name) {
				if (variableVector.at(it)->initialized) {
					return false;
				} else {
					return true;
				}
			}
		}
		return false;
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
		cout << endl;
		for(int it = 0; it < variableVector.size(); it++) {
			printf("Name: \"%s\", Value: \"%s\", declarated? \"%d\", memory_adress \"%d\"\n",
				variableVector.at(it)->name.c_str(),
				variableVector.at(it)->value.c_str(),
				variableVector.at(it)->initialized,
				variableVector.at(it)->memory_adress
				);
		}
	}
};


VariableManager variableManager;
MachineCode machineCode;

int end_of_file() {
	machineCode.push_HALT();
}

void generate_cc() {
	machineCode.getMachineCode(dbg);
	if (dbg) {
		variableManager.getVectorVariables();
	}
}

void define_variable(string variableName) {
	Variable* temp = new Variable(variableName);
	temp->setMemoryAdress(++memory_pointer);
	variableManager.addVariable(temp);
}

void get_variable(string variableName) {
	int memory_adress = memory_pointer++;
	variableManager.getVariable(variableName)->initialized = true;
	variableManager.getVariable(variableName)->memory_adress = memory_adress;

	machineCode.push_READ();
	machineCode.push_STORE(to_string(memory_adress));
}

void assign_variable(string v1) {
	Variable *var =	variableManager.getVariable(v1);
	machineCode.push_STORE(to_string(var->memory_adress));
	var->initialized = true;
}

void put_variable(string v1) {
	Variable *var =	variableManager.getInitializedVariable(v1);
	machineCode.push_LOAD(to_string(var->memory_adress));
	machineCode.push_WRITE();
}

void generate_number(string v1) {
	string number = DecToBin(v1);
	int size = number.length();
	machineCode.push_RESET();
	bool stored = false;

	for (int i = 0; i < size; ++i) {
		if (number[i] == '1')
			machineCode.push_INC();
		if (!stored) {
			machineCode.push_STORE("0");
			stored = true;
		}
		if (i < size - 1)
			machineCode.push_SHL("0");
	}
}

void _expression(string v1) {
	if (is_identifier(v1)) {
		string memory_adress = variableManager.getInitializedVariable(v1)->getMemoryAdress();
		machineCode.push_LOAD(memory_adress);
	} else if (is_number(v1)) {
		generate_number(v1);
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[1] - expressions" << endl;
	}
}

void plus_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
		Variable *var1 = variableManager.getInitializedVariable(v1);
		machineCode.push_LOAD(var1->getMemoryAdress());
		machineCode.push_STORE("1");
		generate_number(v2);
		machineCode.push_ADD("1");
	} else if (is_number(v1) && is_identifier(v2)) {
		generate_number(v1);
		machineCode.push_STORE("1");
		Variable *var2 = variableManager.getInitializedVariable(v2);
		machineCode.push_LOAD(var2->getMemoryAdress());
		machineCode.push_ADD("1");
	} else if (is_identifier(v1) && is_identifier(v2)) {
		Variable *var1 = variableManager.getInitializedVariable(v1);
		Variable *var2 = variableManager.getInitializedVariable(v2);
		machineCode.push_LOAD(var1->getMemoryAdress());
		machineCode.push_STORE("1");
		machineCode.push_LOAD(var2->getMemoryAdress());
		machineCode.push_ADD("1");
	} else if (is_number(v1) && is_number(v2)) {
		generate_number(v1);
		machineCode.push_STORE("1");
		generate_number(v2);
		machineCode.push_ADD("1");
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[2] - expressions" << endl;
	}
}

void minus_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
		generate_number(v2);
		machineCode.push_STORE("1");
		Variable *var1 = variableManager.getInitializedVariable(v1);
		machineCode.push_LOAD(var1->getMemoryAdress());
		machineCode.push_SUB("1");
	} else if (is_number(v1) && is_identifier(v2)) {
		Variable *var2 = variableManager.getInitializedVariable(v2);
		machineCode.push_LOAD(var2->getMemoryAdress());
		machineCode.push_STORE("1");
		generate_number(v1);
		machineCode.push_SUB("1");
	} else if (is_identifier(v1) && is_identifier(v2)) {
		Variable *var2 = variableManager.getInitializedVariable(v2);
		Variable *var1 = variableManager.getInitializedVariable(v1);
		machineCode.push_LOAD(var2->getMemoryAdress());
		machineCode.push_STORE("1");
		machineCode.push_LOAD(var1->getMemoryAdress());
		machineCode.push_SUB("1");
	} else if (is_number(v1) && is_number(v2)) {
		generate_number(v2);
		machineCode.push_STORE("1");
		generate_number(v1);
		machineCode.push_SUB("1");
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[3] - expressions" << endl;
	}	
}

// p[0] | p[1] | p[2] | p[3]
//  1   |  v1  |  v2  | v1 * v2
void times_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
		Variable *var1 = variableManager.getInitializedVariable(v1);
		machineCode.push_LOAD(var1->getMemoryAdress());
		machineCode.push_STORE("1");
		generate_number(v2);
		machineCode.push_STORE("2");

		machineCode.push_LOAD("2");
		machineCode.push_SUB("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 7);
		// swap(bo v1 <= v2)
		machineCode.push_LOAD("1");
		machineCode.push_STORE("3");
		machineCode.push_LOAD("2");
		machineCode.push_STORE("1");
		machineCode.push_LOAD("3");
		machineCode.push_STORE("2");
		
		machineCode.push_RESET();
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 5);
		machineCode.push_LOAD("3");
		machineCode.push_ADD("1");
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 3);
		machineCode.push_LOAD("2");
		machineCode.push_JODD(machineCode.lineNumber() - 5);
		machineCode.push_LOAD("2");
		machineCode.push_SHR("0");
		machineCode.push_STORE("2");
		machineCode.push_LOAD("1");
		machineCode.push_SHL("0");
		machineCode.push_STORE("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 2);
		machineCode.push_JUMP(machineCode.lineNumber() - 9);

		machineCode.push_LOAD("3");

	} else if (is_number(v1) && is_identifier(v2)) {
		generate_number(v1);
		machineCode.push_STORE("1");
		Variable *var2 = variableManager.getInitializedVariable(v2);
		machineCode.push_LOAD(var2->getMemoryAdress());
		machineCode.push_STORE("2");

		machineCode.push_LOAD("2");
		machineCode.push_SUB("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 7);
		// swap(bo v1 <= v2)
		machineCode.push_LOAD("1");
		machineCode.push_STORE("3");
		machineCode.push_LOAD("2");
		machineCode.push_STORE("1");
		machineCode.push_LOAD("3");
		machineCode.push_STORE("2");
		
		machineCode.push_RESET();
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 5);
		machineCode.push_LOAD("3");
		machineCode.push_ADD("1");
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 3);
		machineCode.push_LOAD("2");
		machineCode.push_JODD(machineCode.lineNumber() - 5);
		machineCode.push_LOAD("2");
		machineCode.push_SHR("0");
		machineCode.push_STORE("2");
		machineCode.push_LOAD("1");
		machineCode.push_SHL("0");
		machineCode.push_STORE("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 2);
		machineCode.push_JUMP(machineCode.lineNumber() - 9);

		machineCode.push_LOAD("3");

	} else if (is_identifier(v1) && is_identifier(v2)) {
		Variable *var1 = variableManager.getInitializedVariable(v1);
		Variable *var2 = variableManager.getInitializedVariable(v2);
		machineCode.push_LOAD(var2->getMemoryAdress());
		machineCode.push_STORE("1");
		machineCode.push_LOAD(var1->getMemoryAdress());
		machineCode.push_STORE("2");

		machineCode.push_LOAD("2");
		machineCode.push_SUB("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 7);
		// swap(bo v1 <= v2)
		machineCode.push_LOAD("1");
		machineCode.push_STORE("3");
		machineCode.push_LOAD("2");
		machineCode.push_STORE("1");
		machineCode.push_LOAD("3");
		machineCode.push_STORE("2");
		
		machineCode.push_RESET();
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 5);
		machineCode.push_LOAD("3");
		machineCode.push_ADD("1");
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 3);
		machineCode.push_LOAD("2");
		machineCode.push_JODD(machineCode.lineNumber() - 5);
		machineCode.push_LOAD("2");
		machineCode.push_SHR("0");
		machineCode.push_STORE("2");
		machineCode.push_LOAD("1");
		machineCode.push_SHL("0");
		machineCode.push_STORE("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 2);
		machineCode.push_JUMP(machineCode.lineNumber() - 9);

		machineCode.push_LOAD("3");

	} else if (is_number(v1) && is_number(v2)) {

		machineCode.push_RESET();
		machineCode.push_INC();
		machineCode.push_STORE("0");
		generate_number(v2);
		machineCode.push_STORE("1");
		generate_number(v1);
		machineCode.push_STORE("2");

		machineCode.push_LOAD("2");
		machineCode.push_SUB("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 7);
		// swap(bo v1 <= v2)
		machineCode.push_LOAD("1");
		machineCode.push_STORE("3");
		machineCode.push_LOAD("2");
		machineCode.push_STORE("1");
		machineCode.push_LOAD("3");
		machineCode.push_STORE("2");
		
		machineCode.push_RESET();
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 5);
		machineCode.push_LOAD("3");
		machineCode.push_ADD("1");
		machineCode.push_STORE("3");
		machineCode.push_JUMP(machineCode.lineNumber() + 3);
		machineCode.push_LOAD("2");
		machineCode.push_JODD(machineCode.lineNumber() - 5);
		machineCode.push_LOAD("2");
		machineCode.push_SHR("0");
		machineCode.push_STORE("2");
		machineCode.push_LOAD("1");
		machineCode.push_SHL("0");
		machineCode.push_STORE("1");
		machineCode.push_JZERO(machineCode.lineNumber() + 2);
		machineCode.push_JUMP(machineCode.lineNumber() - 9);

		machineCode.push_LOAD("3");
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[4] - expressions" << endl;
	}
}

void div_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_number(v1) && is_identifier(v2)) {
	} else if (is_identifier(v1) && is_identifier(v2)) {
	} else if (is_number(v1) && is_number(v2)) {
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[5] - expressions" << endl;
	}
}

void mod_expression(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_number(v1) && is_identifier(v2)) {
	} else if (is_identifier(v1) && is_identifier(v2)) {
	} else if (is_number(v1) && is_number(v2)) {
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[6] - expressions" << endl;
	}
}


// Conditions
void eq_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {

	} else if (is_number(v1) && is_identifier(v2)) {

	} else if (is_identifier(v1) && is_identifier(v2)) {

	} else if (is_number(v1) && is_number(v2)) {

	} else {
		cout << "BARDZO POWAŻNY BŁĄD[1] - conditions" << endl;
	}
}

void diff_condition(string v1, string v2) {
	if (is_identifier(v1) && is_number(v2)) {
	} else if (is_number(v1) && is_identifier(v2))
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
	} else if (is_number(v1) && is_identifier(v2))
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
	} else if (is_number(v1) && is_identifier(v2))
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
	} else if (is_number(v1) && is_identifier(v2))
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
	} else if (is_number(v1) && is_identifier(v2))
	{
	} else if (is_identifier(v1) && is_identifier(v2))
	{
	} else if (is_number(v1) && is_number(v2))
	{
	} else {
		cout << "BARDZO POWAŻNY BŁĄD[6] - conditions" << endl;
	}
}
