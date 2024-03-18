#pragma once
#include "Sector.h"
#include <vector>
#include <list>
#include "Search.h"
#include <functional>


class Logica
{
	
	

	public:

		typedef function<void (Search Build, Sector Builds, list<Recomendation> &Results)> Filter;

		list<string> Results(vector<Sector> Map, Search Building, Filter filtro);

		void Filtrado(Search Build, Sector Builds, list<Recomendation> &Recomendaciones);


		bool Cumple(Search Build, Apartment filtro);

		bool Cumple(Search Build, House filtro);

		bool Cumple(Search Build, Premises filtro);


		bool SortBudget(Recomendation  A, Recomendation B);


		void OrdenarRecomendaciones(std::list<Recomendation>& recomendaciones);

		void OrdenarID(std::list<Recomendation>& recomendaciones, list<string>& ID);

};

