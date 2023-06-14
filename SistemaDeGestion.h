//
// Created by Selene on 13/06/2023.
//

#ifndef PROYECTO_FINAL_4_SISTEMADEGESTION_H
#define PROYECTO_FINAL_4_SISTEMADEGESTION_H

#include <iostream>
#include "Clientes.h"
#include "Transacciones.h"
#include <vector>

using namespace std;


class SistemaDeGestion {
private:
    vector<Transacciones> vector_transacciones;
    vector<Clientes> vector_clientes;

public:
    void CargarDeArchivo();

    void CargarNuevoCliente();
    void CargarNuevoClienteArchivo(Clientes);
    void Consulta_NumeroCliente();
    void ConsultaTodosClientes();

    void ConsultaTransaccionporCliente();
    void HacerTransaccion();
    void CargarTransaccionArchivo(Transacciones);
    void ConsultaTransaccion_6_meses();
    void ConsultaTransaccion_anio();
    void ConsultaTransaccion_total();
    void DardeBajaCliente();





};


#endif //PROYECTO_FINAL_4_SISTEMADEGESTION_H
