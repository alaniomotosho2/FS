#include <sstream>
#include <array>
#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
class Student{
public:
  //char name[15];char usn[15];char age[5];char sem[5];char branch[15];char buffer[60];
  array<char,15> name;array<char,15> usn;array<char,5> age;array<char,5> sem; array<char,15> branch;
  //vector<char> buffer1(60);
};
inline void cleanInput_stream();//we call it many time so we make it inline for perfomance gain
void pack();//function to add records
void search();//search
int unpack(vector<string>&,string,string);
void displayFile();
void modify();
void printHeader();
int main(){

  cout<<"\n\n"<<internal<<setw(120)<<"Fixed Lenght Record programs with fields delimited by '|'implementing pack, unpack, search and modify\n\n";
  fstream fout("student.dat",fstream::app);
  if(not fout){
    cerr<<setw(50)<<"File could not be opened!";
    exit(0);//exit succesfully
  }
  fout.close();//file exit, now we can open it again for append in pack function
  int yourChoice;
  //condition is true until user enter zero
  while(1){
    cout<<"\nO:exit\n 1: write to file\n 2:display the file"<<"\n 3:modify the file\n 4:search";
     cout<<"\n\n Enter your choice ?"; cin>>yourChoice;
     switch(yourChoice)
     {
     case 1: pack();break;
     case 2: displayFile();break;
     case 3: modify();break;
     case 4: search (); break;
     case 0: exit(0);
     default: cerr<<"\nInvalid input!";break;
     }
  }
  return 0;
}

void pack(){
  fstream fout("student.dat",fstream::app);//open file in append mode
  Student student;
  string record;
  if(not fout){
    cerr<<setw(50)<<"File not exist!";
    exit(0);
  }
  cleanInput_stream();
  cout<<"\nEnter the student name ?";//cin>>student.name;
  cin.get(student.name.data(),student.name.size());
  cleanInput_stream();
  cout<<"\nEnter the usn ?";//cin>>student.usn;
  cin.get(student.usn.data(),student.usn.size());
  cleanInput_stream();
  cout<<"\nEnter the age ?";//cin>>student.age;
  cin.get(student.age.data(),student.age.size());
  cleanInput_stream();
  cout<<"\nEnter the sem ?";//cin>>student.sem,5;
  cin.get(student.sem.data(),student.sem.size());
  cleanInput_stream();
  cout<<"\nEnter the branch ?";//cin>>student.branch;
  cin.get(student.branch.data(),student.branch.size());
  cleanInput_stream();
  //pack information
  record =  string(student.name.data())+"|"+ string(student.usn.data())+"|"+string(student.age.data())+"|"+string(student.sem.data())+"|"+string(student.branch.data());
  //record = static_cast<string>(student.name)+"|"+static_cast<string>(student.usn)+"|"+static_cast<string>(student.age)+"|"+static_cast<string>(student.sem)+"|"+static_cast<string>(student.branch);
  fout<<record<<endl;
  fout.close();
  cout<<setw(50)<<"Done Record addeded!";
}

void search(){
  fstream fin("student.dat",fstream::in);
  vector<string> search_record;
  Student student;
  cout<<"Enter records usn you want to search ?";
  string usn;
  cin>>usn;
  cleanInput_stream();
  if(!fin){
    cerr<<"Unable to open file";
    exit(0);//exit with success status
  }
string record;
while(fin>>record){
  if(unpack(search_record,record,usn)){
    //display
    printHeader();
    for(auto& str: search_record){
      cout<<setw(15)<<str<<setw(15);
    }
    cout<<endl;
    return; //search found exit the function
  }
}
cout<<setw(50)<<"Record Not Found!";
}


int unpack(vector<string>& search_record,string record,string usn){
  stringstream searBuffer;
  searBuffer<<record;
  vector<string> temp_list{};
  string temp;
  while(getline(searBuffer,temp,'|')){
    //search_record.push_back(temp);
    temp_list.push_back(temp);
  }
  searBuffer.clear();
  searBuffer.str("");
  if(temp_list.at(1) == usn){//record found
    search_record = temp_list;
    return 1;
  }

  search_record.clear();//clear the vector for another input
  return 0;
}

void displayFile(){
  printHeader();
  fstream fin("student.dat",fstream::in);
  string temp;
  string record;
  stringstream searBuffer;
  vector<string> record_list;
    while(fin>>record){
      searBuffer<<record;//put it in stringstream
      while(getline(searBuffer,temp,'|')){
        record_list.push_back(temp);
      }

      for(auto& str: record_list){
        cout<<setw(15)<<str<<setw(15);
      }
      cout<<endl;
      record_list.clear();
      searBuffer.clear();
      searBuffer.str("");
    }
}

void modify(){
  fstream fin("student.dat",fstream::in);
  if(!fin){
    cerr<<setw(50)<<"file could not be opened!";
    return;
  }
  cout<<"Enter USN of the record you want to update?";
  string usn;
  cin>>usn;
  vector<string> record_list;
  vector<string> tempField;
  stringstream searBuffer;
  string record;
  string temp;
  int recordLocation =0;
  int status =0;
  while(fin>>record){

    record_list.push_back(record);
    tempField.push_back(record);
    if(status == 0){
      if(unpack(tempField,record,usn)){
        status =1;
        printHeader();
        searBuffer<<record;
        while(getline(searBuffer,temp,'|')){
          cout<<setw(15)<<temp;
        }

      }
    }

    if(status == 0){
      recordLocation +=1;//this record usn has to be unique else ir changes the last one
    }
  }
  fin.close();
  if(not status){
    cerr<<setw(50)<<"No match found for the USSN!";
    return;
  }
  Student student;
  cleanInput_stream();
  cout<<"\nEnter new values :\n";
  cout<<"Name ?";//cin>>student.name;
  cin.get(student.name.data(),student.name.size());
  cleanInput_stream();
  cout<<"USN ?";//cin>>student.usn;
  cin.get(student.usn.data(),student.usn.size());
  cleanInput_stream();
  cout<<"Age ?";//cin>>student.age;
  cin.get(student.age.data(),student.age.size());
  cleanInput_stream();
  cout<<"Semester ?";//cin>>student.sem;
  cin.get(student.sem.data(),student.sem.size());
  cleanInput_stream();
  cout<<"Branch ?";//cin>>student.branch;
  cin.get(student.branch.data(),student.branch.size());
  cleanInput_stream();
  //reuse record variable
  record =  string(student.name.data())+"|"+ string(student.usn.data())+"|"+string(student.age.data())+"|"+string(student.sem.data())+"|"+string(student.branch.data());
  //record = static_cast<string>(student.name)+"|"+static_cast<string>(student.usn)+"|"+static_cast<string>(student.age)+"|"+static_cast<string>(student.sem)+"|"+static_cast<string>(student.branch);
  //change the old record in memeory before written to this back
  record_list.at(recordLocation) = record;//update the record
  fstream fout("student.dat",fstream::out);
  for(auto& rcd: record_list){
    fout<<rcd<<endl;
  }
  cout<<setw(50)<<"Done record updated!";
}
void printHeader(){
  cout<<setw(15)<<"NAME"<<setw(15)<<"USN"<<setw(15)<<"AGE"<<setw(15)<<"SEMESTER"<<setw(15)<<"BRANCH"<<endl;
  cout<<"-------------------------------------------------------------------------------\n";
}

inline void cleanInput_stream(){
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(),'\n');
}
