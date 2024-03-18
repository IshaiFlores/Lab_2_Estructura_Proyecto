#pragma once
#include "Build.h"
#include <string>
#include <list>

using namespace std;


class Premises : public Build
{
	list<string> Activities;

	public:

		Premises();

		Premises(string address, double precio, string phone, string id, list<string> actividades);

		list<string> GetActivites();

};

