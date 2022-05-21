#pragma once
#include<iostream>
#include<vector>
#include <string>
using namespace std;
class graf
{
	vector<string> cities;
	int** a;
	int pos_vec(string name)
	{
		int pos = -1;
		for (int i = 0; i < cities.size(); ++i)
			if (cities[i] == name)
				pos = i;
		return pos;
	}
	bool findelem(vector<string> iwh,string myway)
	{
		bool flag = true;
		for (int i = 0; i < iwh.size() and flag; ++i)
			if (myway == iwh[i])
				flag = false;
		return flag;
	}
	int distance(vector<string> way)
	{
		int hohoho=0;
		for (int i = way.size() - 1; i > 0; --i)
			hohoho += a[pos_vec(way[i-1])][pos_vec(way[i])];
		return hohoho;
	}
	vector<string> hodmana(vector<string> iwh,string whereigo)
	{
		vector<vector<string>> ways;// пути которые ведут от данной точки до точки начала
		vector<string> way;// минимальный путь от данной точки до точки начала
		vector<string> wayotpr;
		int minway = -1;
		iwh.push_back(whereigo);//пушим посещенную вершину
		if (iwh.size() < cities.size())//если не посетили все вершины то идём дальше
		{
			for (int i = 0; i < cities.size(); ++i)
			{
				if (findelem(iwh, cities[i]) and a[pos_vec(cities[i])][pos_vec(whereigo)] > 0)//если вершины нет в векторе посещенных и путь есть то идем в неё
					ways.push_back(hodmana(iwh, cities[i]));
			}
			if (ways.size() > 0)//если пути есть то выбираем из них наименьший
			{
				for (int i = 0; i < ways.size(); ++i)
				{
					if (ways[i].size() > 0)//если путь из данной точки через точку i существует то
					{
						if (((distance(ways[i]) + a[pos_vec(ways[i][0])][pos_vec(whereigo)]) < minway) or minway == -1)//сравниваем путь путь равен всему переданному пути + путь от данной точки до точки из которой пришли(это первая точка в векторе пути) 
						{
							minway = distance(ways[i]) + a[pos_vec(ways[i][0])][pos_vec(whereigo)];
							way = ways[i];
						}
					}
					
				}
				if (way.size() > 0)//если путь есть то отправляем его
				{
					wayotpr.push_back(whereigo);
					for (int i = 0; i < way.size(); ++i)
						wayotpr.push_back(way[i]);
				}
			}
			return wayotpr;
		}
		else
		{
			if (a[pos_vec(cities[0])][pos_vec(whereigo)] > 0)//если из конечной точки есть путь в точку начала всё хорошо
			{
				way.push_back(whereigo);
				way.push_back(cities[0]);
			}
			return way;
		}
	}
public:
	graf()
	{
		a = new int*;
	}
	vector<string> get_optway()
	{
		vector<string> g;
		if (cities.size() > 0)
			return hodmana(g, cities[0]);
		else
			return g;
	}
	void show_opt_way()
	{
		vector<string> way = get_optway();
		for (int i = 0; i < way.size(); ++i)
			cout << way[i] << " ";
		cout << endl;
	}
	void add_city(string name)
	{
		cities.push_back(name);
		int** b=new int*[cities.size()];
		for (int i = 0; i < cities.size(); ++i)
			b[i] = new int[cities.size()];
		for (int i = 0; i < cities.size() - 1; ++i)
		{
			for (int j = 0; j < cities.size() - 1; ++j)
				b[i][j] = a[i][j];
		}
		for (int i = 0; i < cities.size() - 1; ++i)
			delete[] a[i];
		delete[] a;
		b[cities.size() - 1][cities.size() - 1] = -1;
		int i= cities.size() - 1;
		for (int j = 0; j < cities.size() - 1; ++j)
		{
			b[i][j] = 0;
			b[j][i] = 0;
		}
		a = b;
	}
	void add_connection(string name1, string name2, int way)
	{
		if (name1 != name2)
		{
			a[pos_vec(name1)][pos_vec(name2)] = way;
			a[pos_vec(name2)][pos_vec(name1)] = way;
		}
	}
	void add_connection(int name1, int name2, int way)
	{
		if (name1 != name2)
		{
			a[name1][name2] = way;
			a[name2][name1] = way;
		}
	}
	void add_connection_once(string name1, string name2, int way)
	{
		if (name1 != name2)
		{
			a[pos_vec(name2)][pos_vec(name1)] = way;
		}
	}
	void add_connection_once(int name1, int name2, int way)
	{
		if (name1 != name2)//add weight
		{
			a[name2][name1] = way;
		}
	}
	void print()
	{
		cout << "  ";
		for (int i = 0; i < cities.size(); ++i)
			cout << cities[i]<<"  ";
		cout << endl;
		for (int i = 0; i < cities.size(); ++i)
		{
			for (int j = -1; abs(j) < cities.size(); ++j)
			{
				if (j == -1)
					cout << cities[i] << " ";
				else
					cout << a[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	string get_name_of_city(int number)
	{
		return cities[number];
	}
	int count_of_cities()
	{
		return cities.size();
	}
	void delete_city(string name)
	{
		if (cities.size() - 1 > 0)
		{
			int x = 0, y = 0;
			int** b = new int* [cities.size() - 1];
			for (int i = 0; i < cities.size(); ++i)
			{
				if (cities[i] != name)
				{
					b[x] = new int[cities.size() - 1];
					y = 0;
					for (int j = 0; j < cities.size(); ++j)
					{
						if (cities[j] != name)
						{
							b[x][y] = a[i][j];
							++y;
						}
					}
					++x;
				}

			}
			for (int i = 0; i < cities.size(); ++i)
				delete[] a[i];
			delete[] a;
			a = b;
			vector<string> buff;
			for (int i = 0; i < cities.size(); ++i)
				if (cities[i] != name)
					buff.push_back(cities[i]);
			cities.clear();
			cities = buff;
		}
		else
		{
			int** b = new int*;
			/*cout << "AAAAAAAAA" << endl;*/
			delete[] a;
			a = b;
			cities.clear();
		}
	}
	void delete_connection(string name1, string name2)
	{
		a[pos_vec(name1)][pos_vec(name2)] = 0;
		a[pos_vec(name2)][pos_vec(name1)] = 0;
	}
	int get_connection(string name1, string name2)
	{
		return a[pos_vec(name2)][pos_vec(name1)];
	}
	int get_connection(int name1, int name2)
	{
		return a[name2][name1];
	}
	void pereimenovat_city(string last_name, string new_name)
	{
		cities[pos_vec(last_name)] = new_name;
	}
	int minway()
	{
		vector<string> iwh;
		vector<string> wty = hodmana(iwh, cities[0]);
		if (wty.size() > 1)
			return distance(wty);
		else
			return -1;
	}
};