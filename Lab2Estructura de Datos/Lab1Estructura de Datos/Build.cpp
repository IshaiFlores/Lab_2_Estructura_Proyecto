#include "Build.h"


Build::Build()
{
}

Build::Build(string direccion, double precio, string phone, string id)
{
	this->address = direccion;
	this->price = precio;
	this->Phone = phone;
	this->ID = id;
}

string Build::GetAddress()
{

	return address;

}




double Build::GetPrice()
{
	return price;
}


void Build::SetPrice(double precio)
{

	this->price = precio;

}

string Build::GetID()
{
	return ID;

}

void Build::SetID(string id)
{

	this->ID = id;

}

void Build::SetDireccion(string direccion)
{

	address = direccion;
}


