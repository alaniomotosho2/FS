#include <map>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <cstdio>
using namespace std;

class Record{
public:
  //i made branch 15 from 5
  char myAge[5] ,myUSN[20],myName[20],myBranch[15],mySem[2];
};
void add();
void sort_usn();
void displayFile();
void printHeader();
void unpack(vector<string>&);
void printRecord(vector<string>&);
void search();
int search_handler(int);
void delete_record();
void delete_handler(int);
void update_index(int);
int main()
{
  int yourChoice;
  cout<<setw(80)<<"Simple index on a primary key implementing add(),display(),search() and delete()\n\n";

  while(1){
    cout<<"\nO:exit\n 1: Add Record(s)\n 2:Display Records"<<"\n 3:search Records\n 4:Delete Records ";
     cout<<"\n\n Enter your choice:? "; cin>>yourChoice;
     switch(yourChoice){
       case 1: add();break;
       case 2: displayFile();break;
       case 3: search();break;
       case 4: delete_record();break;
       case 0: exit(0);
     }
  }
}

void add(){
  Record re;
  string record;
  fstream fout_data("recordd.dat",fstream::out|fstream::app|fstream::binary);
  fstream fout_index("indexx.dat",fstream::out|fstream::app|fstream::app|fstream::binary);
  //index_count = getIndex_Count();
  if(!fout_data | !fout_index){
    cerr<<setw(50)<<"File Could not be opened!";
    return;
  }
  string inp;
  cout<<"\nEnter student USN :? ";
  cin>>inp;inp.copy(re.myUSN,inp.size());re.myUSN[inp.size()] = '\0';
  cout<<"\nEnter student Name:? ";cin>>inp;inp.copy(re.myName,inp.size());re.myName[inp.size()] = '\0';
  cout<<"\nEnter student Age:? ";cin>>inp;inp.copy(re.myAge,inp.size());re.myAge[inp.size()] = '\0';
  cout<<"\nEnter student Semester:? ";cin>>inp;inp.copy(re.mySem,inp.size());re.mySem[inp.size()] = '\0';
  cout<<"\nEnter student Branch:? ";cin>>inp;inp.copy(re.myBranch,inp.size());re.myBranch[inp.size()] = '\0';
  string buffer_data = string(re.myUSN)+"|"+string(re.myName)+"|"+string(re.myAge)+"|"+string(re.mySem)+"|"+string(re.myBranch)+"#";
  //fout_data.write(buffer_data.c_str(),buffer_data.size()+1);
  fout_data<<buffer_data;
  //fout_data<<re.myUSN+"|"+re.myName+"|"+re.myAge+"|"+re.mySem+"|"+re.myBranch+"#";
  long len = buffer_data.size();
  long byte_offset;
  //len +=1;
  if(fout_data.tellp() == 0){
    byte_offset = fout_data.tellp() - len;
  }
  if(fout_data.tellp() != 0){
    byte_offset = fout_data.tellp() - len;
  }
  string index_data = string(re.myUSN)+"|"+to_string(byte_offset);
  fout_index<<re.myUSN<<"|"<<to_string(byte_offset)<<endl;
  //cout<<buffer_data.size()<<" Tell == "<<fout_data.tellp()<<endl;
  fout_data.close();
  fout_index.close();
  sort_usn();
  cout<<setw(50)<<"Done Record Added!";
}

void sort_usn(){
  fstream fout_index("indexx.dat",fstream::in|fstream::binary);
  fstream fout_temp("temp_file.dat",fstream::out|fstream::binary);
  vector<int> key{};
  vector<string> ref{};
  int tmp;
  map<int,string> index_file;
  stringstream stream;
  string record;
  string keykey; string refref;
  while(fout_index>>record){
    stream<<record;
    getline(stream,keykey,'|');
    getline(stream,refref,'\n');
    tmp = stoi(keykey);
    //tmp = stoi(keykey);
    key.push_back(tmp);
    ref.push_back(refref);
    stream.clear();
  }
  fout_index.close();
//sort(index_file.begin(),index_file.end());
  for(int i{0};i < key.size(); i++){
    index_file[key.at(i)] = ref.at(i);
  }

  for(auto& key: index_file){
    fout_temp<<key.first<<'|'<<key.second<<endl;
  }
  rename("temp_file.dat","indexx.dat");
  fout_temp.close();

}

void displayFile(){
  fstream fout_data("recordd.dat",fstream::in);
  vector<string> record{};
  string rec;
  printHeader();
  while(getline(fout_data,rec,'#')){
    record.push_back(rec);
    unpack(record);
    printRecord(record);
  }
}
void printHeader(){
  cout<<setw(15)<<"USN"<<setw(15)<<"NAME"<<setw(15)<<"AGE"<<setw(15)<<"SEMESTER"<<setw(15)<<"BRANCH"<<endl;
  cout<<"-------------------------------------------------------------------------------\n";
}


void unpack(vector<string>& record){
  stringstream stream;
  string stream_record = record.front();
  string temp;
  stream<<stream_record ;
  record.clear();
  while(getline(stream,temp,'|')){
    record.push_back(temp);
  }
  stream.clear();
}

void printRecord(vector<string>& record){
  for(auto& item : record){
    cout<<setw(15)<<item;
  }
  cout<<endl;
  record.clear();
}


void search(){
  cout<<"Enter The usn you want to search ?";
  int usn;
  cin>>usn;
  int byte_offset = search_handler(usn);
  if(byte_offset < 0 ){
    cerr<<setw(50)<<"No Match Found!";
    return;
  }
fstream fout_data("recordd.dat",fstream::in);
fout_data.seekg(byte_offset,fstream::beg);
string rec;
getline(fout_data,rec,'#');//what if we are seeking the last record???
std::vector<string> record;
record.push_back(rec);
unpack(record);
printHeader();
printRecord(record);
fout_data.close();
}

int search_handler(int usn){
  fstream fout_index("indexx.dat",fstream::in);
  stringstream stream;
  string key,value, rec;
  while(fout_index>>rec){
    stream<<rec;
    getline(stream,key,'|');
    getline(stream,value,'\n');
    if(stoi(key) == usn){
      fout_index.close();
      stream.clear();//enusure to clear the buffer
      return stoi(value);//return the byte offset
    }
    stream.clear();
  }
  fout_index.close();
  stream.clear();
  return -1;//not match found
}

void delete_record(){
  cout<<"Enter usn of the record you want to delete ?";
  int usn;
  cin>>usn;
  int byte_offset = search_handler(usn);
  if(byte_offset < 0){
    cerr<<setw(50)<<"Record Not Found!";
    return;
  }

  delete_handler(usn);
  update_index(usn);
  cout<<setw(50)<<"Done Reord deleted!";
}

void delete_handler(int usn){
  fstream fout_data("recordd.dat",fstream::in|fstream::out|fstream::binary);
  fstream fout_data1("recordd1.dat",fstream::out|fstream::binary);
  std::vector<string> record_list{};
  string buffer;
  while(getline(fout_data,buffer,'#')){
    int pos = buffer.find_first_of('|');
    if(to_string(usn) == buffer.substr(0,pos)){
      continue;
    }
    record_list.push_back(buffer);
  }
  for(auto& item: record_list){
    fout_data1<<item<<'#';
  }
  fout_data.close();
  fout_data1.close();
  remove("recordd.dat");
  rename("recordd1.dat","recordd.dat");
}

void update_index(int usn){
  fstream fout_index("indexx.dat",fstream::in|fstream::out|fstream::binary);
  fstream fout_index1("indexx1.dat",fstream::out|fstream::binary);
  string buffer,key,value;
  std::map<int, string> index_list;
  stringstream stream;
  while(getline(fout_index,buffer,'\n')){
    int pos = buffer.find_first_of('|');
    if(to_string(usn) == buffer.substr(0,pos)){
      continue;
    }
    stream<<buffer;
    getline(stream,key,'|');
    getline(stream,value,'\n');
    index_list[stoi(key)] = value;
    stream.clear();stream.str("");
  }

  for(auto& item: index_list){
    fout_index1<<item.first<<'|'<<item.second<<endl;
  }
  fout_index.close();
  fout_index1.close();
  remove("indexx.dat");
  rename("indexx1.dat","indexx.dat");
}
