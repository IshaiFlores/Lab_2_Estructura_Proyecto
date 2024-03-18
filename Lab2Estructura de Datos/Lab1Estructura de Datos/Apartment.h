#pragma once
#include <string>
#include <list>
#include "Build.h"	

using namespace std;

class Apartment: public Build
{ 
	//Atributos
	bool FriendlyPet;

	public:

		//Constructor
		Apartment(string address, double precio, string phone, string id, bool pet);
			
		Apartment();

		bool GetFriendly();

};

