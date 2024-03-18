#include "Apartment.h"

Apartment::Apartment(string address, double precio, string phone, string id, bool pet) : Build(address, precio, phone, id), FriendlyPet(pet)
{
	this->FriendlyPet = pet;

}


Apartment::Apartment()
{

}

bool Apartment::GetFriendly()
{
	return FriendlyPet;
}
