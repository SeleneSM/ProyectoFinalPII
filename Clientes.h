//
// Created by Selene on 13/06/2023.
//

#ifndef PROYECTO_FINAL_4_CLIENTES_H
#define PROYECTO_FINAL_4_CLIENTES_H

#include <iostream>
using namespace std;


class Clientes {
private:
    int nro_cliente;
    string nombre;
    string apellido;
    string tipo;
    int anio;
    string estado;

public:

    Clientes();
    Clientes(int _nro_cliente, std::string _nombre, std::string _apellido, std::string _tipo, int _anio, std::string _estado);


    int getNumeroCliente() const;
    void setNumeroCliente(int _numeroCliente);
    string getNombre();
    void setNombre(string _nombre);
    string getApellido();
    void setApellido(string _apellido);
    string getTipo();
    void setTipo(string _tipo);
    int getAnio();
    void setAnio(int _anio);
    string getEstado();
    void setEstado(string _estado);

};


#endif //PROYECTO_FINAL_4_CLIENTES_H
