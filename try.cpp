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
#include <algorithm>
using namespace std;
class Re{
	public:
	string name;
};

int main()
{
vector<string> t {"zebra","aba","AbA","a","u"};
for(auto& item: t){
cout<<item<<endl;
}
sort(t.begin(),t.end());
cout<<"------------------------\n";
for(auto& i : t){
cout<<i<<endl;
}
return 0;
}

