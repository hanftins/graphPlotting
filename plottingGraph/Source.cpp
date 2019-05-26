#include "evaluateAndPlot.h"

int main() {
	string fs[3];
	int n;
	do {
		cout << "How many functions do you want to plot? (max = 3): ";
		cin >> n;
		if (n <= 0 || n > 3)
			cout << "Invalid option, try again!\n";
	} while (n <= 0 || n > 3);	
	rewind(stdin);
	for (int i = 0; i < n; i++) {
		cout << "Input function " << i + 1 << ": ";
		getline(cin, fs[i]);
	}
	plotGraph(fs, n);
}	