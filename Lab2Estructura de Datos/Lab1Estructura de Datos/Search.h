#pragma once
#include <list>
#include <string>
#include <variant>

using namespace std;

struct Search
{

	list<string> Services;

	string Type;

	double budget;

	variant<bool, string> Parameter;
	
};



struct Recomendation
{
	double budget;

	string id;

};

