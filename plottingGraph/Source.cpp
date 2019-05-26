#include "evaluateAndPlot.h"

int main() {
	string function;
	cout << "Input function: ";
	getline(cin, function);
	//function = "sqrt(x)";
	//cout << eval(function, -1);
	plotGraph(function);
}	