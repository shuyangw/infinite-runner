#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void log_writeln(string msg) {
	ofstream output;
	output.open("/output/log.txt");
	output << msg << endl;
	output.close();
}