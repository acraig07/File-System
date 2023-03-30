#include "shell.h"
#include "block.h"
#include <iostream>
#include <vector>
using namespace std;

Shell::Shell(string diskname, int numberofblocks, int blocksize) : Filesys(diskname, numberofblocks, blocksize)
{
  cout << "Shell  created" << endl;
}

int Shell::dir()
{
    vector<string> flist = ls();
    
    for(int i = 0; i < flist.size(); i++)
    {
      cout << flist[i] << endl;
    }
    return 1;
}

int Shell::add(string file, string buffer)
{
    int error = newfile(file);
    if(error < 1)
    {
      cout << "Could not add file" << endl;
      return 0;
    }

    vector<string> blocks = block(buffer, getblocksize());
    
    for(int i = 0; i < blocks.size(); i++)
    {
      addblock(file, blocks[i]);
    }
}

int Shell::del(string file)
{
    while(getfirstblock(file) > 0)
    {
      delblock(file, getfirstblock(file));
    }
    
    rmfile(file);
    return 1;
}

int Shell::type(string file)
{
    int block = getfirstblock(file);
    string buffer;

    while(block > 0)
    {
      string t;
      int error = readblock(file, block, t);
      buffer += t;
      block = nextblock(file, block);
    }
    
    cout << buffer << endl;
    cout << buffer.length() << endl;
}

int Shell::copy(string file1, string file2)
{
    int block = getfirstblock(file1);
    int error = newfile(file2);
    string buffer;

    while(block > 0)
    {
      string t;
      error = readblock(file1, block, t);
      buffer += t;
      addblock(file2, buffer);
      block = nextblock(file1, block);
    }
    return 1;
}
