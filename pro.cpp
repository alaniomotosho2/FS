#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;
void reverseName(string&);//inplace reverse
void std_io();//default std I/O
void usr_io();//redirection and pipe
//void usr_io();
void getNames(vector<string>&, int);
int main()
{
  cout<<"\n\n"<<internal<<setw(80)<<"Programs to implementing I/O redirection and pipe\n\n";
  int ch;
 try{
   do{
    cout<<"\n1: Std. I/O\n2: User File I/O\n3: Exit \n";
    cout<<"Enter your choice ?";
    cin>>ch;
    if(cin.fail()){//test for incorrect input
      cin.clear();
      cin.ignore();
      cerr<<setw(50)<<"Bad Input! Enter Your Choice again?"<<endl;
      cout<<"\n1. Std. I/O\n2.User File I/O\n3. Exit\n\t\tEnter your choice\n";
      cin>>ch;
      //throw runtime_error("Bad Input!");
    }
    switch(ch)
    {
     case 1: std_io(); break;
     case 2: usr_io(); break;
     case 3: exit(0);
    }
   }while(ch<=3);
 }catch(...){
   cerr<<setw(50)<<"You must enter a valid choice!!!";
   exit(0);
 }
 return 0;
}

void std_io(){
  cout<<"Enter The number of names: ? ";
  int num;
  cin>>num;
  //string name[num];
  vector<string> nameList(num);
  getNames(nameList,num);

  cout<<setw(50)<<"The reversed names are :";
  for(auto& myName: nameList){
    reverseName(myName);
    cout<<setw(50)<<myName<<endl;
  }
}

void usr_io(){
  cout<<"Enter The the Name of a file to store the names : ? ";
  string nameFile;
  cin>>nameFile;
  cout<<"Enter The name of file to stored reversed names : ? ";
  string revFile;
  cin>>revFile;
  cout<<"Enter The number of names to enter : ? ";
  int num;
  cin>>num;
  vector<string> nameList(num);
  //redirectio
  fstream outFile(nameFile+".dat",fstream::out|fstream::app);
  fstream outFileR(revFile+".dat",fstream::out);
  getNames(nameList,num);
  streambuf*  cinBuf = cin.rdbuf();//save default std Input before Redirection
  streambuf* coutBuf = cout.rdbuf();//save default std output before redirection
  cout.rdbuf(outFile.rdbuf());//redirect stdout to logical file outFile instead of terminal
  for(auto& item: nameList){
    cout<<item<<endl;
  }

  outFile.close();
  //exit(0);
  string nameToreverse;
  fstream out_file(nameFile+".dat",fstream::in);//reopen oufile for redirection and pipe
  cout.rdbuf(coutBuf);//stdout reset to default
  //redirection and pipe
  cin.rdbuf(out_file.rdbuf());//redirect stdin
  cout.rdbuf(outFileR.rdbuf());//redirection and pipe
  while(cin>>nameToreverse){//redirection and pipe
    if(not nameToreverse.empty()){
      reverseName(nameToreverse);
      cout<<nameToreverse;
    }
  }
  //reset to the  default source and destination of std I/O
  cin.rdbuf(cinBuf);//stdin reset to default
  cout.rdbuf(coutBuf);//stdout reset to default
  cout<<"Redirection and Pipe Done!\n";
}

//reverse function
void reverseName(string& itsName){
  string temp(50,' ');//empty string of size 50 to temporarily hold the reversed string
  int index =0;
  for(int i = itsName.size()-1; i >-1; i--){
    temp[index] = itsName[i];
    index++;
  }
  itsName = temp;//reversed string is done in place so no need to return it explicitly
}
//name are first store in a container
void getNames(vector<string>& nameList,int num){
  string name;
  cout<<"Enter Name? ";
  cin>>name;
  nameList.push_back(name);
  for(int i =1; i < num; i++){
    cout<<"Enter Again ? ";
    cin>>name;
    nameList.push_back(name);
  }
}
