#pragma once
#include "CounterForOneFile.h"

namespace fs = std::filesystem;

struct CounterForGroupOfFiles : CounterFofOneFile
{
public:

	CounterForGroupOfFiles(string path) : CounterFofOneFile(path)
	{
	}

	void CountEverithing() override;

private:

	vector<string> files{ ".cpp", ".h", ".hpp", ".c" };
	vector<string> FileForScan;

	string GetFileExtension(const string& FileName);
	void GetPathes();
	void Counting(string& path);
	static void StartCount(string path, CounterForGroupOfFiles& );

};

