#pragma once
#include <string>

using namespace std;

class Build
{
	string address;
	double price;
	string Phone;
	string ID;

		
	public:

		Build();

		Build(string direccion, double precio, string phone, string id);

		string GetAddress();
	
		double GetPrice();

		void SetPrice(double precio);

		string GetID();



		void SetID(string ID);

		void SetDireccion(string direccion);

};

