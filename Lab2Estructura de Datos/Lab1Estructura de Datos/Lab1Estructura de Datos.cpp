
#include <iostream>
#include <json/json.h>
#include <string>
#include <fstream>
#include <list>
#include "Apartment.h"
#include "House.h"
#include "Sector.h"
#include "Premises.h"
#include "Search.h"
#include "Logica.h"


using namespace std;

Logica Recomendacion;

int main()
{ 
    //Inicializaciónd de variables de ruta de archivo
    string ruta;
    bool open = false;
    ifstream file;
    ofstream Archivo;
    string ruta2;

    ////Bucle While que impide el avance del programa, hasta que no se haya completado la lectura del archivo JSON Line
    //do
    //{
    //    cout << "Ingrese la ruta de archivo del archivo JSON Line (sin comillas)" << endl;

    //    cin >> ruta;

    //    //Lee el Json Line
    //    file.open(ruta,ios::in);

    //    cin.clear();

    //    system("cls");

    //    cout << "Error al abrir archivo" << endl;
    //    
    //} while (!file.is_open());

    //system("cls");

    //do
    //{
    //    
    //    cout << "Ingrese la direccion donde desea exportar los apartamentos recomendados (sin comillas)" << endl;
    //    cin >> ruta2;

    //    Archivo.open(ruta2 + "/Output.txt");

    //   
    //    cin.clear();

    //    system("cls");

    //    cerr << "No se pudo generar el Archivo.text" << endl;

    //} while (Archivo.fail());

    //system("cls");

    Archivo.open("C:/Users/Ishai/OneDrive/Documentos/Output2.txt");

    file.open("C:/Users/Ishai/source/repos/Lab1Estructura de Datos/input_challenge_lab_2.jsonl");


	// Crea un lector de JSON
	Json::Reader reader;
	Json::Value json;

    //String que representa cada linea del archivo
    string line;


    // Lee el archivo línea por línea
    while (getline(file, line))
    {

        // Parsea la línea JSON
        bool parsed = reader.parse(line, json, false);

        //Valida si se pudo parsear la línea JSON
        if (!parsed) {
            cerr << "Error al analizar la línea JSON: " << reader.getFormattedErrorMessages() << endl;
            return 1;
        }


        //Separa la linea JSON en dos inputs
        const Json::Value input1Array = json["input1"];
        const Json::Value input2Array = json["input2"];

        //Inicializa el vector de Apartamentos y de parámetros


        vector<Sector> Map;

        House nuevo = House();


        //Recorre cada elemento del Array: Input 1
        for (const auto& input1 : input1Array)
        {
            Json::Value services = input1["services"];
            const Json::Value builds = input1["builds"];

            list<string> servicios;


            list<House> Casas;
            list<Apartment> Apartamentos;
            list<Premises> Negocios;




            for (const auto& itemS : services.getMemberNames())
            {

                if (services[itemS].asBool())
                {

                    servicios.push_back(itemS);

                }
            }

            for (const auto& itemB : builds.getMemberNames())
            {
                if (itemB == "Houses")
                {
                    Json::Value houses = builds["Houses"];

                    for (const auto& house : houses)
                    {


                        Casas.push_back(House(house["address"].asString(), house["price"].asDouble(), house["contactPhone"].asString(), house["id"].asString(), house["zoneDangerous"].asString()));


                    }

                }

                if (itemB == "Apartments")
                {
                    Json::Value apartments = builds["Apartments"];

                    for (const auto& apartment : apartments)
                    {

                        Apartamentos.push_back(Apartment(apartment["address"].asString(), apartment["price"].asDouble(), apartment["contactPhone"].asString(), apartment["id"].asString(), apartment["isPetFriendly"].asBool()));


                    }

                }

                if (itemB == "Premises")
                {
                    Json::Value premises = builds["Premises"];

                    for (const auto& premise : premises)
                    {
                        list<string> locales;

                        Json::Value Activities = premise["commercialActivities"];

                        for (const auto& local : Activities)
                        {


                            locales.push_back(local.asString());

                        }

                        Negocios.push_back(Premises(premise["address"].asString(), premise["price"].asDouble(), premise["contactPhone"].asString(), premise["id"].asString(), locales));

                    }



                }


            }

            Map.push_back(Sector(servicios, Apartamentos, Casas, Negocios));



        }

        Search Busqueda;

            Busqueda.Type = input2Array["typeBuilder"].asString();
            Busqueda.budget = input2Array["budget"].asDouble();

            Json::Value ServiciosRequeridos = input2Array["requiredServices"];

            for (const auto& S1 : ServiciosRequeridos)
            {
                Busqueda.Services.push_back(S1.asString());
            }

            if (Busqueda.Type == "Houses")
            {

                Busqueda.Parameter = input2Array["minDanger"].asString();

            }
            else if (Busqueda.Type == "Premises")
            {
                Busqueda.Parameter = input2Array["commercialActivity"].asString();

            }else
            {
                Busqueda.Parameter = input2Array["wannaPetFriendly"].asBool();
            }

            function<void(Search, Sector, list<Recomendation>&)> filtro = bind(&Logica::Filtrado, &Recomendacion, placeholders::_1, placeholders::_2, std::placeholders::_3);
            list<string> resultados = Recomendacion.Results(Map, Busqueda, filtro);
        
            

            cout << "[";
            Archivo << "[";

            if (!resultados.empty()) {
                auto iter = resultados.begin();
                cout << "\"" << *iter << "\"";
                Archivo << "\"" << *iter << "\"";
                ++iter;

                for (; iter != resultados.end(); ++iter) {
                    std::cout <<  "," << "\""  << *iter << "\"";
                    Archivo << "," << "\"" << *iter << "\"";

              
                }
            }

            cout << "]" << endl;

            Archivo << "]" << endl;
           

             

        Map.clear();



    }

    // Cerrar el archivo
    file.close();
    Archivo.close();
}

