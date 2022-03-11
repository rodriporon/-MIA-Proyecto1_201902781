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
        cerr << "Error: " << strerror(errno) << endl;
    } else {
        cout << "Directorio creado"     << endl;
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
        for (int i = 0; i < 4; ++i) {
            strncpy(mbr.particion[i].part_name, "-1", 200);
            mbr.particion[i].part_size = -1;
            mbr.particion[i].part_start = -1;
        }
        int seek = 0;

        fseek(file, seek, SEEK_SET);
        fwrite(&mbr, sizeof (MBR), 1, file);

        cout << "MBR registrado" << endl;
        fclose(file);
    }
}

void Comandos::fdisk(struct fdisk_attribs_struct fdiskAttribsStruct) {
    string path = fdiskAttribsStruct.path;
    path.erase(remove(path.end()-1, path.end(), ' '), path.end());

    FILE *file = fopen(path.c_str(), "rb+");
    int seek = 0;
    if (file != NULL) {
        MBR mbr_read;
        fseek(file, seek, SEEK_SET);
        fread(&mbr_read, sizeof (MBR), 1, file);
        int contador = 1;
        for (int i = 0; i < 4; ++i) {
            if ((mbr_read.particion[i].part_size == -1) && (mbr_read.particion[i].part_start = -1) && (strcmp(mbr_read.particion[i].part_name, "-1") == 0)) {
                cout << contador << endl;
                contador++;
            }
        }
        //strncpy(mbr_read.particion[0].part_name, "Primera", 25);
        fclose(file);
    } else {
        cout << "El disco con direccion: " << path << " no existe" << endl;
    }
}

void Comandos::rmdisk(struct rmdisk_attribs_struct rmdiskAttribsStruct) {
    if (remove(rmdiskAttribsStruct.path.c_str()) != 0) {
        cerr << "Error al borrar el disco: " << strerror(errno) << endl;
    } else {
        cout << "Disco con direccion: " << rmdiskAttribsStruct.path << " eliminado" << endl;
    }

}

void Comandos::mount(struct mount_attribs_struct mountAttribsStruct) {

}



