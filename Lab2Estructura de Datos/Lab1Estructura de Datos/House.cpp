#include "House.h"

House::House()
{

}

House::House(string address, double precio, string phone, string id, string zona):Build(address, precio, phone, id), Zone(zona)
{

	this->Zone = zona;
}

string House::GetZone()
{
	return Zone;
}
