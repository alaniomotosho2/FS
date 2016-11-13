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
multimap<int,string> da,it;
da.insert(make_pair(1,"mustapha"));
da.insert(make_pair(2,"Munir"));
da.insert(make_pair(1,"usman"));
//multimap<int,string>::iterator it;
it = da.equal_range(1);
for(multimap<int,string>::iterator i = it.first, i < it.second; i++){
cout<<i->second<<endl;
}
return 0;
}

