//
// Created by rodri on 3/03/22.
//

#ifndef PROYECTO1_ANALIZADOR_H
#define PROYECTO1_ANALIZADOR_H


#include <iostream>

struct mkdisk_attribs_struct {
    int size;
    std::string unit; // Megabytes predeterminado
    std::string path;
    std::string fit;
};

struct fdisk_attribs_struct {
    int size;
    std::string unit; // kilobytes predeterminado
    std::string path;
    std::string type;
    std::string fit; // peor ajuste WF
    std::string deleteS;
    std::string add;
    std::string name;
};

struct rmdisk_attribs_struct {
    std::string path;
};

struct mount_attribs_struct {
    std::string path;
    std::string name;
};

struct  rep_attribs_struct {
    std::string path;
};

class Analizador {
public:

    void analizar(std::string comando);

    std::string toLower(std::string data);

    static std::string rutaAbsolutaF(std::string path);

    static std::string rutaRelativaF(std::string path);

};


#endif //PROYECTO1_ANALIZADOR_H
