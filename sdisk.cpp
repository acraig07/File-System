#include "sdisk.h"
#include <iostream>
#include <fstream>
using namespace std;

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize)
{
  this->diskname = diskname;
  this->numberofblocks = numberofblocks;
  this->blocksize = blocksize;

  fstream file;
  file.open(diskname.c_str(), ios::in | ios::out);

  if(file)
  {
    cout << "File exists!" << endl;
  }
  else
  {
    file.open(diskname.c_str(), ios::out);
    
    for(int i = 0; i < (blocksize * numberofblocks); i++)
    {
      file.put('#');
    }
  }
  file.close();
}

int Sdisk::getblock(int blocknumber, string& buffer)
{
  fstream infile;
  infile.open(diskname.c_str(), ios::in | ios::out);
  infile.seekg(blocknumber*blocksize);
  
  if(infile.good())
  {
    for(int i = 0; i < blocksize; i++)
    {
      buffer += infile.get();
    }
    infile.close();
    return 1;
  }
  else
  {
    return 0;
  }
}

int Sdisk::putblock(int blocknumber, string buffer)
{
  fstream outfile;
  outfile.open(diskname.c_str(), ios::in | ios::out);
  outfile.seekg(blocknumber*blocksize);
  
  if(outfile.good())
  {
    for(int i = 0; i < buffer.length() && i < blocksize; i++)
    {
      outfile.put(buffer[i]);
    }
    outfile.close();
    return 1;
  }
  else
  {
    cout << "Failed to write to " << diskname << endl;
    return 0;
  }
}

int Sdisk::getnumberofblocks()
{
  return numberofblocks;
}

int Sdisk::getblocksize()
{
  return blocksize;
}
