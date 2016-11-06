#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
using namespace std;
class Re{
	public:
	string name;
	string age;
};
istream& writeFunc(istream&,Re);
int main()
{
fstream fout("rak.dat",fstream::in|fstream::binary);
Re re;

fout.seekg(2*(sizeof(Re)));
writeFunc(fout,re);

cout<<"Done";
return 0;
}

istream& writeFunc(istream& out, Re re){

out.read(reinterpret_cast<char*>(&re),sizeof(Re));
cout<<re.name<<"\t"<<re.age<<endl;
}
