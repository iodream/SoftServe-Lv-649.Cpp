#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <filesystem>
#include <functional>
#include <vector>
#include <array>
using namespace std;
namespace fs = std::filesystem;

ifstream fin;
ofstream fout;
mutex mtx;

int CountBlankLines(string filePath) {
	mtx.lock();
	fin.open(filePath);
	fin.seekg(0);
	int blankLines = 0;

	if (!fin.is_open()) {
		cout << "Cannot open file";
		mtx.unlock();
		return blankLines;
	}
	else {
		char checkedSymbol;
		vector<char> checkedSymbolVector;

		while (fin.get(checkedSymbol)){
			checkedSymbolVector.push_back(checkedSymbol);
		}

		for (auto i = checkedSymbolVector.begin(); i != checkedSymbolVector.end()-1; ++i) {
			if (*i == '\n' && *(i + 1) == '\n') {
				blankLines++;
			}
		}

		fin.close();
		blankLines++;
		mtx.unlock();
		return blankLines;
	}
}

int CountCommentLines(string filePath) {
	mtx.lock();
	fin.seekg(0);
	fin.open(filePath);
	int commentLines = 0;

	if (!fin.is_open()) {
		cout << "Cannot open file";
		mtx.unlock();
		return commentLines;
	}
	else {
		char checkedSymbol;
		vector<char> checkedSymbolVector;
		bool commentFlag = false;

		while (fin.get(checkedSymbol)) {
			checkedSymbolVector.push_back(checkedSymbol);
		}

		for (auto i = checkedSymbolVector.begin(); i != checkedSymbolVector.end() - 1; ++i) {
			if (*i == '/' && *(i + 1) == '/') {
				commentLines++;
			}

			if (*i == '/' && *(i + 1) == '*') {
				commentFlag = true;
			}
			if (commentFlag && *i == '\n') {
				commentLines++;
			}
			if (*i == '*' && *(i + 1) == '/') {
				commentFlag = false;
			}
			if (*i == '*' && *(i + 1) == '/' && *(i + 2) == '\n') {
				commentFlag = false;
				commentLines++;
			}
		}

		fin.close();
		mtx.unlock();
		return commentLines;
	}
}

int CountAllLines(string filePath) {
	mtx.lock();
	fin.open(filePath);
	int lines = 0;

	if (!fin.is_open()) {
		cout << "Cannot open file";
		mtx.unlock();
		return lines;
	}
	else {
		char checkedSymbol;

		while (fin.get(checkedSymbol)) {
			if (checkedSymbol == '\n') {
				lines++;
			}
		}

		fin.close();
		lines++;
		mtx.unlock();
		return lines;
	}
}

vector<string> GetAllFiles(const fs::path& path){
	vector<string> result;

	for (const auto& p : fs::recursive_directory_iterator(path)){
		if (!fs::is_directory(p)){
			fs::path path = p.path();
			result.push_back(path.string());
		}
	}

	return result;
}

bool EndsWith(string const& fullString, string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

vector<string> FileSelector(vector<string> fileVector) {
	vector<string> selectedFiles;

	for (auto& i : fileVector) {
		if (EndsWith(i, ".cpp")) {
			selectedFiles.push_back(i);
		}
		else if (EndsWith(i, ".c")) {
			selectedFiles.push_back(i);
		}
		else if (EndsWith(i, ".hpp")) {
			selectedFiles.push_back(i);
		}
		else if (EndsWith(i, ".h")) {
			selectedFiles.push_back(i);
		}
		else {
			continue;
		}
	}

	return selectedFiles;
}


int main() {
	fs::path rootFolderPath;
	cout << "Input the root folder of your project:\t";
	cin >> rootFolderPath;

	auto startTime = chrono::high_resolution_clock::now();

	fout.open("result.txt");
	if (!fout.is_open()) {
		cout << "cannot open file";
	}

	vector<string> allFiles = GetAllFiles(rootFolderPath);
	vector<string> selectedFiles = FileSelector(allFiles);

	int codeLines = 0;

	auto RoutineBlankLines = [](vector<string> &sF) {
		int blankLines = 0;
		for (unsigned i = 0; i < sF.size(); i++) {
			blankLines += CountBlankLines(sF[i]);
		}
		fout << "amount of all the blank lines in the folder: " << blankLines << endl;
	};

	auto RoutineCommentLines = [](vector<string> &sF) {
		int commentLines = 0;
		for (unsigned i = 0; i < sF.size(); i++) {
			commentLines += CountCommentLines(sF[i]);
		}
		fout << "amount of all the blank lines in the folder: " << commentLines << endl;
	};

	auto RoutineCodeLines = [](vector<string>& sF) {
		int codeLines = 0;
		for (unsigned i = 0; i < sF.size(); i++) {
			codeLines += CountAllLines(sF[i]) - CountBlankLines(sF[i]) - CountCommentLines(sF[i]);
		}
		fout << "amount of all the code lines in the folder: " << codeLines << endl;
	};

	array<thread, 3> threads;
	threads[0] = thread(RoutineBlankLines, ref(selectedFiles));
	threads[1] = thread(RoutineCommentLines, ref(selectedFiles));
	threads[2] = thread(RoutineCodeLines, ref(selectedFiles));

	fout << "the number of files in the folder: " << allFiles.size() << endl;
	fout << "the number of processed C/C++ files: " << selectedFiles.size() << endl;

	threads[0].join();
	threads[1].join();
	threads[2].join();

	auto endTime = chrono::high_resolution_clock::now();
	chrono::duration<double> durationTime = endTime - startTime;
	fout << "time of execution is " << durationTime.count() << " s\n";

	fout.close();
	return 0;
}