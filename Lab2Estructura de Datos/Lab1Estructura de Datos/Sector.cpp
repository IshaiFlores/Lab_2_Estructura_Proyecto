#include "Sector.h"

Sector::Sector()
{
}

Sector::Sector(list<string> servicios, list<Apartment> buildA, list<House> buildB, list<Premises> buildC)
{
	this->Services = servicios;

	this->Apartaments = buildA;

	this->Houses = buildB;

	this->Premise = buildC;

}

list<Apartment> Sector::GetApartments()
{

	return Apartaments;
}

list<House> Sector::GetHouses()
{
	return Houses;
}

list<Premises> Sector::GetPremises()
{
	return Premise;
}






