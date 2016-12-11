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
 void insert();//write to file and create linked list
 string pack(Student*);//pack Student type as a string
 void insert_link(string,string);//insert packed field into linked list
 void display();//display linked list
 void delete_record();//delete a link or node from linked list
 void writeFile();//write updated linked list to file
 void insert_at_slot();//insert at empty node or link
 Student* Head = NULL;//link or node head is pointing to nothing at the beginning
 Student student;
 //program entry point
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
    exit(0);//exit with success status
  }
}
return 0;//entry point is void...we return 0
 }

 void insert(){
   fstream fout("node.dat",fstream::out);//logical file
   cout<<"Enter usn ?";cin>>student.usn;
   cout<<"Enter name ?";cin>>student.name;
   student.next = NULL;
   insert_link(student.usn,student.name);
   //link Header is always NULL at the beginning
   Student* node = Head;
   string buffer;
   //update file using content of linked list
   while(node){
     buffer = pack(node);//packed the field before writing to file
     fout<<buffer<<endl;
     node = node->next;//next link if any
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
   if(Head == NULL){//test if link is null
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
    if(st->usn == usn){//if usn to be deleted found
      st->usn = "*";//mark the record by special symbol signifying deletion
      st->name = "*";
      cout<<setw(30)<<"Record Deleted!\n";
      writeFile();//update the file
      return;
    }
    st = st->next;
  }
  cout<<setw(20)<<"record Not Found!\n";
}

void writeFile(){
  //update file with linked list
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

void insert_at_slot(){//insert into empty slot if any
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
      return;//return after insertion into empty slot
    }
    ptr = ptr->next;
  }
  //no empty slot insert at the rear
  Student * ptr1 = new Student();
  cout<<setw(30)<<"No empty slot...record will be placed at the rear\n";
  ptr1->usn = usn;ptr1->name = name;
  ptr1->next = Head;
  Head = ptr1;
  writeFile();
}
