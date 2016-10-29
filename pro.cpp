#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;
void reverseName(string&);
void std_io();
void usr_io();
//void usr_io();
void getNames(vector<string>&, string [], int);
int main()
{
  int ch;
 do{
  cout<<"\n1. Std. I/O\n2.User File I/O\n3. Exit\n\t\tEnter your choice\n";
  cin>>ch;
  switch(ch)
  {
   case 1: std_io(); break;
   case 2: usr_io(); break;
   case 3: exit(0);
  }
 }while(ch<=3);
}

void std_io(){
  cout<<"Enter The number of names :>>\t";
  int num;
  cin>>num;
  cout<<"Enter name :>>\t";
  string name[num];
  vector<string> nameList(num);
  //reuse this function
  getNames(nameList,name,num);

  cout<<"The reversed names are :";
  for(auto& myName: nameList){
    reverseName(myName);
    cout<<right<<setw(15)<<myName<<endl;
  }
}

void usr_io(){
  cout<<"Enter The the Name of a file to store the names :>>\t";
  string nameFile;
  cin>>nameFile;
  cout<<"Enter The name of file to stored reversed names :>>\t";
  string revFile;
  cin>>revFile;
  cout<<"Enter The number of names :>>\t";
  int num;
  cin>>num;
  string name[num];
  vector<string> nameList(num);
  //redirectio
  fstream outFile(nameFile+".dat",fstream::out);
  fstream outFileR(revFile+".dat",fstream::out);
  getNames(nameList,name,num);
  streambuf*  cinBuf = cin.rdbuf();//save old input buffer before Redirection
  streambuf* coutBuf = cout.rdbuf();//save old output buffer before redirection
  cout.rdbuf(outFile.rdbuf());//redirect stdout
  for(auto& myName : nameList ){
    cout<<myName<<" ";
  }
  cout<<endl;
  outFile.close();
  string nameToreverse;
  fstream out_file(nameFile+".dat",fstream::in);//reopen for piping
  cout.rdbuf(coutBuf);//stdout reset to default
  cin.rdbuf(out_file.rdbuf());//redirect stdin
  cout.rdbuf(outFileR.rdbuf());//redirection and pipe
  vector<string> listToreverse(1);
  while(cin>>nameToreverse){
    if(nameToreverse !=" "){
      listToreverse.push_back(nameToreverse);
    }
    for(auto& nameR: listToreverse){
      reverseName(nameR);
      cout<<nameR<<" ";
    }
    listToreverse.clear();
  }
  //reset the buffer
  cin.rdbuf(cinBuf);//stdin reset to default
  cout.rdbuf(coutBuf);//stdout reset to default
  cout<<"Redirection and Pipe Done!\n";
}

//reverse function
void reverseName(string& itsName){
  string temp(50,' ');
  int index =0;
  for(int i = itsName.size()-1; i >-1; i--){
    temp[index] = itsName[i];
    index++;
  }
  itsName = temp;
}
//reusable function
void getNames(vector<string>& nameList,string name[],int num){
  for(int i =0; i < num; i++){
    cin>>name[i];
    cout<<">>\n";
    nameList.push_back(name[i]);
  }
}
