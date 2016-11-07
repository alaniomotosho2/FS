#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
using namespace std;
class Re{
	public:
	char ar1[25];
	char ar2[25];
};

int main()
{
string in, an;
fstream fout("sch.dat",fstream::in|fstream::binary);
Re re;
fout.read(reinterpret_cast<char*>(&re),sizeof(Re));
cout<<re.ar1<<"\t"<<re.ar2<<endl;
/*
for(int i =0; i <3; i++)
{
cout<<"Enter name :?";
cin>>in;
in.copy(re.ar1,0,7);
cout<<"Enter age?";
cin>>an;
an.copy(re.ar2,0,7);
fout.write(reinterpret_cast<char*>(&re),sizeof(Re));
}*/
return 0;
}

