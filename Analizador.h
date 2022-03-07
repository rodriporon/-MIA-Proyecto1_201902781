//
// Created by rodri on 3/03/22.
//

#ifndef PROYECTO1_ANALIZADOR_H
#define PROYECTO1_ANALIZADOR_H


#include <iostream>

struct mkdisk_attribs_struct {
    int size;
    std::string unit;
    char path[300];
    std::string fit;
};

struct fdisk_attribs_struct {
    int size;
    std::string unit;
    char path[300];
    char name[25];
};

struct rmdisk_attribs_struct {
    char path[300];
};

struct  rep_attribs_struct {
    char path[300];
};

class Analizador {
public:

    void analizar(std::string comando);

    std::string toLower(std::string data);

    static std::string rutaAbsolutaF(std::string path);

    static std::string rutaRelativaF(std::string path);

};


#endif //PROYECTO1_ANALIZADOR_H
