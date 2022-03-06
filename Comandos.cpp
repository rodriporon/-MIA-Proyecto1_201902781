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


    string rutaRelativa = Analizador::rutaRelativaF(structmkdiskAttribsStruct.path);
    string rutaAbsoluta = Analizador::rutaAbsolutaF(structmkdiskAttribsStruct.path);

    MBR mbr{};
    MBR mbr_read{};

    mbr.mbr_dsk_signature = 0;
    mbr.mbr_fecha_creacion = time(0);

    if (structmkdiskAttribsStruct.unit == "b ") {
        mbr.mbr_tamano = structmkdiskAttribsStruct.size;

    } else if (structmkdiskAttribsStruct.unit == "k ") {
        mbr.mbr_tamano = structmkdiskAttribsStruct.size * 1024;

    } else if (structmkdiskAttribsStruct.unit == "m ") {
        mbr.mbr_tamano = structmkdiskAttribsStruct.size * 1024 * 1024;

    } else {
        mbr.mbr_tamano = structmkdiskAttribsStruct.size * 1024;
    }

    if (mkdir(rutaRelativa.c_str(), 0777) == -1) {
        cout << "Error: " << strerror(errno) << endl;
    } else {
        cout << "Directorio creado" << endl;
    }

    if (!Utils::exists(rutaAbsoluta.c_str())) {

        int tamano =  mbr.mbr_tamano;
        FILE *file = fopen(rutaAbsoluta.c_str(), "wb");
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
}

void Comandos::fdisk(struct fdisk_attribs_struct fdiskAttribsStruct) {
    cout << "Entro con path: " << fdiskAttribsStruct.path << endl;
    FILE *file = fopen(fdiskAttribsStruct.path, "rb+");
    int seek = 0;
    if (file != NULL) {
        MBR mbr_read;
        fseek(file, seek, SEEK_SET);
        fread(&mbr_read, sizeof (MBR), 1, file);
        cout << "Tamano: " << mbr_read.mbr_tamano << endl;
        fclose(file);
    }
}

