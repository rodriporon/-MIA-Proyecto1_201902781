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

int primarias = 0;
int extendidas = 0;

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
            strncpy(mbr.particion[i].part_name, "-1", 16);
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
    int part_size;
    string path = fdiskAttribsStruct.path;
    path.erase(remove(path.end()-1, path.end(), ' '), path.end());



    if (Analizador::toLower(fdiskAttribsStruct.type) == "p") {
        primarias++;
    } else if (Analizador::toLower(fdiskAttribsStruct.type) == "e") {
       extendidas++;
    }

    if (fdiskAttribsStruct.unit == "b") {
        part_size = fdiskAttribsStruct.size;

    } else if (fdiskAttribsStruct.unit == "k") {
        part_size = fdiskAttribsStruct.size * 1024;

    } else if (fdiskAttribsStruct.unit == "m") {
        part_size = fdiskAttribsStruct.size * 1024 * 1024;

    } else {
        part_size = fdiskAttribsStruct.size * 1024;
    }

    cout << part_size << endl;

    if (((primarias + extendidas) <= 4) && extendidas <= 1) {
        if (!((extendidas >= 2) && (Analizador::toLower(fdiskAttribsStruct.type) == "e"))){
            FILE *file = fopen(path.c_str(), "rb+");
            int seek = 0;
            MBR mbr_read;
            if (file != NULL) {

                fseek(file, seek, SEEK_SET);
                fread(&mbr_read, sizeof (MBR), 1, file);

                for (int i = 0; i < 4; ++i) {
                    if (mbr_read.particion[i].part_size == -1) {

                        cout << "La posición libre es: " << i << endl;
                        strncpy(mbr_read.particion[i].part_name, "0", 1);
                        strncpy(mbr_read.particion[i].part_name, fdiskAttribsStruct.name.c_str(), 16);
                        mbr_read.particion[i].part_size = part_size;
                        strncpy(mbr_read.particion[i].part_type, fdiskAttribsStruct.type.c_str(), 1);
                        strncpy(mbr_read.particion[i].part_fit, fdiskAttribsStruct.type.c_str(), 2);
                        fseek(file, seek, SEEK_SET);
                        fwrite(&mbr_read, sizeof (MBR), 1, file);
                        break;
                    }
                }

                fclose(file);
            } else {
                cout << "El disco con direccion: " << path << " no existe" << endl;
            }
        } else {
            cout << "Error: Solo puede haber una partición extendida" << endl;
        }

    } else {
        cout << "Se sobrepasó el máximo de particiones primarias y extendidas" << endl;
    }

    FILE *file = fopen(path.c_str(), "rb+");
    int seek = 0;
    MBR mbr_read;
    if (file != NULL) {
        fseek(file, seek, SEEK_SET);
        fread(&mbr_read, sizeof (MBR), 1, file);
        cout << "Particiones del disco: " << path << endl;

        for (int i = 0; i < 4; ++i) {
            cout << "Name: " << mbr_read.particion[i].part_name << " size: " << mbr_read.particion[i].part_size << endl;

        }
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

void Comandos::rep(struct rep_attribs_struct repAttribsStruct) {

}





