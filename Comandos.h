//
// Created by rodri on 3/03/22.
//

#ifndef PROYECTO1_COMANDOS_H
#define PROYECTO1_COMANDOS_H

#include "Analizador.h"

struct mkdisk_attribs_struct;

struct PARTICION{
    char part_name[25];
    int part_start;
    int part_size;
};

struct MBR {
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_dsk_signature;
    PARTICION particion[4];
};


class Comandos {
public:

    static void mkdisk(struct mkdisk_attribs_struct structmkdiskAttribsStruct);
    static void fdisk(struct fdisk_attribs_struct fdiskAttribsStruct);
    static void rmdisk(struct rmdisk_attribs_struct rmdiskAttribsStruct);

};


#endif //PROYECTO1_COMANDOS_H
