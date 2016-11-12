#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <cstring>
#include <sstream>
#include <array>
#include <map>
using namespace std;
class Re{
	public:
	string name;
};

int main()
{
map<int,string> m;
m[1] = "mustapha";
m[2] = "Serifat";
m[3] = "Chidinma";
for(auto& i : m){
cout<<i.first<<":"<<i.second<<endl;
m.erase(1);
}
for(auto & r: m)
{
cout<<r.first<<":"<<r.second<<endl;
}
return 0;
}

