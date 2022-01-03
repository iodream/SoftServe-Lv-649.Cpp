#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "projStats.h"

int  main()
{
  using namespace std;
  using namespace std::chrono;
  int nSingleLineComments = 0;
  int nMultiLinesCommentLines = 0;
  int nBlankLines = 0;
  int nCodeLines = 0;
  int nProcessedFiles = 0;
  int nExecTime = 0;

  string exts[]={".cpp", ".c", ".h", ".hpp"}; //these extensions allowed
  vector<string> files;                       //the files we're processing

  namespace fs = std::filesystem;

  cout << "Please enter the path for project root folder: ";
  string rootPath;
  getline(cin,rootPath);                        //getline to deal with spaces


  auto start = high_resolution_clock::now();                                        //start clock

  for(fs::recursive_directory_iterator i(rootPath), end; i != end; ++i)             //recursive iterator will go through all the files in specified diretory via absolute path
    if (!is_directory(i->path()))
      {
        string curFile = i->path().string();                                                 // path of current file
        for(auto &extensions: exts)
            if(std::equal(extensions.rbegin(), extensions.rend(), curFile.rbegin()))  //see if the ending of current file path has our extension
                files.push_back(curFile);                                             //add the file
      }


  for(auto &curfilepath:files)
    {
      int nSingleLineCommentsCur = 0;
      int nMultiLinesCommentLinesCur = 0;
      int nBlankLinesCur = 0;
      int nCodeLinesCur = 0;

      cout << "\nProcessing file " << curfilepath << "...\n";

      ifstream curfile(curfilepath);
      if(!curfile)
      {
          cout << "error opening file: "<< curfilepath << endl;
          exit(1);
      }

      vector<string>lines;
      string s;

      while(getline(curfile,s))
        lines.push_back(s);     //read all lines


      std::thread t1(CountSingleCommentLines, std::ref(lines), std::ref(nSingleLineCommentsCur));
      std::thread t2(CountMultiLineCommentLines, std::ref(lines), std::ref(nMultiLinesCommentLinesCur));
      std::thread t3(CountBlankLines, std::ref(lines), std::ref(nBlankLinesCur));
      t1.join();
      t2.join();
      t3.join();

      nCodeLinesCur = lines.size() - nSingleLineCommentsCur - nMultiLinesCommentLinesCur - nBlankLinesCur+1;  //calculate just the code lines

      //print stats about current file
      cout << "Single Line Comments: "<< nSingleLineCommentsCur << endl;
      cout << "Multi Line Comments: " << nMultiLinesCommentLinesCur << endl;
      cout << "Blank Lines: " << nBlankLinesCur << endl;
      cout << "Code Lines: "<< nCodeLinesCur << endl;

      nProcessedFiles++;

      //update total scores
      nSingleLineComments += nSingleLineCommentsCur;
      nMultiLinesCommentLines += nMultiLinesCommentLinesCur;
      nBlankLines += nBlankLinesCur;
      nCodeLines += nCodeLinesCur;
   }

  auto stop = high_resolution_clock::now();                     //stop timer
  auto duration = duration_cast<microseconds>(stop - start);    //in microseconds
  nExecTime = duration.count();

  cout << "\nResults:\n";
  cout << "Single Line Comments: " << nSingleLineComments<<endl;
  cout << "Multi Line Comments: " << nMultiLinesCommentLines<<endl;
  cout << "Blank Lines: " << nBlankLines << endl;
  cout << "Code Lines: " << nCodeLines << endl;
  cout << "Exec Time(microsecs): " << nExecTime << endl;


  ofstream out("results.txt");
  if(!out)
  {
      cout << "problem opening output file" << endl;
      exit(1);
  }
  out << "Single Line Comments: " << nSingleLineComments << endl;
  out << "Multi Line Comments: " << nMultiLinesCommentLines << endl;
  out << "Blank Lines: " << nBlankLines << endl;
  out << "Code Lines: " << nCodeLines << endl;
  out << "Exec Time(microsecs): " << nExecTime << endl;
  return 0;
}
