#include "Logica.h"
#include <algorithm>

list<string> Logica::Results(vector<Sector> Map, Search Building, Filter filtro)
{
    list<string> resultados;

    list<Recomendation> Recomendaciones;

    auto it = Map.begin();

    while(it != Map.end())
    {
        Sector objeto = *it;
       
        filtro(Building, objeto, Recomendaciones);

        it++;
    }

    OrdenarRecomendaciones(Recomendaciones);

    OrdenarID(Recomendaciones, resultados);


    return resultados;
}

void Logica::Filtrado(Search Build, Sector sector, list<Recomendation> &Results)
{
     
     list<Recomendation> Recomendacion;
     Recomendation Nuevo;

     if(Build.Type == "Houses")
     {
         list<House> listado = sector.GetHouses();

         if (!listado.empty())
         {
             for (auto it1 = listado.begin(); it1 != listado.end(); it1++)
             {
                 if (Cumple(Build, *it1))
                 {
                     Nuevo.budget = it1->GetPrice();
                     Nuevo.id = it1->GetID();
                     Results.push_back(Nuevo);
                 }

             }
         }
     
     }else if(Build.Type == "Apartments")
     {

         list<Apartment> listadoP = sector.GetApartments();

         if (!listadoP.empty())
         {
             for (auto it2 = listadoP.begin(); it2 != listadoP.end(); it2++)
             {
                 if (Cumple(Build, *it2))
                 {

                     Nuevo.budget = it2->GetPrice();
                     Nuevo.id = it2->GetID();

                     Results.push_back(Nuevo);
                 }

             }
         }
     
     }else
     {
         list<Premises> listadoT = sector.GetPremises();

         if (!listadoT.empty()) {
             // Crear una lista temporal para almacenar los elementos que deseas agregar a Results
            

             // Iterar sobre la lista GetPremises
             for (auto it3 = listadoT.begin(); it3 != listadoT.end(); it3++) 
             {
                 if (Cumple(Build, *it3)) 
                 {
                     Nuevo.budget = it3->GetPrice();
                     Nuevo.id = it3->GetID();

                     Results.push_back(Nuevo);

                     
                 }
             }
              
         }
     
     }


    
}

bool Logica::Cumple(Search Build, Apartment filtro)
{
    if (filtro.GetPrice() <= Build.budget && filtro.GetFriendly() == std::get<bool>(Build.Parameter))
    {

        return true;
    }

    return false;

}

bool Logica::Cumple(Search Build, House filtro)
{
        if(filtro.GetPrice() <= Build.budget)
        {
            string zona = get<string>(Build.Parameter);

            if(zona == "Red")
            {
            
                return filtro.GetZone() == "Red";
            
            }else if(zona == "Orange")
            {
                
                return filtro.GetZone() == "Red" || filtro.GetZone() == "Orange";
            
            }else if(zona == "Yellow")
            {
            
                return filtro.GetZone() == "Red" || filtro.GetZone() == "Orange" || filtro.GetZone() == "Yellow";
            
            }else
            {
            
                return filtro.GetZone() == "Red" || filtro.GetZone() == "Orange" || filtro.GetZone() == "Yellow" || filtro.GetZone() == "Green";
            
            }
        }

        return false;
   
}

    bool Logica::Cumple(Search Build, Premises filtro)
    {
        if (filtro.GetPrice() <= Build.budget)
        {
            string Activity = get<string>(Build.Parameter);
            
            list<string> Actividades = filtro.GetActivites();

            if(find(Actividades.begin(), Actividades.end(),Activity) != Actividades.end())
            {
            
                return true;
                
            }
        
        }
        return false;
    }


    void Logica::OrdenarRecomendaciones(std::list<Recomendation>& recomendaciones)
    {
        vector<Recomendation> Ssort(recomendaciones.begin(), recomendaciones.end());
       
        int n = Ssort.size();

        for(int i = 0; i < n - 1; i++)
        {
            int minindex = i;
            
            for(int j = i + 1; j < n; j++)
            {
                if(Ssort[j].budget < Ssort[minindex].budget)
                {
                
                    minindex = j;
                
                }
           
            }

            Recomendation Temp = Ssort[minindex];
            Ssort[minindex] = Ssort[i];
            Ssort[i] = Temp;
        }

        recomendaciones.assign(Ssort.begin(), Ssort.end());
        
        Ssort.clear();

    }

    void Logica::OrdenarID(std::list<Recomendation>& recomendaciones, list<string>& ID)
    {
        for (auto it = recomendaciones.begin(); it != recomendaciones.end(); it++)
        {
            string id = it->id;
        
            ID.push_back(id);
        
        }

    }

    
    // Definición de la función para ordenar una lista de Recomendation
   

   

