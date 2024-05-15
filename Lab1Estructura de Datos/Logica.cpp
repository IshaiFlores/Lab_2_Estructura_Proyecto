#include "Logica.h"
#include <algorithm>

/**
 * @brief Obtener resultados filtrados y ordenados seg�n criterios de b�squeda y filtro
 *
 * Esta funci�n genera una lista de resultados filtrados y ordenados seg�n los criterios de b�squeda
 * y filtro especificados. Recorre los sectores del mapa y aplica el filtro sobre cada sector,
 * acumulando las recomendaciones obtenidas en una lista. Luego, ordena las recomendaciones por presupuesto
 * ascendente y extrae los IDs de las recomendaciones ordenadas, almacen�ndolos en una lista separada
 * que se devuelve como resultado final.
 *
 * @param Map Vector que contiene los sectores del mapa donde se realizar� la b�squeda.
 * @param Building Objeto de tipo Search que contiene los criterios de b�squeda.
 * @param filtro Objeto de tipo Filter que define el filtro a aplicar sobre los sectores.
 * @return Una lista de strings que contiene los IDs de las recomendaciones filtradas y ordenadas.
 */
list<string> Logica::Results(vector<Sector> Map, Search Building, Filter filtro)
{
    // Lista para almacenar los resultados finales
    list<string> resultados;

    // Lista para almacenar las recomendaciones obtenidas de los sectores
    list<Recomendation> Recomendaciones;

    // Iterador que recorre los sectores del mapa
    auto it = Map.begin();

    // Recorre cada sector del mapa
    while (it != Map.end())
    {
        // Obtiene el sector actual
        Sector objeto = *it;

        // Aplica el filtro sobre el sector actual y almacena las recomendaciones obtenidas
        filtro(Building, objeto, Recomendaciones);

        // Avanza al siguiente sector
        it++;
    }

    // Ordena las recomendaciones por presupuesto ascendente
    OrdenarRecomendaciones(Recomendaciones);

    // Extrae los IDs de las recomendaciones ordenadas y los almacena en la lista de resultados
    OrdenarID(Recomendaciones, resultados);

    // Retorna la lista de resultados que contiene los IDs de las recomendaciones filtradas y ordenadas
    return resultados;
}










/**
 * @brief Filtrado de propiedades seg�n criterios de b�squeda
 *
 * Esta funci�n filtra las propiedades disponibles en un sector espec�fico seg�n los criterios
 * de b�squeda especificados. Recorre las diferentes listas de propiedades disponibles en el
 * sector (casas, apartamentos o locales comerciales) y compara cada propiedad con los criterios
 * de b�squeda. Si una propiedad cumple con los criterios, se agrega a la lista de resultados.
 *
 * @param Build Objeto de tipo Search que contiene los criterios de b�squeda.
 * @param sector Objeto de tipo Sector que representa el �rea donde se encuentran las propiedades.
 * @param Results Lista de objetos de tipo Recomendation donde se almacenar�n los resultados filtrados.
 */
void Logica::Filtrado(Search Build, Sector sector, list<Recomendation>& Results)
{
    // Lista temporal para almacenar las recomendaciones
    list<Recomendation> Recomendacion;

    // Objeto Recomendation para almacenar cada nueva recomendaci�n
    Recomendation Nuevo;

    // Verifica el tipo de propiedad que se est� buscando
    if (Build.Type == "Houses")
    {
        // Obtiene la lista de casas del sector
        list<House> listado = sector.GetHouses();

        // Verifica si la lista de casas no est� vac�a
        if (!listado.empty())
        {
            // Itera sobre la lista de casas
            for (auto it1 = listado.begin(); it1 != listado.end(); it1++)
            {
                // Comprueba si la casa cumple con los criterios de b�squeda
                if (Cumple(Build, *it1))
                {
                    // Si cumple, se asignan los datos de la casa a un nuevo objeto Recomendation
                    Nuevo.budget = it1->GetPrice();
                    Nuevo.id = it1->GetID();

                    // Se agrega el nuevo objeto Recomendation a la lista de resultados
                    Results.push_back(Nuevo);
                }
            }
        }
    }
    else if (Build.Type == "Apartments")
    {
        // Obtiene la lista de apartamentos del sector
        list<Apartment> listadoP = sector.GetApartments();

        // Verifica si la lista de apartamentos no est� vac�a
        if (!listadoP.empty())
        {
            // Itera sobre la lista de apartamentos
            for (auto it2 = listadoP.begin(); it2 != listadoP.end(); it2++)
            {
                // Comprueba si el apartamento cumple con los criterios de b�squeda
                if (Cumple(Build, *it2))
                {
                    // Si cumple, se asignan los datos del apartamento a un nuevo objeto Recomendation
                    Nuevo.budget = it2->GetPrice();
                    Nuevo.id = it2->GetID();

                    // Se agrega el nuevo objeto Recomendation a la lista de resultados
                    Results.push_back(Nuevo);
                }
            }
        }
    }
    else
    {
        // Obtiene la lista de locales comerciales del sector
        list<Premises> listadoT = sector.GetPremises();

        // Verifica si la lista de locales comerciales no est� vac�a
        if (!listadoT.empty())
        {
            // Itera sobre la lista de locales comerciales
            for (auto it3 = listadoT.begin(); it3 != listadoT.end(); it3++)
            {
                // Comprueba si el local comercial cumple con los criterios de b�squeda
                if (Cumple(Build, *it3))
                {
                    // Si cumple, se asignan los datos del local comercial a un nuevo objeto Recomendation
                    Nuevo.budget = it3->GetPrice();
                    Nuevo.id = it3->GetID();

                    // Se agrega el nuevo objeto Recomendation a la lista de resultados
                    Results.push_back(Nuevo);
                }
            }
        }
    }
}














/**
 * @brief Verificar si un apartamento cumple con los criterios de b�squeda
 *
 * Esta funci�n verifica si un apartamento cumple con los criterios de b�squeda especificados.
 * Compara el precio del apartamento con el presupuesto especificado en la b�squeda y verifica
 * si la amigabilidad del apartamento coincide con el par�metro de b�squeda (si se proporciona).
 *
 * @param Build Objeto de tipo Search que contiene los criterios de b�squeda.
 * @param filtro Objeto de tipo Apartment que representa el apartamento a evaluar.
 * @return true si el apartamento cumple con los criterios de b�squeda, o false en caso contrario.
 */
bool Logica::Cumple(Search Build, Apartment filtro)
{
    // Verifica si el precio del apartamento es menor o igual al presupuesto especificado en la b�squeda
    // y si la amigabilidad del apartamento coincide con el par�metro de b�squeda (si se proporciona)
    if (filtro.GetPrice() <= Build.budget && filtro.GetFriendly() == std::get<bool>(Build.Parameter))
    {
        return true; // Retorna true si cumple con los criterios de b�squeda
    }
    return false; // Retorna false si no cumple con los criterios de b�squeda
}









/**
 * @brief Verificar si una casa cumple con los criterios de b�squeda
 *
 * Esta funci�n verifica si una casa cumple con los criterios de b�squeda especificados.
 * Compara el precio de la casa con el presupuesto especificado en la b�squeda y verifica
 * si la zona de la casa coincide con la zona especificada en el par�metro de b�squeda.
 *
 * @param Build Objeto de tipo Search que contiene los criterios de b�squeda.
 * @param filtro Objeto de tipo House que representa la casa a evaluar.
 * @return true si la casa cumple con los criterios de b�squeda, o false en caso contrario.
 */
bool Logica::Cumple(Search Build, House filtro)
{
    // Verifica si el precio de la casa es menor o igual al presupuesto especificado en la b�squeda
    if (filtro.GetPrice() <= Build.budget)
    {
        // Obtiene la zona especificada en el par�metro de b�squeda
        string zona = get<string>(Build.Parameter);

        // Compara la zona de la casa con la zona especificada en el par�metro de b�squeda
        if (zona == "Red")
        {
            return filtro.GetZone() == "Red";
        }
        else if (zona == "Orange")
        {
            return filtro.GetZone() == "Red" || filtro.GetZone() == "Orange";
        }
        else if (zona == "Yellow")
        {
            return filtro.GetZone() == "Red" || filtro.GetZone() == "Orange" || filtro.GetZone() == "Yellow";
        }
        else
        {
            return filtro.GetZone() == "Red" || filtro.GetZone() == "Orange" || filtro.GetZone() == "Yellow" || filtro.GetZone() == "Green";
        }
    }
    return false; // Retorna false si no cumple con los criterios de b�squeda
}





/**
 * @brief Verificar si un local comercial cumple con los criterios de b�squeda
 *
 * Esta funci�n verifica si un local comercial cumple con los criterios de b�squeda especificados.
 * Compara el precio del local comercial con el presupuesto especificado en la b�squeda y verifica
 * si la actividad del local comercial coincide con la actividad especificada en el par�metro de b�squeda.
 *
 * @param Build Objeto de tipo Search que contiene los criterios de b�squeda.
 * @param filtro Objeto de tipo Premises que representa el local comercial a evaluar.
 * @return true si el local comercial cumple con los criterios de b�squeda, o false en caso contrario.
 */
bool Logica::Cumple(Search Build, Premises filtro)
{
    // Verifica si el precio del local comercial es menor o igual al presupuesto especificado en la b�squeda
    if (filtro.GetPrice() <= Build.budget)
    {
        // Obtiene la actividad especificada en el par�metro de b�squeda
        string Activity = get<string>(Build.Parameter);

        // Obtiene la lista de actividades del local comercial
        list<string> Actividades = filtro.GetActivites();

        // Verifica si la actividad del local comercial est� en la lista de actividades especificada
        if (find(Actividades.begin(), Actividades.end(), Activity) != Actividades.end())
        {
            return true; // Retorna true si cumple con los criterios de b�squeda
        }
    }
    return false; // Retorna false si no cumple con los criterios de b�squeda
}






/**
* @brief Ordenar la lista de recomendaciones por presupuesto ascendente
*
* Esta funci�n ordena la lista de recomendaciones por presupuesto de forma ascendente.
* Utiliza el algoritmo de ordenaci�n de selecci�n para comparar los presupuestos de las recomendaciones
* y reorganizar la lista en orden ascendente.
*
* @param recomendaciones Lista de objetos de tipo Recomendation que se desea ordenar.
*/
void Logica::OrdenarRecomendaciones(std::list<Recomendation>& recomendaciones)
{
    // Convierte la lista de recomendaciones a un vector para facilitar la ordenaci�n
    vector<Recomendation> Ssort(recomendaciones.begin(), recomendaciones.end());

    // Obtiene el tama�o del vector
    int n = Ssort.size();

    // Aplica el algoritmo de ordenaci�n de selecci�n para ordenar por presupuesto ascendente
    for (int i = 0; i < n - 1; i++)
    {
        int minindex = i;

        for (int j = i + 1; j < n; j++)
        {
            // Compara los presupuestos de las recomendaciones para encontrar el m�s peque�o
            if (Ssort[j].budget < Ssort[minindex].budget)
            {
                minindex = j;
            }
        }

        // Intercambia las recomendaciones para ordenarlas
        Recomendation Temp = Ssort[minindex];
        Ssort[minindex] = Ssort[i];
        Ssort[i] = Temp;
    }

    // Asigna la lista ordenada de vuelta a la lista original de recomendaciones
    recomendaciones.assign(Ssort.begin(), Ssort.end());

    // Libera la memoria del vector temporal
    Ssort.clear();
}







/**
 * @brief Obtener una lista de IDs de las recomendaciones
 *
 * Esta funci�n recorre la lista de recomendaciones y extrae los IDs de cada recomendaci�n,
 * almacen�ndolos en una lista separada.
 *
 * @param recomendaciones Lista de objetos de tipo Recomendation de donde se extraen los IDs.
 * @param ID Lista de strings donde se almacenar�n los IDs de las recomendaciones.
 */
void Logica::OrdenarID(std::list<Recomendation>& recomendaciones, list<string>& ID)
{
    // Itera sobre la lista de recomendaciones
    for (auto it = recomendaciones.begin(); it != recomendaciones.end(); it++)
    {
        // Obtiene el ID de cada recomendaci�n y lo agrega a la lista de IDs
        string id = it->id;
        ID.push_back(id);
    }
}


    
    
   

   

