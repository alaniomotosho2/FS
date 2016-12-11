#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdio>
using namespace std;
class Student{
public:
  string record;//
  Student* next;//next link to another record in case of overflow
};
const int hash_size = 102;//we make it big to avoid collison
vector<Student*> hash_table;//vector of type Student*
void store_record();
size_t get_hash(string);//function to get home address of a key/record
void retrieve_record();
bool check_collision(size_t);//check for collison
void printValue(string);//print record
void printHeader();
bool is_hash_full();
int main(){
  hash_table.resize(hash_size);//hash table has 102 address space
  cout<<setw(70)<<"\nPrograms to implement hashing with collision resolution\n";
  cout<<setw(70)<<"\nusing chained with a separate overflow area\n";
  int your_choice;
  while(1){
    cout<<"\n1: store records ? \n2: retrieve records ? \n3: exit ?";
    cin>>your_choice;
    switch (your_choice){
      case 1:
      store_record();
      break;
      case 2:
      retrieve_record();
      break;
      case 3:
        remove("pro11.dat");//delete the file
      exit(0);
    }
  }
}
void store_record(){
  fstream fout("pro11.dat",fstream::out|fstream::app);//this not neccsary only for devuging purpose
  string key,name,sem;
  Student* student = new Student();//dynamic allocation of memory
  cout<<"Enter your key ?";cin>>key;
  cout<<"Enter your name ?";cin>>name;
  cout<<"Enter sem ?";cin>>sem;
  student->next = NULL;//set next to null since it is pointing to nothing at the moment
  student->record = key +"|"+name+"|"+sem;//packed record
  fout<<student->record<<endl;
  //hash value is size_t because we dont signed value
  size_t hash_value =  get_hash(key);//get the home address of the record
  bool is_collision =  check_collision(hash_value);//check if there is collsion
  if(is_hash_full()){
    //no available slot has is filled up
    cout<<setw(30)<<"hash table is filled up!\n";
    return;
  }
  if(is_collision == false){//no collsion store in its home address
    hash_table.at(hash_value) = student;//no collsion
    cout<<endl;
    cout<<setw(40)<<"\nrecord srored in its home address!\n";
  }else{//collision we link overflow area to its home address
    cout<<endl;
    cout<<setw(30)<<"there is collision! we use chained with a separate overflow area! technique\n";
    student->next = hash_table.at(hash_value);//create a block of memory at its home address and link
    hash_table.at(hash_value) = student;
    cout<<setw(40)<<"\nrecord linked to its home address!\n";
  }
  fout.close();
}
size_t get_hash(string key){
  size_t buffer = 0;
  for(int i {0}; i < key.size(); i++){
    buffer +=key.at(i);//get the asscii value of all the character in the key
  }
  return (buffer % 101);//use prime number to minimize collison
}

void retrieve_record(){
  cout<<"Enter the key of record to retrieve ?";
  string key;
  cin>>key;
  string record;
  size_t hash_value = get_hash(key);
  if(hash_table.at(hash_value)->next == NULL){//no collison print the record at the home address
    printValue(hash_table.at(hash_value)->record);
    return;
  }
  if(hash_table.at(hash_value)->next != NULL){//there is chained overflow area
    Student * ptr;
    ptr = hash_table.at(hash_value);
    while(ptr){
      if(key == ptr->record.substr(0,ptr->record.find_first_of('|'))){
        printValue(ptr->record);
        return;
      }
      ptr = ptr->next;//check the next link if any
    }
  }
    cout<<setw(30)<<"Key not found in hash table!";
  }

void printValue(string record){
  //string record = hash_table.at(hash_value);
  printHeader();
  stringstream stream;
  stream<<record;
  string temp;
  while(getline(stream,temp,'|')){
    cout<<setw(20)<<temp;
  }
  stream.clear();stream.str("");
}

//check for collsion
bool check_collision(size_t hash_value){
  if(!hash_table.at(hash_value)){
    return false;
  }
  return true;
}

void printHeader(){
  cout<<setw(20)<<"key"<<setw(20)<<"Name"<<setw(20)<<"semester"<<setw(20)<<endl;
  cout<<"--------------------------------------------------------------------------------\n";
}

bool is_hash_full(){
  for(int i{0}; i < hash_table.size(); i++){
    if(!hash_table.at(i))return false;//there are still empty slot
  }
  return true;//hash table is filled up;
}
