#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;
class Student{
  public :
  string usn, string name; string sem;
};
void writeFile();
void display();
void pack(Student);
void printHeader();
void print(vector<string>);
vector<string> unpack(string);
int main(){
  cout<<setw(40)<<"\n variable length record delimeted by #\n";
  int your_choice;
  while(1){
    cout<<"\n1: writeFile()\n2: display()\n3: search()\n4: modify()\n5: exit()";
    cout<<"\nEnter your choice ?";
    cin>>your_choice;
    switch (your_choice){
      case 1: writeFile();break;
      case 2: display();break
    }
  }
}

void writeFile(){
  Student student;
  cout<<"Enter sudent usn ?";cin>>student.usn;
  cout<<"Enter student name ?";cin>>student.name;
  cout<<"Enter sudent semester ?";cin>>student.sem;
  fstream fout("pro33.dat",fstream::out|fstream::app);
  string buffer = pack(student);
  fout<<buffer;
  cout<<"Done Record Added!";
  fout.close();
}

string pack(Student obj){
  return student.usn+"|"+student.name+"|"+student.sem+"#";
}

void display(){
fstream fout("pro33.dat",fstream::in);
string buffer;
vector<string> container;
printHeader();
while(getline(fout,buffer,"#")){
  container = unpack(buffer);
  print(container);
  container.clear();
}
}
vector<string> unpack(string buffer){
  stringstream stream;
  string temp;
  stream<<buffer;
  vector<string> list;
  while(getline(stream,temp,'|')){
    list.push_back(temp);
  }
  return list;
}

void print(vector<string> buffer){
  for(auto& item: buffer){
    cout<<setw(20)<<item;
  }
  cout<<endl;
}

void printHeader(){
  cout<<setw(20)<<"USN"<<setw(20)<<"Name"<<setw(20)<<"SEMESTER"<<endl;
  cout<<"--------------------------------------------------------------------\n";
}
