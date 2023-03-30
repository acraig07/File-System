#include <iostream>
#include "sdisk.h"
#include "filesys.h"
#include "block.h"
#include "shell.h"
#include "table.h"
using namespace std;

int main()
{
  //Sdisk sdisk = Sdisk("sdisk.txt",256,128);
  //Filesys fsys = Filesys("sdisk.txt",256,128);
  Shell shell = Shell("sdisk.txt",256,128);
  Table table = Table("sdisk.txt",256,128,"flatfile","indexfile");
  table.Build_Table("data.txt");

  string s;
  string command = "go";
  string op1, op2;

  while (command != "quit")
  {
    command.clear();
    op1.clear();
    op2.clear();
    cout << "$";
    getline(cin,s);
    int firstblank = s.find(' ');
    if(firstblank < s.length())
    {
      s[firstblank] = '#';
    }

    int secondblank = s.find(' ');
    command = s.substr(0,firstblank);
    if (firstblank < s.length())
      op1 = s.substr(firstblank+1,secondblank-firstblank-1);
    if (secondblank < s.length())
      op2 = s.substr(secondblank+1);
    if (command == "dir")
    {
      shell.dir();    // use the ls function
    }
    if (command == "search")
    {
      table.Search(op1);    // The variable op1 is the date
    }
    if (command == "add")
    {
      shell.add(op1, op2);   // The variable op1 is the new file
    }
    if (command == "del")
    {
      shell.del(op1);   // The variable op1 is the file
    }
    if (command == "type")
    {
      shell.type(op1);    // The variable op1 is the file
    }
    if (command == "copy")
    {
      shell.copy(op1, op2);   // The variable op1 is the source file and the variable op2 is the destination file.
    }
  }
  return 0;
}
