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
 string pack(Student*);
 void insert_link(string,string);
 void display();
 void delete_record();
 void writeFile();
 void insert_at_slot();
 Student* Head = NULL;
 Student student;
 int main(){
   int your_choice;
while(1){
  cout<<setw(30)<<"\n1: insert at the rear\n2: display Record\n3: delete record\n4: insert at an empty slot()\n5: exit\n\n";
  cout<<"Enter your choice ?";
  cin>>your_choice;
  switch (your_choice){
    case 1:
    insert();
    break;
    case 2:
    display();
    break;
    case 3:
    delete_record();
    break;
    case 4:
    insert_at_slot();
    break;
    case 5:
    exit(0);
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
   string buffer;
   while(node){
     buffer = pack(node);
     fout<<buffer<<endl;
     node = node->next;
   }
   cout<<setw(30)<<"Record added and  Linked!\n";
   fout.close();
 }

 string pack(Student* node){
   return node->usn+"|"+node->name;
 }
 void insert_link(string usn, string name){
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

void delete_record(){
  cout<<"Enter usn of record to be deleted ? ";
  string usn;
  cin>>usn;
  Student* st;
  st = Head;
  while(st){
    if(st->usn == usn){
      st->usn = "*";
      st->name = "*";
      cout<<setw(30)<<"Record Deleted!\n";
      writeFile();
      return;
    }
    st = st->next;
  }
  cout<<setw(20)<<"record Not Found!\n";
}

void writeFile(){
  remove("node.dat");
  fstream fout("node.dat",fstream::out|fstream::app);
  Student* st;
  st = Head;
  string rec;
  while(st){
    rec = pack(st);
    fout<<rec<<endl;
    st = st->next;
  }
  fout.close();
}

void insert_at_slot(){
  cout<<"Enter usn to be inserted ?";
  string usn;
  cin>>usn;
  cout<<"Enter name ?";
  string name;cin>>name;
  Student* ptr = new Student();
  ptr = Head;
  while(ptr){
    if(ptr->usn == "*"){
      ptr->usn = usn;
      ptr->name = name;
      cout<<setw(30)<<"Record Inserted at an empty location!\n";
      writeFile();
      return;
    }
    ptr = ptr->next;
  }
  Student * ptr1 = new Student();
  cout<<setw(30)<<"No empty slot...record will be placed at the rear\n";
  ptr1->usn = usn;ptr1->name = name;
  ptr1->next = Head;
  Head = ptr1;
  writeFile();
}
