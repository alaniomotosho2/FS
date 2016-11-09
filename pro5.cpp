#include <exception>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;

class Record{
public:
  //i made branch 15 from 5
  char myAge[5] ,myUSN[20],myName[20],myBranch[15],mySem[2];
};
size_t getIndex_Count();
size_t index_count =0;//this shouldnt be global
void printHeader();
void add();
void search();
void displayFile();
void printRecord(int);
void delete_record();
void search_handler(int&,string);
void arrange_index(string&, int&);
int main()
{
  int yourChoice;
  cout<<setw(120)<<"\n\nSimple index on a primary key implementing add(),display(),search() and delete()\n\n";
  try{
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
  }catch(...){
    cerr<<setw(50)<<"unhandled Exception!";
    exit(0);
  }
  return 0;
}

void add(){
  //we implment index counter for subsequent count
  Record re;
  string record;
  fstream fout_data("record.dat",fstream::out|fstream::app|fstream::binary);
  fstream fout_data_b("record_b.dat",fstream::out|fstream::app);
  fstream fout_index("index.dat",fstream::out|fstream::app);
  index_count = getIndex_Count();
  if(!fout_data | !fout_index){
    cerr<<setw(50)<<"File Could not be opened!";
    exit(0);
  }
  string inp;
  cout<<"\nEnter student USN :? ";
  cin>>inp;inp.copy(re.myUSN,inp.size());re.myUSN[inp.size()] = '\0';
  cout<<"\nEnter student Name:? ";cin>>inp;inp.copy(re.myName,inp.size());re.myName[inp.size()] = '\0';
  cout<<"\nEnter student Age:? ";cin>>inp;inp.copy(re.myAge,inp.size());re.myAge[inp.size()] = '\0';
  cout<<"\nEnter student Semester:? ";cin>>inp;inp.copy(re.mySem,inp.size());re.mySem[inp.size()] = '\0';
  cout<<"\nEnter student Branch:? ";cin>>inp;inp.copy(re.myBranch,inp.size());re.myBranch[inp.size()] = '\0';
  index_count +=1;
  string buffer_data = to_string(index_count)+"|"+string(re.myUSN)+"|"+string(re.myName)+"|"+string(re.myAge)+"|"+string(re.mySem)+"|"+string(re.myBranch);
  string buffer_index = string(re.myUSN)+"|"+to_string(index_count);
  fout_data.write(reinterpret_cast<char*>(&re),sizeof(Record));
  fout_data_b<<record;
  fout_index<<buffer_index<<endl;
  cout<<setw(50)<<"Done Record Added!";
  fout_data.close();
  fout_data_b.close();
  fout_index.close();
}

size_t getIndex_Count(){
  fstream fin_index("index.dat",fstream::in);

  fin_index.seekg(0,fstream::end);//check for empty file
  int len = fin_index.tellg();
  if(len == 0 | len == 1){
    fin_index.close();
    return 0;
  }
  fin_index.seekg(0,fstream::beg);//return the pointer else it will always return 0 whih is wrong
  if(not fin_index){
    cerr<<setw(50)<<"Index could not be opened!";
    exit(0);
  }
  size_t counter = 0;//without initialization the output is undefined
  string key;
  while(fin_index>>key){
    counter+=1;
  }
  fin_index.close();
  return counter;
}

void printHeader(){
  cout<<setw(15)<<"USN"<<setw(15)<<"NAME"<<setw(15)<<"AGE"<<setw(15)<<"SEMESTER"<<setw(15)<<"BRANCH"<<endl;
  cout<<"-------------------------------------------------------------------------------\n";
}

void displayFile(){
  printHeader();
  fstream fin("record.dat",fstream::in);
  if(not fin){
    cerr<<"File could not be opened!";
    exit(0);
  }
  Record re;
  while(fin.read(reinterpret_cast<char*>(&re),sizeof(Record))){
    cout<<setw(15)<<re.myUSN<<setw(15)<<re.myName<<setw(15)<<re.myAge<<setw(15)<<re.mySem<<setw(15)<<re.myBranch<<endl;
  }
}

void search(){
  cout<<setw(50)<<"\nEnter The usn of the record to search ?";
  string usn;
  string record;
  int index_loc{-1};
  cin>>usn;
  search_handler(index_loc,usn);
  if(not (index_loc+1)){//index location is actually fot calcalating record address
    cout<<setw(50)<<"Usn you entered does not match any record!";
    return;
  }
  printRecord(index_loc);
}

void printRecord(int index_loc){
  Record record;
  fstream fout_data("record.dat",fstream::in|fstream::binary);
  printHeader();
  fout_data.seekg(index_loc*(sizeof(Record)));
  fout_data.read(reinterpret_cast<char*>(&record),sizeof(Record));
  cout<<setw(15)<<record.myUSN<<setw(15)<<record.myName<<setw(15)<<record.myAge<<setw(15)<<record.mySem<<setw(15)<<record.myBranch<<endl;
}

void delete_record(){
  Record record;
  cout<<"\nEnter The usn of record to be deleted ?";
  string usn;
  cin>>usn;
  //int usn_int = stoi(usn);
  int index_loc {-1};
  search_handler(index_loc,usn);
  if(not (index_loc+1)){
    cout<<setw(50)<<"Usn you entered does not match any record!";
    return;
  }
  int counter {1};
  int index_counter {1};
  fstream fin_data("record.dat",fstream::in);
  fstream fout_temp("record_temp.dat",fstream::out|fstream::binary);
  fstream fin_index("index.dat",fstream::out);
  while(fin_data.read(reinterpret_cast<char*>(&record),sizeof(Record))){
    if( record.myUSN != usn){
      fout_temp.write(reinterpret_cast<char*>(&record),sizeof(Record));
      fin_index<<record.myUSN<<"|"<<index_counter<<endl;
      index_counter +=1;//this wont need rearrange again
    }
  }
  fin_data.close();
  std::remove("record.dat");
  std::rename("record_temp.dat","record.dat");
  cout<<setw(50)<<"Record deleted!";
}

void search_handler(int& index_loc,string usn){
  fstream fin_index("index.dat",fstream::in);
  string temp;
  string record;
  stringstream tokenizer;
  while(fin_index>>record){
    index_loc +=1;
    tokenizer<<record;
    getline(tokenizer,temp,'|');
    if (temp == usn){
      fin_index.close();
      return;
    }else{
      tokenizer.clear();tokenizer.str("");
      continue;
    }
  }
  fin_index.close();
  index_loc = -1;
}

void arrange_index(string& str,int& index){
  stringstream buffer;
  string temp;
  buffer<<str;
  vector<string> list {};
  while(getline(buffer,temp,'|')){
    list.push_back(temp);
  }
  list.at(1) = index;//update the index by re arragning it
  str = list.at(0)+"|"+list.at(1);
}
