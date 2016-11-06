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
  string myAge;
  string myUSN;
  string myName;
  string myBranch;
  string mySem;
  void add();
  size_t getIndex_Count();
  vector<string> unpack(vector<string>&);
  void printHeader();
  vector<string> get_packed_item(fstream&);
  void search();//usm bumber as parameter
  void display_items(vector<string>&);
  //void delete();
  //void modify();
};
size_t index_count =0;
int main()
{
  Record student;
  int yourChoice;
  try{
    while(1){
      cout<<"\nO:exit\n 1: Add Record(s)\n 2:Display Records"<<"\n 3:Modify Records\n 4:search Records ";
       cout<<"\n\n Enter your choice:? "; cin>>yourChoice;
       switch(yourChoice){
         case 1: student.add();break;
         case 2: student.search();break;
         //case 3: student.delete();break;
         //case 4: student.search(); break;
         //case 0: exit(0);
       }
    }
  }catch(...){
    cerr<<setw(50)<<"unhandled Exception!";
    exit(0);
  }
  return 0;
}

void Record::add(){
  //we implment index counter for subsequent count
  fstream fout_data("record.dat",fstream::app);
  fstream fout_index("index.dat",fstream::app);
  index_count = getIndex_Count();
  if(!fout_data | !fout_index){
    cerr<<setw(50)<<"File Could not be opened!";
    exit(0);
  }
  cout<<"\nEnter student USN :? "; cin>>myUSN;
  cout<<"\nEnter student Name:? "; cin>>myName;
  cout<<"\nEnter student Age:? "; cin>>myAge;
  cout<<"\nEnter student Semester:? "; cin>>mySem;
  cout<<"\nEnter student Branch:? "; cin>>myBranch;
  index_count +=1;
  string buffer_data = to_string(index_count)+"|"+myUSN+"|"+myName+"|"+myAge+"|"+mySem+"|"+myBranch;
  string buffer_index = myUSN+"|"+to_string(index_count);
  fout_data<<buffer_data<<endl;
  fout_index<<buffer_index<<endl;
  cout<<setw(50)<<"Done Record Added!";
  fout_data.close();
  fout_index.close();
}

size_t Record::getIndex_Count(){
  fstream fin_index("index.dat",fstream::in);

  fin_index.seekg(0,fstream::end);//check for empty file
  int len = fin_index.tellg();
  if(len == 0 | len == 1){
    fin_index.close();
    return 0;
  }
  fin_index.seekg(0,fstream::beg);//return the pointer else it will always return 0 whih is wrong
  if(!fin_index){
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

void Record::search(){
  fstream fin("index.dat",fstream::in);//use index for performance
  vector<string> items;
  vector<string> packed_item {};
  vector<string> unpacked_items {};
  Record student;
  cout<<"Enter records usn you want to search :?";
  string usn;
  cin>>usn;
  if(!fin){
    cerr<<"Unable to open file";
    exit(0);//exit with success status
  }
  fin.close();
string record;
while(fin>>record){
  items.push_back(record)
}
int search_loc = find_ssn(items);
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
//start here next time
while(fin >> record){
  items.push_back(record);
  unpacked_items = unpack(items);
  if(unpacked_items.at(0) == usn){
    fin.close();
    fstream fout_data("record.dat",fstream::in);//record found
    packed_item  = get_packed_item(fout_data);
    unpacked_items = unpack(packed_item);
    display_items(unpacked_items);
    fout_data.close();
    return;//terminate the function
  }
  items.clear();//clear the container
}
cout<<setw(50)<<"Record Not Found!"<<endl;
}

vector<string> Record::unpack(vector<string>& items){
  printHeader();
  stringstream stream;
  vector <string> unpacked_items{};
  string temp;
  string string_item;
  for(auto&  item : items){
    string_item = item;
    stream<<string_item;
    //unpacking
    while(getline(stream,temp,'|')){
      unpacked_items.push_back(temp);
      //cout<<setw(15)<<temp;
    }
    unpacked_items.push_back("\n");
    stream.clear();//clear stream for the next input
    stream.str("");
    cout<<endl;
  }
  return unpacked_items;//copy unpacked to the parameter sent
}


vector<string> Record::get_packed_item(fstream& fout_data){
  std::vector<string> v{};
  string record;
  while(fout_data>>record){
    v.push_back(record);
  }
  return v;
}

void Record::display_items(vector<string>& items){
  for(auto item : items){
    cout<<setw(15)<<item;
  }
}
void Record::printHeader(){
  cout<<setw(15)<<"NAME"<<setw(15)<<"USN"<<setw(15)<<"AGE"<<setw(15)<<"SEMESTER"<<setw(15)<<"BRANCH"<<endl;
  cout<<"-------------------------------------------------------------------------------\n";
}
