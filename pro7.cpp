#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;

void writeList(int,int);
void matchList();
void getList(vector<string>&,vector<string>&);

int main()
{
  cout<<setw(70)<<"Cosequential Processing---Matching----\n\n";
  int count = 1;
  cout<<"Enter number of Names in File "<<count<<" ?";
  int number;
  cin>>number;
  writeList(number,count);
  count++;
  cout<<"Enter number of Names in File "<<count<<" ?";
  cin>>number;
  writeList(number,count);
  matchList();
  return 0;
}
void writeList(int number,int count){
  fstream fout("file"+to_string(count)+".dat",fstream::out);
  string name;
  std::vector<string> list;
  cout<<"Enter Name(s) one Per line ?";
  cin>>name;
  list.push_back(name);
  for(int i{0}; i < number-1; ++i){
    cout<<"Enter Again ?";
    cin>>name;
    list.push_back(name);
  }
  std::sort(list.begin(),list.end());
  for(auto& item : list){
    fout<<item<<endl;
  }
  fout.close();
}

void getList(vector<string>& list1,vector<string>& list2){
  fstream fout1("file1.dat",fstream::in);
  fstream fout2("file2.dat",fstream::in);
  string buffer;
  while(fout1 >> buffer){
    list1.push_back(buffer);
  }
  while (fout2 >> buffer) {
    list2.push_back(buffer);
  }
  fout1.close();fout2.close();
}
void matchList(){
  fstream fout3("ouput.dat",fstream::out);
  std::vector<string> list1{};
  std::vector<string> list2{};
  getList(list1,list2);
  int i=0;int j =0;
  cout<<setw(30)<<"The Matched Name(s) are : \n";
  while(i < list1.size() && j < list2.size()){
    if(list1.at(i) == list2.at(j)){
      cout<<setw(40)<<list1.at(i)<<endl;
      fout3<<list1.at(i)<<endl;
      i++;
      j++;
      if( i == list1.size() | j == list2.size()) break;
      continue;
    }
    if(list1.at(i) < list2.at(j)){
      i++;
      if( i == list1.size()) break;
    }
    if(list1.at(i) > list2.at(j) ){
      j++;
      if( i == list1.size()) break;
    }
  }
}
