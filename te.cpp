#include <vector>
#include <iostream>
#include <string>
using namespace std;
int main()
{
vector<string> f;
f.push_back("Man");
f.push_back("woman");
f.push_back("others#");
f.at(2) = "Nive man";
for(auto& i : f){
cout<<i<<endl;
}
return 0;
}
