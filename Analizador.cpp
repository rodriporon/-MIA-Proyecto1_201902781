//
// Created by rodri on 3/03/22.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include "Analizador.h"

using namespace std;

struct mkdisk_attribs_struct mkdiskAttribsStruct;


void Analizador::analizar(string comando) {

    string value;
    string path;
    stringstream input_stringstream(comando);

    getline(input_stringstream, value, ' ');
    if (value == "exec") {
        getline(input_stringstream, value, '"');
        getline(input_stringstream, value, '"');
        path = value;
        cout << "El path del archivo script es: " << path << endl;
    } else {
        cout << "Escriba un comando correcto: exec" << endl;
    }



    ifstream archivo(path);
    string linea;
    string palabra;
    string attribs;
    string attrib;


    while (getline(archivo, linea)) {
        //cout << linea << endl;
        stringstream input_linea(linea);
        while (getline(input_linea, palabra, ' ')) {
            if (palabra == "#") {
                break;
            }

            if (toLower(palabra) == "mkdisk") {



                while (getline(input_linea, attribs, '-')) {

                    string type;
                    string delimiter = "=";
                    size_t pos = 0;
                    string token;

                    while ((pos = attribs.find(delimiter)) != string::npos) {
                        token = attribs.substr(0, pos);
                        type = token;

                        attribs.erase(0, pos + delimiter.length());
                    }
                    if (toLower(type) == "size") {
                        mkdiskAttribsStruct.size = stoi(attribs);
                    } else if (toLower(type) == "unit") {
                        strcpy(reinterpret_cast<char *>(mkdiskAttribsStruct.unit), attribs.c_str());
                    } else if (toLower(type) == "path") {
                        strcpy(mkdiskAttribsStruct.path, rutaAbsolutaF(attribs).c_str());
                    }


                }

                //mkdisk(mkdiskAttribsStruct);


            } else if (toLower(palabra) == "fdisk") {



                fdisk_attribs_struct fdiskAttribsStruct;


                while (getline(input_linea, attribs, '-')) {

                    string type;
                    string delimiter = "=";
                    size_t pos = 0;
                    string token;

                    while ((pos = attribs.find(delimiter)) != string::npos) {
                        token = attribs.substr(0, pos);
                        type = token;

                        attribs.erase(0, pos + delimiter.length());
                    }
                    if (toLower(type) == "size") {
                        fdiskAttribsStruct.size = stoi(attribs);
                    } else if (toLower(type) == "unit") {
                        strcpy(reinterpret_cast<char *>(fdiskAttribsStruct.unit), attribs.c_str());
                    } else if (toLower(type) == "path") {
                        strcpy(fdiskAttribsStruct.path, rutaAbsolutaF(attribs).c_str());
                    } else if (toLower(type) == "name") {
                        strcpy(fdiskAttribsStruct.name, attribs.c_str());
                    }


                }




            } else if (toLower(palabra) == "rep") {

                rep_attribs_struct repAttribsStruct;


                while (getline(input_linea, attribs, '-')) {

                    string type;
                    string delimiter = "=";
                    size_t pos = 0;
                    string token;

                    while ((pos = attribs.find(delimiter)) != string::npos) {
                        token = attribs.substr(0, pos);
                        type = token;

                        attribs.erase(0, pos + delimiter.length());
                    }
                    if (toLower(type) == "path") {
                        strcpy(repAttribsStruct.path, attribs.c_str());
                    }

                }
            }

        }
    }

    archivo.close();
    //fdisk(listFdisk);



}

string Analizador::toLower(string data) {
    string aux = data;
    for_each(aux.begin(), aux.end(), [](char & c) {
        c = tolower(c);
    });

    return aux;
}

std::string Analizador::rutaAbsolutaF(string path) {

    int contador = 0;
    string directorio = path;
    string lectura;
    string auxComillas;
    string rutaAbsoluta;
    string rutaRelativa;


    stringstream aux(directorio);
    while (getline(aux, lectura, '/')) {
        stringstream aux2(lectura);

        getline(aux2, auxComillas, '"');

        if (contador != 0) {
            rutaAbsoluta += "/";
            rutaAbsoluta += auxComillas;
        } else {
            rutaAbsoluta += auxComillas;
        }

        contador++;
    }

    return rutaAbsoluta;

}
