#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
class Account{
public:
    Account(){}
    Account(int id=0,string name="anonymous",float number=0.0):myId(id),myName(name),myNumber(number){}
    friend ostream& operator<<(ostream& out,Account& obj);
    friend istream& operator>>(istream& in,Account& obj);
    int getId(){return myId;}
    string getName(){return myName;}
    float getNumber(){return myNumber;}
private:
    int myId;
    string myName;
    float myNumber;
};
int main(int argc, char** argv) {
    fstream fout("fas2.dat",fstream::in);
    //Account account;
    if(!fout){
        cerr<<"Error! ";
        exit(1);
    }
    int id;
    string name;
    float number;
    int num;
    //search here
    cout<<"Sera a number : ";
    cin>>num;
    //put this to separate it
    cout<<"? ";
    while(fout>>id>>name>>number){
        //fout<<account.getId()<<' '<<account.getName()<<' '<<account.getNumber()<<' '<<endl;
        //cout<<id<<setw(20)<<name<<setw(20)<<number<<endl;
        //fout<<id<<' '<<name<<' '<<number<<endl;
        //cout<<"?\n ";
        if(id == num){
            cout<<id<<setw(20)<<name<<setw(20)<<number<<endl;
        }

    }
    //cout<<account;
    return 0;
}
ostream& operator<<(ostream& out,Account& obj){
    out<<obj.myId<<setw(20)<<obj.myName<<setw(20)<<obj.myNumber<<endl;
    return out;
}
istream& operator>>(istream& in, Account& obj){
    in>>obj.myId>>obj.myName>>obj.myNumber;
    cout<<"? ";
    return in;
}
