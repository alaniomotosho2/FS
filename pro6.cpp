#include <exception>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;
class Record{
public:
  //i made branch 15 from 5
  char myAge[5] ,myUSN[20],myName[20],myBranch[15],mySem[2];
};

int main()
{
  int yourChoice;
  cout<<setw(80)<<"Secondary index key implementing add(),display(),search() and delete()\n\n";
  while(1){
    cout<<"\nO:exit\n 1: Add Record(s)\n 2:Display Records"<<"\n 3:search Records\n 4:Delete Records ";
     cout<<"\n\n Enter your choice:? "; cin>>yourChoice;
     switch(yourChoice){
       case 1: add();break;
       //case 2: displayFile();break;
       //case 3: search();break;
       //case 4: delete_record();break;
       //case 4: student.search(); break;
       case 0: exit(0);
     }
  }
  return 0;
}
