#include<vector>
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdio>
using namespace std;
const int hash_size = 1000;//we make it big to avoid collison
vector<string> hash_table{};
class Student{
public:
  string key,name,sem;
};
void store_record();
size_t get_hash(string);
void retrieve_record();
bool check_collision(size_t);
void printHeader();
int main(){
  hash_table.resize(1000);//we set the hash table high to avoid collision
  cout<<setw(70)<<"\nPrograms to implement hashing with collision resolution\n";
  int your_choice;
  while(1){
    cout<<"\n 1: store records\n 2: retrieve records\n 3: exit\n";
    cin>>your_choice;
    switch (your_choice){
      case 1:
      store_record();
      break;
      case 2:
      retrieve_record();
      break;
      case 3:
        remove("pro11.dat");
      exit(0);
    }
  }
}
void store_record(){
  fstream fout("pro11.dat",fstream::out|fstream::app);
  Student student;
  cout<<"Enter your key ?";cin>>student.key;
  cout<<"Enter your name ?";cin>>student.name;
  cout<<"Enter sem ?";cin>>student.sem;
  string buffer = student.key +"|"+student.name+"|"+student.sem;
  fout<<buffer<<endl;
  size_t hash_value =  get_hash(student.key);
  //////////////////
  cout<<"1 is "<<hash_value<<endl;
  bool is_collision =  check_collision(hash_value);
  if(is_collision == false){
    hash_table.at(hash_value) = buffer;
  }else{
    for(int i= hash_table.size()-1;i >=0; i--){
      if(not hash_table.at(i).empty()){
        ///put the name of collision here
        hash_table.at(i) = buffer;
      }
    }
  }
  cout<<setw(40)<<"Done record has been Hashed!\n";
  fout.close();
}
size_t get_hash(string key){
  size_t buffer = 0;
  for(int i {0}; i < key.size(); i++){
    buffer +=key.at(i);
  }
  return (buffer % 997);
}

void retrieve_record(){
  cout<<"Enter the key of record to retrieve ?";
  string key;
  cin>>key;
  size_t hash_value = get_hash(key);
  ////////////////////////
  cout<<"2 is "<<hash_value<<endl;
  if(hash_table.at(hash_value).empty()){
    cout<<"Record not found in hash table!";
    return;
  }
  string record = hash_table.at(hash_value);
  printHeader();
  stringstream stream;
  stream<<record;
  string temp;
  while(getline(stream,temp,'|')){
    cout<<setw(20)<<temp;
  }
  stream.clear();stream.str("");

}

bool check_collision(size_t hash_value){
  if(hash_table.at(hash_value).empty()){
    return false;
  }
  return true;
}

void printHeader(){
  cout<<setw(20)<<"key"<<setw(20)<<"Name"<<setw(20)<<"semester"<<setw(20)<<endl;
  cout<<"--------------------------------------------------------------------------------\n";
}
