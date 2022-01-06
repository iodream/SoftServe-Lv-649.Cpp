#include "CounterForGroupOfFiles.h"

void CounterForGroupOfFiles::CountEverithing()
{

	GetPathes();
	vector<thread> t;

	for (int i = 0; i < FileForScan.size(); i++)
	{
		t.push_back(thread(StartCount, FileForScan[i], std::ref(*this)));
		t[i].join();
	}
	
	processed_files = FileForScan.size();
	WriteData();

}

string CounterForGroupOfFiles::GetFileExtension(const string& FileName)
{
	if (FileName.find_last_of(".") != string::npos)
		return   FileName.substr(FileName.find_last_of("."));
	return "";
}

void CounterForGroupOfFiles::GetPathes()
{
	for (auto const& dir_entry : fs::directory_iterator(path)) {

		auto &fileName = dir_entry.path().native();
		string temp(fileName.begin(), fileName.end());

		for (int i = 0; i < files.size(); i++)
		{
			if (GetFileExtension(temp) == files[i])	FileForScan.push_back(temp);
		}

	}
}

void CounterForGroupOfFiles::Counting(string& path)
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

	}
	catch (const ifstream::failure& ex)
	{
		cout << "Opennig files with code" << ex.what() << " " << ex.code() << "\t" << path << endl;
	}

}

void CounterForGroupOfFiles::StartCount(string path, CounterForGroupOfFiles& counter)
{
	counter.Counting(path);
}
