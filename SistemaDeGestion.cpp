//
// Created by Selene on 13/06/2023.
//

#include "SistemaDeGestion.h"
#include "Clientes.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <limits>


using namespace std;

template<typename T> //Funcion Template

T SolicitarDato(const string& mensaje){
    T dato;
    bool DatoValido = false;

    do{
        try{
            cout<<mensaje<<endl;
            cin>>dato;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Tipo de dato incorrecto. Ingrese un valor valido. ");
            }

            DatoValido = true;
        }
        catch(const exception& e){
            cout << "Error: " << e.what() << endl;

        }
    }while (!DatoValido);

    return dato;
}

template<> //Especializacion para el caso de string
string SolicitarDato<string>(const string& mensaje){
    string dato;
    bool DatoValido = false;

    do{
        try{
            cout<<mensaje<<endl;
            cin>>dato;

            for(char c : dato){
                if(isdigit(c)){
                    throw runtime_error("La cadena contiene un numero");
                }
            }

            DatoValido = true;
        }catch(const exception& e){
            cout << "Error: " << e.what() << endl;
        }
    }while (!DatoValido);

    return dato;
}


void SistemaDeGestion::CargarDeArchivo() { //Carga de arhivos tanto de clientes como de transacciones
    //Clientes
    try{

    ifstream archivoClientes;
    archivoClientes.open("Clientes.txt");

    if(archivoClientes.is_open()){
        string linea;

        Clientes c;
        int nro_cliente;
        string nombre;
        string apellido;
        string tipo;
        int anio;
        string estado;
        while(getline(archivoClientes, linea)){
            archivoClientes >> nro_cliente >> nombre >> apellido >> tipo >> anio >> estado;
            c.setNumeroCliente(nro_cliente);
            c.setNombre(nombre);
            c.setApellido(apellido);
            c.setTipo(tipo);
            c.setAnio(anio);
            c.setEstado(estado);
            vector_clientes.push_back(c);
        }
        //Cargo lo que hay en el archivo en el vector_clientes

    }


    }

    catch (const ifstream::failure& e) {
        // Error al abrir o leer el archivo
        cout << "Error al leer el archivo de clientes." << endl;
    } catch (...) {
        // Error desconocido
        cout << "Se produjo un error inesperado." << endl;
    }
    //Transacciones
    try{

        ifstream archivoTransacciones;
        archivoTransacciones.open("Transacciones.txt");

        if(archivoTransacciones.is_open()){
            string linea;

            Transacciones t;
            int nro_cliente;
            int nro_transaccion;
            int cantidad;
            char tipo;
            int dia;
            int mes;
            int anio;
            while(getline(archivoTransacciones, linea)){
                archivoTransacciones >> nro_cliente >> nro_transaccion >> cantidad >> tipo >> dia >> mes >> anio;
                t.set_nro_cliente(nro_cliente);
                t.set_nro_transaccion(nro_transaccion);
                t.set_cantidad(cantidad);
                t.set_tipo(tipo);
                t.set_dia(dia);
                t.set_mes(mes);
                t.set_anio(anio);
                vector_transacciones.push_back(t);
            }
            //Cargo lo que hay en el archivo en el vector_transacciones

        }


    }

    catch (const ifstream::failure& e) {
        // Error al abrir o leer el archivo
        cout << "Error al leer el archivo de clientes." << endl;
    } catch (...) {
        // Error desconocido
        cout << "Se produjo un error inesperado." << endl;
    }
}

void SistemaDeGestion::CargarNuevoCliente() {
    try{

        string nombre, apellido, tipo, estado;
        int anio;

        Clientes _nuevocliente;

        nombre = SolicitarDato<string>("Ingrese el nombre del cliente:");
        apellido = SolicitarDato<string>("Ingrese el apellido del cliente:");

        anio = SolicitarDato<int>("Ingrese el anio de alta del cliente:");

        estado = SolicitarDato<string>("Ingrese el estado del cliente:");


        if(anio>=2021){

            tipo="plata";

        }

        if(anio<2021 && anio>=2019){

            tipo="oro";

        }

        if(anio<2019){

            tipo="black";

        }

        _nuevocliente.setNombre(nombre);
        _nuevocliente.setApellido(apellido);
        _nuevocliente.setTipo(tipo);
        _nuevocliente.setAnio(anio);
        _nuevocliente.setEstado(estado);
        _nuevocliente.setNumeroCliente(vector_clientes.size()+1);
        cout << vector_clientes.size() << endl;

        vector_clientes.push_back(_nuevocliente); //Carga un nuevo cliente en el vector_clientes

        cout << vector_clientes.size() << endl;


        CargarNuevoClienteArchivo(_nuevocliente);




    }

    catch (const exception& e) {
        cout << "Error al agregar un nuevo cliente: " << e.what() << endl;
    }
    catch (...) {
        // Error desconocido
        cout << "Se produjo un error inesperado." << endl;
    }

    return;
}

void SistemaDeGestion::CargarNuevoClienteArchivo(Clientes c) {
    //En este metodo guardo el vector_clientes con su info vieja mas la nueva en el arhivo
    ofstream arch;
    arch.open("Clientes.txt",ofstream::app);
    //Lo abro en modo apertura y no borra lo que hay :) !!!!

    if(arch.is_open()){

        arch << endl <<"    "<< c.getNumeroCliente() << "            " << c.getNombre() << "   " << c.getApellido()
             << "  " << c.getTipo()<< "   " << c.getAnio()<< "    " << c.getEstado();
    }else{
        cout << "No se abrio el archivo" << endl;
    }
}

void SistemaDeGestion::Consulta_NumeroCliente()  {
    int numero_cliente;

    numero_cliente = SolicitarDato<int>("Ingrese el numero del cliente que quiere consultar:");


    for (int i=0; i<vector_clientes.size(); i++) {

        if (vector_clientes[i].getNumeroCliente() == numero_cliente) {

            cout<<"******* DATOS DE SU CLIENTE ******"<<endl;
            cout<<endl;
            cout<<"Nombre: "<<vector_clientes[i].getNombre()<<endl;
            cout<<"Apellido: "<<vector_clientes[i].getApellido()<<endl;
            cout<<"Tipo: "<<vector_clientes[i].getTipo()<<endl;
            cout<<"Anio: "<<vector_clientes[i].getAnio()<<endl;
            cout<<"Estado: "<<vector_clientes[i].getEstado()<<endl;
            cout<<endl;

            if(vector_clientes[i].getTipo() == "oro"){

                std::cout << "******************************************" << std::endl;
                std::cout << "* TIENE ACCESO A UNA TARJETA DE $50.000  *" << std::endl;
                std::cout << "******************************************" << std::endl;

            }

            if(vector_clientes[i].getTipo() == "black"){

                std::cout << "******************************************" << std::endl;
                std::cout << "* TIENE ACCESO A UNA TARJETA DE $250.000 *" << std::endl;
                std::cout << "******************************************" << std::endl;

            }

            cout<<endl;
            cout<<endl;
            break;
        }
    }


}

void SistemaDeGestion::ConsultaTransaccionporCliente() {
    int numero_cliente;

    numero_cliente = SolicitarDato<int>("Ingrese el numero del cliente que quiere consultar sus transacciones:");


    for (int i=0; i<vector_transacciones.size(); i++){

        if(vector_transacciones[i].get_nro_cliente()==numero_cliente){

            cout << "*****INFORMACION DE TRANSACCION NUMERO " << vector_transacciones[i].get_nro_transacciones()
                 << "  :*****" << endl;
            cout <<"Cantidad :"<< vector_transacciones[i].get_cantidad() <<endl;
            cout <<"Tipo :" <<vector_transacciones[i].get_tipo() << endl;
            cout <<"Fecha:"<<vector_transacciones[i].get_dia()<<"/";
            cout << vector_transacciones[i].get_mes()<<"/";
            cout << vector_transacciones[i].get_anio()<<"/"<< endl;
            cout << endl;

        }
    }


}

void SistemaDeGestion::HacerTransaccion() {
    int nro_cliente;
    int anio, mes, dia, cantidad;
    char tipo;

    Transacciones _nuevaTransaccion;

    nro_cliente = SolicitarDato<int>("Ingrese el numero del cliente:");

    if(vector_clientes[nro_cliente].getEstado() == "baja"){

        cout<<"+++++++++  ALERTA  ++++++++++"<<endl;

        cout<<"USTED NO PUEDE HACER UNA TRANSACCION YA QUE SE ENCUENTRA EN ESTADO DE BAJA "<<endl;
        cout<<endl;


    }

    else{
        tipo = SolicitarDato<char>("Ingrese el tipo de transferencia:");
        cantidad = SolicitarDato<int>("Ingrese la cantidad:");
        dia = SolicitarDato<int>("Ingrese el dia:");
        mes = SolicitarDato<int>("Ingrese el mes:");
        anio = SolicitarDato<int>("Ingrese el anio:");

        _nuevaTransaccion.set_nro_cliente(nro_cliente);
        _nuevaTransaccion.set_anio(anio);
        _nuevaTransaccion.set_dia(dia);
        _nuevaTransaccion.set_mes(mes);
        _nuevaTransaccion.set_cantidad(cantidad);
        _nuevaTransaccion.set_tipo(tipo);
        _nuevaTransaccion.set_nro_transaccion(vector_transacciones.size()+1);

        vector_transacciones.push_back(_nuevaTransaccion);

        CargarTransaccionArchivo(_nuevaTransaccion);


    }
}

void SistemaDeGestion::CargarTransaccionArchivo(Transacciones t) {
    ofstream trans;
    trans.open("Transacciones.txt",ofstream::app);
    //Lo abro en modo apertura y no borra lo que hay :)

    if(trans.is_open()){

        trans << endl << t.get_nro_cliente() << "            " << t.get_nro_transacciones() << "                 " << t.get_cantidad()
             << "                " << t.get_tipo()<< "             " << t.get_dia()<< "            " << t.get_mes() << "             " << t.get_anio();
    }else{
        cout << "No se abrio el archivo" << endl;
    }

}

void SistemaDeGestion::ConsultaTransaccion_6_meses() {
    int anio;
    int periodo, periodo_1;

    anio = SolicitarDato<int>("Ingrese el anio que desea consultar la transaccion:");

    periodo = SolicitarDato<int>("Ingrese el periodo del ao al que quiere consultar (1 = primero, 2 = segundo) :");


    for (int i=0; i<vector_transacciones.size(); i++){

        if(vector_transacciones[i].get_mes()<=6){


            periodo_1=1;

        }

        if(vector_transacciones[i].get_mes()>6){

            periodo_1=2;

        }

        if(vector_transacciones[i].get_anio() == anio && periodo == periodo_1){

            cout << "*****INFORMACION DE TRANSACCION :*****" << endl;

            cout << "Numero de cliente: "<< vector_transacciones[i].get_nro_cliente()<<endl;
            cout <<"Cantidad: "<< vector_transacciones[i].get_cantidad() <<endl;
            cout <<"Tipo: " <<vector_transacciones[i].get_tipo() << endl;
            cout << "Fecha: "<<vector_transacciones[i].get_dia()<<"/";
            cout << vector_transacciones[i].get_mes()<<"/";
            cout << vector_transacciones[i].get_anio()<<endl;
            cout << endl;

        }
    }

}

void SistemaDeGestion::ConsultaTransaccion_anio() {
    int _anio;

    _anio = SolicitarDato<int>("Ingrese el anio que desea consultar la transaccion:");

    for (int i=0; i<vector_transacciones.size(); i++){

        if(vector_transacciones[i].get_anio()==_anio){

            cout << "*****INFORMACION DE TRANSACCIONES EN EL ANIO " << vector_transacciones[i].get_anio()<<":*****"<< endl;
            cout << "numero de cliente: "<< vector_transacciones[i].get_nro_cliente()<<endl;
            cout <<"cantidad: "<< vector_transacciones[i].get_cantidad() <<endl;
            cout <<"tipo: " <<vector_transacciones[i].get_tipo() << endl;
            cout << "fecha: "<<vector_transacciones[i].get_dia()<<"/";
            cout << "*****INFORMACION DE TRANSACCIONES EN EL DIA " << vector_transacciones[i].get_dia()
                 << " Y EL MES "<< vector_transacciones[i].get_mes()<<"  :*****"<< endl;
            cout << "numero de cliente :"<< vector_transacciones[i].get_nro_cliente();
            cout <<"cantidad :"<< vector_transacciones[i].get_cantidad() <<endl;
            cout <<"tipo :" <<vector_transacciones[i].get_tipo() << endl;
            cout << "fecha:"<<vector_transacciones[i].get_dia()<<"/";
            cout << vector_transacciones[i].get_mes()<<"/";
            cout << vector_transacciones[i].get_anio()<< endl;
            cout << endl;

        }
    }

}

void SistemaDeGestion::ConsultaTransaccion_total() {
    for (int i=0; i<vector_transacciones.size(); i++){

        cout << "*****INFORMACION DE TRANSACCIONES TOTAL " << vector_transacciones[i].get_dia()<<"/"<< vector_transacciones[i].get_mes()<<"/"<< vector_transacciones[i].get_anio()
             << "  :*****" << endl;


        cout << "numero de cliente: "<< vector_transacciones[i].get_nro_cliente()<<endl;
        cout <<"cantidad: "<< vector_transacciones[i].get_cantidad() <<endl;
        cout <<"tipo: " <<vector_transacciones[i].get_tipo() << endl;
        cout << "fecha: "<<vector_transacciones[i].get_dia()<<"/";
        cout << vector_transacciones[i].get_mes()<<"/";
        cout << vector_transacciones[i].get_anio()<<endl;
        cout << endl;
        cout <<endl;


    }
}

void SistemaDeGestion::ConsultaTodosClientes() {
    for (int i=0; i<vector_clientes.size(); i++){

        cout << "*****INFORMACION DE TODOS LOS CLIENTES ******"<<endl;

        cout<<"Numero de Cliente :"<<vector_clientes[i].getNumeroCliente();
        cout<<"Nombre: "<<vector_clientes[i].getNombre()<<endl;
        cout<<"Apellido: "<<vector_clientes[i].getApellido()<<endl;
        cout<<"Tipo: "<<vector_clientes[i].getTipo()<<endl;
        cout<<"Anio: "<<vector_clientes[i].getAnio()<<endl;
        cout<<"Estado: "<<vector_clientes[i].getEstado()<<endl;
        cout<<endl;

    }
}

void SistemaDeGestion::DardeBajaCliente() {
    int Nro_Cliente;

    Nro_Cliente = SolicitarDato<int>("Ingrese el numero del cliente al que le quiere le cambiar el Estado a Baja:");

    for (int i=0; i<vector_clientes.size(); i++) {

        if (vector_clientes[i].getNumeroCliente() == Nro_Cliente) {
            vector_clientes[i].setEstado("Baja");

            cout<<"***** SE LE HA CAMBIADO EL ESTADO AL CLIENTE DE NUMERO "<<Nro_Cliente<<" DE ACTIVO A BAJA"<<endl;
            cout<<endl;
            break;
        }
    }
}


