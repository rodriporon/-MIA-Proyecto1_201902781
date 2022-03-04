//
// Created by rodri on 4/03/22.
//

#include <cstdio>
#include "Utils.h"


bool Utils::exists(const char *path) {
    FILE *file = NULL;
    file = fopen(path, "r");
    if (file == NULL) {
        return false;
    } else {
        fclose(file);
        return true;
    }
}

void Utils::clear(char *cadena, int tamano) {
    for (int i = 0; i < tamano; ++i) {
        cadena[i] = '\0';
    }
}
