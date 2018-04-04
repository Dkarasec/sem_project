#include <cstdio>
#include <fstream>
#include <iostream>
#include <set>
#include "operator.h"

vector<Operator> grammatic;
set<string> matr[100][100];

bool Find( Operator tmp )
{
	for (int i = 0; i < grammatic.size(); i++)
		if( grammatic[i] == tmp)
			return true;
	return false;
}

 void Addlinkoper( int number, string s )
 {
	int cnt = 0, i;
	for(i = 0; i < s.size() - 1; i++)
	{
		if (s[i] == '\\' && s[i + 1] == '(')
			cnt++;
		if (cnt == number)
			break;
	}
	if (cnt != number)
		cerr << "invalid operator";
	else
	{
		string a = '\\' + to_string(number);
		string b;
		i += 2;
		while (s[i] != '\\' || s[i + 1] != ')')
			b += s[i++];
		Operator tmp(a, b);
		if (!Find(tmp))
			grammatic.push_back(tmp);
	}
 }

void BuildGrammatic( string s )
{
	vector<bool> flags;
	Operator empty("\n", "");
	grammatic.push_back(empty);
	Operator start("S", s);
	grammatic.push_back(start);
	for(int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\\') 
		{
			if (i + 1 == s.size())
				cerr << "error";
			if (s[i + 1] >= 48 && s[i + 1] < 58)
			{
				int number = 0;
				while (s[i + 1] >= 48 && s[i + 1] < 58)
				{
					i++;
					number *= 10;
					number += s[i] - 48;
				}
				//i--;
				Addlinkoper(number, s);
			}
			else
			{
				switch(s[i + 1])
				{
				case '*':
				{
					string name = "\\*"; 
					
					if (i > 3 && s[i - 2] == '\\' && s[i - 1] == ')')
					{
						int j = i - 3;
						string b, c;
						c += "\\(";
						while (s[j - 1] != '\\' || s[j] != '(')
							b += s[j--];
						for (int k = 1; k <= b.size(); k++)
							c.push_back(b[b.size() - k]);
						c += "\\)";
						string d = c;
						d += "\\*";
						d += c;
						string e = "\n";
						name += c;
						Operator tmp(name, c);
						tmp.addProd(d);
						tmp.addProd(e);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					else
					{
						name += (s[i - 1]);
						string a;
						a += s[i - 1];
						string b;
						b += (s[i - 1]);
						b += "\\*";
						b += (s[i - 1]);
						string c = "\n";
						Operator tmp(name, a);
						tmp.addProd(b);
						tmp.addProd(c);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					break;
				}
				case '+':
				{
					string name = "\\+";
					name += s[i - 1];
					if (i > 3 && s[i - 2] == '\\' && s[i - 1] == ')')
					{
						int j = i - 3;
						string b, c;
							c += "\\(";
						while (s[j - 1] != '\\' || s[j] != '(')
							b += s[j--];
						for (int k = 1; k <= b.size(); k++)
							c.push_back(b[b.size() - k]);
							c += "\\)";
						string d = c;
						d += "\\+";
						d += c;
						name += c;
						Operator tmp(name, c);
						tmp.addProd(d);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					else
					{
						string a;
						a += s[i - 1];
						string b;
						b += s[i - 1];
						b += "\\+";
						b += s[i - 1];
						Operator tmp(name, a);
						tmp.addProd(b);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					break;
				}
				case '?':
				{
					string name = "\\?"; 
					name += s[i - 1];
					if (i > 3 && s[i - 2] == '\\' && s[i - 1] == ')')
					{
						int j = i - 3;
						string b, c;
							c += "\\(";
						while (s[j - 1] != '\\' || s[j] != '(')
							b += s[j--];
						for (int k = 1; k <= b.size(); k++)
							c.push_back(b[b.size() - k]);
							c += "\\)";
						string e = "\n";
						name += c;
						Operator tmp(name, c);
						tmp.addProd(e);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					else
					{
						string a; 
						a += s[i - 1];
						string c = "\n";
						Operator tmp(name, a);
						tmp.addProd(c);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					break;
				}
				case '|':
				{
					string name;
					//name += s[i - 1];
	/*				if (i > 3 && s[i - 2] == '/' && s[i - 1] == ')')
					{
						int j = i;
						string b, c;
						while (s[j] != '\\' || s[j + 1] != '(')
							b += s[j--];
						for (int k = 0; k < b.size(); k++)
							c.push_back(b[b.size() - k + 1]);
						Operator tmp(name, c);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					else*/
						int j;
						if (i == 0)
							j = 0;
						else
							j = i - 1;
						string b, c;
						int cnt = 0;
						while ( j >= 0 && (j == 0 || s[j - 1] != '\\' || s[j] != '|' || cnt > 0))
						{
							if (j > 0 && (s[j - 1] == '\\' && s[j] == ')'))
								cnt++;
							if (j > 0 && (s[j - 1] == '\\' && s[j] == '('))
							{
								if (cnt == 0)
									break;
								cnt--;
							}
							b += s[j--];
						}
						for (int k = 1; k <= b.size(); k++)
							c.push_back(b[b.size() - k]);
						if (c == "")
							c = "\n";
						name += c;
						name +=  "\\|";
				/*	if (i < s.size() - 3 && s[i + 2] == '/' && s[i + 3] == ')')
					{
						int j = i;
						string b;
						while (s[j] != '\\' || s[j + 1] != ')')
							b += s[j++];
						Operator tmp(name, b);
						if (!Find(tmp))
							grammatic.push_back(tmp);
					}
					else	*/
						if (i == s.size() - 2)
							j = i;
						else
							j = i + 2;
						b.clear();
						cnt = 0;
						while (j < s.size() && (s[j] != '\\' || s[j + 1] != '|' || cnt > 0))
						{
							if (j < s.size() && (s[j] == '\\' && s[j + 1] == '('))
								cnt++;
							if (j < s.size() && (s[j] == '\\' && s[j + 1] == ')'))
							{
								if (cnt == 0)
									break;
								cnt--;
							}
							b += s[j++];
						}
						if (b == "")
							b = "\n";
						name += b;
						Operator tmp(name, c);
						tmp.addProd(b);
			      if (!Find(tmp))
						grammatic.push_back(tmp);
					break;
				}
				case '\\':
				{
					string name = "\\";
					Operator tmp(name, name);
					if (!Find(tmp))
						grammatic.push_back(tmp);
					break;
				}
				case '(':
					break;
				case ')':
					break;
				default:
					cerr << "error";
				}
				i++;
			}
		}
		else
		{
			string name;
			name += s[i];
			Operator tmp(name, name);
			if (Find(tmp) == false)
				grammatic.push_back(tmp);
		}
	}
}

int CountnonTerm( string s )
{
	int cnt = 0;
	for (int i = 0; i < s.size(); i++)
		if (s[i] == '/')
			cnt++;
	return cnt;
}

Operator Fbyname( string s )
{
	for (int i = 0; i < grammatic.size(); i++)
	{
		if (grammatic[i].name == s)
			return grammatic[i];
	}
	
}

void ChangetoHom( void )
{
	bool f = true;
	while (f)
	{
		f = false;
	for (int i = 0; i < grammatic.size(); i++)
		for(int j = 0; j < grammatic[i].productions.size(); j++)
		{
			for (int k = 0; k < grammatic[i].productions[j].size(); k++)
			if (grammatic[i].productions[j][k] == '\\' && grammatic[i].productions[j][k + 1] == '|')
			{
				int a = 0;
				while (k < grammatic[i].productions[j].size())
				{
					/*if (k == grammatic[i].productions[j].size() - 2)
							a = k;
						else
							a = k + 2;	 */
					string b;
					int cnt = 0;
					while ( a < grammatic[i].productions[j].size() && (grammatic[i].productions[j][a] != '\\' || grammatic[i].productions[j][a + 1] != '|' || cnt > 0))
					{
						if (j < grammatic[i].productions[j].size() && (grammatic[i].productions[j][a] == '\\' && grammatic[i].productions[j][a + 1] == '('))
								cnt++;
							if (j < grammatic[i].productions[j].size() && (grammatic[i].productions[j][a] == '\\' && grammatic[i].productions[j][a + 1] == ')'))
							{
								if (cnt == 0)
									break;
								cnt--;
							}
						b += grammatic[i].productions[j][a++];
					}
					if (b == grammatic[i].productions[j])
					{
						int open, close;
						for (int t = 0; t < grammatic[i].productions[j].size(); t++)
						{
							bool flag1 = true;
							if (grammatic[i].productions[j][t] == '\\' && grammatic[i].productions[j][t + 1] == '(' && flag1)
								open = t, flag1 = false;
							if (grammatic[i].productions[j][t] == '\\' && grammatic[i].productions[j][t + 1] == ')')
								close = t;
						}
							string a, d, c;
							a = grammatic[i].productions[j].substr(0, open);
							d = grammatic[i].productions[j].substr(open + 2, close - open - 2);
							c = grammatic[i].productions[j].substr(close + 2, grammatic[i].productions[j].size() - 2);
							grammatic[i].addProd(a + d + c);
					}
					else
					{	
						if (b == "")
							b = "\n";
						grammatic[i].addProd(b);
						b.clear();
					}
						k = a;
						a += 2;
					f = true;
					}
				for( vector<string>::iterator it = grammatic[i].productions.begin(); it < grammatic[i].productions.end(); it++)
					if (*it == grammatic[i].productions[j])
					{
						grammatic[i].productions.erase(it);
						break;
					}
			}
		}	
	}
	for (int i = 0; i < grammatic.size(); i++)
		for(int j = 0; j < grammatic[i].productions.size(); j++)
		{
			string prod, stack;
			for (int k = 0; k < grammatic[i].productions[j].size(); k++)
			{
				if (grammatic[i].productions[j][k] == '\\')
				{
					if (k == grammatic[i].productions[j].size() - 1)
					{
						stack += grammatic[i].productions[j][k];
						stack += "/";
					}
						if (k == 1 || (k >= 2 && grammatic[i].productions[j][k - 2] != '\\'|| ((k >= 3 && (grammatic[i].productions[j][k - 2] == '\\' && grammatic[i].productions[j][k - 3] == '\\')))))
						{
							stack += grammatic[i].productions[j][k - 1];
							stack += "/";
						}
						prod += stack;
						stack.clear();

					if (grammatic[i].productions[j][k + 1] >= 48 && grammatic[i].productions[j][k + 1] < 58)
					{
						int number = 0;
						while (grammatic[i].productions[j][k + 1] >= 48 && grammatic[i].productions[j][k + 1] < 58)
						{
							k++;
							number *= 10;
							number += grammatic[i].productions[j][k] - 48;
						}
				//		k--;
						prod += '\\' + to_string(number) + "/";
					}
					else switch (grammatic[i].productions[j][k + 1])
					{
						{
						case '*':
							{
								if (k > 3 && grammatic[i].productions[j][k - 2] == '\\' && grammatic[i].productions[j][k - 1] == ')')
								{
									int a = k - 3;
									string b, c;
									while (grammatic[i].productions[j][a - 1] != '\\' || grammatic[i].productions[j][a] != '(')
										b += grammatic[i].productions[j][a--];
									for (int k = 1; k <= b.size(); k++)
										c.push_back(b[b.size() - k]);
									prod += "\\*" + c + "/";
								}
								else
								{
									string c;
									c += grammatic[i].productions[j][k - 1];
									prod += "\\*" + c + "/";
								}
							break;
							}
						case '+':
						{
							if (k > 3 && grammatic[i].productions[j][k - 2] == '\\' && grammatic[i].productions[j][k - 1] == ')')
							{
								int a = k - 3;
								string b, c;
								while (grammatic[i].productions[j][a - 1] != '\\' || grammatic[i].productions[j][a] != '(')
									b += grammatic[i].productions[j][a--];
								for (int k = 1; k <= b.size(); k++)
									c.push_back(b[b.size() - k]);
								prod += "\\+" + c + "/";
							}
							else
							{
								string c;
								c += grammatic[i].productions[j][k - 1];
								prod += "\\+" + c + "/";
							}
						break;
						}
						case '?':
						{
							if (k > 3 && grammatic[i].productions[j][k - 2] == '\\' && grammatic[i].productions[j][k - 1] == ')')
							{
								int a = k - 3;
								string b, c;
								while (grammatic[i].productions[j][a - 1] != '\\' || grammatic[i].productions[j][a] != '(')
									b += grammatic[i].productions[j][a--];
								for (int k = 1; k <= b.size(); k++)
									c.push_back(b[b.size() - k]);
								prod += "\\?" + c + "/";
							}
							else
							{
								string c;
								c += grammatic[i].productions[j][k - 1];
								prod += "\\?" + c + "/";
							}
							break;
						}
						case '(':
						{
							k++;
							break;
						}
						case ')':
						{
							break;
						}
							case '\\':
							{
								stack += grammatic[i].productions[j][k];
								stack += "/";
								break;
							}
						}
						k++;
					}
				}
				else
				{
					if (k > 0 && (k == 1 || grammatic[i].productions[j][k - 2] != '\\' || ((k >= 3 && (grammatic[i].productions[j][k - 2] == '\\' && grammatic[i].productions[j][k - 3] == '\\')))))
					{
						stack += grammatic[i].productions[j][k - 1];
					  stack += "/";	 /* / - разделительный символ*/
					}
					if (k == grammatic[i].productions[j].size() - 1)
					{
						stack += grammatic[i].productions[j][k];
						stack += "/";
					}

				}

			}
			prod += stack;
			grammatic[i].productions[j] = prod;
		}
	bool flag1 = true;
	while (flag1)
	{
		flag1 = false;
	for (int i = 0; i < grammatic.size(); i++)
		for(int j = 0; j < grammatic[i].productions.size(); j++)
			for (int k = 0; k < grammatic[i].productions[j].size(); k++)
			{
				if (CountnonTerm(grammatic[i].productions[j]) == 1)
				{
					if (grammatic[i].productions[j].size() != 2)
					{
						if (grammatic[i].productions[j] == grammatic[i].name + "/")
						{
							grammatic[i].productions[j].erase(grammatic[i].productions[j].begin() + j);
							flag1 = true;
						}
						else
						{
							int b;
							for (int t = 0; t < grammatic.size(); t++)
								if (grammatic[i].productions[j] == grammatic[t].name + "/")
								{
									b = t;
									break;
								}
								for (int t = 0; t < grammatic[b].productions.size(); t++)
									grammatic[i].addProd(grammatic[b].productions[t]);
								grammatic[i].productions[j].erase(grammatic[i].productions[j].begin() + j);
								flag1 = true;
						}
					}
				}
				while (CountnonTerm(grammatic[i].productions[j]) > 2)
				{
					int b1 = -1, b2 = -1;
					for (int t = 0; t < grammatic[i].productions[j].size(); t++)
						if (grammatic[i].productions[j][t] == '/')
							if (b1 == -1)
							{
								b1 = t;
							}
							else
							{
								b2 = t;
								break;
							}
							string name = grammatic[i].productions[j].substr(0, b1) + "&&" + grammatic[i].productions[j].substr(b1 + 1, b2 - b1 - 1);
							string nam = grammatic[i].productions[j].substr(0, b2 + 1);
							Operator n(name, nam);
							grammatic.push_back(n);
							grammatic[i].productions[j] = grammatic[i].productions[j].substr(0, b1) + "&&" + grammatic[i].productions[j].substr(b1 + 1, grammatic[i].productions[j].size() - b1);
							flag1 = true;
				}
			}
	}
	for (int i = 0; i < grammatic.size(); i++)
		for(int j = 0; j < grammatic[i].productions.size(); j++)
			for (int k = 0; k < grammatic[i].productions[j].size(); k++)
			{
					string f, s;
					if (grammatic[i].productions[j][k] == '/')
					{
						bool flag = false;
						f = grammatic[i].productions[j].substr(0, k);
						s = grammatic[i].productions[j].substr(k + 1, grammatic[i].productions[j].size() - k - 2);
						Operator F, S;
						if (k + 1 < grammatic[i].productions[j].size())
						{
							F = Fbyname(f);
							for (int t = 0; t < F.productions.size(); t++)
								if (F.productions[t] == "\n/")
								{
									s += "/";
									grammatic[i].addProd(s);
									s = s.substr(0, s.size() - 1);
									flag = true;
								}
						}
						if (k + 1 < grammatic[i].productions[j].size())
						{
							S = Fbyname(s);
							for (int t = 0; t < S.productions.size(); t++)
								if (S.productions[t] == "\n/")
								{
									f += "/";
									grammatic[i].addProd(f);
									f = f.substr(0, f.size() - 1);
									if (flag)
										grammatic[i].addProd("\n/");
								}
						}
						break;
					}
			}
	bool flag = true;
	while (flag)
	{
		flag = false;
	for (int i = 0; i < grammatic.size(); i++)
		for(int j = 0; j < grammatic[i].productions.size(); j++)
			for (int k = 0; k < grammatic[i].productions[j].size(); k++)
			{
				if (CountnonTerm(grammatic[i].productions[j]) == 1)
				{
					if (grammatic[i].productions[j].size() != 2)
					{
						if (grammatic[i].productions[j] == grammatic[i].name + "/")
						{
							grammatic[i].productions[j].erase(grammatic[i].productions[j].begin() + j);
							flag = true;
						}
						else
						{
							int b;
							for (int t = 0; t < grammatic.size(); t++)
								if (grammatic[i].productions[j] == grammatic[t].name + "/")
								{
									b = t;
									break;
								}
								for (int t = 0; t < grammatic[b].productions.size(); t++)
									grammatic[i].addProd(grammatic[b].productions[t]);
								grammatic[i].productions.erase(grammatic[i].productions.begin() + j);
								flag = true;
						}
					}
				}
				while (CountnonTerm(grammatic[i].productions[j]) > 2)
				{
					int b1 = -1, b2 = -1;
					for (int t = 0; t < grammatic[i].productions[j].size(); t++)
						if (grammatic[i].productions[j][t] == '/')
							if (b1 == -1)
							{
								b1 = t;
							}
							else
							{
								b2 = t;
								break;
							}
							string name = grammatic[i].productions[j].substr(0, b1) + "&&" + grammatic[i].productions[j].substr(b1 + 1, b2 - b1 - 1);
							string nam = grammatic[i].productions[j].substr(0, b2 + 1);
							Operator n(name, nam);
							grammatic.push_back(n);
							grammatic[i].productions[j] = grammatic[i].productions[j].substr(0, b1) + "&&" + grammatic[i].productions[j].substr(b1 + 1, grammatic[i].productions[j].size() - b1);
							flag = true;
				}
			}
	}
}

bool CYK( string s )
{
	int i, j, k, l;
		for(l = 0; l < 50 && s[l] != 0; l++)
		{
			string a;
			a += s[l];
			a += '/';
			for (int i = 0; i < grammatic.size(); i++)
					for(int j = 0; j < grammatic[i].productions.size(); j++)
					{
						if (grammatic[i].productions[j] == a)
							matr[l][l].insert(grammatic[i].name);
					}
		}
    for(j = 1; j < l; j++)
        for(i = 0; i + j < l; i++)
            for(k = i; k < i + j; k++)
            {
							for (int t = 0; t < grammatic.size(); t++)
								for(int l = 0; l < grammatic[t].productions.size(); l++)
									for (int p = 0; p < grammatic[t].productions[l].size(); p++)
									{
										string f, s;
										if (grammatic[t].productions[l][p] == '/')
										{
											f = grammatic[t].productions[l].substr(0, p);
											s = grammatic[t].productions[l].substr(p + 1, grammatic[t].productions[l].size() - p - 2);
											if(matr[i][k].count(f) > 0 && 
													matr[k + 1][i + j].count(s) > 0) 
												matr[i][i + j].insert(grammatic[t].name);
											break;
										}
								}
            }
		return	l ==0 || matr[0][l - 1].count(grammatic[1].name) > 0;
}

void main()
{
  ofstream fout("output.txt");
	ifstream fin("input.txt");
	string gram;
	fin >> gram;
	BuildGrammatic(gram);
	ChangetoHom();
	string s;
	while ((fin >> s))
	{
	 if (CYK(s))
		 fout << s << endl;
	 for(int i = 0 ; i < 100; i++)
		 for (int j = 0; j < 100 ; j++)
			 matr[i][j].clear();
	}
}
