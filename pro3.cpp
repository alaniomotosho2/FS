#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
class Student{
public:
  string myName;
  string myUSN;
  string myAge;
  string mySem;
  string myBranch;
};//always add semi colom
void printHeader();
void pack();
void displayFile();
void search();
int unpack(vector<string>&,string,string);
void modify();
int main()
{
  fstream fout("student2.dat",fstream::app);
  if(!fout){
    cerr<<setw(50)<<"File could not be opened!";
    exit(0);//exit succesfully
  }
  fout.close();//file exit, now we can open it again for append in pack function
  int yourChoice;
  //condition is true until user enter zero
  while(1){
    cout<<setw(30)<<"\nO:exit\n 1: write to file\n 2:display the file"<<"\n 3:modify the file\n 4:search";
     cout<<setw(30)<<"\n\n Enter your choice:>>\t"; cin>>yourChoice;
     switch(yourChoice)
     {
     case 1: pack();break;
     case 2: displayFile();break;
     case 3: modify();break;
     case 4: search (); break;
     case 0: exit(0);
     default: cerr<<setw(30)<<"\nInvalid input!";break;
     }
  }
}

void printHeader(){
  cout<<setw(15)<<"NAME"<<setw(15)<<"USN"<<setw(15)<<"AGE"<<setw(15)<<"SEMESTER"<<setw(15)<<"BRANCH"<<endl;
  cout<<"-------------------------------------------------------------------------------\n";
}

void pack(){
  fstream fout("student2.dat",fstream::app);//open file in append mode
  Student student;
  string record;
  if(!fout){
    cerr<<"File not exist!";
    exit(0);
  }
  cout<<"\nEnter the student name = "; cin>>student.myName;
  cout<<"\nEnter the usn = "; cin>>student.myUSN;
  cout<<"\nEnter the age = "; cin>>student.myAge;
  cout<<"\nEnter the sem = "; cin>>student.mySem;
  cout<<"\nEnter the branch = "; cin>>student.myBranch;
  //pack information
  record = student.myName+"|"+student.myUSN+"|"+student.myAge+"|"+student.mySem+"|"+student.myBranch+"#";
  fout<<record<<endl;
  fout.close();
  cout<<setw(50)<<"Done Record addeded!";
}

void displayFile(){
  printHeader();
  fstream fin("student2.dat",fstream::in);
  string temp;
  string record;
  stringstream searBuffer;
  vector<string> field;
    while(fin>>record){
      searBuffer<<record;//put it in stringstream
      while(getline(searBuffer,temp,'|')){
        field.push_back(temp);
      }
      //i want to strip record delimeter---this method not the best but get the job done
      searBuffer.clear();
      searBuffer.str("");
      temp = field.at(field.size()-1);
      searBuffer<<temp;
      while(getline(searBuffer,temp,'#')){
        field.at(field.size()-1) = temp;
      }


      for(auto& str: field){
        cout<<setw(15)<<str<<setw(15);
      }
      cout<<endl;
      field.clear();
      searBuffer.clear();
      searBuffer.str("");
    }
}

void search(){
  fstream fin("student2.dat",fstream::in);
  vector<string> field;
  Student student;
  cout<<"Enter records usn you want to search :>>\t";
  string usn;
  cin>>usn;
  if(!fin){
    cerr<<"Unable to open file";
    exit(0);//exit with success status
  }
string record;
while(fin>>record){
  if(unpack(field,record,usn)){
    //display
    printHeader();
    for(auto& str: field){
      cout<<setw(15)<<str<<setw(15);
    }
    cout<<endl;
    return; //search found exit the function
  }
}
cout<<setw(50)<<"\nRecord Not Found!\t";
}


int unpack(vector<string>& field,string record,string usn){
  stringstream searBuffer;
  searBuffer<<record;
  string temp;
  while(getline(searBuffer,temp,'|')){
    field.push_back(temp);
  }

  //i want to strip record delimeter---this method not the best but get the job done
  searBuffer.clear();
  searBuffer.str("");
  temp = field.at(field.size()-1);
  searBuffer<<temp;
  while(getline(searBuffer,temp,'#')){
    field.at(field.size()-1) = temp;
  }
  searBuffer.clear();
  searBuffer.str("");
  for(auto& i : field){
    if(i == usn){
      return 1;
    }
  }
  field.clear();//clear the vector for another input
  return 0;//match not found
}

void modify(){
  fstream fin("student2.dat",fstream::in);
  if(!fin){
    cerr<<"file could not be opened!";
    return;
  }
  cout<<"Enter USSN of the record you want to update>>  ";
  string usn;
  cin>>usn;
  vector<string> field;
  vector<string> tempField;
  stringstream searBuffer;
  string record;
  string temp;
  int recordLocation =0;
  int status =0;
  while(fin>>record){

    field.push_back(record);
    tempField.push_back(record);
    if(!status){
      if(unpack(tempField,record,usn)){
        status =1;
        printHeader();
        searBuffer<<record;
        while(getline(searBuffer,temp,'|')){
          cout<<setw(15)<<temp;
        }

      }
    }

    if(!status){
      recordLocation +=1;//this record usn has to be unique else ir changes the last one
    }
  }
  fin.close();
  if(!status){
    cerr<<setw(50)<<"No match found for the USSN!";
    return;
  }
  Student student;
  cout<<"\nEnter new values :\n";
  cout<<"Name :>>";cin>>student.myName;
  cout<<"USN :>>";cin>>student.myUSN;
  cout<<"Age :>>";cin>>student.myAge;
  cout<<"Semester:>>";cin>>student.mySem;
  cout<<"Branch:>>";cin>>student.myBranch;
  //reuse record variable
  record = student.myName+"|"+student.myUSN+"|"+student.myAge+"|"+student.mySem+"|"+student.myBranch+"#";
  //change the old record in memeory before written to this back
  field.at(recordLocation) = record;//update the record for the given location
  fstream fout("student2.dat",fstream::out);
  for(auto& rcd: field){
    fout<<rcd<<endl;
  }
  cout<<endl;
  cout<<setw(50)<<"Done record updated!";
}
