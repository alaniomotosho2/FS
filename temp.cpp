#include <limits>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
char name[10],age[10];
cin.getline(name,10,'\n');
cin.clear();
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
cin.getline(age,10,'\n');
cout<<name<<"\t"<<age;
}
