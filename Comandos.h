//
// Created by rodri on 3/03/22.
//

#ifndef PROYECTO1_COMANDOS_H
#define PROYECTO1_COMANDOS_H

#include "Analizador.h"


struct mkdisk_attribs_struct;

struct EBR {
    char *part_status;
    char *part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};

struct PARTICION{
    char part_status[1];
    char part_type[1];
    char part_fit[2];
    char part_name[16];
    int part_start;
    int part_size;
};

struct MBR {
    int mbr_tamano;
    time_t mbr_fecha_creacion;
    int mbr_dsk_signature;
    char *dsk_fit;
    PARTICION particion[4];
};


class Comandos {
public:
    static void mkdisk(struct mkdisk_attribs_struct structmkdiskAttribsStruct);
    static void fdisk(struct fdisk_attribs_struct fdiskAttribsStruct);
    static void rmdisk(struct rmdisk_attribs_struct rmdiskAttribsStruct);
    static void mount(struct mount_attribs_struct mountAttribsStruct);
    static void rep(struct rep_attribs_struct repAttribsStruct);
};


#endif //PROYECTO1_COMANDOS_H
