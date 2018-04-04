#include "operator.h"

Operator::Operator( string name, string first )
{
	this->name = name;
	//for(int i = 0; i < first.size(); i++)
	this->productions.push_back(first);
}

void Operator::addProd( string prod )
{
	//for(int i = 0; i < prod.size(); i++)
	this->productions.push_back(prod);
}

bool Operator::operator==( Operator tmp )
{
	/*if (this->productions.size() != tmp.productions.size())
		return false;
	for (int i = 0; i < this->productions.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < tmp.productions.size(); j++)
			if (this->productions[i] == tmp.productions[j])
			{
				flag = true;
				break;
			}
		if (!flag)
			return false;
	}	 */
	if (this->name == tmp.name)
		return true;
	else
		return false;
}