#include "Premises.h"

Premises::Premises()
{
}

Premises::Premises(string address, double precio, string phone, string id, list<string> actividades): Build(address, precio, phone, id), Activities(actividades)
{

	this->Activities = actividades;

}

list<string> Premises::GetActivites()
{
	return Activities;
}
