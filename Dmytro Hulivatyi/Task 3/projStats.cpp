#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <regex>

using namespace std;

//counts lines which are commented out as single line comments at the start of the string
void CountSingleCommentLines(const vector<string> &lines, int& nRes)
{
   int nSingleCommentLines=0;
   string pattern("^ *//"); // pattern looks for comments at the beginning of line along with whitespace
   regex r(pattern);
   smatch results;
   for(auto &it:lines)
      if (regex_search(it, results, r))             // if there is a match
          nSingleCommentLines++;                    //increment
     nRes = nSingleCommentLines;
}

//find multiline comments and count the lines
void CountMultiLineCommentLines(const vector<string> &lines, int& nRes)
{
    unsigned int nCommentLinesMulti = 0;
    for(size_t i=0; i<lines.size(); i++)
    {
        string curLine = lines[i];
        if(curLine.find("/*") != std::string::npos)            //found beginning of comment
            for(auto j=i; j<lines.size(); j++)
            {
                curLine=lines[j];
                if(curLine.find("*/") != std::string::npos)    //found end of comment
                    if( i == j )                               // comment has ended on the same line
                    {
                        nCommentLinesMulti++;                  //count this line
                        int nOccurOnThisLine = 0;
                        size_t pos=0;
                        do
                        {
                            pos=curLine.find("/*", pos+1);      //try and see if there is another comment starting
                            if(pos!=std::string::npos)
                                nOccurOnThisLine++;
                        } while(pos != std::string::npos);      //if there is another multiline comment starting here

                        if(nOccurOnThisLine>=1)                 //if there's more than 1
                            continue;                           //counting further till we reach the end
                        else
                            i++;
                        break;
                    }
                    else
                    {
                        nCommentLinesMulti+= (j - i) + 1;   //count the lines between
                        i = j;                              //start next search after the lines we just searched
                        break;
                    }

            }
    }
   nRes = nCommentLinesMulti;
}

//count blank lines or lines with whitespace-only
void CountBlankLines(const vector<string> &lines, int& nRes)
{
   int nBlankLines = 0;
   bool bBlank=true;
   for(auto &it: lines)
   {
       string curLine = it;
       if(curLine.size() == 0)
       {
           nBlankLines++;
           continue;
       }
       for(auto ch=curLine.begin(), end=curLine.end(); ch!=end; ch++)
           if(!isspace(*ch))    //see if any char is not whitespace or blank
           {
               bBlank=false;
               break;
           }
      if(bBlank)
               nBlankLines++;
    }
    nRes=nBlankLines;
}
