#include <iostream>
#include "Analizador.h"
using namespace std;

int main() {
    string comando;

    Analizador analizador;

    cout << "Rodrigo Antonio Porón De León - 201902781" <<endl;
    cout << "Ingrese el comando a ejecutar " << endl;

    getline(cin, comando, '\n');

    analizador.analizar(comando);

    return 0;
}
