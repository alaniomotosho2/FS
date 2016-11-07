#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

class Student{
public:
  string myId;
  string myName;
  string mySem;
  void pack();
  void unpack();
  int search_rrn(vector<string>&,int);
  void searchBy_rrn();
  void modify();
  //void displayFile();
  int getRCount();
  void displayHeader();
  void printQuery(vector<string>&);
};

int main()
{
  Student student;
  fstream fout("student3.dat",fstream::app);
  if(not fout){
    cerr<<setw(50)<<"File could not be opened!";
    exit(0);//exit succesfully
  }
  fout.close();//file exit, now we can open it again for append in pack function
  int yourChoice;
  //condition is true until user enter zero
  while(1){
    cout<<"\nO:exit\n 1: write to file\n 2:display the file"<<"\n 3:modify the file\n 4:search By RRN";
     cout<<"\n\n Enter your choice:? "; cin>>yourChoice;
     switch(yourChoice)
     {
     case 1: student.pack();break;
     case 2: student.unpack();break;
     case 3: student.modify();break;
     case 4: student.searchBy_rrn(); break;
     case 0: exit(0);
     //default: cerr<<"\nInvalid input!";break;
     }
  }
  return 0;
}

void Student::pack(){
  int rrnCount = getRCount();
  fstream fout("student3.dat",fstream::out|fstream::app);
  if(not fout){
    cerr<<setw(50)<<"File could not be opened!";
  }
  cout<<"\nEnter the student Id :? "; cin>>myId;
  cout<<"\nEnter the student Name:? "; cin>>myName;
  cout<<"\nEnter Semester:? "; cin>>mySem;
  rrnCount +=1;//the next rrn
  string rrn = to_string(rrnCount);
  string buffer  = rrn+"|"+myId+"|"+myName+"|"+mySem+"#";
  fout<<buffer<<endl;
  cout<<setw(50)<<"Done Record Added!";
  fout.close();
}

int Student::getRCount(){
  fstream fin("student3.dat",fstream::in);
  if(not fin){
    cerr<<setw(50)<<"File Could Not be Opened!";
  }

  fin.seekg (0, fstream::end);//check if the file is empty
  int length = fin.tellg();
  if (length == 0 | length == 1){
    fin.close();
    return 0;
  }

  fin.clear();
  fin.seekg(0,fstream::beg);
  string rrcount;
  int sentinel = 0;
  while(fin>>rrcount){
    //do nothing
    sentinel +=1;
  }
  return sentinel;
}

void Student::unpack(){
  vector<string> buffer;
  fstream fin("student3.dat",fstream::in);
  if(not fin){
    cerr<<setw(50)<<"File could not be opened!";
    return;
  }
  string record;
  while(fin>>record){
    buffer.push_back(record);
  }
  printQuery(buffer);
}

void Student::displayHeader(){
  cout<<setw(15)<<"ID"<<setw(15)<<"NAME"<<setw(15)<<"SEMESTER"<<endl;
  cout<<"--------------------------------------------------------------\n";
}

void Student::searchBy_rrn(){
  vector<string> query;
  cout<<"Enter RRN of record to search :? ";
  int rrn;cin>>rrn;
  int location = search_rrn(query,rrn);
  if(location == -1){
    std::cerr << setw(50) <<"RRN didnt match any Record!";
    return;
  }
  printQuery(query);

}
int Student::search_rrn(vector<string>& query, int rrn){
  vector<string> buffer;
  //int location =1;
  string temp;
  string record;
  stringstream streamBuffer;
  fstream fin("student3.dat",fstream::in);
  if(not fin){
    cerr<<setw(50)<<"File could Not be opened!";
    exit(0);
  }
  while(fin>>record){
    buffer.push_back(record);
  }
  for(auto& item : buffer){
    streamBuffer<<item;
    getline(streamBuffer,temp,'|');
    streamBuffer.clear();streamBuffer.str("");
    if(temp == to_string(rrn)){
      streamBuffer.clear();streamBuffer.str("");
      query.push_back(item);
      //return location;
      return rrn;
    }
    //location +=1;//rrn matched
  }
  return -1;//rrn not matched
}

void Student::modify(){
  cout<<"Enter The RRN of the record to modify: ? ";
  int rrn;
  vector<string> buffer;
  cin>>rrn;
  int location = search_rrn(buffer,rrn);
  if(location == -1){
    std::cerr<<setw(50) << "RRN Didnt match any Record!" << std::endl;
    return;
  }
  fstream fin("student3.dat",fstream::in);
  std::vector<string> file;
  string record;
  while(fin>>record){
    file.push_back(record);
  }
  fin.close();
  printQuery(buffer);
  cout<<setw(50)<<"Ente New Records:\n";
  cout<<"Enter ID: ? ";cin>>myId;
  cout<<"Enter Name: ? ";cin>>myName;
  cout<<"Enter Semester: ? ";cin>>mySem;
  int rrnLocation = rrn;
  string internal = to_string(rrn)+"|"+myId+"|"+myName+"|"+mySem+"#";
  file.at(rrnLocation-1) = internal;//modify the file internally
  fstream fout("student3.dat",fstream::out);
  for(auto& record: file){
    fout<<record<<endl;
  }
  cout<<setw(50)<<"Done! Record Modified";
  fout.close();

}

void Student::printQuery(vector<string>& query){
  displayHeader();
  stringstream streamBuffer;
  stringstream endBuffer;
  string temp;
  int hide =0;
  for(auto & item: query){
    streamBuffer<<item;
    while(getline(streamBuffer,temp,'|')){
      endBuffer<<temp;
      getline(endBuffer,temp,'#');//to strip record delimeter
      endBuffer.clear();endBuffer.str("");//clear the buffer
      if(hide ==0){
        //do nothng
      }else{
        cout<<setw(15)<<temp;
      }
      hide +=1;
    }
    cout<<endl;
    hide =0;
    streamBuffer.clear();
    streamBuffer.str("");
  }

}
