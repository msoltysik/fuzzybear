#include <iostream>
using namespace std;
 

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
	vector<Variable*> v;

public:
	void addVariable(Variable* var) {
		v.push_back(var);
	}
	void addVariable(string name, string value) {
		Variable* var = new Variable(name, value);
		v.push_back(var);
	}

	int size() {
		return v.size();
	}
};


VariableManager variableManager;



int end_of_file()
{
	Variable* var = new Variable("name");
	var->setValue("12");
	variableManager.addVariable(var);
	printf("%d\n", variableManager.size());


    printf( "Koniec\n" );
}