#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Writes to std out and to a log file in log.txt
void log_writeln(string msg) {
	ofstream output;
	output.open("log.txt");
	cout << msg << endl;
	output << msg << endl;
	output.close();
}