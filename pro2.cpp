#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
class Student{
public:
  char name[15];char usn[15];char age[5];char sem[5];char branch[15];char buffer[60];
  //vector<char> buffer1(60);
};
void pack();//function to add records
void search();//search
int unpack(vector<string>&,string,string);
void displayFile();
void modify();
void printHeader();
int main(){
  fstream fout("student.dat",fstream::app);
  if(!fout){
    cerr<<setw(50)<<"File could not be opened!";
    exit(0);//exit succesfully
  }
  fout.close();//file exit, now we can open it again for append in pack function
  int yourChoice;
  //condition is true until user enter zero
  while(1){
    cout<<"\nO:exit\n 1: write to file\n 2:display the file"<<"\n 3:modify the file\n 4:search";
     cout<<"\n\n Enter your choice:>>\t"; cin>>yourChoice;
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
}

void pack(){
  fstream fout("student.dat",fstream::app);//open file in append mode
  Student student;
  string record;
  if(!fout){
    cerr<<setw(50)<<"File not exist!";
    exit(0);
  }
  cout<<"\nEnter the student name = "; cin>>student.name;
  cout<<"\nEnter the usn = "; cin>>student.usn;
  cout<<"\nEnter the age = "; cin>>student.age;
  cout<<"\nEnter the sem = "; cin>>student.sem;
  cout<<"\nEnter the branch = "; cin>>student.branch;
  //pack information
  record = static_cast<string>(student.name)+"|"+static_cast<string>(student.usn)+"|"+static_cast<string>(student.age)+"|"+static_cast<string>(student.sem)+"|"+static_cast<string>(student.branch);
  fout<<record<<endl;
  fout.close();
  cout<<setw(50)<<"Done Record addeded!";
}

void search(){
  fstream fin("student.dat",fstream::in);
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
    cout<<"sear\n";
    //display
    printHeader();
    for(auto& str: field){
      cout<<setw(15)<<str<<setw(15);
    }
    cout<<endl;
    return; //search found exit the function
  }
}
cout<<setw(50)<<"Record Not Found!";
}


int unpack(vector<string>& field,string record,string usn){
  stringstream searBuffer;
  searBuffer<<record;
  string temp;
  while(getline(searBuffer,temp,'|')){
    field.push_back(temp);
  }
  searBuffer.clear();
  searBuffer.str("");

    for(auto& i : field){
      //there is hidden bugs here
      if(i == usn){
        return 1;
      }
    }
  field.clear();//clear the vector for another input
  return 0;
}

void displayFile(){
  printHeader();
  fstream fin("student.dat",fstream::in);
  string temp;
  string record;
  stringstream searBuffer;
  vector<string> field;
    while(fin>>record){
      searBuffer<<record;//put it in stringstream
      while(getline(searBuffer,temp,'|')){
        field.push_back(temp);
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

void modify(){
  fstream fin("student.dat",fstream::in);
  if(!fin){
    cerr<<setw(50)<<"file could not be opened!";
    return;
  }
  cout<<"Enter USSN of the record you want to update>>\t";
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
  if(!status){
    cerr<<setw(50)<<"No match found for the USSN!";
    return;
  }
  Student student;
  cout<<"\nEnter new values :\n";
  cout<<"Name :>>";cin>>student.name;
  cout<<"USN :>>";cin>>student.usn;
  cout<<"Age :>>";cin>>student.age;
  cout<<"Semester:>>";cin>>student.sem;
  cout<<"Branch:>>";cin>>student.branch;
  //reuse record variable
  record = static_cast<string>(student.name)+"|"+static_cast<string>(student.usn)+"|"+static_cast<string>(student.age)+"|"+static_cast<string>(student.sem)+"|"+static_cast<string>(student.branch);
  //change the old record in memeory before written to this back
  field.at(recordLocation) = record;//update the record
  fstream fout("student.dat",fstream::out);
  for(auto& rcd: field){
    fout<<rcd<<endl;
  }
  cout<<setw(50)<<"Done record updated!";
}
void printHeader(){
  cout<<setw(15)<<"Name"<<setw(15)<<"USN"<<setw(15)<<"Age"<<setw(15)<<"semester"<<setw(15)<<"Branch"<<endl;
  cout<<"-------------------------------------------------------------------------------\n";
}
