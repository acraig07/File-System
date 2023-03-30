#ifndef FILESYS_H
#define FILESYS_H
#include "sdisk.h"
#include <string>
#include <vector>
using namespace std;

class Filesys : public Sdisk
{
public:
    	Filesys(string diskname, int numberofblocks, int blocksize);
    	int fsclose();
    	int newfile(string file);
    	int rmfile(string file);
    	int getfirstblock(string file);
    	int addblock(string file, string block);
    	int delblock(string file, int blocknumber);
    	int readblock(string file, int blocknumber, string& buffer);
    	int writeblock(string file, int blocknumber, string buffer);
    	int nextblock(string file, int blocknumber);
    	vector<string> ls();

private:
    	int rootsize;
    	int fatsize;
    	vector<string> filename;
    	vector<int> firstblock;
    	vector<int> fat;
    	int buildfs();
    	int readfs();
    	int fssynch();
    	bool checkblock(string file, int blocknumber);
};
#endif
