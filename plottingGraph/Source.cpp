#include "evaluateAndPlot.h"

int main() {
	string fs[8], g[8];
	int n = 0;
	addGraph(fs[0], fs[1], g[0], n);
	if (fs[0] != "") 
		plotGraph(fs, n, g);
	cout << "SUCCESS!\n";
}	