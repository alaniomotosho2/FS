#include <exception>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <map>
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
void printRecord(vector<string>&);
void unpack(vector<string>&);
void search();
int search_handler(string);
void update_index(int);
void delete_record();
void delete_handler(int);
int main()
{
  cout<<setw(120)<<"index on a Secondary key implementing add(),display(),search() and delete()\n\n";
  int yourChoice;
  while(1){
    cout<<"\nO:exit\n 1: Add Record(s)\n 2:Display Records"<<"\n 3:search Records\n 4:Delete Records ";
     cout<<"\n\n Enter your choice:? "; cin>>yourChoice;
     switch(yourChoice){
       case 1: add();break;
       case 2: displayFile();break;
       case 3: search();break;
       case 4: delete_record();break;
       //case 4: student.search(); break;
       case 0: exit(0);
     }
  }
  return 0;
}

void add(){
  Record re;
  string record;
  fstream fout_data("dataFile.dat",fstream::out|fstream::app|fstream::binary);
  fstream fout_index("indexFile.dat",fstream::out|fstream::app|fstream::app|fstream::binary);
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
  fout_data<<buffer_data;
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
  fout_index<<re.myName<<'|'<<re.myUSN<<'|'<<to_string(byte_offset)<<endl;
  //cout<<buffer_data.size()<<" Tell == "<<fout_data.tellp()<<endl;
  fout_data.close();
  fout_index.close();
  sort_usn();
  cout<<setw(50)<<"Done Record Added!";
}

void sort_usn(){
  fstream fout_index("indexFile.dat",fstream::in|fstream::binary);
  fstream fout_temp("temp_file.dat",fstream::out|fstream::binary);
  vector<string> key{};
  vector<string> ref{};
  multimap<string,string> index_file;
  string record;
  string keykey; string refref;
  while(fout_index>>record){
    int pos = record.find_first_of('|');
    refref = record.substr(pos+1);
    key.push_back(record.substr(0,pos));
    ref.push_back(refref);
  }
  fout_index.close();
  for(int i{0};i < key.size(); i++){
    index_file.insert(make_pair(key.at(i),ref.at(i)));
  }

  for(auto& key: index_file){
    int pos = key.second.find_first_of('|');
    fout_temp<<key.first<<'|'<<key.second.substr(0,pos)<<'|'<<key.second.substr(pos+1)<<endl;
  }
  rename("temp_file.dat","indexFile.dat");
  fout_temp.close();

}

void displayFile(){
  fstream fout_data("dataFile.dat",fstream::in);
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
  cout<<"Enter The Name you want to search ?";
  string name;
  cin>>name;
  int byte_offset = search_handler(name);
  if(byte_offset < 0 ){
    cerr<<setw(50)<<"No Match Found!";
    return;
  }
fstream fout_data("dataFile.dat",fstream::in);
fout_data.seekg(byte_offset,fstream::beg);
string rec;
getline(fout_data,rec,'#');
std::vector<string> record;
record.push_back(rec);
unpack(record);
printHeader();
printRecord(record);
fout_data.close();
}

int search_handler(string name){
  fstream fout_index("indexFile.dat",fstream::in);
  multimap<string,string> search_result;
  string key,value, rec;
  int counter =0;
  while(fout_index>>rec){
    int pos = rec.find_first_of('|');
    key = rec.substr(0,pos);
    if(key == name){
      search_result.insert(make_pair(key,rec.substr(pos+1)));
      counter +=1;//remove this and use count from algorithm
    }
  }
  fout_index.close();
  if(counter  == 1){
    string temp = search_result.find(name)->second;
    temp = temp.substr(temp.find('|')+1);
    return stoi(temp);
  }
  if(counter > 1){
    cout<<setw(50)<<"Search Return More Than One result for the Given Key!\n";
    cout<<"Enter The USN of the Name ?";
    int usn;
    cin>>usn;
    for(multimap<string,string>::iterator it=  search_result.begin(); it != search_result.end(); ++it){
      int pos = it->second.find_first_of('|');
      string temp = it->second.substr(0,pos);
      if(to_string(usn) == temp){
        return stoi(it->second.substr(pos+1));
      }
    }
  }
  return -1;//not match found
}
void delete_record(){
  cout<<"Enter name of the record you want to delete ?";
  string name;
  cin>>name;
  int byte_offset = search_handler(name);
  if(byte_offset < 0){
    cerr<<setw(50)<<"Record Not Found!";
    return;
  }

  delete_handler(byte_offset);
  update_index(byte_offset);////////////////////////////////////
  cout<<setw(50)<<"Done Reord deleted!";
}
////////////////////we are thinking of global
void delete_handler(int byte_offset){
  fstream fout_data("dataFile.dat",fstream::in|fstream::out|fstream::binary);
  fstream fout_data1("temp.dat",fstream::out|fstream::binary);
  fout_data.seekg(byte_offset,fstream::beg);
  string deleted_record;
  getline(fout_data,deleted_record,'#');
  std::vector<string> record_list{};
  fout_data.seekg(0);//reset....always use i parameter
  string buffer;
  while(getline(fout_data,buffer,'#')){
    //int pos = buffer.find_first_of('|');
    if(deleted_record == buffer){
      continue;
    }else{
      record_list.push_back(buffer);
    }
  }
  for(auto& item: record_list){
    fout_data1<<item<<'#';
  }
  fout_data.close();
  fout_data1.close();
  rename("temp.dat","dataFile.dat");
}

void update_index(int byte_offset){
  fstream fout_index("indexFile.dat",fstream::in|fstream::out|fstream::binary);
  fstream fout_index1("temp.dat",fstream::out|fstream::binary);
  vector<string> index_holder{};
  string deleted_index,buffer;
while(fout_index>> buffer){
  string index_rcd = buffer.substr(buffer.find_last_of('|')+1);
  if(index_rcd == to_string(byte_offset))continue;
  index_holder.push_back(buffer);
}
  for(auto& item: index_holder){
    fout_index1<<item<<endl;
  }
  fout_index1.close();
  fout_index.close();
  rename("temp.dat","indexFile.dat");
}
