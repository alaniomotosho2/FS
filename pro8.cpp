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
void createList();
void sort(vector<string>&);
void readFile(vector<string>&,int);
void mergeList(vector<string>&,vector<string>&,vector<string>&,vector<string>&,vector<string>&,vector<string>&,vector<string>&,vector<string>&);
int main()
{
  cout<<setw(40)<<"program to read K lists of names and merge them using K-way merge algorithm with k=8\n\n";
  vector<string>list1{};vector<string>list2{};vector<string>list3{};vector<string>list4{};
  vector<string>list5{};vector<string>list6{};vector<string>list7{};vector<string>list8{};

  createList();
  for(int i {1}; i <=8; ++i){
    switch (i){
      case 1:
      readFile(list1,1);
      sort(list1);
      break;
      case 2:
      readFile(list2,2);
      sort(list2);
      break;
      case 3:
      readFile(list3,3);
      sort(list3);
      break;
      case 4:
      readFile(list4,4);
      sort(list4);
      break;
      case 5:
      readFile(list5,5);
      sort(list5);
      break;
      case 6:
      readFile(list6,6);
      sort(list6);
      break;
      case 7:
      readFile(list7,7);
      sort(list7);
      break;
      case 8:
      readFile(list8,8);
      sort(list8);
      break;
      default:
      cout<<"Exception!";exit(0);
    }
  }
  mergeList(list1,list2,list3,list4,list5,list6,list7,list8);
  return 0;
}

void sort(vector<string>& list){
  for(int i =0; i < list.size(); i++){
    for(int j = 1; j < list.size(); j++){
      string temp;
      if(list.at(i) > list.at(j)){
        temp = list.at(i);
        list.at(i) = list.at(j);
        list.at(j) = temp;
      }
    }
  }
}

void createList(){
  int i =1;
  while( i <= 8){
    fstream fout("data"+to_string(i)+".dat",fstream::out);
    cout<<"Enter number of names to enter into file "<<i<<" ?";
    string name;
    int number;
    cin>>number;
    cout<<"Enter name one per line ?";
    cin>>name;
    fout<<name<<endl;
    for(int j =1; j < number; j++){
      cout<<"Enter name again ?";
      cin>>name;
      fout<<name<<endl;
    }
    fout.close();
    i +=1;
  }
cout<<setw(50)<<"8 File created!\n\n";
}

void readFile(vector<string>& list, int num){
  string name;
    fstream fout("data"+to_string(num)+".dat",fstream::in);
    while( fout >> name){
      list.push_back(name);
    }
}

void mergeList(vector<string>& list1, vector<string>& list2,vector<string>& list3, vector<string>& list4,vector<string>& list5,vector<string>& list6, vector<string>& list7,vector<string>& list8){
  vector<string> mergedList {};
  int i =0;
  while(!list1.empty() | !list2.empty() | !list3.empty() | !list4.empty() | !list5.empty() | !list6.empty() | !list7.empty() | !list8.empty()){
    string min;
    int i =0;
    if(!list1.empty()){
      min = list1.at(i);
    }else if(!list2.empty()){
      min = list2.at(i);
    }else if(!list3.empty()){
      min = list3.at(i);
    }else if(!list4.empty()){
      min = list4.at(i);
    }else if(!list5.empty()){
      min = list5.at(i);
    }else if(!list6.empty()){
      min = list6.at(i);
    }else if(!list7.empty()){
      min = list7.at(i);
    }else if(!list8.empty()){
      min = list8.at(i);
    }else{
      break;
    }
    if(!list1.empty() && list1.at(i) < min ) min = list1.at(i);
    if(!list2.empty() && list2.at(i) < min )min = list2.at(i);
    if(!list3.empty() && list3.at(i) < min)min = list3.at(i);
    if(!list4.empty() && list4.at(i) < min) min = list4.at(i);
    if(!list5.empty() && list5.at(i) < min) min = list5.at(i);
    if(!list6.empty() && list6.at(i) < min ) min = list6.at(i);
    if(!list7.empty() && list7.at(i) < min)min = list7.at(i);
    if(!list8.empty() && list8.at(i) < min ) min = list8.at(i);
    if(!list1.empty() && min == list1.at(i)){
      mergedList.push_back(min);
      list1.erase(list1.begin()+0);
    }
    if(!list2.empty() && min == list2.at(i) ){
      mergedList.push_back(min);
      list2.erase(list2.begin()+0);
    }
    if(!list3.empty() && min == list3.at(i) ){
      mergedList.push_back(min);
      list3.erase(list3.begin()+0);
    }
    if(!list4.empty() &&  min == list4.at(i) ){
      mergedList.push_back(min);
      list4.erase(list4.begin()+0);
    }
    if(!list5.empty() && min == list5.at(i) ){
      mergedList.push_back(min);
      list5.erase(list5.begin()+0);
    }
    if(!list6.empty() && min == list6.at(i) ){
      mergedList.push_back(min);
      list6.erase(list6.begin()+0);
    }
    if(!list7.empty() &&  min == list7.at(i) ){
      mergedList.push_back(min);
      list7.erase(list7.begin()+0);
    }
    if(!list8.empty() && min == list8.at(i) ){
      mergedList.push_back(min);
      list8.erase(list8.begin()+0);
    }
  }

  cout<<setw(30)<<"\n\nSorted Merged List are\n\n";
  cout<<"\n[";
  for(auto& item: mergedList){
    cout<<setw(25)<<item<<endl;
  }
  cout<<setw(40)<<"]\n";
}
