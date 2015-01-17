#include <iostream>
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


class Variable {
public:
	string name;
	string value;

	Variable(string name) {
		this->name = name;
		this->value = "NIL";
	}
	
	Variable(string name, string value) {
		this->name = name;
		this->value = value;
	}

	void setValue(std::string value) {
		this->value = value;
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
				if (variableVector.at(it)->value == "NIL") {
					return true;
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
	variableManager.getVectorVariables();
    printf( "Koniec Programu\nLiczba zmiennych: %d\n", variableManager.size());
}

void define_variable(string variableName) {
	// printf("Deklaruje jak szalony: %s\n", variableName.c_str());
	// printf("Linijka: %d\n", yylineno);
	variableManager.addVariable(new Variable(variableName));
}

void get_variable(string variableName) {
	// printf("%s\n", variableName.c_str());
	variableManager.getVariable(variableName);
}

void assign_variable(string v1, string v2) {
	variableManager.getVariable(v1);
	variableManager.getInitializedVariable(v2);
}

void put_variable(string v1) {
	variableManager.getInitializedVariable(v1);

}