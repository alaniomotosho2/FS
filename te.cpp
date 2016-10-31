#include <vector>
#include <iostream>
#include <string>
using namespace std;
int main()
{
vector<string> f;
vector<string> ffa;
f.push_back("man");f.push_back("woman");f.push_back("other");
ffa = f;
cout<<f.at(1);
f.at(1) = "Bulshit";
cout<<f.at(1);
for(int i =0; i <10; i++){
cout<<i;break;}
cout<<"-------------------\n";
cout<<ffa.at(0);
return 0;
}
