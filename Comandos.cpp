//
// Created by rodri on 3/03/22.
//

#include <iostream>
#include <sys/stat.h>
#include <cstring>
#include "Comandos.h"
#include "Analizador.h"
#include "Utils.h"
using namespace std;


void Comandos::mkdisk(struct mkdisk_attribs_struct structmkdiskAttribsStruct) {
    cout << "entro a mkdisk con path: " << structmkdiskAttribsStruct.path << endl;

    /* string rutaRelativa = Analizador::rutaRelativaF(structmkdiskAttribsStruct.path);
    string rutaAbsoluta = Analizador::rutaAbsolutaF(structmkdiskAttribsStruct.path);


    string unit = structmkdiskAttribsStruct.unit;
    string b = "b ";
    string k = "k ";
    string m = "m ";

    MBR mbr{};
    MBR mbr_read{};

    mbr.mbr_dsk_signature = 0;
    mbr.mbr_fecha_creacion = time(0);

    if (unit == b) {
        mbr.mbr_tamano = structmkdiskAttribsStruct.size;

    } else if (unit == k) {
        mbr.mbr_tamano = structmkdiskAttribsStruct.size * 1024;

    } else if (unit == m) {
        mbr.mbr_tamano = structmkdiskAttribsStruct.size * 1024 * 1024;

    }


    cout << "La ruta Absoluta es: " << rutaAbsoluta << endl;
    cout << "la ruta Relativa es: " << rutaRelativa << endl;

    if (mkdir(rutaRelativa.c_str(), 0777) == -1) {
        cerr << "Error: " << strerror(errno) << endl;
    } else {
        cout << "Directorio creado" << endl;
    }

    if (!Utils::exists(rutaAbsoluta.c_str())) {

        int tamano =  mbr.mbr_tamano;
        FILE *file = fopen(rutaAbsoluta.c_str(), "ab");
        if (file != NULL) {
            int endFile = tamano / 1024;
            char buffer[1024];
            Utils::clear(buffer, 1024);
            int i = 0;
            while (i != endFile) {
                fwrite(&buffer, 1024, 1, file);
                i++;
            }
            fclose(file);
        }
    }

    FILE *file = fopen(rutaAbsoluta.c_str(), "rb+");
    if (file != NULL) {
        int seek = 0;

        fseek(file, seek, SEEK_SET);
        fwrite(&mbr, sizeof (MBR), 1, file);
        cout << "MBR registrado" << endl;
        fclose(file);

    }
     */
}

