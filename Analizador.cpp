//
// Created by rodri on 3/03/22.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <list>
#include "Analizador.h"
#include "Comandos.h"

using namespace std;

struct mkdisk_attribs_struct mkdiskAttribsStruct;


void Analizador::analizar(string comando) {

    string value;
    string palabraE;
    string path;
    string attribsE;
    stringstream input_stringstream(comando);

    while (getline(input_stringstream, palabraE, ' ')) {
        if (palabraE == "#") {
            break;
        }
        if (toLower(palabraE) == "exec") {
            while (getline(input_stringstream, attribsE, '-')) {

                string type;
                string delimiter = "=";
                size_t pos = 0;
                string token;


                while ((pos = attribsE.find(delimiter)) != string::npos) {
                    token = attribsE.substr(0, pos);
                    type = token;

                    attribsE.erase(0, pos + delimiter.length());
                }
                if (toLower(type) == "path") {
                    path = rutaAbsolutaF(attribsE);
                }
            }
        }
    }

    cout << "El path del script es: " << path << endl;

        ifstream archivo(path);
        string linea;
        string palabra;
        string attribs;
        string attrib;


        while (getline(archivo, linea)) {
            if (linea[0] == '#') {
                continue;
            }
            stringstream input_linea(linea);
            while (getline(input_linea, palabra, ' ')) {

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

                            mkdiskAttribsStruct.unit = attribs;
                        } else if (toLower(type) == "path") {
                            cout << "en mkdisk el path es: " << attribs.c_str() << endl;
                            mkdiskAttribsStruct.path = rutaAbsolutaF(attribs);
                        }


                    }

                    Comandos::mkdisk(mkdiskAttribsStruct);

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
                            attribs.erase(remove(attribs.begin(), attribs.end(), ' '));
                            fdiskAttribsStruct.unit = attribs;
                        } else if (toLower(type) == "path") {
                            fdiskAttribsStruct.path = rutaAbsolutaF(attribs);
                        } else if (toLower(type) == "name") {
                            fdiskAttribsStruct.name = attribs;
                        } else if (toLower(type) == "type") {
                            attribs.erase(remove(attribs.begin(), attribs.end(), ' '));
                            fdiskAttribsStruct.type = attribs;
                        } else if (toLower(type) == "fit") {
                            attribs.erase(remove(attribs.begin(), attribs.end(), ' '));
                            fdiskAttribsStruct.fit = attribs;
                        } else if (toLower(type) == "delete") {
                            attribs.erase(remove(attribs.begin(), attribs.end(), ' '));
                            fdiskAttribsStruct.deleteS = attribs;
                        } else if (toLower(type) == "add") {
                            fdiskAttribsStruct.add = stoi(attribs);
                        }
                    }

                    Comandos::fdisk(fdiskAttribsStruct);

                } else if (toLower(palabra) == "rmdisk") {

                    rmdisk_attribs_struct rmdiskAttribsStruct;
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
                            rmdiskAttribsStruct.path = attribs;
                        }

                    }

                    Comandos::rmdisk(rmdiskAttribsStruct);
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
                            repAttribsStruct.path = attribs;
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

std::string Analizador::rutaRelativaF(std::string path) {
    int contador = 0;
    int contadorRelativa = 0;
    string directorio = path;
    string lectura;
    string auxComillas;
    string rutaAbsoluta;
    string rutaRelativa;
    list<string> listStrings;

    stringstream aux(directorio);
    while (getline(aux, lectura, '/')) {
        stringstream aux2(lectura);

        getline(aux2, auxComillas, '"');

        listStrings.push_back(auxComillas);

        if (contador != 0) {
            rutaAbsoluta += "/";
            rutaAbsoluta += auxComillas;
        } else {
            rutaAbsoluta += auxComillas;
        }

        contador++;
    }

    list<string>::iterator it = listStrings.begin();
    auto one_before_end = listStrings.end();
    advance(one_before_end, -1);
    for (it; it != one_before_end; ++it) {
        if (contadorRelativa == 0) {
            rutaRelativa += *it;
        } else {
            rutaRelativa += "/";
            rutaRelativa += *it;
        }
        contadorRelativa++;

    }
    rutaRelativa += "/";
    return rutaRelativa;
}
