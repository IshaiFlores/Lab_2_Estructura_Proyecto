#pragma once
#include "Build.h"

using namespace std;

class House: public Build
{
	string Zone;


	public:

	House();

	House(string address, double precio, string phone, string id, string zona);

	string GetZone();
};

