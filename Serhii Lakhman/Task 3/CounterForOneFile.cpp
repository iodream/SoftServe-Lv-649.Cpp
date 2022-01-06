#include "CounterForOneFile.h"

void CounterFofOneFile::CountComments(ifstream& FILE, string line, int& commented_lines)
{

	if (strstr(line.c_str(), "//"))		++commented_lines;
	if (strstr(line.c_str(), "/*"))		LongComments(FILE, code_lines);

}

void CounterFofOneFile::LongComments(ifstream& FILE, int& commented_lines)
{
	string line;

	while (strstr(line.c_str(), "*/"))
	{
		++commented_lines;
		getline(FILE, line);
	}
}

void CounterFofOneFile::CountEmptyLines(string line, int& empty_lines)
{
	if (line == "")  ++empty_lines;
}

void CounterFofOneFile::CountCodeLines(string line, int& code_lines)
{
	if (!strstr(line.c_str(), "//") && !strstr(line.c_str(), "/*") && !strstr(line.c_str(), "*/") && line != "")
		++code_lines;
}

void CounterFofOneFile::WriteData()
{
	ofstream FILE;
	FILE.exceptions(ofstream::badbit | ofstream::failbit);

	try
	{
		FILE.open("info.txt");

		FILE << setw(21) << left << "Empty lines: "		<< setw(16)	<< GetEmptyLines()	   << endl;
		FILE << setw(21) << left << "Commented lines: " << setw(16) << GetCommentedLines() << endl;
		FILE << setw(21) << left << "Code lines: "		<< setw(16) << GetCodeLines()	   << endl;
		FILE << setw(21) << left << "All lines: "		<< setw(16) << GetAllLines()	   << endl;
		FILE << setw(21) << left << "File processed: "	<< setw(16) << GetProcessedFiles() << endl;
		FILE << setw(21) << left << "Spended time: "	<< setw(16) << timer.TimeOfWork()  << endl;

	}
	catch (const ofstream::failure& ex)
	{
		cout << "Writing data " << ex.what() << " " << ex.code() << endl;
	}

}


void CounterFofOneFile::CountEverithing()
{

	ifstream FILE;
	FILE.exceptions(ifstream::badbit | ifstream::failbit);

	string line;

	try
	{
		FILE.open(path);
		
		while (!FILE.eof())
		{
			getline(FILE, line);
			CountEmptyLines(line, empty_lines);
			CountComments(FILE, line, commented_lines);
			CountCodeLines(line, code_lines);
			
			++all_lines;
		}

		WriteData();

	}
	catch (const ifstream::failure& ex) 
	{
		cout << "Opennig files with code" << ex.what() << " " << ex.code() << endl;
	}

}

void CounterFofOneFile::PrintInfo()
{
	cout << setw(21) << left << "Empty lines: "		<< setw(16) << GetEmptyLines()		<< endl;
	cout << setw(21) << left << "Commented lines: " << setw(16) << GetCommentedLines()  << endl;
	cout << setw(21) << left << "Code lines: "		<< setw(16) << GetCodeLines()		<< endl;
	cout << setw(21) << left << "All lines: "		<< setw(16) << GetAllLines()		<< endl;
	cout << setw(21) << left << "File processed: "  << setw(16) << GetProcessedFiles()  << endl;
	cout << setw(21) << left << "Spended time: "	<< setw(16) << timer.TimeOfWork()   << endl;
}
