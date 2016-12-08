#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;
 class Student{
 public:
   string usn;
   string name;
   Student* next;
 };
 void insert();
 string pack(string,string);
 void insert_link(string,string);
 void display();
 Student* Head = NULL;
 Student student;
 int main(){
   int your_choice;
while(1){
  cout<<"\n1: insert at the rear\n2: display Record\n2: delete record\n3: exit\n";
  cout<<"Enter your choice ?";
  cin>>your_choice;
  switch (your_choice){
    case 1:
    insert();
    break;
    case 2:
    display();
    break;
  }
}
 }

 void insert(){
   fstream fout("node.dat",fstream::out);
   cout<<"Enter usn ?";cin>>student.usn;
   cout<<"Enter name ?";cin>>student.name;
   student.next = NULL;
   insert_link(student.usn,student.name);
   Student* node = Head;
   while(node){
     string buffer = pack(student.usn,student.name);
     fout<<buffer;
     node = node->next;
   }
   cout<<"Record Linked!";
 }

 string pack(string usn,string name){
   return usn+"|"+name+"->";
 }
 void insert_link(string usn, string name){
   ///////////////////////start here
   Student* stud = new Student();
   stud->usn = usn;
   stud->name = name;
   stud->next = NULL;
   if(Head == NULL){
     Head = stud;
     return;
   }
   stud->next = Head;
   Head = stud;
 }

void display(){
  Student* temp = Head;
  while(temp){
    cout<<temp->usn+'|'+temp->name+"-->";
    temp = temp->next;
  }
}
