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
};

int main()
{
Re ra[2];
ra[0].name = "Mustapha";
ra[1].name = "Teng";
cout<<&ra[0].name<<" "<<&ra[1].name<<endl;
return 0;
}

