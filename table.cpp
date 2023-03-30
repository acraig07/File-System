#include "table.h"
#include "block.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile) : Filesys(diskname, numberofblocks, blocksize){
  this->indexfile = indexfile;
  this->flatfile = flatfile;
  newfile(flatfile);
  newfile(indexfile);
}

int Table::Build_Table(string input_file)
{
  int code = newfile(indexfile);
  code = newfile(flatfile);
  ostringstream ostream;  
  ifstream infile;
  infile.open(input_file.c_str());
  string inputline;
  getline(infile, inputline);

  while(infile.good())
  {
    string key = inputline.substr(0, 5);  
    string rest = inputline.substr(5);  

    vector<string> blocks = block(inputline, getblocksize());
    int blockid = addblock(flatfile, blocks[0]);

    ostream << key << " " << blockid << " ";
    getline(infile, inputline);
  }
  
  ostream << "XXXXX" << " " << 0 << " ";
  string buffer = ostream.str();
  vector<string> iblocks = block(buffer, getblocksize());

  for(int i = 0; i < iblocks.size(); i++)
  {
    addblock(indexfile, iblocks[i]);
  }
  return 1;
}

int Table::Search(string value)
{
  int b = IndexSearch(value);
  if(b <= 0)
  {
  	cout << "Record doesnt exist" << endl;
    return 0;
  }
  else
  {
  	string buffer;
  	readblock(flatfile, b, buffer);
  	cout << buffer << endl;
  }
  return 1;
}

int Table::IndexSearch(string value)
{
  istringstream instream;
  int b = getfirstblock(indexfile);
  while(b != 0)
  {
    string buffer;
    readblock(indexfile, b, buffer);

    string key;
    int block;

    instream.str(buffer);

    for(int i = 1; i <= 4; i++)
    {
      instream >> key >> block;
      if(value == key)
      {
        return block;
      }
    }
    b = nextblock(indexfile, b);
  }
  return 1;
}
