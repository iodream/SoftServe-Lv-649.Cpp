#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <Windows.h>
#include <thread>
#include <iomanip>
#include <vector>
#include "Timer.h"
#include <filesystem>
#include <mutex>

using namespace std;

struct CounterFofOneFile
{

public:
	
	CounterFofOneFile(string path) 
	{
		this->path = path;
	}

	virtual void CountEverithing();
	void PrintInfo();

protected:

	int code_lines = 0, empty_lines = 0, commented_lines = 0, all_lines = 0;
	int processed_files = 1;

	string path;
	Timer timer;

	void CountComments(ifstream& FILE, string line, int& commented_lines);
	void LongComments(ifstream& FILE, int& commented_lines);
	void CountEmptyLines(string line, int& empty_lines);
	void CountCodeLines(string line, int& code_lines);	
	void WriteData();

	int GetCommentedLines() { return commented_lines; }
	int GetEmptyLines()		{ return empty_lines;	  }
	int GetCodeLines()		{ return code_lines;	  }
	int GetAllLines()		{ return all_lines;		  }
	int GetProcessedFiles() { return processed_files; }


};