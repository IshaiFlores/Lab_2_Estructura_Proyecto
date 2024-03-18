#pragma once
#include <string>
#include <list>
#include "Build.h"
#include "Apartment.h"
#include "House.h"
#include "Premises.h"

	
using namespace std;

class Sector
{
	list<string> Services;

	list<Apartment> Apartaments;

	list<House> Houses;

	list<Premises> Premise;


	public:

		Sector();
	
		Sector(list<string> Services, list<Apartment> BuildA, list<House> BuildB, list<Premises> BuildC);

		list<Apartment> GetApartments ();

		list<House> GetHouses ();

		list<Premises> GetPremises();

};


