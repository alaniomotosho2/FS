#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
void stdIO();
//void usrIO();
void reverseStr(string&);
int main()
{
  int ch;
  do{
   //cout<<"\n1. Std. I/O\n2.User File I/O\n3. Exit\n\t\tEnter your choice\n";
   cout<<"\nEnter \t (1) for Std. I/O\nEnter \t (2) for User File I/O\nEnter \t (0) to quit\n";
   cin>>ch;
   switch(ch)
   {
    case 1: stdIO(); break;
    //case 2: usrIO(); break;
    //case 3: quit();
    default:
    break;
   }
  }while(ch<=3);
return 0;
}
void stdIO()
{
  cout<<"\n Enter the number of names (1 - 10)\n";
  int n;
  cin>>n;
  cout<<"Enter the names \n";
  string name[n];
  for(int i=0;name.length(); i++)
  {
   cin>>name[i];
  }
  reverseStr(name);
  cout<<"\n Reversed of the string Enter is : \n";
  for(auto str: name){
    cout<<name<<setw(15);
  }
}

void reverseStr(string& myName){
  string temp(n,' ');
  int cnt =0;
  for(auto i : myName){
    for(auto j= i.size(); j > -1; j--){
      temp[i] = i[cnt];
      cnt++;
    }
    myName = temp;
  }
}
