#include <string>
#include <vector>

using namespace std;

struct Operator
{
	string name;
	vector<string> productions;

	Operator(){};
	Operator( string name, string first );
	void addProd( string prod );
	bool operator==( Operator tmp );
};